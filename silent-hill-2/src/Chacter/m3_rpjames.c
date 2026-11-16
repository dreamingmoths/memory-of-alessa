#include "sh2_common.h"
#include "vec.h"
#include "Chacter/character.h"
#include "Chacter/m3_rpjames.h"

static float wall_pos;
static int mirror_mode;

static int HumanRPJMSInit(SubCharacter* scp);
static void HumanRPJMSFunction(SubCharacter* this);

#line 50
static int HumanRPJMSInit(SubCharacter* scp) {
    SCAnimeTypeSwitch(scp, true);

    scp->model_type = 1;
    
    return 0;
}

#line 65
static void HumanRPJMSFunction(SubCharacter* this) {
    
    
    
    switch (this->step) {
        
        case 0:
            HumanRPJMSInit(this);
            this->step++;
            return;
        
        
        case 1:
            sh2gfw_Set_JMSequip(this, sh2jms.parts_lhand, sh2jms.parts_rhand, sh2jms.parts_light);
        
            switch (mirror_mode) {
                
                case 0:
                    this->pos.x = wall_pos + (wall_pos - sh2jms.player->pos.x);
                    this->pos.y = sh2jms.player->pos.y;
                    this->pos.z = sh2jms.player->pos.z;
                    this->rot.y = -sh2jms.player->rot.y;
                    return;
                
                case 1:
                    this->pos.x = sh2jms.player->pos.x;
                
                    
                    
                    
                    
                    this->pos.y = wall_pos + (wall_pos - sh2jms.player->pos.y);
                    
                    this->pos.z = sh2jms.player->pos.z;
                    this->rot.y = sh2jms.player->rot.y;
                    this->rot.z = PI;
                    return;
                case 2:
                    
                    this->pos.x = sh2jms.player->pos.x;
                    this->pos.y = sh2jms.player->pos.y;
                    this->pos.z = wall_pos + (wall_pos - sh2jms.player->pos.z);
                    if (sh2jms.player->rot.y >= 0.0f) {
                        this->rot.y = PI - sh2jms.player->rot.y;
                        return;}
                    this->rot.y = -PI - sh2jms.player->rot.y;
                    return;
            }
            break;
    }



    
}

#line 135
void shCharacterSetHumanRPJMSLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanRPJMSFunction);
}

#line 148
void shGetJamesLightPos_Calc_Reverse(void) {
    switch (mirror_mode) {
        case 0:
            sh2jms.light_pos_revise_reverse[0] = wall_pos + (wall_pos - sh2jms.light_pos_revise[0]);
            sh2jms.light_pos_revise_reverse[1] = sh2jms.light_pos_revise[1];
            sh2jms.light_pos_revise_reverse[2] = sh2jms.light_pos_revise[2];
            sh2jms.light_pos_revise_reverse[3] = 1.0;
            sh2jms.light_pos_reverse[0] = wall_pos + (wall_pos - sh2jms.light_pos[0]);
            sh2jms.light_pos_reverse[1] = sh2jms.light_pos[1];
            sh2jms.light_pos_reverse[2] = sh2jms.light_pos[2];
            sh2jms.light_pos_reverse[3] = 1.0;
            
            sh2jms.light_vec_revise_reverse[0] = -sh2jms.light_vec_revise[0];
            sh2jms.light_vec_revise_reverse[1] = sh2jms.light_vec_revise[1];
            sh2jms.light_vec_revise_reverse[2] = sh2jms.light_vec_revise[2];
            sh2jms.light_vec_reverse[0] = -sh2jms.light_vec[0];
            sh2jms.light_vec_reverse[1] = sh2jms.light_vec[1];
            sh2jms.light_vec_reverse[2] = sh2jms.light_vec[2];
            return;
        case 1:
            sh2jms.light_pos_revise_reverse[0] = sh2jms.light_pos_revise[0];
            
            
            
            
            sh2jms.light_pos_revise_reverse[1] = wall_pos + (wall_pos - sh2jms.light_pos_revise[1]);
            
            sh2jms.light_pos_revise_reverse[2] = sh2jms.light_pos_revise[2];
            sh2jms.light_pos_revise_reverse[3] = 1.0;
            sh2jms.light_pos_reverse[0] = sh2jms.light_pos[0];
            
            
            
            
            sh2jms.light_pos_reverse[1] = wall_pos + (wall_pos - sh2jms.light_pos[1]);
            
            sh2jms.light_pos_reverse[2] = sh2jms.light_pos[2];
            sh2jms.light_pos_reverse[3] = 1.0;
            
            sh2jms.light_vec_revise_reverse[0] = sh2jms.light_vec_revise[0];
            sh2jms.light_vec_revise_reverse[1] = -sh2jms.light_vec_revise[1];
            sh2jms.light_vec_revise_reverse[2] = sh2jms.light_vec_revise[2];
            sh2jms.light_vec_reverse[0] = sh2jms.light_vec[0];
            sh2jms.light_vec_reverse[1] = -sh2jms.light_vec[1];
            sh2jms.light_vec_reverse[2] = sh2jms.light_vec[2];
            return;
        case 2:
            sh2jms.light_pos_revise_reverse[0] = sh2jms.light_pos_revise[0];
            sh2jms.light_pos_revise_reverse[1] = sh2jms.light_pos_revise[1];
            sh2jms.light_pos_revise_reverse[2] = wall_pos + (wall_pos - sh2jms.light_pos_revise[2]);
            sh2jms.light_pos_revise_reverse[3] = 1.0;
            sh2jms.light_pos_reverse[0] = sh2jms.light_pos[0];
            sh2jms.light_pos_reverse[1] = sh2jms.light_pos[1];
            sh2jms.light_pos_reverse[2] = wall_pos + (wall_pos - sh2jms.light_pos[2]);
            sh2jms.light_pos_reverse[3] = 1.0;
            
            sh2jms.light_vec_revise_reverse[0] = sh2jms.light_vec_revise[0];
            sh2jms.light_vec_revise_reverse[1] = sh2jms.light_vec_revise[1];
            sh2jms.light_vec_revise_reverse[2] = -sh2jms.light_vec_revise[2];
            sh2jms.light_vec_reverse[0] = sh2jms.light_vec[0];
            sh2jms.light_vec_reverse[1] = sh2jms.light_vec[1];
            sh2jms.light_vec_reverse[2] = -sh2jms.light_vec[2];
            return;
    }
}

#line 226
void shGetJamesLightPosOriginal_Reverse(float* pos, float* vec) {
    shVectorCopy(pos, sh2jms.light_pos_reverse);
    shVectorCopy(vec, sh2jms.light_vec_reverse);
}

#line 240
void PlayerSetReverseMode(void) {
    #line 243
    switch (RoomNameJms()) {
        case 1:
            mirror_mode = 0;
            wall_pos = -20000.0f;
            sh2jms.water_road = 0;
            break;
        case 36:
            mirror_mode = 2;
            wall_pos = -99995.0f;
            sh2jms.water_road = 0;
            break;
        case 37:
        case 38:
        case 98:
            mirror_mode = 1;
            wall_pos = 0.0f;
            sh2jms.water_road = 0;
            break;
        case 99:
            
        case 128:
        case 133:
        case 122:
            
        case 124:
        case 126:
        case 182:
            
        case 183:
        case 171:
        case 184:
            
        case 185:
            mirror_mode = 1;
            wall_pos = -100.0f;
            sh2jms.water_road = 1;
            break;
        default:
            mirror_mode = -1;
            sh2jms.water_road = 0;
            break;
    }
    sh2jms.light_reverse = (mirror_mode == -1)? 0 : 1;
}
