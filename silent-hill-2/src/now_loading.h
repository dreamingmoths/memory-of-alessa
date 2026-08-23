#ifndef NOW_LOADING_H
#define NOW_LOADING_H

#include "sh2_common.h"
#include "GFW/sh2_GsAllEnv.h"

unsigned short* dicSetStr(void* str /* r2 */);
void fjFontDrawExecVif1(void);
void fontClear(void);
void fontPrintStr(u_short* str /* r29+0x1C */, int x /* r2 */, int y /* r2 */);
void fontSetColorDirect(u_char r /* r2 */, u_char g /* r2 */, u_char b /* r2 */, u_char alp /* r2 */);
u_int sh2gfw_DeclimentLoopCounter(shGsAllEnv* stdb /* r2 */);
u_int sh2gfw_InclimentLoopCounter(shGsAllEnv* stdb /* r2 */);

extern int D_01F01DD0; // now_loading_enable
extern int D_01F01DD8; // now_loading_draw
extern int D_01F01DE0; // count

extern struct ScreenEffect_Parameter scr_efct;

#endif
