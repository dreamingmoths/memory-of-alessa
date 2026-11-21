#include "sh2_common.h"

#include "candles.h"
#include "vec.h"
#include "math.h"
#include "gs.h"

#include "sce/libgraph.h"
#include "sce/libvifpk.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#include "sh2shd/sh2shd_structs.h"
#include "sh2shd/sh2shd_macros.h"
#include "sh2shd/sh2shd_char_jms.h"

extern SHADOW_OFF_WORK_CHAR shadow_off_work_char[2];

CANDLE(sh2shd_init_char_man, CANDLE_TYPE_GPR, *);

#line 53
void sh2shd_init_char_man(SHADOW_CHAR_MAN* man, SubCharacter* scp, Q_WORDDATA* raw_data, u_short kind, short id, int light_kind, sceVu0FVECTOR light_pos, sceVu0FVECTOR light_dir, sceVu0FVECTOR light_param) {
    SHADOW_CHAR_HEAD char_head; // r29+0x20
    short obj_id    = -1;       // r2
    Q_WORDDATA* raw = raw_data; // r2

    man->scp      = scp;
    man->raw_data = raw_data;

    char_head    = *(SHADOW_CHAR_HEAD*) raw;
    man->kind    = kind;
    man->id      = id;
    man->obj_num = char_head.obj_num;

    man->light_kind = light_kind;
    shVectorCopy(man->light_pos, light_pos);
    shVectorCopy(man->light_dir, light_dir);
    shVectorCopy(man->light_param, light_param);

    man->light_param[1] = sqrt(1.0f - SQUARE(man->light_param[0]));
    man->light_param[2] = 5000.0f;
    #line 94
}

#line 99
void sh2shd_make_reftag_pool_char(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata) {
    SHADOW_CHAR_HEAD char_head;         // r29+0x10
    SHADOW_CHAR_OBJ_HEAD char_obj_head; // r29+0x20
    SHADOW_GEOM_HEAD geom_head;         // r29+0x30

    Q_WORDDATA* ref = ref_packet->curr; // r3
    Q_WORDDATA* raw = rawdata;          // r2

    short shape_no = -1; // r7

    char_head = *(SHADOW_CHAR_HEAD*) raw;
    raw++;

    while (char_head.obj_num != 0) {
        shape_no++;

        char_obj_head = *(SHADOW_CHAR_OBJ_HEAD*) raw;

        man->shape[shape_no].pRefPacket = ref->ui32;
        man->shape[shape_no].obj_id     = char_obj_head.obj_id;

        // @info these didn't use the macro according to the line numbers of sh2 v0.10 prototype
        ref[0].ui32[0] = DMAref | 1;
        ref[0].ui32[1] = REF_ADDR(raw + 1);
        ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
        ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0, 2, SCE_VIF_UPK_V4_16, 0);

        raw += 6;

        REFTAG(ref[1], 6, REF_ADDR(&man->shape[shape_no]), STCYCL(1, 1), UNPACK(6, 6, SCE_VIF_UPK_V4_32));

        CNT(ref[2], SCE_VIF1_SET_MSCAL(0, 0), SCE_VIF1_SET_FLUSH(0));
        ref += 3;

        while (char_obj_head.geom_num != 0) {
            geom_head = *(SHADOW_GEOM_HEAD*) raw;

            if (geom_head.prim == 5 || geom_head.prim == 6) {

                REFTAG(ref[0], 1, raw, STCYCL(1, 1), UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[1], 1, raw + 1, STCYCL(1, 2), UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[2], geom_head.ee_memory_size - 2, raw + 2, STCYCL(2, 3), UNPACK(0x8006, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16));
                ref += 3;
            }

            #line 188
            CNT(ref[0], 0, SCE_VIF1_SET_MSCNT(0));
            ref++;

            raw += geom_head.ee_memory_size;
            char_obj_head.geom_num--;
        }

        RET(ref);

        char_head.obj_num--;
    }

    ref_packet->curr = ref;
    #line 208
    ASSERT_ON_LINE(ref_packet->curr - ref_packet->head < SHD_REFTAG_POOL_SIZE, 208);
}

