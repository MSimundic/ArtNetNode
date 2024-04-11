#ifndef ARTPOLLREPLYPACKET_H
#define ARTPOLLREPLYPACKET_H
//#include "qtypes.h"
#include <cstdint>
typedef struct ArtPollReplyPacket
{
    uint8_t id[8];
    uint8_t op_code_l;
    uint8_t op_code_h;
    uint8_t ip[4];
    uint8_t port_l;
    uint8_t port_h;
    uint8_t ver_h;
    uint8_t ver_l;
    uint8_t net_sw;
    uint8_t sub_sw;
    uint8_t oem_h;
    uint8_t oem_l;
    uint8_t ubea_ver;
    uint8_t status_1;
    uint8_t esta_man_l;
    uint8_t esta_man_h;
    uint8_t short_name[18];
    uint8_t long_name[64];
    uint8_t node_report[64];
    uint8_t num_ports_h;
    uint8_t num_ports_l;
    uint8_t port_types[4];
    uint8_t good_input[4];
    uint8_t good_output[4];
    uint8_t sw_in[4];
    uint8_t sw_out[4];
    uint8_t sw_video;
    uint8_t sw_macro;
    uint8_t sw_remote;
    uint8_t spare[3];
    uint8_t style;
    uint8_t mac[6];
    uint8_t bind_ip[4];
    uint8_t bind_index;
    uint8_t status_2;
    uint8_t filler[26];
} ArtPollReplyPacket;

#endif // ARTPOLLREPLYPACKET_H
