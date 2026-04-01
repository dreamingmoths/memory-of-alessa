#ifndef SH3_GFW_CHARACTER_OT_H
#define SH3_GFW_CHARACTER_OT_H

#include "common.h"

// src\Chacter_Draw\sh2gfw_CharacterOT.c
u_long128 *CharacterOt_RequestPacket(int qwc /* r2 */);
void CharacterOt_Append(u_int depth /* r3 */, u_long128 *packet /* r2 */);

#endif