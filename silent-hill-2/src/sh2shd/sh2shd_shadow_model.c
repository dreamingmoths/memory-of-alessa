#include "sh2_common.h"
#include "GFW/sh2_GsAllEnv.h"
#include "sh2shd/sh2shd_structs.h"
#include "Heap/utilheap.h"
#include "sh2shd/sh2shd_shadow_model.h"
#include "sh2shd/sh2shd_char_jms.h"
#include "Event/demoview.h"
#include "Chacter/m3_sc.h"
#include "SH2_common/map_ids.h"
#include "vec.h"

static void sh2shd_renew_shadow_man(CAMERA_DAT* cam, int glb_coord, int map_id);
static void make_chara_reftag_pool_and_kick_packet_for_spot(void);
static void make_bg_reftag_pool_and_kick_packet_for_spot(float spot_cam_angle);
static void make_chara_reftag_pool_and_kick_packet_for_point(void);
static void make_chara_reftag_pool_and_kick_packet_for_self(void);
static void make_chara_reftag_pool_and_kick_packet_for_parallel(void);
static void make_bg_reftag_pool_and_kick_packet_for_parallel(void);
static float get_spot_camera_angle(float* cam_pos, float* light_pos, float* light_dir, float* light_param);

extern u_int Shadow_micro_code[];
extern u_int Shadow_micro_code_parallel[];
extern sceVu0FVECTOR light_dir_for_jms; // size: 0x10, address: 0x1125310
extern sceVu0FVECTOR light_pos_for_jms; // size: 0x10, address: 0x1125320
extern sceVu0FVECTOR light_param_for_jms; // size: 0x10, address: 0x1125300

void sh2shd_init_shadow(void) {
    int i;

    
    shadow_man.change_flag = 0;
    shadow_man.spot_char_num = 0;
    shadow_man.spot_bg_num = 0;
    shadow_man.self_num = 0;
    shadow_man.parallel_char_num = 0;
    shadow_man.parallel_bg_num = 0;
    shadow_man.point_char_num = 0;
    shadow_man.char_man_num = 0;
    shadow_man.outdoor_man_num = 0;
    
    shadow_man.enemy_num = 0;
    
    
    shadow_man.chr_shadow_switch = 1;
    shadow_man.bg_shadow_switch = 1;

    for (i = 0; i < SHADOW_CHAR_MAN_SIZE; i++)
        shadow_man.char_man[i] = NULL;

    for (i = 0; i < SHADOW_OUTDOOR_MAN_SIZE; i++)
        shadow_man.outdoor_man[i] = NULL;

    shadow_calcheap = utilHeapInit(&Shadow_Calcwork[1], 0x19000U);
    ASSERT_ON_LINE(shadow_calcheap, 129);


    
    
    sh2shd_init_packet_buf(&shadow_man.kick_packet, Shadow_Kick_Packet);



    
    sh2shd_init_packet_buf(&shadow_man.reftag_pool, Shadow_REFtag_Packet);
    
    

    for (i = 0; i < SHADOW_OFF_WORK_CHAR_SIZE; i++) {
        int j;
    
        shadow_off_work_char[i].kind = 0;
        shadow_off_work_char[i].id = -1;
        for (j = 0; j < SHADOW_OFF_WORK_CHAR_OBJ_COUNT; j++)
            shadow_off_work_char[i].obj_id[j] = -1;
    }

    
    for (i = 0; i < SHADOW_OFF_WORK_BG_SIZE; i++) {
        int j;

        
        shadow_off_work_bg[i].map_id = -1;
        for (j = 0; j < SHADOW_OFF_WORK_BG_OBJ_COUNT; j++)
            shadow_off_work_bg[i].obj_id[j] = -1;
    }
 
    
    shadow_micro_init(&shadow_micro_frame[0], &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame[1], &shGs_AllEnv);
    shadow_micro_init(shadow_micro_frame_parallel, &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame_point, &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame_parallel[1], &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame_parallel[2], &shGs_AllEnv);
    
    jms_added_flag = 0;
}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_reset_shadow);

