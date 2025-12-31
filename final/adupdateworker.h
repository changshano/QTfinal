#ifndef ADUPDATEWORKER_H
#define ADUPDATEWORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

class AdUpdateWorker : public QObject
{
    Q_OBJECT
public:
    explicit AdUpdateWorker(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

signals:
    void updateProgress(const QString &message);
    void adsNeedUpdate();

private slots:
    void checkForUpdates();

private:
    QTimer *m_updateTimer;
    QString m_lastUpdateTime;
    bool m_isRunning = false;
};
#endif // ADUPDATEWORKER_H
