#include "tlv.h"
#include <stdio.h>

void QTlvSocket::reliableRead()
{
    static QByteArray infoPackBuffer;
    static QByteArray dataBuffer;
    static bool infoPackIsReceived{false};

    while(bytesAvailable() > 0) {
        if(!infoPackIsReceived) {
            QByteArray buf = read(sizeof(InfoPack) - infoPackBuffer.size());

            if(buf.size() > 0)
                infoPackBuffer.append(buf);

            if(infoPackBuffer.size() == sizeof(InfoPack)) {
                data.clear();
                infoPack = *reinterpret_cast<InfoPack*>(infoPackBuffer.data());
                infoPackBuffer.clear();

                if(infoPack.length == 0)
                    emit newData(infoPack.type, QByteArray());
                else {
                    infoPackIsReceived = true;
                }
            }
        }
        else {
            QByteArray buf = read(infoPack.length - dataBuffer.size());

            if(buf.size() > 0)
                dataBuffer.append(buf);

            if(dataBuffer.size() == infoPack.length) {
                data.clear();
                data = dataBuffer;
                infoPackIsReceived = false;
                dataBuffer.clear();
                emit newData(infoPack.type, this->data);
            }
        }
    }
}

QTlvSocket::QTlvSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(reliableRead()));
}

u16be QTlvSocket::reliableWrite(const u8 type, const QByteArray &value)
{
    QByteArray dataBuffer;
    InfoPack infoPack;
    u16be currentWriteSize{0};

    infoPack.length = value.size();
    infoPack.type = type;

    dataBuffer.append(reinterpret_cast<char*>(&infoPack), sizeof(InfoPack));
    dataBuffer.append(value);

    while(currentWriteSize < dataBuffer.size()) {
        qint64 size = write(dataBuffer);
        if(size < 0) {
            return currentWriteSize;
        }
        else {
            currentWriteSize += size;
            dataBuffer = dataBuffer.right(dataBuffer.size() - size);
        }
    }
    return currentWriteSize;
}

void QTlvServer::incomingConnection(qintptr socketDescriptor)
{
    QTlvSocket* qts = new QTlvSocket;
    qts->setSocketDescriptor(socketDescriptor);
    pendingConnection = qts;
}

QTlvSocket *QTlvServer::nextPendingConnection()
{
    return pendingConnection;
}
