#include "LoadBg/loadbg_2x2.h"
#include "LoadBg/loadbg_cam.h"
#include "LoadBg/loadbg_cld.h"
#include "LoadBg/loadbg_kg2.h"
#include "LoadBg/loadbg_map.h"
#include "LoadBg/mem/loadbg_buf.h"
#include "data/fs_structs.h"
#include "FilesList/fileslist_bg.h"
#include "SH2_common/mem_share.h"

static loadBg2x2_Ctrl lb2x2Ctrl; // size: 0x5AC, address: 0x1202800

static void loadBg2x2_ResetSectFileList(loadBgMem_File* filelist, int n);
static void loadBg2x2_ResetSectionAll(void);
static void* loadBg2x2_GetLoadWork(void);
static void* loadBg2x2_GetCacheWork(void);
static void loadBg2x2_CheckSlotWork(void);

static void loadBg2x2_ResetSectFileList(loadBgMem_File* filelist, int n) {
    int i;

    
    for (i = 0; i < n; i++) {
        filelist[i].file = NULL;
        filelist[i].ofsS = 0;
        filelist[i].ofsE = 0;
        filelist[i].addr = NULL;
    }
}

static void loadBg2x2_ResetSectionAll(void) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    int i, j, ofsSI, ofsS;
    for (i = 0; i < 2; i++) {
        
        ofsSI = i * 0x1E0000;
        ctrl->SectI[i].ofsS = ofsSI;
        ctrl->SectI[i].ofsE = ofsSI + 0x5A0000;
        ctrl->SectI[i].files = 0;
        ctrl->SectI[i].filelist = ctrl->FileI[i];
        ctrl->SectI[i].upper = i;
        ctrl->SectI[i].reduceRate8 = 0;
        ctrl->SectI[i].overwrite = 0;
        ctrl->SectI[i].sectID = 1;
        loadBg2x2_ResetSectFileList(ctrl->SectI[i].filelist, 20);
        
        
        for (j = 0; j < 4; j++) {
            ofsS = j * 0x1E0000;
            ctrl->SectO[i + j * 2].ofsS = ofsS;
            ctrl->SectO[i + j * 2].ofsE = ofsS + 0x1E0000;
            ctrl->SectO[i + j * 2].files = 0;
            ctrl->SectO[i + j * 2].filelist = ctrl->FileO[i + j * 2];
            ctrl->SectI[i].upper = i;
            ctrl->SectI[i].reduceRate8 = 0;
            ctrl->SectO[i + j * 2].overwrite = 0;
            ctrl->SectO[i + j * 2].sectID = 1;
            loadBg2x2_ResetSectFileList(ctrl->SectO[i + j * 2].filelist, 4);
        
        
        }
        ctrl->SectList[i] = NULL;
    }
    ctrl->Sections = 0;
}

static void* loadBg2x2_GetLoadWork(void) {
    void* addr;    
    addr = MemShareGetBgLoadWorkAddr();
    if (addr == NULL) {
        
        
        lb2x2Ctrl.load_cleanup = 1;
    }
    
    return addr;
}

static void* loadBg2x2_GetCacheWork(void) {
    void* addr;
    
    addr = MemShareGetBgLoadCacheAddr();
    if (addr != NULL) {
        lb2x2Ctrl.cache_cleanup = 0;
        return addr;}
    lb2x2Ctrl.cache_cleanup = 1;
    return addr;




}

static void loadBg2x2_CheckSlotWork(void) {
    int slot;    
    for (slot = 0; slot < 8; slot++) {
        if (MemShareGetBgLoadSectionWorkAddr(slot) != NULL) {
            
            lb2x2Ctrl.slot_cleanup[slot] &= 2;            
        } else {
            lb2x2Ctrl.slot_cleanup[slot] = 3;
        }
    }
}

void loadBg2x2_CheckCacheWork(void) {
    int try;
    void* addr;
    if (lb2x2Ctrl.load != NULL) {
        
        for (try = 2; try > 0; try--) {
            
            
            
            addr = loadBg2x2_GetCacheWork();
            if (addr != NULL) {
                if (lb2x2Ctrl.cache == NULL) {
                    lb2x2Ctrl.cache = loadBg2x2_CacheCtrl;
                    _loadBgMem_InitCache(loadBg2x2_CacheCtrl, 
                                         0x10000, 
                                         8, 
                                         loadBg2x2_CacheUnit, 
                                         addr);
                }
                
                          
                break;
            } 
            lb2x2Ctrl.cache = NULL;
                            
        }
    }
}

