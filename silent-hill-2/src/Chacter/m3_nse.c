#include "Chacter/m3_nse.h"
#include "Chacter/m3_sc.h"
#include "Enemy/en_common.h"
#include "Enemy/en_nse.h"
#include "sce/libvu0.h"
#include "vec.h"

// @todo: split rodata

extern /* static */ AnimeInfo nse_anim[27]; // size: 0x144, address: 0x3965B0

// @note: I am not finding these 2 below on ghidra

extern /* static */ AnimeInfo d_nse_anim[1]; // size: 0xC, address: 0x0 
extern /* static */ int dnse_anime_adr_list[1]; // size: 0x4, address: 0x0

static int EnemyNSEInit(SubCharacter* this) {
    return 0;
}

static void EnemyNSEFunction(SubCharacter* this) {
    float pos[4]; // r29+0x20
    float rot[4]; // r29+0x30
    EnLOCAL_DATA* dp; // r2
    switch (this->step) {
        case 0:
            if (this->battle.status & 0x400) {
                
                
                
                volatile_vec_copy(&pos, &this->pos);
                volatile_vec_copy(&rot, &this->rot);
                
                EnemyNSEInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                    
                    SCAnimeTypeSwitch(this, 1);
                    
                    shCharacterEnemyNSEAnimeSetP(this, 0x157D, 1);  // @todo: add define
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    volatile_vec_copy(&this->pos, &pos);                
                    volatile_vec_copy(&this->rot, &rot);
    
                    if (this->status & 0x4) {                        
                        
                        
                        if ((dp = enEntryEnemy(6))) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } else {
                            this->enemy_p = NULL;
                        }
                    }

                }
                
                this->step++;
            }
            /* fallthrough */
        
        case 1:
        case 2:
            break;
    
    }

}

void shCharacterSetEnemyNSELow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyNSEFunction);
}

int shCharacterEnemyNSEAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip; // r18
       
    if ((shCharacterGetModelID(scp) == EN_NSE_CHARA_KIND) || (shCharacterGetModelID(scp) == EN_XOO_CHARA_KIND)) {
        
        aip = &nse_anim[anime_id - 0x157C]; // @todo: add define
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        return 0;
    }
    return -1;

}

void shGetEnemyNSEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec) {
    sceVu0FVECTOR pos0; // r29+0x40
    sceVu0FVECTOR pos1; // r29+0x50
    sceVu0FVECTOR vec; // r29+0x60
    sceVu0FMATRIX lw_mat; // r29+0x70
    Matrix4 mat; // r29+0xB0
    int i; // r3
    int sk_num; // r4     
    shSkelton* stp; // r16
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
