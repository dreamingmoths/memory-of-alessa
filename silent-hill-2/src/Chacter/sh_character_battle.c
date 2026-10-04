#include "sh2_common.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2dt.h"

#include "Chacter/sh_character_battle.h"
#include "Chacter/sh_character_status.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_wep.h"
#include "Chacter/m3_scu.h"
#include "Chacter/m3_mkn.h"
#include "Chacter/m3_nse.h"
#include "Chacter/m3_red.h"
#include "Chacter/m3_oni.h"
#include "Chacter/m3_edb.h"
#include "Chacter/m3_pap.h"
#include "Chacter/m3_tyu.h"
#include "Chacter/m3_ike.h"
#include "Chacter/m3_bos.h"
#include "Chacter/m3_arm.h"

#include "Chacter_Draw/sh2_JmsSpot_Man.h"

#include "Collision/cl_main.h"

#include "Effect/ef_common.h"
#include "Effect2/hh_class_object_execute.h"

#include "Enemy/en_edb.h"
#include "Enemy/en_common.h"

#include "Event/item.h"
#include "Event/stg_name.h"

#include "sce/libvu0.h"

#include "SH2_common/sh_vu0.h"

#include "sound/sh_sound.h"

#include "vec.h"

static void shBattleDamageRevise(float* damage, float* shock, SubCharacter* scp, CL_BATTLE_RESULT* result);
static void shBattleSetEffectDamage(SubCharacter* scp, float* pos, float* vec, u_short atk);
static void shBattleSetSoundDamage(SubCharacter* scp, CL_BATTLE_RESULT* result);
static void shBattleAddEffectAttack(SubCharacter* attacker, float* pos, float* vec);
static void shBattleAttackByHumanGunshotTypeA(SubCharacter* attacker , u_short atk);
static void shBattleAttackByHumanGunshotTypeB(SubCharacter* attacker, u_short atk);
static void shBattleAttackByHumanFightType(SubCharacter* attacker, u_short atk);
static void shBattleAttackByHumanFog(SubCharacter* attacker, u_short atk);
static void shBattleAttackByHumanFinish(SubCharacter* attacker, u_short atk);
static void shGetEnemyAttackStartPos(SubCharacter* attacker, u_short atk, float* s_pos, float* s_vec);
static void shBattleAttackByEnemySlash(SubCharacter* attacker, u_short atk);
static void shBattleAttackByEnemyStrike(SubCharacter* attacker, u_short atk);
static void shBattleAttackByEnemyFog(SubCharacter* attacker, u_short atk);
static void shBattleAttackByEnemyBite(void);
static void shBattleAttackByEnemyHug(SubCharacter* attacker, u_short atk);
static void shBattleAttackByEnemyNeedle(SubCharacter* attacker, u_short atk);
static void shBattleAttackByEnemyShot(SubCharacter* attacker, u_short atk);
static void shBattleAddAttackQueue(SubCharacter* scp, u_char wep_no , u_short atk_no);


extern /* static */ struct shAttackInfo sh2_attack_list[66];

// bss

float sh2_battle_wall_hit = 0.0f;
int sh2_battle_attack_check = 0;
shAttackQueue sh2_attack_queue;
static float max_range_1171;
static float min_range_1172;

static void shBattleDamageRevise(float* damage, float* shock, SubCharacter* scp, CL_BATTLE_RESULT* result) {
    if (scp->battle.status & (1 << 6)) {
        *damage = 0.0f;
    } else {
        switch ((u_int) (u_char) result->btlid) {
            case 45:
                scp->battle.hp = -1.0f;
                *damage = sh2_attack_list[(u_char)result->btlid].ap;
                break;
            default:
                *damage = sh2_attack_list[(u_char)result->btlid].ap;
                break;
        }
    }
    *shock = sh2_attack_list[(u_char)result->btlid].sp;
}

static void shBattleSetEffectDamage(SubCharacter* scp, float* pos, float* vec, u_short atk) {
    float vec_tmp[4];
    int atk_type;

    switch (scp->kind) { 
    case EN_RED_CHARA_KIND: case EN_ONI_CHARA_KIND: case ITEM_B_NIK_CHARA_KIND:
        return;
    }

    if (7 >= atk || atk == 52) {
        atk_type = 0;
    } else {
        atk_type = 1;
    }
    
    if (!(atk == 53 || atk == 63 || atk == 62 || atk == 60 || atk == 59 ||
        atk == 58 || atk == 57 || atk == 55 || atk == 54 || atk == 48 ||
        atk == 47 || atk == 37 || atk == 36 || atk == 9 || atk == 8)) {
        vec_copy(vec_tmp,vec);
        HH_Effect_Object_Blood_Splash_Impact_Post(pos, vec_tmp, (u_int)scp, atk_type);        
    }

}

