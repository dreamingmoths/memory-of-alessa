#include "sh2_common.h"
#include "sce/libvifpk.h"
#include "vec.h"
#include "sdk.h"
#include "candles.h"
#include "sh2shd/sh2shd_structs.h"

#define SHD_REFTAG_POOL_SIZE 6400
#define SHD_KICK_PACKET_SIZE 640
#define SHD_OFF_WORK_BG_NUM  4
#define REF_ADDR(x)          ((u_int) (x) & 0x7fffffff)

extern SHADOW_OFF_WORK_BG shadow_off_work_bg[SHD_OFF_WORK_BG_NUM]; // size: 0x108, address: 0x1125340

CANDLE(sh2shd_init_outdoor_man2, CANDLE_TYPE_GPR, *);

#line 86
void sh2shd_init_outdoor_man2(SHADOW_OUTDOOR_MAN* man, Q_WORDDATA* raw_data, int unknown, short light_kind, sceVu0FVECTOR light_pos, float* light_dir, float* light_param) {
    SHADOW_OUTDOOR_HEAD outdoor_head; // r29+0x80
    SHADOW_OUTDOOR_OBJ_HEAD obj_head; // r29+0x90
    SHADOW_GEOM_HEAD geom_head;       // r29+0xA0
    short obj_id    = -1;             // r16
    Q_WORDDATA* raw = raw_data;       // r17

    man->raw_data = raw_data;

    outdoor_head = *(SHADOW_OUTDOOR_HEAD*) raw;
    man->kind    = outdoor_head.kind;
    man->map_id  = outdoor_head.map_id;
    man->obj_num = outdoor_head.obj_num;

    raw++;

    while (outdoor_head.obj_num != 0) {

        obj_head = *(SHADOW_OUTDOOR_OBJ_HEAD*) raw;
        raw++;
        obj_id++;

        raw += 5;

        geom_head = *(SHADOW_GEOM_HEAD*) raw;
        if (geom_head.prim == 3 ||
            geom_head.prim == 4 || geom_head.prim == 10) {
            sceVu0CopyMatrix(
                man->shape[obj_id].local_world,
                raw - 4);

            raw += geom_head.ee_memory_size;
        } else {

            sceVu0CopyMatrix(man->shape[obj_id].local_world, raw - 4);

            raw += geom_head.ee_memory_size;
            obj_head.geom_num--;
            while (obj_head.geom_num != 0) {

                geom_head = *(SHADOW_GEOM_HEAD*) raw;
                raw += geom_head.ee_memory_size;
                obj_head.geom_num--;
            }
        }
        outdoor_head.obj_num--;
    }
    man->light_kind = light_kind;
    shVectorCopy(man->light_pos, light_pos);
    shVectorCopy(man->light_dir, light_dir);
    shVectorCopy(man->light_param, light_param);

    man->light_param[1] = sqrt(1.0f - SQUARE(man->light_param[0]));
    man->light_param[2] = 5000.0f;
}

