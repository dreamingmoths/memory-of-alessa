#ifndef SHTSKMAN_H
#define SHTSKMAN_H

#include "sh2_common.h"

#define TASK_LIST_SIZE 8

// total size: 0x14
typedef struct _shTskEXECUTE {
    // Members
    void (*adrs)(void*); // offset 0x0, size 0x4
    void* next;          // offset 0x4, size 0x4
    void* prev;          // offset 0x8, size 0x4
    int mode;            // offset 0xC, size 0x4
    int atr;             // offset 0x10, size 0x4
} shTskEXECUTE;

// total size: 0x200
typedef struct _shTskTASK {
    // Members
    shTskEXECUTE exe;    // offset 0x0, size 0x14
    u_char freemem[492]; // offset 0x14, size 0x1EC
} shTskTASK;

void shTSKInitTaskList(u_char* buffer, u_int size);

shTskTASK* shTSKSetTask(void (* func)(void *), u_char num);

shTskTASK* shTSKSetTaskPrev(shTskTASK* task, void (* func)(void *));

void shTSKDelTask(shTskTASK* task);

shTskTASK* shTSKCutTask(shTskTASK* task);

void shTSKExecuteTask(u_char num);

shTskTASK* shTSKSearchTaskWithAtr(int atr, shTskTASK* start, u_char num);

void shTSKFreeTaskLine(u_char num);


extern shTskTASK* shTskTaskListTop[TASK_LIST_SIZE];

#endif // SHTSKMAN_H
