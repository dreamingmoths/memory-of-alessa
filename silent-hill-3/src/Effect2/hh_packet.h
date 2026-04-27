#ifndef HH_PACKET_H
#define HH_PACKET_H

#include "common.h"
#include "eestruct.h"
#include "libvifpk.h"

sceVif1Packet* HH_Vif1Packet_Current_Get(void);
void HH_Vif1PacketBuffer_GifTag_Open(void);
void HH_Vif1PacketBuffer_GifTag_Close(void);
void HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open(void);
void HH_Vif1Packet_GeneralGifTag_Sprite_Open(void);
void HH_Vif1Packet_GeneralGifTag_GS_AD_Open(void);

#endif
