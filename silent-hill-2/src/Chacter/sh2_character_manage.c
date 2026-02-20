#include "sh2_common.h"
#include "Chacter/character.h"

#include "m3_sc.h"

#ifdef NON_MATCHING
int shCharacter_Manage_SetDataAdresss(SubCharacter *scp)
{
    sh2gfw_ModelDraw_MAN *pMD;
    SubCharacterDisp *scp_d = (SubCharacterDisp *)scp;

    if (scp_d == NULL)
    {
        return 0;
    }

    pMD = sh2gfw_Get_pMD((s64)scp_d->sc.kind);
    if (pMD == NULL)
    {
        return 0;
    }

    if (scp_d->model_adr == NULL)
    {
        SCSetModel(&scp_d->sc, (u64)pMD->sh_Model, (u64)pMD->pAnime);
        scp_d->model_adr = (u64)pMD->sh_Model;
        scp_d->anime_adr = (u64)pMD->pAnime;
        scp_d->clani_adr = (u64)pMD->pCluster;
        (scp_d->anime).anime = (void *)scp_d->anime_adr;
        scp_d->sc.function(&scp_d->sc);
    }
    else
    {
        scp_d->model_adr = (u64)pMD->sh_Model;
        scp_d->anime_adr = (u64)pMD->pAnime;
        scp_d->clani_adr = (u64)pMD->pCluster;
        (scp_d->anime).anime = (void *)scp_d->anime_adr;
        scp_d->models[0] = (void *)scp_d->model_adr;
        scp_d->models[1] = (void *)scp_d->model_adr;
        scp_d->models[2] = (void *)scp_d->model_adr;
    }

    return 1;
}
#endif

// E:\work\sh2(CVS全取得)\src\Chacter\sh_character_status.c
extern void shBattleInitEnemyCheckWork();
// E:\work\sh2(CVS全取得)\src\Chacter\sh2_character_manage.c
extern int id_counter; // size: 0x4, address: 0x116DB70

void shCharacter_Manage_Init() {
    id_counter = 0x1000;
    shBattleInitEnemyCheckWork();
}

// E:\work\sh2(CVS全取得)\src\Enemy\en_common.c
extern void enDeleteEnemy(EnLOCAL_DATA * dp /* r2 */);

int shCharacter_Manage_Delete(struct SubCharacter * scp /* r2 */, short kind /* r2 */, short id /* r2 */) {
    SubCharacter * del_scp; // r16

    int delete_on = 0; // r7

    if (scp != NULL) {
        del_scp = scp;
    } else {
        for (del_scp = sh2chara.head; del_scp != NULL; del_scp = del_scp->next) {
            if (del_scp->kind == kind && del_scp->id == id) {
                delete_on = 1;
                break;
            }
        }
        if (delete_on == 0) {
            del_scp = NULL;
        }
    }

    if (del_scp == NULL) {
        return 0;
    }

    if (del_scp->kind >> 8 == 2 || del_scp->kind == 0x421) {
        enDeleteEnemy(del_scp->enemy_p);
    }

    shCharacterDelete(del_scp);

    return 1;
}

struct SubCharacter* shCharacter_Manage_GetCharacterList() {
    return sh2chara.head;
}

#define COPY_VEC4(dst, src) \
do { \
    float w, z, y, x; \
    x = (src).x; \
    y = (src).y; \
    z = (src).z; \
    w = (src).w; \
    (dst).x = x; \
    (dst).y = y; \
    (dst).z = z; \
    (dst).w = w; \
} while (0)

int shCharacter_Manage_Create_After_MC_Load(Character_Info* chara) {
    SubCharacter * scp; // r2
    int i; // r16
    
    for (i = 0; i < chara->total; i++) {
        scp = (SubCharacter*) shCharacterCreate(0, 0, 0, 0, chara->ci_sc[i].kind);



        scp->status = chara->ci_sc[i].status;
        scp->sub_status = chara->ci_sc[i].sub_status;
        scp->sub_st = chara->ci_sc[i].sub_st;
        scp->id = chara->ci_sc[i].id;
        COPY_VEC4(scp->pos, chara->ci_sc[i].pos);
        COPY_VEC4(scp->rot, chara->ci_sc[i].rot);
        COPY_VEC4(scp->pos_spd, chara->ci_sc[i].pos_spd);
        COPY_VEC4(scp->rot_spd, chara->ci_sc[i].ot_spd);
        COPY_VEC4(scp->b_pos, chara->ci_sc[i].b_pos);
        COPY_VEC4(scp->b_rot, chara->ci_sc[i].b_rot);
        scp->en_first_status = chara->ci_sc[i].en_first_status;
        scp->eye_y = chara->ci_sc[i].eye_y;
        scp->center_y = chara->ci_sc[i].center_y;
        scp->spd = chara->ci_sc[i].spd;
        scp->spd_org = chara->ci_sc[i].spd_org;
        scp->spd_y = chara->ci_sc[i].spd_y;
        scp->spd_roty = chara->ci_sc[i].spd_roty;
        scp->battle.hp = chara->ci_sc[i].battle_hp;
        scp->battle.hp_max = chara->ci_sc[i].battle_hp_max;
        scp->battle.hp_rate = chara->ci_sc[i].battle_hp_rate;
        scp->battle.status = chara->ci_sc[i].battle_status;
        if (chara->ci_sc[i].battle_status & 2) {
            scp->en_first_status = 5;
        }
    }



    
    sh2jms.tired = chara->tired;
    sh2jms.tired_max = chara->tired_max;
    sh2jms.spirit = chara->spirit;
    sh2jms.weapon = chara->weapon;
    sh2jms.spray_time = chara->spray_time;
    sh2jms.running_time = chara->running_time;
    sh2jms.tired = chara->tired;
    sh2jms.tired_max = chara->tired_max;
    sh2jms.spirit = chara->spirit;
    sh2jms.weapon = chara->weapon;
    sh2jms.spray_set = chara->spray_set;
    sh2jms.room_name_prev = -1;

    return (int) scp;
}
