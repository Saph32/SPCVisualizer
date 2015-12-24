#pragma once

#include "BaseTypes.h"

struct SPCFile
{
    char header[33];
    uint8 id666Tag[3];
    uint8 minor;

    uint8 pc[2];
    uint8 a;
    uint8 x;
    uint8 y;
    uint8 psw;
    uint8 sp;
    char reserved[2];

    char song[32];
    char game[32];
    char dumper[16];
    char comments[32];
    char date[11];

    char seconds[3];
    char fadeLenght[5];
    char artist[32];

    uint8 channel;
    uint8 emulator;
    char reserved2[45];

    uint8 ram[65536];
    uint8 dspRegs[128];
    uint8 unused[64];
    uint8 extraRAM[64];
};