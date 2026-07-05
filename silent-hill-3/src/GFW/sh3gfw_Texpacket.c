#include "common.h"
#include "GFW/sh3gfw_Texpacket.h"

static int Fake_SetTexSlot(int sid, void* pk);
extern /* static */ Q_WORDDATA fake_kick;

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B5030);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_set_TexToTrasMan);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_get_newMANID);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_del_TexMAN);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B56F0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_init_SyncTexTag);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B5AC0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B5AD0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B5AE0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B5AF0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_Get_RegTEX0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B5B80);

#ifdef NON_MATCHING
int sh2gfw_Thr_d2TextureSend(void* ptm, int mode, int* cid, int* slotid) {
    sh2gfw_TexMAN* pTM = ptm; // r16
    int slot = sh2gfw_EnQue_TexSlot(pTM); // r17
    volatile int comid_; // r2
    int comid;

    sh3gfw_SetSlot2Tex(pTM, slot, mode);
    d2tscBeginToUseSlot(slot);

    _comid = d2tscSend(slot, (int) pTM, &pTM->DMACNT);
    comid = _comid;

    *cid = comid;
    *slotid = slot;

    pTM->commandid = comid;
    pTM->slotid = slot;

    return comid;
}
#else
INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_Thr_d2TextureSend);
#endif

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_Thr_d1d2SyncKick);

static int Fake_SetTexSlot(int sid, void* pk) {
    volatile int ret; // @todo `volatile` required for match?
    d2tscBeginToUseSlot(sid);
    ret = d2tscSend(sid, (u_int) pk + sid, pk);
    return ret;
}

void sh3gfw_Lock_AllTexSlot_For_Shadow(void) {
    int i;
    for (i = 1; i < 5; i++) {
        fake_cid[i] = Fake_SetTexSlot(i, &fake_kick);
    }
}

void sh3gfw_UnLock_AllTexSlot_For_Shadow(void) {
    int i;
    for (i = 1; i < 5; i++) {
        sh3gfw_Thr_d1d2SyncKick(&fake_kick, fake_cid[i], i);
    }
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_EnQue_TexSlot);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", sh3gfw_SetSlot2Tex);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B6070);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B60B0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B60F0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B6240);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_Texpacket", func_001B6310);