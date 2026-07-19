#ifndef SH2_CHARACTER_MANAGE_H
#define SH2_CHARACTER_MANAGE_H

#include "common.h"
#include "Chacter/character.h"

int shCharacter_Manage_Init(void);

int shCharacter_Manage_Create(short kind, short id, float* pos, float* rot, u_int status);

int shCharacter_Manage_Delete(SubCharacter* scp, short kind, short id);

SubCharacter* shCharacter_Manage_GetCharacterList(void);

int shCharacter_Manage_SetDataAdresss(SubCharacter* scp);

void shCharacter_Manage_SetJamesAnimeAdresss(SubCharacter* scp, u_int address);

int shCharacter_Manage_Create_After_MC_Load(Character_Info* chara);

#endif // SH2_CHARACTER_MANAGE_H
