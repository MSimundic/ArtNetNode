#ifndef ARTIPPROGREPLYPACKET_H
#define ARTIPPROGREPLYPACKET_H
#include <cstdint>
typedef struct ArtIpProgReplyPacket
{
    uint8_t id[8];
    uint8_t opCodeLo;
    uint8_t opCodeHi;
    uint8_t protVerHi;
    uint8_t protVerLo;

    uint8_t filler[4];

    uint8_t progIpHi;
    uint8_t progIp2;
    uint8_t progIp1;
    uint8_t progIpLo;

    uint8_t progSmHi;
    uint8_t progSm2;
    uint8_t progSm1;
    uint8_t progSmLo;

    uint8_t progPortHi;
    uint8_t progPortLo;

    uint8_t status;

    uint8_t spare2;

    uint8_t progDgHi;
    uint8_t progDg2;
    uint8_t progDg1;
    uint8_t progDgLo;

    uint8_t spare7;
    uint8_t spare8;
} ArtIpProgReplyPacket;
#endif // ARTIPPROGREPLY_H
