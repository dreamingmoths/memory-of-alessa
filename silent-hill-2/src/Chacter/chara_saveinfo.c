#include "Chacter/chara_saveinfo.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/m3_sc.h"

void shCharacterSetSaveData(Character_Info* chara) {
    SubCharacter* scp; // r16
    int i; // r17

    chara->spray_time = sh2jms.spray_time;
    chara->running_time = sh2jms.running_time;
    chara->tired = sh2jms.tired;
    chara->tired_max = sh2jms.tired_max;
    chara->spirit = sh2jms.spirit;
    chara->weapon = (u_char) sh2jms.weapon;
    chara->spray_set = sh2jms.spray_set;
    i = 0;
    scp = sh2chara.head;
    while (scp != NULL) {
        switch (scp->kind >> 8) {
            case 1:
            case 2:
                SCNowPlayableEventSwitch(scp, 0);
                chara->ci_sc[i].status = scp->status;
                chara->ci_sc[i].sub_status = scp->sub_status;
                chara->ci_sc[i].sub_st = scp->sub_st;
                chara->ci_sc[i].kind = scp->kind;
                chara->ci_sc[i].id = scp->id;
                chara->ci_sc[i].pos = scp->pos;
                chara->ci_sc[i].rot = scp->rot;
                chara->ci_sc[i].pos_spd = scp->pos_spd;
                chara->ci_sc[i].ot_spd = scp->rot_spd;
                chara->ci_sc[i].b_pos = scp->b_pos;
                chara->ci_sc[i].b_rot = scp->b_rot;
                chara->ci_sc[i].en_first_status = scp->en_first_status;
                chara->ci_sc[i].eye_y = scp->eye_y;
                chara->ci_sc[i].center_y = scp->center_y;
                chara->ci_sc[i].spd = scp->spd;
                chara->ci_sc[i].spd_org = scp->spd_org;
                chara->ci_sc[i].spd_y = scp->spd_y;
                chara->ci_sc[i].spd_roty = scp->spd_roty;
                chara->ci_sc[i].battle_hp = scp->battle.hp;
                chara->ci_sc[i].battle_hp_max = scp->battle.hp_max;
                chara->ci_sc[i].battle_hp_rate = scp->battle.hp_rate;
                chara->ci_sc[i].battle_status = scp->battle.status;
                i++;
                break;
            default:
                break;
        }
        scp = scp->next;
    }
    chara->total = i;
}

void shCharacterExtGameData(Character_Info* chara) {
    shCharacter_Manage_Create_After_MC_Load(chara);
}
