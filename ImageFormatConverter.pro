#-------------------------------------------------
#
# Project created by QtCreator 2018-01-08T10:21:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageFormatConverter
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

GIT_VERSION = "$(shell git -C \""$$_PRO_FILE_PWD_"\" describe)"
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32 {
INCLUDEPATH += C:\opencv\build\include
LIBS += -LC:\opencv\build\x86\mingw\lib \
        -lopencv_core331        \
        -lopencv_highgui331     \
        -lopencv_imgcodecs331   \
        -lopencv_imgproc331     \
        -lopencv_features2d331  \
        -lopencv_calib3d331
} else {
CONFIG += link_pkgconfig
PKGCONFIG += opencv
}
