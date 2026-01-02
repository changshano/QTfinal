#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    void fetchAds();

signals:
    void adContentReady(const QString &adId, const QString &type,
                        const QString &content, const QString &localPath);
    void adsUpdated();
    void errorOccurred(const QString &error);

private slots:
    void onAdDownloaded(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_cacheDir;

    QString getCachePath(const QString &filename);
    bool saveToCache(const QByteArray &data, const QString &filename);
};
#endif // NETWORKMANAGER_H
