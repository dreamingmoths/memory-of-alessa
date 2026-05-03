#ifndef FOG_H
#define FOG_H

#include "common.h"

/* some of these funcs may not exist in sh3, delete the missing ones */

void fogInit(void);

void fog_set_defpacket(void);

void fogSetEnvironment(FOG_ENV_DATA* edata);

void fogInitScreen(void);

void fogInitWind(void);

void fogChangeWind(int wind);

void fogInitParticle(void);

void fog_init_part_sub(FOG_PART_DATA* pd);

void fog_part_newpos(FOG_PART_DATA* pd);

void fogResetWall(void);

void fogSetWall(void* Vector);

void fogResetObj(void);

void fogSetObj(u_long ID, void* Center, float Size);

void fogMoveObj(u_long ID, void* Center);

void fogSetObj2(u_long ID, void* Center, float Size);

void fogEraseObj(u_long ID);

void fogSetObjSize(u_long ID, float Size);

FOG_OBJ_DATA* fogGetObj(u_long ID);

void fogMoveParticle(void);

void fog_load_objdata(void);

void fog_set_stay(void);

void fog_part_wall(void);

void fog_part_grid(void);

void fog_part_obj(void);

void fog_part_obj2(void);

void fog_part_alp(void);

void fog_part_clamp(void);

void fogMakePacket(void);

void fog_view_screen_fog(void);

void fogSetColor(u_char r, u_char g, u_char b, u_char a);

void fogSetPartNum(int PartNum);

void fogSetProjection(float Projection);

void fogSetFloorY(float FloorY);

void fogSetWorldScreenM(void* WorldScreenM);

void fogSetWorldViewM(void* WorldViewM);

void fogSetWorldPosV(void* WorldPosV);

void fogSetStayPos(void* WorldPosV);

void fogResetStayPos(void);

void fogSetStayPoint(void* StayPoint);

void fogResetStayPoint(void);

void fogSetCameraPosV(void* CameraPosV);

void fogSetLocalPosV(void);

void fogSetSpeedLevel(float SpeedLevel);

u_long* fogTex0Adr(void);

#endif // FOG_H
