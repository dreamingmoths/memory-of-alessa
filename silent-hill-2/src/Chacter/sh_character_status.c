#include "sh_character_status.h"

static void shBattleCheckHitEyes(struct _CL_VHIT_RESULT *eye, struct SubCharacter *scp, int i, int net) {
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

void shBattleCheckTargetMyArea(struct shInArea *in_area, struct SubCharacter *scp, struct SubCharacter *tgt, float *look, float *feel) {
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