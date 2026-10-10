#ifndef EVENT_SUB_H
#define EVENT_SUB_H

#include "Chacter/character.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/pad.h"
#include "Event/event.h"
#include "Event/demoview.h"

#include "data/fs_structs.h"

// @todo: clean up

// gamemain.c
extern char* get_gp_data_buf_addr(void); // @note: removing this gives problems

// almost every function above should be moved to its correct place
int EvSubMessage(int msg /* r2 */);
int EvSubQuestion(int msg /* r2 */);
int EvSubItemUse0(int kind /* r19 */, int message /* r20 */, int se /* r18 */, int stereo /* r17 */, float* pos /* r16 */, int xxx /* r2 */);
int EvSubItemGet(int kind /* r16 */, int message /* r2 */);
int EvSubItemGetAndAnim(int kind /* r16 */, int message /* r2 */);
int EvSubFileLoadAndFadeOut(int unk, fsFileIndex* file_0, fsFileIndex* file_1); // @note: signature different from DWARF
void EvSubPictureDisplayAndFadeIn(float timer); // @note: signature different from DWARF
int EvSubPictureDisplayOnly(void);
void EvSubPictureDisplayAndFadeOut(float timer); // @note: signature different from DWARF
int EvSubPictureDisplay(fsFileIndex* file /* r16 */, int msg /* r17 */);
int EvSubMapGet(fsFileIndex* file /* r2 */, int msg /* r2 */);
void EvSubPictureLayer(int x0 /* r20 */, int y0 /* r19 */, int x1 /* r18 */, int y1 /* r17 */, int alpha /* r16 */);
void EvSubPictureFilter(void);
void EvSubPictureInit(void);
void EvSubPictureStart(void);
void EvSubPictureEnd(void);
void EvSubPictureCursor(int color);
void EvDispControlModelEntry(int* list /* r2 */, int room /* r2 */, int no /* r2 */);
void EvDispControlModelExec(int* list /* r16 */);
void EvSubMovieReady(fsFileIndex* file, DramaDemo_MessageTime* msg_time, int msg_no);
int EvSubMovieStart(int demo /* r16 */);
void EvSubMovieEnd(void);


extern float ev_filter;
extern int ev_filter_on;
extern int ev_cancel;
extern int ev_prog_flag_set;
extern int ev_s_step;
extern char* layer_adr;
extern u_short msg_buffer[];
extern struct shPlayerWork sh2jms;
extern struct Pad_KeyConfig key_config;

#endif
