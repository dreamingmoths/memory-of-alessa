#include "Chacter/sh_character_status.h"
#include "Collision/cl_main.h"
#include "Chacter_Draw/sh2gfw_model_light.h"
#include "Chacter/sh_character_battle.h"

static void shBattleCheckHitEyes(CL_VHIT_RESULT* eye, SubCharacter* scp, int i, int net);
static float _shLength(float* v0 /* r2 */, float* v1 /* r2 */);

static void shBattleCheckHitEyes(CL_VHIT_RESULT* eye, SubCharacter* scp, int i, int net) {
    float sp[4];
    float ep[4];

    sp[0] = scp->pos.x;
    sp[1] = scp->eye_y;
    sp[2] = scp->pos.z;

    if ((sh2_target_info[i].adr.scp->kind >> 8) == 7) {
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
    float tgt_pos[4];
    float tgt_to_look;
    float tgt_to_feel;

    if ((tgt->kind >> 8) == 7) {
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

    switch (tgt->kind >> 8) {
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

static float _shLength(float* v0, float* v1) {
    float r;

    asm volatile("
        lwc1 %0, 0(%1)
        lwc1 f8, 0(%2)
        lwc1 f9, 4(%1)
        sub.s %0,%0,f8
        lwc1 f10, 4(%2)
        mula.s %0, %0
        lwc1 %0, 8(%1)
        lwc1 f8, 8(%2)
        sub.s f9,f9,f10
        sub.s %0,%0,f8
        madda.s f9, f9
        madd.s %0, %0,%0
        sqrt.s %0,%0"
        : "+f"(r) : "r"(v0), "r"(v1) : "f8", "f9", "f10");

    return r;
}

int shBattleAroundTargetEnemy(void) {
    SubCharacter* tgt = sh2chara.head; 

    while (tgt != NULL) {
        if ((tgt->kind >> 8) == 2) {
            if ((tgt->battle.status & 0x400) && !(tgt->battle.status & 2)) {
                return 1;
            }
        }
        tgt = tgt->next;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_status", shBattleCheckTargetChara);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_status", shBattleGetTargetEnemy);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_status", shBattleChangeTargetEnemy);

u_int shBattleGetTargetChara(SubCharacter* scp, int kind) {
    int i; // r16
    struct _CL_VHIT_RESULT eye; // r29+0x30
    
    switch (kind) {
        case 0:
            if (rest_tgt == 0x14) {
                return 0;
            }

                        
            for (i = 0; i < (0x14 - rest_tgt); i++) {
                
                shBattleCheckHitEyes(&eye, scp, i, 1);  



                
                if ((eye.kind != 1) && (eye.kind != 2)) {
                    return (u_int) sh2_target_info[i].adr.scp;
                }
            
            }
            break;
        case 1:
            return 0;
    
    }
    return 0;
}

SubCharacter* shCameraGetNearTarget(int i, int type) {
    int kind; // r4
    
    if (rest_tgt_buf == 0x14) {
        return NULL;
    }
    if (sh2_target_info_buf[i].adr.scp != NULL) {
        kind = sh2_target_info_buf[i].adr.scp->kind >> 8;
        
        if ((type == 0 && kind == 2) || (type == 1 && kind == 7)) {
            
            return sh2_target_info_buf[i].adr.scp;            
        }        
    }
    return NULL;
    
}

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_status", shBattleGetNearDeadlyTargetEnemy);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_status", shBattleGetTargetHuman);

int shBattleListenHumanSound(SubCharacter* scp, SubCharacter* tgt) {
    if (tgt->battle.status & 0x200) {
        return 1;
    }
    
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_status", shBattleSeeHumanLight);

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
    if (sh2jms.no_damage || sh2jms.muteki_time) {
        return 1;
    } 
    return 0;  
}

int shBattleNoDamageHumanMaria(void) {
    if ((sh2mar.no_damage != 0) || (sh2mar.muteki_time)) {
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
    rest_tgt_buf = 0x14;
    rest_tgt = 0x14;
}

void shBattleInit(void) {
    shBattleInitEnemyCheckWork();
    shBattleInitAttackQueue();
}

void shBattleExec(void) {
    shBattleExecAttackQueue();
}
