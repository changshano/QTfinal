#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>
#include <QList>
#include <QDebug>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    ~DatabaseHandler();

    bool initDatabase();
    bool addAd(const QVariantMap &adData);
    bool updateAd(const QVariantMap &adData);
    bool removeAd(const QString &adId);
    QList<QVariantMap> getAllAds();
    QVariantMap getAd(const QString &adId);
    bool clearAllAds();

private:
    QSqlDatabase m_db;
    bool createTables();
};
#endif // DATABASEHANDLER_H