#line 213
void sh2shd_make_reftag_pool_char_p_maria(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata) {
    SHADOW_CHAR_HEAD char_head;         // r29+0x10
    SHADOW_CHAR_OBJ_HEAD char_obj_head; // r29+0x20
    SHADOW_GEOM_HEAD geom_head;         // r29+0x30

    Q_WORDDATA* ref = ref_packet->curr; // r7
    Q_WORDDATA* raw = rawdata;          // r2

    short shape_no = -1; // r88

    char_head = *(SHADOW_CHAR_HEAD*) raw;
    raw++;

    while (char_head.obj_num != 0) {
        shape_no++;

        char_obj_head = *(SHADOW_CHAR_OBJ_HEAD*) raw;

        man->shape[shape_no].pRefPacket = ref->ui32;

        switch (char_obj_head.obj_id) {
            case 9:
                char_obj_head.obj_id = 9;
                break;

            case 6:
                char_obj_head.obj_id = 6;
                break;

            case 4:
                char_obj_head.obj_id = 4;
                break;

            case 0:
                char_obj_head.obj_id = 0;
                break;

            case 1:
                char_obj_head.obj_id = 1;
                break;

            case 32:
                char_obj_head.obj_id = 23;
                break;

            case 38:
                char_obj_head.obj_id = 29;
                break;

            case 41:
                char_obj_head.obj_id = 32;
                break;

            case 29:
                char_obj_head.obj_id = 21;
                break;

            case 40:
                char_obj_head.obj_id = 28;
                break;

            case 39:
                char_obj_head.obj_id = 30;
                break;

            case 3:
                char_obj_head.obj_id = 3;
                break;

            case 10:
                char_obj_head.obj_id = 7;
                break;

            case 27:
                char_obj_head.obj_id = 20;
                break;

            case 5:
                char_obj_head.obj_id = 5;
                break;

            case 15:
                char_obj_head.obj_id = 8;
                break;

            case 30:
                char_obj_head.obj_id = 22;
                break;
        }
        man->shape[shape_no].obj_id = char_obj_head.obj_id;

        // @info these didn't use the macro according to the line numbers of sh2 v0.10 prototype
        ref[0].ui32[0] = DMAref | 1;
        ref[0].ui32[1] = REF_ADDR(raw + 1);
        ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
        ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0, 2, SCE_VIF_UPK_V4_16, 0);

        raw += 6;

        REFTAG(ref[1], 6, REF_ADDR(&man->shape[shape_no]), STCYCL(1, 1), UNPACK(6, 6, SCE_VIF_UPK_V4_32));

        CNT(ref[2], SCE_VIF1_SET_MSCAL(0, 0), SCE_VIF1_SET_FLUSH(0));
        ref += 3;

        while (char_obj_head.geom_num != 0) {
            geom_head = *(SHADOW_GEOM_HEAD*) raw;

            if (geom_head.prim == 5 || geom_head.prim == 6) {

                REFTAG(ref[0], 1, raw, STCYCL(1, 1), UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[1], 1, raw + 1, STCYCL(1, 2), UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[2], geom_head.ee_memory_size - 2, raw + 2, STCYCL(2, 3), UNPACK(0x8006, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16));
                ref += 3;
            }

            #line 373
            CNT(ref[0], 0, SCE_VIF1_SET_MSCNT(0));
            ref++;

            raw += geom_head.ee_memory_size;
            char_obj_head.geom_num--;
        }

        RET(ref);

        char_head.obj_num--;
    }

    ref_packet->curr = ref;
    #line 393
    ASSERT_ON_LINE(ref_packet->curr - ref_packet->head < SHD_REFTAG_POOL_SIZE, 393);
}

