#include "adupdateworker.h"

AdUpdateWorker::AdUpdateWorker(QObject *parent)
    : QObject(parent)
    , m_updateTimer(new QTimer(this))
{
    m_updateTimer->setInterval(300000); // 5分钟检查一次更新

    connect(m_updateTimer, &QTimer::timeout,
            this, &AdUpdateWorker::checkForUpdates);
}

void AdUpdateWorker::start()
{
    if (m_isRunning) return;

    m_isRunning = true;
    m_updateTimer->start();

    emit updateProgress("后台更新服务已启动");
    qDebug() << "后台更新线程启动";

    // 启动后立即检查一次更新
    QTimer::singleShot(1000, this, &AdUpdateWorker::checkForUpdates);
}

void AdUpdateWorker::stop()
{
    m_isRunning = false;
    m_updateTimer->stop();
    emit updateProgress("后台更新服务已停止");
    qDebug() << "后台更新线程停止";
}

void AdUpdateWorker::checkForUpdates()
{
    if (!m_isRunning) return;

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit updateProgress("检查广告更新... " + currentTime);
    qDebug() << "检查广告更新:" << currentTime;

    // 触发网络管理器获取广告
    emit adsNeedUpdate();

    m_lastUpdateTime = currentTime;
}