#line 159
void sh2shd_make_reftag_pool_outdoor(SHADOW_OUTDOOR_MAN* man, SHADOW_PACKET_BUF* ref_packet, float spot_cam_angle) {
    SHADOW_OUTDOOR_HEAD outdoor_head; // r29+0x10
    SHADOW_OUTDOOR_OBJ_HEAD obj_head; // r29+0x20
    SHADOW_GEOM_HEAD geom_head;       // r29+0x30
    Q_WORDDATA* ref = ref_packet->curr;
    Q_WORDDATA* raw = man->raw_data;

    outdoor_head = *(SHADOW_OUTDOOR_HEAD*) raw;
    raw++;

    man->map_id = outdoor_head.map_id;

    while (outdoor_head.obj_num != 0) {
        obj_head                             = *(SHADOW_OUTDOOR_OBJ_HEAD*) raw;
        man->shape[obj_head.obj_id].pRawData = raw->ui32;

        man->shape[obj_head.obj_id].pRefPacket = ref->ui32;

        #define REFTAG(i, count, address, wl, cl, vuaddr, num, cmd) \
            ref[i].ui32[0] = DMAref | (count);                      \
            ref[i].ui32[1] = (u_int) (address);                     \
            ref[i].ui32[2] = SCE_VIF1_SET_STCYCL(wl, cl, 0);        \
            ref[i].ui32[3] = SCE_VIF1_SET_UNPACK(vuaddr, num, cmd, 0);
        #define CNT(i, vifcode1, vifcode2) \
            ref[i].ui32[0] = DMAcnt | 0;   \
            ref[i].ui32[1] = 0;            \
            ref[i].ui32[2] = vifcode1;     \
            ref[i].ui32[3] = vifcode2;
        ref[0].ui32[0] = DMAref | 4;
        ref[0].ui32[1] = REF_ADDR(raw + 1);
        ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
        ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0, 8, SCE_VIF_UPK_V4_16, 0);

        raw += 6;

        REFTAG(1, 6, REF_ADDR(&man->shape[obj_head.obj_id]), 1, 1, 6, 6, SCE_VIF_UPK_V4_32);

        CNT(2, SCE_VIF1_SET_MSCAL(0, 0), SCE_VIF1_SET_FLUSH(0));
        ref += 3;

        while (obj_head.geom_num != 0) {

            geom_head = *(SHADOW_GEOM_HEAD*) raw;

            #line 253
            if (geom_head.prim == 1 || geom_head.prim == 2) {

                #line 258
                REFTAG(0, 2, raw, 1, 1, 0x8000, 4, SCE_VIF_UPK_V4_16);

                REFTAG(1, geom_head.ee_memory_size - 2, raw + 2, 1, 2, 0x8005, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16);
                ref += 2;

            } else if (geom_head.prim == 5 || geom_head.prim == 6) {

                REFTAG(0, 1, raw, 1, 1, 0x8000, 2, SCE_VIF_UPK_V4_16);

                ref[1].ui32[0] = DMAref | 1;
                ref[1].ui32[1] = (u_int) (raw + 1);
                ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16, 0);
                ref[2].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                ref[2].ui32[1] = (u_int) (raw + 2);
                ref[2].ui32[2] = SCE_VIF1_SET_STCYCL(2, 3, 0);
                ref[2].ui32[3] = SCE_VIF1_SET_UNPACK(0x8006, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                ref += 3;
            } else if (geom_head.prim == 3 || geom_head.prim == 4) {
                ref[0].ui32[0] = DMAref | 1;
                ref[0].ui32[1] = (u_int) raw;
                ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
                ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16, 0);
                ref[1].ui32[0] = DMAref | 1;
                ref[1].ui32[1] = (u_int) (raw + 1);
                ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(2, 3, 0);
                ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16, 0);
                ref[2].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                ref[2].ui32[1] = (u_int) (raw + 2);
                ref[2].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                ref[2].ui32[3] = SCE_VIF1_SET_UNPACK(0x8005, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                ref += 3;
            }
            if (spot_cam_angle < 0.0f) {
                if (geom_head.prim == 7) {
                    ref[0].ui32[0] = DMAref | 2;
                    ref[0].ui32[1] = (u_int) raw;
                    ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
                    ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0x8000, 4, SCE_VIF_UPK_V4_16, 0);
                    ref[1].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                    ref[1].ui32[1] = (u_int) (raw + 2);
                    ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                    ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8005, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                    ref += 2;
                } else if (geom_head.prim == 8 || geom_head.prim == 9) {
                    ref[0].ui32[0] = DMAref | 1;
                    ref[0].ui32[1] = (u_int) raw;
                    ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
                    ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16, 0);
                    ref[1].ui32[0] = DMAref | 1;
                    ref[1].ui32[1] = (u_int) (raw + 1);
                    ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                    ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16, 0);
                    ref[2].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                    ref[2].ui32[1] = (u_int) (raw + 2);
                    ref[2].ui32[2] = SCE_VIF1_SET_STCYCL(2, 3, 0);
                    ref[2].ui32[3] = SCE_VIF1_SET_UNPACK(0x8006, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                    ;
                    ref += 3;
                } else if (geom_head.prim == 10) {
                    ref[0].ui32[0] = DMAref | 1;
                    ref[0].ui32[1] = (u_int) raw;
                    ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
                    ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16, 0);
                    ref[1].ui32[0] = DMAref | 1;
                    ref[1].ui32[1] = (u_int) (raw + 1);
                    ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(2, 3, 0);
                    ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16, 0);
                    ref[2].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                    ref[2].ui32[1] = (u_int) (raw + 2);
                    ref[2].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                    ref[2].ui32[3] = SCE_VIF1_SET_UNPACK(0x8005, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                    ref += 3;
                }
            }
            ref->ui32[0] = DMAcnt | 0;
            ref->ui32[1] = 0;
            ref->ui32[2] = 0;
            ref->ui32[3] = SCE_VIF1_SET_MSCNT(0);
            ref++;
            raw += geom_head.ee_memory_size;
            obj_head.geom_num--;
        }
        ref->ui32[0] = DMAret;
        ref->ui32[1] = 0;
        ref->ui32[2] = 0;
        ref->ui32[3] = 0;
        ref++;
        outdoor_head.obj_num--;
    }
    ref_packet->curr = ref;
    ASSERT_ON_LINE(ref_packet->curr - ref_packet->head < SHD_REFTAG_POOL_SIZE, 371);
}

