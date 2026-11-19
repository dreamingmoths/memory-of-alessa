#include "Chacter/m3_ike.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "sce/libvu0.h"
#include "vec.h"

static const AnimeInfo ike_anim[21] = {
    {
        NULL
    },
    {
        /* .name = */ IKE_PLAY_ANIM(1),
        /* .frame = */ 23,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 22,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(2),
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 23,
        /* .end = */ 54,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(3),
        /* .frame = */ 16,
        /* .speed = */ 1024,
        /* .start = */ 55,
        /* .end = */ 70,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(4),
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 71,
        /* .end = */ 86,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(5),
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 87,
        /* .end = */ 110,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(6),
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 111,
        /* .end = */ 125,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(7),
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 126,
        /* .end = */ 144,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(8),
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 145,
        /* .end = */ 163,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(9),
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 164,
        /* .end = */ 182,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(10),
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 183,
        /* .end = */ 201,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(11),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 202,
        /* .end = */ 234,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(12),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 235,
        /* .end = */ 267,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(13),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 268,
        /* .end = */ 300,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(14),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 301,
        /* .end = */ 333,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(15),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 334,
        /* .end = */ 366,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(16),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 367,
        /* .end = */ 399,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(17),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 400,
        /* .end = */ 432,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(18),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 433,
        /* .end = */ 465,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(19),
        /* .frame = */ 28,
        /* .speed = */ 2048,
        /* .start = */ 466,
        /* .end = */ 493,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_PLAY_ANIM(20),
        /* .frame = */ 23,
        /* .speed = */ 2048,
        /* .start = */ 494,
        /* .end = */ 516,
        /* .loop = */ false,
        /* .pad = */ 0,
    }
};

static const AnimeInfo d_ike_anim[12] = {
    {
        NULL
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(1),
        /* .frame = */ 42,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 41,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(2),
        /* .frame = */ 778,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 777,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(3),
        /* .frame = */ 93,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 92,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(4),
        /* .frame = */ 641,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 640,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(5),
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 33,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(6),
        /* .frame = */ 661,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 660,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(7),
        /* .frame = */ 778,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 777,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(8),
        /* .frame = */ 93,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 92,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(9),
        /* .frame = */ 641,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 640,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(10),
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 34,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ IKE_DRAMA_ANIM(11),
        /* .frame = */ 661,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 660,
        /* .loop = */ false,
        /* .pad = */ 0,
    }
};

static int dike_anime_adr_list[12] = {
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
    scp->kind = EN_IKE_CHARA_KIND;
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
                
                shCharacterEnemyIKEAnimeSetP(this, IKE_PLAY_ANIM(1), 1);
                
                
                
                
                
                
                
                
                if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {
                
                    
                    if ((dp = enEntryEnemy(EnKIND_IKE)) != NULL) {
                        this->enemy_p = dp;
                        enInitData(dp, this);
                    } 
                    else this->enemy_p = NULL;
                }
            }
            
            
            
            shVectorCopy(&this->pos, pos);
            shVectorCopy(&this->rot, rot);
            
            this->step++;
            
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

    if (shCharacterGetModelID(scp) == EN_IKE_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, false);
        aip = (AnimeInfo*) &d_ike_anim[anime_id - IKE_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(
            scp, 
            0,
            2,
            aip,
            dike_anime_adr_list[anime_id - IKE_DRAMA_ANIME_ID_START] + 
            (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - IKE_DRAMA_ANIME_ID_START)
        );
        return 0;
    }
    
    return -1;
}

#line 199
int shCharacterEnemyIKEAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;
    
    
    if (scp->status & (1 << SCP_STATUS_BIT_ANIME_TYPE) && shCharacterGetModelID(scp) == EN_IKE_CHARA_KIND) {
        aip = (AnimeInfo*) &ike_anim[anime_id - IKE_PLAY_ANIME_ID_START];

        
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
