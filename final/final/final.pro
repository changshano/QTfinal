QT       += core gui widgets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 添加资源文件
RESOURCES += \
    resources.qrc

# 源文件
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    databasehandler.cpp \
    networkmanager.cpp \
    adupdateworker.cpp \
    adplanmodel.cpp

HEADERS += \
    mainwindow.h \
    databasehandler.h \
    networkmanager.h \
    adupdateworker.h \
    adplanmodel.h

FORMS += \
    mainwindow.ui

# 默认规则
DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc
UI_DIR = $$PWD/ui
