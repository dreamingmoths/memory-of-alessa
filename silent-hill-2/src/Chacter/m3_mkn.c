#include "sh2_common.h"

#include "vec.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_mkn.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_sc.h"

#include "Enemy/en_common.h"

#define MANNEQUIN_PLAY_ANIME_ID_START 5100
#define MANNEQUIN_PLAY_ANIM(id) (id + MANNEQUIN_PLAY_ANIME_ID_START)

#define MANNEQUIN_DRAMA_ANIME_ID_START 6100
#define MANNEQUIN_DRAMA_ANIM(id) (id + MANNEQUIN_DRAMA_ANIME_ID_START)

const AnimeInfo mkn_anim[35] = {
    {NULL},
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(1),
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 23,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(2),
        /* .frame = */ 31,
        /* .speed = */ 2048,
        /* .start = */ 24,
        /* .end = */ 54,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(3),
        /* .frame = */ 35,
        /* .speed = */ 2048,
        /* .start = */ 55,
        /* .end = */ 89,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(4),
        /* .frame = */ 35,
        /* .speed = */ 2048,
        /* .start = */ 90,
        /* .end = */ 124,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(5),
        /* .frame = */ 18,
        /* .speed = */ 2048,
        /* .start = */ 125,
        /* .end = */ 142,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(6),
        /* .frame = */ 25,
        /* .speed = */ 2048,
        /* .start = */ 143,
        /* .end = */ 167,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(7),
        /* .frame = */ 25,
        /* .speed = */ 2048,
        /* .start = */ 168,
        /* .end = */ 192,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(8),
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 193,
        /* .end = */ 212,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(9),
        /* .frame = */ 20,
        /* .speed = */ 2048,
        /* .start = */ 213,
        /* .end = */ 232,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(10),
        /* .frame = */ 27,
        /* .speed = */ 2048,
        /* .start = */ 233,
        /* .end = */ 259,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(11),
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 260,
        /* .end = */ 291,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(12),
        /* .frame = */ 32,
        /* .speed = */ 2048,
        /* .start = */ 292,
        /* .end = */ 323,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(13),
        /* .frame = */ 16,
        /* .speed = */ 1500,
        /* .start = */ 324,
        /* .end = */ 339,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(14),
        /* .frame = */ 17,
        /* .speed = */ 1500,
        /* .start = */ 340,
        /* .end = */ 356,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(15),
        /* .frame = */ 16,
        /* .speed = */ 1500,
        /* .start = */ 357,
        /* .end = */ 372,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(16),
        /* .frame = */ 30,
        /* .speed = */ 1800,
        /* .start = */ 373,
        /* .end = */ 402,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(17),
        /* .frame = */ 30,
        /* .speed = */ 1800,
        /* .start = */ 403,
        /* .end = */ 432,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(18),
        /* .frame = */ 10,
        /* .speed = */ 1600,
        /* .start = */ 433,
        /* .end = */ 442,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(19),
        /* .frame = */ 12,
        /* .speed = */ 2048,
        /* .start = */ 443,
        /* .end = */ 454,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(20),
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 455,
        /* .end = */ 470,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(21),
        /* .frame = */ 44,
        /* .speed = */ 2048,
        /* .start = */ 471,
        /* .end = */ 514,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(22),
        /* .frame = */ 50,
        /* .speed = */ 2048,
        /* .start = */ 515,
        /* .end = */ 564,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(23),
        /* .frame = */ 39,
        /* .speed = */ 2048,
        /* .start = */ 565,
        /* .end = */ 603,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(24),
        /* .frame = */ 42,
        /* .speed = */ 2048,
        /* .start = */ 604,
        /* .end = */ 645,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(25),
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 646,
        /* .end = */ 661,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(26),
        /* .frame = */ 16,
        /* .speed = */ 2048,
        /* .start = */ 662,
        /* .end = */ 677,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(27),
        /* .frame = */ 8,
        /* .speed = */ 2048,
        /* .start = */ 678,
        /* .end = */ 685,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(28),
        /* .frame = */ 8,
        /* .speed = */ 2048,
        /* .start = */ 686,
        /* .end = */ 693,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(29),
        /* .frame = */ 15,
        /* .speed = */ 2048,
        /* .start = */ 694,
        /* .end = */ 708,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(30),
        /* .frame = */ 7,
        /* .speed = */ 2048,
        /* .start = */ 709,
        /* .end = */ 715,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(31),
        /* .frame = */ 2,
        /* .speed = */ 2048,
        /* .start = */ 716,
        /* .end = */ 717,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(32),
        /* .frame = */ 2,
        /* .speed = */ 2048,
        /* .start = */ 718,
        /* .end = */ 719,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(33),
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 355,
        /* .end = */ 355,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_PLAY_ANIM(34),
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 371,
        /* .end = */ 371,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

const AnimeInfo d_mkn_anim[8] = {
    {NULL},
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(1),
        /* .frame = */ 1,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(2),
        /* .frame = */ 360,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 359,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(3),
        /* .frame = */ 1336,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1335,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(4),
        /* .frame = */ 880,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 879,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(5),
        /* .frame = */ 360,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 359,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(6),
        /* .frame = */ 1336,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1335,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ MANNEQUIN_DRAMA_ANIM(7),
        /* .frame = */ 880,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 879,
        /* .loop = */ 1,
        /* .pad = */ 0,
    }
}; // size: 0x60, address: 0x0

