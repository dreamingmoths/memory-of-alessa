#ifndef LOADBG_EVENT_H
#define LOADBG_EVENT_H

#include "common.h"
#include "LoadBg/loadbg_mem.h"

void LoadBgEventInit(void* adr, u_int size);
void LoadBgEventFileLoad(fsFileIndex* fileid, void* adr);
void LoadBgEventLoadSync(void);
int LoadBgEventListCnt(void);
int LoadBgEventLoadCnt(void);
int LoadBgEventIsLoad(void);
void LoadBgEventDispose(void);

#endif // LOADBG_EVENT_H
