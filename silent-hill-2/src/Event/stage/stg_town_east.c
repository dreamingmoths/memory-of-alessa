#include "sh2_common.h"
#include "sce/libvu0.h"

#include "Chacter/m3_play_event.h"
#include "Chacter/m3_sc.h"

#include "Collision/cl_main.h"

#include "data/fs_structs.h"
#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_wp.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/demoview.h"
#include "Event/item.h"
#include "Event/chara_data_load.h"

#include "GFW/sh2gfw_2d_filters.h"

#include "SH2_common/pad.h"
#include "SH2_common/sh2dt.h"

#include "sh2shd/sh2shd_shadow_model.h"

#include "view/vc_main.h"
#include "view/vc_util.h"

UNMIGRATED(fsFileIndex data_demo_saisho_scu_anm[1]); // data_demo_saisho.c
UNMIGRATED(fsFileIndex data_chr_scu_scu_anm[1]); // data_chr_scu.c

UNMIGRATED(/* static */ u_long128* stg_town_east_anim_adr); // size: 0x4, address: 0x1F08200
UNMIGRATED(/* static */ char* stg_town_east_dds_adr[4]); // size: 0x10, address: 0x1F07DD0
UNMIGRATED(/* static */ u_long128* stg_town_east_wp_mdl); // size: 0x4, address: 0x1F08208
UNMIGRATED(/* static */ u_long128* stg_town_east_wp_anm); // size: 0x4, address: 0x1F08210

UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb11[8]); // @ 0x1F05580
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb12[7]); // @ 0x1F05800
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb18[4]); // @ 0x1F05A30
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb19[10]); // @ 0x1F05B70
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb20[10]); // @ 0x1F05E90
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb21[2]); // @ 0x1F061B0
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb49[14]); // @ 0x1F06250
UNMIGRATED(/* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb52[2]); // @ 0x1F066B0


/* static */ int stg_town_east_EvProgShadowOfSomenthing(void) {
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos0); // @ 0x01F07E50
    UNMIGRATED(Event_CamSetData stg_town_east_cam_data_01F07DE0); // @ 0x01F07DE0
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos1); // @ 0x01F07E60
    UNMIGRATED(sceVu0FVECTOR stg_town_east_scu_pos_01F07E80); // @ 0x01F07E80
    UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_01F07E20); // @ 0x01F07E20
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos2); // @ 0x01F07E70
    sceVu0FVECTOR scu_rot; // r29+0x10

    
    
    
    
    
    
    
    
    demo_number = 5;
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_pos0, -QUARTER_TURN);
            EV_PROG_STEP(27);
    
        case 27:
            DramaDemoFade();
            vcSetEventCamParamRefView(stg_town_east_cam_data_01F07DE0.pos, NULL, stg_town_east_cam_data_01F07DE0.itr, NULL, stg_town_east_cam_data_01F07DE0.roll, 1);
            
            vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
            PlayerEventMove(stg_town_east_pos1);
            if (PlayerEventMoveIsEnd()) EV_PROG_STEP(30);            
            if (shPadTrigger(0, key_config.skip)) EV_PROG_STEP(13);            
            break;
        
        case 30:
            DramaDemoFade();
            if (EvSubMessage(28)) {
                stg_town_east_info_01F07E20.adr_dds_top = stg_town_east_dds_adr[3];
                *(u_long128 *)scu_rot = 0;
                CharaWorkCreate(EN_SCU_CHARA_KIND, 0, stg_town_east_scu_pos_01F07E80, scu_rot, 17);
                ev_timer = 0.0f;
                EV_PROG_STEP(23);
            
            case 23:
                if (DramaDemoMain(&stg_town_east_info_01F07E20)) 
                    if (shPadTrigger(0, key_config.skip)) EV_PROG_STEP(13);
                    else EV_PROG_STEP(16);                                    
            }
            break;
        
        case 16:
            ev_timer += shGetDT();
            if (ev_timer > 3.0f) EV_PROG_STEP(31);            
            if (shPadTrigger(0, key_config.skip)) EV_PROG_STEP(13);            
            DramaDemoSkipLast(&stg_town_east_info_01F07E20);
            break;
        
        case 31:
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_pos2, 0.0f);
            vcReturnPreAutoCamWork(1);

        case 32:
            DramaDemoFade();
            if (EvSubMessage(29)) {
                EV_PROG_STEP(13);
                
                case 13:
                    shCharacter_Manage_Delete(NULL, EN_SCU_CHARA_KIND, 0);
                    shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_pos2, 0.0f);
                    vcReturnPreAutoCamWork(1);
                    SCNowPlayableEventSwitch(sh2jms.player, false);
                    PlayerEventMoveCancel();
                    return 1;
            }            
    }
    return 0;
}

