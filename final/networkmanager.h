#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    void fetchAds();
    void downloadAd(const QString &url, const QString &adId, const QString &type);

signals:
    void adContentReady(const QString &adId, const QString &type,
                        const QString &content, const QString &localPath);
    void adsUpdated();
    void errorOccurred(const QString &error);

private slots:
    void onAdsFetched(QNetworkReply *reply);
    void onAdDownloaded(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    QMap<QNetworkReply*, QString> m_downloadMap; // reply -> adId
    QMap<QNetworkReply*, QString> m_typeMap;    // reply -> ad type
    QString m_cacheDir;

    QString getCachePath(const QString &filename);
    void parseAdsJson(const QByteArray &data);
};
#endif // NETWORKMANAGER_H
