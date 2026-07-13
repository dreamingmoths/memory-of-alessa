#include "common.h"
#include "sce/libvifpk.h"
#include "sce/eestruct.h"
#include "sce/libdma.h"
#include "Chacter_Draw/vifot/sh_kt_vif0pkbuf.h"
#include "Chacter_Draw/model_common.h"
#include "Chacter_Draw/model3_n.h"
#include "Chacter_Draw/model3_sub_n.h"
#include "shared/Chacter_Draw/model3_cluster_n.h"

// @todo migrate bss
#define initialized initialized_0x01EE2F98

static void LoadProgram(void);
static void MakeTransferDefaultClusterNodesPacket(u_long128* packet_buffer, DefaultClusterNode* nodes_top, int n_nodes);
static void TransferDefaultClusterNodes(Model* model);
static void MakeApplyClusterPacket(u_long128* packet_buffer, ClusterElement* top, int n, float weight);
static void ApplyCluster(Model* model, Cluster* cluster, float weight);

extern u_long128 model3_mpg0_cluster_load[];

static void LoadProgram(void) {
    extern /* static */ int initialized;
    extern /* static */ u_long packet_buffer[4];
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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_cluster_n", TransferDefaultClusterNodes);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_cluster_n", MakeApplyClusterPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_cluster_n", ApplyCluster);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_cluster_n", func_001D2510);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_cluster_n", Model3UpdateClusters);
