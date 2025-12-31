#include <QstatusBar>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口属性
    setWindowTitle("智能电梯广告系统");
    resize(1000, 700);

    // 设置样式
    QFile styleFile(":/resources/styles.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    setupUI();
    setupLocalAds();       // 从本地导入广告
    setupElevatorTimer();
    setupAdCarousel();

    // 初始显示
    updateFloorDisplay(1, "停止");

    // 显示第一个广告
    if (!m_adList.isEmpty()) {
        updateAdDisplay(m_adList.first());
    }

    // 状态栏
    ui->statusbar->showMessage("系统就绪 - 电梯停止在1楼");
}

MainWindow::~MainWindow()
{
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
    floorDisplayGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: bold; }");
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
    floorButtonsGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: bold; }");
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
    adGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: bold; }");
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

    // 设置按钮样式
    QString btnStyle =
        "QPushButton {"
        "  font-size: 14px;"
        "  padding: 8px 16px;"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border-radius: 5px;"
        "  min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #388E3C;"
        "}";

    prevBtn->setStyleSheet(btnStyle);
    nextBtn->setStyleSheet(btnStyle);
    pauseBtn->setStyleSheet(btnStyle);
    resumeBtn->setStyleSheet(btnStyle);

    connect(prevBtn, &QPushButton::clicked, this, &MainWindow::switchToPreviousAd);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::switchToNextAd);
    connect(pauseBtn, &QPushButton::clicked, this, [this]() {
        if (m_adCarouselTimer) {
            m_adCarouselTimer->stop();
            ui->statusbar->showMessage("广告轮播已暂停", 2000);
        }
    });
    connect(resumeBtn, &QPushButton::clicked, this, [this]() {
        if (m_adCarouselTimer) {
            m_adCarouselTimer->start();
            ui->statusbar->showMessage("广告轮播已继续", 2000);
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

void MainWindow::setupLocalAds()
{
    // 清除现有广告列表
    m_adList.clear();

    // 创建项目目录结构
    QDir dir;
    QString adsDir = "ads";
    if (!dir.exists(adsDir)) {
        dir.mkdir(adsDir);
    }

    // 检查ads目录下是否有真实的图片文件
    QString imagePath = "ads/";
    QStringList imageNames = {"ad1.jpg", "ad2.jpg"/*, "ad3.jpg", "ad4.jpg", "ad5.jpg"*/};

    for (int i = 0; i < imageNames.size(); i++) {
        QString fullPath = imagePath + imageNames[i];
        if (QFile::exists(fullPath)) {
            QVariantMap imageAd;
            imageAd["id"] = QString("img_ad_%1").arg(i+1);
            imageAd["title"] = QString("广告图片 %1").arg(i+1);
            imageAd["type"] = "image";
            imageAd["content"] = QString("这是第%1个图片广告").arg(i+1);
            imageAd["local_path"] = fullPath;
            imageAd["duration"] = 5;
            m_adList.append(imageAd);
        }
    }

    // 如果没有任何广告，添加一个默认的
    if (m_adList.isEmpty()) {
        QVariantMap defaultAd;
        defaultAd["id"] = "default_ad";
        defaultAd["title"] = "默认广告";
        defaultAd["type"] = "text";
        defaultAd["content"] = "欢迎使用智能电梯广告系统！";
        defaultAd["local_path"] = "";
        defaultAd["duration"] = 5;
        m_adList.append(defaultAd);
    }

    qDebug() << "Loaded" << m_adList.size() << "ads from local";
}

void MainWindow::setupElevatorTimer()
{
    // 模拟电梯自动运行的定时器
    m_elevatorSimTimer = new QTimer(this);
    m_elevatorSimTimer->setInterval(3000);
    connect(m_elevatorSimTimer, &QTimer::timeout, this, &MainWindow::simulateElevatorMovement);
    m_elevatorSimTimer->start();
}

void MainWindow::setupAdCarousel()
{
    m_adCarouselTimer = new QTimer(this);
    m_adCarouselTimer->setInterval(5000); // 5秒切换广告
    connect(m_adCarouselTimer, &QTimer::timeout, this, &MainWindow::playNextAd);
    m_adCarouselTimer->start();
}

void MainWindow::callElevatorToFloor(int floor)
{
    if (floor < 1 || floor > 8) {
        ui->statusbar->showMessage("无效楼层：" + QString::number(floor), 2000);
        return;
    }
    if (floor == m_currentFloor) {
        ui->statusbar->showMessage("电梯已在" + QString::number(floor) + "楼", 2000);
        return;
    }
    // 设置目标楼层
    m_targetFloor = floor;
    // 确定方向
    if (floor > m_currentFloor) {
        m_currentDirection = "上行";
    } else {
        m_currentDirection = "下行";
    }
    // 更新显示
    updateFloorDisplay(m_currentFloor, m_currentDirection);
    ui->statusbar->showMessage(
        QString("前往%1楼").arg(floor),
        2000
        );
}

void MainWindow::simulateElevatorMovement()
{
    static bool goingUp = true;

    if (m_targetFloor > 0) {
        // 有目标楼层，向目标楼层移动
        if (m_currentFloor < m_targetFloor) {
            m_currentFloor++;
            m_currentDirection = "上行";
        } else if (m_currentFloor > m_targetFloor) {
            m_currentFloor--;
            m_currentDirection = "下行";
        } else {
            // 到达目标楼层
            m_currentDirection = "停止";
            m_targetFloor = 0;
            ui->statusbar->showMessage("叮！已到达" + QString::number(m_currentFloor) + "楼", 3000);
        }
    } else {
        // 没有目标楼层，模拟随机运行
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
            // 如果没有图片，显示占位符
            m_adDisplayLabel->setText(
                QString("<h2>%1</h2><p>%2</p>").arg(title).arg(content)
                );
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
        m_textAdLabel->setText("<h2>" + title + "</h2><p>" + content + "</p>");
        m_adStackedWidget->setCurrentIndex(1);
    }

    // 显示当前播放信息
    ui->statusbar->showMessage(
        QString("正在播放: %1 (%2/%3)")
            .arg(title)
            .arg(m_currentAdIndex + 1)
            .arg(m_adList.size()),
        3000
    );
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
