#include "common.h"
#include "Chacter_Draw/clani.h"

static u_int DataId(void* data);
static u_int NClusters(void* data);
static u_int NFrames(void* data);
static void* NthCluster(void * data, int n);
static float CalcDummy(void);
static float Calc1(void* cluster, int frame, int n_frames, short f_counter);
static void ClearWeights(shClusterAnime* cap);
float func_001404C0(void);

ClusterAnimeWork sh3cluster;

const static CalcFunc calc_func_list[2] __attribute__((section(".rodata"))) = {
    func_001404C0,
    Calc1
}; 

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

void ClusterAnimeSet(shClusterAnime* cap, void* data) {
    int n_clusters;

    int data_id;

    
    if (!cap) {
        return;
    }
        
    if (!data) {
        cap->data = NULL;
        ClearWeights(cap);
        return;
    }
    
    data_id = DataId(data);
    if (data_id != 0x29843918 && data_id != 0x29853918) {
        printf("ClusterAnimeSet: illegal data\n\0");
        return;
    }
    
    n_clusters = NClusters(data);
    if (n_clusters != cap->n_clusters) {
        printf("ClusterAnimeSet: n_clusters mismatch\n");
        return;
    }
    
    cap->data = data;
    cap->frame_no = 0;
    cap->frame_updated = 1;
}

void ClusterAnimeExec(shClusterAnime* cap, shAnime3dNew* ap) {
    int sp9C;
    float sp98;
    Header * header;
    int n_frames;
    int n_clusters;
    int frame;
    int revision;
    int total_counter;
    float var_f20;
    
    CalcFunc calc_func = NULL;
    int i;
    void * cluster;

    if (!cap) {
        return;
    }
    if (!cap->used) {
        return;
    }

    func_0020F070(ap->unkC, ap->unkE, &sp9C, &sp98);
    header = cap->data;
    if (!cap->data) {
        return;
    }
    if (!sp9C) {
        return;
    }

    n_frames = NFrames(header);
    
    if (cap->frame_updated) {
        var_f20 = 0.0f;
        cap->frame_updated = 0;
    } else {
        cap->frame_no = sp98;
        var_f20 = sp98 - cap->frame_no;

        if (var_f20 > 0.01f && func_002A4280()) {
            var_f20 = 0.0f;
            cap->frame_no++;
        }
    }

    if (cap->frame_no >= n_frames - 1) {
        var_f20 = 0.0f;
        cap->frame_no = n_frames - 1;
    }
    
    if (cap->frame_no < 0) {
        var_f20 = 0.0f;
        cap->frame_no = 0;
    }
    
    frame = cap->frame_no;
    
    revision = header->revision;
    
    if (revision < 2u) {
        calc_func = calc_func_list[revision];
    }
    
    if (!calc_func) {
        calc_func = CalcDummy;
    }
    
    n_clusters = NClusters(header);
    
    for (i = 0; i < n_clusters; i++) {
        cluster = NthCluster(cap->data, i);
        cap->weights[i] = calc_func(
            cluster,
            frame,
            n_frames,  
            var_f20
        );   
    }
}

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
