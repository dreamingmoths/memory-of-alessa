#ifndef FILESLIST_BG_H
#define FILESLIST_BG_H

#include "common.h"

// total size: 0x10
typedef struct fsMgcFile {
    // Members
    int type : 8;         // offset 0x0, size 0x4
    int padding : 24;     // offset 0x0, size 0x4
    union fsFile* parent; // offset 0x4, size 0x4
    char* start;          // offset 0x8, size 0x4
    char* end;            // offset 0xC, size 0x4
} fsMgcFile;

// total size: 0x10
typedef struct fsCdFile {
    // Members
    int type : 8;    // offset 0x0, size 0x4
    int number : 24; // offset 0x0, size 0x4
    char* name;      // offset 0x4, size 0x4
    int lsn;         // offset 0x8, size 0x4
    int size;        // offset 0xC, size 0x4
} fsCdFile;

// total size: 0x10
typedef struct fsHdFile {
    // Members
    int type : 8;     // offset 0x0, size 0x4
    int padding : 24; // offset 0x0, size 0x4
    char* name;       // offset 0x4, size 0x4
    int offset;       // offset 0x8, size 0x4
    int size;         // offset 0xC, size 0x4
} fsHdFile;

// total size: 0x10
typedef struct fsMgpFile {
    // Members
    int type : 8;            // offset 0x0, size 0x4
    int padding : 24;        // offset 0x0, size 0x4
    union fsFile* file;      // offset 0x4, size 0x4
    struct fsMgcFile* start; // offset 0x8, size 0x4
    struct fsMgcFile* end;   // offset 0xC, size 0x4
} fsMgpFile;

// total size: 0x10
typedef struct fsMgfFile {
    // Members
    int type : 8;         // offset 0x0, size 0x4
    int padding : 24;     // offset 0x0, size 0x4
    union fsFile* parent; // offset 0x4, size 0x4
    int offset;           // offset 0x8, size 0x4
    int size;             // offset 0xC, size 0x4
} fsMgfFile;

typedef union fsFile {
    // total size: 0x10
    struct /* @anon5 */ {
        // Members
        int type : 8;     // offset 0x0, size 0x4
        int number : 24;  // offset 0x0, size 0x4
        int pad0;         // offset 0x4, size 0x4
        int pad1;         // offset 0x8, size 0x4
        int pad2;         // offset 0xC, size 0x4
    } check;              // offset 0x0, size 0x10
    u_long128 pack;       // offset 0x0, size 0x10
    struct fsCdFile cd;   // offset 0x0, size 0x10
    struct fsHdFile hd;   // offset 0x0, size 0x10
    struct fsMgcFile mgc; // offset 0x0, size 0x10
    struct fsMgfFile mgf; // offset 0x0, size 0x10
    struct fsMgpFile mgp; // offset 0x0, size 0x10
} fsFile;

typedef union fsFileIndex {
    // total size: 0x8
    struct /* @anon0 */ {
        // Members
        union fsFile* fp; // offset 0x0, size 0x4
        char* name;       // offset 0x4, size 0x4
    } index;              // offset 0x0, size 0x8
    unsigned long pack;   // offset 0x0, size 0x4
} fsFileIndex;

// total size: 0x20
typedef struct FilesBgBlock {
    // Members
    fsFileIndex* map; // offset 0x0, size 0x4
    fsFileIndex* cld; // offset 0x4, size 0x4
    fsFileIndex* cam; // offset 0x8, size 0x4
    fsFileIndex* kg2; // offset 0xC, size 0x4
    fsFileIndex* tex; // offset 0x10, size 0x4
    fsFileIndex* ex0; // offset 0x14, size 0x4
    fsFileIndex* ex1; // offset 0x18, size 0x4
    fsFileIndex* ex2; // offset 0x1C, size 0x4
} FilesBgBlock;

typedef enum STAGE_ID {
    BG_ID_null = 0,
    BG_ID_ap = 9,
    BG_ID_bw = 7,
    BG_ID_ca = 1,
    BG_ID_cb = 2,
    BG_ID_cc = 3,
    BG_ID_cd = 4,
    BG_ID_er = 6,
    BG_ID_hp = 10,
    BG_ID_ps = 11,
    BG_ID_ob = 5,
    BG_ID_rr = 12,
    BG_ID_ru = 13,
    BG_ID_th = 8,
    BG_ID_qp = 14,
    BG_ID_qt = 15,
    BG_ID_ma = 16,
    BG_ID_num = 17,
} STAGE_ID;

// total size: 0x10
struct FilesBgRoom {
    // Members
    struct FilesBgBlock* block[4]; // offset 0x0, size 0x10
};

// total size: 0x10
typedef struct FilesBgStage {
    // Members
    struct FilesBgBlock** block_list; // offset 0x0, size 0x4
    int* block_max;                   // offset 0x4, size 0x4
    struct FilesBgRoom** room_list;   // offset 0x8, size 0x4
    int* room_max;                    // offset 0xC, size 0x4
} FilesBgStage;

extern struct FilesBgStage* FilesBgStageList[17];
extern int FilesBgStageMax[1];

#endif