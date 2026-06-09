#ifndef LIBGRAPH_H
#define LIBGRAPH_H

#include "eeregs.h"

#define SCE_GS_FALSE (0)
#define SCE_GS_TRUE  (1)

#define SCE_GS_PSMCT32			(0)
#define SCE_GS_PSMCT24			(1)
#define SCE_GS_PSMCT16			(2)
#define SCE_GS_PSMCT16S			(10)
#define SCE_GS_PSMT8			(19)
#define SCE_GS_PSMT4			(20)
#define SCE_GS_PSMT8H			(27)
#define SCE_GS_PSMT4HL			(36)
#define SCE_GS_PSMT4HH			(44)
#define SCE_GS_PSMZ32			(48)
#define SCE_GS_PSMZ24			(49)
#define SCE_GS_PSMZ16			(50)
#define SCE_GS_PSMZ16S			(58)

#define SCE_GS_PRIM_POINT		(0)
#define SCE_GS_PRIM_LINE		(1)
#define SCE_GS_PRIM_LINESTRIP		(2)
#define SCE_GS_PRIM_TRI			(3)
#define SCE_GS_PRIM_TRISTRIP		(4)
#define SCE_GS_PRIM_TRIFAN		(5)
#define SCE_GS_PRIM_SPRITE		(6)
#define SCE_GS_PRIM_IIP			(1<<3)
#define SCE_GS_PRIM_TME			(1<<4)
#define SCE_GS_PRIM_FGE			(1<<5)
#define SCE_GS_PRIM_ABE			(1<<6)
#define SCE_GS_PRIM_AA1			(1<<7)
#define SCE_GS_PRIM_FST			(1<<8)
#define SCE_GS_PRIM_CTXT1		(0)
#define SCE_GS_PRIM_CTXT2		(1<<9)
#define SCE_GS_PRIM_FIX			(1<<10)

#define SCE_GS_MODULATE			(0)
#define SCE_GS_DECAL			(1)
#define SCE_GS_HILIGHT			(2)

#define SCE_GS_ZNOUSE			(0)
#define SCE_GS_ZALWAYS			(1)
#define SCE_GS_ZGEQUAL			(2)
#define SCE_GS_ZGREATER			(3)

#define SCE_GS_AFAIL_KEEP		(0)
#define SCE_GS_AFAIL_FB_ONLY		(1)
#define SCE_GS_AFAIL_ZB_ONLY		(2)
#define SCE_GS_AFAIL_RGB_ONLY		(3)

#define SCE_GS_ALPHA_NEVER		(0)
#define SCE_GS_ALPHA_ALWAYS		(1)
#define SCE_GS_ALPHA_LESS		(2)
#define SCE_GS_ALPHA_LEQUAL		(3)
#define SCE_GS_ALPHA_EQUAL		(4)
#define SCE_GS_ALPHA_GEQUAL		(5)
#define SCE_GS_ALPHA_GREATER		(6)
#define SCE_GS_ALPHA_NOTEQUAL		(7)

#define SCE_GS_ALPHA_CS			(0)
#define SCE_GS_ALPHA_CD			(1)
#define SCE_GS_ALPHA_ZERO		(2)
#define SCE_GS_ALPHA_AS			(0)
#define SCE_GS_ALPHA_AD			(1)
#define SCE_GS_ALPHA_FIX		(2)

typedef struct {
	tGS_PMODE	pmode;
	tGS_SMODE2	smode2;
	tGS_DISPFB2	dispfb;
	tGS_DISPLAY2	display;
	tGS_BGCOLOR	bgcolor;
} sceGsDispEnv;

#endif
