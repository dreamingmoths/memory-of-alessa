#ifndef STG_NAME_H
#define STG_NAME_H

#include "sh2_common.h"

#define Glb_crd_null 0 
#define Glb_crd_num 17

typedef struct Block {
    // Members
    short xz; // offset 0x0, size 0x2
    short block; // offset 0x2, size 0x2
} Block;

int RoomNameJms(void);
int RoomName(int glb_crd, float pos_x, float pos_z);
int BlockNumber(int* ret, int glb_crd, float pos_x, float pos_z);
int BgIsOut(int glb_crd);

#endif // STG_NAME_H
