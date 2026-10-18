#ifndef SH2_COMMON_MEM_SHARE_H
#define SH2_COMMON_MEM_SHARE_H

#include "sh2_common.h"

/**
 * Reserved offset in the memshare buf for the memory card info. 
 */
#define MCW_HEAP_ADDRESS          0x140000

/**
 * Movie work address in the memshare buf.
 */
#define MOVIE_HEAP_ADDRESS        0x150000
#define MOVIE_VOBUF_ADDRESS       0x1F5400
#define MOVIE_VIBUF_ADDRESS       0x3D5400
#define MOVIE_EVENT_MPEG_ADDRESS  0x275400
#define MOVIE_EVENT_READ_ADDRESS  0x34DC00

#define MOVIE_TITLE_HEAP_ADDRESS  0x50000
#define MOVIE_TITLE_MPEG_ADDRESS  0x455400
#define MOVIE_TITLE_READ_ADDRESS  0x52DC00

/**
 * Map marker file address in the memshare buf.
 */
#define MARKER_FILE_HEAP_ADDRESS  0x104800

/**
 * LoadBg-related file address in the memshare buf.
 */
#define BG_LOAD_HEAP_ADDRESS      0x512000
#define BG_LOAD_HEAP_UNIT_SIZE    0x1E0000

/**
 * Memshare offset for Effect2 effects.
 */
#define EFFECT2_HEAP_ADDRESS      0x90000
    
/**
 * Memshare offset for map?
 */
#define BG_CHARA_HEAP_ADDRESS     0x282000

/**
 * Memshare offset for BgLoad cache?
 */
#define BG_L_CACHE_HEAP_ADDRESS   0x342000

void MemShareAllocateTitleMovie(void);
void MemShareAllocateEventMovie(int slot);
void MemShareReleaseMovie(void);
void MemShareRecoverMovie(void);
void MemShareWaitRealloc(int mode);
void* MemShareGetBgLoadWorkAddr(void);
void* MemShareGetBgLoadSectionWorkAddr(int slot);
void* MemShareGetBgLoadCacheAddr(void);
void* MemShareGetBgCharaWorkAddr(void);
void* MemShareGetEffect2WorkAddr(void);
void* MemShareGetMovieTagWorkAddr(void);
void* MemShareGetMovieVoWorkAddr(void);
void* MemShareGetMovieViWorkAddr(void);
void* MemShareGetMovieMpegWorkAddr(void);
void* MemShareGetMovieReadWorkAddr(void);

// total size: 0x90
typedef struct MemShareCtrl {
    // Members
    int cid; // offset 0x0, size 0x4
    int step; // offset 0x4, size 0x4
    s_char* movie_tag; // offset 0x8, size 0x4
    s_char* movie_vo; // offset 0xC, size 0x4
    s_char* movie_vi; // offset 0x10, size 0x4
    s_char* movie_mpeg; // offset 0x14, size 0x4
    s_char* movie_read; // offset 0x18, size 0x4
    int pad; // offset 0x1C, size 0x4
    s_char* _effect; // offset 0x20, size 0x4
    s_char* effect; // offset 0x24, size 0x4
    s_char* _effect2; // offset 0x28, size 0x4
    s_char* effect2; // offset 0x2C, size 0x4
    s_char* _bg_chara; // offset 0x30, size 0x4
    s_char* bg_chara; // offset 0x34, size 0x4
    s_char* _bg_c_cache; // offset 0x38, size 0x4
    s_char* bg_c_cache; // offset 0x3C, size 0x4
    s_char* _bg_l_cache; // offset 0x40, size 0x4
    s_char* bg_l_cache; // offset 0x44, size 0x4
    s_char* _bg_loadall; // offset 0x48, size 0x4
    s_char* bg_loadall; // offset 0x4C, size 0x4
    s_char* _bg_load[8]; // offset 0x50, size 0x20
    s_char* bg_load[8]; // offset 0x70, size 0x20
} MemShareCtrl;

extern char MemShare_gp_data_buf[13180928]; // size: 0xC92000, address: 0x126FBC0

#endif
