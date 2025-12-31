#include <QStackedWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adupdateworker.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QStatusBar>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QPainter>
#include <QThread>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口属性
    setWindowTitle("智能电梯广告轮播与楼层信息系统");
    resize(1200, 800);

    // 设置样式
    QFile styleFile(":/resources/styles.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    setupUI();
    setupDatabase();
    setupNetwork();
    setupWorkerThread();
    setupAdCarousel();

    // 模拟电梯运行
    m_elevatorSimTimer = new QTimer(this);
    connect(m_elevatorSimTimer, &QTimer::timeout,
            this, &MainWindow::simulateElevatorMovement);
    m_elevatorSimTimer->start(3000); // 每3秒更新一次楼层

    // 初始显示
    updateFloorDisplay(1, "停止");
    loadCachedAds();
}

MainWindow::~MainWindow()
{
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
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // ========== 楼层显示区域 ==========
    QGroupBox *floorGroup = new QGroupBox("电梯状态", centralWidget);
    floorGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: bold; }");
    QVBoxLayout *floorLayout = new QVBoxLayout(floorGroup);

    // 楼层数字显示
    QWidget *floorDisplayWidget = new QWidget(floorGroup);
    QHBoxLayout *floorDisplayLayout = new QHBoxLayout(floorDisplayWidget);
    floorDisplayLayout->setAlignment(Qt::AlignCenter);

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

    m_directionLabel = new QLabel("停止", floorDisplayWidget);
    m_directionLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 40px;"
        "  font-weight: bold;"
        "  color: #4CAF50;"
        "  padding: 20px;"
        "}"
        );

    m_floorArrowLabel = new QLabel("⬆", floorDisplayWidget);
    m_floorArrowLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 60px;"
        "  color: #2196F3;"
        "  padding: 20px;"
        "}"
        );

    floorDisplayLayout->addStretch();
    floorDisplayLayout->addWidget(m_floorNumberLabel);
    floorDisplayLayout->addWidget(m_floorArrowLabel);
    floorDisplayLayout->addWidget(m_directionLabel);
    floorDisplayLayout->addStretch();

    // 楼层控制按钮
    QWidget *floorControlWidget = new QWidget(floorGroup);
    QHBoxLayout *floorControlLayout = new QHBoxLayout(floorControlWidget);

    QStringList floorBtns = {"1楼", "2楼", "3楼", "4楼", "5楼", "6楼", "7楼", "8楼"};
    for (const QString &text : floorBtns) {
        QPushButton *btn = new QPushButton(text, floorControlWidget);
        btn->setStyleSheet(
            "QPushButton {"
            "  font-size: 16px;"
            "  padding: 10px;"
            "  background-color: #607D8B;"
            "  color: white;"
            "  border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #455A64;"
            "}"
            );
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            int floor = text.left(text.length() - 1).toInt();
            updateFloorDisplay(floor, "停止");
        });
        floorControlLayout->addWidget(btn);
    }

    floorLayout->addWidget(floorDisplayWidget);
    floorLayout->addWidget(floorControlWidget);

    // ========== 广告显示区域 ==========
    QGroupBox *adGroup = new QGroupBox("广告播放", centralWidget);
    adGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: bold; }");
    QVBoxLayout *adLayout = new QVBoxLayout(adGroup);

    m_adStackedWidget = new QStackedWidget(adGroup);

    // 图片广告显示标签
    m_adDisplayLabel = new QLabel(adGroup);
    m_adDisplayLabel->setAlignment(Qt::AlignCenter);
    m_adDisplayLabel->setStyleSheet(
        "QLabel {"
        "  background-color: #F5F5F5;"
        "  border: 3px solid #BDBDBD;"
        "  border-radius: 10px;"
        "  min-height: 300px;"
        "}"
        );
    m_adDisplayLabel->setMinimumHeight(300);

    // 文字广告显示标签
    m_textAdLabel = new QLabel(adGroup);
    m_textAdLabel->setAlignment(Qt::AlignCenter);
    m_textAdLabel->setStyleSheet(
        "QLabel {"
        "  background-color: #E3F2FD;"
        "  border: 3px solid #2196F3;"
        "  border-radius: 10px;"
        "  font-size: 24px;"
        "  color: #0D47A1;"
        "  padding: 20px;"
        "  min-height: 300px;"
        "}"
        );
    m_textAdLabel->setWordWrap(true);

    m_adStackedWidget->addWidget(m_adDisplayLabel);
    m_adStackedWidget->addWidget(m_textAdLabel);

    // 广告控制按钮
    QWidget *adControlWidget = new QWidget(adGroup);
    QHBoxLayout *adControlLayout = new QHBoxLayout(adControlWidget);

    QPushButton *prevBtn = new QPushButton("上一个广告", adControlWidget);
    QPushButton *nextBtn = new QPushButton("下一个广告", adControlWidget);
    QPushButton *pauseBtn = new QPushButton("暂停轮播", adControlWidget);
    QPushButton *resumeBtn = new QPushButton("继续轮播", adControlWidget);

    for (auto btn : {prevBtn, nextBtn, pauseBtn, resumeBtn}) {
        btn->setStyleSheet(
            "QPushButton {"
            "  font-size: 14px;"
            "  padding: 8px 16px;"
            "  background-color: #4CAF50;"
            "  color: white;"
            "  border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #388E3C;"
            "}"
            );
    }

    connect(prevBtn, &QPushButton::clicked, this, &MainWindow::switchToPreviousAd);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::switchToNextAd);
    connect(pauseBtn, &QPushButton::clicked, this, [this]() {
        if (m_adCarouselTimer) m_adCarouselTimer->stop();
    });
    connect(resumeBtn, &QPushButton::clicked, this, [this]() {
        if (m_adCarouselTimer) m_adCarouselTimer->start();
    });

    adControlLayout->addStretch();
    adControlLayout->addWidget(prevBtn);
    adControlLayout->addWidget(nextBtn);
    adControlLayout->addWidget(pauseBtn);
    adControlLayout->addWidget(resumeBtn);
    adControlLayout->addStretch();

    adLayout->addWidget(m_adStackedWidget);
    adLayout->addWidget(adControlWidget);

    // ========== 广告管理区域 ==========
    QGroupBox *managementGroup = new QGroupBox("广告计划管理", centralWidget);
    managementGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: bold; }");
    QVBoxLayout *managementLayout = new QVBoxLayout(managementGroup);

    // 管理按钮
    QWidget *btnWidget = new QWidget(managementGroup);
    QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);

    QPushButton *refreshBtn = new QPushButton("刷新列表", btnWidget);
    QPushButton *manualUpdateBtn = new QPushButton("手动更新广告", btnWidget);
    QPushButton *addBtn = new QPushButton("添加广告", btnWidget);
    QPushButton *removeBtn = new QPushButton("删除广告", btnWidget);

    for (auto btn : {refreshBtn, manualUpdateBtn, addBtn, removeBtn}) {
        btn->setStyleSheet(
            "QPushButton {"
            "  font-size: 14px;"
            "  padding: 8px 16px;"
            "  background-color: #2196F3;"
            "  color: white;"
            "  border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #1976D2;"
            "}"
            );
    }

    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::onRefreshAdsClicked);
    connect(manualUpdateBtn, &QPushButton::clicked, this, &MainWindow::onManualUpdateClicked);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddAdClicked);
    connect(removeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveAdClicked);

    btnLayout->addStretch();
    btnLayout->addWidget(refreshBtn);
    btnLayout->addWidget(manualUpdateBtn);
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(removeBtn);
    btnLayout->addStretch();

    // 广告计划表格
    QTableView *adTableView = new QTableView(managementGroup);
    m_adPlanModel = new AdPlanModel(this);
    adTableView->setModel(m_adPlanModel);

    // 设置表头
    adTableView->horizontalHeader()->setStretchLastSection(true);
    adTableView->setAlternatingRowColors(true);
    adTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    adTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    managementLayout->addWidget(btnWidget);
    managementLayout->addWidget(adTableView);

    // ========== 状态栏 ==========
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->showMessage("系统就绪 | 最后更新: " +
                           QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    // 添加到主布局
    mainLayout->addWidget(floorGroup, 2);
    mainLayout->addWidget(adGroup, 3);
    mainLayout->addWidget(managementGroup, 3);

    // 创建动画
    m_floorAnim = new QPropertyAnimation(m_floorNumberLabel, "geometry", this);
    m_adFadeAnim = new QPropertyAnimation(m_adDisplayLabel, "windowOpacity", this);
    m_adFadeAnim->setDuration(1000);
    m_adFadeAnim->setStartValue(0.0);
    m_adFadeAnim->setEndValue(1.0);
}

