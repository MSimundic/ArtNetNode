#include "decoder.h"
Decoder::Decoder() {}

void Decoder::decodeDatagram(QNetworkDatagram datagram)
{
    //qInfo("try decode datagram");

    OpCode opCode = getOpCode(datagram);
    //qInfo() << "OpCode: " << QString("0x%1").arg(static_cast<int>(opCode), 4, 16, QLatin1Char('0'));
    switch (opCode) {
    case OpCode::Poll:
        qInfo() << "ArtPoll";
        emit artPoll(datagram);
        break;
    case OpCode::PollReply:
        qInfo() << "ArtPollReply";
        emit artPollReply(datagram);
        break;
    case OpCode::Dmx:
        qInfo() << "ArtDMX";
        emit artDMX(datagram);
        break;
    case OpCode::Address:
        qInfo() << "ArtAddress";
        emit artAddress(datagram);
        break;
    case OpCode::IpProg:
        qInfo() << "IpProg";
        emit artIpProg(datagram);
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
