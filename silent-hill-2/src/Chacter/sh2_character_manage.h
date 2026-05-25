#ifndef SH2_CHARACTER_MANAGE_H
#define SH2_CHARACTER_MANAGE_H

#include "common.h"
#include "Chacter/character.h"

int shCharacter_Manage_Delete(struct SubCharacter* scp /* r2 */, short kind /* r2 */, short id /* r2 */);
struct SubCharacter* shCharacter_Manage_GetCharacterList(void);
int shCharacter_Manage_SetDataAdresss(struct SubCharacter* scp /* r16 */);

#endif // SH2_CHARACTER_MANAGE_H