#line 381
void sh2shd_make_reftag_pool_outdoor_for_parallel(SHADOW_OUTDOOR_MAN* man, SHADOW_PACKET_BUF* ref_packet) {
    SHADOW_OUTDOOR_HEAD outdoor_head; // r29+0x10
    SHADOW_OUTDOOR_OBJ_HEAD obj_head; // r29+0x20
    SHADOW_GEOM_HEAD geom_head;       // r29+0x30
    Q_WORDDATA* ref = ref_packet->curr;
    Q_WORDDATA* raw = man->raw_data;

    #line 396
    outdoor_head = *(SHADOW_OUTDOOR_HEAD*) raw;
    raw++;

    man->map_id = outdoor_head.map_id;

    while (outdoor_head.obj_num != 0) {
        obj_head                             = *(SHADOW_OUTDOOR_OBJ_HEAD*) raw;
        man->shape[obj_head.obj_id].pRawData = raw->ui32;

        man->shape[obj_head.obj_id].pRefPacket = ref->ui32;

        #define REFTAG(i, count, address, wl, cl, vuaddr, num, cmd) \
            ref[i].ui32[0] = DMAref | (count);                      \
            ref[i].ui32[1] = (u_int) (address);                     \
            ref[i].ui32[2] = SCE_VIF1_SET_STCYCL(wl, cl, 0);        \
            ref[i].ui32[3] = SCE_VIF1_SET_UNPACK(vuaddr, num, cmd, 0);
        #define CNT(i, vifcode1, vifcode2) \
            ref[i].ui32[0] = DMAcnt | 0;   \
            ref[i].ui32[1] = 0;            \
            ref[i].ui32[2] = vifcode1;     \
            ref[i].ui32[3] = vifcode2;
        ref[0].ui32[0] = DMAref | 4;
        ref[0].ui32[1] = REF_ADDR(raw + 1);
        ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
        ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0, 8, SCE_VIF_UPK_V4_16, 0);

        raw += 6;

        REFTAG(1, 6, REF_ADDR(&man->shape[obj_head.obj_id]), 1, 1, 6, 6, SCE_VIF_UPK_V4_32);

        CNT(2, SCE_VIF1_SET_MSCAL(0, 0), SCE_VIF1_SET_FLUSH(0));
        ref += 3;

        while (obj_head.geom_num != 0) {

            geom_head = *(SHADOW_GEOM_HEAD*) raw;

            #line 534
            if (geom_head.prim == 1 || geom_head.prim == 2) {

                REFTAG(0, 2, raw, 1, 1, 0x8000, 4, SCE_VIF_UPK_V4_16);

                REFTAG(1, geom_head.ee_memory_size - 2, raw + 2, 1, 2, 0x8005, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16);

                CNT(2, 0, SCE_VIF1_SET_MSCNT(0));
                ref += 3;
            }
            if (geom_head.prim == 5 || geom_head.prim == 6) {

                REFTAG(0, 1, raw, 1, 1, 0x8000, 2, SCE_VIF_UPK_V4_16);

                ref[1].ui32[0] = DMAref | 1;
                ref[1].ui32[1] = (u_int) (raw + 1);
                ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16, 0);
                ref[2].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                ref[2].ui32[1] = (u_int) (raw + 2);
                ref[2].ui32[2] = SCE_VIF1_SET_STCYCL(2, 3, 0);
                ref[2].ui32[3] = SCE_VIF1_SET_UNPACK(0x8006, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                CNT(3, 0, SCE_VIF1_SET_MSCNT(0));
                ref += 4;
            } else if (geom_head.prim == 3 || geom_head.prim == 4) {
                ref[0].ui32[0] = DMAref | 1;
                ref[0].ui32[1] = (u_int) raw;
                ref[0].ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
                ref[0].ui32[3] = SCE_VIF1_SET_UNPACK(0x8000, 2, SCE_VIF_UPK_V4_16, 0);
                ref[1].ui32[0] = DMAref | 1;
                ref[1].ui32[1] = (u_int) (raw + 1);
                ref[1].ui32[2] = SCE_VIF1_SET_STCYCL(2, 3, 0);
                ref[1].ui32[3] = SCE_VIF1_SET_UNPACK(0x8002, 2, SCE_VIF_UPK_V4_16, 0);
                ref[2].ui32[0] = DMAref | (geom_head.ee_memory_size - 2);
                ref[2].ui32[1] = (u_int) (raw + 2);
                ref[2].ui32[2] = SCE_VIF1_SET_STCYCL(1, 2, 0);
                ref[2].ui32[3] = SCE_VIF1_SET_UNPACK(0x8005, geom_head.send_data_num - 3, SCE_VIF_UPK_V4_16, 0);
                ref[3].ui32[0] = DMAcnt | 0;
                ref[3].ui32[1] = 0;
                ref[3].ui32[2] = 0;
                ref[3].ui32[3] = SCE_VIF1_SET_MSCNT(0);
                ref += 4;
            }
            raw += geom_head.ee_memory_size;
            obj_head.geom_num--;
        }
        ref->ui32[0] = DMAret;
        ref->ui32[1] = 0;
        ref->ui32[2] = 0;
        ref->ui32[3] = 0;
        ref++;
        outdoor_head.obj_num--;
    }
    ref_packet->curr = ref;
    ASSERT_ON_LINE(ref_packet->curr - ref_packet->head < SHD_REFTAG_POOL_SIZE, 626);
}