int dmkn_anime_adr_list[8] = { 0, 0, 0, 26996, 45896, 56672, 83536, 94312 }; // size: 0x20, address: 0x2A8A10

static int EnemyMKNInit(SubCharacter* this);
static void EnemyMKNFunction(SubCharacter* this /* r16 */);

static int EnemyMKNInit(SubCharacter* this) {
    return false;
}

static void EnemyMKNFunction(SubCharacter* this /* r16 */) {
    sceVu0FVECTOR pos; // r29+0x20
    sceVu0FVECTOR rot; // r29+0x30
    EnLOCAL_DATA* dp; // r2
    switch (this->step) {
        case 0:
            if (this->battle.status & (1 << 10)) {
                
                
                
                shVectorCopy(pos, &this->pos);
                shVectorCopy(rot, &this->rot);
                
                
                
                EnemyMKNInit(this);
                
                if (!PlayerNowDemoEventMode()) {
                
                    SCAnimeTypeSwitch(this, true);
                    
                    shCharacterEnemyMKNAnimeSetP(this, MANNEQUIN_PLAY_ANIM(2), 1);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    if (this->status & (1 << 2)) {
                    
                        
                        if ((dp = enEntryEnemy(2))) {
                            this->enemy_p = dp;
                            enInitData(dp, this);
                        } else {
                            this->enemy_p = NULL;
                        }
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

void shCharacterSetEnemyMKNLow(SubCharacter* scp /* r2 */) {
    shCharacterSetFunction(scp, EnemyMKNFunction);
}

int shCharacterEnemyMKNAnimeSet(SubCharacter* scp /* r17 */, int anime_id /* r16 */) {
    AnimeInfo* aip; // r2

    if (shCharacterGetModelID(scp) == EN_MKN_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, 0);
        aip = (AnimeInfo*) &d_mkn_anim[anime_id - MANNEQUIN_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            dmkn_anime_adr_list[anime_id - MANNEQUIN_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - MANNEQUIN_DRAMA_ANIME_ID_START));
            
        
        
        return 0;
    }
    return -1;

}

int shCharacterEnemyMKNAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */) {
    AnimeInfo* aip; // r18

    if (shCharacterGetModelID(scp) == EN_MKN_CHARA_KIND) {
        aip = (AnimeInfo*) &mkn_anim[anime_id - 0x13EC];
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) (comp == 1 ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
            
        
        return 0;
    }
    return -1;

}

void shGetEnemyMKNAttackPos(SubCharacter* scp /* r2 */, float* s_pos /* r18 */, float* s_vec /* r17 */, u_short atk /* r2 */) {
    sceVu0FVECTOR pos0; // r29+0x40
    sceVu0FVECTOR pos1; // r29+0x50
    sceVu0FVECTOR vec; // r29+0x60
    Matrix4 lw_mat; // r29+0x70
    Matrix4 mat; // r29+0xB0
    int i; // r3
    int sk_num; // r4
    sceVu0FVECTOR wep_range = {500.0f, 0.0f, 0.0f, 0.0f}; // r29+0xF0
    shSkelton* stp; // r16

    lw_mat.d = scp->mat;
    stp = scp->sk_top;

    switch (atk) {
        case 38:
            sk_num = 7;
            break;
        case 39:
            sk_num = 5;
            break;
    }

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

    sceVu0ApplyMatrix(pos0, &lw_mat, pos0);
    shVectorCopy(s_pos, pos0);
    sceVu0ApplyMatrix(pos1, &mat, wep_range);

    pos1[0] += stp->src_m.d[3][0];
    pos1[1] += stp->src_m.d[3][1];
    pos1[2] += stp->src_m.d[3][2];
    pos1[3]  = stp->src_m.d[3][3];

    sceVu0ApplyMatrix(pos1, &lw_mat, pos1);

    vec[0] = pos1[0] - pos0[0];
    vec[1] = pos1[1] - pos0[1];
    vec[2] = pos1[2] - pos0[2];
    vec[3] = 0.0f;
    
    shNormalizeVector(vec, s_vec);
}




void shEnemyMKN_EffectFoot(SubCharacter* scp /* r2 */, int type /* r16 */) {
    sceVu0FMATRIX mat; // r29+0x20
    int i1; // r3

    
    
    
    
    int foot = type ? 14 : 13; // r5
    
    
    shSkelton* sk = scp->sk_top; // r6
    for (i1 = 0; i1 < foot; i1++)
        sk = sk->next;

    sceVu0MulMatrix(mat, scp->mat[0], &sk->src_m);
    HH_Effect_Object_Ground_Impact_Post_forEnemy(mat[3], type);
}
