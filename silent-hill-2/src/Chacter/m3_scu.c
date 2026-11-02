#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "Enemy/en_common.h"
#include "vec.h"
#include "Chacter/m3_scu.h"
#include "Chacter/m3_sc.h"

static int EnemySCUInit(SubCharacter* scp);
static void EnemySCUFunction(SubCharacter* this);

static const AnimeInfo scu_anim[] = {
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
        /* .name = */ 5001,
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 14,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5002,
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 15,
        /* .end = */ 45,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5003,
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 46,
        /* .end = */ 62,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5004,
        /* .frame = */ 14,
        /* .speed = */ 2048,
        /* .start = */ 63,
        /* .end = */ 76,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5005,
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 77,
        /* .end = */ 100,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5006,
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 77,
        /* .end = */ 100,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5007,
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 101,
        /* .end = */ 120,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5008,
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 121,
        /* .end = */ 153,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5009,
        /* .frame = */ 30,
        /* .speed = */ 2048,
        /* .start = */ 154,
        /* .end = */ 183,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5010,
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 184,
        /* .end = */ 203,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5011,
        /* .frame = */ 21,
        /* .speed = */ 2048,
        /* .start = */ 204,
        /* .end = */ 224,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5012,
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 225,
        /* .end = */ 243,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5013,
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 244,
        /* .end = */ 277,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5014,
        /* .frame = */ 37,
        /* .speed = */ 2048,
        /* .start = */ 278,
        /* .end = */ 314,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5015,
        /* .frame = */ 23,
        /* .speed = */ 2048,
        /* .start = */ 315,
        /* .end = */ 337,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5016,
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 338,
        /* .end = */ 352,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5017,
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 353,
        /* .end = */ 368,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5018,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 369,
        /* .end = */ 397,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5019,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 398,
        /* .end = */ 426,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5020,
        /* .frame = */ 15,
        /* .speed = */ 1700,
        /* .start = */ 427,
        /* .end = */ 441,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5021,
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 442,
        /* .end = */ 470,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5022,
        /* .frame = */ 30,
        /* .speed = */ 2048,
        /* .start = */ 471,
        /* .end = */ 500,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5023,
        /* .frame = */ 36,
        /* .speed = */ 2048,
        /* .start = */ 501,
        /* .end = */ 536,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5024,
        /* .frame = */ 47,
        /* .speed = */ 2048,
        /* .start = */ 537,
        /* .end = */ 583,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5025,
        /* .frame = */ 38,
        /* .speed = */ 2048,
        /* .start = */ 584,
        /* .end = */ 621,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5026,
        /* .frame = */ 38,
        /* .speed = */ 2048,
        /* .start = */ 622,
        /* .end = */ 659,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5027,
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 660,
        /* .end = */ 674,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5028,
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 675,
        /* .end = */ 689,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5029,
        /* .frame = */ 12,
        /* .speed = */ 2048,
        /* .start = */ 690,
        /* .end = */ 701,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5030,
        /* .frame = */ 12,
        /* .speed = */ 2048,
        /* .start = */ 702,
        /* .end = */ 713,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5031,
        /* .frame = */ 2,
        /* .speed = */ 2048,
        /* .start = */ 714,
        /* .end = */ 715,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5032,
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 351,
        /* .end = */ 351,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5033,
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 367,
        /* .end = */ 367,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5034,
        /* .frame = */ 2,
        /* .speed = */ 2048,
        /* .start = */ 716,
        /* .end = */ 717,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 5030,
        /* .frame = */ 61,
        /* .speed = */ 2048,
        /* .start = */ 718,
        /* .end = */ 778,
        /* .loop = */ 1,
        /* .pad = */ 0,
    }
};

