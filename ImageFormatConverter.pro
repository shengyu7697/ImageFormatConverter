#-------------------------------------------------
#
# Project created by QtCreator 2018-01-08T10:21:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageFormatConverter
TEMPLATE = app
CONFIG += link_pkgconfig
PKGCONFIG += opencv

QMAKE_CXXFLAGS += -std=c++11

#GIT_VERSION = 0.9.1
GIT_VERSION="$(shell git -C \""$$_PRO_FILE_PWD_"\" describe)"
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
