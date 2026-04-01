#include "model3_vu1_n.h"

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", Model3LoadMpg1);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D6910);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D6B10);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D6CB0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D6D90);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7120);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7220);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D72C0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7530);

static void MakeNormalPacket(Part* part, sceVif1Packet* pk) {
    int n_textures = part->n_textures; // r29+0xA0
    unsigned short * text_pos_indices = (u_short*)((u_int)part + part->text_pos_indices_offset); // r29+0xB0
    TextPosParam * text_pos_params = model_common_work->text_pos_params; // r30
    TextureParam * texture_params = (TextureParam*) ((u_int)part + part->texture_params_offset); // r23
    signed int mpg = ((part->backclip == 0) ? 0x16: 0x18); // r16
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
        sceVif1PkAddCode(pk, D_01EE8088 | 0x6C080000); // xitop
        data = (NDrawData*)sceVif1PkReserve(pk, 0x20U);
    
        spr->tex0.s64[0] = text_pos->tex0;
    
        spr->tex1.s64[0] = texture->tex1;
        spr->clamp.s64[0] = texture->clamp;

        fromSPR->sadr = (void* ) ((int) spr & 0x3FFF);
        sceDmaSendN(fromSPR, (void*)((u_int) data & 0xfffffff), 8);

        sceVif1PkAddCode(pk, D_01EE8088 | 0x04000000); // xitop
        sceVif1PkAddCode(pk, mpg | 0x14000000);
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7A00);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7AA0);

void func_001D7B40(Part* part, sceVif1Packet* pk) {
    int mpg = (part->backclip == 0) ? 0x2e : 0x30;

    sceVif1PkCnt(pk, 0U);
    sceVif1PkAddCode(pk, 0x11000000U);
    sceVif1PkRef(pk, (u_long128*)(all_data + 0x730), 
                 10, 0x01000101U, D_01EE8088 | 0x6c0a0000, 0);

    sceVif1PkCnt(pk, 0U);

    sceVif1PkAddCode(pk, D_01EE8088 | 0x04000000);
    sceVif1PkAddCode(pk, mpg | 0x14000000);
}

void MakeSpecularPacket(Part* part, sceVif1Packet* pk) {
    int mpg; // r16
    struct Data * data; // r2

    mpg = (part->backclip == 0) ? 0x1e : 0x20;

    sceVif1PkCnt(pk, 0U);
    sceVif1PkAddCode(pk, 0x11000000U);
    sceVif1PkRef(pk, (u_long128*)(all_data + 0x580), 
                 9, 0x01000101U, D_01EE8088 | 0x6c090000, 0);

    sceVif1PkCnt(pk, 0U);
    sceVif1PkAddCode(pk, 0x01000101U);
    sceVif1PkAddCode(pk, (D_01EE8088 + 9) | 0x6C010000);
    data = (Data*) sceVif1PkReserve(pk, 4U);

#ifdef DEBUG
    if (!(((u_int)data & 0x03) == 0)) {
        printf("model3_vu1_n.c:945> assert:(%s)\n", "((u_int)data & 0x03) == 0");
        do {} while (1);
    }
#endif

    sceVu0CopyVector(data->rgba.fv, part->specular);
    data->rgba.fv[3] = 128.0f;
    
    sceVif1PkAddCode(pk, D_01EE8088 | 0x04000000);
    sceVif1PkAddCode(pk, mpg | 0x14000000);
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7D20);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7DE0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7EA0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D7F60);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D8270);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D8490);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D8570);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D8610);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D8900);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", func_001D8B00);
