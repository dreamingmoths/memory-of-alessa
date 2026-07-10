#include "Chacter/m3_rwep.h"

static void WeaponRFunction(SubCharacter* this) {
    switch (this->step) {
        case 0:
            this->model_type = 1;
            this->step++;
            /* fallthrough */
        
        case 1:
            return;
        
    }
}

void shCharacterSetWeaponRLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, WeaponRFunction);
}
