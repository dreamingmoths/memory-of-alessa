#ifndef MODEL3_N_H
#define MODEL3_N_H

#include "sh2_common.h"
#include "Chacter_Draw/model3_vu1_n.h"

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
typedef struct HeadEnvPacket {
    // total size: 0x70
    u_long dmatag_tag; // offset 0x0, size 0x4
    u_int vifcode_0;   // offset 0x8, size 0x4
    u_int vifcode_1;   // offset 0xC, size 0x4
    u_long giftag_tag; // offset 0x10, size 0x4
    u_long giftag_reg; // offset 0x18, size 0x4
    u_long test_d;     // offset 0x20, size 0x4
    u_long test_a;     // offset 0x28, size 0x4
    u_long texa_d;     // offset 0x30, size 0x4
    u_long texa_a;     // offset 0x38, size 0x4
    u_long fba_d;      // offset 0x40, size 0x4
    u_long fba_a;      // offset 0x48, size 0x4
    u_long alpha_d;    // offset 0x50, size 0x4
    u_long alpha_a;    // offset 0x58, size 0x4
    u_long fogcol_d;   // offset 0x60, size 0x4
    u_long fogcol_a;   // offset 0x68, size 0x4
} HeadEnvPacket;

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
typedef struct TailEnvPacket {
    // total size: 0x30
    u_long dmatag_tag; // offset 0x0, size 0x4
    u_int vifcode_0;   // offset 0x8, size 0x4
    u_int vifcode_1;   // offset 0xC, size 0x4
    u_long giftag_tag; // offset 0x10, size 0x4
    u_long giftag_reg; // offset 0x18, size 0x4
    u_long fba_d;      // offset 0x20, size 0x4
    u_long fba_a;      // offset 0x28, size 0x4
} TailEnvPacket;

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
typedef struct EnvPacket {
    // total size: 0xA0
    struct HeadEnvPacket head_ep; // offset 0x0, size 0x70
    struct TailEnvPacket tail_ep; // offset 0x70, size 0x30
} EnvPacket;

extern EnvPacket envpacketdata; // @ 0x002A9580
extern Model3Junk model3_junk;  // size: 0x1C0, address: 0x419DC0

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\sh2gfw_CharacterOT.c
u_long128* CharacterOt_RequestPacket(int qwc /* r2 */);
void CharacterOt_Append(u_int depth /* r3 */, u_long128* packet /* r2 */);

int Model3NSkeletons(void* model_);

s_char* Model3SkeletonStructure(void* model_);

int Model3NClusters(void* model_);

void Model3DrawPre(void);

void sh2_Model_MakeMatrixParams(void);

void Model3Draw_n(void* scp_d_, void* model_, void* work_, float (*mwm)[4]);

int Model3WorkSize(void* model_);

void Model3InitWork(void* model_, void* work_);

float* Model3WorkClusterWeights(void* work_);

#endif
