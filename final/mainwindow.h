#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include "adplanmodel.h"
#include "networkmanager.h"
#include "databasehandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 楼层信息更新
    void updateFloorInfo(int floor, const QString &direction);

    // 广告管理
    void onAdContentReady(const QString &adId, const QString &type,
                          const QString &content, const QString &localPath);
    void onAdsUpdated();
    void playNextAd();
    void switchToPreviousAd();
    void switchToNextAd();

    // 管理界面
    void onRefreshAdsClicked();
    void onManualUpdateClicked();
    void onAddAdClicked();
    void onRemoveAdClicked();

    // 测试功能
    void simulateElevatorMovement();

private:
    void setupUI();
    void setupDatabase();
    void setupNetwork();
    void setupWorkerThread();
    void setupAdCarousel();
    void loadCachedAds();
    void updateFloorDisplay(int floor, const QString &direction);
    void updateAdDisplay(const QVariantMap &ad);

private:
    Ui::MainWindow *ui;

    // 楼层显示
    int m_currentFloor = 1;
    QString m_currentDirection = "停止";
    QLabel *m_floorNumberLabel = nullptr;
    QLabel *m_directionLabel = nullptr;
    QLabel *m_floorArrowLabel = nullptr;
    QTimer *m_elevatorSimTimer = nullptr;

    // 广告显示
    QLabel *m_adDisplayLabel = nullptr;
    QLabel *m_textAdLabel = nullptr;
    QStackedWidget *m_adStackedWidget = nullptr;
    QTimer *m_adCarouselTimer = nullptr;
    QList<QVariantMap> m_adList;
    int m_currentAdIndex = 0;

    // 模型/视图
    AdPlanModel *m_adPlanModel = nullptr;

    // 网络
    NetworkManager *m_networkManager = nullptr;

    // 数据库
    DatabaseHandler *m_databaseHandler = nullptr;

    // 线程
    QThread *m_workerThread = nullptr;

    // 动画
    QPropertyAnimation *m_floorAnim = nullptr;
    QPropertyAnimation *m_adFadeAnim = nullptr;
};
#endif // MAINWINDOW_H
