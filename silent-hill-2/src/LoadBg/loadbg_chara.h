#ifndef LOADBG_CHARA_H
#define LOADBG_CHARA_H

void LoadBgCharaInit(void);

int LoadBgCharaIsLoad(void);

int LoadBgCharaIsLoadSlot(int no);

int LoadBgCharaIsMapEdge(void);

void LoadBgCharaLoadSync(void);

void LoadBgGetUraCharaSlot(void** slot0, void** slot1);

#endif // LOADBG_CHARA_H
