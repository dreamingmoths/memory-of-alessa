#ifndef EF_PACKET_H
#define EF_PACKET_H

#include "common.h"
#include "libvifpk.h"

sceVif1Packet* shEfctPkInit(void* packet /* r2 */);
sceVif1Packet* shEfctPkReset(void);
sceVif1Packet* shEfctPkTaskHead(void);
sceVif1Packet* shEfctPkTaskTail(void);
void* shEfctPkGetKickAddrByd1cSend(void);

extern sceVif1Packet efctVif1Packet;

#endif // EF_PACKET_H
