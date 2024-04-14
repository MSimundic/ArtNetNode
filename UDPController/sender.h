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

public slots:
    void sendDatagram(QNetworkDatagram datagram);

private:
    QUdpSocket udpSocketv4;
};


#endif // SENDER_H
