#include <QStackedWidget>
#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置应用程序信息
    QApplication::setApplicationName("智能电梯广告轮播与楼层信息系统");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("QtCompany");

    // 设置样式
    QFile styleFile(":/resources/styles.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        // 默认样式
        a.setStyleSheet(R"(
            QMainWindow {
                background-color: #f0f0f0;
            }
            QGroupBox {
                font-weight: bold;
                border: 2px solid #cccccc;
                border-radius: 5px;
                margin-top: 10px;
                padding-top: 10px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px 0 5px;
            }
            QTableView {
                background-color: white;
                alternate-background-color: #f8f8f8;
                selection-background-color: #e0e0e0;
                gridline-color: #d0d0d0;
            }
            QTableView::item {
                padding: 5px;
            }
            QHeaderView::section {
                background-color: #607d8b;
                color: white;
                padding: 5px;
                border: 1px solid #455a64;
            }
        )");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
