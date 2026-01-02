#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantMap>
#include <QList>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    ~DatabaseHandler();

    bool initDatabase();
    bool updateAd(const QVariantMap &adData);
    QList<QVariantMap> getAllAds();

private:
    QSqlDatabase m_db;
    bool createTables();
};
#endif // DATABASEHANDLER_H
