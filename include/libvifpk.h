
#ifndef LIB_VIF_PK_H
#define LIB_VIF_PK_H

#include "eetypes.h"
#include "eestruct.h"

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

typedef struct
{
    u_int *pCurrent;
    u_long128 *pBase;
    u_long128 *pDmaTag;
    u_int *pVifCode;

    u_int numlen;
    u_long *pGifTag;
    u_int pad12;
    u_int pad13;
} sceVif1Packet;

void sceVif0PkAddCode(sceVif0Packet *pPacket, u_int code);
void sceVif0PkAddData(sceVif0Packet *pPacket, u_int data);

void sceVif0PkRef(sceVif0Packet *pPacket, u_long128 *pRef, u_int size, u_int opt1, u_int opt2, u_int flag);
u_int *sceVif0PkReserve(sceVif0Packet *pPacket, u_int count);

#endif