/* static */ int stg_town_east_EvProgSandersBack(void) {
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos); // @ 0x01F08990
    
    switch (ev_p_step) {
        
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);

        case 10:
            if (EvSubMessage(30))
                EV_PROG_STEP(27);            
            break;
            
        case 27:
            stg_town_east_pos[0] = 500.0f + sh2jms.player->pos.x;
            stg_town_east_pos[1] = sh2jms.player->pos.y;
            stg_town_east_pos[2] = sh2jms.player->pos.z;
            stg_town_east_pos[3] = 0.0f;
            EV_PROG_STEP(28);

        case 28:
            PlayerEventMove(stg_town_east_pos);
            if (PlayerEventMoveIsEnd()) EV_PROG_STEP(13);             
            break;
        
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

/* static */ int stg_town_east_EvProgFirstMonsterStart(void) {
    UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_01F07EC0);
    UNMIGRATED(sceVu0FVECTOR stg_town_east_jms_pos_01F07EF0);
    UNMIGRATED(float stg_town_east_jms_rot_01F08238);
    UNMIGRATED(sceVu0FVECTOR stg_town_east_scu_pos_01F07F00);
    UNMIGRATED(sceVu0FVECTOR stg_town_east_scu_rot);



 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


    switch (ev_p_step) {
        case 0:
            stg_town_east_info_01F07EC0.adr_dds_top = *stg_town_east_dds_adr;
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_demo_saisho_scu_anm, stg_town_east_anim_adr, 0);
            
            shCharacter_Manage_Delete(NULL, EN_SCU_CHARA_KIND, 4);
            radio.event = 2;
            EV_PROG_STEP(22);
    
        
        case 22:
            if (DramaDemoMain(&stg_town_east_info_01F07EC0)) EV_PROG_STEP(13);            
            break;
        
        case 13:            
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, ITEM_I_KAKUZAI_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, ITEM_I_RADIO_CHARA_KIND, 0);
            ItemGet(WOODEN_PLANK);
            ItemGet(SH2_ITEM_RADIO);
            item.equip = WOODEN_PLANK;
            CharaDataWeaponTranslation(WEAPON_KAKUZAI_CHARA_KIND, data_chr_jms_jms_wpkaku_anm, stg_town_east_wp_anm, data_chr_wp_wp_kakuzai_mdl, stg_town_east_wp_mdl);
            
            
            ConnectCharaWorkWeapon();
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_jms_pos_01F07EF0, stg_town_east_jms_rot_01F08238);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_chr_scu_scu_anm, stg_town_east_anim_adr, 0);
            
            CharaAdminReCreate(EN_SCU_CHARA_KIND, 4, 0, stg_town_east_scu_pos_01F07F00, stg_town_east_scu_rot, 16);
            
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_518);
            return 1;
    }
    return 0;
}


/* static */ int stg_town_east_EvProgFirstMonsterCorpse(void) {
    UNMIGRATED(float stg_town_east_jms_rot_01F08240); // @ 0x01F08240
    UNMIGRATED(sceVu0FVECTOR stg_town_east_jms_pos_01F07F70); // @ 0x01F07F70
    UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_a_01F07F40); // @ 0x01F07F40
    SubCharacter* scp;




    
    
    
    
    
    
    
    
    
    
    
    
    switch (ev_p_step) {
        case 0:
            radio.event = 0;
            stg_town_east_info_a_01F07F40.adr_dds_top = stg_town_east_dds_adr[1];
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_demo_saisho_scu_anm, stg_town_east_anim_adr, 0);
            
            scp = shCharacterGetSubCharacter(EN_SCU_CHARA_KIND, 4);
            scp->status &= ~(1 << SCP_STATUS_BIT_4);
            UNSET_GAME_FLAG(GAME_FLAG_518);
            EV_PROG_STEP(23);
        
        
        case 23:            
            if (DramaDemoMain(&stg_town_east_info_a_01F07F40)) EV_PROG_STEP(13);            
            break;
            
        case 13:
            CharaDataDeleteOne(ITEM_I_KAKUZAI_CHARA_KIND);
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, EN_SCU_CHARA_KIND, 0);
            scp = shCharacterGetSubCharacter(EN_SCU_CHARA_KIND, 4);
            scp->status |= (1 << SCP_STATUS_BIT_4);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_chr_scu_scu_anm, stg_town_east_anim_adr, 1);
            
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_jms_pos_01F07F70, stg_town_east_jms_rot_01F08240);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            return 1;
    }
    return 0;
}

