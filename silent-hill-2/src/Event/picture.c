#include "sce/libgraph.h"
#include "Fog/spack.h"
#include "Event/picture.h"

INCLUDE_ASM("asm/nonmatchings/Event/picture", PictureDraw);

#define MAX_IMAGE_RESOLUTION (512 * 512)
#define DEFAULT_CLUT_ADDRESS 0x3640
#pragma divbyzerocheck off
#line 193
void PictureLoadImage(sh2gfw_AREA_HEAD* ap, int otp, int tex_adr, int clut_adr) {
    sh2gfw_TEX_HEAD* tp;
    sh2gfw_CLUTS_HEAD* cp;
    int tpws;
    int load_img_all;
    int i;
    int load_img;

    tp = (sh2gfw_TEX_HEAD*) ((u_char*) ap + ap->toGlobalTexHead);
    cp = (sh2gfw_CLUTS_HEAD*) ((u_char*) ap + ap->toGlobalClutsHead);
    tpws = tp->w >> tp->bitshift;
    load_img_all = tp->datasize >> 2;
    if (tex_adr == -1) tex_adr = sh2gfw_Get_BaseTBP0for2D();
    if (clut_adr == -1) clut_adr = DEFAULT_CLUT_ADDRESS;
    
    spkStartEnvLoadImage(otp + 16 /* envid */);
    for (i = 0; load_img_all != 0; i++) {
        if (0x10000 < load_img_all) load_img = 0x10000;
        else load_img = load_img_all;
        load_img_all -= load_img;
        spkSetEnvLoadImage(
            (u_char*) tp + tp->padbyte + i * MAX_IMAGE_RESOLUTION + sizeof(sh2gfw_TEX_HEAD),
            tex_adr + i * 1024, tpws >> 6, tp->sendpsm, 0, 0, tpws, load_img / tpws
        );
    }
    if (tp->drawpsm != 0)
        spkSetEnvLoadImage(
            (u_char*) cp + cp->toRawClut + sizeof(sh2gfw_CLUTS_HEAD),
            clut_adr, cp->clw >> 6, 0, 0, 0, cp->clw, cp->clh
        );

    spkEndEnvLoadImage();    

    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, 0, 1), SCE_GIF_PACKED_AD, (((0x100 - otp) & 0xFFFF) - 0x8000) - 0x8000, (otp + 0x10) & 0xFFFF);
    
    (*spack.pos++) = 0; (*spack.pos++) = 0x3F;
    spkCloseGiftag();
}

