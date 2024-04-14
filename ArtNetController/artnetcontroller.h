#ifndef ARTNETCONTROLLER_H
#define ARTNETCONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QtNetwork>

#include "ArtPollReplyPacket.h"
#include "definitions.h"
#include "packetConfig.h"
class ArtNetController : public QObject
{
    Q_OBJECT
public:
    ArtNetController();

public slots:
    void artPoll(QNetworkDatagram datagram);
    void artPollReply(QNetworkDatagram datagram);
    void artDMX(QNetworkDatagram datagram);
    void artAddress(QNetworkDatagram datagram);

private:
    ArtPollReplyPacket constructArtPollReply(QNetworkDatagram datagram);
    PacketConfig getPacketConfig();

signals:
    void sendDatagram(QNetworkDatagram datagram);
};

#endif // ARTNETCONTROLLER_H