void loadBg2x2_CheckLoadWork(void) {
    int try;
    void* addr;    
    for (try = 2; try > 0; try--) {
        
        
        
        addr = loadBg2x2_GetLoadWork();
        if (addr != NULL) {
            if (lb2x2Ctrl.load == NULL) {
                lb2x2Ctrl.load = loadBg2x2_LoadCtrl;
                _loadBgMem_InitLoad(loadBg2x2_LoadCtrl, 
                                    0x10000, 
                                    120, 
                                    loadBg2x2_LoadUnit, 
                                    loadBg2x2_RequestUnit, 
                                    addr);
                
                loadBg2x2_ResetSectionAll();
            }
            
            break;
        }
            lb2x2Ctrl.load = NULL;
        
    }
    loadBg2x2_CheckCacheWork();
    
    loadBg2x2_CheckSlotWork();
}

void loadBg2x2_ClearRequest(void) {
    loadBg2x2_ResetSectionAll();
    _loadBgMem_ClearRequest(lb2x2Ctrl.load);
}

void loadBg2x2_SetRequest(void) {
    loadBgMem_SetRequest(lb2x2Ctrl.load, lb2x2Ctrl.SectList);
}

void loadBg2x2_CleanupNonRequest(void) {
    int slot;
    if (_loadBgMem_CleanupNonRequest(lb2x2Ctrl.load)) {        
        for (slot = 0; slot < 8; slot++) {
            lb2x2Ctrl.slot_cleanup[slot] &= 1;
        }
    }
}

int loadBg2x2_GetOutdoorBlockSection(int bx, int bz) {
    return (bx & 1) + ((bz & 1) * 2);
}

int loadBg2x2_GetOutdoorBlockPhase(int bx, int bz) {
    return (((bx & 2) + (bz & 2)) & 2) >> 1;
}

int loadBg2x2_CheckLoadBufferOutdoor(int bx, int bz) {
    int cleanup; 
    int bgslot;
    
    bgslot = loadBg2x2_GetSlotOutdoor(bx, bz);
    
    cleanup = lb2x2Ctrl.slot_cleanup[bgslot];
    
    
    
    
    
    
    
    
    return cleanup;
}

int loadBg2x2_SetRequestOutdoor(int prio, int reduceRate8, int bx, int bz, int mid) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    loadBgMem_Sect* SectO; loadBgMem_File* sFile;
    int n; int i; int sectNo;
    fsFileIndex* file;
    FilesBgBlock* filesbg;
    int glb; int j;
    if (ctrl->load == NULL) return 0;
    
    if (loadBg2x2_CheckLoadBufferOutdoor(bx, bz)) {
        return 1;
    }
    
    ASSERT_ON_LINE(ctrl->Sections<LBM2x2_SECTIONS_O, 317);

    SectO = ctrl->SectO;
    
    
    
    
    
    
    
    
       
    SectO += loadBg2x2_GetSlotOutdoor(bx, bz); // they probably used another temporary variable here since now this not line matched
    
    
    
    sFile = SectO->filelist;
    
    n = 0;
    if (mid != 0) {
    
        
        glb = (mid >> 0x10) & 0xFFFF;
        if (glb != 0) ASSERT_ON_LINE(BgIsOut(glb), 340);
        
        filesbg = FilesGetBgBlock(glb & 0xFF, mid & 0xFFFF);
        
        
        file = filesbg->cam; sFile[0].file = file;
        file = filesbg->cld; sFile[1].file = file;
        
        file = filesbg->kg2; sFile[2].file = file;
        file = filesbg->map; sFile[3].file = file; n += 4;        
    } else {
        
        for (j = 0; j < 4; j++) sFile[n++].file = 0;
    }
    ASSERT_ON_LINE(n==LBM2x2_SECTFILES_O, 354);
    SectO->files = n;
    SectO->sectID = prio + 1;
    SectO->reduceRate8 = reduceRate8;
    ctrl->SectList[ctrl->Sections++] = SectO;
    
    
    for (i = 0; i < n; i++) {
        fsFileIndex* file; 
        int size;
        file = sFile[i].file;
        size = 0;
        if (file != 0) size = FcGetFileSize(file);        
        if (size <= 0) {
            size = 0;
            sFile[i].file = 0;
        }
        sFile[i].ofsS = 0;
        sFile[i].ofsE = size;
        sFile[i].addr = 0;
    }
    return 0;
}

