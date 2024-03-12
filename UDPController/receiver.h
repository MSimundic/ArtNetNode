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
    Receiver(QWidget *parent = nullptr);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocketv4;
    QHostAddress groupAddressv4;
};

#endif // RECEIVER_H
