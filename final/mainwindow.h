#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QStackedWidget>
#include <QList>
#include <QVariantMap>

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
    // 电梯控制相关
    void callElevatorToFloor(int floor);
    void moveElevatorOneStep();
    void updateFloorDisplay(int floor, const QString &direction);

    // 广告播放相关
    void updateAdDisplay(const QVariantMap &ad);
    void playNextAd();
    void switchToPreviousAd();
    void switchToNextAd();

    // 模拟电梯移动
    void simulateElevatorMovement();

private:
    void setupUI();
    void setupLocalAds();           // 改为从本地导入广告
    void setupElevatorTimer();
    void setupAdCarousel();

private:
    Ui::MainWindow *ui;

    // 电梯状态
    int m_currentFloor = 1;          // 当前楼层
    QString m_currentDirection = "停止";  // 当前方向
    int m_targetFloor = 0;          // 目标楼层
    bool m_isMoving = false;        // 是否正在移动

    // 电梯UI组件
    QLabel *m_floorNumberLabel = nullptr;   // 楼层数字显示
    QLabel *m_directionLabel = nullptr;     // 方向显示
    QLabel *m_floorArrowLabel = nullptr;    // 方向箭头
    QTimer *m_elevatorMoveTimer = nullptr;  // 电梯移动定时器
    QTimer *m_elevatorSimTimer = nullptr;   // 模拟电梯定时器

    // 广告显示
    QLabel *m_adDisplayLabel = nullptr;     // 图片广告显示标签
    QLabel *m_textAdLabel = nullptr;        // 文字广告显示标签
    QStackedWidget *m_adStackedWidget = nullptr; // 广告堆叠组件
    QTimer *m_adCarouselTimer = nullptr;    // 广告轮播定时器
    QList<QVariantMap> m_adList;            // 广告列表
    int m_currentAdIndex = 0;               // 当前广告索引
};
#endif // MAINWINDOW_H
