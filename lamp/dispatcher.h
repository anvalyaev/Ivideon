#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <QDebug>
#include <QQmlContext>
#include <QDesktopServices>
#include <QGuiApplication>
#include <tlv.h>

class Dispatcher : public QObject
{
    Q_OBJECT
    QTlvSocket socket;
public:
    Dispatcher(QObject *qmlObject);
    ~Dispatcher(){}

public slots:
   void parseData(const u8 type, const QByteArray &value);
   void connectToHost(const QString &hostName, int port);
private slots:
    void parseSocketState(QAbstractSocket::SocketState socketState);

protected:
    QObject *viewer;

};

#endif // DISPATCHER_H
