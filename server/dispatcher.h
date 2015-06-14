#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <QObject>
#include <tlv.h>

class Dispatcher : public QObject
{
    Q_OBJECT
    QTlvServer* server;
    QList<QTlvSocket*> sockets;
public:
    explicit Dispatcher(QObject *parent = 0);
    ~Dispatcher();
    void sendData(const Command type, const QByteArray &value = QByteArray());

signals:


private slots:
    void parseSocketState(QAbstractSocket::SocketState socketState);
    void acceptConnection();

};

#endif // DISPATCHER_H
