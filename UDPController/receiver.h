#ifndef RECEIVER_H
#define RECEIVER_H

#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>
#include <QtNetwork>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver();

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocketv4;

signals:
    void readDone(QNetworkDatagram datagram);
};

#endif // RECEIVER_H
