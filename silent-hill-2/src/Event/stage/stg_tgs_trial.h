#ifndef STG_TGS_TRIAL_H
#define STG_TGS_TRIAL_H

#include "Event/stg_overlay.h"
#include "FilesList/fileslist_bg.h"

int EvProgGetHospitalMap(void);

extern int ev_prog_flag_set;
extern float ev_timer; // size: 0x4, address: 0x11263A0

extern union fsFileIndex data_pic_hsp_p_boxnumber_2_tex[1]; // size: 0x8, address: 0x3A1C98
extern union fsFileIndex data_pic_hsp_p_boxnumber_tex[1];   // size: 0x8, address: 0x3A1C90

extern union fsFileIndex data_pic_hsp_p_box_tex;
extern union fsFileIndex data_pic_hsp_p_hair_hair_tex;
extern union fsFileIndex data_pic_hsp_p_hair_tex;
extern union fsFileIndex data_pic_hsp_pboxkey01_tex;
extern float ev_cursor_x;
extern float ev_cursor_y;

#endif // STG_TGS_TRIAL_H