static void shBattleSetSoundDamage(SubCharacter* scp, CL_BATTLE_RESULT* result) {
    int se;
    int type;
    float vol; 

    type = 0;

    switch ((u_char) result->btlid) {
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
            se = 11033;
            vol = 0.8f;
            break;
        case 23:
        case 24:
            se = 11046;
            vol = 0.8f;
            break;
        case 8:
        case 9:
            return;
        case 1:
        case 2:
        case 4:
        case 6:
            type = 1;
        default:
            se = -1;
            break;
    }
    
    
    if (se == -1) {
        if (!(scp->battle.status & 2)) {    
            switch (scp->kind) {
                case EN_SCU_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 12015;
                    vol = 1.0f;
                    break;
                case EN_MKN_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 12501;
                    vol = 1.0f;
                    break;
                
                case EN_NSE_CHARA_KIND:
                case EN_XOO_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 12113;
                    vol = 1.0f;
                    break;
                case EN_LLL_EDI_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 18203;
                    vol = 1.0f;
                    break;
                case EN_IKE_CHARA_KIND:
                    se = ((shRandI() >> 10) % 3) + 18501;
                    vol = 1.0f;
                    break;
                case EN_PAP_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 18301;
                    vol = 0.8f;
                    break;
                case EN_RED_CHARA_KIND:
                case EN_ONI_CHARA_KIND:
                    switch ((u_char) result->btlid) {
                        case 2:
                        case 1:
                            se = 16110;
                            vol = 1.0f;
                            break;
                        case 12:
                        case 13:
                        case 14:
                            se = 16112;
                            vol = 1.0f;
                            break;
                        case 15:
                        case 16:
                        case 17:
                        case 18:
                            se = 16111;
                            vol = 1.0f;
                            break;
                        default:
                            se = ((shRandI() >> 10) % 4) + 16114;
                            vol = 0.8f;
                    }
                                                    
                    break;
                
                
                case EN_TYU_CHARA_KIND:
                    se = ((shRandI() >> 10) % 6) + 12208;
                    vol = 0.5f;
                    break;
                case EN_ARM_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 12254;
                    vol = 1.0f;
                    break;
                case EN_BOS_CHARA_KIND:
                    se = ((shRandI() >> 10) % 4) + 18858;
                    vol = 0.8f;
                    break;
                
                default:
                    se = -1;

            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    if (se > 0) {
        if (type != 0) {
            enSoundSetQueue(scp, se, vol, 0.1f);
        } else {
            SeCallPos(se, vol, result->pos, 0);
        }
    }

}

static void shBattleAddEffectAttack(SubCharacter* attacker, float* pos, float* vec) {
    EFCTSetGunFire(pos, vec);
    EFCTSetGunSmoke(pos);
    sh2gfw_Set_JmsGunLight();
}

static void shBattleAttackByHumanGunshotTypeA(SubCharacter * attacker /* r20 */, u_short atk /* r16 */) {

    float gunpos[4]; // r29+0x60
    float gunvec[4]; // r29+0x70
    u_short cur_frame; // r2
    u_short st; // r2
    u_short ed; // r16
    CL_BATTLE_QUE que; // r29+0x80
    int wep; // r2

    if (atk == 3 || atk == 7) {
        return;
    }

    cur_frame = shCharacterAnimeFrameGet_(attacker, 1);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;

    if (!(cur_frame < st || cur_frame > ed || attacker->battle.atk_result)) {
        shGetJamesWeaponEndPos(gunpos, gunvec);

        que.svs[0] = gunpos[0] + gunvec[0] * sh2_attack_list[atk].min_range;
        que.svs[1] = gunpos[1] + gunvec[1] * sh2_attack_list[atk].min_range;
        que.svs[2] = gunpos[2] + gunvec[2] * sh2_attack_list[atk].min_range;
        que.svs[3] = 1.0f;
        que.sve[0] = gunpos[0] + gunvec[0] * sh2_attack_list[atk].max_range;
        que.sve[1] = gunpos[1] + gunvec[1] * sh2_attack_list[atk].max_range;
        que.sve[2] = gunpos[2] + gunvec[2] * sh2_attack_list[atk].max_range;
        que.sve[3] = 1.0f;
        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        clBattleAddQue(&que);

        attacker->battle.atk_result = 1;
        shBattleAddEffectAttack(attacker, gunpos, gunvec);

        SeCallPos(atk == 6 ? 11048 : 11028, 1.0f, gunpos, 0);

        wep = PlayerNowItemName(sh2jms.weapon);
        ItemWeaponShoot(wep, 1);
        sh2jms.se_on = 1;
        sh2jms.d_shock = 4;
    }

    if (ed < cur_frame) {
        attacker->battle.atk_result = 0;
    }
}

static void shBattleAttackByHumanGunshotTypeB(SubCharacter* attacker, u_short atk) {
    int i; // r16
    sceVu0FVECTOR vec = {0}; // r29+0x70
    sceVu0FVECTOR rot = {0}; // r29+0x80
    sceVu0FVECTOR gunpos; sceVu0FVECTOR gunvec;     
    sceVu0FMATRIX unit; // r29+0xB0
    sceVu0FMATRIX mat; // r29+0xF0    
    float rot_spread; // r21
    float rot_direction; // r22
    u_short cur_frame; // r17
    u_short st; // r2
    u_short ed; // r18
    CL_BATTLE_QUE que; // r29+0x130
    int wep; // r2
    if (atk == 5) {
        return;
    }
    
    cur_frame = shCharacterAnimeFrameGet(attacker);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    
    
    
    if (!(cur_frame < st || cur_frame > ed || attacker->battle.atk_result)) {
        
        
        
        
        shGetJamesWeaponEndPos(gunpos, gunvec);
        rot[1] = shAtan2(gunvec[2], gunvec[0]);
        rot[0] = -shAtan2(vec_length(gunvec), gunvec[1]);
        vu0_unit_matrix(unit);
        shRotMatrixZ(mat, unit, rot[2]); shRotMatrixX(mat, mat, rot[0]); shRotMatrixY(mat, mat, rot[1]);
        
        for (i = 0; i < 10; i++) { 
            
            
            rot_spread = 0.5235988f * shRandF();
            rot_direction = PI * ((2.0f * shRandF()) - 1.0f);
            
            
            vec[2] = shCosF(rot_spread);
            vec[0] = shSinF(rot_spread) * shSinF(rot_direction); 
            vec[1] = -shSinF(rot_spread) * shCosF(rot_direction);
            sceVu0ApplyMatrix(vec, mat, vec);
            
            
            que.svs[0] = gunpos[0] + vec[0] * sh2_attack_list[atk].min_range;
            que.svs[1] = gunpos[1] + vec[1] * sh2_attack_list[atk].min_range;
            que.svs[2] = gunpos[2] + vec[2] * sh2_attack_list[atk].min_range;
            que.svs[3] = 1.0f;
            que.sve[0] = gunpos[0] + vec[0] * sh2_attack_list[atk].max_range;
            que.sve[1] = gunpos[1] + vec[1] * sh2_attack_list[atk].max_range;
            que.sve[2] = gunpos[2] + vec[2] * sh2_attack_list[atk].max_range;
            que.sve[3] = 1.0f;
            que.btlid = atk + 256;
            que.kind = sh2_attack_list[atk].kind;
            que.sc = attacker;
            
            
            
            
            
            clBattleAddQue(&que);
        }
        
        
        attacker->battle.atk_result = 1;
        
        
        shBattleAddEffectAttack(attacker, gunpos, gunvec);
        
        
        SeCallPos(11051, 1.0f, gunpos, 0);
        
        
        
        wep = PlayerNowItemName(sh2jms.weapon);
        ItemWeaponShoot(wep, 1);
        
        sh2jms.se_on = 1;
        
        
        sh2jms.d_shock = 4;
    }
    
    
    
    if (cur_frame > ed) {
        attacker->battle.atk_result = 0;
    }    
}

static void shBattleAttackByHumanFightType(SubCharacter* attacker, u_short atk) {
    int jouken; // r4
    sceVu0FVECTOR s_pos; sceVu0FVECTOR s_vec;     
    u_short cur_frame; 
    u_short st; 
    u_short ed;
    CL_BATTLE_QUE que;    
    cur_frame = shCharacterAnimeFrameGet_(attacker, 1);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    
    
    shGetJamesWeaponStartPos(s_pos,s_vec);
    que.eve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
    que.eve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
    que.eve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
    que.eve[3] = 1.0f;
    
    
    switch (atk) {
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
             if (cur_frame >= st && cur_frame <= ed && !attacker->battle.atk_result)
                jouken = 1;

            else jouken = 0;
            break;
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:    
            if (cur_frame >= st && cur_frame <= ed)
                jouken = 1;

            else jouken = 0;        
            break;
        default:
            return;
    }


    
    if (cur_frame == ed) {
        sh2jms.wep_no_hit_floor = 1;
    
    } else {
        sh2jms.wep_no_hit_floor = 0;
    }
    
    
    if (jouken) {
        
        que.evs[0] = que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range;
        que.evs[1] = que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;    
        que.evs[2] = que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;        
        que.svs[3] = que.evs[3] = 1.0f;
        que.sve[0] = attacker->battle.prev_atk_pos.x;
        que.sve[1] = attacker->battle.prev_atk_pos.y;
        que.sve[2] = attacker->battle.prev_atk_pos.z;
        que.sve[3] = 1.0f;
        
        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        
        
        
        
        
        
        
        
    
        if (attacker->battle.prev_atk_pos.w) {
            clBattleAddQue(&que);
        }
    }
    
    
    
    
    sceVu0CopyVector(&attacker->battle.prev_atk_pos, que.eve);
    
    
    if (cur_frame <= ed) return;
    attacker->battle.atk_result = 0;
    
   
}

void shGetHumanAttackSprayPos(int i, float* s_pos, float* s_vec, float* result) {
    sceVu0FVECTOR pos1; // r29+0x60
    sceVu0FVECTOR vec; // r29+0x70
    float rotx; // r20
    float roty; // r21
    

    
    
    
    
    
    
    
    
    
    roty = shAtan2(s_vec[2], s_vec[0]);
    rotx = shAtan2(vec_length(s_vec), s_vec[1]);
    
    switch (i) {
        case 0:
            pos1[0] = s_pos[0] + (900.0f * shSinF(roty));
            pos1[2] = s_pos[2] + (900.0f * shCosF(roty));
            pos1[1] = s_pos[1] + (900.0f * shSinF(rotx));
            break;
        case 1:
            pos1[0] = s_pos[0] + (900.0f * shSinF(roty));
            pos1[2] = s_pos[2] + (900.0f * shCosF(roty));
            pos1[1] = s_pos[1] + (900.0f * shSinF(0.41887903f + rotx));
            break;
        case 2:
            pos1[0] = s_pos[0] + (900.0f * shSinF(0.41887903f + roty));
            pos1[2] = s_pos[2] + (900.0f * shCosF(0.41887903f + roty));
            pos1[1] = s_pos[1] + (900.0f * shSinF(rotx));
            break;
        case 3:
            pos1[0] = s_pos[0] + (900.0f * shSinF(roty));
            pos1[2] = s_pos[2] + (900.0f * shCosF(roty));
            pos1[1] = s_pos[1] + (900.0f * shSinF(rotx - 0.41887903f));
            break;
        case 4:
            pos1[0] = s_pos[0] + (900.0f * shSinF(roty - 0.41887903f));
            pos1[2] = s_pos[2] + (900.0f * shCosF(roty - 0.41887903f));
            pos1[1] = s_pos[1] + (900.0f * shSinF(rotx));
            break;
    }
    
    vec[0] = pos1[0] - s_pos[0];
    vec[1] = pos1[1] - s_pos[1];
    vec[2] = pos1[2] - s_pos[2];
    vec[3] = 0.0f;
    vec_normalize(vec, result);

    
}

static void shBattleAttackByHumanFog(SubCharacter* attacker /* r18 */, u_short atk /* r17 */) {
    int i; // r16
    sceVu0FVECTOR s_pos; // r29+0x40
    sceVu0FVECTOR s_vec; // r29+0x50
    sceVu0FVECTOR s_vec_result; // r29+0x60
    sceVu0FVECTOR sp_start; // r29+0x70
    sceVu0FVECTOR sp_end; // r29+0x80
    u_short cur_frame; // r2
    u_short st; // r2
    u_short ed; // r2
    CL_BATTLE_QUE que; // r29+0x90
    int wep; // r16
    u_int pow; // r2
    u_int color; // @note: not in dwarf

    if ((atk == 10) || (atk == 11)) {
        attacker->battle.se = 0;
        return;
    }

    if (sh2jms.spray_time == 0.0f) {
        wep = PlayerNowItemName(sh2jms.weapon);
        do {

        } while (ItemWeaponShoot(wep, 1));
        return;
    }

    // @note: some optimized out code here?
    cur_frame = shCharacterAnimeFrameGet_(attacker, 1);
    shGetJamesWeaponEndPos(s_pos, s_vec);

    max_range_1171 = sh2jms.spray_time >= 10.0f 
        ? sh2_attack_list[atk].max_range 
        : 0.1f * (sh2jms.spray_time * sh2_attack_list[atk].max_range);
    min_range_1172 = sh2jms.spray_time >= 10.0f 
        ? sh2_attack_list[atk].min_range 
        : 0.1f * (sh2jms.spray_time * sh2_attack_list[atk].min_range);
    for (i = 0; i < 5; i++) {
        shGetHumanAttackSprayPos(i, &s_pos[0], &s_vec[0], &s_vec_result[0]);
        que.svs[0] = s_pos[0] + (s_vec_result[0] * min_range_1172);
        que.svs[1] = s_pos[1] + (s_vec_result[1] * min_range_1172);
        que.svs[2] = s_pos[2] + (s_vec_result[2] * min_range_1172);
        que.sve[0] = s_pos[0] + (s_vec_result[0] * max_range_1171);
        que.sve[1] = s_pos[1] + (s_vec_result[1] * max_range_1171);
        que.sve[2] = s_pos[2] + (s_vec_result[2] * max_range_1171);
        que.sve[3] = 1.0f;
        que.svs[3] = 1.0f;
        que.btlid = 256 + (short) atk;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        clBattleAddQue(&que);
        if (i == 0) {
            max_range_1171 += 150.0f;
            que.sve[0] = s_pos[0] + (s_vec_result[0] * max_range_1171);
            que.sve[1] = s_pos[1] + (s_vec_result[1] * max_range_1171);
            que.sve[2] = s_pos[2] + (s_vec_result[2] * max_range_1171);
            volatile_vec_copy(sp_start, que.svs);
            vu0_sub_vector(sp_end, que.sve, que.svs);
        }
    }
    switch (playing.spray_pow) {
        case -1:
            color = COLOR_RGBA(64, 0, 64, 255);
            break;
        case 0:
            color = COLOR_RGBA(192, 192, 192, 255);
            break;
        case 1:
            color = COLOR_RGBA(192, 192, 64, 255);
            break;
        case 2:
            color = COLOR_RGBA(64, 255, 64, 255);
            break;
        default:
            ASSERT_ON_LINE(0, 953);
    }

    enEfctSetSpray(sp_start, sp_end, color, 12);
    if (attacker->battle.se == 0) {
        if (!sh2jms.csaw_se_vol) {
            sh2jms.csaw_se_vol = 0.7f;
            SeCallPos(11047, sh2jms.csaw_se_vol, s_pos, 0);
        }
        attacker->battle.se = 1;
    }

    sh2jms.spray_time -= shGetDT();
    if (sh2jms.spray_time <= 0.0f) {
        wep = PlayerNowItemName(sh2jms.weapon);
        do {

        } while (ItemWeaponShoot(wep, 1) != 0);
        sh2jms.spray_time = 0.0f;
    }
    return;
}

static void shBattleAttackByHumanFinish(SubCharacter* attacker, u_short atk) {
    sceVu0FVECTOR s_pos; sceVu0FVECTOR s_vec; // r29+0x90        
    u_short cur_frame; // r16
    u_short st; // r17
    u_short ed; // r18    
    CL_BATTLE_QUE que; // r29+0xA0    
    cur_frame = shCharacterAnimeFrameGet_(attacker, 2);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    
    
    if (atk >= 30) {
        shGetJamesTrampStartPos(s_pos, s_vec);
    } else {
        shGetJamesKickStartPos(s_pos, s_vec);
    }
    que.eve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
    que.eve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
    que.eve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
    que.eve[3] = 1.0f;

    

    if (!(cur_frame < st || cur_frame > ed)) {
    
        
        que.evs[0] = que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range;
        que.evs[1] = que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;   
        que.evs[2] = que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;
        que.sve[0] = attacker->battle.prev_atk_pos.x;
        que.sve[1] = attacker->battle.prev_atk_pos.y;
        que.sve[2] = attacker->battle.prev_atk_pos.z;
        que.svs[3] = que.sve[3] = que.evs[3] = que.eve[3] = 1.0f;

        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        
        
        
        
        
        
        if (attacker->battle.prev_atk_pos.w) {
            clBattleAddQue(&que);
        }
    }
    
    
    sceVu0CopyVector(&attacker->battle.prev_atk_pos, que.eve);


}


static void shGetEnemyAttackStartPos(SubCharacter* attacker, u_short atk, float* s_pos, float* s_vec) {
    
    switch (attacker->kind) {
        
        case EN_SCU_CHARA_KIND:
            shGetEnemySCUAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_MKN_CHARA_KIND:
            shGetEnemyMKNAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_NSE_CHARA_KIND:
        case EN_XOO_CHARA_KIND:
            shGetEnemyNSEAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_RED_CHARA_KIND:
            shGetEnemyREDAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_ONI_CHARA_KIND:
            shGetEnemyONIAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_LLL_EDI_CHARA_KIND:
            shGetEnemyEDBAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_PAP_CHARA_KIND:
            shGetEnemyPAPAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_TYU_CHARA_KIND:
            shGetEnemyTYUAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_IKE_CHARA_KIND:
            shGetEnemyIKEAttackPos(attacker, s_pos, s_vec, atk);
            break;
        case EN_BOS_CHARA_KIND:
            shGetEnemyBOSAttackPos(attacker, s_pos, s_vec, atk);
            break;
        
        case EN_ARM_CHARA_KIND:            
            shGetEnemyARMAttackPos(attacker, s_pos, s_vec, 0);
            shGetEnemyARMAttackPos(attacker, s_pos, s_vec, 1);
            /* fallthrough */
    }
}

static void shBattleAttackByEnemySlash(SubCharacter* attacker, u_short atk) {
    sceVu0FVECTOR s_pos; // r29+0x80
    sceVu0FVECTOR s_vec; // r29+0x90  
    unsigned short cur_frame; // r17    
    unsigned short st; // r18    
    unsigned short ed; // r19        
    CL_BATTLE_QUE que; // r29+0xA0
    cur_frame = shCharacterAnimeFrameGet(attacker);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    
    
    
    
    shGetEnemyAttackStartPos(attacker, atk, s_pos, s_vec);    
    
    que.eve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
    que.eve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
    que.eve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
    que.eve[3] = 1.0f;
    
    
    
    
    
    
    if (!(cur_frame < st || cur_frame > ed)) {
        
        
        
        que.evs[0] = que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range; 
        que.evs[1] = que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;
        que.evs[2] = que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;
        que.svs[3] = que.evs[3] = 1.0f;        
        
        que.sve[0] = attacker->battle.prev_atk_pos.x;
        que.sve[1] = attacker->battle.prev_atk_pos.y;
        que.sve[2] = attacker->battle.prev_atk_pos.z;
        que.sve[3] = 1.0f;
        
        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        
        
        
        
        
        
        
        
        
        clBattleAddQue(&que);
        
        
        
        if (attacker->battle.se == 0) {
            switch (atk) {
                case 38:
                case 39:
                    break;
                
                
                case 44:
                case 45:
                    SeCallPos(16106, 0.7f, s_pos, 0);
                    break;
            }
            
            attacker->battle.se = 1;
        }
    }
    
    
    sceVu0CopyVector(&attacker->battle.prev_atk_pos, que.eve);
}


static void shBattleAttackByEnemyStrike(SubCharacter* attacker, u_short atk) {
    sceVu0FVECTOR s_pos; // r29+0x80
    sceVu0FVECTOR s_vec; // r29+0x90
    u_short cur_frame; // r17
    u_short st; // r18
    u_short ed; // r19    
    CL_BATTLE_QUE que; // r29+0xA0
    cur_frame = shCharacterAnimeFrameGet(attacker);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    
    
    
    shGetEnemyAttackStartPos(attacker, atk, s_pos, s_vec);
    
    que.eve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
    que.eve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
    que.eve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
    que.eve[3] = 1.0f;

    
    
    
    if (!(cur_frame < st || cur_frame > ed || attacker->battle.atk_result)) {
        
        
        que.evs[0] = que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range; 
        que.evs[1] = que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;
        que.evs[2] = que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;
        que.evs[3] = que.svs[3] = 1.0f;        
        que.sve[0] = attacker->battle.prev_atk_pos.x;
        que.sve[1] = attacker->battle.prev_atk_pos.y;
        que.sve[2] = attacker->battle.prev_atk_pos.z;
        que.sve[3] = 1.0f;

        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        
        
        
        
        
        
        
        
        if (attacker->battle.prev_atk_pos.w) {            
            clBattleAddQue(&que);
        }
       
        
        
        if (attacker->battle.se == 0) {
            switch (atk) {
            case 38:
            case 39:
                break;
            
                
            case 40:
            case 42:
                SeCallPos(12102, 0.7f, s_pos, 0);
                break;
            case 41:
            case 43:
                SeCallPos(12101, 0.7f, s_pos, 0);
                break;
            case 49:
                SeCallPos(16108, 0.7f, s_pos, 0);
                break;
            case 50:
                SeCallPos(16109, 0.7f, s_pos, 0);
                break;
            case 56:
                SeCallPos(18500, 1.0f, s_pos, 0);
                break;
            
                
            case 54:
                SeCallPos(((shRandI() >> 10) & 1) + 18504, 1.0f, s_pos, 0);
                
                break;
            case 59:
                SeCallPos(((shRandI() >> 10) & 3) + 18852, 0.7f, s_pos, 0);
                
                break;
            case 61:                
                SeCallPos(((shRandI() >> 10) & 1) + 18850, 0.7f, s_pos, 0);
            }
            
            
            
            attacker->battle.se = 1;
        }
    }
    
    
    sceVu0CopyVector(&attacker->battle.prev_atk_pos, que.eve);





}

static void shBattleAttackByEnemyFog(SubCharacter* attacker, u_short atk) {
    int i;
    sceVu0FVECTOR s_pos; sceVu0FVECTOR s_vec;   
    u_short cur_frame;
    u_short st;
    u_short ed;  
    float max_range;    
    CL_BATTLE_QUE que;


    cur_frame = shCharacterAnimeFrameGet(attacker);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    

    
    
    if (!(cur_frame < st || cur_frame > ed || attacker->battle.atk_result)) {
        
        max_range = ((cur_frame - st) * (500.0f * (BgIsOut(0) ? 3.6f : 1.8f))) / (ed - st);

        for (i = 0; i < 5; i++) {
            
            
            
            
            shGetEnemyAttackStartPos(attacker, (u_short) i, s_pos, s_vec);
            
            que.svs[0] = s_pos[0];
            que.svs[1] = s_pos[1];
            que.svs[2] = s_pos[2];
            que.sve[0] = s_pos[0] + s_vec[0] * max_range;
            que.sve[1] = s_pos[1] + s_vec[1] * max_range;
            que.sve[2] = s_pos[2] + s_vec[2] * max_range;
            que.svs[3] = que.sve[3] = 1.0f;
            
            que.btlid = atk + 256;
            que.kind = sh2_attack_list[atk].kind;
            que.sc = attacker;
            
            
            
            
            
            
            
            clBattleAddQue(&que);
        }
        
        
        
        if (attacker->battle.se == 0) {
            SeCallPos(12000, 0.7f, s_pos, 0);
            attacker->battle.se = 1;
        }
    
    }
}

static void shBattleAttackByEnemyBite(void) {
    return;
}

static void shBattleAttackByEnemyHug(SubCharacter* attacker, u_short atk) {
    sceVu0FVECTOR s_pos; // r29+0x40    
    sceVu0FVECTOR s_vec; // r29+0x50    
    CL_BATTLE_QUE que; // r29+0x60

    
    shGetEnemyAttackStartPos(attacker, atk, s_pos, s_vec);

    que.eve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
    que.eve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
    que.eve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
    que.eve[3] = 1.0f;
        
    
    
    
    
    que.evs[0] = que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range;
    que.evs[1] = que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;   
    que.evs[2] = que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;
    que.evs[3] = que.svs[3] = 1.0f;
    que.sve[0] = attacker->battle.prev_atk_pos.x;
    que.sve[1] = attacker->battle.prev_atk_pos.y;
    que.sve[2] = attacker->battle.prev_atk_pos.z;
    que.sve[3] = 1.0f;
    
    que.btlid = atk + 256;
    que.kind = sh2_attack_list[atk].kind;
    que.sc = attacker;
    
    
    
    
    
    
    
    
    if (attacker->battle.prev_atk_pos.w) {
        clBattleAddQue(&que);
    }
    
    
    sceVu0CopyVector(&attacker->battle.prev_atk_pos, que.eve);
}

static void shBattleAttackByEnemyNeedle(SubCharacter* attacker, u_short atk) {
    int i; // r16
    sceVu0FVECTOR s_pos; sceVu0FVECTOR s_vec;   
    u_short cur_frame; // r2
    u_short st; // r2
    u_short ed; // r2    
    CL_BATTLE_QUE que; // r29+0x70
    cur_frame = shCharacterAnimeFrameGet(attacker);
    st = sh2_attack_list[atk].atk_start;


    
    for (i = 0; i < 2; i++) {
        shGetEnemyAttackStartPos(attacker, (u_short) i, s_pos, s_vec);

        que.sve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
        que.sve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
        que.sve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
        que.sve[3] = 1.0f;
        
        que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range;
        que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;   
        que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;
        que.svs[3] = 1.0f;
        
        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        
        
        
        
        
        
        
        
        
        clBattleAddQue(&que);
        
        
        if (attacker->battle.se == 0) {
            
            SeCallPos(((shRandI() >> 10) & 1) + 12252, 0.8f, s_pos, 0);
            
            attacker->battle.se = 1;
        }

    }
}

static void shBattleAttackByEnemyShot(SubCharacter* attacker, u_short atk) {
    sceVu0FVECTOR s_pos; // r29+0x60
    sceVu0FVECTOR s_vec; // r29+0x70
    u_short cur_frame; // r2
    u_short st; // r2
    u_short ed; // r16    
    CL_BATTLE_QUE que; // r29+128

    cur_frame = shCharacterAnimeFrameGet(attacker);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;
    
    
    if (!(cur_frame < st || cur_frame > ed || attacker->battle.atk_result)) {

        
        shGetEnemyAttackStartPos(attacker, atk, s_pos, s_vec);
        

        que.svs[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].min_range;
        que.svs[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].min_range;
        que.svs[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].min_range;
        que.svs[3] = 1.0f;
        que.sve[0] = s_pos[0] + s_vec[0] * sh2_attack_list[atk].max_range;
        que.sve[1] = s_pos[1] + s_vec[1] * sh2_attack_list[atk].max_range;
        que.sve[2] = s_pos[2] + s_vec[2] * sh2_attack_list[atk].max_range;
        que.sve[3] = 1.0f;        
        que.btlid = atk + 256;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;







        
        clBattleAddQue(&que);
        
        
        
        attacker->battle.atk_result = 1;
        
        if (attacker->kind == EN_LLL_EDI_CHARA_KIND) {
            
            enEDBSetGunFire(attacker->enemy_p);
            
            
            
            SeCallPos(18201, 1.0f, s_pos, 1);
        }
    }
    
    
    
    
    if (ed < cur_frame) {
        attacker->battle.atk_result = 0;
    }
}

static void shBattleAddAttackQueue(SubCharacter* scp, u_char wep_no, u_short atk_no) {
    int no; // r3
    
    if (!sh2_attack_queue.rest)
        ASSERT_ON_LINE(0, 1690);


    
    no = 20 - sh2_attack_queue.rest;  // #define ?
    sh2_attack_queue.queue[no].scp = scp;
    sh2_attack_queue.queue[no].wep_no = wep_no;
    sh2_attack_queue.queue[no].atk_no = atk_no;
    sh2_attack_queue.rest--;
}

void shBattleAttackHitCheckInit(SubCharacter* scp /* r2 */) {
    scp->battle.se = 0;
    scp->battle.prev_atk_pos.w = 0;
    scp->battle.atk_result = 0;
}

void shBattleAttackHitCheckToEnemy(SubCharacter* scp /* r2 */, u_char wep_no /* r2 */, u_short atk_no /* r2 */) {
    shBattleAddAttackQueue(scp, wep_no, atk_no);
}

void shBattleAttackHitCheckToHuman(SubCharacter* scp /* r2 */, u_short atk_no /* r2 */) {
    shBattleAddAttackQueue(scp, 0, atk_no);
}

int shBattleRequestNextAttackIsOk(u_short atk, u_short frame) {

    
    
    switch (atk) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return 0;
        case 1:
        case 2:

            if (!((frame < (sh2_attack_list[atk].atk_start + 9)) || ((frame > sh2_attack_list[atk].atk_end  + 9)))) {
                
                return 1;
            }
            return 0;
        
        
        case 8:
        case 9:
        case 10:
        case 11:
            if (!((frame < (sh2_attack_list[atk].atk_end - 2)) || (frame > sh2_attack_list[atk].atk_end))) {
                return 1;
            }
            return 0;
        
        
        
        case 12:
        case 13:
        case 15:
        case 16:
            if (((frame >= (sh2_attack_list[atk].atk_end + 2)) && ((sh2_attack_list[atk].atk_end + 4) >= frame)) || ( (shCharacterAnimeSpeedGet_(sh2jms.player, 1) < 0))) {
                
                return 1;
            }
            return 0;
        
        
        case 14:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            return 0;
        
        
        default:
            if (!((frame < sh2_attack_list[atk].atk_start) || (frame > sh2_attack_list[atk].atk_end))) {
                
                return 1;
            }
            return 0;    
    }


}

void shBattleGetResult(SubCharacter* scp) {
    CL_BATTLE_RESULT* result;
    float damage_revise; float shock_revise;    
    result = NULL;
    
    while ((result = clBattleGetResult((u_int)scp, result))->atr) {
        switch (result->atr) {
            
                        
            case 1:
                if (result->btlid & 0xFF00) 
                    scp->battle.atk_result = result->atr;
                
                
                
                scp->battle.target = result->obj.en;
                
                if (scp->kind <= HLL_JMS_CHARA_KIND && sh2jms.attack_no < 25) {
                    switch ((u_char) sh2jms.weapon) {
                        case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                        case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                        case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                        case WEAPON_ID(WEAPON_CSAW_CHARA_KIND):
                            sh2jms.d_shock = 1;
                            break;

                    }                
                }                
                break;
            
            
            case 2:
            case 3:
                if (sh2jms.wep_no_hit_floor == 0) {
                    
                    if (scp->kind <= HLL_JMS_CHARA_KIND && sh2jms.attack_no < 25) {
                        switch ((u_char) sh2jms.weapon) {
                            case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                            case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                            case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                            case WEAPON_ID(WEAPON_CSAW_CHARA_KIND):
                                sh2jms.d_shock = 4;
                                break;

                        }
                    }
                    scp->battle.atk_result = result->atr;
                }
                
                
                if (scp->kind <= HLL_JMS_CHARA_KIND) { 
                    if ((result->obj.pl)->pad != 0) {
                        sh2_battle_wall_hit = sh2_attack_list[(u_char)result->btlid].ap;
                    } else {
                        sh2_battle_wall_hit = 0.0f;
                    }
                }
                break;
            
            
            
            
            
            case 4:
                if ((result->btlid & 0xFF00) == 0)
                    break;
                if (scp->kind <= RINU_CHARA_KIND && (u_char) result->btlid >= 25 && (u_char) result->btlid < 35) {
                        
                    
                    break;
                }
    
                
                
                shBattleDamageRevise(&damage_revise, &shock_revise, scp, result);
    
                
                
                
                
                
                if (damage_revise >= 0.0f) {
                    scp->battle.damage += damage_revise;
                }
                if (scp->battle.shock <= shock_revise && scp->battle.id == 0) {
                    scp->battle.shock = shock_revise;
                    sceVu0CopyVector(&scp->battle.pos, result->pos);
                    sceVu0CopyVector(&scp->battle.vec, result->vec);
                    scp->battle.id = (u_char)result->btlid;
                    scp->battle.kind = result->kind;
                    
                    scp->battle.target = result->obj.en;
                }
    
                
                
                
                
                
                
                if (scp->kind <= HLL_JMS_CHARA_KIND && (PlayerChectGuardSuccess() || shBattleNoDamageHuman())) {
                    break;
                }
    
                if (damage_revise > 0.0f) {
                    shBattleSetEffectDamage(scp, result->pos, result->vec, (u_char)result->btlid);
                }
    
                shBattleSetSoundDamage(scp, result);
                
                
                
                
                break;    
            default:
                scp->battle.atk_result = result->atr;

        }
    
    }
}

void shBattleInitAttackQueue(void) {
    shQzero(&sh2_attack_queue, sizeof(shAttackQueue));
    sh2_attack_queue.rest = 20;
    sh2_battle_wall_hit = 0.0f;
}

void shBattleExecAttackQueue(void) {
    int i = 0; // r16


    if (sh2_attack_queue.rest == 20) 
        sh2_battle_attack_check = 0;         
    else 
        sh2_battle_attack_check = 1;
    
    while (sh2_attack_queue.queue[i].scp != NULL) {
        
        if (sh2_attack_queue.queue[i].atk_no >= 36) {
            
            
            switch (sh2_attack_list[sh2_attack_queue.queue[i].atk_no].kind) {
                case 1:
                    shBattleAttackByEnemySlash(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);                    
                    
                    
                    
                    break;
                case 2:
                    shBattleAttackByEnemyStrike(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                case 4:
                    shBattleAttackByEnemyFog(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                case 5:
                    shBattleAttackByEnemyBite();
                    
                    
                    
                    break;
                case 6:
                    shBattleAttackByEnemyHug(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                case 3:
                    
                    switch (sh2_attack_queue.queue[i].atk_no) {
                        case 52:
                        case 51:
                            shBattleAttackByEnemyShot(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                            
                            
                            
                            break;
                        case 41:
                        case 43:
                        case 49:
                            shBattleAttackByEnemyStrike(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                            
                            
                            
                            break;
                        case 64:
                        case 65:
                            shBattleAttackByEnemyNeedle(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                            break;
                        }
                    break;
            
            
            
            
            
            
            
            
            
                        
            }
        } else {
            
            if (sh2_attack_queue.queue[i].atk_no >= 25) {
                shBattleAttackByHumanFinish(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
            
            
            
            } else {                
                switch (sh2_attack_queue.queue[i].wep_no) {
                case 0:
                    ASSERT_ON_LINE(0, 2081); // I dont remember how this works lol
                
                case 1:
                case 3:
                    shBattleAttackByHumanGunshotTypeA(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                case 2:
                    shBattleAttackByHumanGunshotTypeB(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                    shBattleAttackByHumanFightType(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                case 4:
                    shBattleAttackByHumanFog(sh2_attack_queue.queue[i].scp, sh2_attack_queue.queue[i].atk_no);
                    
                    
                    
                    break;
                }
            }
        }
        i++;
    }
}

float shBattleGetJamesHP(void) {
    return sh2jms.player->battle.hp;
}

float shBattleGetJamesHP_Rate(void) {
    return sh2jms.player->battle.hp_rate;
}

void shBattleSetJamesDamage(u_short id /* r2 */, float damage /* r29 */, float* vec /* r2 */) {
    sh2jms.player->battle.damage = damage;
    sh2jms.player->battle.id = id;
    volatile_vec_copy((float *)&sh2jms.player->battle.vec, vec);
}

float shBattleEventWallHitCheck(void) {
    return sh2_battle_wall_hit;
}

int shBattleCheckAttackByEnemy(void) {
    return sh2_battle_attack_check;
}