#line 654
void sh2shd_add_char_to_kick_packet(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* kick_packet) {
    int i;                               // r3
    Q_WORDDATA* curr;                    // r9
    u_int* reftag_pool_addr;             // r10
    int count_call_tag_num;              // r6
    Q_WORDDATA* top = kick_packet->curr; // r2
    int j, k;                            // r10, r11
    count_call_tag_num = 0;

    REFTAG(top[0], 3, REF_ADDR(man->light_pos), STCYCL(1, 1), UNPACK(12, 3, SCE_VIF_UPK_V4_32));
    curr = top + 1;
    top  = curr;

    for (i = 0; i < man->obj_num; i++) {

        reftag_pool_addr        = man->shape[i].pRefPacket;
        man->shape[i].pKickAddr = curr->ui32;

        curr->ui32[0] = DMAcall;
        curr->ui32[1] = (u_int) reftag_pool_addr;
        curr->ui32[2] = 0;
        curr->ui32[3] = SCE_VIF1_SET_FLUSH(0);
        curr++;
        count_call_tag_num++;
    }

    curr->ui32[0] = DMAend;
    curr->ui32[1] = 0;
    curr->ul64[1] = 0;

    kick_packet->curr = curr;
    #line 697
    ASSERT_ON_LINE(kick_packet->curr - kick_packet->head < SHD_KICK_PACKET_SIZE, 697);

    #line 701
    for (i = 0; i < SHADOW_OFF_WORK_CHAR_SIZE; i++) {
        if (man->kind == shadow_off_work_char[i].kind &&
            man->id == shadow_off_work_char[i].id) {
            #define OBJ_ID shadow_off_work_char[i].obj_id[j]

            if (shadow_off_work_char[i].obj_id[0] == 999) {
                for (k = 0; k < count_call_tag_num; k++)
                    top[k].ui32[0] = DMAcnt | 0;
                top[k].ui32[1] = 0;
                top[k].ui32[2] = 0;
                top[k].ui32[3] = 0; // @bug?
            } else {
                for (j = 0; j < SHD_OFF_WORK_CHAR_NUM; j++) {
                    if (OBJ_ID == -1)
                        break;
                    for (k = 0; k < man->obj_num; k++) {
                        if (man->shape[k].obj_id == OBJ_ID)
                            break;
                    }
                    if (k < count_call_tag_num)
                        top[k].ui32[0] = DMAcnt | 0;
                    top[k].ui32[1] = 0;
                    top[k].ui32[2] = 0;
                    top[k].ui32[3] = 0;
                }
            }
        }
    }
}

#line 746
void sh2shd_renew_char_man(SHADOW_CHAR_MAN* man, sceVu0FVECTOR spot_pos, float leng, SHADOW_ENV* shadow_env) {
    int i;                     // r16
    sceVu0FMATRIX world_local; // r29+0x70

    for (i = 0; i < man->obj_num; i++) {
        shCharacterGetPartsMatrixForShadow(man->shape[i].local_world, man->kind, man->id, man->shape[i].obj_id);
        sceVu0InversMatrix(world_local, man->shape[i].local_world);
        sceVu0ApplyMatrix(man->shape[i].local_light_position, world_local, spot_pos);

#line 770
        man->shape[i].length.fl32[0] = leng;
        man->shape[i].length.si32[1] = shadow_env->clip_kind;
    }
}

#line 779
void sh2shd_renew_char_man_for_spot(SHADOW_CHAR_MAN* man, sceVu0FVECTOR spot_pos, float leng /* @note not in dwarf */, SHADOW_ENV* shadow_env) {
    int i;                     // r16
    sceVu0FMATRIX world_local; // r29+0x60

    for (i = 0; i < man->obj_num; i++) {
        shCharacterGetPartsMatrixForShadow(man->shape[i].local_world, man->kind, man->id, man->shape[i].obj_id);
        sceVu0InversMatrix(world_local, man->shape[i].local_world);
        sceVu0ApplyMatrix(man->shape[i].local_light_position, world_local, spot_pos);

        man->shape[i].length.fl32[0] = shadow_env->leng;
        man->shape[i].length.si32[1] = shadow_env->clip_kind;
    }
}

#line 813
void sh2shd_renew_char_man_parallel(SHADOW_CHAR_MAN* man, sceVu0FVECTOR virtual_light_position) {
    int i;                     // r16
    float leng;                // r29+0x90
    sceVu0FMATRIX world_local; // r29+0x50

    for (i = 0; i < man->obj_num; i++) {
        shCharacterGetPartsMatrixForShadow(man->shape[i].local_world, man->kind, man->id, man->shape[i].obj_id);
        sceVu0InversMatrix(world_local, man->shape[i].local_world);
        sceVu0ApplyMatrix(man->shape[i].local_light_position, world_local, virtual_light_position);

        man->shape[i].length.fl32[0] = 10000.0f;
    }
}

