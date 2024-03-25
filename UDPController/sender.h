#ifndef SENDER_H
#define SENDER_H

#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>
#include <QtNetwork>

class Sender : public QObject
{
    Q_OBJECT

public:
    explicit Sender();
    void sendDatagram(QByteArray datagram, QString ipAddress);

private:
    QUdpSocket udpSocketv4;
    QHostAddress consoleAddress4;

};


#endif // SENDER_H
