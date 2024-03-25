#include "sender.h"

Sender::Sender()
{
    udpSocketv4.bind(QHostAddress(QHostAddress::AnyIPv4), 0);

}




void Sender::sendDatagram(QByteArray datagram, QString ipAddress)
{
    qInfo("try send");
    datagram = datagram;
    consoleAddress4.setAddress(QString(ipAddress));
    udpSocketv4.writeDatagram(datagram, consoleAddress4, 6454);
    qInfo("sent");
}
