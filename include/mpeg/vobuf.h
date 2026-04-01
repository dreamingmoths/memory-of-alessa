// https://github.com/Mikompilation/Himuro/blob/828c49053f0d0a67694ae678463dfa3b770b6ef3/include/sce/mpeg/vobuf.h#L29

#ifndef SCE_MPEG_VOBUF_H
#define SCE_MPEG_VOBUF_H

#include "common.h"
#include "mpeg/libmpeg.h"
#include "mpeg/defs.h"
#include "mpeg/cscvu1.h"
#include "libipu.h"

#define VOBUF_STATUS_EMPTY 0
#define VOBUF_STATUS_TOPDONE 1
#define VOBUF_STATUS_FULL 2

typedef struct {
    u_char v[MAX_MBX * MAX_MBY * sizeof(sceIpuRAW8)];
} VoData;

typedef struct
{
    int status;
    u_int* v;
    int dummy[14];
} VoTag;

typedef struct
{
    VoData *data;
    VoTag *tagInter;
    VoTag *tag;
    volatile int write;
    volatile int count;
    int size;
} VoBuf;

#endif // SCE_MPEG_VOBUF_H
