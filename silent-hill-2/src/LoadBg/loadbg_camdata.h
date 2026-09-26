#ifndef LOADBG_CAMDATA_H
#define LOADBG_CAMDATA_H

#include "sh2_common.h"
#include "data/fs_structs.h"

#define VC_DATA_MAX 1

void loadBgCAM_LoadData(int slot, fsFileIndex* file, int mapid);

#endif // LOADBG_CAMDATA_H
