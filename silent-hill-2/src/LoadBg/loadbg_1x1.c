#include "LoadBg/loadbg_1x1.h"
#include "LoadBg/loadbg_common.h"

#include "Event/stg_name.h"

#include "FilesList/fileslist_bg.h"

int loadBg1x1_GetIdForDrawEnv(void) {
    loadBgCommon_Info_T* info = _loadBgCommon_Info;
    int glb_crd; // r17
    int mapid; // r2

    
    glb_crd = info->glb_crd;     
    if (BgIsOut(glb_crd)) {
        mapid = 1;
    } else {
        mapid = info->BlockID[0];
    }
    
    return (glb_crd << 0x10) | mapid;

}

void* loadBg1x1_GetTrTexFile(void) {
    loadBgCommon_Info_T* info = _loadBgCommon_Info;
    int glb_crd;
    int map_no;
    FilesBgBlock* filesbg;
    void* file;
    int i;

    glb_crd = info->glb_crd;
    if (BgIsOut(glb_crd)) {
        filesbg = FilesGetBgBlock((STAGE_ID)glb_crd, 1);
        file = filesbg->tex;
    } else {
        
        file = NULL;
        for (i = 0; i < 4; i++) {
            
            if (map_no = info->BlockID[i], map_no == 0) break;                
            filesbg = FilesGetBgBlock((STAGE_ID)glb_crd, map_no);
            file = filesbg->tex;
            if (file != NULL) break;            
        }
    }

    return file;
}
