#include "Chacter/m3_inu.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play_event.h"

#define INU_DRAMA_ANIME_ID_START 4900
#define INU_PLAY_ANIME_ID_START  4850
#define INU_PLAY_ANIM_4851       4851

// @todo: migrate data

extern /* static */ AnimeInfo inu_anim[1]; // size: 0xC, address: 0x39A7A0
extern /* static */ AnimeInfo d_inu_anim[3]; // size: 0x24, address: 0x39A7B0
extern /* static */ int dinu_anime_adr_list[3]; // size: 0xC, address: 0x371BA0

#line 69
/* static */ void HumanINUFunction(SubCharacter* this) {
    float pos[4]; // r29+0x20
    float rot[4]; // r29+0x30

    switch (this->step) {
        case 0:
            
            
            
            
            volatile_vec_copy(pos, &this->pos);
            volatile_vec_copy(rot, &this->rot);
    
            if (PlayerNowDemoEventMode() == 0) {
            
                SCAnimeTypeSwitch(this, 1);
                
                shCharacterHumanINUAnimeSetP(this, INU_PLAY_ANIM_4851, 1);
            }
            
            
            
            volatile_vec_copy(&this->pos, pos);
            volatile_vec_copy(&this->rot, rot);
    
            this->step++;
        /* fallthrough */
        
        
        
        case 1:
            return;
    }
}

#line 118
void shCharacterSetHumanINULow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanINUFunction);
}

#line 132
int shCharacterHumanINUAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2

    if (shCharacterGetModelID(scp) == INU_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, 0);
        aip = &d_inu_anim[anime_id - INU_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            dinu_anime_adr_list[anime_id - INU_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - INU_DRAMA_ANIME_ID_START));
        
        
        
        return 0;
    }
    return -1;

}

#line 163
int shCharacterHumanINUAnimeSetP(SubCharacter* scp, int anime_id, int comp) {
    AnimeInfo* aip; // r18

    if (shCharacterGetModelID(scp) == INU_CHARA_KIND) {
        aip = &inu_anim[anime_id - INU_PLAY_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            (char) ((comp == 1) ? 4 : 2), // @todo: add comp type defines
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        return 0;
    }
    return -1;

}
