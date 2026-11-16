#include "sh2_common.h"
#include "vec.h"
#include "Enemy/en_common.h"
#include "Chacter/character.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_pap.h"

static int EnemyPAPInit(SubCharacter* scp);
static void EnemyPAPFunction(SubCharacter* this);

static const AnimeInfo pap_anim[] = {
    {
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5701,
        /* .frame = */ 22,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 21,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5702,
        /* .frame = */ 28,
        /* .speed = */ 2048,
        /* .start = */ 22,
        /* .end = */ 49,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5703,
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 50,
        /* .end = */ 69,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5704,
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 70,
        /* .end = */ 93,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5705,
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 94,
        /* .end = */ 113,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5706,
        /* .frame = */ 13,
        /* .speed = */ 2048,
        /* .start = */ 114,
        /* .end = */ 126,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5707,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 127,
        /* .end = */ 155,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5708,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 156,
        /* .end = */ 184,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5709,
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 185,
        /* .end = */ 202,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5710,
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 203,
        /* .end = */ 220,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5711,
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 221,
        /* .end = */ 235,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5712,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 236,
        /* .end = */ 264,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5713,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 265,
        /* .end = */ 293,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5714,
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 294,
        /* .end = */ 325,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5715,
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 326,
        /* .end = */ 343,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5716,
        /* .frame = */ 21,
        /* .speed = */ 2048,
        /* .start = */ 344,
        /* .end = */ 364,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5717,
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 365,
        /* .end = */ 396,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5718,
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 397,
        /* .end = */ 428,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5719,
        /* .frame = */ 37,
        /* .speed = */ 2048,
        /* .start = */ 429,
        /* .end = */ 465,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5720,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 466,
        /* .end = */ 494,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5721,
        /* .frame = */ 27,
        /* .speed = */ 2048,
        /* .start = */ 495,
        /* .end = */ 521,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5722,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 522,
        /* .end = */ 554,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5723,
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 555,
        /* .end = */ 572,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5724,
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 573,
        /* .end = */ 603,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5725,
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 604,
        /* .end = */ 621,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5726,
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 622,
        /* .end = */ 641,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5727,
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 642,
        /* .end = */ 665,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5728,
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 666,
        /* .end = */ 685,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

static const AnimeInfo d_pap_anim[] = {
    {
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6601,
        /* .frame = */ 42,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 41,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6602,
        /* .frame = */ 438,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 437,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6603,
        /* .frame = */ 799,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 798,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6604,
        /* .frame = */ 850,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 849,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6605,
        /* .frame = */ 643,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 642,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6606,
        /* .frame = */ 713,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 712,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6607,
        /* .frame = */ 1155,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1154,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

static int dpap_anime_adr_list[] = { 
    0, 
    0, 
    0, 
    33480,
    93408,
    157300,
    205684, 
    259364 
};


#line 65
static int EnemyPAPInit(SubCharacter* scp) {
    scp->kind = 516;
    return 0;
}

#line 80
static void EnemyPAPFunction(SubCharacter* this) {
    Vector4 pos, rot;
    EnLOCAL_DATA* dp;

    switch (this->step) {
        case 0:
            if (this->battle.status & BATTLE_STATS_FLAG_10) {
                
                
                
                shVectorCopy(&pos, &this->pos);
                shVectorCopy(&rot, &this->rot);
                
                EnemyPAPInit(this);
                
                if (PlayerNowDemoEventMode() == false) {
                
                    SCAnimeTypeSwitch(this, true);
                    
                    shCharacterEnemyPAPAnimeSetP(this, 5701, 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {
                    
                        
                        if ((dp = enEntryEnemy(8)) != NULL) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } 
                        else this->enemy_p = NULL;
                    }
                }

                
                shVectorCopy(&this->pos, &pos);
                shVectorCopy(&this->rot, &rot);
                
                this->step++;
            }
            /* fallthrough */
        case 1:
        case 2:
            return;
    }

    
}

#line 149
void shCharacterSetEnemyPAPLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyPAPFunction);
}

#line 164
int shCharacterEnemyPAPAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == 516) {
        SCAnimeTypeSwitch(scp, 0);
        aip = (AnimeInfo*) &d_pap_anim[anime_id - 6600];
        shCharacterAnimeSet(
            scp, 
            0, 
            2, 
            aip, 
            dpap_anime_adr_list[anime_id - 6600] +
            (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - 6600)
        );
        return 0;
    }
    return -1;

}

#line 195
int shCharacterEnemyPAPAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == 516) {
        aip = (AnimeInfo*) &pap_anim[anime_id - 5700];
        shCharacterAnimeSet(
            scp, 
            0, 
            (s_char) ((comp == 1) ? 4 : 2), 
            aip, 
            (int) shCharacterGetAnimeAdrForPlay(scp)
        );
        return 0;
    }
    return -1;

}

#line 224
void shGetEnemyPAPAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
    sceVu0FVECTOR pos0, pos1, vec;
    Matrix4 lw_mat, mat;
    int i, sk_num;
    sceVu0FVECTOR wep_range[2] = {
        { 293.0f, 226.0f, 0.0f, 0.0f }, 
        { -293.0f, 226.0f, 0.0f, 0.0f }
    };
    shSkelton* stp;

    lw_mat.d = scp->mat;
    stp = scp->sk_top;
    
    sk_num = 14;
    for (i = 0; i < sk_num; i++) {
        stp = stp->next;
    }
    
    
    mat = stp->src_m;
    pos0[0] = stp->src_m.d[3][0];
    pos0[1] = stp->src_m.d[3][1];
    pos0[2] = stp->src_m.d[3][2];
    pos0[3] = stp->src_m.d[3][3];
    mat.d[3][0] = mat.d[3][1] = mat.d[3][2] = 0.0f;
    mat.d[3][3] = 1.0f;
    
    sceVu0ApplyMatrix(pos0, lw_mat.d[0], pos0);
    shVectorCopy(s_pos, pos0);
    
    
    
    if (atk == 57) { 
        sceVu0ApplyMatrix(pos1, &mat, &wep_range[0][0]);
    }
    else sceVu0ApplyMatrix(pos1, &mat, &wep_range[1][0]);
    
    pos1[0] += stp->src_m.d[3][0];
    pos1[1] += stp->src_m.d[3][1];
    pos1[2] += stp->src_m.d[3][2];
    pos1[3] = stp->src_m.d[3][3];
    sceVu0ApplyMatrix(pos1, lw_mat.d[0], pos1);
    vec[0] = pos1[0] - pos0[0];
    vec[1] = pos1[1] - pos0[1];
    vec[2] = pos1[2] - pos0[2];
    vec[3] = 0.0f;
    shNormalizeVector(vec, s_vec);
}
