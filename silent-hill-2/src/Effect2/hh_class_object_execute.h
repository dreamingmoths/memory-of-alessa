#ifndef HH_CLASS_OBJECT_EXECUTE_H
#define HH_CLASS_OBJECT_EXECUTE_H

#include "common.h"

void HH_Class_Object_Initialize(void);

void HH_Class_Object_Execute(void);

void HH_Class_Object_Packet_Kick(void);

// void HH_Effect_Object_Blood_Pool_Impact_Post(float* Location);
void HH_Effect_Object_Blood_Pool_Impact_Post(float* Location /* r16 */, int idk); // second arg not present in the DWARF

void HH_Effect_Object_Blood_Splash_Impact_Post(float* Location, float* Direction, u_int Scp_Address, u_int Impact_Kind);

void HH_Effect_Object_Ground_Impact_Post(float* Toe, float* Heel, u_int Foot_Kind, u_int Character_ID);

void HH_Effect_Object_Ground_Impact_Post_forEnemy(float* Foot_Location, u_int Foot_Kind);

void HH_Effect_Object_WaterSplash_Impact_Post(float* Location);

#endif
