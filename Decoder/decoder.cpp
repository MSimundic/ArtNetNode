#include "decoder.h"
Decoder::Decoder() {}

void Decoder::decodeDatagram(QNetworkDatagram datagram)
{
    qInfo("try decode datagram");

    OpCode opCode = getOpCode(datagram);
    qInfo() << "OpCode: " << QString("0x%1").arg(static_cast<int>(opCode), 4, 16, QLatin1Char('0'));
    switch (opCode) {
    case OpCode::Poll:
        qInfo() << "ArtPoll";
        break;
    case OpCode::PollReply:
        qInfo() << "ArtPoll";
        break;
    default:

        break;
    }
}

OpCode Decoder::getOpCode(QNetworkDatagram datagram)
{
    OpCode opCode = static_cast<OpCode>(datagram.data().at(9) << 8 | datagram.data().at(8));
    return opCode;
}
