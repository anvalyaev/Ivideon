#-------------------------------------------------
#
# Project created by QtCreator 2015-06-13T09:33:52
#
#-------------------------------------------------

QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dispatcher.cpp

HEADERS  += mainwindow.h \
    dispatcher.h

unix: LIBS += -L$$OUT_PWD/../tlv/ -ltlv

INCLUDEPATH += $$PWD/../tlv
DEPENDPATH += $$PWD/../tlv

unix: PRE_TARGETDEPS += $$OUT_PWD/../tlv/libtlv.a
