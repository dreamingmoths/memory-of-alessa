#ifndef EN_COMMON_H
#define EN_COMMON_H

#include "Chacter/character.h"

struct EnSOUND_QUEUE {
    // total size: 0x10
    struct SubCharacter * scp; // offset 0x0, size 0x4
    signed int num; // offset 0x4, size 0x4
    float vol; // offset 0x8, size 0x4
    float time; // offset 0xC, size 0x4
};

struct EnFORBIDDENAREA {
    // total size: 0x10
    float x0; // offset 0x0, size 0x4
    float z0; // offset 0x4, size 0x4
    float x1; // offset 0x8, size 0x4
    float z1; // offset 0xC, size 0x4
};
struct EnLOCAL_WORK {
    // total size: 0x1E10
    struct EnLOCAL_DATA Data[32]; // offset 0x0, size 0x1C00
    struct EnCOMMUNICATION Communication[8]; // offset 0x1C00, size 0x100
    struct EnFORBIDDENAREA ForbiddenArea[2]; // offset 0x1D00, size 0x20
    struct EnSOUND_QUEUE SoundQueue[8]; // offset 0x1D20, size 0x80
    signed int CommunicationNum; // offset 0x1DA0, size 0x4
    signed int ForbiddenNum; // offset 0x1DA4, size 0x4
    signed int SoundQueueNum; // offset 0x1DA8, size 0x4
    unsigned int Status; // offset 0x1DAC, size 0x4
    struct EnLOCAL_DATA * This; // offset 0x1DB0, size 0x4
    struct _CL_VHIT_RESULT HitResult; // offset 0x1DC0, size 0x40
    signed int Max3DSounds; // offset 0x1E00, size 0x4
    signed int ActiveEnemy; // offset 0x1E04, size 0x4
};
struct EnLOCAL_WORK enLocalWork; // size: 0x1E10, address: 0x5506A0
struct EnLOCAL_DATA * enEntryEnemy(signed int kind /* r2 */);

#endif
