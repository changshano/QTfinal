#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehandler.h"
#include "networkmanager.h"
#include "adupdateworker.h"

#include <QThread>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentFloor(1)
    , m_currentDirection("停止")
    , m_currentAdIndex(0)
    , m_floorNumberLabel(nullptr)
    , m_directionLabel(nullptr)
    , m_floorArrowLabel(nullptr)
    , m_adDisplayLabel(nullptr)
    , m_textAdLabel(nullptr)
    , m_adStackedWidget(nullptr)
    , m_elevatorSimTimer(nullptr)
    , m_adCarouselTimer(nullptr)
    , m_networkManager(nullptr)
    , m_databaseHandler(nullptr)
    , m_workerThread(nullptr)
{
    ui->setupUi(this);

    // 设置窗口属性
    setWindowTitle("智能电梯广告系统");
    resize(1000, 700);

    // 调试输出
    qDebug() << "智能电梯广告系统启动...";

    setupUI();
    setupDatabase();
    setupNetwork();
    setupWorkerThread();
    setupAdCarousel();

    // 模拟电梯运行
    m_elevatorSimTimer = new QTimer(this);
    connect(m_elevatorSimTimer, &QTimer::timeout, this, &MainWindow::simulateElevatorMovement);
    m_elevatorSimTimer->start(3000); // 每3秒更新一次楼层

    // 初始显示
    updateFloorDisplay(1, "停止");
    loadCachedAds();
}

MainWindow::~MainWindow()
{
    qDebug() << "智能电梯广告系统关闭...";

    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
    }
    delete ui;
}

void MainWindow::setupUI()
{
    // 创建中央部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // ========== 左侧：电梯控制区域 ==========
    QWidget *elevatorWidget = new QWidget(centralWidget);
    QVBoxLayout *elevatorLayout = new QVBoxLayout(elevatorWidget);
    elevatorLayout->setSpacing(20);

    // 楼层显示面板
    QGroupBox *floorDisplayGroup = new QGroupBox("电梯状态", elevatorWidget);
    QVBoxLayout *floorDisplayLayout = new QVBoxLayout(floorDisplayGroup);

    // 楼层显示
    QWidget *floorDisplayWidget = new QWidget(floorDisplayGroup);
    QHBoxLayout *floorDisplayHLayout = new QHBoxLayout(floorDisplayWidget);
    floorDisplayHLayout->setAlignment(Qt::AlignCenter);

    m_floorNumberLabel = new QLabel("1", floorDisplayWidget);
    m_floorNumberLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 100px;"
        "  font-weight: bold;"
        "  color: #FF5722;"
        "  background-color: #333;"
        "  border: 5px solid #FF9800;"
        "  border-radius: 20px;"
        "  padding: 20px;"
        "  min-width: 200px;"
        "  min-height: 200px;"
        "  qproperty-alignment: 'AlignCenter';"
        "}"
        );

    m_floorArrowLabel = new QLabel("⏸", floorDisplayWidget);
    m_floorArrowLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 60px;"
        "  color: #2196F3;"
        "  padding: 20px;"
        "}"
        );

    m_directionLabel = new QLabel("停止", floorDisplayWidget);
    m_directionLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 40px;"
        "  font-weight: bold;"
        "  color: #4CAF50;"
        "  padding: 20px;"
        "}"
        );

    floorDisplayHLayout->addStretch();
    floorDisplayHLayout->addWidget(m_floorNumberLabel);
    floorDisplayHLayout->addWidget(m_floorArrowLabel);
    floorDisplayHLayout->addWidget(m_directionLabel);
    floorDisplayHLayout->addStretch();

    // 楼层按钮面板
    QGroupBox *floorButtonsGroup = new QGroupBox("选择楼层", elevatorWidget);
    QGridLayout *floorButtonsLayout = new QGridLayout(floorButtonsGroup);

    // 创建楼层按钮（8-1楼）
    for (int i = 8; i >= 1; i--) {
        int row = 8 - i;  // 从上到下排列
        int col = row % 2;
        int gridRow = row / 2;

        QPushButton *btn = new QPushButton(QString("%1楼").arg(i), floorButtonsGroup);
        btn->setFixedSize(80, 50);
        btn->setStyleSheet(
            "QPushButton {"
            "  font-size: 16px;"
            "  background-color: #607D8B;"
            "  color: white;"
            "  border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #455A64;"
            "}"
            );

        connect(btn, &QPushButton::clicked, this, [this, i]() {
            callElevatorToFloor(i);
        });

        floorButtonsLayout->addWidget(btn, gridRow, col);
    }

    floorDisplayLayout->addWidget(floorDisplayWidget);
    elevatorLayout->addWidget(floorDisplayGroup, 3);
    elevatorLayout->addWidget(floorButtonsGroup, 2);

    // ========== 右侧：广告显示区域 ==========
    QWidget *adWidget = new QWidget(centralWidget);
    QVBoxLayout *adLayout = new QVBoxLayout(adWidget);
    adLayout->setSpacing(20);

    QGroupBox *adGroup = new QGroupBox("广告播放", adWidget);
    QVBoxLayout *adGroupLayout = new QVBoxLayout(adGroup);
    adGroupLayout->setSpacing(20);

    m_adStackedWidget = new QStackedWidget(adGroup);

    // 图片广告
    m_adDisplayLabel = new QLabel(adGroup);
    m_adDisplayLabel->setAlignment(Qt::AlignCenter);
    m_adDisplayLabel->setMinimumHeight(300);
    m_adDisplayLabel->setStyleSheet(
        "QLabel {"
        "  background-color: #F5F5F5;"
        "  border: 3px solid #BDBDBD;"
        "  border-radius: 10px;"
        "}"
        );

    // 文字广告
    m_textAdLabel = new QLabel(adGroup);
    m_textAdLabel->setAlignment(Qt::AlignCenter);
    m_textAdLabel->setWordWrap(true);
    m_textAdLabel->setMinimumHeight(300);
    m_textAdLabel->setStyleSheet(
        "QLabel {"
        "  background-color: #E3F2FD;"
        "  border: 3px solid #2196F3;"
        "  border-radius: 10px;"
        "  font-size: 24px;"
        "  color: #0D47A1;"
        "  padding: 20px;"
        "}"
        );

    m_adStackedWidget->addWidget(m_adDisplayLabel);
    m_adStackedWidget->addWidget(m_textAdLabel);

    // 广告控制按钮
    QWidget *adControlWidget = new QWidget(adGroup);
    QHBoxLayout *adControlLayout = new QHBoxLayout(adControlWidget);

    QPushButton *prevBtn = new QPushButton("上一个", adControlWidget);
    QPushButton *nextBtn = new QPushButton("下一个", adControlWidget);
    QPushButton *pauseBtn = new QPushButton("暂停", adControlWidget);
    QPushButton *resumeBtn = new QPushButton("继续", adControlWidget);

    connect(prevBtn, &QPushButton::clicked, this, &MainWindow::switchToPreviousAd);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::switchToNextAd);
    connect(pauseBtn, &QPushButton::clicked, this, [this]() {
        if (m_adCarouselTimer) {
            m_adCarouselTimer->stop();
            qDebug() << "广告轮播已暂停";
        }
    });
    connect(resumeBtn, &QPushButton::clicked, this, [this]() {
        if (m_adCarouselTimer) {
            m_adCarouselTimer->start();
            qDebug() << "广告轮播已继续";
        }
    });

    adControlLayout->addStretch();
    adControlLayout->addWidget(prevBtn);
    adControlLayout->addWidget(nextBtn);
    adControlLayout->addWidget(pauseBtn);
    adControlLayout->addWidget(resumeBtn);
    adControlLayout->addStretch();

    adGroupLayout->addWidget(m_adStackedWidget, 3);
    adGroupLayout->addWidget(adControlWidget, 1);
    adLayout->addWidget(adGroup);

    // 添加到主布局
    mainLayout->addWidget(elevatorWidget, 1);
    mainLayout->addWidget(adWidget, 2);
}

