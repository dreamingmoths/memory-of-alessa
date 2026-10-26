#include "Chacter/m3_tyu.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_tyu.h"
#include "sce/libvu0.h"
#include "vec.h"

// @todo: migrate rodata (previously had issues -Piccio 05/08/2026 )

extern /* static */ AnimeInfo tyu_anim[3];

/*
static const AnimeInfo tyu_anim[3] = {
    { // [0]
         .name  =  0x0000,
         .frame =  0x0000,
         .speed =  0x0000,
         .start =  0x0000,
         .end   =  0x0000,
         .loop  =  0x00,
         .pad   =  0x00
    },
    { // [1]
         .name  =  0x1451,
         .frame =  0x0001,
         .speed =  0x0800,
         .start =  0x0000,
         .end   =  0x0001,
         .loop  =  0x01,
         .pad   =  0x00
    },
    { // [2]
         .name  =  0x1452,
         .frame =  0x0008,
         .speed =  0x0800,
         .start =  0x0000,
         .end   =  0x0007,
         .loop  =  0x01,
         .pad   =  0x00
    }
}; // @ 0x00396CF0
*/

// static struct _AnimeInfo d_tyu_anim[1]; // size: 0xC, address: 0x0
// static int dtyu_anime_adr_list[1]; // size: 0x4, address: 0x0

static int EnemyTYUInit(SubCharacter* this);
static void EnemyTYUFunction(SubCharacter* this);

static int EnemyTYUInit(SubCharacter* this) {
    return 0;
}

static void EnemyTYUFunction(SubCharacter* this) {
    sceVu0FVECTOR pos; // r29+0x20
    sceVu0FVECTOR rot; // r29+0x30
    EnLOCAL_DATA* dp; // r2
    switch (this->step) {        
        case 0:
            if (this->battle.status & 0x400) {
                
                
                
                shVectorCopy(&pos, &this->pos);
                shVectorCopy(&rot, &this->rot);
                                
                EnemyTYUInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                
                    SCAnimeTypeSwitch(this, 1);
                    
                    shCharacterEnemyTYUAnimeSetP(this, TYU_PLAY_ANIM_5201, 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & 4) {
                    
                        
                        if (dp = enEntryEnemy(3)) {
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
        /* fallthrough */        
        case 1:
            return;
        
    }
}

void shCharacterSetEnemyTYULow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyTYUFunction);
}

int shCharacterEnemyTYUAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip; // r18
    
    if (shCharacterGetModelID(scp) == EN_TYU_CHARA_KIND) {
        aip = (AnimeInfo*)&tyu_anim[anime_id - TYU_PLAY_ANIME_ID_START];         
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
    
    
        return 0;
    }    
    return -1;

}

void shGetEnemyTYUAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk) {
    sceVu0FVECTOR pos0; sceVu0FVECTOR pos1; sceVu0FVECTOR vec;     
    sceVu0FMATRIX lw_mat; Matrix4 mat; 
    int i; int sk_num; shSkelton* stp;
    sceVu0FVECTOR wep_range = { -500.0f, 200.0f, 0.0f, 0.0f };

    
    lw_mat = scp->mat;
    stp = scp->sk_top;
    
    sk_num = 0; 
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
    vec_normalize(vec, s_vec); 
}