#line 1127
void sh2shd_add_outdoor_to_kick_packet(SHADOW_OUTDOOR_MAN* man, SHADOW_PACKET_BUF* kick_packet) {
    int i;                   // r3
    Q_WORDDATA *top, *curr;  // r6, r7
    u_int* reftag_pool_addr; // r10
    int count_call_tag_num;  // r8
    int j;                   // r9

    curr = kick_packet->curr;

    count_call_tag_num = 0;

    curr->ui32[0] = DMAref | 3;
    curr->ui32[1] = REF_ADDR(man->light_pos);
    curr->ui32[2] = SCE_VIF1_SET_STCYCL(1, 1, 0);
    curr->ui32[3] = SCE_VIF1_SET_UNPACK(12, 3, SCE_VIF_UPK_V4_32, 0);
    curr          = curr + 1;

    top = curr;

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

    ASSERT_ON_LINE(kick_packet->curr - kick_packet->head < SHD_KICK_PACKET_SIZE, 1169);

    for (i = 0; i < SHD_OFF_WORK_BG_NUM; i++) {
        if (man->map_id == shadow_off_work_bg[i].map_id) {
            #define OBJ_ID shadow_off_work_bg[i].obj_id[j]
            for (j = 0; j < 32; j++) {
                if (OBJ_ID == -1)
                    break;

                if (OBJ_ID < count_call_tag_num)
                    top[OBJ_ID].ui32[0] = DMAcnt | 0;
                top[OBJ_ID].ui32[1] = 0;
                top[OBJ_ID].ui32[2] = 0;
                top[OBJ_ID].ui32[3] = 0;
            }
        }
    }

    kick_packet->curr = curr;
}