void MainWindow::setupDatabase()
{
    m_databaseHandler = new DatabaseHandler(this);
    if (m_databaseHandler->initDatabase()) {
        qDebug() << "数据库初始化成功";
    } else {
        QMessageBox::warning(this, "警告", "数据库初始化失败");
    }
}

void MainWindow::setupNetwork()
{
    m_networkManager = new NetworkManager(this);

    connect(m_networkManager, &NetworkManager::adContentReady,
            this, &MainWindow::onAdContentReady);
    connect(m_networkManager, &NetworkManager::adsUpdated,
            this, &MainWindow::onAdsUpdated);
    connect(m_networkManager, &NetworkManager::errorOccurred,
            this, [this](const QString &error) {
                qWarning() << "网络错误:" << error;
            });
}

void MainWindow::setupWorkerThread()
{
    m_workerThread = new QThread(this);
    AdUpdateWorker *worker = new AdUpdateWorker();
    worker->moveToThread(m_workerThread);

    connect(m_workerThread, &QThread::started, worker, &AdUpdateWorker::start);
    connect(m_workerThread, &QThread::finished, worker, &QObject::deleteLater);

    connect(worker, &AdUpdateWorker::updateProgress,
            this, [](const QString &message) {
                qDebug() << message;
            });
    connect(worker, &AdUpdateWorker::adsNeedUpdate,
            m_networkManager, &NetworkManager::fetchAds);

    m_workerThread->start();
}

void MainWindow::setupAdCarousel()
{
    m_adCarouselTimer = new QTimer(this);
    m_adCarouselTimer->setInterval(5000); // 5秒切换广告
    connect(m_adCarouselTimer, &QTimer::timeout, this, &MainWindow::playNextAd);
    m_adCarouselTimer->start();
}

