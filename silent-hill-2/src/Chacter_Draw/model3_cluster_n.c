#include "common.h"
#include "sce/libvifpk.h"
#include "sce/libvu0.h"
#include "sce/eestruct.h"
#include "sce/libdma.h"
#include "Chacter_Draw/vifot/sh_kt_pkbuf.h"
#include "Chacter_Draw/vifot/sh_kt_vif0pkbuf.h"
#include "Chacter_Draw/model_common.h"
#include "Chacter_Draw/model3_n.h"
#include "Chacter_Draw/model3_sub_n.h"
#include "shared/Chacter_Draw/model3_cluster_n.h"

static void LoadProgram(void);
static void MakeTransferDefaultClusterNodesPacket(u_long128* packet_buffer, DefaultClusterNode* nodes_top, int n_nodes);
static void TransferDefaultClusterNodes(Model* model);
static void MakeApplyClusterPacket(u_long128* packet_buffer, ClusterElement* top, int n, float weight);
static void ApplyCluster(Model* model, Cluster* cluster, float weight);

extern u_long128 model3_mpg0_cluster_load[];

typedef u_long PacketBuffer[4] __attribute__((aligned(32)));

static void LoadProgram(void) {
    static int initialized = 0;
    static PacketBuffer packet_buffer;
    if (initialized == 0) {
        sceVif0Packet packet;
        sceVif0Packet* pk = &packet;
        sceVif0PkInit(pk, (void*) READ_UNCACHED(&packet_buffer));
        sceVif0PkCall(pk, &model3_mpg0_cluster_load, 0);
        sceVif0PkEnd(pk, 0);
        sceVif0PkTerminate(pk);
        initialized = 1;
    }
    ktVif0Send(packet_buffer, 1);
}

static void MakeTransferDefaultClusterNodesPacket(u_long128* packet_buffer, DefaultClusterNode* nodes_top, int n_nodes) {
    sceVif0Packet packet;
    sceVif0Packet* pk = &packet;
    int qwc = (u_int) ((n_nodes * 6) + 15) / 16;

    sceVif0PkInit(pk, (u_long128*) READ_UNCACHED(packet_buffer));
    sceVif0PkRef(pk, nodes_top, qwc,
                 SCE_VIF0_SET_ITOP(n_nodes - 1, 0),
                 SCE_VIF0_SET_UNPACK(0, (u_char) n_nodes, SCE_VIF_UPK_V3_16, 0), 0);
    sceVif0PkEnd(pk, 0);
    sceVif0PkAddCode(pk, SCE_VIF0_SET_CODE(0, 0, SCE_VIF_MSCAL,  0));
    sceVif0PkAddCode(pk, SCE_VIF0_SET_CODE(0, 0, SCE_VIF_FLUSHE, 0));
    sceVif0PkTerminate(pk);
}

void TransferDefaultClusterNodes(Model* model) {
    int n_cluster_nodes = model->n_cluster_nodes; // r16
    sceVu0FVECTOR* cluster_nodes = model3_junk.cluster_nodes; // r17
    DefaultClusterNode* default_cluster_nodes = (u_char*) model + model->cluster_nodes_offset ; // r18
    int i = 0; // r19

    while (i < n_cluster_nodes) {
        int n_rest_nodes = n_cluster_nodes - i;
        int n_nodes = n_rest_nodes < 0x100 ? n_rest_nodes : 0x100;
        int sadr = (i < MAX_N_CLUSTERS ? i : MAX_N_CLUSTERS) * 16; // r20

        sceDmaChan* fromSPR;
        sceDmaChan* toSPR;
        u_long128* packet_buffer = ktVif0PkBufNext();
        MakeTransferDefaultClusterNodesPacket(packet_buffer, &default_cluster_nodes[i], n_nodes);
        ktVif0Send(packet_buffer, 1);
        ktVif0Wait2();
        
        
        
        
        toSPR = sceDmaGetChan(SCE_DMA_toSPR);
        toSPR->sadr = (void*) sadr;
        sceDmaSendN(toSPR, (void*) VU0_MEM, n_nodes);
        
        BLOCK_WHILE(sceDmaSync(toSPR, 0, 0));
        
        
        
        if (i >= MAX_N_CLUSTERS) {
        
            
            fromSPR = sceDmaGetChan(SCE_DMA_fromSPR);
            fromSPR->sadr = (void*) sadr;
            sceDmaSendN(fromSPR, cluster_nodes[i], n_nodes);
            
            BLOCK_WHILE(sceDmaSync(fromSPR, 0, 0));
        }
        
        i += n_nodes;
    }
}

