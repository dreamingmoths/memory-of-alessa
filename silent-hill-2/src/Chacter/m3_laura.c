#include "Chacter/m3_laura.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#define LAURA_DRAMA_ANIME_ID_START 2500
#define LAURA_PLAY_ANIME_ID_START  2900

// @todo: migrate data
extern /* static */ AnimeInfo laura_anim[41]; // size: 0x1EC, address: 0x38AC50
extern /* static */ AnimeInfo plaura_anim[3]; // size: 0x24, address: 0x38AE40
extern /* static */ int dlaura_anime_adr_list[41]; // size: 0xA4, address: 0x2A88B0
extern /* static */ int dlaura_clani_adr_list[41]; // size: 0xA4, address: 0x2A8960

static int HumanLAUInit(SubCharacter* this) {
    return 0;
}

static void HumanLAUFunction(SubCharacter* this) {
    short id;
    AnimeInfo* aip;
    
    switch (this->step) {
        case 0:




            
            id = shCharacterGetModelID(this);
            
            if (id == LAU_CHARA_KIND) {
                HumanLAUInit(this);
    
                
                
                
                shCharacterAnimeSet(this,
                                    0,
                                    0,
                                    (aip = &laura_anim[1]),
                                    (int) shCharacterGetAnimeAdrForDrama(this, 1));

            }
            
            this->step++;
            /* fallthrough */
        case 1:
            return;
    }



}

void shCharacterSetHumanLAULow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanLAUFunction);
}

int shCharacterHumanLAUAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2

    
    SCAnimeTypeSwitch(scp, 0);
    if (shCharacterGetModelID(scp)== LAU_CHARA_KIND) {
        
        
        aip = &laura_anim[anime_id - LAURA_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            dlaura_anime_adr_list[anime_id - LAURA_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - LAURA_DRAMA_ANIME_ID_START));
        
        
        

        
        shCharacterClusterAnimeSet(scp, dlaura_clani_adr_list[anime_id - LAURA_DRAMA_ANIME_ID_START] + (int) shCharacterGetClusterAnimeAdr(scp));
        
        
        
        
        
        return 0;
    }
    return -1;

}

int shCharacterHumanLAUAnimeSetP(SubCharacter* scp, int anime_id) {
    AnimeInfo * aip;
   
    SCAnimeTypeSwitch(scp, 1);
    
    
    if (shCharacterGetModelID(scp) == LAU_CHARA_KIND) {
        
        
        
        
        
        
        aip = &plaura_anim[anime_id - LAURA_PLAY_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            0,
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        return 0;
    }
    return -1;

}
