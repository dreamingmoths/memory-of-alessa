#ifndef EN_TYU_H
#define EN_TYU_H

#include "Enemy/en_common.h"

typedef enum {
    TYUAnimeRest = 1,
    TYUAnimeWalk = 2,
} EnTYUAnimeKind;

void enTYUInitData(EnLOCAL_DATA* dp);
void enTYUCtrlMain(EnLOCAL_DATA* dp);

#endif // EN_TYU_H
