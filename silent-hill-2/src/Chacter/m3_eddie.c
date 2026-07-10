#include "Chacter/m3_eddie.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

// @todo: add defines like how it was done in m3_angela.c

// @todo: migrate data

extern /* static */ AnimeInfo eddie_anim[28]; // size: 0x150, address: 0x38A940
extern /* static */ AnimeInfo peddie_anim[4]; // size: 0x30, address: 0x38AA90
extern /* static */ int deddie_anime_adr_list[28]; // size: 0x70, address: 0x2A8790
extern /* static */ int deddie_clani_adr_list[28]; // size: 0x70, address: 0x2A8800

#line 143
/* static */ void HumanEDIFunction(SubCharacter* this) {
    AnimeInfo* aip;
    short id;

    switch (this->step) {
        case 0:
            
            
            
            
            
            id = shCharacterGetModelID(this);
            
            if (id == HHH_EDI_CHARA_KIND) {                
                
                
                
                
                
                shCharacterAnimeSet(this,
                                    0,
                                    0,
                                    (aip = &eddie_anim[1]),
                                    (int) shCharacterGetAnimeAdrForDrama(this, 1));
            }
            
            
            this->step++;
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        case 1:
            return;
    }
}

#line 224
void shCharacterSetHumanEDILow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanEDIFunction);
}

#line 240
int shCharacterHumanEDIAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    SCAnimeTypeSwitch(scp, 0);
    
    if (shCharacterGetModelID(scp) == HHH_EDI_CHARA_KIND) {
        
        
        aip = &eddie_anim[anime_id - 0x1194];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            deddie_anime_adr_list[anime_id - 0x1194] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - 0x1194));
        
        
        
        
        
        
        shCharacterClusterAnimeSet(scp, deddie_clani_adr_list[anime_id - 0x1194] + (int) shCharacterGetClusterAnimeAdr(scp));

        
        
        return 0;
    }
    return -1;

}

#line 280
int shCharacterHumanEDIAnimeSetP(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2
    
    SCAnimeTypeSwitch(scp, 1);
    
    if (shCharacterGetModelID(scp) == HHH_EDI_CHARA_KIND) {
        
        
        switch (anime_id) {
            case 0x12C1:
                scp->eye_y = -242.1998f; scp->center_y = -242.1998f;
                
                break;
            case 0x12C2:
                scp->eye_y = -432.1998f; scp->center_y = -432.1998f;
                
                break;
            
            
            case 0x12C3:
                break;
        }
        aip = &peddie_anim[anime_id - 0x12C0];
        shCharacterAnimeSet(scp,
                            0,
                            0,
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));
        
        
        
        return 0;
    }
    return -1;

}