#line 859
void sh2shd_calc_light_position_for_self(sceVu0FVECTOR light_pos, u_short kind, short id, JMS_SHADOW_ENV* env, sceVu0FVECTOR chara_pos /* not present in dwarf */, float height) {
    sceVu0FVECTOR tmp;                               // r29+0x50
    sceVu0FVECTOR z_unit = {0.0f, 0.0f, 1.0f, 0.0f}; // r29+0x60
    sceVu0FMATRIX mat;                               // r29+0x70

    float height_revision = env->height_revision; // r21
    float bias            = env->bias;            // r22
    float scale           = env->scale;           // r23
    float sc;                                     // r29+0xB0
    shCharacterGetPartsMatrixForShadow(mat, kind, id, 0);
    mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
    mat[0][1] = mat[1][0] = mat[1][1] = mat[1][2] = mat[2][1] = 0.0f;
    sceVu0ApplyMatrix(z_unit, mat, z_unit);

    shCharacterGetPartsMatrixForShadow(mat, kind, id, 3);

    mat[3][1] -= height;

    shVectorCopy(tmp, z_unit);
    tmp[1] = 0.0f;
    shNormalizeVector(tmp, tmp);

    sc = bias + (654.0f + mat[3][1]) * scale;
    if (sc < 0.0f)
        sc *= -1.0f;
    shScaleVector(tmp, tmp, sc);

    if (height != height_revision)

        tmp[1] = -height_revision;

    else
        tmp[1] = 0.1f;

    tmp[3] = 0.0f;

    shVectorCopy(light_pos, tmp);
}

#line 903
void sh2shd_calc_light_position_for_self_spot(sceVu0FVECTOR light_pos, u_short kind, short id, JMS_SHADOW_ENV* env, sceVu0FVECTOR chara_pos, float height) {
    sceVu0FVECTOR tmp;                               // r29+0x60
    sceVu0FVECTOR z_unit = {0.0f, 0.0f, 1.0f, 0.0f}; // r29+0x70
    sceVu0FMATRIX mat;                               // r29+0x80

    float height_revision = env->height_revision; // r21
    float bias            = env->bias;            // r22
    float scale           = env->scale;           // r23

    shCharacterGetPartsMatrixForShadow(mat, kind, id, 0);
    mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
    mat[0][1] = mat[1][0] = mat[1][1] = mat[1][2] = mat[2][1] = 0.0f;
    sceVu0ApplyMatrix(z_unit, mat, z_unit);

    shCharacterGetPartsMatrixForShadow(mat, kind, id, 3);

    mat[3][1] -= height;

    shVectorCopy(tmp, z_unit);
    tmp[1] = 0.0f;
    shNormalizeVector(tmp, tmp);
    shScaleVector(tmp, tmp, bias + (654.0f + mat[3][1]) * scale);

    tmp[0] += chara_pos[0];
    if (height != height_revision)
        tmp[1] = height - height_revision;

    else
        tmp[1] = 0.1f;
    tmp[2] += chara_pos[2];
    tmp[3] = 1.0f;
    shVectorCopy(light_pos, tmp);
}

