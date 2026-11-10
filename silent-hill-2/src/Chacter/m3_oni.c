#include "Chacter/m3_oni.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_oni.h"
#include "sce/libvu0.h"
#include "vec.h"

static int doni_anime_adr_list[10] = { 
    0, 
    0, 
    0, 
    40256, 
    0, 
    91128, 
    0, 
    164952, 
    304652, 
    48164
}; // size: 0x28, address: 0x34C300

static const AnimeInfo oni_anim[16] = {
    {
        NULL
    },
    {
        /* .name = */ ONI_PLAY_ANIM(1),
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 17,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(2),
        /* .frame = */ 46,
        /* .speed = */ 2048,
        /* .start = */ 18,
        /* .end = */ 63,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(3),
        /* .frame = */ 39,
        /* .speed = */ 2048,
        /* .start = */ 64,
        /* .end = */ 102,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(4),
        /* .frame = */ 25,
        /* .speed = */ 2048,
        /* .start = */ 103,
        /* .end = */ 127,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(5),
        /* .frame = */ 22,
        /* .speed = */ 2048,
        /* .start = */ 128,
        /* .end = */ 149,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(6),
        /* .frame = */ 22,
        /* .speed = */ 2048,
        /* .start = */ 150,
        /* .end = */ 171,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(7),
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 172,
        /* .end = */ 200,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(8),
        /* .frame = */ 22,
        /* .speed = */ 2048,
        /* .start = */ 201,
        /* .end = */ 222,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(9),
        /* .frame = */ 13,
        /* .speed = */ 2048,
        /* .start = */ 223,
        /* .end = */ 235,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(10),
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 236,
        /* .end = */ 264,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(11),
        /* .frame = */ 13,
        /* .speed = */ 2048,
        /* .start = */ 265,
        /* .end = */ 277,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(12),
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 278,
        /* .end = */ 306,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(13),
        /* .frame = */ 29,
        /* .speed = */ 2048,
        /* .start = */ 307,
        /* .end = */ 335,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(14),
        /* .frame = */ 22,
        /* .speed = */ 2048,
        /* .start = */ 336,
        /* .end = */ 357,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_PLAY_ANIM(15),
        /* .frame = */ 2,
        /* .speed = */ 2048,
        /* .start = */ 358,
        /* .end = */ 359,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
}; // size: 0xC0, address: 0x396EA0

static const AnimeInfo d_oni_anim[10] = {
    {
        NULL
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(1),
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(2),
        /* .frame = */ 794,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 793,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(3),
        /* .frame = */ 716,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 715,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(4),
        /* .frame = */ 1670,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1669,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(5),
        /* .frame = */ 771,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 770,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(6),
        /* .frame = */ 170,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 169,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(7),
        /* .frame = */ 1670,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1669,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(8),
        /* .frame = */ 771,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 770,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ONI_DRAMA_ANIM(9),
        /* .frame = */ 170,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 169,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
}; // size: 0x78, address: 0x396F60

static int EnemyONIInit(SubCharacter* scp);
static void EnemyONIFunction(SubCharacter* scp);

static int EnemyONIInit(SubCharacter* this) {
    return false;
}

static void EnemyONIFunction(SubCharacter* this) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot;
    EnLOCAL_DATA* dp;
    switch (this->step) {        
        case 0:
            if (this->battle.status & (1 << 10)) {
                
                
                
                shVectorCopy(&pos, &this->pos);
                shVectorCopy(&rot, &this->rot);
                                
                EnemyONIInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                
                    SCAnimeTypeSwitch(this, 1);
                    shCharacterEnemyONIAnimeSetP(this, ONI_PLAY_ANIM(1), 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {
                    
                        
                        if (dp = enEntryEnemy(EnKIND_ONI)) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } else {
                            this->enemy_p = NULL;
                        }
                    }
                }
                
                
                shVectorCopy(&this->pos, &pos);                
                shVectorCopy(&this->rot, &rot);
                
                this->step++;
            }
              
        
        case 1:
            return;
        
    }
}

void shCharacterSetEnemyONILow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyONIFunction);
}

int shCharacterEnemyONIAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == EN_ONI_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, 0);
        aip = (AnimeInfo*) &d_oni_anim[anime_id - ONI_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            doni_anime_adr_list[anime_id - ONI_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - ONI_DRAMA_ANIME_ID_START));
        
        
        
        return 0;
    }
    return -1;

}

int shCharacterEnemyONIAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;
    
    if (shCharacterGetModelID(scp) == EN_ONI_CHARA_KIND) {
        aip = (AnimeInfo*) &oni_anim[anime_id - ONI_PLAY_ANIME_ID_START];         
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
    
    
        return 0;
    }    
    return -1;

}

void shGetEnemyONIAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
    sceVu0FVECTOR pos0; sceVu0FVECTOR pos1; sceVu0FVECTOR vec;     
    sceVu0FMATRIX lw_mat; Matrix4 mat; 
    int i; int sk_num; shSkelton* stp;
    sceVu0FVECTOR wep_range = { 500.0f, 0.0f, 0.0f, 0.0f };

    
    lw_mat = scp->mat;
    stp = scp->sk_top;
    
    sk_num = 36; 
    for (i = 0; i < sk_num; i++) 
        stp = stp->next;
    

    mat = *(Matrix4*)stp->src_m.d;       
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
