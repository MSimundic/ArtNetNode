#ifndef PACKETCONFIG_H
#define PACKETCONFIG_H
#include <QDebug>
#include <QObject>
#include <cstdint>
typedef struct PacketConfig
{
    uint16_t oem{0x00FF};
    uint16_t esta_man{0x0000};
    uint16_t netSubNetUni{0x0000};
    uint8_t status1{0x00};
    uint8_t status2{0x08};
    QString short_name{"OrangePI ArtNet"};
    QString long_name{"OrangePI ArtNet Protocol long"};
    QString node_report{"nothing to report"};
    QString ip{"192.168.0.40"};
    //QString mac{"02:81:0c:15:eb:bc"};
    QString mac{"58:11:22:DC:18:37"};
} PacketConfig;

#endif // PACKETCONFIG_H
