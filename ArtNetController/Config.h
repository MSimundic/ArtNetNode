#ifndef CONFIG_H
#define CONFIG_H
#include <QDebug>
#include <QObject>
#include <cstdint>
typedef struct Config
{
    uint16_t oem{0x00FF};
    uint16_t estaMan{0x0000};
    uint8_t net{0x00};
    uint8_t subNet{0x00};
    uint8_t uni1{0x00};
    uint8_t uni2{0x01};
    uint8_t status1{0x00};
    uint8_t status2{0x08};
    QString shortName{"OrangePI ArtNet"};
    QString longName{"OrangePI ArtNet Protocol long"};
    QString nodeReport{"nothing to report"};
    QString ip{"192.168.0.40"};
    QString subnetMask {"255.255.255.0"};
    //QString mac{"02:81:0c:15:eb:bc"};
    QString mac{"58:11:22:DC:18:37"};
    QString device1{"/dev/ttyUSB0"};
    QString device2{"/dev/ttyUSB1"};
} Config;

#endif // CONFIG_H
