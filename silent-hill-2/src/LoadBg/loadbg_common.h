#ifndef LOADBG_COMMON_H
#define LOADBG_COMMON_H

#include "types.h"
#include "data/fs_structs.h"

int _loadBgCommon_LoadData(void* loadbuf, fsFileIndex* file, int limit);

int BPOSfromFPOS(float f);

float FPOSfromBPOS(int i);

int loadBgCommon_SetInfo(int glb_crd, float px, float pz);

int loadBgCommon_HideMapBlockOutdoor(int mapid);

#endif // LOADBG_COMMON_H
