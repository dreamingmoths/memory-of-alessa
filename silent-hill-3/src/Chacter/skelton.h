#ifndef SKELTON_H
#define SKELTON_H

#include "common.h"

void shCharacterInitSkeltons(void);
void shCharacterFreeSkeltons(shSkelton* top);
void sh3CharacterSubtractSkeletons(int n);
void sh3CharacterAddSkeletons(int n);
shSkelton* shCharacterGetSkeletons(int n, u_char* hrc);

#endif // SKELTON_H
