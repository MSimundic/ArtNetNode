#include "artnetcontroller.h"

ArtNetController::ArtNetController()
{
    serialPort1 = new QSerialPort;
    serialPort2 = new QSerialPort;
    configSerialPort(serialPort1, "/dev/ttyUSB0");
    configSerialPort(serialPort2, "/dev/ttyUSB1");
    //configSerialPort(serialPort1, "COM10");
    //configSerialPort(serialPort2, "COM12");
    if (!serialPort1->open(QIODevice::WriteOnly))
        qCritical() << serialPort1->error();
    if (!serialPort2->open(QIODevice::WriteOnly))
        qCritical() << serialPort2->error();
    data1.fill(0x00, 512);
    data2.fill(0x00, 512);
    //() << "Data length: " << data.length();
    getConfig();
}
ArtNetController::~ArtNetController()
{
    serialPort1->close();
    delete serialPort1;
    serialPort2->close();
    delete serialPort2;
}
void ArtNetController::getConfig()
{
    qInfo() << "ArtnetCon get config";
    JsonSerializer jsonSer;
    QJsonDocument jsonDoc = jsonSer.readJsonFile("./configuration.json");
    QJsonObject jsonObj = jsonDoc.object();
    config.shortName=jsonObj.find("shortName").value().toString();
    config.longName=jsonObj.find("longName").value().toString();
    config.ip=jsonObj.find("ipAddress").value().toString();
    config.subnetMask=jsonObj.find("subnetMask").value().toString();
    config.net=static_cast<uint8_t>(jsonObj.find("net").value().toInt());
    //uint8_t test = static_cast<uint8_t>(jsonObj.find("subnet").value().toString().toInt());
    config.subNet = static_cast<uint8_t>(jsonObj.find("subnet").value().toString().toInt());
    config.uni1 = static_cast<uint8_t>(jsonObj.find("uni1").value().toString().toInt());
    config.uni2 = static_cast<uint8_t>(jsonObj.find("uni2").value().toString().toInt());
    changeIpNetmask(config.ip, config.subnetMask);
}

void ArtNetController::changeIpNetmask(QString ip, QString netmask){
    qInfo() << "ChangeIpNetMask";
    QProcess process;
    QString command("echo msimundic | sudo -S ifconfig enp1s0 %1 netmask %2");
    command = command.arg(config.ip).arg(config.subnetMask);
    qInfo() << "command: " << command;

    process.startCommand("sh");
    process.write(command.toLocal8Bit().data());
    process.closeWriteChannel();
    process.waitForFinished();
    process.terminate();

    emit newIpSet();
}

void ArtNetController::configSerialPort(QSerialPort *serialPort, QString portName)
{
    //QSerialPort serialPort;
    serialPort->setPortName(portName);
    serialPort->setBaudRate(256000);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::TwoStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
}