static const AnimeInfo d_scu_anim[] = {
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
        /* .name = */ 6001,
        /* .frame = */ 42,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 41,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6002,
        /* .frame = */ 510,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 509,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6003,
        /* .frame = */ 706,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 705,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6004,
        /* .frame = */ 160,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 159,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6005,
        /* .frame = */ 72,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 71,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6006,
        /* .frame = */ 58,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 57,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6007,
        /* .frame = */ 438,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 437,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6008,
        /* .frame = */ 343,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 342,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 6009,
        /* .frame = */ 469,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 468,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

static int dscu_anime_adr_list[] = { 
    0, 
    0,
    0, 
    0, 
    92184, 
    114364, 
    115888, 
    124028, 
    183952, 
    0
};


#line 65
static int EnemySCUInit(SubCharacter* scp) {
    return 0;
}

#line 79
static void EnemySCUFunction(SubCharacter* this) {
    sceVu0FVECTOR pos, rot;
    EnLOCAL_DATA* dp;
    
    switch (this->step) {
        case 0:
            if (this->battle.status & 0x400) {
                
                
                
                shVectorCopy(pos, &this->pos);
                shVectorCopy(rot, &this->rot);
                
                EnemySCUInit(this);
                
                if (PlayerNowDemoEventMode() == 0) {
                
                    SCAnimeTypeSwitch(this, 1);
                    
                    shCharacterEnemySCUAnimeSetP(this, 5002, 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {
                    
                        
                        if ((dp = enEntryEnemy(1)) != NULL) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } 
                        else this->enemy_p = NULL;
                    }
                }
                
    
                
                shVectorCopy(&this->pos, pos);
                shVectorCopy(&this->rot, rot);
                
                this->step++;
            
            
            }
        /* fallthrough */
        case 1:
            return;
    }
}

#line 148
void shCharacterSetEnemySCULow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemySCUFunction);
}

#line 162
int shCharacterEnemySCUAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == 512) {
        SCAnimeTypeSwitch(scp, 0);
        aip = (AnimeInfo*)&d_scu_anim[anime_id - 6000];
        shCharacterAnimeSet(
            scp, 
            0, 
            2, 
            aip, 
            dscu_anime_adr_list[anime_id - 6000] + (int)shCharacterGetAnimeAdrForDrama(scp, anime_id - 6000)
        );

        return 0;
    }
    return -1;
    
}

#line 193
int shCharacterEnemySCUAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == 512) {
        aip = (AnimeInfo*)&scu_anim[anime_id - 5000];
        shCharacterAnimeSet(
            scp,             
            0,
            (char) ((comp == 1) ? 4 : 2),
            aip, 
            (int)shCharacterGetAnimeAdrForPlay(scp)
        );
        return 0;
    }
    return -1;

}

#line 222
void shGetEnemySCUAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
    sceVu0FVECTOR pos0; 
    sceVu0FVECTOR pos1; 
    sceVu0FVECTOR vec;     

 
    
    
    
    pos0[0] = scp->pos.x;
    pos0[1] = -650.0f + scp->pos.y;
    pos0[2] = scp->pos.z;

    shVectorCopy(s_pos, pos0);


    
    
    
    
    
    
    
    switch (atk) {
        case 0:
            pos1[0] = pos0[0] + (900.0f * shSinF(scp->rot.y));
            pos1[2] = pos0[2] + (1000.0f * shCosF(scp->rot.y));
            pos1[1] = pos0[1];
            break;
        case 1:
            pos1[0] = pos0[0] + (900.0f * shSinF(scp->rot.y));
            pos1[2] = pos0[2] + (1000.0f * shCosF(scp->rot.y));
            pos1[1] = pos0[1] - (900.0f * shCosF(0.41887903f));
            break;
        case 2:
            pos1[0] = pos0[0] + (900.0f * shSinF(0.41887903f + scp->rot.y));
            pos1[2] = pos0[2] + (1000.0f * shCosF(0.41887903f + scp->rot.y));
            pos1[1] = pos0[1];
            break;
        case 3:
            pos1[0] = pos0[0] + (900.0f * shSinF(scp->rot.y));
            pos1[2] = pos0[2] + (1000.0f * shCosF(scp->rot.y));
            pos1[1] = pos0[1] + (900.0f * shCosF(0.41887903f));
            break;
        case 4:
            pos1[0] = pos0[0] + (900.0f * shSinF(scp->rot.y - 0.41887903f));
            pos1[2] = pos0[2] + (1000.0f * shCosF(scp->rot.y - 0.41887903f));
            pos1[1] = pos0[1];
            break;
    }
    
    vec[0] = pos1[0] - pos0[0];
    vec[1] = pos1[1] - pos0[1];
    vec[2] = pos1[2] - pos0[2];
    vec[3] = 0;
    shNormalizeVector(vec, s_vec);
}

#line 289
void shEnemySCU_EffectFoot(SubCharacter* scp, int type) {
    sceVu0FMATRIX mat;
    int i1;
    int foot;
    shSkelton* sk;

    
    
    
    
    foot = type ? 20 : 21;
    
    
    sk = scp->sk_top;
    for (i1 = 0; i1 < foot; i1++) 
        sk = sk->next;

    sceVu0MulMatrix(mat, scp->mat[0], &sk->src_m);
    
    
    
    
    
    
    mat[3][1] += 50.0f;
    
    HH_Effect_Object_Ground_Impact_Post_forEnemy(mat[3], type);
}
