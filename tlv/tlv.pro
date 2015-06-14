#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T08:41:34
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = tlv
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

SOURCES += tlv.cpp

HEADERS += tlv.h \
    littlebigendian.h \
    littlebigendiannames.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
