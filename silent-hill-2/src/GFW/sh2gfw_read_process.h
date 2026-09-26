#ifndef SH2GFW_READ_PROCESS_H
#define SH2GFW_READ_PROCESS_H

#include "sh2_common.h"
#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_blockman.h"
#include "GFW/sh2gfw_alltexman.h"

void sh2gfw_Set_TrTex(void* pT);
int sh2gfw_LoadSet_SemiTransTEX(int mapid, void* fl);
void sh2gfw_LOAD_AREADATA_ID(u_int stage);

int sh2gfw_Process_AREAtoMAN(Q_WORDDATA* d_h /* r18 */, sh2gfw_Area_Data_Man* pAMAN /* r17 */, sh2gfw_ALLTEXSYNC_MAN* pATSM /* r16 */);

u_int sh2gfw_process_AreaDATA(u_int map_id, sh2gfw_Area_Data_Man* pAMAN);

void sh2gfw_Free_BlockLocalTex(sh2gfw_ALLTEXSYNC_MAN* pATSM, sh2gfw_BLOCK_MAN* pB_man);

void sh2gfw_AllClear_TrMAN(void);

u_int sh2gfw_process_blockLOCAL_main(
    Q_WORDDATA* datahead /* r22 */,
    sh2gfw_BLOCK_MAN * pB_man /* r21 */,
    sh2gfw_Area_Data_Man* pA_man /* r20 */,
    Q_WORDDATA* b_pack /* r19 */,
    Q_WORDDATA* g_pack /* r18 */, 
    Q_WORDDATA* t_pack /* r30 */, 
    int stid /* r29+0xA4 */, 
    int mapid /* r23 */
); 

void sh2gfw_Set_GB_Tex(void* addr);
void sh2gfw_Delete_GB_Tex(void);
void sh2gfw_Set_TR_Tex(void* addr);
void sh2gfw_Delete_TR_Tex(void);
void sh2gfw_Set_BlockLocal(int slot, void* addr, int mapid);
void sh2gfw_Delete_BlockLocal(int slot);

#endif // SH2GFW_READ_PROCESS_H
