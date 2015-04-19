#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T18:02:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PassMan
TEMPLATE = app

CONFIG += c++11

#openssl
win32 {
    INCLUDEPATH += c:/OpenSSL-Win32/include
    LIBS += -Lc:/OpenSSL-Win32/bin -llibeay32
}

linux|macx {
    LIBS += -lcrypto
}


SOURCES += main.cpp\
        mainwindow.cpp \
    cryptfiledevice.cpp

HEADERS  += mainwindow.h \
    cryptfiledevice.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
