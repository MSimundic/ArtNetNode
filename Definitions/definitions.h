#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "qtypes.h"

enum class OpCode : quint16 {
    // Device Discovery
    Poll = 0x2000,
    PollReply = 0x2100,
    // Device Configuration
    Address = 0x6000,
    Input = 0x7000,
    IpProg = 0xF800,
    IpProgReply = 0xF900,
    Command = 0x2400,
    // Streaming Control
    Dmx = 0x5000,
    Nzs = 0x5100,
    Sync = 0x5200,
    // RDM
    TodRequest = 0x8000,
    TodData = 0x8100,
    TodControl = 0x8200,
    Rdm = 0x8300,
    RdmSub = 0x8400,
    // Time-Keeping
    TimeCode = 0x9700,
    TimeSync = 0x9800,
    // Triggering
    Trigger = 0x9900,
    // Diagnostics
    DiagData = 0x2300,
    // File Transfer
    FirmwareMaster = 0xF200,
    FirmwareReply = 0xF300,
    Directory = 0x9A00,
    DirectoryReply = 0x9B00,
    FileTnMaster = 0xF400,
    FileFnMaster = 0xF500,
    FileFnReply = 0xF600,
    // N/A
    NA = 0x0000,
};

constexpr int DEFAULT_PORT{6454}; // 0x1936
constexpr int PROTOCOL_VER{14};   // 0x000E
constexpr int ID_LENGTH{8};
constexpr char ARTNET_ID[static_cast<int>(ID_LENGTH)]{"Art-Net"};

#endif // DEFINITIONS_H
