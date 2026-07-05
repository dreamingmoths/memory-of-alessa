#ifndef CLANI_SHARED_H
#define CLANI_SHARED_H

#include "common.h"

#define CLANI_FRAME_DURATION (1.0f / 4096.0f)

typedef struct _USXY {
    // total size: 0x4
    u_short x; // offset 0x0, size 0x2
    u_short y; // offset 0x2, size 0x2
} USXY;

typedef struct _SXY {
    // total size: 0x4
    short x; // offset 0x0, size 0x2
    short y; // offset 0x2, size 0x2
} SXY;

typedef struct _IXY {
    // total size: 0x8
    int x; // offset 0x0, size 0x4
    int y; // offset 0x4, size 0x4
} IXY;

typedef struct _AnimeInfo {
    // total size: 0xC
    u_short name;  // offset 0x0, size 0x2
    u_short frame; // offset 0x2, size 0x2
    short speed;   // offset 0x4, size 0x2
    u_short start; // offset 0x6, size 0x2
    u_short end;   // offset 0x8, size 0x2
    u_char loop;   // offset 0xA, size 0x1
    char pad;      // offset 0xB, size 0x1
} AnimeInfo;


typedef struct shClusterAnime {
    // total size: 0x10
    void* data;           // offset 0x0, size 0x4
    u_char used;          // offset 0x4, size 0x1
    u_char n_clusters;    // offset 0x5, size 0x1
    u_char is_repeat;     // offset 0x6, size 0x1
    u_char frame_updated; // offset 0x7, size 0x1
    int frame_no;         // offset 0x8, size 0x4
    float* weights;       // offset 0xC, size 0x4
} shClusterAnime;

typedef struct Element1 {
    // total size: 0x4
    u_short frame; // offset 0x0, size 0x2
    short weight;  // offset 0x2, size 0x2
} Element1;
typedef struct Cluster1 {
    // total size: 0x2
    u_short n_keys;             // offset 0x0, size 0x2
    struct Element1 elements[]; // offset 0x2, size 0x0
} Cluster1;

#endif // CLANI_SHARED_H
