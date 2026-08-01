#include "Chacter/m3_arm.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_arm.h"
#include "sce/libvu0.h"
#include "vec.h"

static const AnimeInfo arm_anim[14] = {
    { // [0]
        /* .name  = */ 0x0000,
        /* .frame = */ 0x0000,
        /* .speed = */ 0x0000,
        /* .start = */ 0x0000,
        /* .end   = */ 0x0000,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [1]
        /* .name  = */ 0x1483,
        /* .frame = */ 0x0031,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0000,
        /* .end   = */ 0x0030,
        /* .loop  = */ 0x01,
        /* .pad   = */ 0x00
    },
    { // [2]
        /* .name  = */ 0x1484,
        /* .frame = */ 0x0011,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0031,
        /* .end   = */ 0x0041,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [3]
        /* .name  = */ 0x1485,
        /* .frame = */ 0x0011,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0042,
        /* .end   = */ 0x0052,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [4]
        /* .name  = */ 0x1486,
        /* .frame = */ 0x0011,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0053,
        /* .end   = */ 0x0063,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [5]
        /* .name  = */ 0x1487,
        /* .frame = */ 0x0011,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0064,
        /* .end   = */ 0x0074,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [6]
        /* .name  = */ 0x1488,
        /* .frame = */ 0x0010,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0075,
        /* .end   = */ 0x0084,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [7]
        /* .name  = */ 0x1489,
        /* .frame = */ 0x0010,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0085,
        /* .end   = */ 0x0094,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [8]
        /* .name  = */ 0x148A,
        /* .frame = */ 0x001F,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0095,
        /* .end   = */ 0x00B3,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [9]
        /* .name  = */ 0x148B,
        /* .frame = */ 0x001F,
        /* .speed = */ 0x0800,
        /* .start = */ 0x00B4,
        /* .end   = */ 0x00D2,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [10]
        /* .name  = */ 0x148C,
        /* .frame = */ 0x001F,
        /* .speed = */ 0x0800,
        /* .start = */ 0x00D3,
        /* .end   = */ 0x00F1,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [11]
        /* .name  = */ 0x148D,
        /* .frame = */ 0x001F,
        /* .speed = */ 0x0800,
        /* .start = */ 0x00F2,
        /* .end   = */ 0x0110,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [12]
        /* .name  = */ 0x148E,
        /* .frame = */ 0x0042,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0111,
        /* .end   = */ 0x0152,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    },
    { // [13]
        /* .name  = */ 0x148F,
        /* .frame = */ 0x0042,
        /* .speed = */ 0x0800,
        /* .start = */ 0x0153,
        /* .end   = */ 0x0194,
        /* .loop  = */ 0x00,
        /* .pad   = */ 0x00
    }
}; // @ 0x00399080

// static struct _AnimeInfo d_arm_anim[1]; // size: 0xC, address: 0x0   unused???
// static signed int darm_anime_adr_list[1]; // size: 0x4, address: 0x0 unused???

static int EnemyARMInit(SubCharacter* this);
static void EnemyARMFunction(SubCharacter* this);

static int EnemyARMInit(SubCharacter* this) {
    return 0;
}

static void EnemyARMFunction(SubCharacter* this) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot;  
    EnLOCAL_DATA* dp;
    switch (this->step) {
        case 0:
            if (this->battle.status & 0x400) {
                
                
                
                volatile_vec_copy(&pos, &this->pos);
                volatile_vec_copy(&rot, &this->rot);
                
                EnemyARMInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                    
                    SCAnimeTypeSwitch(this, 1);
                    
                    shCharacterEnemyARMAnimeSetP(this, ARM_PLAY_ANIM_5251, 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & 4) {

                    
                        if (dp = enEntryEnemy(10)) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } else {
                            this->enemy_p = NULL;
                        }
                    }
                }
                
                volatile_vec_copy(&this->pos, &pos);                
                volatile_vec_copy(&this->rot, &rot);
                
                this->step++;
            }
            /* fallthrough */
        
        
        case 1:
            return;
    }
}

void shCharacterSetEnemyARMLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyARMFunction);
}

int shCharacterEnemyARMAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip; // r18

    if (shCharacterGetModelID(scp) == EN_ARM_CHARA_KIND) {
        aip = (AnimeInfo*)&arm_anim[anime_id - ARM_PLAY_ANIME_ID_START];         
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
    

    mat = *(Matrix4*)stp->src_m.d;       
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