static const char zero_str[] = "0";
 #define ASSERT_ZERO_ON_LINE(line)                                   \
    do {                                                            \
        if (!(0)) {                                                 \
            printf(__FILE__ ":" #line "> assert:(%s)\n", zero_str); \
            do {                                                    \
            } while (1);                                            \
        }                                                           \
    } while (0)

#line 1061
void sh2shd_make_reftag_pool_char_for_drop_with_order(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata) {
    SHADOW_CHAR_HEAD char_head;         // r29+0x80
    SHADOW_CHAR_OBJ_HEAD char_obj_head; // r29+0x90
    SHADOW_GEOM_HEAD geom_head;         // r29+0xA0
    Q_WORDDATA* ref = ref_packet->curr; // r19
    Q_WORDDATA* raw = rawdata;          // r20

    short shape_no2 = -1; // r21
    int shape_no;         // r5

    char_head = *(SHADOW_CHAR_HEAD*) raw;
    raw++;

    while (char_head.obj_num != 0) {
        shape_no2++;

        char_obj_head = *(SHADOW_CHAR_OBJ_HEAD*) raw;

        shape_no = sh2shd_get_shape_no(man->kind, char_obj_head.obj_id);
        if (shape_no == -1) {
            shape_no = shape_no2;
        }

        man->shape[shape_no].pRefPacket = ref->ui32;
        man->shape[shape_no].obj_id     = char_obj_head.obj_id;

        // @info these didn't use the macro according to the line numbers of sh2 v0.10 prototype
        ref[0].ui32[0] = DMAref | 1;
        ref[0].ui32[1] = REF_ADDR(raw + 1);
        ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
        ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0, 2, SCE_VIF_UPK_V4_16, 0);

        raw += 6;

        REFTAG(ref[1], 4, REF_ADDR(man->drop_shadow_matrix), STCYCL(1, 1), UNPACK(12, 4, SCE_VIF_UPK_V4_32));

        REFTAG(ref[2], 6, REF_ADDR(&man->shape[shape_no]), STCYCL(1, 1), UNPACK(6, 6, SCE_VIF_UPK_V4_32));

        CNT(ref[3], SCE_VIF1_SET_MSCAL(0, 0), SCE_VIF1_SET_FLUSH(0));
        ref += 4;

        while (char_obj_head.geom_num != 0) {
            geom_head = *(SHADOW_GEOM_HEAD*) raw;

            if (geom_head.prim == 5 || geom_head.prim == 6) {

                REFTAG(ref[0], 1, raw, STCYCL(1, 1), UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[1], 1, raw + 1, STCYCL(1, 1), UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[2], geom_head.ee_memory_size - 2, raw + 2, STCYCL(1, 1), UNPACK(0x8004, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16));
                ref += 3;

            } else {
                do {
                    int a = 0;
                } while (0);
            }

            #line 1160
            CNT(ref[0], 0, SCE_VIF1_SET_MSCNT(0));
            ref++;

            raw += geom_head.ee_memory_size;
            char_obj_head.geom_num--;
        }

        RET(ref);

        char_head.obj_num--;
    }

    ref_packet->curr = ref;
    #line 1180
    ASSERT_ON_LINE(ref_packet->curr - ref_packet->head < SHD_REFTAG_POOL_SIZE, 1180);
}

