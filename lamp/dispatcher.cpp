#include "dispatcher.h"
#include "iostream"
#include <QColor>

using namespace std;
Dispatcher::Dispatcher(QObject *qmlObject) : viewer(qmlObject)
{
    connect(&socket, SIGNAL(newData(const u8, const QByteArray&)), this, SLOT(parseData(const u8, const QByteArray&)));
    connect(qmlObject, SIGNAL(turnConnect(QString, int)), this, SLOT(connectToHost(QString, int)));
    connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
            SLOT(parseSocketState(QAbstractSocket::SocketState)));
}

void Dispatcher::parseData(const u8 type, const QByteArray &value)
{
    switch (type) {
    case (u8)Command::ON: {
        QVariant returnedValue;
        QMetaObject::invokeMethod(viewer, "turnOn",
                Q_RETURN_ARG(QVariant, returnedValue));
        break;
    }
    case (u8)Command::OFF: {
        QVariant returnedValue;
        QMetaObject::invokeMethod(viewer, "turnOff",
                Q_RETURN_ARG(QVariant, returnedValue));
        break;
    }
    case (u8)Command::COLOR: {
        const RGB *rgb = reinterpret_cast<const RGB *>(value.data());
        QColor color(rgb->red, rgb->green, rgb->blue);
        QVariant returnedValue;
        QMetaObject::invokeMethod(viewer, "changeColor",
                Q_RETURN_ARG(QVariant, returnedValue),
                Q_ARG(QVariant, color));
        break;
    }
    default:
        cout<<"Unknown command whith type "<< type<<endl;
        break;
    }
}

void Dispatcher::connectToHost(const QString &hostName, int port)
{
    socket.connectToHost(hostName, port, QTcpSocket::ReadOnly);
}

void Dispatcher::parseSocketState(QAbstractSocket::SocketState socketState)
{
    qDebug()<<socketState;
    if(socketState == QAbstractSocket::UnconnectedState) {
        QVariant returnedValue;
        QMetaObject::invokeMethod(viewer, "showConnectDialog",
                Q_RETURN_ARG(QVariant, returnedValue));
    }
}

