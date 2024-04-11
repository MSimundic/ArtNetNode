#include <QCoreApplication>
#include "receiver.h"
#include "sender.h"
#include "decoder.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Receiver receiver;
    Decoder decoder;
    Sender sender;

    QObject::connect(&receiver, &Receiver::readDone, &decoder, &Decoder::decodeDatagram);
    QByteArray datagram = "1234";
    QString ipAddress = "192.168.0.24";
    sender.sendDatagram(datagram, ipAddress);

    return a.exec();
}
