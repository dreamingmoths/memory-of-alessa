#include "Chacter/sh_character_status.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#include "Event/item.h"

#include "GFW/sh2_get_drawenv.h"

#include "sh2shd/sh2shd_shadow_model.h"

#include "SH2_common/sh_vu0.h"
#include "sce/libvu0.h"

#include "vec.h"

static void shBattleCheckHitEyes(CL_VHIT_RESULT* eye, SubCharacter* scp, int i, int net);

static float _shLength(float*, float*);

static void shBattleCheckHitEyes(CL_VHIT_RESULT* eye, SubCharacter* scp, int i, int net) {
    sceVu0FVECTOR sp;
    sceVu0FVECTOR ep;

    sp[0] = scp->pos.x;
    sp[1] = scp->eye_y;
    sp[2] = scp->pos.z;

    if (GET_KIND_TYPE(sh2_target_info[i].adr.scp->kind) == OBJECT_X_CHARA_KIND) {
        ep[0] = sh2_target_info[i].adr.scp->pos_spd.x;
        ep[1] = sh2_target_info[i].adr.scp->center_y;
        ep[2] = sh2_target_info[i].adr.scp->pos_spd.z;
    } else {
        ep[0] = sh2_target_info[i].adr.scp->pos.x;
        ep[1] = sh2_target_info[i].adr.scp->center_y;
        ep[2] = sh2_target_info[i].adr.scp->pos.z;
    }

    clCheckHitEyes(eye, (u_int) scp, sp, ep, net);
}

void shBattleCheckTargetMyArea(shInArea* in_area, SubCharacter* scp, SubCharacter* tgt, float* look, float* feel) {
    sceVu0FVECTOR tgt_pos;
    float tgt_to_look;
    float tgt_to_feel;

    if (GET_KIND_TYPE(tgt->kind) == OBJECT_X_CHARA_KIND) {
        tgt_pos[0] = tgt->pos_spd.x;
        tgt_pos[1] = tgt->center_y;
        tgt_pos[2] = tgt->pos_spd.z;
    } else {
        tgt_pos[0] = tgt->pos.x;
        tgt_pos[1] = tgt->center_y;
        tgt_pos[2] = tgt->pos.z;
    }

    tgt_to_look = _shLength(look, tgt_pos);
    tgt_to_feel = _shLength(feel, tgt_pos);

    in_area->light_on = (sh2gfw_Check_CharaDarkOrBright(tgt) && tgt_to_feel <= 1.5f * scp->battle.look.radius) ? 1 : 0;
    
    in_area->look_on = (tgt_to_look <= scp->battle.look.radius) ? 1 : 0;
    in_area->feel_on = (tgt_to_feel <= scp->battle.feel.radius) ? 1 : 0;

    switch (GET_KIND_TYPE(tgt->kind)) {
        case 7:
            if (!(scp->status & 0x200)) {
                in_area->look_on = in_area->feel_on = 0;
            }
            if (tgt_pos[1] < scp->eye_y - 600.0f || tgt_pos[1] > scp->eye_y + 1000.0f) {
                
                in_area->light_on = in_area->look_on = in_area->feel_on = 0;
            }
            break;
        case 2:
            if (tgt->battle.dead_timer <= 1.5f) {
                return;
            }
            in_area->light_on = in_area->look_on = in_area->feel_on = 0;;
            break;
        case 1:
            in_area->light_on = in_area->feel_on = 0;
            break;
        default:
            break;
    }
}

static asm float _shLength(register float* x, register float* y) { // @todo: write C equivalent
    lwc1    f0, 0(a0)
    lwc1    $f8,0(a1)
    lwc1    $f9,4(a0)
    lwc1    $f0,0(a0)
    lwc1    $f8,0(a1)
    lwc1    $f9,4(a0)
    sub.s   $f0,$f0,$f8
    lwc1    $f10,4(a1)
    mula.s  $f0,$f0
    lwc1    $f0,8(a0)
    lwc1    $f8,8(a1)
    sub.s   $f9,$f9,$f10
    sub.s   $f0,$f0,$f8
    madda.s $f9,$f9
    madd.s  $f0,$f0,$f0
    sqrt.s  $f0,$f0
    nop     
    nop     
    nop     
    jr      ra
    nop     
}

