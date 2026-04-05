#include "sh_character_battle.h"

static void shBattleDamageRevise(float *damage, float *shock, struct SubCharacter *scp, struct _CL_BATTLE_RESULT *result) {
    if (scp->battle.status & 0x40) {
        *damage = 0.0f;
    }
    else{
    switch ((u_int)(u_char)result->btlid) {
        case 0x2D:
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

static void shBattleSetEffectDamage(struct SubCharacter *scp, float *pos, float *vec, u_short atk) {
    float vec_tmp[4];
    int atk_type;

    switch (scp->kind) { 
    case 0x208: case 0x209: case 0x421:
        return;
    }

    if (7 >= atk || atk == 0x34) {
        atk_type = 0;
    } else {
        atk_type = 1;
    }
    
    if (!(atk == 0x35 || atk == 0x3F || atk == 0x3E || atk == 0x3C || atk == 0x3B ||
        atk == 0x3A || atk == 0x39 || atk == 0x37 || atk == 0x36 || atk == 0x30 ||
        atk == 0x2F || atk == 0x25 || atk == 0x24 || atk == 0x9 || atk == 0x8)) {
        vec_copy(vec_tmp,vec);
        HH_Effect_Object_Blood_Splash_Impact_Post(pos, vec_tmp, (u_int)scp, atk_type);        
    }

}

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleSetSoundDamage);

static void shBattleAddEffectAttack(struct SubCharacter *attacker, float *pos, float *vec) {
    EFCTSetGunFire(pos, vec);
    EFCTSetGunSmoke(pos);
    sh2gfw_Set_JmsGunLight();
}

static void shBattleAttackByHumanGunshotTypeA(struct SubCharacter * attacker /* r20 */, u_short atk /* r16 */) {

    float gunpos[4]; // r29+0x60
    float gunvec[4]; // r29+0x70
    u_short cur_frame; // r2
    u_short st; // r2
    u_short ed; // r16
    struct _CL_BATTLE_QUE que; // r29+0x80
    int wep; // r2

    if (atk == 3 || atk == 7) {
        return;
    }

    cur_frame = shCharacterAnimeFrameGet_(attacker, 1);
    st = sh2_attack_list[atk].atk_start;
    ed = sh2_attack_list[atk].atk_end;

    if (!(cur_frame < st || cur_frame > ed || attacker->battle.atk_result != 0)) {
        shGetJamesWeaponEndPos(gunpos, gunvec);

        que.svs[0] = gunpos[0] + gunvec[0] * sh2_attack_list[atk].min_range;
        que.svs[1] = gunpos[1] + gunvec[1] * sh2_attack_list[atk].min_range;
        que.svs[2] = gunpos[2] + gunvec[2] * sh2_attack_list[atk].min_range;
        que.svs[3] = 1.0f;
        que.sve[0] = gunpos[0] + gunvec[0] * sh2_attack_list[atk].max_range;
        que.sve[1] = gunpos[1] + gunvec[1] * sh2_attack_list[atk].max_range;
        que.sve[2] = gunpos[2] + gunvec[2] * sh2_attack_list[atk].max_range;
        que.sve[3] = 1.0f;
        que.btlid = atk + 0x100;
        que.kind = sh2_attack_list[atk].kind;
        que.sc = attacker;
        clBattleAddQue(&que);

        attacker->battle.atk_result = 1;
        shBattleAddEffectAttack(attacker, gunpos, gunvec);

        SeCallPos(atk == 6 ? 0x2B28 : 0x2B14, 1.0f, gunpos, 0);

        wep = PlayerNowItemName(sh2jms.weapon);
        ItemWeaponShoot(wep, 1);
        sh2jms.se_on = 1;
        sh2jms.d_shock = 4;
    }

    if (ed < cur_frame) {
        attacker->battle.atk_result = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByHumanGunshotTypeB);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByHumanFightType);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shGetHumanAttackSprayPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByHumanFog);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByHumanFinish);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shGetEnemyAttackStartPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemySlash);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemyStrike);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemyFog);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemyBite);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemyHug);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemyNeedle);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackByEnemyShot);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAddAttackQueue);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackHitCheckInit);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackHitCheckToEnemy);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleAttackHitCheckToHuman);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleRequestNextAttackIsOk);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleGetResult);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleInitAttackQueue);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleExecAttackQueue);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleGetJamesHP);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleGetJamesHP_Rate);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleSetJamesDamage);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleEventWallHitCheck);

INCLUDE_ASM("asm/nonmatchings/Chacter/sh_character_battle", shBattleCheckAttackByEnemy);