int loadBg2x2_GetIndoorRoomSection(int roomid) {
    int sect;
    sect = roomid & 1;
    if (roomid != 0x1D) {
        return sect;
    }
    
    return sect ^ 1;





}

int loadBg2x2_CheckLoadBufferIndoor(int roomid) {
    int cleanup = 0;
    int bgslot;

    
    bgslot = loadBg2x2_GetUseSlotIndoor(roomid); 

    
    cleanup |= lb2x2Ctrl.slot_cleanup[bgslot];
    cleanup |= lb2x2Ctrl.slot_cleanup[bgslot ^ 1];
    cleanup |= lb2x2Ctrl.slot_cleanup[2];
    cleanup |= lb2x2Ctrl.slot_cleanup[3];
    cleanup |= lb2x2Ctrl.slot_cleanup[4];
    cleanup |= lb2x2Ctrl.slot_cleanup[5];
    return cleanup;



    



















}

int loadBg2x2_SetRequestIndoor(int roomid, int* mid4) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    loadBgMem_Sect* SectI;
    loadBgMem_File* sFile;
    int n; int slot; int i; int sectNo; int mid;
    fsFileIndex* file; 
    FilesBgBlock* filesbg;
    int glb; int j;
    if (ctrl->load == NULL) return 0;
    
    if (loadBg2x2_CheckLoadBufferIndoor(roomid)) {
        return 1;
    }
    
    SectI = ctrl->SectI;    
    ASSERT_ON_LINE(ctrl->Sections<=LBM2x2_SECTIONS_I, 450);

    
    sectNo = loadBg2x2_GetIndoorRoomSection(roomid);
    SectI += sectNo;
    sFile = SectI->filelist;
    
    ctrl->SectList[ctrl->Sections++] = SectI;
    
    n = 0;
    for (slot = 0; slot < 5; slot++) {
        
        if (slot == 4) {
            if (((mid4[0] >> 0x10) & 0xFFFF) == 5) {
                mid = mid4[3] + 1;
            } else {
                mid = 0;
            }
        } else {
            mid = mid4[slot];
        }
        if (mid != 0) {

            
            glb = (mid >> 0x10) & 0xFFFF;
            ASSERT_ON_LINE(!BgIsOut(glb), 475);
            
            filesbg = FilesGetBgBlock(glb, mid & 0xFFFF);
            
            
            sFile[n++].file = file = filesbg->cam;
            sFile[n++].file = file = filesbg->cld;
            
            sFile[n++].file = file = filesbg->kg2;
            sFile[n++].file = file = filesbg->map;
        }
        else {
            for (j = 0; j < 4; j++) sFile[n++].file = 0;
        }
    }
    ASSERT_ON_LINE(n==LBM2x2_SECTFILES_I, 490);
    SectI->files = 20;
    SectI->sectID = 1;
    SectI->reduceRate8 = 0;
    
    
    for (i = 0; i < n; i++) {
        fsFileIndex* file;  
        int size;
        file = sFile[i].file;
        size = 0;
        if (file != NULL) size = FcGetFileSize(file);
        if (size <= 0) {
            size = 0;
            sFile[i].file = NULL;
        }
        sFile[i].ofsS = 0;
        sFile[i].ofsE = size;
        sFile[i].addr = NULL;
    }
    
    return 0;
}

int loadBg2x2_CheckRequest(int* reqUnits) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    int ret;
    ret = loadBgMem_CheckRequest(ctrl->load, reqUnits);
    return ret;
}

int loadBg2x2_LoadRequest(void) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    int ret;
    
    ret = loadBgMem_LoadRequest(ctrl->load, 
                                ctrl->cache, 
                                20, 
                                5, 
                                ctrl->cache_in_access_count, 
                                ctrl->cache_out_access_count, 
                                ctrl->file_access_count, 
                                ctrl->miss_access_count);
    

        
    return ret;
}

