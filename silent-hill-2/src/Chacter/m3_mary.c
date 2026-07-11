#include "Chacter/m3_mary.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#define MARY_DRAMA_ANIME_ID_START  4000
#define MARY_PLAY_ANIME_ID_START   4090

// @todo: migrate data
extern /* static */ AnimeInfo dmary_anim[21]; // size: 0xFC, address: 0x399130
extern /* static */ AnimeInfo pmary_anim[3]; // size: 0x24, address: 0x399230
extern /* static */ int dmary_anime_adr_list[21]; // size: 0x54, address: 0x34E910
extern /* static */ int dmary_clani_adr_list[21]; // size: 0x54, address: 0x34E970

static int HumanMRYInit(SubCharacter* this) {
    return 0;
}

static void HumanMRYFunction(SubCharacter* this) {
    AnimeInfo* aip; // r2
    short id; // r4

    switch (this->step) {
        case 0:
            
            
            
            
            
            id = shCharacterGetModelID(this);
            
            if (id == MRY_CHARA_KIND) {
                HumanMRYInit(this);
                
                
                
                
                shCharacterAnimeSet(this,
                                    0,
                                    0,
                                    (aip = &dmary_anim[1]),
                                    (int) shCharacterGetAnimeAdrForDrama(this, 1));
            }
            
            
            this->step++;
            /* fallthrough */
        
        case 1:
            return;
    
    }

}

void shCharacterSetHumanMRYLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanMRYFunction);
}

int shCharacterHumanMRYAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2

    
    SCAnimeTypeSwitch(scp, 0);
    if (shCharacterGetModelID(scp) == MRY_CHARA_KIND) {
        
        aip = &dmary_anim[anime_id - MARY_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            dmary_anime_adr_list[anime_id - MARY_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - MARY_DRAMA_ANIME_ID_START));

        
        
        
        shCharacterClusterAnimeSet(scp, dmary_clani_adr_list[anime_id - MARY_DRAMA_ANIME_ID_START] + (int) shCharacterGetClusterAnimeAdr(scp));
        
        
        
        return 0;
    }
    return -1;

}

int shCharacterHumanMRYAnimeSetP(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2
    
    SCAnimeTypeSwitch(scp, 1);
    if (shCharacterGetModelID(scp) == MRY_CHARA_KIND) {
        
        aip = &pmary_anim[anime_id - MARY_PLAY_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            0,
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        
        
        return 0;
    }
    return -1;

}
