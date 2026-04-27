#ifndef HH_PACKET_H
#define HH_PACKET_H

#include "common.h"
#include "eestruct.h"

u_int HH_Vif1PacketBuffer_Memory_Allocate_Check(void);

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
