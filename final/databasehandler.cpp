#include "databasehandler.h"
#include <QDir>
#include <QDebug>
#include <QSqlError>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseHandler::~DatabaseHandler()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseHandler::initDatabase()
{
    // 创建数据目录
    QString dataDir = "data";
    QDir dir(dataDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // 设置数据库文件路径
    m_db.setDatabaseName(dataDir + "/elevator_ads.db");

    if (!m_db.open()) {
        qDebug() << "无法打开数据库:" << m_db.lastError().text();
        return false;
    }

    return createTables();
}

bool DatabaseHandler::createTables()
{
    QSqlQuery query;

    // 创建广告表
    QString createAdTable =
        "CREATE TABLE IF NOT EXISTS ads ("
        "    id TEXT PRIMARY KEY,"
        "    title TEXT NOT NULL,"
        "    type TEXT NOT NULL,"
        "    content TEXT,"
        "    remote_url TEXT,"
        "    local_path TEXT,"
        "    last_update DATETIME"
        ");";

    if (!query.exec(createAdTable)) {
        qDebug() << "创建广告表失败:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::updateAd(const QVariantMap &adData)
{
    QSqlQuery query;
    query.prepare(
        "INSERT OR REPLACE INTO ads (id, title, type, content, remote_url, local_path, last_update) "
        "VALUES (:id, :title, :type, :content, :remote_url, :local_path, :last_update)"
        );

    query.bindValue(":id", adData["id"].toString());
    query.bindValue(":title", adData["title"].toString());
    query.bindValue(":type", adData["type"].toString());
    query.bindValue(":content", adData["content"].toString());
    query.bindValue(":remote_url", adData.value("remote_url").toString());
    query.bindValue(":local_path", adData["local_path"].toString());
    query.bindValue(":last_update", adData["last_update"].toString());

    if (!query.exec()) {
        qDebug() << "更新广告失败:" << query.lastError().text();
        return false;
    }

    return true;
}

QList<QVariantMap> DatabaseHandler::getAllAds()
{
    QList<QVariantMap> ads;
    QSqlQuery query("SELECT * FROM ads ORDER BY last_update DESC");

    while (query.next()) {
        QVariantMap ad;
        ad["id"] = query.value("id").toString();
        ad["title"] = query.value("title").toString();
        ad["type"] = query.value("type").toString();
        ad["content"] = query.value("content").toString();
        ad["remote_url"] = query.value("remote_url").toString();
        ad["local_path"] = query.value("local_path").toString();
        ad["last_update"] = query.value("last_update").toString();
        ads.append(ad);
    }

    return ads;
}
