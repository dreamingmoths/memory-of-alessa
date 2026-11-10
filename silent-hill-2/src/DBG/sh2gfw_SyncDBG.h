#ifndef SH2GFW_SYNCDBG_H
#define SH2GFW_SYNCDBG_H

#define DRAW_MAIN_PERF_MD 8

void sh2gfw_Init_AllVertCounter(void);

void sh2gfw_Incliment_VertNumIndices(void);

void sh2gfw_Add_SemiTransVertNum(int num /* r2 */);

void sh2gfw_Add_VertexNum(int num /* r2 */);

void sh2gfw_init_Perf(void);

void sh2gfw_Store_Perf2(int count /* r2 */, int md /* r2 */);

#endif // SH2GFW_SYNCDBG_H
