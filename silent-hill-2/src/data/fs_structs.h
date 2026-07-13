#ifndef SH_FS_STRUCTS_H
#define SH_FS_STRUCTS_H

#include "sce/eetypes.h"

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

#endif // SH_FS_STRUCTS_H
 