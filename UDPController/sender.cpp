#include "sender.h"

Sender::Sender()
{
    udpSocketv4.bind(QHostAddress(QHostAddress::AnyIPv4), 0);

}

void Sender::sendDatagram(QNetworkDatagram datagram)
{
    qInfo("try send");
    qInfo() << datagram.destinationAddress();
    //consoleAddress4.setAddress(QString(ipAddress));
    udpSocketv4.writeDatagram(datagram);
    qInfo("sent\n\n");
}