void MainWindow::loadCachedAds()
{
    m_adList = m_databaseHandler->getAllAds();
    if (!m_adList.isEmpty()) {
        m_currentAdIndex = 0;
        updateAdDisplay(m_adList.first());
        qDebug() << QString("加载了%1个广告").arg(m_adList.size()).toStdString().c_str();
    } else {
        m_adDisplayLabel->setText("<h2>暂无广告</h2><p>正在从服务器获取广告...</p>");
        qDebug() << "从服务器获取广告中...";
    }
}

void MainWindow::callElevatorToFloor(int floor)
{
    if (floor < 1 || floor > 8) {
        qDebug() << QString("无效楼层: %1").arg(floor).toStdString().c_str();
        return;
    }

    if (floor == m_currentFloor) {
        qDebug() << QString("电梯已在%1楼").arg(floor).toStdString().c_str();
        return;
    }

    // 设置目标楼层
    int targetFloor = floor;

    // 确定方向
    if (floor > m_currentFloor) {
        m_currentDirection = "上行";
    } else {
        m_currentDirection = "下行";
    }

    // 更新显示
    updateFloorDisplay(m_currentFloor, m_currentDirection);

    qDebug() << QString("前往%1楼").arg(floor).toStdString().c_str();
}

void MainWindow::simulateElevatorMovement()
{
    static bool goingUp = true;

    if (m_currentFloor >= 8) {
        goingUp = false;
        m_currentDirection = "下行";
    } else if (m_currentFloor <= 1) {
        goingUp = true;
        m_currentDirection = "上行";
    }

    if (goingUp) {
        m_currentFloor++;
    } else {
        m_currentFloor--;
    }

    updateFloorDisplay(m_currentFloor, m_currentDirection);
}

void MainWindow::updateFloorDisplay(int floor, const QString &direction)
{
    m_currentFloor = floor;
    m_currentDirection = direction;

    m_floorNumberLabel->setText(QString::number(floor));
    m_directionLabel->setText(direction);

    // 设置箭头
    if (direction == "上行") {
        m_floorArrowLabel->setText("⬆");
        m_floorArrowLabel->setStyleSheet(
            "QLabel {"
            "  font-size: 60px;"
            "  color: #4CAF50;"
            "  padding: 20px;"
            "}"
            );
    } else if (direction == "下行") {
        m_floorArrowLabel->setText("⬇");
        m_floorArrowLabel->setStyleSheet(
            "QLabel {"
            "  font-size: 60px;"
            "  color: #F44336;"
            "  padding: 20px;"
            "}"
            );
    } else {
        m_floorArrowLabel->setText("⏸");
        m_floorArrowLabel->setStyleSheet(
            "QLabel {"
            "  font-size: 60px;"
            "  color: #FF9800;"
            "  padding: 20px;"
            "}"
            );
    }
}

void MainWindow::updateAdDisplay(const QVariantMap &ad)
{
    QString type = ad["type"].toString();
    QString content = ad["content"].toString();
    QString localPath = ad["local_path"].toString();
    QString title = ad["title"].toString();

    if (type == "image") {
        if (localPath.isEmpty() || !QFile::exists(localPath)) {
            m_adDisplayLabel->setText("<h3>暂无图片广告</h3>");
        } else {
            QPixmap pixmap(localPath);
            if (!pixmap.isNull()) {
                pixmap = pixmap.scaled(m_adDisplayLabel->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
                m_adDisplayLabel->setPixmap(pixmap);
            } else {
                m_adDisplayLabel->setText("<h3>图片加载失败</h3>");
            }
        }
        m_adStackedWidget->setCurrentIndex(0);
    } else if (type == "text") {
        m_textAdLabel->setText("<h3>" + title + "</h3><p>" + content + "</p>");
        m_adStackedWidget->setCurrentIndex(1);
    }

    // 控制台输出当前播放信息
    qDebug() << QString("正在播放: %1 (%2/%3)")
                    .arg(title)
                    .arg(m_currentAdIndex + 1)
                    .arg(m_adList.size())
                    .toStdString().c_str();
}

void MainWindow::playNextAd()
{
    if (m_adList.isEmpty()) return;

    m_currentAdIndex = (m_currentAdIndex + 1) % m_adList.size();
    updateAdDisplay(m_adList.at(m_currentAdIndex));
}

void MainWindow::switchToPreviousAd()
{
    if (m_adList.isEmpty()) return;

    m_currentAdIndex = (m_currentAdIndex - 1 + m_adList.size()) % m_adList.size();
    updateAdDisplay(m_adList.at(m_currentAdIndex));
}

void MainWindow::switchToNextAd()
{
    playNextAd();
}

void MainWindow::onAdContentReady(const QString &adId, const QString &type,
                                  const QString &content, const QString &localPath)
{
    QVariantMap adData;
    adData["id"] = adId;
    adData["type"] = type;
    adData["content"] = content;
    adData["local_path"] = localPath;
    adData["last_update"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    adData["title"] = adId;  // 使用adId作为标题

    m_databaseHandler->updateAd(adData);

    loadCachedAds();
}

void MainWindow::onAdsUpdated()
{
    loadCachedAds();
    qDebug() << "广告列表已更新";
}
