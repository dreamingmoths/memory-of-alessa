#ifndef CL_MAIN_H
#define CL_MAIN_H

typedef struct _CL_HITPOLY_PLANE
{
    // total size: 0x50
    unsigned char kind;    // offset 0x0, size 0x1
    unsigned char shape;   // offset 0x1, size 0x1
    unsigned short pad;    // offset 0x2, size 0x2
    unsigned int weight;   // offset 0x4, size 0x4
    unsigned int material; // offset 0x8, size 0x4
    signed int flg;        // offset 0xC, size 0x4
    float p[4][4];         // offset 0x10, size 0x40
} CL_HITPOLY_PLANE;

#endif

