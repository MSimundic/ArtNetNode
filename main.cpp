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
    return a.exec();
}
