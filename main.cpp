#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include "artnetcontroller.h"
#include "decoder.h"
#include "receiver.h"
#include "sender.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer *timer = new QTimer();

    // Receiver *receiver = new Receiver();
    // QThread *receiverThread = new QThread();
    // receiver->moveToThread(receiverThread);
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

    QObject::connect(timer, &QTimer::timeout, &artNetController, &ArtNetController::outputDmx);
    timer->start(250);

    return a.exec();
}
