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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionSettings;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_floor;
    QVBoxLayout *verticalLayout_floor;
    QWidget *widget_floor_display;
    QHBoxLayout *horizontalLayout_floor;
    QSpacerItem *horizontalSpacer_floor_left;
    QLabel *label_floor_number;
    QLabel *label_floor_arrow;
    QLabel *label_floor_direction;
    QSpacerItem *horizontalSpacer_floor_right;
    QWidget *widget_floor_buttons;
    QHBoxLayout *horizontalLayout_floor_buttons;
    QPushButton *btn_floor_1;
    QPushButton *btn_floor_2;
    QPushButton *btn_floor_3;
    QPushButton *btn_floor_4;
    QPushButton *btn_floor_5;
    QPushButton *btn_floor_6;
    QPushButton *btn_floor_7;
    QPushButton *btn_floor_8;
    QGroupBox *groupBox_ad;
    QVBoxLayout *verticalLayout_ad;
    QStackedWidget *stackedWidget_ad;
    QWidget *page_image;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_ad_image;
    QWidget *page_text;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_ad_text;
    QWidget *widget_ad_control;
    QHBoxLayout *horizontalLayout_ad_control;
    QSpacerItem *horizontalSpacer_ad_left;
    QPushButton *btn_ad_prev;
    QPushButton *btn_ad_next;
    QPushButton *btn_ad_pause;
    QPushButton *btn_ad_resume;
    QSpacerItem *horizontalSpacer_ad_right;
    QGroupBox *groupBox_manage;
    QVBoxLayout *verticalLayout_manage;
    QWidget *widget_manage_buttons;
    QHBoxLayout *horizontalLayout_manage_buttons;
    QSpacerItem *horizontalSpacer_manage_left;
    QPushButton *btn_refresh;
    QPushButton *btn_update;
    QPushButton *btn_add;
    QPushButton *btn_remove;
    QSpacerItem *horizontalSpacer_manage_right;
    QTableView *tableView_ads;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 1091);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName("actionSettings");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(20, 20, 20, 20);
        groupBox_floor = new QGroupBox(centralwidget);
        groupBox_floor->setObjectName("groupBox_floor");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        groupBox_floor->setFont(font);
        verticalLayout_floor = new QVBoxLayout(groupBox_floor);
        verticalLayout_floor->setSpacing(20);
        verticalLayout_floor->setObjectName("verticalLayout_floor");
        widget_floor_display = new QWidget(groupBox_floor);
        widget_floor_display->setObjectName("widget_floor_display");
        horizontalLayout_floor = new QHBoxLayout(widget_floor_display);
        horizontalLayout_floor->setObjectName("horizontalLayout_floor");
        horizontalSpacer_floor_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_floor->addItem(horizontalSpacer_floor_left);

        label_floor_number = new QLabel(widget_floor_display);
        label_floor_number->setObjectName("label_floor_number");
        label_floor_number->setMinimumSize(QSize(200, 200));
        label_floor_number->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_floor->addWidget(label_floor_number);

        label_floor_arrow = new QLabel(widget_floor_display);
        label_floor_arrow->setObjectName("label_floor_arrow");
        label_floor_arrow->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_floor->addWidget(label_floor_arrow);

        label_floor_direction = new QLabel(widget_floor_display);
        label_floor_direction->setObjectName("label_floor_direction");
        label_floor_direction->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_floor->addWidget(label_floor_direction);

        horizontalSpacer_floor_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_floor->addItem(horizontalSpacer_floor_right);


        verticalLayout_floor->addWidget(widget_floor_display);

        widget_floor_buttons = new QWidget(groupBox_floor);
        widget_floor_buttons->setObjectName("widget_floor_buttons");
        horizontalLayout_floor_buttons = new QHBoxLayout(widget_floor_buttons);
        horizontalLayout_floor_buttons->setObjectName("horizontalLayout_floor_buttons");
        btn_floor_1 = new QPushButton(widget_floor_buttons);
        btn_floor_1->setObjectName("btn_floor_1");

        horizontalLayout_floor_buttons->addWidget(btn_floor_1);

        btn_floor_2 = new QPushButton(widget_floor_buttons);
        btn_floor_2->setObjectName("btn_floor_2");

        horizontalLayout_floor_buttons->addWidget(btn_floor_2);

        btn_floor_3 = new QPushButton(widget_floor_buttons);
        btn_floor_3->setObjectName("btn_floor_3");

        horizontalLayout_floor_buttons->addWidget(btn_floor_3);

        btn_floor_4 = new QPushButton(widget_floor_buttons);
        btn_floor_4->setObjectName("btn_floor_4");

        horizontalLayout_floor_buttons->addWidget(btn_floor_4);

        btn_floor_5 = new QPushButton(widget_floor_buttons);
        btn_floor_5->setObjectName("btn_floor_5");

        horizontalLayout_floor_buttons->addWidget(btn_floor_5);

        btn_floor_6 = new QPushButton(widget_floor_buttons);
        btn_floor_6->setObjectName("btn_floor_6");

        horizontalLayout_floor_buttons->addWidget(btn_floor_6);

        btn_floor_7 = new QPushButton(widget_floor_buttons);
        btn_floor_7->setObjectName("btn_floor_7");

        horizontalLayout_floor_buttons->addWidget(btn_floor_7);

        btn_floor_8 = new QPushButton(widget_floor_buttons);
        btn_floor_8->setObjectName("btn_floor_8");

        horizontalLayout_floor_buttons->addWidget(btn_floor_8);


        verticalLayout_floor->addWidget(widget_floor_buttons);


        verticalLayout_3->addWidget(groupBox_floor);

        groupBox_ad = new QGroupBox(centralwidget);
        groupBox_ad->setObjectName("groupBox_ad");
        groupBox_ad->setFont(font);
        verticalLayout_ad = new QVBoxLayout(groupBox_ad);
        verticalLayout_ad->setSpacing(20);
        verticalLayout_ad->setObjectName("verticalLayout_ad");
        stackedWidget_ad = new QStackedWidget(groupBox_ad);
        stackedWidget_ad->setObjectName("stackedWidget_ad");
        page_image = new QWidget();
        page_image->setObjectName("page_image");
        page_image->setMinimumSize(QSize(0, 300));
        verticalLayout_4 = new QVBoxLayout(page_image);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_ad_image = new QLabel(page_image);
        label_ad_image->setObjectName("label_ad_image");
        label_ad_image->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_ad_image);

        stackedWidget_ad->addWidget(page_image);
        page_text = new QWidget();
        page_text->setObjectName("page_text");
        verticalLayout_5 = new QVBoxLayout(page_text);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_ad_text = new QLabel(page_text);
        label_ad_text->setObjectName("label_ad_text");
        label_ad_text->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_ad_text->setWordWrap(true);

        verticalLayout_5->addWidget(label_ad_text);

        stackedWidget_ad->addWidget(page_text);

        verticalLayout_ad->addWidget(stackedWidget_ad);

        widget_ad_control = new QWidget(groupBox_ad);
        widget_ad_control->setObjectName("widget_ad_control");
        horizontalLayout_ad_control = new QHBoxLayout(widget_ad_control);
        horizontalLayout_ad_control->setObjectName("horizontalLayout_ad_control");
        horizontalSpacer_ad_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ad_control->addItem(horizontalSpacer_ad_left);

        btn_ad_prev = new QPushButton(widget_ad_control);
        btn_ad_prev->setObjectName("btn_ad_prev");

        horizontalLayout_ad_control->addWidget(btn_ad_prev);

        btn_ad_next = new QPushButton(widget_ad_control);
        btn_ad_next->setObjectName("btn_ad_next");

        horizontalLayout_ad_control->addWidget(btn_ad_next);

        btn_ad_pause = new QPushButton(widget_ad_control);
        btn_ad_pause->setObjectName("btn_ad_pause");

        horizontalLayout_ad_control->addWidget(btn_ad_pause);

        btn_ad_resume = new QPushButton(widget_ad_control);
        btn_ad_resume->setObjectName("btn_ad_resume");

        horizontalLayout_ad_control->addWidget(btn_ad_resume);

        horizontalSpacer_ad_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ad_control->addItem(horizontalSpacer_ad_right);


        verticalLayout_ad->addWidget(widget_ad_control);


        verticalLayout_3->addWidget(groupBox_ad);

        groupBox_manage = new QGroupBox(centralwidget);
        groupBox_manage->setObjectName("groupBox_manage");
        groupBox_manage->setFont(font);
        verticalLayout_manage = new QVBoxLayout(groupBox_manage);
        verticalLayout_manage->setSpacing(10);
        verticalLayout_manage->setObjectName("verticalLayout_manage");
        widget_manage_buttons = new QWidget(groupBox_manage);
        widget_manage_buttons->setObjectName("widget_manage_buttons");
        horizontalLayout_manage_buttons = new QHBoxLayout(widget_manage_buttons);
        horizontalLayout_manage_buttons->setObjectName("horizontalLayout_manage_buttons");
        horizontalSpacer_manage_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_manage_buttons->addItem(horizontalSpacer_manage_left);

        btn_refresh = new QPushButton(widget_manage_buttons);
        btn_refresh->setObjectName("btn_refresh");

        horizontalLayout_manage_buttons->addWidget(btn_refresh);

        btn_update = new QPushButton(widget_manage_buttons);
        btn_update->setObjectName("btn_update");

        horizontalLayout_manage_buttons->addWidget(btn_update);

        btn_add = new QPushButton(widget_manage_buttons);
        btn_add->setObjectName("btn_add");

        horizontalLayout_manage_buttons->addWidget(btn_add);

        btn_remove = new QPushButton(widget_manage_buttons);
        btn_remove->setObjectName("btn_remove");

        horizontalLayout_manage_buttons->addWidget(btn_remove);

        horizontalSpacer_manage_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_manage_buttons->addItem(horizontalSpacer_manage_right);


        verticalLayout_manage->addWidget(widget_manage_buttons);

        tableView_ads = new QTableView(groupBox_manage);
        tableView_ads->setObjectName("tableView_ads");
        tableView_ads->setAlternatingRowColors(true);
        tableView_ads->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableView_ads->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableView_ads->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_manage->addWidget(tableView_ads);


        verticalLayout_3->addWidget(groupBox_manage);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionExit);
        menu_2->addAction(actionSettings);
        menu_3->addAction(actionAbout);

        retranslateUi(MainWindow);

        stackedWidget_ad->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\347\224\265\346\242\257\345\271\277\345\221\212\350\275\256\346\222\255\344\270\216\346\245\274\345\261\202\344\277\241\346\201\257\347\263\273\347\273\237", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        groupBox_floor->setTitle(QCoreApplication::translate("MainWindow", "\347\224\265\346\242\257\347\212\266\346\200\201", nullptr));
        label_floor_number->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_floor_arrow->setText(QCoreApplication::translate("MainWindow", "\342\217\270", nullptr));
        label_floor_direction->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        btn_floor_1->setText(QCoreApplication::translate("MainWindow", "1\346\245\274", nullptr));
        btn_floor_2->setText(QCoreApplication::translate("MainWindow", "2\346\245\274", nullptr));
        btn_floor_3->setText(QCoreApplication::translate("MainWindow", "3\346\245\274", nullptr));
        btn_floor_4->setText(QCoreApplication::translate("MainWindow", "4\346\245\274", nullptr));
        btn_floor_5->setText(QCoreApplication::translate("MainWindow", "5\346\245\274", nullptr));
        btn_floor_6->setText(QCoreApplication::translate("MainWindow", "6\346\245\274", nullptr));
        btn_floor_7->setText(QCoreApplication::translate("MainWindow", "7\346\245\274", nullptr));
        btn_floor_8->setText(QCoreApplication::translate("MainWindow", "8\346\245\274", nullptr));
        groupBox_ad->setTitle(QCoreApplication::translate("MainWindow", "\345\271\277\345\221\212\346\222\255\346\224\276", nullptr));
        label_ad_image->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\345\212\240\350\275\275\345\271\277\345\221\212...", nullptr));
        label_ad_text->setText(QCoreApplication::translate("MainWindow", "\346\232\202\346\227\240\346\226\207\345\255\227\345\271\277\345\221\212", nullptr));
        btn_ad_prev->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\344\270\252\345\271\277\345\221\212", nullptr));
        btn_ad_next->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252\345\271\277\345\221\212", nullptr));
        btn_ad_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234\350\275\256\346\222\255", nullptr));
        btn_ad_resume->setText(QCoreApplication::translate("MainWindow", "\347\273\247\347\273\255\350\275\256\346\222\255", nullptr));
        groupBox_manage->setTitle(QCoreApplication::translate("MainWindow", "\345\271\277\345\221\212\350\256\241\345\210\222\347\256\241\347\220\206", nullptr));
        btn_refresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        btn_update->setText(QCoreApplication::translate("MainWindow", "\346\211\213\345\212\250\346\233\264\346\226\260\345\271\277\345\221\212", nullptr));
        btn_add->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\271\277\345\221\212", nullptr));
        btn_remove->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\271\277\345\221\212", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
