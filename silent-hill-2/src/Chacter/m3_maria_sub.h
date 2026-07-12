#ifndef M3_MARIA_SUB_H
#define M3_MARIA_SUB_H

#include "Chacter/character.h"

typedef struct MariaSoundInfo {
    // total size: 0x8
    float vol; // offset 0x0, size 0x4
    s_char frame; // offset 0x4, size 0x1
    s_char domain; // offset 0x5, size 0x1
} MariaSoundInfo;
typedef struct MariaAppearPoint {
    // total size: 0x20
    short room_name_prev; // offset 0x0, size 0x2
    short room_name_now; // offset 0x2, size 0x2
    int active_type; // offset 0x4, size 0x4
    sceVu0FVECTOR pos; // offset 0x10, size 0x10
} MariaAppearPoint;

void MariaStatusClear(void);
void GetMariaPartsWorldMatrix(float (* mat)[4], u_int parts_name);
void mar_flg_on(u_int* type, u_int status);
void mar_flg_off(u_int* type, u_int status);
int mar_sub_flg_on(u_int status);
int mar_anime_flg_on(u_int status);
void mar_main_st_set(int status, struct shMariaWork* w);
void mar_sub_st_set(int status, struct shMariaWork* w);
void mar_sub_flg_set(int status, struct shMariaWork* w);
void MariaSetHeightDummy(void);
void MariaSetHeight(struct SubCharacter* this);
void MariaCheckDamage(struct SubCharacter* this);
void MariaCheckSetParameterPhase1(struct SubCharacter* this);
void MariaCheckSetParameterPhase2(struct SubCharacter* this);
void MariaCheckControl(struct SubCharacter* this);
void MariaCheckAnime(void);
void MariaUpdatePosition(struct SubCharacter* this);
void MariaCheckSound(void);
void MariaInitOnConnect(void);
void MariaSetHeightConnectWait(void);


#endif // M3_MARIA_SUB_H
