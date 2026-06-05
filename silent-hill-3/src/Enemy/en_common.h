#ifndef EN_COMMON_H
#define EN_COMMON_H

#include "Chacter/character.h"
#include "Chacter/m3_sc.h"

#define ENEMY_DATA_COUNT 32
typedef struct EnemyData {
    // size: 0x170
    void (*function)(struct EnemyData*);
    SubCharacter* scp;
    u_char unk_0x8[0x158];
    u_char unk_0x160;
    u_char unk_0x161;
    u_char unk_0x162;
    u_char unk_0x163;
    int unk_0x164;
    int unk_0x168;
    int unk_0x16c;
} EnemyData;

typedef struct EnemyWork {
    // size: 0x2e50
    EnemyData Data[ENEMY_DATA_COUNT];
    short unk2E00;
    short unk2E02;
    int Status;
    u_char unk2E08[0x38];
    int unk2E40;
    int unk2E44;
    int unk2E48;
    int unk2E4C;
} EnemyWork;

extern EnemyWork enemyWork;


void func_0022F1D0(void);
void func_0022FAC0(EnemyData* work);
void func_0022FC20(EnemyData* work);
void func_0022FCF0(EnemyData* work);
void func_0022FE80(EnemyData* work);

void func_0022EB70(SubCharacter* scp);
extern u_int D_01F2A564;
extern u_char D_01F2A581;

#endif
