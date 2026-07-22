#include "sh2_common.h"

#include "SH2_common/mem_share.h"

#include "Multi_thr/filesys/fcread.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/stg_name.h"
#include "Event/demoview.h"
#include "Event/chara_data_load.h"

#include "Chacter/chara_list.h"
#include "Chacter/sh2_character_manage.h"

#include "DS_Pad/dsr_data.h"

#include "data/daily.thu/data_demo_kagikeri.h"
#include "data/daily.thu/data_chr_item.h"
#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_lau.h"

static int stg_apart_e3fw_EvProgLauraKickKey(void);
static int stg_apart_e3fw_EvProgGetHandgun(void);
static void stg_apart_e3fw_EvRoomInit(void);
static void stg_apart_e3fw_EvProgSubScreamOn(void);

static AnimeInfo stg_apart_e3fw_pjames_stage_anim[21] = { // @ 0x01F02380
    {
        /* .name =  */ 0x4E21,
        /* .frame = */ 0x0014, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0400, 
        /* .end =   */ 0x0413,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x0A
    },
    {
        /* .name =  */ 0x4E27,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0414, 
        /* .end =   */ 0x0431,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E28,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0300,
        /* .start = */ 0x0432, 
        /* .end =   */ 0x0440,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E29,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0300,
        /* .start = */ 0x0441, 
        /* .end =   */ 0x044F,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E2A,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0300,
        /* .start = */ 0x0450, 
        /* .end =   */ 0x046D,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E2B,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0300,
        /* .start = */ 0x046E, 
        /* .end =   */ 0x048B,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E2C,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0490, 
        /* .end =   */ 0x049A,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E2D,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x049F, 
        /* .end =   */ 0x04A9,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E2E,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0280,
        /* .start = */ 0x04AA, 
        /* .end =   */ 0x04C7,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E2F,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0280,
        /* .start = */ 0x04C8, 
        /* .end =   */ 0x04E5,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E30,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x04EA, 
        /* .end =   */ 0x04F4,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E31,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x04F9, 
        /* .end =   */ 0x0503,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E32,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0504, 
        /* .end =   */ 0x0521,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E33,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0522, 
        /* .end =   */ 0x053F,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E34,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0540, 
        /* .end =   */ 0x055D,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E39,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0562, 
        /* .end =   */ 0x056C,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E3A,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x0571, 
        /* .end =   */ 0x057B,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E3B,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x057C, 
        /* .end =   */ 0x0599,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E3C,
        /* .frame = */ 0x001E, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x059A, 
        /* .end =   */ 0x05B7,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    {
        /* .name =  */ 0x4E45,
        /* .frame = */ 0x000F, 
        /* .speed = */ 0x0400,
        /* .start = */ 0x05B8, 
        /* .end =   */ 0x05C6,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    },
    { 
        /* .name =  */ 0x0000,
        /* .frame = */ 0x0000, 
        /* .speed = */ 0x0000,
        /* .start = */ 0x0000, 
        /* .end =   */ 0x0000,
        /* .loop =  */ 0x00, 
        /* .pad =   */ 0x00
    }
}; 

static u_int stg_apart_e3fw_ev_pos[36] = { // @ 0x01F02480 // @note: note sure about this one
    0x475B7A9F,
    0xBFF68000,
    0x64B04628,
    0x469C3529,
    0x3F3B8000,
    0xDA70469E,
    0xD2DA55C1,
    0x57FF5D88,
    0x38E65AED,
    0x8000471C,
    0x4635DCFB,
    0xF87D5F5D,
    0x8000471F,
    0x4628841F,
    0x93325FD0,
    0x80004690,
    0x46AF3000,
    0x42FD5FF9,
    0x80004693,
    0x468E2F00,
    0x6AA468B0,
    0x473A887D,
    0x841F8000,
    0x5FD04628,
    0x47583602,
    0xE8008000,
    0x5FD04628,
    0xC7C07B00,
    0xB406EB08,
    0x5FC5C68C,
    0x46A62C01,
    0xCE088000,
    0x5E8F469A,
    0x46931F08,
    0xF6038000,
    0x5E8F469A
}; 

static Event_List stg_apart_e3fw_ev_list[14] = { // @ 0x01F02510
    {
        /* .flag =  */ 0x00430000, 
        /* .cond =  */ 0x20004004,
        /* .rslt0 = */ 0x30000000, 
        /* .rslt1 = */ 0x00004000
    },
    {
        /* .flag =  */ 0x00590000,
        /* .cond =  */ 0x20004000, 
        /* .rslt0 = */ 0x60000000,
        /* .rslt1 = */ 0x00010000 
    },
    {
        /* .flag =  */ 0x05840000,
        /* .cond =  */ 0x30004000,
        /* .rslt0 = */ 0x10000000,
        /* .rslt1 = */ 0x00000584 
    },
    {
        /* .flag =  */ 0x00420000,
        /* .cond =  */ 0x200C7000, 
        /* .rslt0 = */ 0x30000000, 
        /* .rslt1 = */ 0x00008042
    },
    {
        /* .flag =  */ 0x00000000,
        /* .cond =  */ 0x20223000,
        /* .rslt0 = */ 0x90000000,
        /* .rslt1 = */ 0x013FC577
    },
    {
        /* .flag =  */ 0x00000000,
        /* .cond =  */ 0x202E1000,
        /* .rslt0 = */ 0x403A2000,
        /* .rslt1 = */ 0x00400578
    },
    {
        /* .flag =  */ 0x00000000, 
        /* .cond =  */ 0x203A2000,
        /* .rslt0 = */ 0x402E1000, 
        /* .rslt1 = */ 0x00400578 
    },
    {
        /* .flag =  */ 0x05850000, 
        /* .cond =  */ 0x4046B004, 
        /* .rslt0 = */ 0x10000000,
        /* .rslt1 = */ 0x00000585 
    },
    {
        /* .flag =  */ 0x05860000,
        /* .cond =  */ 0x4046B004,
        /* .rslt0 = */ 0x10000000,
        /* .rslt1 = */ 0x00000586 
    },
    {
        /* .flag =  */ 0x00000000,
        /* .cond =  */ 0x20541000,
        /* .rslt0 = */ 0x90000000, 
        /* .rslt1 = */ 0x007FC579 
    },
    {
        /* .flag =  */ 0x00000000,
        /* .cond =  */ 0x20601000,
        /* .rslt0 = */ 0x406C2180, 
        /* .rslt1 = */ 0x01000582 
    },
    {
        /* .flag =  */ 0x00000000,
        /* .cond =  */ 0x20784000, 
        /* .rslt0 = */ 0x90000000, 
        /* .rslt1 = */ 0x007FC000 
    },
    {
        /* .flag =  */ 0x00000000,
        /* .cond =  */ 0x20843000,
        /* .rslt0 = */ 0x90000000,
        /* .rslt1 = */ 0x007FC000
    },
    {
        /* .flag =  */ 0,
        /* .cond =  */ 0,
        /* .rslt0 = */ 0,
        /* .rslt1 = */ 0
    }
}; 

static Item_List stg_apart_e3fw_gi_list[4] = { // @ 0x01F025F0
    {
        /* .pos_x = */ 20967.279f,
        /* .pos_z = */ 19368.400f,
        /* .pos_y = */ 0xDBE9,
        /* .rot_y = */ 0x8000,
        /* .st =    */ 0x20000303
    },
    {
        /* .pos_x = */ 21034.08f, 
        /* .pos_z = */ 19456.0f,
        /* .pos_y = */ 0xDBE9,
        /* .rot_y = */ 0x3C66,
        /* .st =    */ 0x20000305
    },
    {
        /* .pos_x = */ 21020.08f,  
        /* .pos_z = */ 19402.0f,
        /* .pos_y = */ 0xDBE9,
        /* .rot_y = */ 0x3CE2,
        /* .st =    */ 0x20000307
    },
    {
        /* .pos_x = */ 0.0f,
        /* .pos_z = */ 0.0f, 
        /* .pos_y = */ 0x0000,
        /* .rot_y = */ 0x0000,
        /* .st =    */ 0xE0000000
    }
}; 

static int (*stg_apart_e3fw_ev_prog[3])(void) = { // @ 0x01F02630
    NULL,                                  
    stg_apart_e3fw_EvProgLauraKickKey,     
    stg_apart_e3fw_EvProgGetHandgun        
}; 

static Model_List stg_apart_e3fw_mdl_list[4] = { // @ 0x01F02640
    {
        /* .kind =     */ ITEM_X_HANDGUN_CHARA_KIND,
        /* .id =       */ 0x0000,
        /* .flag_off = */ 0x0042,
        /* .flag_on =  */ 0x0000,
        /* .pos =      */ { 19979.719f, -333.7622f, 20395.0f, 0.0f },
        /* .rot =      */ { 1.570796f, -0.0f, -1.523667f, 0.0f }
    },
    {
        /* .kind =     */ ITEM_X_KEYCOURT_CHARA_KIND,
        /* .id =       */ 0x0000,
        /* .flag_off = */ 0x0043,
        /* .flag_on =  */ 0x0000,
        /* .pos =      */ { 56560.535f, -3.41766f, 11205.266f, 0.0f },
        /* .rot =      */ { -1.597323f, -0.06904f, 0.189038f, 0.0f }
    },
    {
        /* .kind =     */ ITEM_X_KEYCOURT_CHARA_KIND,
        /* .id =       */ 0x0000,
        /* .flag_off = */ 0x0059,
        /* .flag_on =  */ 0x0043,
        /* .pos =      */ { 57170.984f, -3.53376f, 11713.185f, 0.0f },
        /* .rot =      */ { -1.512634f, -0.053164f, 0.41216f, 0.0f }
    },
    {
        /* .kind =     */ 0x0000,
        /* .id =       */ 0x0000,
        /* .flag_off = */ 0x0000,
        /* .flag_on =  */ 0x0000,
        /* .pos =      */ { 0.0f, 0.0f, 0.0f, 1.0f },
        /* .rot =      */ { 0.0f, 0.0f, 0.0f, 1.0f }
    },
};

static Enemy_List stg_apart_e3fw_en_list[5] = { // @ 0x01F02700
    {
        /* .kind =      */ EN_SCU_CHARA_KIND,
        /* .id =        */ 0x004E,
        /* .pos_x =     */ 0x0000EC54,
        /* .pos_z =     */ 0x00007530,
        /* .pos_y =     */ 0x0000,
        /* .rot_y =     */ 0x0000,
        /* .status =    */ 0x0000,
        /* .condition = */ 0x0083
    },
    {
        /* .kind =      */ EN_SCU_CHARA_KIND,
        /* .id =        */ 0x004F,
        /* .pos_x =     */ 0x0000EB28,
        /* .pos_z =     */ 0x00006D60,
        /* .pos_y =     */ 0x0000,
        /* .rot_y =     */ 0xCDBD,
        /* .status =    */ 0x0000,
        /* .condition = */ 0x0080
    },
    {
        /* .kind =      */ EN_SCU_CHARA_KIND,
        /* .id =        */ 0x0050,
        /* .pos_x =     */ 0x00012110,
        /* .pos_z =     */ 0x00002BC0,
        /* .pos_y =     */ 0x0000,
        /* .rot_y =     */ 0x1921,
        /* .status =    */ 0x0000,
        /* .condition = */ 0x0081
    },
    {
        /* .kind =      */ EN_SCU_CHARA_KIND,
        /* .id =        */ 0x0051,
        /* .pos_x =     */ 0x0000C92C,
        /* .pos_z =     */ 0x00002C24,
        /* .pos_y =     */ 0x0000,
        /* .rot_y =     */ 0xE6DF,
        /* .status =    */ 0x0000,
        /* .condition = */ 0x0083
    },
    {
        /* .kind =      */ 0x0000,
        /* .id =        */ 0x0000,
        /* .pos_x =     */ 0x00000000,
        /* .pos_z =     */ 0x00000000,
        /* .pos_y =     */ 0x0000,
        /* .rot_y =     */ 0x0000,
        /* .status =    */ 0x0000,
        /* .condition = */ 0x0000
    }
}; 

static Stage_Data stage_apart_e3fw = { // @ 0x01F02770
    /* .ev_list = */                stg_apart_e3fw_ev_list,
    /* .ev_pos = */                 (u_char*)stg_apart_e3fw_ev_pos,
    /* .ev_prog = */                stg_apart_e3fw_ev_prog,
    /* .gi_list = */                stg_apart_e3fw_gi_list,
    /* .mdl_list = */               stg_apart_e3fw_mdl_list,
    /* .en_list = */                stg_apart_e3fw_en_list,
    /* .stage_init = */             NULL,
    /* .room_init = */              (void (*)(void))stg_apart_e3fw_EvRoomInit,
    /* .alltime_func = */           NULL,
    /* .glb_crd = */                9,
    /* .pc_model = */               1,
    /* .stg_anim_info = */          stg_apart_e3fw_pjames_stage_anim,
    /* .bgm_control = */            NULL,
    /* .gfw_func = */               NULL,
    /* .chara_data_clear = */       NULL,
    /* .sound_call_after_load = */  NULL,
    /* .reserve_11 = */             0
}; 

static short stg_apart_e3fw_anim_01F027B8[4] = { // @ 0x01F027B8
    0x03EB,
    0x09C7,
    0x2711,
    0x0000
}; 

static DramaDemo_MessageTime stg_apart_e3fw_movie_msg_01F027C0[8] = { // @ 0x01F027C0
    { 0x01A2,  0x01C3 },
    { 0x01F3,  0x020B },
    { 0x020B,  0x0235 },
    { 0x0235,  0x0262 },
    { 0xFFFF,  0xFFFF }, 
    { 0x0000,  0x0000 }, 
    { 0x0000,  0x0000 }, 
    { 0x0000,  0x0000 }  
}; 

static DramaDemo_PlayInfo stg_apart_e3fw_kick = {
    /* .demo_no = */      9,
    /* .adr_dds_top = */  MemShare_gp_data_buf, 
    /* .adr_anim = */     &stg_apart_e3fw_anim_01F027B8,
    /* .adr_msg_time = */ &stg_apart_e3fw_movie_msg_01F027C0, 
    /* .msg_start = */    5,
    /* .voice_sd_no = */  0,
    /* .adr_voice = */    NULL, 
    /* .stream_no = */    0x0000EA83, 
    /* .stream_start = */ 25.0f, 
    /* .add_pos_x = */    0.0f, 
    /* .add_pos_z = */    0.0f
}; // @ 0x01F027E0

static CharaData_DemoList stg_apart_e3fw_kagikeri_data[4] = { // @ 0x01F02810
    {
        /* .kind = */      HHH_JMS_CHARA_KIND,
        /* .model = */     data_chr_jms_hhh_jms_mdl,
        /* .animation = */ data_demo_kagikeri_hhh_jms_anm,
        /* .shadow = */    data_chr_jms_hhh_jms_kg1,
        /* .cluster = */   data_demo_kagikeri_hhh_jms_cls
    },
    {
        /* .kind = */      LAU_CHARA_KIND,
        /* .model = */     data_chr_lau_lau_mdl,
        /* .animation = */ data_demo_kagikeri_lau_anm,
        /* .shadow = */    data_chr_lau_lau_kg1,
        /* .cluster = */   data_demo_kagikeri_lau_cls
    },
    {
        /* .kind = */      ITEM_I_KEYCOU_CHARA_KIND,
        /* .model = */     data_chr_item_i_keycou_mdl,
        /* .animation = */ data_demo_kagikeri_i_keycou_anm,
        /* .shadow = */    NULL,
        /* .cluster = */   NULL
    },
    0
}; 

static float stg_apart_e3fw_yard_key_after_data[2][4] = { // @ 0x01F02860
    { 57170.98438f, -3.533760071f, 11713.18457f, 0.0f },  
    { -1.512634039f, -0.05316400155f, 0.4121600091f, 0.0f }
};

static int stg_apart_e3fw_EvProgLauraKickKey(void) {   
    if (demo_frame > 405.5f && demo_frame <= 406.7f) {
        DSR_Entry0(__otn_kick_key_00, 0, 1.0f);
    }
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            FcRead(data_demo_kagikeri_kagikeri_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_e3fw_kagikeri_data, 1);
            EV_PROG_STEP(10);
            /* fallthrough */
    
        case 10:
            if (EvSubQuestion(3)) {
                if (!fontGetStatus()) {
                    EV_PROG_STEP(2);
                } else {
                    CharaDataLoadCancel(stg_apart_e3fw_kagikeri_data);
                    EV_PROG_STEP(13);
                }
            }
            break;
    
        case 2:
            if (fsSync(1, -1) >= 0) {
                CharaDataLoadDemo(stg_apart_e3fw_kagikeri_data, 0);
                CharaAdminPlayableDisplay(0);
                shCharacter_Manage_Delete(NULL, ITEM_X_KEYCOURT_CHARA_KIND, 0);
                SCNowDemoEventSwitch(sh2jms.player, 1);
                EV_PROG_STEP(22);
            case 22:
                if (DramaDemoMain(&stg_apart_e3fw_kick)) {
                    EV_PROG_STEP(6);
                }
            }
            break;
    
        case 6:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(LAU_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_KEYCOU_CHARA_KIND);
            CharaWorkCreate(ITEM_X_KEYCOURT_CHARA_KIND, 0, stg_apart_e3fw_yard_key_after_data[0], stg_apart_e3fw_yard_key_after_data[1], 0);
            CharaAdminPlayableDisplay(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_67);
            EV_PROG_STEP(13);
            /* fallthrough */

        case 13:
            if (GET_GAME_FLAG(GAME_FLAG_66))
                stg_apart_e3fw_EvProgSubScreamOn();

            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }

    return 0;
}

static int stg_apart_e3fw_EvProgGetHandgun(void) {
    int ret = EvSubItemGetAndAnim(4, 0); // r16

    if (ret && GET_GAME_FLAG(GAME_FLAG_67)) {
        stg_apart_e3fw_EvProgSubScreamOn();
    }

    return ret;
}

static void stg_apart_e3fw_EvRoomInit(void) {
    /* empty */
}

static void stg_apart_e3fw_EvProgSubScreamOn(void) {
    SubCharacter* scp; // r16

    SET_GAME_FLAG(GAME_FLAG_68);
    scp = shCharacter_Manage_GetCharacterList();

    while (scp != NULL) {
        if (IS_SCP_ENEMY(scp) && RoomName(0, scp->pos.x, scp->pos.z) == 21 && scp->battle.hp <= 0.0f) {
            SET_FLAG(game_flag.enemy, scp->id);
            shCharacter_Manage_Delete(scp, 0, 0);
        }
        scp = scp->next;
    }
}