int sh2shd_add_char(SubCharacter* scp, Q_WORDDATA* raw_data, short light_kind, float* light_pos, float* light_dir, float* light_param) { 
    Q_WORDDATA* cur; // r2
    SHADOW_CHAR_HEAD char_head; // r29+0x90
    int i; // r16
    int demo_no = DramaDemoNumber(); // r16
    int glb_coord; // r29+0xD8…
    int map_id; // r29+0xDC
    sceVu0FVECTOR chr_pos; // r29+0xA0
    sceVu0FVECTOR cam_pos; // r29+0xB0
    sceVu0FVECTOR light_vec; // r29+0xC0

    get_map_id(&glb_coord, &map_id);
    if (demo_no == DRAMA_DEMO_4E) {
        if (scp->kind == LAU_CHARA_ID) {
            light_kind = 4;
            light_dir[0] = -0.00404023f;
            light_dir[1] = 0.6262416f;
            light_dir[2] = 0.7796187f;
            light_dir[3] = 0.0f;
        }
    } else if ((glb_coord == 9) && map_id == MAP_ID_0x1E && scp->kind == EN_MKN_CHARA_ID && light_kind == LIGHT_KIND_5) {
        return 1;
    }

    if ((light_kind == LIGHT_KIND_9) && ((glb_coord != 9) || (map_id != MAP_ID_0x48))) {
        return 1;
    }

    if (IS_PLAYER_KIND(scp->kind)) {
        if (demo_no != 0) {
            sh2shd_get_demo_jms_shadow_env(&jms_shadow_env, demo_no);
        } else {
            sh2shd_get_jms_shadow_env(&jms_shadow_env, light_kind, light_dir);
        }
        if (jms_shadow_env.light_kind == LIGHT_KIND_NONE) {
            jms_shadow_env.light_kind = light_kind;
        }
        if ((jms_shadow_env.light_kind == LIGHT_KIND_5) && (demo_no == 0)) {
            vwGetViewPosition(cam_pos);
            cam_pos[1] = 0;
            vec_copy_reverse(&scp->pos, chr_pos);
            chr_pos[1] = 0;
            vec_sub_reverse(chr_pos, cam_pos, cam_pos);
            vec_normalize(cam_pos, cam_pos);
            vec_copy_reverse(light_pos, light_vec);
            light_vec[1] = 0;
            vec_sub_reverse(chr_pos, light_vec, light_vec);
            vec_normalize(light_vec, light_vec);
            if (vec3_dot_product(cam_pos, light_vec) < -0.707f) {
                vwGetViewPosition(cam_pos);
                vec_sub_reverse(cam_pos, &scp->pos, cam_pos);
                if (sqrtf(vec3_dot_product(cam_pos, cam_pos)) < 1800.0f) {
                    sh2shd_del_jms_upper_body(scp->kind, scp->id);
                }
            }
        }
        if (jms_shadow_env.light_kind == LIGHT_KIND_9) {
            return 1;
        }
        jms_added_flag = 1;
    } else if ((scp->kind >= 0x800) && (scp->kind < 0x809)) {
        if (jms_added_flag == 0) {
            return 1;
        }
        light_kind = jms_shadow_env.light_kind;
    } else if (IS_ENEMY_KIND(scp->kind) && (GET_BIT(scp->battle.status, 1) || GET_BIT(scp->battle.status, 2))) {
        return 1;
    }
    if (shadow_man.char_man_num >= SHADOW_CHAR_MAN_SIZE) return 0;
    
    cur = &char_head;
    hword_struct_copy(cur->ss16, raw_data->ss16);
    for (i = 0; i <= SHADOW_CHAR_MAN_SIZE; i++) {
        if (shadow_man.char_man[i] == NULL) break;
    }
    if (i == SHADOW_CHAR_MAN_SIZE) {
        return 0;
    }
    shadow_man.char_man[i] = utilHeapMalloc(shadow_calcheap, SHADOW_CALC_HEAP_SIZE);
    if (shadow_man.char_man[i] == 0)
       ASSERT_ON_LINE(shadow_man.char_man[i] != 0, 386);

    shadow_man.char_man[i]->shape = utilHeapMalloc(shadow_calcheap, char_head.obj_num * 0x70);
    ASSERT_ON_LINE(shadow_man.char_man[i]->shape != 0, 400);
    shadow_man.char_man_num++;

    if (IS_PLAYER_KIND(scp->kind) && (jms_shadow_env.light_kind >= 0)) {
        sh2shd_init_char_man(shadow_man.char_man[i], scp, raw_data, scp->kind, scp->id, jms_shadow_env. light_kind, light_pos, light_dir, light_param);
        light_kind = jms_shadow_env.light_kind;
        vec_copy_reverse(light_pos, light_pos_for_jms);
        vec_copy_reverse(light_dir, light_dir_for_jms);
        vec_copy_reverse(light_param, light_param_for_jms);
    } else {
        if ((scp->kind >= 0x800) && (scp->kind < 0x809)) {
            sh2shd_init_char_man(shadow_man.char_man[i], scp, raw_data, scp->kind, scp->id, light_kind, light_pos_for_jms, light_dir_for_jms, light_param_for_jms);
        } else {
            sh2shd_init_char_man(shadow_man.char_man[i], scp, raw_data, scp->kind, scp->id, light_kind, light_pos, light_dir, light_param);
        }
    }
    switch (light_kind) {
        case LIGHT_KIND_0:
            shadow_man.spot_char_num++;
            break;
        case LIGHT_KIND_6:
            shadow_man.spot_char_num++;
            break;
        case LIGHT_KIND_7:
            shadow_man.spot_char_num++;
            break;
        case LIGHT_KIND_8:
            shadow_man.spot_char_num++;
            break;
        case LIGHT_KIND_1:
            shadow_man.self_num++;
            break;
        case LIGHT_KIND_2:
            shadow_man.self_num++;
            break;
        case LIGHT_KIND_3:
            shadow_man.self_num++;
            break;
        case LIGHT_KIND_4:
            shadow_man.parallel_char_num++;
            break;
        case LIGHT_KIND_5:
            shadow_man.point_char_num++;
            break;
    }

    if (IS_ENEMY_KIND(scp->kind)) {
        shadow_man.enemy_num++;
    }
    shadow_man.change_flag = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_Draw_ShadowChar);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_map);

