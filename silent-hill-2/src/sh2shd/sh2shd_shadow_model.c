#include "sh2_common.h"
#include "sce/libvu0.h"
#include "vec.h"
#include "GFW/sh2_GsAllEnv.h"
#include "sh2shd/sh2shd_structs.h"
#include "Heap/utilheap.h"
#include "sh2shd/sh2shd_shadow_model.h"
#include "sh2shd/sh2shd_char_jms.h"
#include "sh2shd/sh2shd_shadow_env.h"
#include "Event/demoview.h"
#include "Chacter/m3_sc.h"
#include "Chacter_Draw/light_n.h"
#include "SH2_common/map_ids.h"
#include "view/camera_dat.h"

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
        for (j = 0; j < SHD_OFF_WORK_CHAR_NUM; j++)
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
        if (scp->kind == LAU_CHARA_KIND) {
            light_kind = 4;
            light_dir[0] = -0.00404023f;
            light_dir[1] = 0.6262416f;
            light_dir[2] = 0.7796187f;
            light_dir[3] = 0.0f;
        }
    } else if ((glb_coord == 9) && map_id == MAP_ID_0x1E && scp->kind == EN_MKN_CHARA_KIND && light_kind == LIGHT_KIND_5) {
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
        if (jms_shadow_env.light_kind == LIGHT_KIND_UNSET) {
            jms_shadow_env.light_kind = light_kind;
        }
        if ((jms_shadow_env.light_kind == LIGHT_KIND_5) && (demo_no == 0)) {
            vwGetViewPosition(cam_pos);
            cam_pos[1] = 0;
            vec_copy_reverse(&scp->pos, chr_pos);
            chr_pos[1] = 0;
            vec_sub_reverse(chr_pos, cam_pos, cam_pos);
            shNormalizeVector(cam_pos, cam_pos);
            vec_copy_reverse(light_pos, light_vec);
            light_vec[1] = 0;
            vec_sub_reverse(chr_pos, light_vec, light_vec);
            shNormalizeVector(light_vec, light_vec);
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
        case LIGHT_KIND_NONE:
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
        case LIGHT_KIND_PARALLEL:
            shadow_man.self_num++;
            break;
        case LIGHT_KIND_POINT:
            shadow_man.self_num++;
            break;
        case LIGHT_KIND_3:
            shadow_man.self_num++;
            break;
        case LIGHT_KIND_REFLECTION:
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

#ifdef NON_MATCHING
void sh2shd_renew_shadow_man(CAMERA_DAT* cam, int glb_coord, int map_id) {
    int  i; // r16
    sceVu0FVECTOR virtual_spot_c_back; // r29+0x90
    sceVu0FMATRIX drop_shadow_matrix; // r29+0xA0
    sceVu0FVECTOR spot_cam_vector; // r29+0xE0
    sceVu0FVECTOR cam_pos; // r29+0xF0
    SHADOW_ENV shadow_env; // r29+0x228
    int demo_no; // r17
    float dis; // r29+0x240
    sceVu0FVECTOR inverse_vector; // r29+0x100
    float length_chara; // r20

    
    
    
    
    
    demo_no = DramaDemoNumber();
    
    vwGetViewPosition(&cam_pos);
    
    
    if (shadow_man.spot_char_num > 0) {
        int i;
        
        

        
        shadow_set_micro_params(&shadow_micro_frame, cam, &drop_shadow_matrix, 0);
        
        
        if (shadow_man.char_man_num > 0) {
            for (i = 0; i < 16; i++) {
                if ((shadow_man.char_man[i] != NULL)) {
                    if (((shadow_man.char_man[i]->light_kind == 0) || 
                         (shadow_man.char_man[i]->light_kind == 6) || 
                         (shadow_man.char_man[i]->light_kind == 7) || 
                         (shadow_man.char_man[i]->light_kind == 8))) {
                        float spot_cam_angle;
                        sceVu0FVECTOR virtual_spot_pos; // r29+0x110
                        sceVu0FVECTOR chara_pos; // r29+0x120
                        sceVu0FVECTOR normal; // r29+0x130
                        float height; // r29+0x230


                        
                        spot_cam_angle = get_spot_camera_angle(&cam_pos, &shadow_man.char_man[i]->light_pos, &shadow_man.char_man[i]->light_dir, &shadow_man.char_man[i]->light_param);
                        
                        
                        
                        
                        shSubVector(&spot_cam_vector, &shadow_man.char_man[i]->light_pos, &cam_pos); 
                        spot_cam_vector[3] = vec3_length(&spot_cam_vector);
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        shVectorCopy(&virtual_spot_pos, &shadow_man.char_man[i]->light_pos);
                        
                        
                        
                        
                        
                        if (spot_cam_angle > 0.0f) {
                            virtual_spot_pos[1] = shadow_man.char_man[i]->light_pos[1] - (400.0f * spot_cam_angle);
                        }
                        
                        
                        
                        if ((demo_no == 0) && 
                            (((shadow_man.char_man[i]->kind < LLL_JMS_CHARA_KIND) || (HHH_JMS_CHARA_KIND < shadow_man.char_man[i]->kind)) && 
                            ((shadow_man.char_man[i]->kind < WEAPON_ID_NONE) || (WEAPON_NATA_CHARA_KIND < shadow_man.char_man[i]->kind)))) {
                                    get_distance_from_light_to_chara(shadow_man.char_man[i], &inverse_vector);
                            
                                    shAddVector(&virtual_spot_pos, &virtual_spot_pos, &inverse_vector);
                            }
                        
                        
                        if (demo_no == 0) {
                        
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            sh2shd_get_shadow_env_chr(&shadow_env, shadow_man.char_man[i], glb_coord, map_id);
                            
                            
                            
                            
                            
                            if (spot_cam_angle > 0.5f)
                                if (shadow_env.leng > 1.5f * spot_cam_vector[3])
                                    shadow_env.leng = 1.5f * spot_cam_vector[3];
                        } else {

                            
                            sh2shd_get_demo_shadow_env_for_char(&shadow_env, shadow_man.char_man[i], demo_no);
                        }



                        if ((shadow_man.char_man[i]->light_kind >= 6) && (shadow_man.char_man[i]->light_kind < 9)) {

                            
                            shCharacterGetGroundInfoForShadow(&chara_pos, &normal, &height, shadow_man.char_man[i]->kind, shadow_man.char_man[i]->id);
                            
                            
                            sh2shd_calc_light_position_for_self_spot(&virtual_spot_pos, shadow_man.char_man[i]->kind, shadow_man.char_man[i]->id, &jms_shadow_env, &chara_pos, height);
                            
                            
                            
                            if (demo_no == 0xA) {
                            
                                virtual_spot_pos[0] = -58387.0f;
                                virtual_spot_pos[1] = -1500.0f;
                                virtual_spot_pos[2] = 19326.0f;
                            }
                            
                            
                            
                            
                            
                            
                            shadow_env.clip_kind = 0x3E7;
                            shadow_env.leng = 6000.0f;
                        }
                        
                        sh2shd_renew_char_man_for_spot(shadow_man.char_man[i], &virtual_spot_pos, length_chara, &shadow_env);
                    }
                }
            }
        }
    }
    
    if (shadow_man.spot_bg_num > 0) {
        int spot_cam_flag; // r21
        
        
        int count = 0;
        
        
        for (i = 0; i < 4; i++) {
        
            if (shadow_man.outdoor_man[i] != NULL) {
                float spot_cam_angle;
                

                count++;
                spot_cam_angle = get_spot_camera_angle(&cam_pos, &shadow_man.outdoor_man[i]->light_pos, &shadow_man.outdoor_man[i]->light_dir, &shadow_man.outdoor_man[i]->light_param);
                
                
                
                
                if (spot_cam_angle > 0.0f) 
                    spot_cam_flag = 1;
                else 
                    spot_cam_flag = 0;

                shVectorCopy(&virtual_spot_c_back, shadow_man.outdoor_man[i]->light_pos);
                
                
                
                if (demo_no == 0)
                    sh2shd_get_shadow_env_bg(&shadow_env, shadow_man.outdoor_man[i]->raw_data);
                else
                    
                    sh2shd_get_demo_shadow_env_for_bg(&shadow_env, demo_no);
                
                
                
                
                
                
                
                
                
                shadow_set_micro_params(&shadow_micro_frame + 1, cam, &drop_shadow_matrix, spot_cam_flag);
                
                if (shadow_man.outdoor_man[i]->light_kind == 0)
                    sh2shd_renew_outdoor_man(shadow_man.outdoor_man[i], &virtual_spot_c_back, &shadow_env);
                
            }
        }
    }



    
    if (shadow_man.point_char_num > 0) {
        float light_leng; // r29+0x240
        sceVu0FVECTOR vec; // r29+0x140
        sceVu0FVECTOR chara_pos; // r29+0x150













        shadow_set_micro_params(&shadow_micro_frame_point, cam, drop_shadow_matrix, 0 /* spot cam flag? */);
        
        
        if (shadow_man.char_man_num > 0) {
            for (i = 0; i < 16; i++) {   
                if ((shadow_man.char_man[i] != NULL))
                    if (shadow_man.char_man[i]->light_kind == 5) {
                        
                        if (demo_no != 0)
                            sh2shd_get_demo_shadow_env_for_char(&shadow_env, shadow_man.char_man[i], demo_no);
                        else {
                            
                            
                            
                            shadow_env.clip_kind = 0x3E7;
                            
                            
                            sh2shd_get_shadow_env_chr(&shadow_env, shadow_man.char_man[i], glb_coord, map_id);
                            
                            
                            
                            shadow_env.leng = shadow_man.char_man[i]->light_param[2];





                            
                            chara_pos[0] = shadow_man.char_man[i]->scp->pos.x;
                            chara_pos[1] = shadow_man.char_man[i]->scp->pos.y;
                            chara_pos[2] = shadow_man.char_man[i]->scp->pos.z;
                            chara_pos[3] = 1.0f;
                            shSubVector(&vec, &chara_pos, shadow_man.char_man[i]->light_pos);
                            light_leng = vec3_dot_product(&vec, &vec);
                            light_leng = 0.3f * sqrtf(light_leng);
                            
                            shadow_man.char_man[i]->light_pos[1] -= light_leng;
                            
                                shadow_env.leng *= 1.2f;
                        }
                        
                        sh2shd_renew_char_man(shadow_man.char_man[i], shadow_man.char_man[i]->light_pos, shadow_env.leng, &shadow_env);
                    }
            }
        }
    }

    
    if (shadow_man.self_num > 0) {
        sceVu0FVECTOR chara_pos; // r29+0x160
        sceVu0FVECTOR normal; // r29+0x170
        sceVu0FVECTOR plane; // r29+0x180
        sceVu0FVECTOR virtual_light_position; // r29+0x190
        sceVu0FVECTOR tmp_light_position; // r29+0x1A0
        float height; // r29+0x234
        int  weapon_flag; // r2
        int  count; // r18
        
        for (i = 0; i < 16; i++) {
            
            if ((shadow_man.char_man[i] != NULL))
                
                if ((shadow_man.char_man[i]->kind >= 0x100) && (shadow_man.char_man[i]->kind < 0x104) && (check_self_para((u16) shadow_man.char_man[i]->light_kind) != 0)) {

                
                    shCharacterGetGroundInfoForShadow(&chara_pos, &normal, &height, shadow_man.char_man[i]->kind, shadow_man.char_man[i]->id);
                    
                    
                    chara_pos[1] = 100.0f + height;
                    
                    normal[0] = 0.0f;
                    normal[1] = -1.0f;
                    normal[2] = 0;
                    sh2shd_make_stencil_drop_shadow_plane(plane, chara_pos, normal);
                    
                    sh2shd_calc_light_position_for_self(virtual_light_position, shadow_man.char_man[i]->kind, shadow_man.char_man[i]->id, &jms_shadow_env, &chara_pos, height);
                    
                    
                    
                    shVectorCopy(&tmp_light_position, &virtual_light_position);
                    if (tmp_light_position[1] > 0.0f)
                        tmp_light_position[1] *= -1.0f;
                    sceVu0DropShadowMatrix(drop_shadow_matrix, tmp_light_position, plane[0], plane[1], plane[2], 0);
                    
                    
                    
                    shadow_set_micro_params(&shadow_micro_frame_parallel, cam, &drop_shadow_matrix, 0);
                    
                    
                    
                    shAddVector(&virtual_light_position, &virtual_light_position, &chara_pos);
                    
                    
                    sh2shd_renew_char_man_parallel(shadow_man.char_man[i], virtual_light_position);
                    
                    break;
                }
        
        }
        
        for (i = 0; i < 16; i++) {
        
            if (shadow_man.char_man[i] != NULL)
                
                if ((shadow_man.char_man[i]->kind >= 0x800) && (shadow_man.char_man[i]->kind < 0x809)) {
                
                    if ((shadow_man.char_man[i]->light_kind == 1) || (shadow_man.char_man[i]->light_kind == 3)) {
                    
                        
                        
                        sh2shd_renew_char_man_parallel(shadow_man.char_man[i], &virtual_light_position);
                    }
                    break;
                }

        }
    }

    
    
    
    if (shadow_man.parallel_char_num > 0) {
        sceVu0FVECTOR light_pos; // r29+0x1B0
        int count = 0; // r17
        sceVu0FVECTOR dir; // r29+0x1C0
        sceVu0FMATRIX mat; // r29+0x1D0
        int glb_coord; // r29+0x238
        int map_id; // r29+0x23C

        
        for (i = 0; i < 16; i++) {
        
            if (shadow_man.char_man[i] != NULL) {
            
                if (count == 0) {
                    
                    
                    
                    get_map_id(&glb_coord, &map_id);
                    
                    count++;
                    shVectorCopy(&dir, &shadow_man.char_man[i]->light_dir);
                    shScaleVector(&dir, &dir, -1.0f);
                    if (demo_no == 77)
                        sceVu0DropShadowMatrix(drop_shadow_matrix, dir, 0.0f, 0.10f, 0.0f, 0.0f); 
                    else {
                        sceVu0DropShadowMatrix(drop_shadow_matrix, dir, 0.0f, 100.0f, 0.0f, 0.0f);
                    }
                    
                    shCharacterGetPartsMatrixForShadow(mat, shadow_man.char_man[i]->kind, shadow_man.char_man[i]->id, 0U);
                    
                    
                    vec_scale(10000.0f, &dir, &light_pos);
                    vec_add(&light_pos, &mat[3], &light_pos);
                    
                    
                    shadow_set_micro_params(&shadow_micro_frame_parallel + 1, cam, &drop_shadow_matrix, 0);
                }

                shVectorCopy(&shadow_man.char_man[i]->light_pos, &light_pos[0]);
                
                if (shadow_man.char_man[i]->light_kind == 4)
                    sh2shd_renew_char_man_parallel(shadow_man.char_man[i], &shadow_man.char_man[i]->light_pos);
            }
        }
    }

    
    if (shadow_man.parallel_bg_num > 0) {
        sceVu0FVECTOR dir; // r29+0x210
        demo_no = 0;
            
        for (i = 0; i < 4; i++) {
            
            if ((shadow_man.outdoor_man[i] != NULL) &&
                (shadow_man.outdoor_man[i]->light_kind == 4)) {
                
                if (demo_no == 0) {
                    
                    
                    
                    
                    demo_no++;
                    
                    shVectorCopy(&dir, &shadow_man.outdoor_man[i]->light_dir);
                    shScaleVector(&dir, &dir, -1.0f);
                    
                    
                    shScaleVector(&shadow_man.outdoor_man[i]->light_pos, &dir, 10000.0f);
                    shAddVector(&shadow_man.outdoor_man[i]->light_pos, &shadow_man.outdoor_man[i]->light_pos, &shadow_man.outdoor_man[i]->shape->local_world[3]);
                    
                    
                    
                    sceVu0DropShadowMatrix(drop_shadow_matrix, dir, 0.0f, 0.01f, 0.0f, 0);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    shadow_set_micro_params(&shadow_micro_frame_parallel + 2, cam, drop_shadow_matrix, 0);
                }
                sh2shd_get_shadow_env_bg(&shadow_env, shadow_man.outdoor_man[i]->raw_data);
                if (shadow_man.outdoor_man[i]->light_kind == 4) {
                    sh2shd_renew_outdoor_man_for_parallel(shadow_man.outdoor_man[i], &shadow_man.outdoor_man[i]->light_pos[0], &shadow_env);
                }
            }
        }
    }




}
#else
INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_renew_shadow_man)
#endif


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
