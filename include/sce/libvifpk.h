
#ifndef LIB_VIF_PK_H
#define LIB_VIF_PK_H

#include "sce/eetypes.h"
#include "sce/eestruct.h"

#define SCE_VIF_NOP			(0x00U)
#define SCE_VIF_STCYCL		(0x01U)
#define SCE_VIF_OFFSET		(0x02U)
#define SCE_VIF_BASE		(0x03U)
#define SCE_VIF_ITOP		(0x04U)
#define SCE_VIF_STMOD		(0x05U)
#define SCE_VIF_MSKPATH3	(0x06U)
#define SCE_VIF_MARK		(0x07U)
#define SCE_VIF_FLUSHE		(0x10U)
#define SCE_VIF_FLUSH		(0x11U)
#define SCE_VIF_FLUSHA		(0x13U)
#define SCE_VIF_MSCAL		(0x14U)
#define SCE_VIF_MSCALF		(0x15U)
#define SCE_VIF_MSCNT		(0x17U)
#define SCE_VIF_STMASK		(0x20U)
#define SCE_VIF_STROW		(0x30U)
#define SCE_VIF_STCOL		(0x31U)
#define SCE_VIF_MPG			(0x4aU)
#define SCE_VIF_DIRECT		(0x50U)
#define SCE_VIF_DIRECTHL	(0x51U)
#define SCE_VIF_UNPACK		(0x60U)

#define SCE_VIF_UPK_S_32	(0x0U)
#define SCE_VIF_UPK_S_16	(0x1U)
#define SCE_VIF_UPK_S_8		(0x2U)
#define SCE_VIF_UPK_V2_32	(0x4U)
#define SCE_VIF_UPK_V2_16	(0x5U)
#define SCE_VIF_UPK_V2_8	(0x6U)
#define SCE_VIF_UPK_V3_32	(0x8U)
#define SCE_VIF_UPK_V3_16	(0x9U)
#define SCE_VIF_UPK_V3_8	(0xaU)
#define SCE_VIF_UPK_V4_32	(0xcU)
#define SCE_VIF_UPK_V4_16	(0xdU)
#define SCE_VIF_UPK_V4_8	(0xeU)
#define SCE_VIF_UPK_V4_5	(0xfU)

typedef struct
{
    u_int* pCurrent;
    u_long128* pBase;
    u_long128* pDmaTag;
    u_int* pVifCode;

    u_int numlen;
    u_int pad11;
    u_int pad12;
    u_int pad13;
} sceVif0Packet;

typedef struct
{
    u_int* pCurrent;
    u_long128* pBase;
    u_long128* pDmaTag;
    u_int* pVifCode;

    u_int numlen;
    u_long* pGifTag;
    u_int pad12;
    u_int pad13;
} sceVif1Packet;

void sceVif0PkAddCode(sceVif0Packet* pPacket, u_int code);
void sceVif0PkAddData(sceVif0Packet* pPacket, u_int data);

void sceVif0PkRef(sceVif0Packet* pPacket, u_long128* pRef, u_int size, u_int opt1, u_int opt2, u_int flag);
u_int* sceVif0PkReserve(sceVif0Packet* pPacket, u_int count);

void sceVif0PkInit(sceVif0Packet* pPacket, u_long128* pBase);
void sceVif0PkReset(sceVif0Packet* pPacket);
void sceVif0PkNext(sceVif0Packet* pPacket, u_long128* pNext, u_int flag);
void sceVif0PkCall(sceVif0Packet* pPacket, u_long128* pCall, u_int flag);
void sceVif0PkEnd(sceVif0Packet* pPacket, u_int flag);
void sceVif0PkCnt(sceVif0Packet* pPacket, u_int flag);
void sceVif0PkRefMpg(sceVif0Packet* pPacket, u_short vuaddr, u_long128* pMicro, u_int size, u_int opt1);
u_long128* sceVif0PkTerminate(sceVif0Packet* pPacket);

void sceVif1PkInit(sceVif1Packet* pPacket, u_long128* pBase);
void sceVif1PkReset(sceVif1Packet* pPacket);
void sceVif1PkCnt(sceVif1Packet* pPacket, u_int flag);
void sceVif1PkOpenDirectCode(sceVif1Packet* pPacket, int stall);
void sceVif1PkCloseDirectCode(sceVif1Packet* pPacket);
void sceVif1PkEnd(sceVif1Packet* pPacket, u_int flag);
u_long128* sceVif1PkTerminate(sceVif1Packet* pPacket);
u_int* sceVif1PkReserve(sceVif1Packet* pPacket, u_int count);

#endif
