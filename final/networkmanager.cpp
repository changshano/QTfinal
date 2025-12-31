#include "networkmanager.h"
#include <QDateTime>
#include <QCryptographicHash>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    // 创建缓存目录
    m_cacheDir = QDir::currentPath() + "/cache";
    QDir dir(m_cacheDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &NetworkManager::onAdsFetched);
}

NetworkManager::~NetworkManager()
{
    m_networkManager->deleteLater();
}

void NetworkManager::fetchAds()
{
    // 模拟从服务器获取广告列表
    // 实际应用中替换为真实的服务器URL
    QString serverUrl = "http://192.168.1.100:8080/api/ads";
    QUrl url(serverUrl);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("User-Agent", "ElevatorAdSystem/1.0");

    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onAdsFetched(reply);
    });

    // 记录请求时间
    qDebug() << "开始获取广告列表:" << QDateTime::currentDateTime().toString();
}

void NetworkManager::downloadAd(const QString &url, const QString &adId, const QString &type)
{
    if (url.isEmpty()) {
        qWarning() << "广告URL为空, adId:" << adId;
        return;
    }

    QUrl qurl(url);
    QNetworkRequest request(qurl);
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                         QNetworkRequest::NoLessSafeRedirectPolicy);

    QNetworkReply *reply = m_networkManager->get(request);
    m_downloadMap[reply] = adId;
    m_typeMap[reply] = type;

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onAdDownloaded(reply);
    });

    qDebug() << "开始下载广告:" << adId << "URL:" << url;
}

void NetworkManager::onAdsFetched(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        parseAdsJson(data);
    } else {
        emit errorOccurred("获取广告列表失败: " + reply->errorString());
        qDebug() << "获取广告列表失败:" << reply->errorString();
    }

    reply->deleteLater();
}

void NetworkManager::onAdDownloaded(QNetworkReply *reply)
{
    QString adId = m_downloadMap.take(reply);
    QString type = m_typeMap.take(reply);

    if (!adId.isEmpty() && reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        // 保存到缓存文件
        QString filename = adId;
        if (type == "image") {
            // 从Content-Type或URL推断扩展名
            QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
            if (contentType.contains("jpeg") || contentType.contains("jpg")) {
                filename += ".jpg";
            } else if (contentType.contains("png")) {
                filename += ".png";
            } else if (contentType.contains("gif")) {
                filename += ".gif";
            } else {
                filename += ".dat";
            }
        } else if (type == "text") {
            filename += ".txt";
        }

        QString cachePath = getCachePath(filename);
        QFile file(cachePath);

        if (file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.close();

            QString content = (type == "text") ? QString::fromUtf8(data) : "";

            emit adContentReady(adId, type, content, cachePath);
            qDebug() << "广告下载成功:" << adId << "保存到:" << cachePath;
        } else {
            emit errorOccurred("无法保存文件: " + cachePath);
        }
    } else if (!adId.isEmpty()) {
        emit errorOccurred("下载广告失败: " + adId + " - " + reply->errorString());
    }

    reply->deleteLater();
}

QString NetworkManager::getCachePath(const QString &filename)
{
    return m_cacheDir + "/" + filename;
}

void NetworkManager::parseAdsJson(const QByteArray &data)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        emit errorOccurred("JSON解析错误: " + parseError.errorString());
        return;
    }

    if (!doc.isArray()) {
        emit errorOccurred("广告数据格式错误: 不是数组");
        return;
    }

    QJsonArray adArray = doc.array();
    int downloadedCount = 0;

    for (const QJsonValue &value : adArray) {
        if (!value.isObject()) continue;

        QJsonObject adObj = value.toObject();
        QString adId = adObj["id"].toString();
        QString title = adObj["title"].toString();
        QString type = adObj["type"].toString();
        QString content = adObj["content"].toString();
        QString remoteUrl = adObj["url"].toString();
        int duration = adObj["duration"].toInt(5);
        int priority = adObj["priority"].toInt(1);

        if (adId.isEmpty() || title.isEmpty()) {
            qWarning() << "广告数据不完整，跳过";
            continue;
        }

        // 下载广告内容
        if (!remoteUrl.isEmpty()) {
            downloadAd(remoteUrl, adId, type);
            downloadedCount++;
        } else if (type == "text" && !content.isEmpty()) {
            // 文本广告直接保存
            emit adContentReady(adId, type, content, "");
        }
    }

    if (downloadedCount > 0) {
        qDebug() << "开始下载" << downloadedCount << "个广告";
    } else {
        emit adsUpdated();
    }
}
