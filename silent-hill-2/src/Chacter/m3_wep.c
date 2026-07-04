#include "Chacter/m3_wep.h"
#include "Chacter/m3_sc.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_play.h"

/* static */ const AnimeInfo weapon_anim[9] = { // but does this belong here?
    // name,  frame, speed, start, end, loop, pad
    { 0x0000, 0,     0,     0,     0,   0,    0 }, // [0]
    { 0x1B59, 1,     0,     0,     0,   0,    0 }, // [1] handgun
    { 0x1B5A, 1,     0,     1,     1,   0,    0 }, // [2] shotgun
    { 0x1B5B, 1,     0,     2,     2,   0,    0 }, // [3] rifle
    { 0x1B5C, 1,     0,     3,     3,   0,    0 }, // [4] spray
    { 0x1B5D, 1,     0,     4,     4,   0,    0 }, // [5] stick
    { 0x1B5E, 1,     0,     5,     5,   0,    0 }, // [6] pipe
    { 0x1B5F, 1,     0,     6,     6,   0,    0 }, // [7] great knife
    { 0x1B60, 1,     0,     7,     7,   0,    0 }  // [8] chainsaw
};

/* static */ void WeaponFunction(SubCharacter* this);

/* static */ void WeaponFunction(SubCharacter* this) {
    AnimeInfo* aip; // r16
    float scale; // r29+0x30 how is this used?

    switch (this->step) {
        case 0:
            SCAnimeTypeSwitch(this, 0);
            switch (shCharacterGetModelID(this)) {
                case WEAPON_HANDGUN_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[1];
                    break;
                case WEAPON_SHOTGUN_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[2];
                    break;
                case WEAPON_RIFLGUN_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[3];
                    break;
                case WEAPON_KAKUZAI_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[5];
                    break;
                case WEAPON_PIPE_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[6];
                    break;
                case WEAPON_SP_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[4];
                    break;
                case WEAPON_CSAW_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[8];
                    break;
                case WEAPON_NATA_CHARA_KIND:
                    aip = (AnimeInfo*)&weapon_anim[7];
                    break;
                }
        
        shCharacterAnimeSet(this, 0, 0, aip, (int)shCharacterGetAnimeAdrForPlay(this));
        this->step++;
        /* fallthrough */
        case 1:
            return;
    }
}

void shUpdateWeaponMatrixAfterAnime(SubCharacter* this, short kind) {
    SubCharacter* player;
    sceVu0FMATRIX mat;

    
    if (this != NULL) {
        
        GetPlayerPartsLocalMatrix(mat, 0x23);    
        this->sk_top->src_m.d = mat;    
        this->sk_top->src_t = *(Vector4*)mat[3];
    
        player = shCharacterGetSubCharacter(kind, -1);        
        if (player != NULL) {

            
            this->mat = player->mat;

            
            volatile_vec_copy(&this->pos, this->mat[3]);
        } 
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_wep", shGetJamesWeaponPos);

void shGetJamesWeaponStartPos(float* pos, float* vec) {
    shGetJamesWeaponPos(pos, vec, 0);
}

void shGetJamesWeaponEndPos(float* pos, float* vec) {
    shGetJamesWeaponPos(pos, vec, 1);
}

void shCharacterSetWeaponLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, WeaponFunction);
}

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_wep", sh2_attack_list);
