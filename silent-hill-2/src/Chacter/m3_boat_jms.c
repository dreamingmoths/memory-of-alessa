#include "sh2_common.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_sc.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_boat.h"
#include "Chacter/m3_boat_jms.h"

Matrix4 bjms_localworld_matrix;

static void BoatPlayerCheckSetParameterPhase1(SubCharacter* this);

static inline void setBoatPlayerLocalWorldMatrix(Vector4* rot) {
    sceVu0FVECTOR vec; 
    vec[0] = rot->x; vec[1] = 0.0f; vec[2] = rot->z; vec[3] = 1.0f;
    sceVu0RotMatrix(bjms_localworld_matrix.d, kt_unit_matrix.d, vec);
    sceVu0RotMatrixY(bjms_localworld_matrix.d, bjms_localworld_matrix.d, rot->y);
}

static inline void setBoatPlayerLocalWorldPosition(Vector4* pos) {
    bjms_localworld_matrix.d[3][0] = pos->x;
    bjms_localworld_matrix.d[3][1] = pos->y;
    bjms_localworld_matrix.d[3][2] = pos->z;
    bjms_localworld_matrix.d[3][3] = 1.0f;
}


#line 121
static void BoatPlayerCheckSetParameterPhase1(SubCharacter* this) {
    SubCharacterDisp* this_d = (SubCharacterDisp*) this;
    this_d->anime2.rot_body_neck.x = 
    this_d->anime2.rot_body_neck.y =
    this_d->anime2.rot_body_neck.z = 0.0f;

    sh2jms.tgt_body_angle.x = 0.0f;
    sh2jms.tgt_body_angle.y = 0.0f;
    sh2jms.tgt_body_angle.z = 0.0f;
    sh2jms.tgt_neck_angle.x = 0.0f;
    sh2jms.tgt_neck_angle.y = 0.0f;
    sh2jms.tgt_neck_angle.z = 0.0f;
    sh2jms.tgt_arms_angle.x = 0.0f;
    sh2jms.tgt_arms_angle.y = 0.0f;
    sh2jms.tgt_arms_angle.z = 0.0f;
    sh2jms.look_tgt = NULL;
}

#line 262
void BoatPlayerCheckControl(void) {
    shCharaInfo* james_info;
    SubCharacter* jms = sh2jms.player;
    SubCharacter* boat;
    SubCharacterDisp* this_d = (SubCharacterDisp*) jms;
    int anim_counter;

    BoatPlayerCheckSetParameterPhase1(jms);
    
    
    BoatPlayerCheckAnime();



    anim_counter = shCharacterAnimeCounterGet(sh2bot.boat_p);
    shCharacterAnimeCounterSet_(sh2jms.player, 1, anim_counter);
    shCharacterAnimeCounterSet_(sh2jms.player, 2, anim_counter);
    shCharacterAnimeSpeedAdd_(sh2jms.player, 1, sh2bot.anime_speed);
    shCharacterAnimeSpeedAdd_(sh2jms.player, 2, sh2bot.anime_speed);
    
    
    
    
    
    
    
    
    
    
    SCRotZYXSwitch(sh2jms.player, 1);
    

    james_info = GetPlayerInfoForCameraCtrl();
    sh2jms.player->pos = james_info->pos;
    sh2jms.player->rot = james_info->rot;
    sh2jms.player->pos_spd = james_info->pos_spd;
    sh2jms.player->rot_spd = james_info->rot_spd;
    
    
    
    
    
    
    
    setBoatPlayerLocalWorldMatrix(&sh2jms.player->rot);
    setBoatPlayerLocalWorldPosition(&sh2jms.player->pos);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    this_d->anime2.rot_neck.x = -sh2jms.player->rot.x;
    this_d->anime2.rot_neck.z = -sh2jms.player->rot.z;
    
    
    
    



    boat = shCharacterGetSubCharacter(BOAT_CHARA_KIND, -1);







}
