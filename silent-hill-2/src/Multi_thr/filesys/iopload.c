#include "Multi_thr/filesys/iopload.h"
#include "Multi_thr/filesys/filepath.h"
#include "Multi_thr/filesys/sh_cdvd.h"

int shIopReplaceMod(char* imgfile) {
    int ret; // r16
    char filename[256]; // r29+0x20
    
    ret = 0;
    if (imgfile != NULL) {
        
        if (shPathMakeIop(filename, imgfile)) {
            ret = shSifRebootIopR(filename);
        }


        
    } else {
        printf_enable(imgfile);
    }
    
    return ret;
}



int shIopLoadMod(char* module) {
    int ret; // r16
    char filename[256]; // r29+0x20
    
    if ((module != NULL) && (*module != 0)) {
        
        if (shPathMakeIop(filename, module))
            ret = shSifLoadModuleR(filename, 0, "");
    
    } 
    
    
    
    
    
    return ret;
}
