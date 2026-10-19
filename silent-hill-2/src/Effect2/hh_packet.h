#ifndef HH_PACKET_H
#define HH_PACKET_H

#include "sh2_common.h"
#include "sce/eestruct.h"
#include "sce/libvifpk.h"

// total size: 0x4
typedef struct Queue_Element {
    // Members
    void* pAddress; // offset 0x0, size 0x4
} Queue_Element;

// total size: 0x30
typedef struct Queue_Object {
    // Members
    u_int enQueue;            // offset 0x0, size 0x4
    u_int deQueue;            // offset 0x4, size 0x4
    u_int Length_Current;     // offset 0x8, size 0x4
    u_int Length_Max;         // offset 0xC, size 0x4
    Queue_Element Element[8]; // offset 0x10, size 0x20
} Queue_Object;

u_int HH_Vif1PacketBuffer_Memory_Allocate_Check(void);
sceVif1Packet* HH_Vif1Packet_Current_Get(void);
void HH_Vif1PacketBuffer_Initialize(void);
void HH_Vif1PacketBuffer_Prefix_GifTag_Open(void);
void HH_Vif1PacketBuffer_Suffix_GifTag_Open(void);
void HH_Vif1PacketBuffer_GifTag_Open(void);
void HH_Vif1PacketBuffer_GifTag_Close(void);
void HH_Vif1Packet_Send(void);
int HH_Vif1Packet_FreePacketSize_Get(void);
void HH_Vif1Packet_GeneralGifTag_GS_AD_Open(void);
void HH_Vif1Packet_GeneralGifTag_Sprite_Open(void);
void HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open(void);
void HH_Vif1Packet_GeneralGifTag_TriangleFan_Open(void);

#endif // HH_PACKET_H
