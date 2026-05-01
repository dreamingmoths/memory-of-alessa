#ifndef INIT_MT_SYS_H
#define INIT_MT_SYS_H

#include "common.h"
#include "Multi_thr/filesys/fcread.h"
#include "FilesList/fileslist_bg.h" // correct?

void check_build_environment(char* bootfilename /* r16 */);

union fsFileIndex data_sound_mgf[1]; // size: 0x8, address: 0x3A1B70
union fsFileIndex data_pic_mgf[1]; // size: 0x8, address: 0x3A1B68
union fsFileIndex data_movie_mgf[1]; // size: 0x8, address: 0x3A2030
union fsFileIndex data_menu_mgf[1]; // size: 0x8, address: 0x3A1B40
union fsFileIndex data_etc_mgf[1]; // size: 0x8, address: 0x3A1798
union fsFileIndex data_chr_mgf[1]; // size: 0x8, address: 0x3A0578
union fsFileIndex data_bg_mgf[1]; // size: 0x8, address: 0x39C7A0

extern int execEnv_skip_load_iop_mod;

#endif // INIT_MT_SYS_H