#line 1189
void sh2shd_make_reftag_pool_char_for_drop_with_order_p_maria(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata) {
    SHADOW_CHAR_HEAD char_head;         // r29+0x80
    SHADOW_CHAR_OBJ_HEAD char_obj_head; // r29+0x90
    SHADOW_GEOM_HEAD geom_head;         // r29+0xA0
    Q_WORDDATA* ref = ref_packet->curr; // r19
    Q_WORDDATA* raw = rawdata;          // r20

    short shape_no2 = -1; // r21
    int shape_no;         // r5

    char_head = *(SHADOW_CHAR_HEAD*) raw;
    raw++;

    while (char_head.obj_num != 0) {
        shape_no2++;

        char_obj_head = *(SHADOW_CHAR_OBJ_HEAD*) raw;

        switch (char_obj_head.obj_id) {
            case 9:
                char_obj_head.obj_id = 9;
                break;

            case 6:
                char_obj_head.obj_id = 6;
                break;

            case 4:
                char_obj_head.obj_id = 4;
                break;

            case 0:
                char_obj_head.obj_id = 0;
                break;

            case 1:
                char_obj_head.obj_id = 1;
                break;

            case 32:
                char_obj_head.obj_id = 23;
                break;

            case 38:
                char_obj_head.obj_id = 29;
                break;

            case 41:
                char_obj_head.obj_id = 32;
                break;

            case 29:
                char_obj_head.obj_id = 21;
                break;

            case 40:
                char_obj_head.obj_id = 28;
                break;

            case 39:
                char_obj_head.obj_id = 30;
                break;

            case 3:
                char_obj_head.obj_id = 3;
                break;

            case 10:
                char_obj_head.obj_id = 7;
                break;

            case 27:
                char_obj_head.obj_id = 20;
                break;

            case 5:
                char_obj_head.obj_id = 5;
                break;

            case 15:
                char_obj_head.obj_id = 8;
                break;

            case 30:
                char_obj_head.obj_id = 22;
                break;
        }

        shape_no = sh2shd_get_shape_no(man->kind, char_obj_head.obj_id);
        if (shape_no == -1) {
            shape_no = shape_no2;
        }

        man->shape[shape_no].pRefPacket = ref->ui32;
        man->shape[shape_no].obj_id     = char_obj_head.obj_id;

        // @info these didn't use the macro according to the line numbers of sh2 v0.10 prototype
        ref[0].ui32[0] = DMAref | 1;
        ref[0].ui32[1] = REF_ADDR(raw + 1);
        ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
        ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0, 2, SCE_VIF_UPK_V4_16, 0);

        raw += 6;

        REFTAG(ref[1], 4, REF_ADDR(man->drop_shadow_matrix), STCYCL(1, 1), UNPACK(12, 4, SCE_VIF_UPK_V4_32));

        REFTAG(ref[2], 6, REF_ADDR(&man->shape[shape_no]), STCYCL(1, 1), UNPACK(6, 6, SCE_VIF_UPK_V4_32));

        CNT(ref[3], SCE_VIF1_SET_MSCAL(0, 0), SCE_VIF1_SET_FLUSH(0));
        ref += 4;

        while (char_obj_head.geom_num != 0) {
            geom_head = *(SHADOW_GEOM_HEAD*) raw;

            if (geom_head.prim == 5 || geom_head.prim == 6) {

                REFTAG(ref[0], 1, raw, STCYCL(1, 1), UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[1], 1, raw + 1, STCYCL(1, 1), UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16));

                REFTAG(ref[2], geom_head.ee_memory_size - 2, raw + 2, STCYCL(1, 1), UNPACK(0x8004, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16));
                ref += 3;

            } else {
            #line 1336
                ASSERT_ZERO_ON_LINE(1336);
            }

            #line 1339
            CNT(ref[0], 0, SCE_VIF1_SET_MSCNT(0));
            ref++;

            raw += geom_head.ee_memory_size;
            char_obj_head.geom_num--;
        }

        RET(ref);

        char_head.obj_num--;
    }

    ref_packet->curr = ref;
    #line 1359
    ASSERT_ON_LINE(ref_packet->curr - ref_packet->head < SHD_REFTAG_POOL_SIZE, 1359);
}

#line 1366
void sh2shd_renew_char_man_for_drop(SHADOW_CHAR_MAN* man, sceVu0FVECTOR spot_pos, float alpha_decay) {
    static float jms_high;     // @ 0x01013B88
    static float jms_low;      // @ 0x01013B80
    int i;                     // r16
    sceVu0FMATRIX world_local; // r29+0x60
    float high;                // r29+0xA8
    float low;                 // r29+0xAC
    float tmp;                 // r29+0xB0

    sh2shd_get_height_for_alpha(&high, &low, man->kind, (u16) man->id);
    tmp = high;
    if (high > low) {
        high = low;
        low  = tmp;
    }
    high = low - 700.0f;

    if (IS_PLAYER_KIND(man->kind)) {
        jms_high = high;
        jms_low  = low;
    }

    if (man->kind >= WEAPON_ID_START && man->kind < WEAPON_ID_END) {
        high = jms_high;
        low  = jms_low;
    }

    for (i = 0; i < man->obj_num; i++) {
        shCharacterGetPartsMatrixForShadow(man->shape[i].local_world, man->kind, man->id, man->shape[i].obj_id);
        sceVu0InversMatrix(world_local, man->shape[i].local_world);
        sceVu0ApplyMatrix(man->shape[i].local_light_position, world_local, spot_pos);

        man->shape[i].length.fl32[0] = high;
        man->shape[i].length.fl32[1] = low;
        man->shape[i].length.fl32[3] = alpha_decay;

        if (DramaDemoNumber() == 3) {
            man->shape[i].length.fl32[0] = low;
        }
    }
}

