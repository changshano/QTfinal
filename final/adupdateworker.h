#ifndef ADUPDATEWORKER_H
#define ADUPDATEWORKER_H

#include <QObject>
#include <QTimer>

class AdUpdateWorker : public QObject
{
    Q_OBJECT
public:
    explicit AdUpdateWorker(QObject *parent = nullptr);

public slots:
    void start();

signals:
    void updateProgress(const QString &message);
    void adsNeedUpdate();

private slots:
    void checkForUpdates();

private:
    QTimer *m_updateTimer;
};
#endif // ADUPDATEWORKER_H
