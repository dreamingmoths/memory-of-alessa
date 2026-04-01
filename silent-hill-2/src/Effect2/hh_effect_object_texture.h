#ifndef HH_EFFECT_OBJECT_TEXTURE_H
#define HH_EFFECT_OBJECT_TEXTURE_H

#include "common.h"

u_int HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(u_int Entry_Level /* r17 */);
u_int HH_Effect_Object_Texture_DesignateEntryLevel_Discard(u_int Entry_Level /* r2 */);
u_long HH_Effect_Object_Texture_GS_Register_Tex0_Get(u_int Texture_ID, u_int Clut_ID);

#endif
