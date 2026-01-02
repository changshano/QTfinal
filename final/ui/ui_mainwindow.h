/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *elevatorWidget;
    QVBoxLayout *verticalLayout_elevator;
    QGroupBox *groupBox_elevator;
    QVBoxLayout *verticalLayout_status;
    QWidget *floorDisplayWidget;
    QHBoxLayout *horizontalLayout_floor;
    QSpacerItem *horizontalSpacer_left;
    QLabel *label_floor_number;
    QLabel *label_floor_arrow;
    QLabel *label_direction;
    QSpacerItem *horizontalSpacer_right;
    QGroupBox *groupBox_buttons;
    QGridLayout *gridLayout_buttons;
    QPushButton *btn_floor_8;
    QPushButton *btn_floor_7;
    QPushButton *btn_floor_6;
    QPushButton *btn_floor_5;
    QPushButton *btn_floor_4;
    QPushButton *btn_floor_3;
    QPushButton *btn_floor_2;
    QPushButton *btn_floor_1;
    QWidget *adWidget;
    QVBoxLayout *verticalLayout_ad;
    QGroupBox *groupBox_ad;
    QVBoxLayout *verticalLayout_ad_content;
    QStackedWidget *stackedWidget_ad;
    QWidget *page_image;
    QVBoxLayout *verticalLayout_image;
    QLabel *label_ad_image;
    QWidget *page_text;
    QVBoxLayout *verticalLayout_text;
    QLabel *label_ad_text;
    QWidget *widget_ad_controls;
    QHBoxLayout *horizontalLayout_ad_controls;
    QSpacerItem *horizontalSpacer_ad_left;
    QPushButton *btn_ad_prev;
    QPushButton *btn_ad_next;
    QPushButton *btn_ad_pause;
    QPushButton *btn_ad_resume;
    QSpacerItem *horizontalSpacer_ad_right;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(20, 20, 20, 20);
        elevatorWidget = new QWidget(centralwidget);
        elevatorWidget->setObjectName("elevatorWidget");
        verticalLayout_elevator = new QVBoxLayout(elevatorWidget);
        verticalLayout_elevator->setSpacing(20);
        verticalLayout_elevator->setObjectName("verticalLayout_elevator");
        groupBox_elevator = new QGroupBox(elevatorWidget);
        groupBox_elevator->setObjectName("groupBox_elevator");
        verticalLayout_status = new QVBoxLayout(groupBox_elevator);
        verticalLayout_status->setSpacing(20);
        verticalLayout_status->setObjectName("verticalLayout_status");
        floorDisplayWidget = new QWidget(groupBox_elevator);
        floorDisplayWidget->setObjectName("floorDisplayWidget");
        horizontalLayout_floor = new QHBoxLayout(floorDisplayWidget);
        horizontalLayout_floor->setSpacing(10);
        horizontalLayout_floor->setObjectName("horizontalLayout_floor");
        horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_floor->addItem(horizontalSpacer_left);

        label_floor_number = new QLabel(floorDisplayWidget);
        label_floor_number->setObjectName("label_floor_number");
        label_floor_number->setMinimumSize(QSize(200, 200));
        label_floor_number->setAlignment(Qt::AlignCenter);

        horizontalLayout_floor->addWidget(label_floor_number);

        label_floor_arrow = new QLabel(floorDisplayWidget);
        label_floor_arrow->setObjectName("label_floor_arrow");
        label_floor_arrow->setMinimumSize(QSize(60, 60));
        label_floor_arrow->setAlignment(Qt::AlignCenter);

        horizontalLayout_floor->addWidget(label_floor_arrow);

        label_direction = new QLabel(floorDisplayWidget);
        label_direction->setObjectName("label_direction");
        label_direction->setMinimumSize(QSize(100, 60));
        label_direction->setAlignment(Qt::AlignCenter);

        horizontalLayout_floor->addWidget(label_direction);

        horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_floor->addItem(horizontalSpacer_right);


        verticalLayout_status->addWidget(floorDisplayWidget);


        verticalLayout_elevator->addWidget(groupBox_elevator);

        groupBox_buttons = new QGroupBox(elevatorWidget);
        groupBox_buttons->setObjectName("groupBox_buttons");
        gridLayout_buttons = new QGridLayout(groupBox_buttons);
        gridLayout_buttons->setSpacing(10);
        gridLayout_buttons->setObjectName("gridLayout_buttons");
        btn_floor_8 = new QPushButton(groupBox_buttons);
        btn_floor_8->setObjectName("btn_floor_8");
        btn_floor_8->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_8, 0, 0, 1, 1);

        btn_floor_7 = new QPushButton(groupBox_buttons);
        btn_floor_7->setObjectName("btn_floor_7");
        btn_floor_7->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_7, 0, 1, 1, 1);

        btn_floor_6 = new QPushButton(groupBox_buttons);
        btn_floor_6->setObjectName("btn_floor_6");
        btn_floor_6->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_6, 1, 0, 1, 1);

        btn_floor_5 = new QPushButton(groupBox_buttons);
        btn_floor_5->setObjectName("btn_floor_5");
        btn_floor_5->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_5, 1, 1, 1, 1);

        btn_floor_4 = new QPushButton(groupBox_buttons);
        btn_floor_4->setObjectName("btn_floor_4");
        btn_floor_4->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_4, 2, 0, 1, 1);

        btn_floor_3 = new QPushButton(groupBox_buttons);
        btn_floor_3->setObjectName("btn_floor_3");
        btn_floor_3->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_3, 2, 1, 1, 1);

        btn_floor_2 = new QPushButton(groupBox_buttons);
        btn_floor_2->setObjectName("btn_floor_2");
        btn_floor_2->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_2, 3, 0, 1, 1);

        btn_floor_1 = new QPushButton(groupBox_buttons);
        btn_floor_1->setObjectName("btn_floor_1");
        btn_floor_1->setMinimumSize(QSize(80, 50));

        gridLayout_buttons->addWidget(btn_floor_1, 3, 1, 1, 1);


        verticalLayout_elevator->addWidget(groupBox_buttons);


        horizontalLayout->addWidget(elevatorWidget);

        adWidget = new QWidget(centralwidget);
        adWidget->setObjectName("adWidget");
        verticalLayout_ad = new QVBoxLayout(adWidget);
        verticalLayout_ad->setSpacing(20);
        verticalLayout_ad->setObjectName("verticalLayout_ad");
        groupBox_ad = new QGroupBox(adWidget);
        groupBox_ad->setObjectName("groupBox_ad");
        verticalLayout_ad_content = new QVBoxLayout(groupBox_ad);
        verticalLayout_ad_content->setSpacing(20);
        verticalLayout_ad_content->setObjectName("verticalLayout_ad_content");
        stackedWidget_ad = new QStackedWidget(groupBox_ad);
        stackedWidget_ad->setObjectName("stackedWidget_ad");
        page_image = new QWidget();
        page_image->setObjectName("page_image");
        verticalLayout_image = new QVBoxLayout(page_image);
        verticalLayout_image->setSpacing(0);
        verticalLayout_image->setObjectName("verticalLayout_image");
        verticalLayout_image->setContentsMargins(0, 0, 0, 0);
        label_ad_image = new QLabel(page_image);
        label_ad_image->setObjectName("label_ad_image");
        label_ad_image->setMinimumSize(QSize(0, 300));
        label_ad_image->setAlignment(Qt::AlignCenter);

        verticalLayout_image->addWidget(label_ad_image);

        stackedWidget_ad->addWidget(page_image);
        page_text = new QWidget();
        page_text->setObjectName("page_text");
        verticalLayout_text = new QVBoxLayout(page_text);
        verticalLayout_text->setSpacing(0);
        verticalLayout_text->setObjectName("verticalLayout_text");
        verticalLayout_text->setContentsMargins(0, 0, 0, 0);
        label_ad_text = new QLabel(page_text);
        label_ad_text->setObjectName("label_ad_text");
        label_ad_text->setMinimumSize(QSize(0, 300));
        label_ad_text->setAlignment(Qt::AlignCenter);
        label_ad_text->setWordWrap(true);

        verticalLayout_text->addWidget(label_ad_text);

        stackedWidget_ad->addWidget(page_text);

        verticalLayout_ad_content->addWidget(stackedWidget_ad);

        widget_ad_controls = new QWidget(groupBox_ad);
        widget_ad_controls->setObjectName("widget_ad_controls");
        horizontalLayout_ad_controls = new QHBoxLayout(widget_ad_controls);
        horizontalLayout_ad_controls->setSpacing(10);
        horizontalLayout_ad_controls->setObjectName("horizontalLayout_ad_controls");
        horizontalSpacer_ad_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ad_controls->addItem(horizontalSpacer_ad_left);

        btn_ad_prev = new QPushButton(widget_ad_controls);
        btn_ad_prev->setObjectName("btn_ad_prev");
        btn_ad_prev->setMinimumSize(QSize(80, 35));

        horizontalLayout_ad_controls->addWidget(btn_ad_prev);

        btn_ad_next = new QPushButton(widget_ad_controls);
        btn_ad_next->setObjectName("btn_ad_next");
        btn_ad_next->setMinimumSize(QSize(80, 35));

        horizontalLayout_ad_controls->addWidget(btn_ad_next);

        btn_ad_pause = new QPushButton(widget_ad_controls);
        btn_ad_pause->setObjectName("btn_ad_pause");
        btn_ad_pause->setMinimumSize(QSize(80, 35));

        horizontalLayout_ad_controls->addWidget(btn_ad_pause);

        btn_ad_resume = new QPushButton(widget_ad_controls);
        btn_ad_resume->setObjectName("btn_ad_resume");
        btn_ad_resume->setMinimumSize(QSize(80, 35));

        horizontalLayout_ad_controls->addWidget(btn_ad_resume);

        horizontalSpacer_ad_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ad_controls->addItem(horizontalSpacer_ad_right);


        verticalLayout_ad_content->addWidget(widget_ad_controls);


        verticalLayout_ad->addWidget(groupBox_ad);


        horizontalLayout->addWidget(adWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget_ad->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\347\224\265\346\242\257\345\271\277\345\221\212\347\263\273\347\273\237", nullptr));
        groupBox_elevator->setTitle(QCoreApplication::translate("MainWindow", "\347\224\265\346\242\257\347\212\266\346\200\201", nullptr));
        label_floor_number->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_floor_arrow->setText(QCoreApplication::translate("MainWindow", "\342\217\270", nullptr));
        label_direction->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        groupBox_buttons->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\245\274\345\261\202", nullptr));
        btn_floor_8->setText(QCoreApplication::translate("MainWindow", "8\346\245\274", nullptr));
        btn_floor_7->setText(QCoreApplication::translate("MainWindow", "7\346\245\274", nullptr));
        btn_floor_6->setText(QCoreApplication::translate("MainWindow", "6\346\245\274", nullptr));
        btn_floor_5->setText(QCoreApplication::translate("MainWindow", "5\346\245\274", nullptr));
        btn_floor_4->setText(QCoreApplication::translate("MainWindow", "4\346\245\274", nullptr));
        btn_floor_3->setText(QCoreApplication::translate("MainWindow", "3\346\245\274", nullptr));
        btn_floor_2->setText(QCoreApplication::translate("MainWindow", "2\346\245\274", nullptr));
        btn_floor_1->setText(QCoreApplication::translate("MainWindow", "1\346\245\274", nullptr));
        groupBox_ad->setTitle(QCoreApplication::translate("MainWindow", "\345\271\277\345\221\212\346\222\255\346\224\276", nullptr));
        label_ad_image->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\345\212\240\350\275\275\345\271\277\345\221\212...", nullptr));
        label_ad_text->setText(QCoreApplication::translate("MainWindow", "\346\232\202\346\227\240\346\226\207\345\255\227\345\271\277\345\221\212", nullptr));
        btn_ad_prev->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\344\270\252", nullptr));
        btn_ad_next->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252", nullptr));
        btn_ad_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        btn_ad_resume->setText(QCoreApplication::translate("MainWindow", "\347\273\247\347\273\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
