#include "LoadBg/loadbg_common.h"
#include "LoadBg/loadbg_all.h"

#include "Event/stg_name.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

// @todo: migrate bss

extern /* static */ int init_507; // @ 0x011EB500

static int loadBgCommon_GetBlockNoOutdoor(int glb_crd, int bx, int bz);

int _loadBgCommon_LoadData(void* loadbuf, fsFileIndex* file, int limit) {
    int size; // r16
    int fid; // r2
    if (file != NULL) {
        size = FcGetFileSize(file);
        if (size > 0) {
            ASSERT_ON_LINE(size<=limit, 27);
            do {
                fid = FcRead(file, loadbuf);
            } while (fid == -1);
            
            fsSync(0, fid);
        } else {
            size = 0;
        }
    } else {
        size = 0;
    }
    return size;
}

int BPOSfromFPOS(float f) {
    int i; // r2
    int ret; // r2

    i = float_floor(f);
    if (i < 0) {
        ret = -((19999 - i) / 20000);
    } else {
        ret = i / 20000;
    }
    return ret;  
}

float FPOSfromBPOS(int i) {
    float ret;
    
    ret = fptosi(10000.0f + (20000.0f * i));
    
    
    
    
    
    return ret;
}

static int loadBgCommon_GetBlockNoOutdoor(int glb_crd, int bx, int bz) {
    int id; // r2
    int blocks[4]; // r29+0x20    
    loadBgCommon_Info_T* info = _loadBgCommon_Info; // r16
    BlockNumber(blocks, glb_crd, bx, bz);
    id = blocks[0] & 0xFFFF;
    
    if (info->hide_map != 0) 
        if (blocks[0] == info->hide_map)
            id = 0;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    return id;
}

#ifdef NON_MATCHING
int loadBgCommon_SetInfo(int glb_crd, float px, float pz) {
    loadBgCommon_Info_T* info = _loadBgCommon_Info; // r16
    int outdoor; // r17
    float bx; // r20
    float bz; // r21
    int ix; // r18
    int iz; // r19
    int icx; // r17
    int icz; // r18    
    int minx; // r20
    int minz; // r21
    float fcx; // r22    
    float fcz; // r23



    
    if (init_507 == 0) { init_507 = 1; loadBgAll_Init(); }
    

    
    info->hide_map = info->hide_map_request;
    info->hide_map_request = 0;

    
    if (glb_crd <= 0) return 0;
    
    info->glb_crd = glb_crd;

    
    icx = BPOSfromFPOS(px);
    icz = BPOSfromFPOS(pz);
    fcx = FPOSfromBPOS(icx);
    fcz = FPOSfromBPOS(icz);

    
    minx = icx - 2;
    minz = icz - 2;

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    info->px = px;
    info->pz = pz;
    info->fcx = fcx;
    info->fcz = fcz;
    info->icx = icx;
    info->icz = icz;
    info->minx = minx;
    info->minz = minz;
    outdoor = BgIsOut(glb_crd);
    info->outdoor = outdoor;
    info->RoomID = RoomName(glb_crd, fcx, fcz);

    
    for (ix = 0; ix < 5; ix++) {
        
        
        bx = FPOSfromBPOS(ix + minx);
        for (iz = 0; iz < 5; iz++) {
            
            
            bz = FPOSfromBPOS(minz + iz);
            
            
            
            
            
            info->AroundID[ix][iz] = (outdoor) ? loadBgCommon_GetBlockNoOutdoor(glb_crd, bx, bz) : RoomName(glb_crd, bx, bz);            
        }
    }

    if (outdoor) {
        
        
        info->BlockID[0] = loadBgCommon_GetBlockNoOutdoor(glb_crd, fcx, fcz);
        for (ix = 1; ix < 4; ix++) {
            info->BlockID[ix] = 0;
        }
    } else {
        BlockNumber(&info->BlockID[0], glb_crd, fcx, fcz);
        for (ix = 0; ix < 4; ix++) {
            info->BlockID[ix] = (u_short)info->BlockID[ix];
        }
    }

    
    
    return info->unit;
}
#else
INCLUDE_ASM("asm/nonmatchings/LoadBg/loadbg_common", loadBgCommon_SetInfo);
#endif

int loadBgCommon_HideMapBlockOutdoor(int mapid) {
    loadBgCommon_Info_T* info = _loadBgCommon_Info;
    int prev; // r2

    prev = info->hide_map_request;
    info->hide_map_request = mapid;
    return prev;
}
