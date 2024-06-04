#ifndef ARTNETCONTROLLER_H
#define ARTNETCONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QtNetwork>

#include "ArtPollReplyPacket.h"
#include "ArtIpProgReplyPacket.h"
#include "Config.h"
#include "definitions.h"
#include "jsonserializer.h"
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
    void artIpProg(QNetworkDatagram datagram);
    void outputDmx1();
    void outputDmx2();
    void getConfig();

private:
    ArtPollReplyPacket constructArtPollReply(QNetworkDatagram datagram);
    ArtIpProgReplyPacket constructIpProgReply();
    void changeIpNetmask(QString ip, QString netmask);
    void configSerialPort(QSerialPort *serialPort, QString portName);
    QString buildIpAddress(QByteArray bytesIp);
    QSerialPort *serialPort1;
    QSerialPort *serialPort2;
    QByteArray data1;
    QByteArray data2;
    Config config;

signals:
    void sendDatagram(QNetworkDatagram datagram);
    void newIpSet();
};

#endif // ARTNETCONTROLLER_H
