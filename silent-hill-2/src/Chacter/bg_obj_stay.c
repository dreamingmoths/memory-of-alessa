#include "Chacter/bg_obj_stay.h"
#include "Chacter/m3_sc.h"
#include "Chacter/item_screen_obj.h"

static int shCharacterStayObjectInit(SubCharacter* scp);
static void StayObjectFunction(SubCharacter* this);

static int shCharacterStayObjectInit(SubCharacter* scp) {
    SCStayModelSwitch(scp, 1);
    return 0;
}

static void StayObjectFunction(SubCharacter* this) {
    float scale;


    
    
    
    
    switch (this->step) {
        case 0:
            shCharacterStayObjectInit(this);
        
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            shCharacterWorldScreenObjectSetNew(this, 1.0f);
            scale = this->eye_y = this->center_y = this->pos.y - 150.0f;

            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            this->step++;
            /* fallthrough */
        case 1:
            break;
    }
    #line 224
}


void shCharacterSetStayObjectLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, StayObjectFunction);
}
