#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>

#include "definitions.h"
class Decoder : public QObject
{
    Q_OBJECT
public:
    Decoder();

public slots:
    void decodeDatagram(QNetworkDatagram datagram);
    OpCode getOpCode(QNetworkDatagram datagram);
};

#endif // DECODER_H