#line 133
void MakeApplyClusterPacket(u_long128* packet_buffer, ClusterElement* top, int n, float weight) {
    sceVif0Packet packet;
    sceVif0Packet* pk = &packet;
    int qwc = (u_int) ((n * 8) + 15) / 16;

    sceVif0PkInit(pk, (u_long128*) READ_UNCACHED(packet_buffer));
    sceVif0PkRef(pk, top, qwc,
                 SCE_VIF0_SET_ITOP(n - 1, 0),
                 SCE_VIF0_SET_UNPACK(0, n, SCE_VIF_UPK_V4_16, 0), 0);
    sceVif0PkEnd(pk, 0);
    sceVif0PkAddCode(pk, SCE_VIF0_SET_CODE(n, 1, SCE_VIF_UNPACK,  0));
    sceVif0PkAddData(pk, reinterpret_as_u_int(weight));
    sceVif0PkAddCode(pk, SCE_VIF0_SET_CODE(2, 0, SCE_VIF_MSCAL,  0));
    sceVif0PkAddCode(pk, SCE_VIF0_SET_CODE(0, 0, SCE_VIF_FLUSHE, 0));
    sceVif0PkTerminate(pk);
}

#ifdef NON_MATCHING
#define CLUSTER_SPR_ADR 0x3000
#define MAX_N_CLUSTERS  0x300

static void ApplyCluster(Model* model, Cluster* cluster, float weight) {
    sceVu0FVECTOR* cluster_nodes = model3_junk.cluster_nodes; // r16
    int n_nodes = cluster->n_nodes; // r17
    ClusterElement* elements = (u_char*) model + cluster->element_offset; // r18
    int i = 0; // r19

    while (i < n_nodes) {
        int n_rest_nodes = n_nodes - i; 
        int n = n_rest_nodes < 0xF0 ? n_rest_nodes : 0xF0;
        int itop; // r2

        
        u_long128* packet_buffer; // r20
        packet_buffer = ktVif0PkBufNext();
        MakeApplyClusterPacket(packet_buffer, &elements[i], n, weight);
        ktVif0Send(packet_buffer, 1);
        ktVif0Wait2();
        {
            sceDmaChan* toSPR; // r20
            sceVu0FVECTOR* spr; // r2

            toSPR = sceDmaGetChan(SCE_DMA_toSPR);
            toSPR->sadr = (void*) CLUSTER_SPR_ADR;
            sceDmaSendN(toSPR, (void*) VU0_MEM, n);
            
            BLOCK_WHILE(sceDmaSync(toSPR, 0, 0));
            
            {
                Q* top; /* r2 */
                Q* end; /* r20 */
                Q* p; /* r21 */
                itop = SCRATCHPAD_START | CLUSTER_SPR_ADR;
                
                end = (Q*) itop + n;
                
                for (p = (Q*) itop; p < end; p++) {
                    int index = p->iv[3];
                    float* v = (float*) ((index < MAX_N_CLUSTERS) ? (sceVu0FVECTOR*) SCRATCHPAD_START + index : &cluster_nodes[index]);
                    sceVu0AddVector(v, v, p->fv);
                }
            }
            
            i += n;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_cluster_n", ApplyCluster);
#endif

void Model3UpdateClusters(Model* model, ModelWork* work) {
    int n_cluster_nodes = model->n_cluster_nodes; // r16
    sceVu0FVECTOR* cluster_nodes; // r17
    Cluster* clusters; // r18
    if (n_cluster_nodes != 0) {
        int n_clusters; // r19
        int i; // r20

        
        LoadProgram();
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        model3_junk.cluster_nodes = &model_common_work->cluster_nodes;
        
        cluster_nodes = model3_junk.cluster_nodes;
        
        
        TransferDefaultClusterNodes(model);
        
        
        
        clusters = (u_char*) model + model->clusters_offset;
        n_clusters = model->n_clusters;
        
        for (i = 0; i < n_clusters; i++) {
            float weight = work->cluster_weights[i];
            if (weight) {
                Cluster* cluster = &clusters[i];
                ApplyCluster(model, cluster, weight);
            }
        }
        
        
        
        
        {
            sceDmaChan* fromSPR = sceDmaGetChan(SCE_DMA_fromSPR);
            sceVu0FVECTOR* spr = (void*) SCRATCHPAD_START;
            int n = n_cluster_nodes < MAX_N_CLUSTERS ? n_cluster_nodes : MAX_N_CLUSTERS;
            int i;
        
            
            for (i = 0; i <  n; i++) {
                void* p = spr[i];
                ktVu0FTOI4VectorXYZ(p, p);
            }
            
            
            fromSPR->sadr = NULL;
            sceDmaSendN(fromSPR, cluster_nodes, n);
            
            
            for (; i <  n_cluster_nodes; i++) {
                void* p = cluster_nodes[i];
                ktVu0FTOI4VectorXYZ(p, p);
            }
            
            
            
            BLOCK_WHILE(sceDmaSync(fromSPR, 0, 0));
            
            
            
            SyncDCache(cluster_nodes, cluster_nodes[n_cluster_nodes]);
        }
    }
}
