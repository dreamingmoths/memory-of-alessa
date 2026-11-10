#include "DBG/sh2gfw_SyncDBG.h"

static int DBG_Perf_index = 0; // size: 0x4, address: 0x491820
int Index_VertNum = 0; // size: 0x4, address: 0x491828
int Index_SemiTrans = 0; // size: 0x4, address: 0x491830
int DBG_Perf[16]; // size: 0x40, address: 0x491880
int SemiTransTex_VertNum[6]; // size: 0x18, address: 0x491860
static int Vertex_Num[6]; // size: 0x18, address: 0x491840

void sh2gfw_Init_AllVertCounter(void) {
    int i; // r4

    for (i = 0; i < 6; i++) {
        SemiTransTex_VertNum[i] = 0;
        Vertex_Num[i] = 0;
    }
    Index_SemiTrans = 0;
    Index_VertNum = 0;
}

void sh2gfw_Incliment_VertNumIndices(void) {
    Index_SemiTrans++;
    Index_VertNum++;
}

void sh2gfw_Add_SemiTransVertNum(int num /* r2 */) {
    SemiTransTex_VertNum[Index_SemiTrans] += num;
}

void sh2gfw_Add_VertexNum(int num /* r2 */) {
    Vertex_Num[Index_VertNum] += num;
}

void sh2gfw_init_Perf(void) {
    DBG_Perf_index = 0;
}

void sh2gfw_Store_Perf2(int count /* r2 */, int md /* r2 */) {
    DBG_Perf[md] = count;
}
