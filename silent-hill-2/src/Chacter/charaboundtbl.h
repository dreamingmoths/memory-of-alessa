#ifndef CHARABOUNDTBL_H
#define CHARABOUNDTBL_H

#include "sh2_common.h"

#define CHARA_BOUND_TBL_NUM 236

// total size: 0x8
typedef struct Chara_Bound {
    // Members
    int chara_id; // offset 0x0, size 0x4
    float r; // offset 0x4, size 0x4
} Chara_Bound;

int CharaBoundTblNum(void);

extern Chara_Bound chara_bound_tbl[CHARA_BOUND_TBL_NUM]; // size: 0x760, address: 0x373070

#endif // CHARABOUNDTBL_H