ArtPollReplyPacket ArtNetController::constructArtPollReply(QNetworkDatagram datagram)
{
    ArtPollReplyPacket packet;

    strcpy(reinterpret_cast<char *>(packet.id), ARTNET_ID);
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
    packet.esta_man_l = (config.estaMan >> 8) & 0xFF;
    packet.esta_man_h = (config.estaMan >> 8) & 0xFF;

    memcpy(packet.short_name, config.shortName.toStdString().c_str(), config.shortName.length());
    memcpy(packet.long_name, config.longName.toStdString().c_str(), config.longName.length());
    memcpy(packet.node_report,
           config.nodeReport.toStdString().c_str(),
           config.nodeReport.length());

    packet.num_ports_h = 0;
    packet.num_ports_l = 2;

    memset(packet.port_types, 0, 4);
    memset(packet.good_input, 0, 4);
    memset(packet.good_output, 0, 4);
    memset(packet.sw_in, 0, 4);
    memset(packet.sw_out, 0, 4);

    packet.net_sw = (config.net) & 0x7F;
    packet.sub_sw = (config.subNet >> 4) & 0x0F;
    packet.sw_in[0] = (config.uni1 >> 0) & 0x0F;
    packet.sw_in[1] = (config.uni2 >> 0) & 0x0F;
    packet.sw_out[0] = (config.uni1 >> 0) & 0x0F;
    packet.sw_out[1] = (config.uni2 >> 0) & 0x0F;
    packet.port_types[0] = 0x80;
    packet.port_types[1] = 0x80;
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

ArtIpProgReplyPacket ArtNetController::constructIpProgReply(){
    ArtIpProgReplyPacket packet;

    strcpy(reinterpret_cast<char *>(packet.id), ARTNET_ID);
    // qInfo() << "Test: " << reinterpret_cast<char *>(packet.id);

    packet.opCodeLo = ((uint16_t) OpCode::IpProgReply >> 0) & 0x00FF;
    packet.opCodeHi = ((uint16_t) OpCode::IpProgReply >> 8) & 0x00FF;

    QStringList ipOctets = config.ip.split(".");
    packet.progIpHi = ipOctets.at(0).toUShort();
    packet.progIp2 = ipOctets.at(1).toUShort();
    packet.progIp1 = ipOctets.at(2).toUShort();
    packet.progIpLo = ipOctets.at(3).toUShort();

    QStringList subnetMaskOctets = config.subnetMask.split(".");
    packet.progSmHi = subnetMaskOctets.at(0).toUShort();
    packet.progSm2 = subnetMaskOctets.at(1).toUShort();
    packet.progSm1 = subnetMaskOctets.at(2).toUShort();
    packet.progSmLo = subnetMaskOctets.at(3).toUShort();

    return packet;
}

void ArtNetController::outputDmx1()
{
    serialPort1->setBreakEnabled(true);
    //QThread::msleep(1);
    serialPort1->setBreakEnabled(false);
    QByteArray dataToSend1 = data1;
    dataToSend1.prepend(QByteArray::fromHex("00"));
    int count = serialPort1->write(dataToSend1);

    qInfo() << "Number of bytes sent Uni1 " << count;

    serialPort1->waitForBytesWritten(-1);
}

void ArtNetController::outputDmx2()
{
    serialPort2->setBreakEnabled(true);
    //QThread::msleep(1);
    serialPort2->setBreakEnabled(false);
    QByteArray dataToSend2 = data2;
    dataToSend2.prepend(QByteArray::fromHex("00"));
    int count = serialPort2->write(dataToSend2);

    qInfo() << "Number of bytes sent Uni 2 " << count;

    serialPort2->waitForBytesWritten(-1);
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

void ArtNetController::artDMX(QNetworkDatagram datagram)
{
    //qInfo() << "Config uni: " << config.net << "Config subnet " << config.subNet;
    //qInfo() << "Packet uni: " << datagram.data().at(15) << "Packet subnetUni "
    //        << datagram.data().at(14);
    uint8_t subNetUni1, subNetUni2;

    //uint8_t uni1 = (config.uni1 & 0x0F);
    //uint8_t uni2 = (config.uni2 & 0x0F);
    // uint8_t subNet1 = (config.subNet << 4);
    // uint8_t subNet2 = (config.subNet << 4);

    subNetUni2 = (config.subNet << 4) | (config.uni1 & 0x0F);
    subNetUni1 = (config.subNet << 4) | (config.uni2 & 0x0F);

    if (datagram.data().at(15) == config.net && datagram.data().at(14) == subNetUni1) {
        //qInfo() << "SubnetUni:" << subNetUni1;
        data1 = datagram.data().mid(18, 512);
        outputDmx1();
    }
    if (datagram.data().at(15) == config.net && datagram.data().at(14) == subNetUni2) {
        //qInfo() << "SubnetUni:" << subNetUni2;
        data2 = datagram.data().mid(18, 512);
        outputDmx2();
    }
}

void ArtNetController::artAddress(QNetworkDatagram datagram) {
    uint8_t command = datagram.data().at(106);

    JsonSerializer jsonSer;
    QJsonDocument jsonDoc = jsonSer.readJsonFile("./configuration.json");
    QJsonObject jsonObj = jsonDoc.object();
    QByteArray data = datagram.data();

    QString longName(data.mid(32,64));
    QString shortName(data.mid(14,18));
    if(longName.at(0)!=0x0000){
        jsonObj.find("longName").value()=longName;
    }
    if(shortName.at(0)!=0x0000){
        jsonObj.find("shortName").value()=shortName;
    }

    if((data.at(12) & 0b10000000) == 128){
        jsonObj.find("net").value() = data.at(12) & 0b01111111;
    }

    // QString subNetUni(jsonObj.find("primary").value());

    // if((data.at(96) & 0b10000000) == 128){
    //     subNetUni =
    // }


    jsonDoc.setObject(jsonObj);
    jsonSer.writeToFile(jsonDoc.toJson(),"./configuration.json");
    getConfig();
    ArtPollReplyPacket packet = constructArtPollReply(datagram);
    QByteArray bytePacket = QByteArray::fromRawData(reinterpret_cast<const char *>(&packet),
                                                    sizeof(packet));
    qInfo() << "emit sendDatagram";
    emit sendDatagram(datagram.makeReply(bytePacket));
}

QString ArtNetController::buildIpAddress(QByteArray bytesIp){
    QString ipAddress;
    //QString octet(reinterpret_cast<int>(bytesIp.at(0)));
    ipAddress =
        QString::number(static_cast<uint8_t>(bytesIp.at(0))) + QString(".") +
        QString::number(static_cast<uint8_t>(bytesIp.at(1))) + QString(".") +
        QString::number(static_cast<uint8_t>(bytesIp.at(2))) + QString(".") +
        QString::number(static_cast<uint8_t>(bytesIp.at(3)));



    return ipAddress;
}

void ArtNetController::artIpProg(QNetworkDatagram datagram) {
    uint8_t command = datagram.data().at(14);

    JsonSerializer jsonSer;
    QJsonDocument jsonDoc = jsonSer.readJsonFile("./configuration.json");
    QJsonObject jsonObj = jsonDoc.object();
    QByteArray data = datagram.data();
    bool enableProgramming = false;
    if((command & 0b10000000) == 128){
        // jsonObj.find("ipAddress").value() = QString(datagram.data().mid(16,4));
        // jsonObj.find("subnetMask").value() = QString(datagram.data().mid(20,4));
        // jsonObj.find("primary").value() = QString(datagram.data().at(25));
        enableProgramming = true;
        qInfo() << "enable prog";
    }
    if ((command & 0b01000000) == (64 & enableProgramming)) {
        qInfo() << "DHCP not avilable";
    }
    if ((command & 0b00100000) == (32 & enableProgramming)) {
        qInfo() << "Not used";
    }
    if ((command & 0b00010000) == (16 & enableProgramming)) {
        qInfo() << "Default gateway not used";
    }
    if ((command & 0b00001000) == (8 & enableProgramming)) {
        Config defaultConfig;
        //jsonObj.find("longName").value()=defaultConfig.longName;
        //jsonObj.find("shortName").value()=defaultConfig.shortName;
        jsonObj.find("ipAddress").value()=defaultConfig.ip;
        jsonObj.find("subnetMask").value()=defaultConfig.subnetMask;
        //jsonObj.find("net").value()=defaultConfig.net;
        //jsonObj.find("primary").value()=defaultConfig.subNetUni;
        //jsonObj.find("device").value()=defaultConfig.device;
        qInfo() << "default change";
    }
    if ((command & 0b00000100) == (4 & enableProgramming)) {
        jsonObj.find("ipAddress").value() = buildIpAddress(datagram.data().mid(16,4));
        qInfo() << "IP change";
    }
    if ((command & 0b00000010) == (2 & enableProgramming)) {
        jsonObj.find("subnetMask").value() = buildIpAddress(datagram.data().mid(20,4));
        qInfo() << "sm change";
    }
    if ((command & 0b00000001) == (1 & enableProgramming)) {
        qInfo() << "Cant change default port";
    }

    jsonDoc.setObject(jsonObj);
    jsonSer.writeToFile(jsonDoc.toJson(),"./configuration.json");
    getConfig();
    ArtIpProgReplyPacket packet = constructIpProgReply();
    QByteArray bytePacket = QByteArray::fromRawData(reinterpret_cast<const char *>(&packet),
                                                    sizeof(packet));
    qInfo() << "emit sendDatagram";
    emit sendDatagram(datagram.makeReply(bytePacket));
}