#line 1432
void sh2shd_get_height_for_alpha(sceVu0FVECTOR high, sceVu0FVECTOR low, u_short kind, u_short id) {
    sceVu0FMATRIX mat; // r29+0x60

    switch (kind) {
        case LLL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
        case HHL_JMS_CHARA_KIND:
        case HHH_JMS_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 8);
            *high = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 30);
            *low = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 29);

            if (*low < mat[3][1]) {
                *low = mat[3][1];
                break;
            }
            break;

        case LLL_MAR_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 9);
            *high = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 22);
            *low = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 20);

            if (*low < mat[3][1]) {
                *low = mat[3][1];
                break;
            }
            break;

        case HHH_MAR_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 9);
            *high = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 30);
            *low = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 27);

            if (*low < mat[3][1]) {
                *low = mat[3][1];
                break;
            }
            break;

        case AGL_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 9);
            *high = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 34);
            *low = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 36);

            if (*low < mat[3][1]) {
                *low = mat[3][1];
                break;
            }
            break;

        case EN_SCU_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 11);
            *high = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 20);
            *low = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 21);
            if (*low < mat[3][1]) {
                *low = mat[3][1];
                break;
            }
            break;

        case EN_MKN_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 9);
            *high = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 11);
            if (*high > mat[3][1]) {
                *high = mat[3][1];
            }
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 13);
            *low = mat[3][1];
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 14);
            if (*low < mat[3][1]) {
                *low = mat[3][1];
                break;
            }
            break;

        case WEAPON_HANDGUN_CHARA_KIND:
        case WEAPON_SHOTGUN_CHARA_KIND:
        case WEAPON_RIFLGUN_CHARA_KIND:
        case WEAPON_SP_CHARA_KIND:
        case WEAPON_KAKUZAI_CHARA_KIND:
        case WEAPON_PIPE_CHARA_KIND:
        case WEAPON_CSAW_CHARA_KIND:
        case WEAPON_NATA_CHARA_KIND:
            shCharacterGetPartsMatrixForShadow(mat, kind, id, 0);
            *high = mat[3][1];
            *low  = mat[3][1];
            break;
    }
}

#line 1543
int sh2shd_get_shape_no(u_short kind, int skel_no) {
    int all_skel_num = skel_no; // r2 ($v0)
    int shape_no;               // r2 ($v0)

    switch (kind) {
        case LLL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
        case HHL_JMS_CHARA_KIND:
        case HHH_JMS_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_jms(all_skel_num); // @hack these don't seem right
            break;

        case LLL_MAR_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_p_mar(all_skel_num);
            break;

        case HHH_MAR_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_mar(all_skel_num);
            break;

        case EN_SCU_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_scu(skel_no);
            break;

        case EN_MKN_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_mkn(skel_no);
            break;

        case EN_LLL_EDI_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_edb(skel_no);
            break;

        case EN_NSE_CHARA_KIND:
        case EN_XOO_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_nse(skel_no);
            break;

        case EN_RED_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_red(skel_no);
            break;

        case EN_ONI_CHARA_KIND:
            all_skel_num = shape_no = sh2shd_get_shape_no_oni(skel_no);
            break;

        default:
            return -1;
    }

    return all_skel_num;
}

int sh2shd_get_shape_no_jms(int skel_no) {
    switch (skel_no) {

        case 26:
            return 0;

        case 25:
            return 1;

        case 14:
            return 2;

        case 13:
            return 3;

        case 5:
            return 4;

        case 4:
            return 5;

        case 1:
            return 6;

        case 3:
            return 7;

        case 28:
            return 8;

        case 27:
            return 9;

        case 34:
            return 10;

        case 33:
            return 11;

        case 35:
            return 12;

        case 40:
            return 13;

        case 8:
            return 14;

        case 15:
            return 15;
    }
}

#line 1812
int sh2shd_get_shape_no_mar(int skel_no) {
    switch (skel_no) {
        case 30:
            return 0;
        case 27:
            return 1;
        case 15:
            return 2;
        case 10:
            return 3;
        case 5:
            return 4;
        case 3:
            return 5;
        case 1:
            return 6;
        case 0:
            return 7;
        case 4:
            return 8;
        case 32:
            return 9;
        case 29:
            return 10;
        case 38:
            return 11;
        case 40:
            return 12;
        case 41:
            return 13;
        case 39:
            return 14;
        case 6:
            return 15;
        case 9:
            return 16;
        default:
            ASSERT_ZERO_ON_LINE(1929);
    }
}

