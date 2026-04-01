#ifndef LIB_DMA_H
#define LIB_DMA_H

#include "eeregs.h"
#include "eetypes.h"

//
// Channels
//
#ifndef SCE_DMA_VIF0
#define SCE_DMA_VIF0 0
#define SCE_DMA_VIF1 1
#define SCE_DMA_GIF 2
#define SCE_DMA_fromIPU 3
#define SCE_DMA_toIPU 4
#define SCE_DMA_SIF0 5
#define SCE_DMA_SIF1 6
#define SCE_DMA_SIF2 7
#define SCE_DMA_fromSPR 8
#define SCE_DMA_toSPR 9
#endif

//
// DMA Tag
//
typedef struct _sceDmaTag
{
    u_short qwc;             // transfer count
    u_char mark;             // mark
    u_char id;               // tag
    struct _sceDmaTag *next; // next tag
    u_int p[2];              // padding
} sceDmaTag __attribute__((aligned(16)));

//
// DMA Environmen
//
typedef struct
{
    u_char sts;      // stall source
    u_char std;      // stall drain
    u_char mfd;      // MFIFO drain
    u_char rcycle;   // release cycle
    u_short express; // express channel mask
    u_short notify;  // notify channel mask
    u_short sqwc;    // Interleave skip qword count
    u_short tqwc;    // Interleave transfer qword count
    void *rbadr;     // MFIFO Ring buffer address
    u_int rbmsk;     // MFIFO Ring buffer mask
} sceDmaEnv;

//
// Channel Attributes
//
typedef struct
{
    tD_CHCR chcr;
    u_int p0[3]; // channel control
    void *madr;
    u_int p1[3]; // memory address
    u_int qwc;
    u_int p2[3]; // transfer count
    sceDmaTag *tadr;
    u_int p3[3]; // tag address
    void *as0;
    u_int p4[3]; // address stack
    void *as1;
    u_int p5[3]; // address stack
    u_int p6[4]; // pad
    u_int p7[4]; // pad
    void *sadr;
    u_int p8[3]; // spr address
} sceDmaChan;


sceDmaChan *sceDmaGetChan(int id);
void sceDmaSendN(sceDmaChan *d, void *addr, int size);
int sceDmaSync(sceDmaChan *d, int mode, int timeout);

#endif
