#include "Chacter/m3_mxx.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

// @todo: migrate data

extern /* static */ AnimeInfo dmxx_anim[11]; // size: 0x84, address: 0x399260
extern /* static */ int dmxx_anime_adr_list[11]; // size: 0x2C, address: 0x0
extern /* static */ int dmxx_clani_adr_list[11]; // size: 0x2C, address: 0x0

#line 71
/* static */ int HumanMXXInit(SubCharacter* scp) {
    scp->kind = HHH_MXX_CHARA_KIND;
    SCAnimeTypeSwitch(scp, 0);
    return 0;
}

#line 87
/* static */ void HumanMXXFunction(SubCharacter* this) {
    AnimeInfo* aip;
    short id;

    switch (this->step) {
        case 0:
            
            
            
            
            
            id = shCharacterGetModelID(this);
            
            if (id == HHH_MXX_CHARA_KIND) {
                HumanMXXInit(this);
                
                
                
                
                shCharacterAnimeSet(this,
                                    0,
                                    0,
                                    (aip = &dmxx_anim[1]),
                                    (int) shCharacterGetAnimeAdrForDrama(this, 1));
            }
            
            
            this->step++;
            /* fallthrough */        
        case 1:
            return;
    
    
    
    }
}

#line 138
void shCharacterSetHumanMXXLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanMXXFunction);
}
