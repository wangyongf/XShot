#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T22:43:31
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScreenShot
TEMPLATE = app


SOURCES += main.cpp\
    afqt/AfRegionSelector.cpp \
    afqt/AfPicture.cpp \
    Portal.cpp \
    afos/AfCd_Win32.cpp

HEADERS  += \
    afqt/AfRegionSelector.h \
    afqt/AfPicture.h \
    afqt/AfScaler.h \
    Portal.h \
    afos/AfCd.h

FORMS += \
    Portal.ui

RESOURCES += \
    screen.qrc
