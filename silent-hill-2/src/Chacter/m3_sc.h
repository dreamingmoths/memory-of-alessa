#ifndef M3_SC_H
#define M3_SC_H

#include "common.h"
#include "Chacter/character.h"
#include "Chacter_Draw/clani.h"
#include "Chacter/item_screen_obj.h"
#include "Chacter/chara_list.h"

#define SCP_STATUS_BIT_ANIME_TYPE          2
#define SCP_STATUS_BIT_ROT_ZYX             7
#define SCP_STATUS_BIT_STAY_MODEL          8
#define SCP_STATUS_BIT_LIGHT_ON_NOW        9
#define SCP_STATUS_BIT_NOW_DEMO_EVENT      13
#define SCP_STATUS_BIT_NOW_PLAYABLE_EVENT  14
#define SCP_STATUS_BIT_FREEFALL            16

// E:\work\sh2(CVS全取得)\src\Chacter\m3_sc.c
extern struct shCharacterAll sh2chara; // size: 0x6810, address: 0x3C84D0

void shCharacterSetPlayer(SubCharacter* scp);

short shCharacterAnimeFrameGet_(SubCharacter* scp /* r2 */, u_int type /* r2 */);
AnimeInfo* shCharacterAnimeGetInfo(SubCharacter* scp /* r2 */);
AnimeInfo* shCharacterAnimeGetInfo_(SubCharacter* scp /* r2 */, int ctrl_type /* r2 */);
void shCharacterAnimeFrameSet(SubCharacter* scp /* r2 */, u_short frame /* r2 */);
void shCharacterAnimeRestart(SubCharacter* scp /* r2 */);

void shCharacterDelete(SubCharacter* scp);
void shCharacterPlayingExecAnimeOne(SubCharacter * scp /* r16 */);
void shCharacterDramaExecAnimeOne(SubCharacter * scp /* r16 */);

short shCharacterGetModelID(SubCharacter* scp /* r2 */);
SubCharacter* shCharacterGetSubCharacter(u_short kind /* r2 */, short id /* r2 */);
int shCharacterAnimeOneFrameSize(u_short id);
void shCharacterInitSubCharacter(void);
void* shCharacterGetAnimeAdrForPlay(SubCharacter* scp /* r2 */);
void shCharacterExecAnimeAll(void);
void shCharacterUpdateAll(void);
void shCharacterSetFunction(SubCharacter* scp /* r2 */, void (*func)(SubCharacter*) /* r2 */);
void shCharacterExecFunctionAll(void);
void shCharacterAnimeSet(SubCharacter* scp /* r19 */, int ctrl_type /* r2 */, int inter_type /* r18 */, AnimeInfo* anim_info /* r17 */, int anime /* r2 */);
void SCSetModel(SubCharacter* scp /* r18 */, int model /* r2 */);
void* shCharacterGetAnimeAdrForDrama(SubCharacter* scp /* r2 */);
void* shCharacterGetClusterAnimeAdr(SubCharacter* scp);
void SCAddPos(SubCharacter* scp, Vector4* pos);
void SCSetRot(SubCharacter* scp, Vector4* rot);
void SCAddRot(SubCharacter* scp, Vector4* rot);
void shCharacterClusterAnimeSet(SubCharacter* scp, int anime);

void shCharacterStayObjectScaleSet(SubCharacter* scp, float scale);
void shCharacterItemScreenObjectSet(SubCharacter* scp, shItemScreenObjectSettingData* data);
void shCharacterStayObjectNthPartsGet1st(SubCharacter* scp /* r2 */, int n /* r2 */, float* pos /* r2 */, float* rot /* r2 */);
void shCharacterStayObjectNthPartsSet(SubCharacter* scp /* r2 */, int n /* r2 */, float* pos /* r2 */, float* rot /* r17 */);

void shCharacterAnimeCopyForReverseModel(SubCharacter * scp /* r16 */);
void SCNowDemoEventSwitch(SubCharacter* scp, int flag);
void SCNowPlayableEventSwitch(SubCharacter* scp /* r2 */, int flag /* r2 */);
void SCStayModelSwitch(SubCharacter* scp, int flag);
void SCAnimeTypeSwitch(SubCharacter* scp, int flag);
void SCRotZYXSwitch(SubCharacter* scp, int flag);
void SCFreefallSwitch(SubCharacter* scp, int sw);
void SCLightOnNowSwitch(SubCharacter* scp, int sw);

short shCharacterAnimeSpeedGet_(SubCharacter* scp, u_int type);
void shCharacterAnimeSpeedAdd(SubCharacter* scp, short add);
void shCharacterAnimeSpeedAdd_(SubCharacter* scp, u_int type, short add);
void shCharacterAnimeSpeedAddY(SubCharacter* scp, short add);
void shCharacterAnimeSpeedAddY_(SubCharacter* scp /* r2 */, u_int type /* r2 */, short add /* r2 */);
void shCharacterAnimePause(SubCharacter* scp);
void shCharacterAnimePause_(SubCharacter* scp, u_int type);
void shCharacterAnimeRestart(SubCharacter* scp);
void shCharacterAnimeRestart_(SubCharacter* scp, u_int type);
int shCharacterAnimeIsEnd(SubCharacter* scp);
int shCharacterAnimeIsEnd_(SubCharacter* scp, u_int type);
short shCharacterAnimeFrameGet(SubCharacter* scp);
short shCharacterAnimeFrameGet_(SubCharacter* scp /* r2 */, u_int type /* r2 */);
void shCharacterAnimeFrameSet(SubCharacter* scp, u_short frame);
void shCharacterAnimeFrameSet_(SubCharacter* scp, u_int type, u_short frame);
int shCharacterAnimeCounterGet(SubCharacter* scp);
int shCharacterAnimeCounterGet_(SubCharacter* scp, u_int type);
void shCharacterAnimeCounterSet_(SubCharacter* scp, u_int type, int counter);
AnimeInfo* shCharacterAnimeGetInfo(SubCharacter* scp);
void shCharacterPlayerModelToDrama(void);
void shCharacterPlayerModelToPlayable(void);
void shCharacterMariaModelToDrama(void);
void shCharacterMariaModelToPlayable(void);
void shCharacterSetPosAfterDemo(SubCharacter* scp, float* pos, float roty);
void shCharacterGetPartsMatrixForShadow(float (*mat)[4], u_short kind, u_short id, u_int parts_name);
void shCharacterGetGroundInfoForShadow(float* pos, float* normal, float* height, u_short kind, u_short id);

extern int demo_status; // correct home for this?
extern sceVu0FMATRIX kt_unit_matrix; // correct home for this?

#endif
