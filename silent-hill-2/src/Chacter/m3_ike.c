#include "sh2_common.h"
#include "vec.h"
#include "Enemy/en_common.h"
#include "Chacter/character.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_ike.h"

static const AnimeInfo ike_anim[] = {
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
        /* .name = */ 5601,
        /* .frame = */ 23,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 22,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5602,
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 23,
        /* .end = */ 54,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5603,
        /* .frame = */ 16,
        /* .speed = */ 1024,
        /* .start = */ 55,
        /* .end = */ 70,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5604,
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 71,
        /* .end = */ 86,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5605,
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 87,
        /* .end = */ 110,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5606,
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 111,
        /* .end = */ 125,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5607,
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 126,
        /* .end = */ 144,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5608,
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 145,
        /* .end = */ 163,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5609,
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 164,
        /* .end = */ 182,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5610,
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 183,
        /* .end = */ 201,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5611,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 202,
        /* .end = */ 234,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5612,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 235,
        /* .end = */ 267,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5613,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 268,
        /* .end = */ 300,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5614,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 301,
        /* .end = */ 333,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5615,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 334,
        /* .end = */ 366,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5616,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 367,
        /* .end = */ 399,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5617,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 400,
        /* .end = */ 432,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5618,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 433,
        /* .end = */ 465,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5619,
        /* .frame = */ 28,
        /* .speed = */ 2048,
        /* .start = */ 466,
        /* .end = */ 493,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5620,
        /* .frame = */ 23,
        /* .speed = */ 2048,
        /* .start = */ 494,
        /* .end = */ 516,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

static const AnimeInfo d_ike_anim[] = {
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
        /* .name = */ 6501,
        /* .frame = */ 42,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 41,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6502,
        /* .frame = */ 778,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 777,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6503,
        /* .frame = */ 93,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 92,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6504,
        /* .frame = */ 641,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 640,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6505,
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 33,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6506,
        /* .frame = */ 661,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 660,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6507,
        /* .frame = */ 778,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 777,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6508,
        /* .frame = */ 93,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 92,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6509,
        /* .frame = */ 641,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 640,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6510,
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 34,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6511,
        /* .frame = */ 661,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 660,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

static int dike_anime_adr_list[] = {
    0, 
    0,
    0, 
    6424, 
    10320, 
    46012, 
    49248, 
    64724, 
    71148, 
    72092, 
    77420, 
    77892 
};

static int EnemyIKEInit(SubCharacter* scp);
static void EnemyIKEFunction(SubCharacter* this);


#line 71
static int EnemyIKEInit(SubCharacter* scp) {
    scp->kind = 515;
    return 0;
}

#line 86
static void EnemyIKEFunction(SubCharacter* this) {
    sceVu0FVECTOR pos, rot;
    EnLOCAL_DATA* dp;
    
    switch (this->step) {
        case 0:
            
            
            
            
            shVectorCopy(pos, &this->pos);
            shVectorCopy(rot, &this->rot);
            
            EnemyIKEInit(this);
            
            if (PlayerNowDemoEventMode() == false) {
            
                SCAnimeTypeSwitch(this, true);
                
                shCharacterEnemyIKEAnimeSetP(this, 5601, 1);
                
                
                
                
                
                
                
                
                if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {
                
                    
                    if ((dp = enEntryEnemy(7)) != NULL) {
                        this->enemy_p = dp;
                        enInitData(dp, this);
                    } 
                    else this->enemy_p = NULL;
                }
            }
            
            
            
            shVectorCopy(&this->pos, pos);
            shVectorCopy(&this->rot, rot);
            
            this->step++;
            /* fallthrough */
        case 1:
            return;
    }

    
}

#line 153
void shCharacterSetEnemyIKELow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyIKEFunction);
}

#line 168
int shCharacterEnemyIKEAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == 515) {
        SCAnimeTypeSwitch(scp, false);
        aip = (AnimeInfo*)&d_ike_anim[anime_id - 6500];
        shCharacterAnimeSet(
            scp, 
            0,
            2,
            aip,
            dike_anime_adr_list[anime_id - 6500] + 
            (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - 6500)
        );
        return 0;
    }
    
    return -1;
}

#line 199
int shCharacterEnemyIKEAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;
    
    
    if (scp->status & (1 << SCP_STATUS_BIT_ANIME_TYPE) && shCharacterGetModelID(scp) == 515) {
        aip = (AnimeInfo*)&ike_anim[anime_id - 5600];

        
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

#line 231
void shGetEnemyIKEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
    sceVu0FVECTOR pos0;
    sceVu0FVECTOR pos1;
    sceVu0FVECTOR vec;
    Matrix4 lw_mat;
    Matrix4 mat;
    int i;
    int sk_num;
    sceVu0FVECTOR wep_range = { 93.0f, 237.0f, 0.0f, 0.0f };
    shSkelton* stp;
    
    lw_mat.d = scp->mat;
    stp = scp->sk_top;
    
    sk_num = 5;
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
    
    sceVu0ApplyMatrix(pos0,  lw_mat.d[0], pos0);
    shVectorCopy(s_pos, pos0);
    
    
    
    sceVu0ApplyMatrix(pos1, mat.d[0], wep_range);
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
