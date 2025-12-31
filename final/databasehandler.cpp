#include "databasehandler.h"
#include <QDir>
#include <QStandardPaths>

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
    QString dataDir = QDir::currentPath() + "/data";
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
        "    type TEXT NOT NULL,"  // 'image' 或 'text'
        "    content TEXT,"        // 对于文字广告，存储文字内容
        "    remote_url TEXT,"
        "    local_path TEXT,"
        "    duration INTEGER DEFAULT 5,"  // 显示时长(秒)
        "    priority INTEGER DEFAULT 1,"  // 优先级
        "    valid_from DATETIME,"
        "    valid_to DATETIME,"
        "    last_update DATETIME,"
        "    created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    if (!query.exec(createAdTable)) {
        qDebug() << "创建广告表失败:" << query.lastError().text();
        return false;
    }

    // 创建播放计划表
    QString createPlanTable =
        "CREATE TABLE IF NOT EXISTS play_plans ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    ad_id TEXT NOT NULL,"
        "    play_order INTEGER NOT NULL,"
        "    start_time DATETIME,"
        "    end_time DATETIME,"
        "    enabled BOOLEAN DEFAULT 1,"
        "    FOREIGN KEY (ad_id) REFERENCES ads (id) ON DELETE CASCADE"
        ");";

    if (!query.exec(createPlanTable)) {
        qDebug() << "创建播放计划表失败:" << query.lastError().text();
        return false;
    }

    // 创建系统配置表
    QString createConfigTable =
        "CREATE TABLE IF NOT EXISTS system_config ("
        "    key TEXT PRIMARY KEY,"
        "    value TEXT NOT NULL,"
        "    description TEXT,"
        "    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    if (!query.exec(createConfigTable)) {
        qDebug() << "创建配置表失败:" << query.lastError().text();
        return false;
    }

    // 插入默认配置
    QString insertDefaultConfig =
        "INSERT OR IGNORE INTO system_config (key, value, description) VALUES "
        "('ad_interval', '5', '广告切换间隔(秒)'),"
        "('server_url', 'http://192.168.1.100:8080/api', '服务器地址'),"
        "('update_interval', '300', '广告更新间隔(秒)'),"
        "('cache_expiry', '86400', '缓存过期时间(秒)');";

    if (!query.exec(insertDefaultConfig)) {
        qDebug() << "插入默认配置失败:" << query.lastError().text();
    }

    return true;
}

bool DatabaseHandler::addAd(const QVariantMap &adData)
{
    QSqlQuery query;
    query.prepare(
        "INSERT OR REPLACE INTO ads (id, title, type, content, remote_url, "
        "local_path, duration, priority, valid_from, valid_to, last_update) "
        "VALUES (:id, :title, :type, :content, :remote_url, :local_path, "
        ":duration, :priority, :valid_from, :valid_to, :last_update)"
        );

    query.bindValue(":id", adData["id"].toString());
    query.bindValue(":title", adData["title"].toString());
    query.bindValue(":type", adData["type"].toString());
    query.bindValue(":content", adData["content"].toString());
    query.bindValue(":remote_url", adData["remote_url"].toString());
    query.bindValue(":local_path", adData["local_path"].toString());
    query.bindValue(":duration", adData["duration"].toInt());
    query.bindValue(":priority", adData["priority"].toInt());
    query.bindValue(":valid_from", adData["valid_from"].toString());
    query.bindValue(":valid_to", adData["valid_to"].toString());
    query.bindValue(":last_update", adData["last_update"].toString());

    if (!query.exec()) {
        qDebug() << "添加广告失败:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::updateAd(const QVariantMap &adData)
{
    return addAd(adData); // 使用 REPLACE 语义
}

bool DatabaseHandler::removeAd(const QString &adId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ads WHERE id = :id");
    query.bindValue(":id", adId);

    if (!query.exec()) {
        qDebug() << "删除广告失败:" << query.lastError().text();
        return false;
    }

    return true;
}

QList<QVariantMap> DatabaseHandler::getAllAds()
{
    QList<QVariantMap> ads;
    QSqlQuery query("SELECT * FROM ads ORDER BY priority DESC, created_at DESC");

    while (query.next()) {
        QVariantMap ad;
        ad["id"] = query.value("id").toString();
        ad["title"] = query.value("title").toString();
        ad["type"] = query.value("type").toString();
        ad["content"] = query.value("content").toString();
        ad["remote_url"] = query.value("remote_url").toString();
        ad["local_path"] = query.value("local_path").toString();
        ad["duration"] = query.value("duration").toInt();
        ad["priority"] = query.value("priority").toInt();
        ad["valid_from"] = query.value("valid_from").toString();
        ad["valid_to"] = query.value("valid_to").toString();
        ad["last_update"] = query.value("last_update").toString();
        ads.append(ad);
    }

    return ads;
}

QVariantMap DatabaseHandler::getAd(const QString &adId)
{
    QVariantMap ad;
    QSqlQuery query;
    query.prepare("SELECT * FROM ads WHERE id = :id");
    query.bindValue(":id", adId);

    if (query.exec() && query.next()) {
        ad["id"] = query.value("id").toString();
        ad["title"] = query.value("title").toString();
        ad["type"] = query.value("type").toString();
        ad["content"] = query.value("content").toString();
        ad["remote_url"] = query.value("remote_url").toString();
        ad["local_path"] = query.value("local_path").toString();
        ad["duration"] = query.value("duration").toInt();
        ad["priority"] = query.value("priority").toInt();
        ad["valid_from"] = query.value("valid_from").toString();
        ad["valid_to"] = query.value("valid_to").toString();
        ad["last_update"] = query.value("last_update").toString();
    }

    return ad;
}

bool DatabaseHandler::clearAllAds()
{
    QSqlQuery query("DELETE FROM ads");
    return query.exec();
}
