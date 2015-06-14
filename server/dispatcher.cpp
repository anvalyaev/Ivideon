#include "dispatcher.h"

Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
    server = new QTlvServer();
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    server->listen(QHostAddress::Any, 9999);
}

Dispatcher::~Dispatcher()
{
    for(auto socket = sockets.begin(); socket != sockets.end(); socket++) {
        (*socket)->close();
    }
    server->close();

}

void Dispatcher::sendData(const Command type, const QByteArray &value)
{
    for(auto socket = sockets.begin(); socket != sockets.end(); socket++) {
        (*socket)->reliableWrite((u8)type, value);
    }
}

void Dispatcher::parseSocketState(QAbstractSocket::SocketState socketState)
{
    if(socketState == QAbstractSocket::UnconnectedState) {
        for(auto socket = sockets.begin(); socket != sockets.end(); socket++) {
            if((*socket)->state() == QAbstractSocket::UnconnectedState) {
                sockets.erase(socket);
            }
        }
    }
}

void Dispatcher::acceptConnection()
{
    QTlvSocket* qTlvSocket = server->nextPendingConnection();
    sockets.append(qTlvSocket);
    connect(qTlvSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
            SLOT(parseSocketState(QAbstractSocket::SocketState)));
}

