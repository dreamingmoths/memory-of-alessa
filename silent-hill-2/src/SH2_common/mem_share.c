#include "SH2_common/mem_share.h"
#include "Multi_thr/loadinit/loadinit.h"

#define LIS_CMD_PUT(_index, ...) ((((int (*)())(&lisPutCmd##_index))(__VA_ARGS__)))

UNMIGRATED(/* static */ MemShareCtrl mem_share_ctrl);

#line 103
static int ___MemShareRemove(void) {
    HH_MemoryManager_MemoryBlock_All_Discard();
    return 1;
}

#line 109
static int ___MemShareLoadInit(void) {
    HH_MemoryManager_MemoryBlock_Allocate_TextureBuffer();
    return 1;
}

#line 115
static int ___MemShareLoadFinish(void) {
    HH_MemoryManager_MemoryBlock_Allocate_Packet_and_ObjectWork();
    return 1;
}
#line 120
static void MemShareClearWorkAddr(int notall) {
    int i;
    mem_share_ctrl.movie_tag = NULL;
    mem_share_ctrl.movie_vo = NULL;
    mem_share_ctrl.movie_vi = NULL;
    mem_share_ctrl.movie_mpeg = NULL;
    mem_share_ctrl.movie_read = NULL;
    
    if (!(notall & 1)) {
        mem_share_ctrl._effect = NULL;
        mem_share_ctrl._effect2 = NULL;
        mem_share_ctrl._bg_chara = NULL;
        mem_share_ctrl._bg_c_cache = NULL;
        mem_share_ctrl._bg_l_cache = NULL;
        mem_share_ctrl.effect = NULL;
        
        mem_share_ctrl.effect2 = NULL;
        mem_share_ctrl.bg_chara = NULL;
        mem_share_ctrl.bg_c_cache = NULL;
        mem_share_ctrl.bg_l_cache = NULL;
    }
    
    if (!(notall & 2)) {
        
        mem_share_ctrl._bg_loadall = NULL;
        for (i = 0; i < 8; i++) {
            mem_share_ctrl._bg_load[i] = NULL;
        }
        
        mem_share_ctrl.bg_loadall = NULL;
        for (i = 0; i < 8; i++) {
            mem_share_ctrl.bg_load[i] = NULL;
        }
    }
}

#line 162
void MemShareAllocateTitleMovie(void) {
    char* addr;
    ASSERT_ON_LINE(mem_share_ctrl.step!=-1, 164);
    if (mem_share_ctrl.step == 2 || mem_share_ctrl.step == 3) {
        MemShareWaitRealloc(0);
    }
    if (mem_share_ctrl.step == 0) {
        mem_share_ctrl.step = 1;
        
        fsSync(0, -1);
        
        ___MemShareRemove();
        MemShareClearWorkAddr(0);
        
        addr = &MemShare_gp_data_buf[MOVIE_HEAP_ADDRESS];
        mem_share_ctrl.movie_tag = addr;
        mem_share_ctrl.movie_vo = addr + MOVIE_VOBUF_ADDRESS;
        mem_share_ctrl.movie_vi = addr + MOVIE_VIBUF_ADDRESS;
        mem_share_ctrl.movie_mpeg = addr + MOVIE_TITLE_MPEG_ADDRESS;
        mem_share_ctrl.movie_read = addr + MOVIE_TITLE_READ_ADDRESS;
    }
}

#line 186
void MemShareAllocateEventMovie(int slot) {
    char* addr; // r5
    ASSERT_ON_LINE(mem_share_ctrl.step!=-1, 188);
    if (mem_share_ctrl.step == 0) {
        mem_share_ctrl.step = 1;
        
        fsSync(0, -1);
        
        ___MemShareRemove();
        MemShareClearWorkAddr(2);
        
        addr = &MemShare_gp_data_buf[MOVIE_TITLE_HEAP_ADDRESS];
        mem_share_ctrl.movie_tag = addr;
        mem_share_ctrl.movie_vi = addr + MOVIE_VOBUF_ADDRESS;
        mem_share_ctrl.movie_mpeg = addr + MOVIE_EVENT_MPEG_ADDRESS;
        mem_share_ctrl.movie_read = addr + MOVIE_EVENT_READ_ADDRESS;
        
        addr = &MemShare_gp_data_buf[BG_LOAD_HEAP_ADDRESS];
        
        addr += (slot / 2 * BG_LOAD_HEAP_UNIT_SIZE);
        mem_share_ctrl.movie_vo = addr;       
        slot /= 2; mem_share_ctrl._bg_load[slot * 2] = NULL;        
        mem_share_ctrl.bg_load[slot * 2] = NULL;
        mem_share_ctrl._bg_load[slot * 2 + 1] = NULL;
        mem_share_ctrl.bg_load[slot * 2 + 1] = NULL;
    }
}


