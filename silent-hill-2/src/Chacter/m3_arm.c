#include "Chacter/m3_arm.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_arm.h"
#include "sce/libvu0.h"
#include "vec.h"

static const AnimeInfo arm_anim[14] = {
    {
        NULL
    },
    {
        /* .name = */ ARM_PLAY_ANIM(1),
        /* .frame = */ 49,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 48,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(2),
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 49,
        /* .end = */ 65,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(3),
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 66,
        /* .end = */ 82,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(4),
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 83,
        /* .end = */ 99,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(5),
        /* .frame = */ 17,
        /* .speed = */ 2048,
        /* .start = */ 100,
        /* .end = */ 116,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(6),
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 117,
        /* .end = */ 132,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(7),
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 133,
        /* .end = */ 148,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(8),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 149,
        /* .end = */ 179,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(9),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 180,
        /* .end = */ 210,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(10),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 211,
        /* .end = */ 241,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(11),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 242,
        /* .end = */ 272,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(12),
        /* .frame = */ 66,
        /* .speed = */ 2048,
        /* .start = */ 273,
        /* .end = */ 338,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ ARM_PLAY_ANIM(13),
        /* .frame = */ 66,
        /* .speed = */ 2048,
        /* .start = */ 339,
        /* .end = */ 404,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
}; // @ 0x00399080

// static struct _AnimeInfo d_arm_anim[1]; // size: 0xC, address: 0x0 unused???
// static int darm_anime_adr_list[1]; // size: 0x4, address: 0x0 unused???

static int EnemyARMInit(SubCharacter* this);
static void EnemyARMFunction(SubCharacter* this);

static int EnemyARMInit(SubCharacter* this) {
    return false;
}

static void EnemyARMFunction(SubCharacter* this) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot;  
    EnLOCAL_DATA* dp;
    switch (this->step) {
        case 0:
            if (this->battle.status & (1 << 10)) {
                
                
                
                shVectorCopy(&pos, &this->pos);
                shVectorCopy(&rot, &this->rot);
                
                EnemyARMInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                    
                    SCAnimeTypeSwitch(this, 1);
                    
                    shCharacterEnemyARMAnimeSetP(this, ARM_PLAY_ANIM(1), 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {

                    
                        if (dp = enEntryEnemy(EnKIND_ARM)) {
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
            break;
    }
}

void shCharacterSetEnemyARMLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyARMFunction);
}

int shCharacterEnemyARMAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == EN_ARM_CHARA_KIND) {
        aip = (AnimeInfo*) &arm_anim[anime_id - ARM_PLAY_ANIME_ID_START];         
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        return 0;
    }    
    return -1;

}

void shGetEnemyARMAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
    sceVu0FVECTOR pos0; sceVu0FVECTOR pos1; sceVu0FVECTOR vec;     
    sceVu0FMATRIX lw_mat; Matrix4 mat; 
    int i; int sk_num; shSkelton* stp;
    sceVu0FVECTOR wep_range = { 500.0f, 0.0f, 0.0f, 0.0f };
    
    
    lw_mat = scp->mat;
    stp = scp->sk_top;
   
    switch (atk) { 
        case 0:
            sk_num = 13;
            break;
        case 1:
            sk_num = 14;
            break;
    }    
    for (i = 0; i < sk_num; i++) 
        stp = stp->next;
    

    mat = *(Matrix4*) stp->src_m.d;       
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