int loadBg2x2_ActivateRequestOutdoor(int slot, int mid, int* reqUnits) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    loadBgMem_Sect* Sect;
    int ret, block_no;
    loadBgMem_File* sFile;
    
    if (slot == 4) {
        
        
        
        
        
        
        loadBgMAP_Replace(slot, 0, NULL, 0);
    } else {
        Sect = ctrl->SectList[0];
        if (Sect != 0) ASSERT_ON_LINE(ctrl->SectList[1]==0, 558);        
        ret = loadBgMem_CheckRequest(ctrl->load, reqUnits);
        block_no = mid & 0xFFFF;        
        if ((Sect == NULL) || (*reqUnits == 0) || (ret > 0) || (block_no == 0)) {
            
            loadBgCAM_Replace(slot, 0, NULL, 0);
            loadBgCLD_Replace(slot, 0, NULL, 0);
            
            loadBgKG2_Replace(slot, 0, NULL, 0);
            loadBgMAP_Replace(slot, 0, NULL, 0);
        } else {
            fsFileIndex* file; int size; char* addr; 
            
            
            
            sFile = Sect->filelist;
            
            
            size = sFile[0].ofsE;
            addr = sFile[0].addr;
            loadBgCAM_Replace(slot, mid, addr, size);
            
            
            size = sFile[1].ofsE;
            addr = sFile[1].addr;
            loadBgCLD_Replace(slot, mid, addr, size);
            
            
            
            size = sFile[2].ofsE;
            addr = sFile[2].addr;
            loadBgKG2_Replace(slot, mid, addr, size);
            
            
            size = sFile[3].ofsE;
            addr = sFile[3].addr;
            loadBgMAP_Replace(slot, mid, addr, size);
        }        
    }

    
    return ret;
}

int loadBg2x2_ActivateRequestIndoor(int* mid4, int* reqUnits) {
    loadBg2x2_Ctrl* ctrl = &lb2x2Ctrl;
    loadBgMem_Sect* Sect;
    int ret;
    loadBgMem_File* sFile = NULL;
    int slot; int mid; int block_no;
    fsFileIndex* file; int size; char* addr;
    Sect = ctrl->SectList[0];
    if (Sect != 0) ASSERT_ON_LINE(ctrl->SectList[1]==0, 612);
    ret = loadBgMem_CheckRequest(ctrl->load, reqUnits);
    if (Sect != 0) sFile = Sect->filelist;       
    for (slot = 0; slot < 5; slot++) {
        
        
        if (slot == 4) {
            if (((mid4[0] >> 16) & 0xFFFF) == 5) {
                mid = mid4[3] + 1;
            } else {
                mid = 0;
            }
        } else {
            mid = mid4[slot];
        }
        block_no = mid & 0xFFFF;  
        if ((Sect == NULL) || (*reqUnits == 0) || (ret > 0) || (block_no == 0)) {
            
            if (slot < 4) loadBgCAM_Replace(slot, 0, NULL, 0);
            if (slot < 4) loadBgCLD_Replace(slot, 0, NULL, 0);            
            
            if (slot < 4) loadBgKG2_Replace(slot, 0, NULL, 0);        
            loadBgMAP_Replace(slot, 0, NULL, 0);
            if (Sect != NULL) sFile += 4;            
        } else {
            
            
            
            
            if (slot < 4) {
            
                size = sFile[0].ofsE;
                addr = sFile[0].addr;
                loadBgCAM_Replace(slot, mid, addr, size);
            }
            
            if (slot < 4) {
                
                size = sFile[1].ofsE;
                addr = sFile[1].addr;
                loadBgCLD_Replace(slot, mid, addr, size);
            }
            
            
            if (slot < 4) {
                
                size = sFile[2].ofsE;
                addr = sFile[2].addr;
                loadBgKG2_Replace(slot, mid, addr, size);
            }
            
            
            size = sFile[3].ofsE;
            addr = sFile[3].addr;
            loadBgMAP_Replace(slot, mid, addr, size);
            sFile += 4;
        }
    }
    
    return ret;
}

int loadBg2x2_GetSlotOutdoor(int bx, int bz) {
    int sectNo;
    int blockSect; 
    int blockPhase;
    blockSect = loadBg2x2_GetOutdoorBlockSection(bx, bz);
    blockPhase = loadBg2x2_GetOutdoorBlockPhase(bx, bz);
    sectNo = blockPhase + (blockSect * 2);
    return sectNo;
}

int loadBg2x2_GetFreeSlotIndoor(int roomid) {
    return (loadBg2x2_GetIndoorRoomSection(roomid)) ? 0 : 7;
}

int loadBg2x2_GetUseSlotIndoor(int roomid) {
    return (loadBg2x2_GetIndoorRoomSection(roomid)) ? 7 : 0;
}
