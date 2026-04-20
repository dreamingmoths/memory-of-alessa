#include "clani.h"

static u_int DataId(void* data);
static u_int NClusters(void* data);
static u_int NFrames(void* data);
static void* NthCluster(void * data, int n);
static float CalcDummy(void);
static float Calc1(void* cluster, int frame, int n_frames, short f_counter);
static void ClearWeights(shClusterAnime* cap);

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

// size: 0x8, address: 0x2A9530
static CalcFunc calc_func_list[2] = {
    NULL,
    Calc1
}; 

ClusterAnimeWork sh2cluster;
float cluster_weight_data[32][20]; // size: 0xA00, address: 0x418780

static u_int DataId(void* data) { Header* header = data; return header->id; }

static u_int NClusters(void* data) { Header* header = data; return header->n_clusters; }

static u_int NFrames(void* data) { Header* header = data; return header->n_frames; }

static void* NthCluster(void * data, int n) { Header* header = data; return (void*)((u_int) data + header->offsets[n]); }

static float CalcDummy(void) {
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/clani", Calc1);

void shCharacterInitCluster(void) {
    memset(&sh2cluster, NULL, sizeof sh2cluster);
}

#line 346
shClusterAnime* ClusterAnimeNew(int n_clusters, int index) {


















    
    shClusterAnime* cap = &sh2cluster.ca[index];
    
    memset(cap, NULL, sizeof *cap);
    cap->used = 1;
    cap->n_clusters = n_clusters;
    if (n_clusters) {
        cap->weights = cluster_weight_data[index];
        ASSERT(cap->weights);
    }
    
    return cap;
}

#line 387
void ClusterAnimeDelete(shClusterAnime* cap, int index) {
    if (!cap) {
        return;
    }
    if (!cap->used) {
        return;
    }
    memset(cluster_weight_data[index], NULL, sizeof cluster_weight_data[index]);
}

#line 401
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
    } }


#line 423
void ClusterAnimeSet(shClusterAnime* cap, void* data) {
    int n_clusters; // r2

    int data_id; // r2

    
    if (cap == NULL) {
        return;
    }
        
    if (data == NULL) {
        cap->data = NULL;
        ClearWeights(cap);
        return;
    }
    
    data_id = DataId(data);
    if ((data_id != 0x29843918) && (data_id != 0x29853918)) {
        printf("ClusterAnimeSet: illegal data\n");
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

void ClusterAnimeExec(shClusterAnime* cap, shAnime3d* ap) {
    Header * header; // r2
    int n_frames; // r16
    int n_clusters; // r17
    int frame; // r18
    int revision; // r2
    int total_counter; // r3
    short frame_counter; // r19
    
    CalcFunc calc_func = NULL; // r20
    int i; // r21
    void * cluster; // r2






















    if (!cap) {
        return;
    }
    if (!cap->used) {
        return;
    }
    if (!cap->data) {
        return;
    }

    header = cap->data;
    n_frames = NFrames(header);
    
    if (cap->frame_updated) {
        
        cap->frame_updated = 0;
        
        frame_counter = 0;
    } else {

        
        total_counter = ap->total_count;
        frame_counter = total_counter & 4095;
        cap->frame_no = total_counter >> 0xC;
    }

    
    if (ap->anim_a->loop) {
        if (cap->frame_no >= n_frames) {
    
            cap->frame_no -= n_frames;
        }
    } else {
        if (cap->frame_no >= n_frames - 1) {
            cap->frame_no = n_frames - 1;
            
            frame_counter = 0;
        }
    }
    
    if (cap->frame_no < 0) {
    
        cap->frame_no = 0;
        
        
        frame_counter = 0;
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
            
            frame_counter
        );

        
    }











    
}

#line 644
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

