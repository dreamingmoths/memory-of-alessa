#include "common.h"
#include "clani.h"

static u_int DataId(void* data);
static u_int NClusters(void* data);
static u_int NFrames(void* data);
static void* NthCluster(void * data, int n);
static float CalcDummy(void);
static float Calc1(void* cluster, int frame, int n_frames, short f_counter);
static void ClearWeights(shClusterAnime* cap);
float func_001404C0(void);

ClusterAnimeWork sh3cluster;

typedef struct Header {
    // total size: 0x10
    u_int id; // offset 0x0, size 0x4
    u_short revision; // offset 0x4, size 0x2
    u_short flag; // offset 0x6, size 0x2
    u_short n_clusters; // offset 0x8, size 0x2
    u_short reserved_0; // offset 0xA, size 0x2
    u_short n_frames; // offset 0xC, size 0x2
    u_short reserved_1; // offset 0xE, size 0x2
    u_int offsets[]; // offset 0x10, size 0x0
} Header;

static u_int DataId(void* data) { Header* header = data; return header->id; }

static u_int NClusters(void* data) { Header* header = data; return header->n_clusters; }

static u_int NFrames(void* data) { Header* header = data; return header->n_frames; }

static void* NthCluster(void * data, int n) { Header* header = data; return (void*)((u_int) data + header->offsets[n]); }

static float CalcDummy(void) {
    return 0.0f;
}

static void ClearWeights(shClusterAnime* cap) {
    int n_clusters;
    float* weights;
    int i;

    if (!cap) {
        return;
    }

    n_clusters = cap->n_clusters;
    weights = cap->weights;
    for (i = 0; i < n_clusters; i++) {
        weights[i] = 0.0f;
    }
}

float func_001404C0(void) {
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/clani", Calc1);

void shCharacterInitCluster(void) {
    memset(&sh3cluster, NULL, sizeof sh3cluster);
}

shClusterAnime* ClusterAnimeNew(int n_clusters, int index) {
    shClusterAnime* cap = &sh3cluster.ca[index];
    
    memset(cap, NULL, sizeof *cap);
    cap->used = 1;
    cap->n_clusters = n_clusters;
    if (n_clusters) {
        cap->weights = sh3cluster.cluster_weight_data[index];
        ASSERT(cap->weights);
    }
    
    return cap;
}

void ClusterAnimeDelete(shClusterAnime* cap, int index) {
    if (!cap) {
        return;
    }
    if (!cap->used) {
        return;
    }
    memset(sh3cluster.cluster_weight_data[index], NULL, sizeof sh3cluster.cluster_weight_data[index]);
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/clani", ClusterAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/clani", ClusterAnimeExec);

float* ClusterAnimeGetWeights(shClusterAnime* cap, float* weights) {
    int n_clusters;
    int i;

    ASSERT(cap);
    ASSERT(cap->used);

    n_clusters = cap->n_clusters;

    for (i = 0; i < n_clusters; i++) {
        weights[i] = cap->weights[i];
    }
    
    return weights;
}
