#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T18:02:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordManager
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
    cryptfiledevice.cpp \
    db/querysmanager.cpp \
    db/connectionmanager.cpp \
    definespath.cpp \
    passwordgenerator.cpp \
    Data/data.cpp \
    dbfileprocessing.cpp \
    recentdocuments.cpp \
    aboutdialog.cpp \
    helpdialog.cpp

HEADERS  += mainwindow.h \
    cryptfiledevice.h \
    db/querysmanager.h \
    db/connectionmanager.h \
    definespath.h \
    globalenum.h \
    passwordgenerator.h \
    Data/data.h \
    dbfileprocessing.h \
    recentdocuments.h \
    aboutdialog.h \
    helpdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    helpdialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    l10n/PassMan_ru.ts
