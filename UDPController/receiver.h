#ifndef RECEIVER_H
#define RECEIVER_H

#include <QHostAddress>
#include <QUdpSocket>

class Receiver
{
public:
    Receiver();

private:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocketv4;
    QHostAddress groupAddressv4;
};

#endif // RECEIVER_H