Q_WORDDATA* sh2shd_exe_shadow(CAMERA_DAT* cam) {
    int i; // r4
    sceVu0FVECTOR cam_pos; // r29+0x40
    float spot_cam_angle_bg; // r20
    int map_id; // r29+0x58
    int glb_coord; // r29+0x5C
    int demo_no; // r16
    int count; // r2

    demo_no = DramaDemoNumber();

















    
    if (shadow_man.change_flag == 0)
        return NULL;

    
    if (shadow_man.chr_shadow_switch == 0) {
    
        if (shadow_man.bg_shadow_switch == 0)
            return NULL;
        if (shadow_man.outdoor_man_num == 0)
            return NULL;
        
        shadow_man.spot_char_num = 0;
        shadow_man.self_num = 0;
        shadow_man.parallel_char_num = 0;
        shadow_man.point_char_num = 0;
    }
    else if (shadow_man.bg_shadow_switch == 0) {
        
        if (shadow_man.chr_shadow_switch == 0)
            return NULL;
        if (shadow_man.char_man_num == 0)
            return NULL;

        shadow_man.spot_bg_num = 0;
        shadow_man.parallel_bg_num = 0;
    }

    
    get_map_id(&glb_coord, &map_id);
    
    
    
    if (demo_no != 0)
        sh2shd_demo_shadow_off(demo_no);
    else
        sh2shd_shadow_off(glb_coord, map_id);
    
    
    
    
    
    
    
    
    
    
    
    vwGetViewPosition(&cam_pos);
    
    
    
    
    if (shadow_man.change_flag == 1) {
    
        
        sh2shd_reset_packet_buf(&shadow_man.reftag_pool);
        sh2shd_reset_packet_buf(&shadow_man.kick_packet);
        
        
        if (shadow_man.spot_char_num > 0) {
        
            
            shadow_micro_init(shadow_micro_frame, &shGs_AllEnv);
            shadow_add_micro2kick_packet(shadow_micro_frame, &shadow_man.kick_packet, &Shadow_micro_code);
        
            
            
            make_chara_reftag_pool_and_kick_packet_for_spot();
        }
        
        
        if (shadow_man.spot_bg_num > 0) {
        
            
            
            for (i = 0; i < 4; i++) {
                if (shadow_man.outdoor_man[i] != NULL) break;
            }
            
            
            
            spot_cam_angle_bg = get_spot_camera_angle(cam_pos, shadow_man.outdoor_man[i]->light_pos, shadow_man.outdoor_man[i]->light_dir, shadow_man.outdoor_man[i]->light_param);
            
            
            
            
            
            shadow_micro_init(&shadow_micro_frame[1], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame[1], &shadow_man.kick_packet, Shadow_micro_code);
            





            
            make_bg_reftag_pool_and_kick_packet_for_spot(spot_cam_angle_bg);
        }
        
        
        
        
        
        if (shadow_man.self_num > 0) {
        
            shadow_micro_init(&shadow_micro_frame_parallel[0], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_parallel[0], &shadow_man.kick_packet, Shadow_micro_code_parallel);
            
            
            make_chara_reftag_pool_and_kick_packet_for_self();
        }
        
        
        
        
        if (shadow_man.point_char_num > 0) {
        
            
            shadow_micro_init(&shadow_micro_frame_point, &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_point, &shadow_man.kick_packet, Shadow_micro_code);
            
            
            
            make_chara_reftag_pool_and_kick_packet_for_point();
        }
        
        
        
        
        
        
        if (shadow_man.parallel_char_num > 0) {
        
            
            shadow_micro_init(&shadow_micro_frame_parallel[1], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_parallel[1], &shadow_man.kick_packet, Shadow_micro_code_parallel);
            
            
            
            make_chara_reftag_pool_and_kick_packet_for_parallel();
        }
        
        
        
        if (shadow_man.parallel_bg_num > 0) {
        
            
            shadow_micro_init(&shadow_micro_frame_parallel[2], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_parallel[2], &shadow_man.kick_packet, Shadow_micro_code_parallel);
            
            
            make_bg_reftag_pool_and_kick_packet_for_parallel();
        }
        
        
        shadow_man.change_flag = 0;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    sh2shd_renew_shadow_man(cam, glb_coord, map_id);
    
    return shadow_man.kick_packet.head;
}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_renew_shadow_man);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_bg_reftag_pool_and_kick_packet_for_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_point);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_self);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_parallel);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_bg_reftag_pool_and_kick_packet_for_parallel);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", get_spot_camera_angle);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", get_distance_from_light_to_chara);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_exe_drop_shadow);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_renew_drop_shadow_man);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_make_stencil_drop_shadow_plane);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_make_drop_shadow_plane);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_reset_shadow_off_work);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_map_to_shadow_off_work);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_off_obj);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_char_to_shadow_off_work);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_off_char_obj);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_off_char_all_parts);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_bg_shadow_off);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", check_self_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", check_self_para);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_del_jms_upper_body);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_del_jms_head);

const char rodata_1230_0x00390CB0[] = "sh2shd_shadow_model.c:495> assert:(%s)\n";

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @1231_0x00390CD8);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @1276_0x00390CE0);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @1277_0x00390D10);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @1278_0x00390D30);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @1279_0x00390D60);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @2077_0x00390D90);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @2078);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @2079);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @2080);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @883);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @884);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_shadow_model", @926);
