#ifndef EVENT_SUB_H
#define EVENT_SUB_H

#include "common.h"
#include "Chacter/character.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/pad.h"

#include "data/fs_structs.h"

#define EV_PROG_STEP(p_step) \
do {                                 \
    ev_p_step = p_step;              \
    ev_s_step = 0;                   \
} while (0)

#define EV_SUB_STEP(s_step) do { ev_s_step = s_step; } while (0)

// @todo: clean up

// gamemain.c
extern char* get_gp_data_buf_addr(void); // @note: removing this gives problems

// almost every function above should be moved to its correct place
int EvSubMessage(int msg /* r2 */);
int EvSubQuestion(int msg /* r2 */);
int EvSubItemUse0(int kind /* r19 */, int message /* r20 */, int se /* r18 */, int stereo /* r17 */, float* pos /* r16 */, int xxx /* r2 */);
int EvSubItemGet(int kind /* r16 */, int message /* r2 */);
int EvSubItemGetAndAnim(int kind /* r16 */, int message /* r2 */);
int EvSubPictureDisplayOnly(void);
int EvSubPictureDisplay(fsFileIndex* file /* r16 */, int msg /* r17 */);
int EvSubMapGet(fsFileIndex* file /* r2 */, int msg /* r2 */);
void EvSubPictureLayer(int x0 /* r20 */, int y0 /* r19 */, int x1 /* r18 */, int y1 /* r17 */, int alpha /* r16 */);
void EvSubPictureFilter(void);
void EvSubPictureInit(void);
void EvSubPictureStart(void);
void EvSubPictureEnd(void);
void EvDispControlModelEntry(int* list /* r2 */, int room /* r2 */, int no /* r2 */);
void EvDispControlModelExec(int* list /* r16 */);
int EvSubMovieStart(int demo /* r16 */);
void EvSubMovieEnd(void);
extern float ev_filter;
extern int ev_filter_on;
extern int ev_cancel;
extern int ev_prog_flag_set;
extern int ev_s_step;
extern char* layer_adr;
extern u_short msg_buffer[];
extern short item_to_chara[75];
extern struct shPlayerWork sh2jms;
extern struct Pad_KeyConfig key_config;

#endif
