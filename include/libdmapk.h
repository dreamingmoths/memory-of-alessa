#ifndef LIB_DMA_PK_H
#define LIB_DMA_PK_H

#include "common.h"

typedef struct
{
    u_int *pCurrent;
    u_long128 *pBase;
    u_long128 *pDmaTag;
    u_int *pVifCode;

    u_int numlen;
    u_int pad11;
    u_int pad12;
    u_int pad13;
} sceVif0Packet;

void sceVif0PkInit(sceVif0Packet *pPacket, u_long128 *pBase);

void sceVif0PkReset(sceVif0Packet *pPacket);
u_long128 *sceVif0PkTerminate(sceVif0Packet *pPacket);

void sceVif0PkNext(sceVif0Packet *pPacket, u_long128 *pNext, u_int flag);
void sceVif0PkCall(sceVif0Packet *pPacket, u_long128 *pCall, u_int flag);

void sceVif0PkEnd(sceVif0Packet *pPacket, u_int flag);

#endif