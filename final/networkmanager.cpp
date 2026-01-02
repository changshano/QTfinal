#include "networkmanager.h"
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    m_cacheDir = "cache";
    QDir dir(m_cacheDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

NetworkManager::~NetworkManager()
{
    m_networkManager->deleteLater();
}

void NetworkManager::fetchAds()
{
    QStringList adUrls = {
        "https://picsum.photos/400/300?random=1",
        "https://picsum.photos/400/300?random=2",
        "https://picsum.photos/400/300?random=3",
        "https://picsum.photos/400/300?random=4",
        "https://picsum.photos/400/300?random=5"
    };

    for (int i = 0; i < adUrls.size(); i++) {
        QString adId = QString("ad_%1").arg(i+1);
        QString url = adUrls[i];

        QNetworkRequest request((QUrl(url)));
        QNetworkReply *reply = m_networkManager->get(request);

        // 存储广告ID用于回调
        reply->setProperty("adId", adId);

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            onAdDownloaded(reply);
        });
    }

    QString adId = "ad_text_1";
    emit adContentReady(adId, "text", "欢迎使用电梯广告系统！", "");

    qDebug() << "开始获取广告";
}

void NetworkManager::onAdDownloaded(QNetworkReply *reply)
{
    QString adId = reply->property("adId").toString();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        // 保存到缓存文件
        QString filename = adId + ".jpg";
        QString cachePath = getCachePath(filename);

        if (saveToCache(data, filename)) {
            QString content = QString("广告图片 %1").arg(adId);
            emit adContentReady(adId, "image", content, cachePath);
        } else {
            emit errorOccurred("无法保存文件:" + cachePath);
        }
    } else {
        emit errorOccurred("下载广告失败:" + reply->errorString());
    }

    reply->deleteLater();
}

QString NetworkManager::getCachePath(const QString &filename)
{
    return m_cacheDir + "/" + filename;
}

bool NetworkManager::saveToCache(const QByteArray &data, const QString &filename)
{
    QString cachePath = getCachePath(filename);
    QFile file(cachePath);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "无法打开文件:" << cachePath;
        return false;
    }

    qint64 bytesWritten = file.write(data);
    file.close();

    if (bytesWritten <= 0) {
        qDebug() << "写入文件失败:" << cachePath;
        return false;
    }

    qDebug() << "缓存文件保存成功:" << cachePath << "大小:" << bytesWritten << "字节";
    return true;
}
