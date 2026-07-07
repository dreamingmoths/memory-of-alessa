#ifndef SH2_COMMON_MEM_SHARE_H
#define SH2_COMMON_MEM_SHARE_H

#include "sh2_common.h"

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

extern char MemShare_gp_data_buf[13180928]; // size: 0xC92000, address: 0x126FBC0

#endif
