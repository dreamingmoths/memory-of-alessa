#ifndef LAKE_WAVE_H
#define LAKE_WAVE_H

typedef struct _shLakeWaveInfo {
    // total size: 0x14
    float distance[2]; // offset 0x0, size 0x8
    float energy; // offset 0x8, size 0x4
    float timer; // offset 0xC, size 0x4
    s_char prev; // offset 0x10, size 0x1
    s_char next; // offset 0x11, size 0x1
} shLakeWaveInfo;


void mizTestLakeWaveInit(void);

shLakeWaveInfo* mizTestLakeWaveMain(struct SubCharacter* scp /* r21 */);

#endif // LAKE_WAVE_H
