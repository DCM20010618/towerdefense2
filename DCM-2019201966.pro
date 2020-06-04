#-------------------------------------------------
#
# Project created by QtCreator 2020-05-25T22:53:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DCM-2019201966
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    chooselevel.cpp \
    easy.cpp \
    hard.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    plistreader.cpp \
    utility.cpp

HEADERS += \
        mainwindow.h \
    chooselevel.h \
    easy.h \
    hard.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    enemy.h \
    bullet.h \
    plistreader.h \
    utility.h

FORMS += \
        mainwindow.ui \
    chooselevel.ui \
    easy.ui \
    hard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
