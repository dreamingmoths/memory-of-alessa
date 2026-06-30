#ifndef EVENT_SUB_H
#define EVENT_SUB_H

#include "common.h"
#include "Chacter/character.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/pad.h"

#define EV_PROG_STEP(p_step) \
do {                                 \
    ev_p_step = p_step;              \
    ev_s_step = 0;                   \
} while (0)

#define EV_SUB_STEP(s_step) do { ev_s_step = s_step; } while (0)

// @todo: clean up

// movie/movie_main.c
extern int MovieWaitReady(void);
// GFW/sh2gfw_viewclip.c
extern int sh2gfw_Set_DispOnOffObj(int mapid /* r2 */, int dispflg /* r2 */);
extern void sh2gfw_Init_DispOnOffObj(void);
extern int sh2gfw_FastSet_DispOnOffObj(int mapid /* r2 */, int dispflg /* r2 */);
// GFW/sh2gfw_2d_filters.c
extern void sh2gfw_Reset_FilterCommand(void);
extern void sh2gfw_Black_Clear(void);
extern void sh2gfw_Set_PauseRetain(void);

// SH2_common/pad.c
extern int shPadTrigger(int port /* r17 */, int key /* r16 */);

// Chacter/sh2_character_manage.c
extern int shCharacter_Manage_Delete(struct SubCharacter* scp /* r2 */, short kind /* r2 */, short id /* r2 */);
// gamemain.c
extern char* get_gp_data_buf_addr(void);
// SH2_common/sh_vu0.c
extern void shQzero(void*, int);

// Chacter/m3_play_event.c
extern void PlayerEventAnimeSet(int anime /* r16 */);
extern int PlayerEventAnimeSuccessFrame(void);
// Chacter/m3_sc.c
extern void SCNowPlayableEventSwitch(struct SubCharacter* scp /* r2 */, int flag /* r2 */);
extern int shCharacterAnimeIsEnd(struct SubCharacter* scp /* r2 */);
extern void shCharacterAnimePause(struct SubCharacter* scp /* r2 */);
extern void shCharacterAnimeRestart(struct SubCharacter* scp /* r2 */);
extern struct SubCharacter* shCharacterGetSubCharacter(u_short kind /* r2 */, short id /* r2 */);

// almost every function above should be moved to its correct place
int EvSubMessage(int msg /* r2 */);
int EvSubQuestion(int msg /* r2 */);
int EvSubItemUse0(int kind /* r19 */, int message /* r20 */, int se /* r18 */, int stereo /* r17 */, float* pos /* r16 */, int xxx /* r2 */);
int EvSubItemGet(int kind /* r16 */, int message /* r2 */);
int EvSubItemGetAndAnim(int kind /* r16 */, int message /* r2 */);
int EvSubPictureDisplayOnly(void);
int EvSubPictureDisplay(union fsFileIndex* file /* r16 */, int msg /* r17 */);
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