int shBattleAroundTargetEnemy(void) {
    SubCharacter* tgt; // r4

    for (tgt = sh2chara.head; tgt != NULL;  tgt = tgt->next) {       
        
        if (((GET_KIND_TYPE(tgt->kind)) == ENEMY_CHARA_KIND) 
            && (tgt->battle.status & 0x400) && !(tgt->battle.status & 2)) {
            return 1;
        }
    }
    
    
    
    return 0;
}

int shBattleCheckTargetChara(SubCharacter* scp) {
    int i; // r16
    int j; // r17
    SubCharacter* tgt; // r16
    shInArea in_area; // r29+0x6C
    sceVu0FVECTOR look_center; // r29+0x40
    sceVu0FVECTOR feel_center; // r29+0x50    
    shInAreaTgtInfo dummy; // r29+0x60
    look_center[0] = scp->pos.x + (scp->battle.look.center * shSinF(scp->rot.y));
    look_center[1] = scp->eye_y;
    look_center[2] = scp->pos.z + (scp->battle.look.center * shCosF(scp->rot.y));
    
    
    feel_center[0] = scp->pos.x + (scp->battle.feel.center * shSinF(scp->rot.y));
    feel_center[1] = scp->center_y;
    feel_center[2] = scp->pos.z + (scp->battle.feel.center * shCosF(scp->rot.y));
    
    
    if (scp->kind == LLL_MAR_CHARA_KIND) {
        shQzero(sh2_target_info, sizeof(sh2_target_info));
        rest_tgt = 20;
    }

    
    
    
    for (tgt = sh2chara.head; tgt != NULL; tgt = tgt->next) {
        
        
        if (tgt == scp) continue;        
        switch (GET_KIND_TYPE(tgt->kind)) {
            case HUMAN_CHARA_KIND: case ENEMY_CHARA_KIND: case OBJECT_X_CHARA_KIND: break;            
            default: continue;                
        }            
                        
        if ((GET_KIND_TYPE(tgt->kind) == ENEMY_CHARA_KIND) && !(tgt->battle.status & 0x400)) continue;
          
        shBattleCheckTargetMyArea(&in_area, scp, tgt, look_center, feel_center);
        if ((in_area.look_on == 0 && in_area.feel_on == 0 && in_area.light_on == 0) || rest_tgt == 0) continue;

        sh2_target_info[20 - rest_tgt].in_area = in_area;
        sh2_target_info[20 - rest_tgt].adr.scp = tgt;
        sh2_target_info[20 - rest_tgt].distance = vec3_dist(&scp->pos, &tgt->pos);
        
        rest_tgt--;        
    }    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    for (i = 0; i < 19 - rest_tgt; i++) {
        for (j = 1; j < 20 - rest_tgt; j++) {
            if (sh2_target_info[i].distance > sh2_target_info[j].distance) {
                memcpy(&dummy, &sh2_target_info[i], sizeof(shInAreaTgtInfo));
                memcpy(&sh2_target_info[i], &sh2_target_info[j], sizeof(shInAreaTgtInfo));
                memcpy(&sh2_target_info[j], &dummy, sizeof(shInAreaTgtInfo));
            }
        }
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    if (scp == sh2jms.player) {
        memcpy(sh2_target_info_buf, sh2_target_info, sizeof(sh2_target_info));
        rest_tgt_buf = rest_tgt;
    }

    if (rest_tgt == 20) {
        return 0;
    }
    return 1;
}

SubCharacter* shBattleGetTargetEnemy(SubCharacter* scp) {
    int i;
    SubCharacter* kari_target = NULL;
    CL_VHIT_RESULT eye;

    if (rest_tgt == 20) 
        return NULL;
    

    
    for (i = 0; i < 20 - rest_tgt; i++) {
        
        if (GET_KIND_TYPE(sh2_target_info[i].adr.scp->kind) == ENEMY_CHARA_KIND) {
            
            if (!(sh2_target_info[i].adr.scp->battle.status & 2)) {
                
                shBattleCheckHitEyes(&eye, scp, i, 1);
                
                if ((eye.kind == 3) && (eye.hobj.chara.sc == sh2_target_info[i].adr.scp)) {
                    
                    if (sh2_target_info[i].adr.scp->battle.status & 4) {
                        
                        if (kari_target == NULL) {
                            kari_target = sh2_target_info[i].adr.scp;
                        }
                        continue;
                    }    
                    return sh2_target_info[i].adr.scp;
                
                }
            }
        }
    }
    return kari_target;
}

SubCharacter* shBattleChangeTargetEnemy(SubCharacter* scp, int key) {
    int i; // r16
    float to_target; // r29+0x90
    float rot_tmp; // r29+0x90
    CL_VHIT_RESULT eye; // r29+0x50
    if (rest_tgt == 20)
        return NULL;
    
    
    
    for (i = 0; i < 20 - rest_tgt; i++) {
        
        if (sh2jms.target == sh2_target_info[i].adr.scp)
            continue;
        if (GET_KIND_TYPE(sh2_target_info[i].adr.scp->kind) != ENEMY_CHARA_KIND)
            continue;
        if (sh2_target_info[i].adr.scp->battle.status & 2)
            continue;
        to_target = shAtan2(sh2_target_info[i].adr.scp->pos.z - scp->pos.z, sh2_target_info[i].adr.scp->pos.x - scp->pos.x);
        
        rot_tmp = shAngleRegulate(to_target - scp->rot.y);
        if ((key == 1 && rot_tmp > 0.0f) || (key == -1 && rot_tmp < 0.0f)) {

            shBattleCheckHitEyes(&eye, scp, i, 1);
    
            if (eye.kind == 3) {
                
                return sh2_target_info[i].adr.scp;
            }
                       
        }  


    }
    return NULL;
}

u_int shBattleGetTargetChara(SubCharacter* scp, int kind) {
    int i; // r16
    CL_VHIT_RESULT eye; // r29+0x30

    switch (kind) {
        case 0: // ???
            if (rest_tgt == 20) 
                return 0;
            
            
            
            for (i = 0; i < 20 - rest_tgt; i++) {
                
                shBattleCheckHitEyes(&eye, scp, i, 1);
                
                
                
                
                if ((eye.kind != 1) && ( eye.kind != 2)) {
                    return (u_int) sh2_target_info[i].adr.scp;
                }
            
            }
            break;
        case HUMAN_CHARA_KIND:
            return 0;
    }
    
    return 0;
}

SubCharacter* shCameraGetNearTarget(int i, int type) {
    int kind; // r4

    if (rest_tgt_buf == 20)
        return NULL;
    
    if (sh2_target_info_buf[i].adr.scp != NULL) {
        kind = GET_KIND_TYPE(sh2_target_info_buf[i].adr.scp->kind);
        
        if ((((type == 0)) && (kind == ENEMY_CHARA_KIND)) ||
            ((type == 1) && (kind == OBJECT_X_CHARA_KIND)))             
            return sh2_target_info_buf[i].adr.scp;
    } 
    
    return NULL;

}

SubCharacter* shBattleGetNearDeadlyTargetEnemy(SubCharacter* scp) {
    int i; // r16
    CL_VHIT_RESULT eye; // r29+0x50

    
    if (rest_tgt == 20) 
        return NULL;
    
    
    
    for (i = 0; i < 20 - rest_tgt; i++) {        
        
        if (GET_KIND_TYPE(sh2_target_info[i].adr.scp->kind) == ENEMY_CHARA_KIND) {
            
            if (!(sh2_target_info[i].adr.scp->battle.status & 2) && (sh2_target_info[i].adr.scp->battle.status & 4)) {
                
                
                shBattleCheckHitEyes(&eye, scp, i, 0);
                if ((eye.kind == 3) && (eye.hobj.chara.sc == sh2_target_info[i].adr.scp)) {
                    
                    
                    if (sh2_target_info[i].distance <= 600.0f) {
                        return sh2_target_info[i].adr.scp;
                    }
                }
            }
        }
    }
    
    return NULL;
}

SubCharacter* shBattleGetTargetHuman(SubCharacter* scp, u_int type) {
    sceVu0FVECTOR pos1; // r29+0x30
    sceVu0FVECTOR pos2; // r29+0x40
    float scalar1; float scalar2; 
    SubCharacter* p; SubCharacter* p1; SubCharacter* p2; 
    switch (type) {
        case 1:
            p = shCharacterGetSubCharacter(LLL_JMS_CHARA_KIND, -1);
            if (p == NULL) 
                p = shCharacterGetSubCharacter(HLL_JMS_CHARA_KIND, -1);            
            break;
        case 2:
            p = shCharacterGetSubCharacter(LLL_MAR_CHARA_KIND, -1);
            break;
        default:
            p1 = shCharacterGetSubCharacter(LLL_JMS_CHARA_KIND, -1);
            if (p1 == NULL) {
                p1 = shCharacterGetSubCharacter(HLL_JMS_CHARA_KIND, -1);
            }
            p2 = shCharacterGetSubCharacter(LLL_MAR_CHARA_KIND, -1);
            
            if (p1 != NULL) {
                if (p2 != NULL) {
                    pos1[0] = p1->pos.x - scp->pos.x;
                    pos1[2] = p1->pos.z - scp->pos.z;
                    pos2[0]= p2->pos.x - scp->pos.x;
                    pos2[2] = p2->pos.z - scp->pos.z;
                    scalar1 = vec_length(pos1);
                    scalar2 = vec_length(pos2);
                    p = (scalar1 <= scalar2) ? p1 : p2;
                    break;
                } else p = p1;                                                                      
                
                break;
            } else if (p2 != NULL)
                
                p = p2;                
            else p = NULL;
            
    }
    return p;


}

int shBattleListenHumanSound(SubCharacter* scp, SubCharacter* tgt) {
    if (tgt->battle.status & 0x200) {
        return 1;
    } 
    return 0;
}

int shBattleSeeHumanLight(SubCharacter* scp) {
    SPOT_LIGHT spot; // r29+0x20
    sceVu0FVECTOR light_center; // r29+0x50
    sceVu0FVECTOR scp_center; // r29+0x60
    float angle; // r29+0x70
    float light_radius; // r1    
    float dist; // r29+0x70

    if (item.light_switch == 0) {
        return -1;
    }
    
    
    
    kari_sh2gde_getspotParams(spot.c, spot.zdir, spot.range);

    
    angle = shAtan2(spot.zdir[2], spot.zdir[0]);

    light_center[0] = spot.c[0] + ((0.5f * spot.range[3]) * spot.zdir[0]);
    light_center[1] = spot.c[1] + ((0.5f * spot.range[3]) * spot.zdir[1]);
    light_center[2] = spot.c[2] + ((0.5f * spot.range[3]) * spot.zdir[2]);

    
    light_radius = (0.5f * spot.range[3]) * shSinF(spot.range[1]);

    
    scp_center[0] = scp->pos.x;    
    scp_center[2] = scp->pos.z;
    scp_center[1] = scp->center_y;

    
    dist = vec3_dist_reverse(scp_center, light_center);

    if (dist < light_radius) {
        return 1;
    }
    return 0;
}

int shBattleAimedByHuman(SubCharacter* scp) {
    if ((sh2jms.target == scp) && (sh2jms.lock_on)) {
        return 1;
    }
    return 0;
}

int shBattleFinishedByHuman(SubCharacter* scp) {
    if ((sh2jms.enemy_liedown == scp) && (sh2jms.lower_now == JMS_ST_L_KICK)) {
        return 1;
    }
    return 0;
}

int shBattleNoDamageHuman(void) {
    return shBattleNoDamageHumanJames();
}

int shBattleNoDamageHumanJames(void) {
    if ((sh2jms.no_damage) || (sh2jms.muteki_time)) {
        return 1;
    }
    return 0;
}

int shBattleNoDamageHumanMaria(void) {
    if ((sh2mar.no_damage) || (sh2mar.muteki_time)) {
        return 1;
    }
    return 0;
}

int shBattleHuggedHuman(void) {
    if (sh2jms.hugging_gauge) {
        return 1;
    }
    return 0;
}

void shBattleSetLookArea(SubCharacter* scp, float center, float radius) {
    scp->battle.look.center = 500.0f * center;
    scp->battle.look.radius = 500.0f * radius;
}

void shBattleSetFeelArea(SubCharacter* scp, float center, float radius) {
    scp->battle.feel.center = 500.0f * center;
    scp->battle.feel.radius = 500.0f * radius;
}

void shBattleInitEnemyCheckWork(void) {
    shQzero(sh2_target_info, sizeof(sh2_target_info));
    shQzero(sh2_target_info_buf, sizeof(sh2_target_info_buf));
    rest_tgt = rest_tgt_buf = 20;
}

void shBattleInit(void) {
    shBattleInitEnemyCheckWork();
    shBattleInitAttackQueue();
}

void shBattleExec(void) {
    shBattleExecAttackQueue();
}