#line 216
static void ___MemShareReleaseMovie(int notall) {
    char* addr; // r4
    int i; // r5    
    MemShareClearWorkAddr(notall);
    
    
    
    addr = &MemShare_gp_data_buf[MOVIE_HEAP_ADDRESS];
    
    mem_share_ctrl._effect = addr;
    
    
    mem_share_ctrl._effect2 = addr + EFFECT2_HEAP_ADDRESS;
    
    
    mem_share_ctrl._bg_chara = addr + BG_CHARA_HEAP_ADDRESS;
    
    
    
    
    
    mem_share_ctrl._bg_l_cache = addr + BG_L_CACHE_HEAP_ADDRESS;
    
    
    
    
    
    addr = &MemShare_gp_data_buf[BG_LOAD_HEAP_ADDRESS];
    mem_share_ctrl._bg_loadall = addr;
    for (i = 0; i < 8; i += 2) {
        mem_share_ctrl._bg_load[i] = addr;
        mem_share_ctrl._bg_load[i + 1] = addr; addr += BG_LOAD_HEAP_UNIT_SIZE;        
    }
}


#line 253
void MemShareReleaseMovie(void) {
    int cid;  
    ASSERT_ON_LINE(mem_share_ctrl.step!=-1, 255);
    if (mem_share_ctrl.step == 1) {
        fsSync(0, -1);
        ___MemShareReleaseMovie(3);
        do {
            cid = LIS_CMD_PUT(0, ___MemShareLoadInit);
        } while (cid == -1);
        mem_share_ctrl.cid = cid;
        mem_share_ctrl.step = 2;
    }
}

#line 268
void MemShareRecoverMovie(void) {
    ASSERT_ON_LINE(mem_share_ctrl.step!=-1, 269);
    if (mem_share_ctrl.step == 1) {
        MemShareReleaseMovie();
    }
    if (mem_share_ctrl.step == 2) {
        ___MemShareReleaseMovie(2);
        mem_share_ctrl.step = 3;
    }
}

#line 280
void MemShareWaitRealloc(int mode) {
    int cid;
    if (mem_share_ctrl.step == -1) {
        
        
        ___MemShareReleaseMovie(0);
        mem_share_ctrl.step = 0;
    }
    if (mem_share_ctrl.step == 1) {
        MemShareReleaseMovie();
    }
    if ((mem_share_ctrl.cid == -1) || (lisSync(mode, mem_share_ctrl.cid) >= 0)) {
        if (mem_share_ctrl.step == 2) {
            MemShareRecoverMovie();
        }
        if (mem_share_ctrl.step == 3) {
            ___MemShareLoadFinish();
            mem_share_ctrl.cid = -1;
        }
        mem_share_ctrl.step = 0;
    }
}

#line 311
void* MemShareGetBgLoadWorkAddr(void) {
    void* addr;
    
    addr = mem_share_ctrl.bg_loadall;
    
    if (addr != mem_share_ctrl._bg_loadall) {
        mem_share_ctrl.bg_loadall = mem_share_ctrl._bg_loadall;
    }
    return addr;
}

#line 329
void* MemShareGetBgLoadSectionWorkAddr(s32 slot) {
    void* addr;
    
    addr = mem_share_ctrl.bg_load[slot];
    if (addr != mem_share_ctrl._bg_load[slot]) {
        mem_share_ctrl.bg_load[slot] = mem_share_ctrl._bg_load[slot];
    }
    return addr;
}

#line 345
void* MemShareGetBgLoadCacheAddr(void) {
    void* addr;
  
    addr = mem_share_ctrl.bg_l_cache;

    if (addr != mem_share_ctrl._bg_l_cache) {
        mem_share_ctrl.bg_l_cache = mem_share_ctrl._bg_l_cache;
    }
    return addr;
}

#line 384
void* MemShareGetBgCharaWorkAddr(void) {
    void* addr;
    
    addr = mem_share_ctrl.bg_chara;

    if (addr != mem_share_ctrl._bg_chara) {
        mem_share_ctrl.bg_chara = mem_share_ctrl._bg_chara;
    }
    return addr;
}

#line 421
void* MemShareGetEffect2WorkAddr(void) {
    void* addr;
    
    addr = mem_share_ctrl.effect2;

    if (addr != mem_share_ctrl._effect2) {
        mem_share_ctrl.effect2 = mem_share_ctrl._effect2;
    }
    return addr;
}




#line 436
void* MemShareGetMovieTagWorkAddr(void) {
    return mem_share_ctrl.movie_tag;
}
#line 440
void* MemShareGetMovieVoWorkAddr(void) {
    return mem_share_ctrl.movie_vo;
}

#line 445
void* MemShareGetMovieViWorkAddr(void) {
    return mem_share_ctrl.movie_vi;
}

#line 450
void* MemShareGetMovieMpegWorkAddr(void) {
    return mem_share_ctrl.movie_mpeg;
}

#line 455
void* MemShareGetMovieReadWorkAddr(void) {
    return mem_share_ctrl.movie_read;
}
