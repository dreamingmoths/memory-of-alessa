#include "Effect/ef_packet.h"

sceVif1Packet* shEfctPkInit(void* packet /* r2 */) {
    sceVif1PkInit(&efctVif1Packet, packet);
    return &efctVif1Packet;
}

sceVif1Packet* shEfctPkReset(void) {
    sceVif1PkReset(&efctVif1Packet);
    return &efctVif1Packet;
}

sceVif1Packet* shEfctPkTaskHead(void) {
    sceVif1PkCnt(&efctVif1Packet, 0);
    sceVif1PkOpenDirectCode(&efctVif1Packet, 0);
    return &efctVif1Packet;
}

sceVif1Packet* shEfctPkTaskTail(void) {
    sceVif1PkCloseDirectCode(&efctVif1Packet);
    return &efctVif1Packet;
}

void* shEfctPkGetKickAddrByd1cSend(void) {
    sceVif1PkEnd(&efctVif1Packet, 0);
    sceVif1PkTerminate(&efctVif1Packet);
    return efctVif1Packet.pBase;
}
