#ifndef RECEIVER_H
#define RECEIVER_H

#include <QHostAddress>
#include <QUdpSocket>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver();

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocketv4;
};

#endif // RECEIVER_H