UNMIGRATED(CharaData_DemoList stg_town_east_enemy_list_01F07FF0[3]); // @ 0x01F07FF0
UNMIGRATED(float stg_town_east_jms_rot_01F08040); // @ 0x01F08040
UNMIGRATED(sceVu0FVECTOR stg_town_east_jms_pos_01F08030); // @ 0x01F08030
UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_b_01F07FC0); // @ 0x01F07FC0
/* static */ int stg_town_east_EvProgFirstMonsterEnd(void) {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    switch (ev_p_step) {
        case 0:
            stg_town_east_info_b_01F07FC0.adr_dds_top = stg_town_east_dds_adr[2];
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(24); 
    
       
        case 24:
            if (DramaDemoMain(&stg_town_east_info_b_01F07FC0)) EV_PROG_STEP(13);            
            break;
            
        case 13:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_RADIO_CHARA_KIND);
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_jms_pos_01F08030, stg_town_east_jms_rot_01F08040);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            CharaDataDeleteExtra();
            CharaAdminBackLoadEnemy(stg_town_east_enemy_list_01F07FF0);
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgBloodSwamp);

/* static */ int stg_town_east_EvProgGetApartGateKey(void) {
    return EvSubItemGetAndAnim(APART_GATE_KEY, 18);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgUseApartGateKey);

/* static */ int stg_town_east_EvProgLookMemoFalled(void) {
    int i; // r5
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(20001);
            EV_PROG_STEP(16);
            /* fallthrough */
        case 16:
            if (ev_cancel) {
                ev_prog_flag_set = 0;
                EV_PROG_STEP(13);
            } else if (PlayerEventAnimeSuccessFrame()) {
                shCharacterAnimePause(sh2jms.player);
                if (GET_GAME_FLAG(GAME_FLAG_51)) {
                    if (!GET_GAME_FLAG(GAME_FLAG_50)) {
                        EV_PROG_STEP(30);
                    } else {
                        EV_PROG_STEP(31);
                    }
                } else if (!GET_GAME_FLAG(GAME_FLAG_52) && !GET_GAME_FLAG(GAME_FLAG_54) && !GET_GAME_FLAG(GAME_FLAG_56) && !GET_GAME_FLAG(GAME_FLAG_58) && !GET_GAME_FLAG(GAME_FLAG_610)) {
                    EV_PROG_STEP(30);
                } else {
                    EV_PROG_STEP(31);
                }
            }
            break;
        
        case 30:
            if (GET_GAME_FLAG(GAME_FLAG_51)) {
                if (!EvSubMessage(26)) break;
            } else {
                if (!EvSubMessage(27)) break;
            }        
            EV_PROG_STEP(31);
            case 31:
                if ((!GET_GAME_FLAG(GAME_FLAG_51) || EvSubMessage(20)) && (!GET_GAME_FLAG(GAME_FLAG_53) || EvSubMessage(21)) && (!GET_GAME_FLAG(GAME_FLAG_55) || EvSubMessage(22)) && (!GET_GAME_FLAG(GAME_FLAG_57) || EvSubMessage(23)) && (!GET_GAME_FLAG(GAME_FLAG_59) || EvSubMessage(24)) && (!GET_GAME_FLAG(GAME_FLAG_611) || EvSubMessage(25))) {
                    if (ev_cancel) {
                        EV_PROG_STEP(13);
                        break;
                    }
                    shCharacterAnimeRestart(sh2jms.player);
                    EV_PROG_STEP(1);
                case 1:
                    if ((shCharacterAnimeIsEnd(sh2jms.player)) && (ev_cancel == 0)) {
                        EV_PROG_STEP(13);
                        case 13:
                            i = 0;
                            while (i < 5) {
                                UNSET_GAME_FLAG((i * 2) + 51);
                                i++;
                            }
                            SCNowPlayableEventSwitch(sh2jms.player, false);
                            return 1;
                    }
                    break;
                }
    }
    return 0;
}

