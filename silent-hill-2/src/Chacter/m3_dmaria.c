#include "Chacter/m3_dmaria.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#define DMARIA_DRAMA_ANIME_ID_START  3000
#define DMARIA_PLAY_ANIME_ID_START   3400

#define DMARIA_PLAY_ANIM_3401        3401    
#define DMARIA_PLAY_ANIM_3402        3402
#define DMARIA_PLAY_ANIM_3403        3403
#define DMARIA_PLAY_ANIM_3404        3404
#define DMARIA_PLAY_ANIM_3405        3405

// @todo: migrate data

extern /* static */ AnimeInfo dmaria_anim[30]; // size: 0x168, address: 0x38A780
extern /* static */ AnimeInfo p_hhh_mar_anim[6]; // size: 0x48, address: 0x38A8F0
extern /* static */ int dmaria_anime_adr_list[31]; // size: 0x7C, address: 0x2A8690
extern /* static */ int dmaria_clani_adr_list[30]; // size: 0x78, address: 0x2A8710

static int HumanDMARInit(SubCharacter* this) {
    return 0;
}

static void HumanDMARFunction(SubCharacter* this) {
    AnimeInfo *aip; // r2
    
    
    switch (this->step) {
        case 0:


            
            if (shCharacterGetModelID(this) == HHH_MAR_CHARA_KIND) {
                HumanDMARInit(this);
                
                
                
                
                shCharacterAnimeSet(this,
                                    0,
                                    0,
                                    (aip = &dmaria_anim[1]),
                                    (int) shCharacterGetAnimeAdrForDrama(this, 1));
            }
            
            
            this->step++;
            /* fallthrough */
        
        case 1:
            return;
    }
}

void shCharacterSetHumanDMARLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanDMARFunction);
}

int shCharacterHumanDMARAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2
    
    SCAnimeTypeSwitch(scp, 0);
    if (shCharacterGetModelID(scp) == HHH_MAR_CHARA_KIND) {
        
        
        aip = &dmaria_anim[anime_id - DMARIA_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                           dmaria_anime_adr_list[anime_id - DMARIA_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - DMARIA_DRAMA_ANIME_ID_START));
        
        
        
        
        shCharacterClusterAnimeSet(scp, dmaria_clani_adr_list[anime_id - DMARIA_DRAMA_ANIME_ID_START] + (int) shCharacterGetClusterAnimeAdr(scp));
        
        
        
        return 0;
    }
    
    return -1;
}

int shCharacterHumanDMARAnimeSetP(SubCharacter* scp, int anime_id) {
    AnimeInfo * aip; // r2
    
    SCAnimeTypeSwitch(scp, 1);
    if (shCharacterGetModelID(scp) == HHH_MAR_CHARA_KIND) {
        
        
        switch (anime_id) {        
            case DMARIA_PLAY_ANIM_3401:
            case DMARIA_PLAY_ANIM_3402:
            case DMARIA_PLAY_ANIM_3403:
            case DMARIA_PLAY_ANIM_3404:            
                break;
            
            
                        
            case DMARIA_PLAY_ANIM_3405:
                scp->eye_y = 2250.0f; scp->center_y = 2250.0f;                
                break;
        }
        
        
        
        aip = &p_hhh_mar_anim[anime_id - DMARIA_PLAY_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            0,
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        
        return 0;
    }    
    return -1;

}
