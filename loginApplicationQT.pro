QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = loginApplicationQT
TEMPLATE = app

QT += sql

SOURCES += main.cpp\
           login.cpp \
           qaesencryption.cpp \
           registration.cpp

HEADERS  += \
            login.h \
            qaesencryption.h \
            registration.h


FORMS    += \
    login.ui \
    registration.ui

