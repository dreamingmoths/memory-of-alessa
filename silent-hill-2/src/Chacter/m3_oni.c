#include "Chacter/m3_oni.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_oni.h"
#include "sce/libvu0.h"
#include "vec.h"

int doni_anime_adr_list[10] = {
    0x00000000, 
    0x00000000,
    0x00000000, 
    0x00009D40, 
    0x00000000, 
    0x000163F8, 
    0x00000000, 
    0x00028458, 
    0x0004A60C, 
    0x0000BC24
}; // size: 0x28, address: 0x34C300

// @todo: migrate rodata

extern /* static */ AnimeInfo oni_anim[16]; // size: 0xC0, address: 0x396EA0
extern /* static */ AnimeInfo d_oni_anim[10]; // size: 0x78, address: 0x396F60

static int EnemyONIInit(SubCharacter* scp);
static void EnemyONIFunction(SubCharacter* scp);

static int EnemyONIInit(SubCharacter* this) {
    return 0;
}

static void EnemyONIFunction(SubCharacter* this) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot; 
    EnLOCAL_DATA* dp;
    switch (this->step) {        
        case 0:
            if (this->battle.status & 0x400) {
                
                
                
                volatile_vec_copy(&pos, &this->pos);
                volatile_vec_copy(&rot, &this->rot);
                                
                EnemyONIInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                
                    SCAnimeTypeSwitch(this, 1);
                    shCharacterEnemyONIAnimeSetP(this, ONI_PLAY_ANIM_5401, 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & 4) {
                    
                        
                        if (dp = enEntryEnemy(5)) {
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

void shCharacterSetEnemyONILow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyONIFunction);
}

int shCharacterEnemyONIAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    if (shCharacterGetModelID(scp) == EN_ONI_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, 0);
        aip = &d_oni_anim[anime_id - D_ONI_ANIM_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            doni_anime_adr_list[anime_id - D_ONI_ANIM_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - D_ONI_ANIM_START));
        
        
        
        return 0;
    }
    return -1;

}

int shCharacterEnemyONIAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip;
    
    if (shCharacterGetModelID(scp) == EN_ONI_CHARA_KIND) {
        aip = &oni_anim[anime_id - ONI_PLAY_ANIME_ID_START];         
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