void MainWindow::setupDatabase()
{
    m_databaseHandler = new DatabaseHandler(this);
    if (m_databaseHandler->initDatabase()) {
        statusBar()->showMessage("数据库初始化成功", 3000);
    } else {
        QMessageBox::critical(this, "错误", "数据库初始化失败");
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
                statusBar()->showMessage("网络错误: " + error, 5000);
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
            this, [this](const QString &message) {
                statusBar()->showMessage(message, 2000);
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
    } else {
        m_adDisplayLabel->setText("<h2>暂无广告</h2><p>等待从服务器获取广告内容...</p>");
    }
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

    // 添加动画效果
    m_floorAnim->setDuration(500);
    m_floorAnim->setStartValue(m_floorNumberLabel->geometry());
    m_floorAnim->setKeyValueAt(0.5, m_floorNumberLabel->geometry().adjusted(0, -10, 0, -10));
    m_floorAnim->setEndValue(m_floorNumberLabel->geometry());
    m_floorAnim->start();
}

void MainWindow::updateAdDisplay(const QVariantMap &ad)
{
    QString type = ad["type"].toString();
    QString content = ad["content"].toString();
    QString localPath = ad["local_path"].toString();

    if (type == "image") {
        QPixmap pixmap(localPath);
        if (!pixmap.isNull()) {
            pixmap = pixmap.scaled(m_adDisplayLabel->size(),
                                   Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);
            m_adDisplayLabel->setPixmap(pixmap);
            m_adStackedWidget->setCurrentIndex(0);

            // 淡入动画
            m_adFadeAnim->start();
        } else {
            m_adDisplayLabel->setText("<h3>图片加载失败</h3>");
        }
    } else if (type == "text") {
        m_textAdLabel->setText("<h2>" + ad["title"].toString() + "</h2>" +
                               "<p>" + content + "</p>");
        m_adStackedWidget->setCurrentIndex(1);
    }

    // 更新状态栏
    statusBar()->showMessage("正在播放: " + ad["title"].toString() +
                                 " (" + QString::number(m_currentAdIndex + 1) +
                                 "/" + QString::number(m_adList.size()) + ")", 3000);
}

void MainWindow::updateFloorInfo(int floor, const QString &direction)
{
    updateFloorDisplay(floor, direction);
}

void MainWindow::onAdContentReady(const QString &adId, const QString &type,
                                  const QString &content, const QString &localPath)
{
    // 更新数据库
    QVariantMap adData;
    adData["id"] = adId;
    adData["type"] = type;
    adData["content"] = content;
    adData["local_path"] = localPath;
    adData["last_update"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    m_databaseHandler->updateAd(adData);

    // 重新加载广告列表
    loadCachedAds();

    // 更新Model
    if (m_adPlanModel) {
        m_adPlanModel->refresh();
    }
}

void MainWindow::onAdsUpdated()
{
    loadCachedAds();
    if (m_adPlanModel) {
        m_adPlanModel->refresh();
    }
    statusBar()->showMessage("广告列表已更新", 3000);
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

void MainWindow::onRefreshAdsClicked()
{
    loadCachedAds();
    if (m_adPlanModel) {
        m_adPlanModel->refresh();
    }
    statusBar()->showMessage("广告列表已刷新", 2000);
}

void MainWindow::onManualUpdateClicked()
{
    m_networkManager->fetchAds();
    statusBar()->showMessage("正在从服务器更新广告...", 2000);
}

void MainWindow::onAddAdClicked()
{
    // 模拟添加广告
    QVariantMap newAd;
    newAd["id"] = "ad_" + QString::number(QDateTime::currentMSecsSinceEpoch());
    newAd["title"] = "新增广告 " + QDateTime::currentDateTime().toString("hh:mm:ss");
    newAd["type"] = "text";
    newAd["content"] = "这是手动添加的测试广告内容";
    newAd["duration"] = 5;
    newAd["priority"] = 1;
    newAd["local_path"] = "";
    newAd["last_update"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    m_databaseHandler->addAd(newAd);
    loadCachedAds();

    if (m_adPlanModel) {
        m_adPlanModel->refresh();
    }

    statusBar()->showMessage("广告已添加", 2000);
}

void MainWindow::onRemoveAdClicked()
{
    if (m_adList.isEmpty()) return;

    QString adId = m_adList.at(m_currentAdIndex)["id"].toString();
    m_databaseHandler->removeAd(adId);

    loadCachedAds();
    if (m_adPlanModel) {
        m_adPlanModel->refresh();
    }

    statusBar()->showMessage("广告已删除", 2000);
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
