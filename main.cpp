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
    QString ipAddress = "10.10.1.140";
    sender.sendDatagram(datagram, ipAddress);

    return a.exec();
}
