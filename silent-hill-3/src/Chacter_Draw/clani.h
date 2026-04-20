#ifndef CLANI_H
#define CLANI_H

#include "Chacter/character.h"

typedef float (*CalcFunc)(void *, int, int, float);

/**
 * total size: 0x1600
 * @note `cluster_weight_data` added to this struct
 */
typedef struct ClusterAnimeWork {
    struct shClusterAnime ca[32]; // offset 0x0, size 0x200
    float cluster_weight_data[32][40]; // offset 0x200, size: 0x1400
} ClusterAnimeWork;

typedef struct shAnime3dNew {
    u_char unk0[0xC];
    u_short unkC;
    u_short unkE;
} shAnime3dNew;

extern ClusterAnimeWork sh3_cluster;

#endif // CLANI_H
