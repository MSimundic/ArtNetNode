#ifndef ARTNETCONTROLLER_H
#define ARTNETCONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QtNetwork>

#include "ArtPollReplyPacket.h"
#include "Config.h"
#include "definitions.h"
class ArtNetController : public QObject
{
    Q_OBJECT
public:
    ArtNetController();
    ~ArtNetController();

public slots:
    void artPoll(QNetworkDatagram datagram);
    void artPollReply(QNetworkDatagram datagram);
    void artDMX(QNetworkDatagram datagram);
    void artAddress(QNetworkDatagram datagram);
    void outputDmx();

private:
    ArtPollReplyPacket constructArtPollReply(QNetworkDatagram datagram);
    Config getConfig();
    void configSerialPort(QSerialPort *serialPort);

    QSerialPort *serialPort;
    QByteArray data;
    Config config;

signals:
    void sendDatagram(QNetworkDatagram datagram);
};

#endif // ARTNETCONTROLLER_H
