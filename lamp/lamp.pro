TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    dispatcher.cpp

HEADERS += \
    dispatcher.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

unix: LIBS += -L$$OUT_PWD/../tlv/ -ltlv

INCLUDEPATH += $$PWD/../tlv
DEPENDPATH += $$PWD/../tlv

unix: PRE_TARGETDEPS += $$OUT_PWD/../tlv/libtlv.a


