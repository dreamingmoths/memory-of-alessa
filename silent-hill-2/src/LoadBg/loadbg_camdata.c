#include "LoadBg/loadbg_camdata.h"
#include "LoadBg/loadbg_cam.h"

// @todo: migrate rodata

extern int CAMsize[1]; // size: 0x4, address: 0x11EACE0
extern char CAMbuf[1][2048]; // size: 0x800, address: 0x11EAD00

static int BgCam_LoadData(void* loadbuf, fsFileIndex* file);

static int BgCam_LoadData(void* loadbuf, fsFileIndex* file) {
    return _loadBgCommon_LoadData(loadbuf, file, 0x800);
}

void loadBgCAM_LoadData(int slot, fsFileIndex* file, int mapid) {
    ASSERT_ON_LINE(0<=slot && slot<VC_DATA_MAX, 30);
    loadBgCAM_ReplaceG(0, NULL, 0);
    CAMsize[slot] = BgCam_LoadData(CAMbuf[slot], file);
    loadBgCAM_ReplaceG(mapid, CAMbuf[slot], CAMsize[slot]);

}
