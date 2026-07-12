#include "Chacter/m3_red.h"
#include "Chacter/m3_sc.h"
#include "Chacter_Draw/model3_equip_n.h"
#include "Enemy/en_common.h"
#include "Enemy/en_red.h"
#include "libvu0.h"
#include "vec.h"

#define D_RED_ANIM_START 6300

// @todo: general clean up

// @todo: migrate rodata

extern /* static */ AnimeInfo red_anim[12]; // size: 0x90, address: 0x0
extern /* static */ AnimeInfo d_red_anim[7]; // size: 0x54, address: 0x0
extern /* static */ int dred_anime_adr_list[7]; // size: 0x1C, address: 0x2A93A0

static int EnemyREDInit(SubCharacter* scp); // not sure about the argument here
static void EnemyREDFunction(SubCharacter* scp);

static int EnemyREDInit(SubCharacter* scp) {
    return 0;
}

static void EnemyREDFunction(SubCharacter* scp) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot; // r29+0x30
    EnLOCAL_DATA* dp; // r2    
    switch (scp->step) {
        case 0:
            if (scp->battle.status & 0x400) {


                
                volatile_vec_copy(&pos, &scp->pos);
                volatile_vec_copy(&rot, &scp->rot);
                
                EnemyREDInit(scp);

                
                if (!PlayerNowDemoEventMode()) {
                    
                    SCAnimeTypeSwitch(scp, 1);
                    shCharacterEnemyREDAnimeSetP(scp,
                                                 0x189D,
                                                 1);







            
                    if (scp->status & 0x4) {
                        
                        dp = enEntryEnemy(4);
                        if (dp != NULL) {
                            scp->enemy_p = dp;
                            enInitData(dp, scp);
                        } else {
                            scp->enemy_p = NULL;
                        }
                    }

                    
                    scp->battle.target = shCharacterGetSubCharacter(0x100, -1);
                }
                
                volatile_vec_copy(&scp->pos, &pos);                
                volatile_vec_copy(&scp->rot, &rot);
                
                scp->step++;                
            }


        
        case 1:
            return;
        }
}

void shCharacterSetEnemyREDLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyREDFunction);
}

void shCharacterSetWeaponRED(SubCharacter* scp, int on_off) {
    sh2gfw_Set_JMSequip(scp, 0, 0, (on_off != 0) ? 3 : 0);
}

int shCharacterEnemyREDAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2

    if (shCharacterGetModelID(scp) == EN_RED_CHARA_KIND) {

        enDeleteEnemy(scp->enemy_p);

        SCAnimeTypeSwitch(scp, 0);
        aip = &d_red_anim[anime_id - D_RED_ANIM_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            dred_anime_adr_list[anime_id - D_RED_ANIM_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - D_RED_ANIM_START));
        
        
        
        return 0;
    }
    return -1;

}

int shCharacterEnemyREDAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */) {
    AnimeInfo* aip; // r18
    
    if (shCharacterGetModelID(scp) == EN_RED_CHARA_KIND) {
        aip = &red_anim[anime_id - 0x14B4];
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));

        
        return 0;
    }
    
    return -1;
}



void shGetEnemyREDAttackPos(SubCharacter* scp /* r2 */, float* s_pos /* r18 */, float* s_vec /* r17 */, u_short atk /* r2 */) {
    sceVu0FVECTOR pos0;
    sceVu0FVECTOR pos1;
    sceVu0FVECTOR vec;
    sceVu0FMATRIX lw_mat;
    Matrix4 mat;
    int i;
    int sk_num;
    shSkelton* stp;
    sceVu0FVECTOR wep_range = { 500.0f, 0.0f, 0.0f, 0.0f };
   
    lw_mat = scp->mat;
    stp = scp->sk_top;
    
    switch (atk) {
        case 0x2C:
        case 0x2D:
            sk_num = 0x24;
            break;
        case 0x2E:
        case 0x2F:
        case 0x30:
            sk_num = 0x19;
            break;
    }
        
    for (i = 0; i < sk_num; i++) {
        stp = stp->next;
    }
    mat = stp->src_m;
    pos0[0] = stp->src_m.d[3][0];
    pos0[1] = stp->src_m.d[3][1];
    pos0[2] = stp->src_m.d[3][2];
    pos0[3] = stp->src_m.d[3][3];
    mat.d[3][0] = 0.0f;
    mat.d[3][3] = 1.0f;
    
    sceVu0ApplyMatrix(&pos0[0], &lw_mat[0], &pos0[0]);
    volatile_vec_copy(s_pos, pos0);
   
    sceVu0ApplyMatrix(&pos1[0], &mat.d[0], &wep_range[0]);
    
    pos1[0] += stp->src_m.d[3][0];
    pos1[1] += stp->src_m.d[3][1];
    pos1[2] += stp->src_m.d[3][2];
    pos1[3] = stp->src_m.d[3][3];
    
    sceVu0ApplyMatrix(&pos1[0], &lw_mat[0], &pos1[0]);
    
    vec[0] = pos1[0] - pos0[0];
    vec[1] = pos1[1] - pos0[1];
    vec[2] = pos1[2] - pos0[2];
    vec[3] = 0.0f;
    
    vec_normalize(vec, s_vec);    
}
