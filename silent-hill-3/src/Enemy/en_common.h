#ifndef EN_COMMON_H
#define EN_COMMON_H

#include "Chacter/character.h"
#include "Chacter/m3_sc.h"

typedef struct EnemyWork {
    int unk_0x0;
    SubCharacter* scp;
    u_char unk_0x8[0x158];
    u_char unk_0x160;
    u_char unk_0x161;
    u_char unk_0x162;
    u_char unk_0x163;
    int    unk_0x164;
    int    unk_0x168;
    int    unk_0x16c;
} EnemyWork;

extern EnemyWork D_01F27760;

void func_0022EB70(SubCharacter* scp);

void func_0022FAC0(EnemyWork* work);
void func_0022FC20(EnemyWork* work);
void func_0022FCF0(EnemyWork* work);
void func_0022FE80(EnemyWork* work);

extern u_int D_01F2A564;
extern u_char D_01F2A581;

#endif
