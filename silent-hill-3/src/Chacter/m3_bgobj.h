#ifndef M3_BGOBJ_H
#define M3_BGOBJ_H

#include "common.h"
#include "Chacter/character.h"

#define OBJECT_STEP_INIT 0
#define OBJECT_STEP_DRAW 1

extern int mirror_mode;
extern float wall_pos;

struct SubCharacter *shCharacterGetSubCharacter(short kind /* r2 */, short id /* r2 */);
int func_00142EE0(struct SubCharacter *scp /* r16 */);
void RObjectFunction(struct SubCharacter *);

void func_00142F20(struct SubCharacter *arg0);
s_char func_00150C60(void);
float func_00150C70(void);

#endif