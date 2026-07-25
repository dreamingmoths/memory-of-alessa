#include "Fog/spack.h"

#include "Font/fj_man.h"

#include "SH2_common/sh_vu0.h"

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkInit);

void spkResetOT(void) {
    
    shQzero(spack.ot_top, (spack.ot_size + 3) * 4);
    
    spack.old_lastpos = spack.pk_last;
    spack.dmabuf_pos = spack.dma_top;
    spack.pk_last = spack.pos = (u_long128 *)(UNCACHED(spack.packet));
    spack.w_mini = -1;
    spack.w_max = 0;
}

void spkResetOT2(void) {
    
    shQzero(spack.ot_top, (spack.ot_size + 3) * 4);
    
    spack.dmabuf_pos = spack.dma_top;
    spack.w_mini = -1;
    spack.w_max = 0;
}

void spkOpenGiftag(void* giftag, u_int w, u_short envid) {
    u_long* pos = spack.pk_last; // r16    
    SPACK_OT_DATA* pd = spack.dmabuf_pos; // r3    
    u_long d[2]; // r29+0x20

    pd->Addr = (void *)(((u_int)(pos)) & 0x0FFFFFFF); // @todo: add macro
    pd->W = w;
    pd->EnvID = envid;
    pd->VifDirect = 0x50;
    
    memcpy(d, giftag, 0x10);
    spack.pgiftag = pos;
    pos[0] = d[0];
    pos[1] = d[1];
    spack.pos = pos + 2;
    spack.giftag_b = d[0];
}

void spkOpenDGiftag(u_long giftag1 /* r2 */, u_long giftag2 /* r2 */, u_int w /* r2 */, u_short envid /* r2 */) {
    u_long* pos = spack.pk_last; // r8
    SPACK_OT_DATA* pd = spack.dmabuf_pos; // r9

    pd->Addr = (void *)(((u_int)(pos)) & 0x0FFFFFFF); // @todo: add macro
    pd->W = w;
    pd->EnvID = envid;
    pd->VifDirect = 0x50;
    
    spack.pgiftag = pos;
    pos[0] =  giftag1;
    pos[1] =  giftag2;
    spack.pos = pos + 2;
    spack.giftag_b = giftag1;
}

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkCloseGiftag);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkCloseOpenDGiftag);

void spkStartPacketS(u_long128* adr) {
    spack.ps_top = (SPACK_STATIC_DATA*) READ_UNCACHED(adr);
    spack.pos = spack.ps_top;
}

void spkOpenGiftagS(void* giftag) {
    u_long d[2]; // r29+0x20
    u_long* pos = spack.pos; // r16

    spack.pgiftag = pos;
    
    memcpy(&d, giftag, 0x10);
    pos[0] = d[0];
    pos[1] = d[1];
    spack.pos = pos + 2;
    spack.giftag_b = d[0];
}

void spkOpenDGiftagS(u_long giftag1, u_long giftag2) {
    u_long* pos = spack.pos; // r3
        
    spack.pgiftag = pos;
    
    pos[0] = giftag1;
    pos[1] = giftag2;
    spack.pos = pos + 2;
    spack.giftag_b = giftag1;
}

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkCloseGiftagS);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkEndPacketS);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkSetEnvPacket);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkStartEnvLoadImage);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkSetEnvLoadImage);

void spkEndEnvLoadImage(void) {
    u_long* pos = spack.pos; // r4
    
    pos[0] = 0x60000000;
    pos[1] = 0;
    spack.pk_last = pos + 2;
}

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkSetOTPacketS); // matched but not added cause of rodata https://decomp.me/scratch/Rqb53

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkSetOTPacketS_asm);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkSetOT);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkDmaKick);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", ot_link);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", ot_qsort_asm);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", ot_qsort_asm2);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", ot_check);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkDmaWaittoSPR); // matched but not added cause of rodata https://decomp.me/scratch/2oZgu

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkDmaWaitfromSPR);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkDmatoSPR);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkDmafromSPR);

INCLUDE_ASM("asm/nonmatchings/Fog/spack", spkDebugPrint);
