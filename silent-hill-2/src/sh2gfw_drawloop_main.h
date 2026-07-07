#ifndef SH2GFW_DRAWLOOP_MAIN_H
#define SH2GFW_DRAWLOOP_MAIN_H

#include "sh2_common.h"

void all_Frame_Buffer_Clear(void);
void DrawLopp_Pre(void);
void kari_drawloop_main_2dSYNC(void);
void draw_main_3dSYNC(void);
void DrawLopp_Post(void);
u_int Get_FrameRate(void);
void draw_main(void);

#endif // SH2GFW_DRAWLOOP_MAIN_H