/* static */ void stg_town_east_EvStageInit(void) {
    if (GET_GAME_FLAG(GAME_FLAG_1303)) 
        SET_GAME_FLAG(GAME_FLAG_1269);    
    if (GET_GAME_FLAG(GAME_FLAG_1302))
        SET_GAME_FLAG(GAME_FLAG_1268);    
    if (GET_GAME_FLAG(GAME_FLAG_1266))
        SET_GAME_FLAG(GAME_FLAG_1295);
}

/* static */ int stg_town_east_EvCharaDataClear(void) {
    return !GET_GAME_FLAG(GAME_FLAG_43);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvRoomInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvAllTimeFunc);

/* static */ int stg_town_east_EvBgmControl(void) {
    if (GET_GAME_FLAG(GAME_FLAG_518)) {
        return 4;
    }
    return GET_GAME_FLAG(GAME_FLAG_41) != 0;
}

/* static */ void stg_town_east_EvLockSetCb46(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_49)) {
        EvDispControlModelEntry(list, 0x2E, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0x2E, 1);
}

/* static */ void stg_town_east_EvCorpseSetCb18(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        clAddDynamicWall(stg_town_east_clActWallList_cb18);
        EvDispControlModelEntry(list, 0x12, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0x12, -1);
}

/* static */ void stg_town_east_EvCorpseSetCb26(void) {
    return;
}

/* static */ void stg_town_east_EvWallSetCb19(int* list) {
    EvDispControlModelEntry(list, 0x13, -1); // @todo: add room id
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x13, 0);
        clAddDynamicWall(stg_town_east_clActWallList_cb19);
    }
}

/* static */ void stg_town_east_EvWallSetCb20(int* list) {
    EvDispControlModelEntry(list, 0x14, -1); // @todo: add room id
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x14, 0);
        clAddDynamicWall(stg_town_east_clActWallList_cb20);
    }
}

/* static */ void stg_town_east_EvWallSetCb21(int* list) {
    EvDispControlModelEntry(list, 0x15, -1);
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        clAddDynamicWall(stg_town_east_clActWallList_cb21);
        EvDispControlModelEntry(list, 0x15, 0);
        return;
    }
    sh2shd_add_map_to_shadow_off_work(0x15);
    sh2shd_off_obj(0x15, 8); // @todo: add room id and obj id
}

/* static */ void stg_town_east_EvWallSetCb49(int* list) {
    if (!GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x31, 1); // @todo: add room id
        clAddDynamicWall(&stg_town_east_clActWallList_cb49[4]);
        return;
    }
    EvDispControlModelEntry(list, 0x31, 0);
    clAddDynamicWall(stg_town_east_clActWallList_cb49);
}

/* static */ void stg_town_east_EvWallSetCb52(int* list) {
    sh2shd_add_map_to_shadow_off_work(0x34);
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x34, 1);
        clAddDynamicWall(stg_town_east_clActWallList_cb52);
        sh2shd_off_obj(0x34, 0x37); // @todo: add room id and obj id
        return;
    }
    EvDispControlModelEntry(list, 0x34, 0);
    sh2shd_off_obj(0x34, 0x36);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb27);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb28);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb29);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb35);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb36);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb37);

/* static */ void stg_town_east_EvTapeSetCb11(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0xB, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0xB, 1);
    clAddDynamicWall(stg_town_east_clActWallList_cb11);
}

/* static */ void stg_town_east_EvTapeSetCb12(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0xC, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0xC, 1);
    clAddDynamicWall(stg_town_east_clActWallList_cb12);
}

/* static */ float stg_town_east_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_CB_1stMoster_FogHosei);

/* static */ void stg_town_east_CB_1stMonster_Filter(void) {
    FilterParams* pfp; // r16
    sceVu0FVECTOR campos; // r29+0x20
    
    vwGetViewPosition(campos);
    if ((campos[2] < 50000.0f) && (campos[1] > -2000.0f) && ((DramaDemoNumber() == 6) || (DramaDemoNumber() == 7))) {
        pfp = sh2gfw_Get_FilterCommandParams();
        sh2gfw_Reset_FilterCommand();
        shGsFilterWork.GsFilterKind = 6;
        pfp->SoftIter = 3;
        pfp->SoftCit = 25;
        pfp->SoftAref = 216;
        pfp->SoftShift = -4;
        pfp->base_Ix = -8;
        pfp->base_Iy = -8;
        return;
    }
    if (shGsFilterWork.GsFilterKind < 15) {
        sh2gfw_Reset_FilterCommand();
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Draw_CB_Tonnel);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Monster1st_Look);
