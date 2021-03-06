#-------------------------------------------------
#
# Project created by QtCreator 2018-01-11T20:48:55
#
#-------------------------------------------------

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = Blink
TEMPLATE = app

DEFINES +=\
    "VERSION_MAJOR=$$VERSION_MAJOR"\
    "VERSION_MINOR=$$VERSION_MINOR"\
    "VERSION_PATCH=$$VERSION_PATCH"
#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}


SOURCES += main.cpp \
    OverlayWindow.cpp \
    Blink.cpp \
    settingsdialog.cpp

HEADERS  += \
    OverlayWindow.h \
    Blink.h \
    settingsdialog.h \
    settingsdef.h

FORMS    += \
    settingsdialog.ui
