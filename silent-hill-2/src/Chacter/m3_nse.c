#include "Chacter/m3_nse.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_nse.h"
#include "sce/libvu0.h"
#include "vec.h"

static const AnimeInfo nse_anim[27] = { 
    {
        NULL
    },
    {
        /* .name = */ NSE_PLAY_ANIM(1),
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 16,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(2),
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 17,
        /* .end = */ 50,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(3),
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 51,
        /* .end = */ 82,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(4),
        /* .frame = */ 34,
        /* .speed = */ 2048,
        /* .start = */ 83,
        /* .end = */ 116,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(5),
        /* .frame = */ 19,
        /* .speed = */ 2048,
        /* .start = */ 117,
        /* .end = */ 135,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(6),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 136,
        /* .end = */ 168,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(7),
        /* .frame = */ 36,
        /* .speed = */ 2048,
        /* .start = */ 169,
        /* .end = */ 204,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(8),
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 205,
        /* .end = */ 228,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(9),
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 229,
        /* .end = */ 252,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(10),
        /* .frame = */ 25,
        /* .speed = */ 2048,
        /* .start = */ 253,
        /* .end = */ 277,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(11),
        /* .frame = */ 33,
        /* .speed = */ 2048,
        /* .start = */ 278,
        /* .end = */ 310,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(12),
        /* .frame = */ 36,
        /* .speed = */ 2048,
        /* .start = */ 311,
        /* .end = */ 346,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(13),
        /* .frame = */ 21,
        /* .speed = */ 2048,
        /* .start = */ 347,
        /* .end = */ 367,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(14),
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 368,
        /* .end = */ 396,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(15),
        /* .frame = */ 23,
        /* .speed = */ 2048,
        /* .start = */ 397,
        /* .end = */ 419,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(16),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 420,
        /* .end = */ 450,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(17),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 451,
        /* .end = */ 481,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(18),
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 482,
        /* .end = */ 498,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(19),
        /* .frame = */ 30,
        /* .speed = */ 2048,
        /* .start = */ 499,
        /* .end = */ 528,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(20),
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 529,
        /* .end = */ 557,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(21),
        /* .frame = */ 35,
        /* .speed = */ 2048,
        /* .start = */ 558,
        /* .end = */ 592,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(22),
        /* .frame = */ 39,
        /* .speed = */ 2048,
        /* .start = */ 593,
        /* .end = */ 631,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(23),
        /* .frame = */ 11,
        /* .speed = */ 2048,
        /* .start = */ 632,
        /* .end = */ 642,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(24),
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 643,
        /* .end = */ 657,
        /* .loop = */ true,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(25),
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 395,
        /* .end = */ 395,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ NSE_PLAY_ANIM(26),
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 418,
        /* .end = */ 418,
        /* .loop = */ false,
        /* .pad = */ 0,
    }
}; // size: 0x144, address: 0x3965B0

// @note: I am not finding these 2 below on ghidra, unused in this proto?
/*
    extern static AnimeInfo d_nse_anim[1]; // size: 0xC, address: 0x0 
    extern static int dnse_anime_adr_list[1]; // size: 0x4, address: 0x0
*/

static int EnemyNSEInit(SubCharacter* this);
static void EnemyNSEFunction(SubCharacter* this);

static int EnemyNSEInit(SubCharacter* this) {
    return false;
}

static void EnemyNSEFunction(SubCharacter* this) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot;
    EnLOCAL_DATA* dp;
    switch (this->step) {
        case 0:
            if (this->battle.status & (1 << 10)) {
                
                
                
                shVectorCopy(&pos, &this->pos);
                shVectorCopy(&rot, &this->rot);
                
                EnemyNSEInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                    
                    SCAnimeTypeSwitch(this, 1);
                    
                    shCharacterEnemyNSEAnimeSetP(this, NSE_PLAY_ANIM(1), 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    shVectorCopy(&this->pos, &pos);                
                    shVectorCopy(&this->rot, &rot);
    
                    if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {                        
                        
                        
                        if ((dp = enEntryEnemy(EnKIND_NSE))) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } else {
                            this->enemy_p = NULL;
                        }
                    }

                }
                
                this->step++;
            }

        
        case 1:
        case 2:
            break;
    
    }

}

void shCharacterSetEnemyNSELow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyNSEFunction);
}

int shCharacterEnemyNSEAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;
       
    if ((shCharacterGetModelID(scp) == EN_NSE_CHARA_KIND) || (shCharacterGetModelID(scp) == EN_XOO_CHARA_KIND)) {
        
        aip = (AnimeInfo*) &nse_anim[anime_id - NSE_PLAY_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        return 0;
    }
    return -1;

}

void shGetEnemyNSEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
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
    sk_num = 24;
        
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
    shVectorCopy(s_pos, pos0);
   
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
    
    shNormalizeVector(vec, s_vec);    
}
