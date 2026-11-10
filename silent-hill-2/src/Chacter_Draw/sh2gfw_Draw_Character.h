#ifndef SH2GFW_DRAW_CHARACTER_H
#define SH2GFW_DRAW_CHARACTER_H

#include "sh2_common.h"

void sh2gfw_set_d1cid(void);
void sh2gfw_sync_d1cid(void);
void sh2gfw_Exec_AnimeAndCollision(void);
void sh2gfw_Exec_Character_Draw(float (* wld_scr)[4], int comm);
void sh2gfw_Exec_Character_Draw_ShadowOnly(void);
int sh2_Model_SyncOT(void* pktop);
int sh2_Model_DummySyncOT(void);
int sh2gfw_get_ModelChangeTB(int texno);
int sh2gfw_get_ModelIndexTB(int texno);
void sh2gfw_Thr_Chracter_d1d2SyncKick(void* pktop, int index);
int sh2gfw_get_Charaid(void);
int sh2gfw_get_TBChangeVU1num(void);
void sh2gfw_set_CharaD1CID(int cid);
void sh2gfw_SetNoise_CharaTexture(int charaid);
void sh2gfw_RemoveNoise_CharaTexture(int charaid);

#endif // SH2GFW_DRAW_CHARACTER_H
