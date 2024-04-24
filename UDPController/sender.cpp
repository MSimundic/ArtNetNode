#include "sender.h"

Sender::Sender()
{
    udpSocketv4.bind(QHostAddress(QHostAddress::AnyIPv4), 0);

}

void Sender::sendDatagram(QNetworkDatagram datagram)
{
    //qInfo("try send");
    qInfo() << datagram.destinationAddress();
    //consoleAddress4.setAddress(QString(ipAddress));
    udpSocketv4.writeDatagram(datagram);
    qInfo("\n\n");
}

void Sender::bindNewIp(){
    udpSocketv4.close();
    udpSocketv4.bind(QHostAddress(QHostAddress::AnyIPv4), 0);
    qInfo() << "Sender bind";
}
