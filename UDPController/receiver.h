#ifndef RECEIVER_H
#define RECEIVER_H

#include <QDialog>
#include <QHostAddress>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class Receiver : public QDialog
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
