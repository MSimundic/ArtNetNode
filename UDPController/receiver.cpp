#include "receiver.h"
#include <QtNetwork>
#include <QtWidgets>
#include <iostream>
using namespace std;
Receiver::Receiver(QWidget *parent)
    : QDialog(parent)
    , groupAddressv4(QStringLiteral("192.168.0.1"))

{
    udpSocketv4.bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress);
    udpSocketv4.joinMulticastGroup(groupAddressv4);

    //connect()
    connect(&udpSocketv4, &QUdpSocket::readyRead, this, &Receiver::processPendingDatagrams);
}

void Receiver::processPendingDatagrams()
{
    QByteArray datagram;

    // using QUdpSocket::receiveDatagram (API since Qt 5.8)
    while (udpSocketv4.hasPendingDatagrams()) {
        QNetworkDatagram dgram = udpSocketv4.receiveDatagram();

        cout << dgram.data().constData() << endl;
    }
}
