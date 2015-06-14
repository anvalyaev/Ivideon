#ifndef ANEXCHANGE_H
#define ANEXCHANGE_H
#include <QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include "littlebigendiannames.h"

#pragma pack (push, 1)
struct InfoPack
{
    u8 type;
    u16be length; /*Ранее не использовал такой подход,
    но выглядит более красиво чем htons/ntohs или QtEndian*/
};
#pragma pack (pop)

enum struct Command : u8
{
    ON = 0x12,
    OFF,
    COLOR = 0x20
};

struct RGB
{
    u8 red;
    u8 green;
    u8 blue;
};

class QTlvSocket : public QTcpSocket
{
    Q_OBJECT
    InfoPack infoPack;
    QByteArray data;
public:
    QTlvSocket(QObject *parent = 0);
    u16be reliableWrite(const u8 type, const QByteArray &value);
signals:
    void newData(const u8 type, const QByteArray &value);
private slots:
    void reliableRead();
};

class QTlvServer : public QTcpServer
{
    QTlvSocket *pendingConnection;
    void incomingConnection(qintptr socketDescriptor);
public:
    QTlvSocket *nextPendingConnection();
};





#endif // ANEXCHANGE_H
