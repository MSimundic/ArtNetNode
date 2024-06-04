#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include "artnetcontroller.h"
#include "decoder.h"
#include "receiver.h"
#include "sender.h"
#include "httpserver.h"
#include "jsonserializer.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer *timer = new QTimer();

    Receiver receiver;
    Decoder decoder;
    Sender sender;
    ArtNetController artNetController;
    HttpServer httpServer;
    JsonSerializer jsonSerializer;


    QObject::connect(&artNetController, &ArtNetController::newIpSet, &sender, &Sender::bindNewIp);
    QObject::connect(&artNetController, &ArtNetController::newIpSet, &receiver, &Receiver::bindNewIp);
    //QObject::connect(&artNetController, &ArtNetController::newIpSet, &httpServer, &HttpServer::listenNewIp);
    QObject::connect(&jsonSerializer, &JsonSerializer::configChanged, &artNetController, &ArtNetController::getConfig);
    QObject::connect(&httpServer, &HttpServer::fileReceived, &jsonSerializer, &JsonSerializer::writeToFile);
    QObject::connect(&receiver, &Receiver::readDone, &decoder, &Decoder::decodeDatagram);
    QObject::connect(&artNetController,
                     &ArtNetController::sendDatagram,
                     &sender,
                     &Sender::sendDatagram);

    QObject::connect(&decoder, &Decoder::artPoll, &artNetController, &ArtNetController::artPoll);
    QObject::connect(&decoder, &Decoder::artDMX, &artNetController, &ArtNetController::artDMX);
    QObject::connect(&decoder, &Decoder::artIpProg, &artNetController, &ArtNetController::artIpProg);
    QObject::connect(&decoder, &Decoder::artAddress, &artNetController, &ArtNetController::artAddress);

    QObject::connect(timer, &QTimer::timeout, &artNetController, &ArtNetController::outputDmx1);
    QObject::connect(timer, &QTimer::timeout, &artNetController, &ArtNetController::outputDmx2);
    timer->start(250);

    return a.exec();
}
