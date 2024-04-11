#ifndef ARTPOLLREPLYPACKET_H
#define ARTPOLLREPLYPACKET_H
#include "qtypes.h"
typedef struct ArtPollReplyPacket
{
    quint8 id[8];
    quint8 op_code_l;
    quint8 op_code_h;
    quint8 ip[4];
    quint8 port_l;
    quint8 port_h;
    quint8 ver_h;
    quint8 ver_l;
    quint8 net_sw;
    quint8 sub_sw;
    quint8 oem_h;
    quint8 oem_l;
    quint8 ubea_ver;
    quint8 status_1;
    quint8 esta_man_l;
    quint8 esta_man_h;
    quint8 short_name[18];
    quint8 long_name[64];
    quint8 node_report[64];
    quint8 num_ports_h;
    quint8 num_ports_l;
    quint8 port_types[4];
    quint8 good_input[4];
    quint8 good_output[4];
    quint8 sw_in[4];
    quint8 sw_out[4];
    quint8 sw_video;
    quint8 sw_macro;
    quint8 sw_remote;
    quint8 spare[3];
    quint8 style;
    quint8 mac[6];
    quint8 bind_ip[4];
    quint8 bind_index;
    quint8 status_2;
    quint8 filler[26];
} ArtPollReplyPacket;

#endif // ARTPOLLREPLYPACKET_H
