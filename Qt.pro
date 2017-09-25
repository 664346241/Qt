#-------------------------------------------------
#
# Project created by QtCreator 2017-09-12T14:48:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rtu.cpp \
    thired.cpp

HEADERS  += mainwindow.h \
    rtu.h \
    chwenjian.h \
    thired.h

FORMS    += mainwindow.ui \
    rtu.ui \
    thired.ui

RESOURCES += \
    resource.qrc

DISTFILES +=
