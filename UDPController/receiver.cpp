#include "receiver.h"

Receiver::Receiver()
{
    udpSocketv4.bind(QHostAddress::AnyIPv4, 6454, QUdpSocket::ShareAddress);
    //udpSocketv4.joinMulticastGroup(groupAddressv4);

    //connect()
    qInfo("try connect");
    connect(&udpSocketv4, &QUdpSocket::readyRead, this, &Receiver::processPendingDatagrams);
    qInfo("connected");
}

void Receiver::processPendingDatagrams()
{
    qInfo("process");
    // using QUdpSocket::receiveDatagram (API since Qt 5.8)
    while (udpSocketv4.hasPendingDatagrams()) {
        QNetworkDatagram dgram = udpSocketv4.receiveDatagram();

        qInfo("%s", dgram.data().constData());
    }
}
