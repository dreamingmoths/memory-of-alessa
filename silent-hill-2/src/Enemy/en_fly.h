#ifndef EN_FLY_H
#define EN_FLY_H

typedef struct EN_FLY_DATA {
    // total size: 0x2D0
    SubCharacter scp; // offset 0x0, size 0x1F0
    EnLOCAL_DATA dp; // offset 0x1F0, size 0xE0
} EN_FLY_DATA;

#endif // EN_FLY_H