#line 1200
void sh2shd_renew_outdoor_man(SHADOW_OUTDOOR_MAN* man, float* spot_pos, SHADOW_ENV* shadow_env) {
    int i;                            // r16
    sceVu0FMATRIX world_local;        // r29+0x50
    SHADOW_GEOM_HEAD geom_head;       // r29+0x90
    sceVu0FVECTOR light_pos_revision; // r29+0xA0

    for (i = 0; i < man->obj_num; i++) {

        geom_head = *(SHADOW_GEOM_HEAD*) (man->shape[i].pRawData + 24);

        sceVu0InversMatrix(world_local, man->shape[i].local_world);
        sceVu0ApplyMatrix(man->shape[i].local_light_position, world_local, spot_pos);

        if (geom_head.prim == 3) {
            if (shadow_env->leng < 8000.0f)
                man->shape[i].length.fl32[0] = 8000.0f;
            else
                man->shape[i].length.fl32[0] = shadow_env->leng;
        } else if (geom_head.prim == 4) {
            if (shadow_env->leng < 10000.0f)
                man->shape[i].length.fl32[0] = 10000.0f;
            else
                man->shape[i].length.fl32[0] = shadow_env->leng;
        } else {
            man->shape[i].length.fl32[0] = shadow_env->leng;
        }
        man->shape[i].length.ui32[1] = shadow_env->clip_kind;
    }

    shVectorCopy(light_pos_revision, man->light_dir);
    light_pos_revision[1] = 0.0f;
    shNormalizeVector(light_pos_revision, light_pos_revision);
    shScaleVector(light_pos_revision, light_pos_revision, 300.0f);
    shSubVector(light_pos_revision, man->light_pos, light_pos_revision);
    shVectorCopy(man->light_pos, light_pos_revision);
}

#line 1253
void sh2shd_renew_outdoor_man_for_parallel(SHADOW_OUTDOOR_MAN* man, float* spot_pos, SHADOW_ENV* shadow_env) {
    int i;                      // r16
    sceVu0FMATRIX world_local;  // r29+0x50
    SHADOW_GEOM_HEAD geom_head; // r29+0x90

    for (i = 0; i < man->obj_num; i++) {

        geom_head = *(SHADOW_GEOM_HEAD*) (man->shape[i].pRawData + 24);

        sceVu0InversMatrix(world_local, man->shape[i].local_world);
        sceVu0ApplyMatrix(man->shape[i].local_light_position, world_local, spot_pos);

        if (geom_head.prim == 3) {
            if (shadow_env->leng < 8000.0f)
                man->shape[i].length.fl32[0] = 8000.0f;
            else
                man->shape[i].length.fl32[0] = shadow_env->leng;
        } else if (geom_head.prim == 4) {
            if (shadow_env->leng < 10000.0f)
                man->shape[i].length.fl32[0] = 10000.0f;
            else
                man->shape[i].length.fl32[0] = shadow_env->leng;
        } else {
            man->shape[i].length.fl32[0] = shadow_env->leng;
        }
        man->shape[i].length.ui32[1] = shadow_env->clip_kind;
    }
}
