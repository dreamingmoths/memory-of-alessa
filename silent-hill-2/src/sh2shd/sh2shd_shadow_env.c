#include "common.h"
#include "Event/demoview.h"
#include "Chacter/m3_sc.h"

extern /* static */ float tmp_time_1450;
static float get_demo_frame(void);

RODATA_PAD_TO(0x0039B850);
INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_shadow_env_bg);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_shadow_env_chr);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_demo_shadow_env_for_bg);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_demo_shadow_env_for_char);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_jms_shadow_env);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_demo_jms_shadow_env);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_drop_shadow_env);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_get_demo_drop_shadow_env);

#line 1815
void sh2shd_demo_shadow_off(int demo_no) {
    float demo_frame; // r20
    float test_time; // r29+0x70 @unused dwarf
    switch (demo_no) {
        case DRAMA_DEMO_9:
            break;




































        case DRAMA_DEMO_D:
            sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
            sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
            return;

        case DRAMA_DEMO_E:
            demo_frame = get_demo_frame();
        
            
            sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
            if (demo_frame <= 1699.0f) 
                sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
            else {
            
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xF);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 8);
                
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 1);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 3);
                
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1A);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x19);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xE);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xD);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 5);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 4);
            }
            
            
            
            sh2shd_add_char_to_shadow_off_work(EN_RED_CHARA_KIND, 0);
            if (get_demo_frame() < 190.0f) {
                
                sh2shd_off_char_obj(EN_RED_CHARA_KIND, 0, 0x24);
                sh2shd_off_char_obj(EN_RED_CHARA_KIND, 0, 0x1D);
                return;
            } else if (demo_frame >= 360.0f && demo_frame <= 1699.0f) {
                
                sh2shd_add_char_to_shadow_off_work(EN_RED_CHARA_KIND, 0);
                sh2shd_off_char_all_parts(EN_RED_CHARA_KIND, 0);
            }
            
            
            
            
            
            
            
            
            
            
            
            
        
            break;
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        case DRAMA_DEMO_21:
            if (get_demo_frame() < 902.0f) {
        
                sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
                sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
                
                
                return;
            }
        
            
            break;

        
        case DRAMA_DEMO_26:
            sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
            sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1A);
            return;

        
        










        
        case DRAMA_DEMO_2E:
            demo_frame = get_demo_frame();
            if (demo_frame < 780.0f) {
        
                sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x21);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x28);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 3);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 1);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1C);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x22);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x23);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1B);
        
                
                if (demo_frame > 510.0f) {
                
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 4);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 5);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    return;
                }
            }
            break;






        
        case DRAMA_DEMO_41:
            break;
        
        
        
        
        
        
        
        
        
        
        
        
        case DRAMA_DEMO_42: {
            float cam_pos[4]; // r29+0x20
            float env_demo_frame;
            vwGetViewPosition(&cam_pos);
            env_demo_frame = get_demo_frame();
            
            if (env_demo_frame >= 135.0f && env_demo_frame <= 192.0f) {
                
                sh2shd_add_char_to_shadow_off_work(EN_PAP_CHARA_KIND, 0);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 3);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 4);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 5);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 7);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 8);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 9);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x11);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x12);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x13);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x17);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1B);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1C);
            } else 
                if (env_demo_frame >= 518.0f && env_demo_frame <= 608.0f) {
                    
                    sh2shd_add_char_to_shadow_off_work(EN_PAP_CHARA_KIND, 0);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 3);
                    
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 5);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 7);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 8);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 9);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x11);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x12);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x13);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x17);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1B);
                    sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1C);
                    
                    sh2shd_add_char_to_shadow_off_work(AGL_CHARA_KIND, 0);
                    sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 0x1F);
                    sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 6);
                    sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 2);
                    sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 0);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    return;
                }
            break;
        }
















        case DRAMA_DEMO_4A: {
            float mat[4][4]; // r29+0x30
            float env_demo_frame = get_demo_frame();
            shCharacterGetPartsMatrixForShadow(mat, LAU_CHARA_KIND, 0U, 0U);
            if (mat[3][2] > 59000.0f) {
                
                if (env_demo_frame > 320.0f && env_demo_frame <= 962.0f) {
                
                    sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                    sh2shd_off_char_all_parts(LAU_CHARA_KIND, 0);
                    
                    return;
                }



                
            } else if (env_demo_frame >= 782.0f && env_demo_frame < 1420.0f) {
                
                sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 1);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xB);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xC);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xF);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x10);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 3);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 7);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x12);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x16);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x1F);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x25);
                
                
                
                return;
            }
            break;
        }


        case DRAMA_DEMO_4E:

            demo_frame = get_demo_frame();
            if (demo_frame > 1750.0f) {
            
                
                
                sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
                
                if (demo_frame < tmp_time_1450)
                    sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
                else if (demo_frame < 3220.0f) {
                     
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1A);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x19);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xE);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xD);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 5);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 4);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 1);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1B);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x21);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 1);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xB);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xC);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xF);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x10);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 3);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 7);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x12);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x16);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x1F);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x25);
                }
            }
            break;
        }



































}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", sh2shd_shadow_off);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", get_demo_frame);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", get_map_id);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", check_bg_light_exist);
