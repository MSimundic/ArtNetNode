#include <QCoreApplication>
#include "receiver.h"
#include "sender.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "test" << endl;
    Receiver receiver;

    Sender sender;

    QByteArray datagram = "1234";
    QString ipAdress = "10.10.1.140";
    sender.sendDatagram(datagram, ipAdress);

    return a.exec();
}
