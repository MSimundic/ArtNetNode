#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>

#include "definitions.h"
class Decoder : public QObject
{
    Q_OBJECT
public:
    Decoder();

private:
    OpCode getOpCode(QNetworkDatagram datagram);

public slots:
    void decodeDatagram(QNetworkDatagram datagram);

signals:
    void artPoll(QNetworkDatagram datagram);
    void artPollReply(QNetworkDatagram datagram);
    void artDMX(QNetworkDatagram datagram);
    void artAddress(QNetworkDatagram datagram);
    void artIpProg(QNetworkDatagram datagram);
};

#endif // DECODER_H