#line 2020
int sh2shd_get_shape_no_p_mar(int skel_no) {
    switch (skel_no) {
        case 22:
            return 0;
        case 20:
            return 1;
        case 8:
            return 2;
        case 7:
            return 3;
        case 5:
            return 4;
        case 3:
            return 5;
        case 1:
            return 6;
        case 0:
            return 7;
        case 4:
            return 8;
        case 23:
            return 9;
        case 21:
            return 10;
        case 29:
            return 11;
        case 28:
            return 12;
        case 32:
            return 13;
        case 30:
            return 14;
        case 6:
            return 15;
        case 9:
            return 16;
        default:
            ASSERT_ZERO_ON_LINE(2076);
    }
}

#line 2147
int sh2shd_get_shape_no_scu(int skel_no) {
    switch (skel_no) {
        case 0:
            return 8;
        case 2:
            return 11;
        case 6:
            return 6;
        case 7:
            return 7;
        case 8:
            return 14;
        case 9:
            return 4;
        case 10:
            return 5;
        case 11:
            return 15;
        case 12:
            return 2;
        case 13:
            return 3;
        case 20:
            return 0;
        case 21:
            return 1;
        case 22:
            return 12;
        case 23:
            return 13;
        case 24:
            return 9;
        case 25:
            return 10;
    }
}

int sh2shd_get_shape_no_mkn(int skel_no) {
    switch (skel_no) {

        case 0:
            return 6;

        case 1:
            return 7;

        case 2:
            return 8;

        case 4:
            return 4;

        case 3:
            return 5;

        case 5:
            return 10;

        case 7:
            return 9;

        case 9:
            return 12;

        case 10:
            return 3;

        case 11:
            return 11;

        case 12:
            return 2;

        case 13:
            return 1;

        case 14:
            return 0;
    }
}

int sh2shd_get_shape_no_nse(int skel_no) {
    switch (skel_no) {

        case 13:
            return 0;

        case 12:
            return 1;

        case 8:
            return 2;

        case 6:
            return 3;

        case 5:
            return 4;

        case 4:
            return 5;

        case 1:
            return 6;

        case 0:
            return 7;

        case 2:
            return 8;

        case 24:
            return 9;

        case 23:
            return 10;

        case 20:
            return 11;

        case 19:
            return 12;

        case 16:
            return 13;

        case 15:
            return 14;

        case 7:
            return 15;

        case 9:
            return 16;
    }
}

int sh2shd_get_shape_no_red(int skel_no) {
    switch (skel_no) {

        case 12:
            return 0;

        case 13:
            return 1;

        case 7:
            return 2;

        case 6:
            return 3;

        case 4:
            return 4;

        case 3:
            return 5;

        case 0:
            return 6;

        case 2:
            return 7;

        case 36:
            return 8;

        case 29:
            return 9;

        case 28:
            return 10;

        case 23:
            return 11;

        case 21:
            return 12;

        case 16:
            return 13;

        case 15:
            return 14;

        case 14:
            return 15;
    }
}

int sh2shd_get_shape_no_oni(int skel_no) {
    switch (skel_no) {

        case 12:
            return 0;

        case 13:
            return 1;

        case 7:
            return 2;

        case 6:
            return 3;

        case 4:
            return 4;

        case 3:
            return 5;

        case 0:
            return 6;

        case 2:
            return 7;

        case 36:
            return 8;

        case 25:
            return 9;

        case 24:
            return 10;

        case 21:
            return 11;

        case 20:
            return 12;

        case 16:
            return 13;

        case 15:
            return 14;

        case 5:
            return 15;

        case 14:
            return 16;
    }
}

int sh2shd_get_shape_no_edb(int skel_no) {
    switch (skel_no) {

        case 15:
            return 0;

        case 14:
            return 1;

        case 4:
            return 2;

        case 3:
            return 3;

        case 0:
            return 4;

        case 5:
            return 5;

        case 22:
            return 6;

        case 17:
            return 7;

        case 28:
            return 8;

        case 27:
            return 9;

        case 31:
            return 10;

        case 30:
            return 11;

        case 6:
            return 12;

        case 13:
            return 13;
    }
}
