#ifndef HH_PACKET_H
#define HH_PACKET_H

#include "common.h"
#include "eestruct.h"

struct sceVif1Packet* HH_Vif1Packet_Current_Get(void);
void HH_Vif1PacketBuffer_GifTag_Open(void);
void HH_Vif1PacketBuffer_GifTag_Close(void);
void HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open(void);

#endif
