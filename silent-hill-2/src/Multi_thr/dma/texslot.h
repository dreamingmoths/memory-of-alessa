#ifndef TEXSLOT_H
#define TEXSLOT_H

#include "sce/eekernel.h"

// total size: 0x10
typedef struct texSlotCtrlT {
    // Members
    int init;      // offset 0x0, size 0x4
    int sid;       // offset 0x4, size 0x4
    int cur_texid; // offset 0x8, size 0x4
    int padding;   // offset 0xC, size 0x4
} texSlotCtrlT;

int texSlotInit(void);

int texSlotBeginToUse(int slot /* r2 */);

int texSlotFinishToUse(int slot /* r2 */);

int texSlotGetCurTexID(int slot /* r2 */);

int texSlotSetCurTexID(int slot /* r2 */, int texid /* r2 */);

int texSlotClearAll(void);

#endif // TEXSLOT_H
