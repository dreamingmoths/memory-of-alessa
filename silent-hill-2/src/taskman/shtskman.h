#ifndef SHTSKMAN_H
#define SHTSKMAN_H

#include "common.h"

// total size: 0x14
typedef struct _shTskEXECUTE {
    // Members
    void (* adrs)(void *); // offset 0x0, size 0x4
    void * next; // offset 0x4, size 0x4
    void * prev; // offset 0x8, size 0x4
    int mode; // offset 0xC, size 0x4
    int atr; // offset 0x10, size 0x4
} _shTskEXECUTE;

// total size: 0x200
typedef struct _shTskTASK {
    // Members
    struct _shTskEXECUTE exe; // offset 0x0, size 0x14
    u_char freemem[492]; // offset 0x14, size 0x1EC
} _shTskTASK;

struct _shTskTASK * shTSKSetTask(void (* func)(void *) /* r6 */, u_char num /* r2 */); 
void shTSKDelTask(struct _shTskTASK* task);
struct _shTskTASK* shTSKSearchTaskWithAtr(int atr, struct _shTskTASK* start, u_char num);

struct _shTskTASK * shTskTaskListTop[8];

#endif // SHTSKMAN_H
