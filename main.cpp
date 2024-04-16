#include <QCoreApplication>
#include "artnetcontroller.h"
#include "decoder.h"
#include "receiver.h"
#include "sender.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Receiver receiver;
    Decoder decoder;
    Sender sender;
    ArtNetController artNetController;

    QObject::connect(&receiver, &Receiver::readDone, &decoder, &Decoder::decodeDatagram);
    QObject::connect(&decoder, &Decoder::artPoll, &artNetController, &ArtNetController::artPoll);
    QObject::connect(&decoder, &Decoder::artDMX, &artNetController, &ArtNetController::artDMX);
    QObject::connect(&artNetController,
                     &ArtNetController::sendDatagram,
                     &sender,
                     &Sender::sendDatagram);

    //QByteArray datagram = "1234";
    //QString ipAddress = "192.168.0.24";
    //sender.sendDatagram(datagram, ipAddress);

    return a.exec();
}
