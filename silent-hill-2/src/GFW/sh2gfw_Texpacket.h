#ifndef SH2GFW_TEXPACKET_H
#define SH2GFW_TEXPACKET_H

#include "GFW/sh2gfw_alltexman.h"
#include "GFW/sh2gfw_structs.h"

extern int fake_cid[4];
extern int fake_slot[4];

void sh2gfw_allinit_TexMANlist(sh2gfw_ALLTEXSYNC_MAN* pATSM);

void sh2gfw_clear_TexMAN_TransParm(void);

sh2gfw_TexMAN* sh2gfw_set_TexToTrasMan(sh2gfw_ALLTEXSYNC_MAN* pATSM, sh2gfw_TEX_HEAD* pTexHead, sh2gfw_CLUTS_HEAD* pClutHead, void* pMAN, u_short mode);

sh2gfw_TexMAN* sh2gfw_del_TexMAN(sh2gfw_ALLTEXSYNC_MAN* pATSM, sh2gfw_TexMAN* pDel);

void sh2gfw_Change_TexBody(void* pT, void* texaddr);

void sh2gfw_Reset_TexBody(void* pT);

__int128* sh2gfw_Get_RegTEX0(sh2gfw_TexMAN* sTM, u_int clutid, u_int flg);

int sh2gfw_Get_TFX(void* sTMV, int clutid);

int sh2gfw_Thr_d2TextureSend(void* ptm, int mode, int* cid, int* slotid);

int sh2gfw_Thr_d1d2SyncKick(void* pkaddr, int cid, int slotid);

void sh2gfw_Lock_AllTexSlot_For_Shadow(void);

void sh2gfw_UnLock_AllTexSlot_For_Shadow(void);

void sh2gfw_init_TexTrans_Manage_Table(void);

int sh2gfw_EnQue_TexSlot(void* pTexMan);

int sh2gfw_SetSlot2Tex(sh2gfw_TexMAN* sTM, int slotno, int mode);

#endif // SH2GFW_TEXPACKET_H
