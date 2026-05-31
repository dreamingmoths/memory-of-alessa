#ifndef CHARA_SAVEINFO_H
#define CHARA_SAVEINFO_H

#include "common.h"
#include "Chacter/character.h"

extern struct shCharacterAll sh2chara;
extern struct shPlayerWork sh2jms;

void shCharacterSetSaveData(Character_Info* chara);
void shCharacterExtGameData(Character_Info* chara);

#endif // CHARA_SAVEINFO_H
