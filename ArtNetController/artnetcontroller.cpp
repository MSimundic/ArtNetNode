#include "artnetcontroller.h"

ArtNetController::ArtNetController()
{
    
}
PacketConfig ArtNetController::getPacketConfig()
{
    PacketConfig config;

    return config;
}

ArtPollReplyPacket ArtNetController::constructArtPollReply(QNetworkDatagram datagram)
{
    ArtPollReplyPacket packet;
    PacketConfig config = ArtNetController::getPacketConfig();

    strcpy_s(reinterpret_cast<char *>(packet.id), 8, ARTNET_ID);
    // qInfo() << "Test: " << reinterpret_cast<char *>(packet.id);

    packet.op_code_l = ((uint16_t) OpCode::PollReply >> 0) & 0x00FF;
    packet.op_code_h = ((uint16_t) OpCode::PollReply >> 8) & 0x00FF;

    QStringList ipOctets = config.ip.split(".");
    packet.ip[0] = ipOctets.at(0).toUShort();
    packet.ip[1] = ipOctets.at(1).toUShort();
    packet.ip[2] = ipOctets.at(2).toUShort();
    packet.ip[3] = ipOctets.at(3).toUShort();

    bool okConversion = false;
    QStringList macOctets = config.mac.split(":");
    for (int i = 0; i < 6; i++) {
        packet.mac[i] = (unsigned char) macOctets.at(i).toUShort(&okConversion, 16);
    }

    packet.port_l = (DEFAULT_PORT >> 0) & 0xFF;
    packet.port_h = (DEFAULT_PORT >> 8) & 0xFF;

    packet.ver_h = (PROTOCOL_VER >> 8) & 0x00FF;
    packet.ver_l = (PROTOCOL_VER >> 0) & 0x00FF;
    packet.oem_h = (config.oem >> 8) & 0xFF;
    packet.oem_l = (config.oem >> 8) & 0xFF;
    packet.ubea_ver = 0; // UBEA not programmed
    packet.status_1 = config.status1;
    packet.esta_man_l = (config.esta_man >> 8) & 0xFF;
    packet.esta_man_h = (config.esta_man >> 8) & 0xFF;

    memcpy_s(packet.short_name,
             sizeof(packet.short_name),
             config.short_name.toStdString().c_str(),
             config.short_name.length());
    memcpy_s(packet.long_name,
             sizeof(packet.long_name),
             config.long_name.toStdString().c_str(),
             config.long_name.length());
    memcpy_s(packet.node_report,
             sizeof(packet.node_report),
             config.node_report.toStdString().c_str(),
             config.node_report.length());

    packet.num_ports_h = 0; // Reserved
    packet.num_ports_l = 1;

    memset(packet.port_types, 0, 4);
    memset(packet.good_input, 0, 4);
    memset(packet.good_output, 0, 4);
    memset(packet.sw_in, 0, 4);
    memset(packet.sw_out, 0, 4);

    packet.net_sw = (config.netSubNetUni >> 8) & 0x7F;
    packet.sub_sw = (config.netSubNetUni >> 4) & 0x0F;
    packet.sw_in[0] = (config.netSubNetUni >> 0) & 0x0F;
    packet.sw_out[0] = 0;
    packet.port_types[0] = 0xC0;
    packet.good_input[0] = 0x80;
    packet.good_output[0] = 0x80;
    packet.sw_video = 0;
    packet.sw_macro = 0;
    packet.sw_remote = 0;
    memset(packet.spare, 0x00, 3);
    packet.style = 0x00;

    packet.bind_ip[0] = ipOctets.at(0).toUShort();
    packet.bind_ip[1] = ipOctets.at(1).toUShort();
    packet.bind_ip[2] = ipOctets.at(2).toUShort();
    packet.bind_ip[3] = ipOctets.at(3).toUShort();

    packet.bind_index = 0;
    packet.status_2 = config.status2;
    memset(packet.filler, 0x00, 26);
    //qInfo() << "Packet formed";
    return packet;
}

void ArtNetController::artPoll(QNetworkDatagram datagram)
{
    //qInfo() << "artpoll called in controller";
    ArtPollReplyPacket packet = constructArtPollReply(datagram);
    QByteArray bytePacket = QByteArray::fromRawData(reinterpret_cast<const char *>(&packet),
                                                    sizeof(packet));
    qInfo() << "emit sendDatagram";
    emit sendDatagram(datagram.makeReply(bytePacket));
}

void ArtNetController::artPollReply(QNetworkDatagram datagram) {}

void ArtNetController::artDMX(QNetworkDatagram datagram) {}

void ArtNetController::artAddress(QNetworkDatagram datagram) {}
