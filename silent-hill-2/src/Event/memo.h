#ifndef MEMO_H
#define MEMO_H

#include "common.h"
#include "FilesList/fileslist_bg.h"

// total size: 0x10
typedef struct Memo_Data { // this was anon
    // Members
    short flag;               // offset 0x0, size 0x2
    short status;             // offset 0x2, size 0x2
    short msg_label;          // offset 0x4, size 0x2
    short msg_memo;           // offset 0x6, size 0x2
    union fsFileIndex* file0; // offset 0x8, size 0x4
    union fsFileIndex* file1; // offset 0xC, size 0x4
} Memo_Data;

extern int select;
extern int list_point;
extern int disp_point;

extern fsFileIndex data_pic_etc_p_memo_tex[1];

extern char* layer_adr;

void MemoMain(void);
int MemoCommandCheck(void);

#endif // MEMO_H
