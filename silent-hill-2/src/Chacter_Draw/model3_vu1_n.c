#include "model3_vu1_n.h"

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", Model3LoadMpg1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", InitAllDataOne);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", InitSprData);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", InitData1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeData1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", InitEnv1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", TiniEnv);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeVu1PartTransferPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeLambertShadingPacket);

static void MakeNormalPacket(Part* part, sceVif1Packet* pk) {
    int n_textures = part->n_textures; // r29+0xA0
    unsigned short * text_pos_indices = (u_short*)((u_int)part + part->text_pos_indices_offset); // r29+0xB0
    TextPosParam * text_pos_params = model_common_work->text_pos_params; // r30
    TextureParam * texture_params = (TextureParam*) ((u_int)part + part->texture_params_offset); // r23
    signed int mpg = (u_char)((part->backclip == 0) ? 0x16: 0x18); // r16
    sceDmaChan* fromSPR = sceDmaGetChan(8); // r17
    signed int i = 0; // r18
    for (i = 0; i < n_textures; i++) {
        int text_pos_index = text_pos_indices[i];
        TextPosParam *text_pos = (TextPosParam *)(text_pos_params + text_pos_index);
        TextureParam *texture = (TextureParam*) &texture_params[i];
        NDrawData * spr = &spr_data->ndraw[i % 2];
        NDrawData * data; // r2
        sceVif1PkCnt(pk, 0U);
        sceVif1PkAddCode(pk, 0x11000000U);
        sceVif1PkAddCode(pk, xitop_0x0041BF08 | 0x6C080000);
        data = (NDrawData*)sceVif1PkReserve(pk, 0x20U);

        if (!(((u_int)data & 0x03) == 0)) {
            printf("model3_vu1_n.c:945> assert:(%s)\n\0\0\0", "((u_int)data & 0x03) == 0\0\0");
            do {} while (1);
        }
    
        spr->tex0.s64[0] = text_pos->tex0;
    
        spr->tex1.s64[0] = texture->tex1;
        spr->clamp.s64[0] = texture->clamp;

        fromSPR->sadr = (void* ) ((int) spr & 0x3FFF);
        sceDmaSendN(fromSPR, (void*)((u_int) data & 0xfffffff), 8);

        sceVif1PkAddCode(pk, xitop_0x0041BF08 | 0x04000000);
        sceVif1PkAddCode(pk, mpg | 0x14000000);
    }
}


void MakeEnvironPacket(Part* part, sceVif1Packet* pk) {
    int mpg; // r16
    struct Data * data; // r2

    mpg = (u_char)((part->backclip == 0) ? 0x1a: 0x1c);

    sceVif1PkCnt(pk, 0U);
    sceVif1PkAddCode(pk, 0x11000000U);
    sceVif1PkRef(pk, (u_long128*)(all_data + 0x600), 
                 8U, 0x01000101U, xitop_0x0041BF08 | 0x6c080000, 0);

    sceVif1PkCnt(pk, 0U);
    sceVif1PkAddCode(pk, 0x01000101U);
    sceVif1PkAddCode(pk, (xitop_0x0041BF08 + 8) | 0x6C010000);
    data = (Data*) sceVif1PkReserve(pk, 4U);
    if (!(((u_int)data & 0x03) == 0)) {
        printf("model3_vu1_n.c:986> assert:(%s)\n\0\0\0", "((u_int)data & 0x03) == 0\0\0");
        do {} while (1);
    }

    data->rgba.u32[0] = 128;
    data->rgba.u32[1] = 128;
    data->rgba.u32[2] = 128;
    data->rgba.u32[3] = part->envmap_param;

    sceVif1PkAddCode(pk, xitop_0x0041BF08 | 0x04000000);
    sceVif1PkAddCode(pk, mpg | 0x14000000);
}


INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeSpecularPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeBaseSpecularPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeOverPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeDrawPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", DrawPart1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", DrawParts1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", Model3DrawVu1Parts);
