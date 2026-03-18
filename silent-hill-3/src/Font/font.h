#include "common.h"

#define FONT_STREAM_BUFFER_SIZE 0x4000
struct FONT_DATA {
    // total size: 0x215B0
    u_int tex_head[12]; // size 0x30
    u_int clut_head[12]; // size 0x30
    u_int clut[8]; // size 0x20
    u_char texbuf[131072]; // size 0x20000
    u_long tex0; // size 0x4
    int fonttype; // size 0x4
    u_int rgb_u; // size 0x4
    u_int rgb_d; // size 0x4
    u_int rgb_s[4]; // size 0x10
    u_int alpha; // size 0x4
    u_int alpha_base; // size 0x4
    u_int flag; // size 0x4
    u_short x; // size 0x2
    u_short y; // size 0x2
    u_short wide_w; // size 0x2
    u_short wide_h; // size 0x2
    u_short right_x; // size 0x2
    u_short right_y; // size 0x2
    u_short wm; // size 0x2
    u_short hm; // size 0x2
    short unk20C0; // size 0x2
    short wait_count; // size 0x2
    short wait_type; // size 0x2
    short page_sound; // size 0x2
    u_short code[400]; // size 0x320
    short upper[400]; // size 0x320
    short lower[400]; // size 0x320
    short top; // size 0x2
    short bottom; // size 0x2
    short st_num; // size 0x2
    short w_st_num; // size 0x2
    short prl_count; // size 0x2
    short preload; // size 0x2
    short shadow_max; // size 0x2
    short shadow_now; // size 0x2
    u_short sel_xl; // size 0x2
    u_short sel_xr; // size 0x2
    u_short sel_yu[4]; // size 0x8
    u_short sel_yd[4]; // size 0x8
    short sel_max; // size 0x2
    short sel_now; // size 0x2
    u_short mes_v[10][64]; // size 0x500
    u_short * unk20F50; // size 0x2
    u_short * mes_str_now; // size 0x4
    u_short * mes_str; // size 0x4
    u_short * prl_str; // size 0x4
    struct FONT_STREAM_DATA * stream; // size 0x4
    struct WFONT_STREAM_DATA * w_stream; // size 0x4
    struct MFONT_STREAM_DATA * m_stream; // size 0x4
    u_short stream_max; // size 0x2
    u_short w_stream_max; // size 0x2
    u_short m_stream_max; // size 0x2
    u_short m_code[256]; // size 0x200
    short m_upper[256]; // size 0x200
    short m_lower[256]; // size 0x200
    short m_top; // size 0x2
    short m_bottom; // size 0x2
    short m_st_num; // size 0x2
    int m_base_x; // size 0x4
    int m_base_y; // size 0x4
    int m_base_z; // size 0x4
    u_int m_rgba; // size 0x4
    int m_sx; // size 0x4
    int m_sy; // size 0x4
    int m_w; // size 0x4
    int m_h; // size 0x4
    int m_x; // size 0x4
    int m_y; // size 0x4
    float bar_blink; // size 0x4
    u_long * pCur; // size 0x4
    int base_x; // size 0x4
    int base_y; // size 0x4
    int base_z; // size 0x4
};

typedef struct WFONT_STREAM_DATA {
    // total size: 0x18
    /* 0x00 */ u_short x; // size 0x2
    /* 0x02 */ u_short y; // size 0x2
    /* 0x04 */ u_short vw; // size 0x2
    /* 0x06 */ u_short vh; // size 0x2
    /* 0x08 */ u_short u; // size 0x2
    /* 0x0A */ u_short v; // size 0x2
    /* 0x0C */ u_int rgb_u; // size 0x4
    /* 0x10 */ u_int rgb_d; // size 0x4
    /* 0x14 */ u_short w; // size 0x2
    /* 0x16 */ u_short h; // size 0x2
} WFONT_STREAM_DATA;

typedef struct MFONT_STREAM_DATA {
    // total size: 0x8
    /* 0x0 */ u_short x; // size 0x2
    /* 0x2 */ u_short y; // size 0x2
    /* 0x4 */ u_short u; // size 0x2
    /* 0x6 */ u_short v; // size 0x2
} MFONT_STREAM_DATA;

typedef struct FONT_STREAM_DATA
{
	u_short x;
	u_short y;
	u_short w;
	u_short h;
	u_short u;
	u_short v;
	u_int rgb_u;
	u_int rgb_d;
} FONT_STREAM_DATA;

struct FONT_DATA font;
extern void fontSetColor(int num);
extern void fontSetStreamMax(u_short s_max, u_short ws_max, u_short ms_max);
extern u_char D_01D08FA0[16];
extern short D_003585A8[20][2];
extern short D_003585AA[20][2];
extern u_long font_dma_data[34];
extern char D_01D08FB0[FONT_STREAM_BUFFER_SIZE];
extern void SeCall(float arg0, float arg1, long arg2);
int fontLoad(u_short code);
void fontClear(void);
void fontSetStreamMax(u_short s_max, u_short ws_max, u_short ms_max);
u_short fontPrintStrMain(u_short** pstr, int flag);
void fontSet(u_short code, u_short x, u_short y);
void fontSetBlankBox(int x0, int x1, int y);
void fontSetLine(int x, int w, int y);
void fontSetColorDirect(u_char r, u_char g, u_char b, u_char alp);
void fontSetAlpha(u_char alp);
void fontBarBlink(void);
void *fontTexLoad(int texadr, int clutadr);
void fontPushButton(void);
void fontPushButton2(void);
void fontSelectUp(void);
void fontSelectDown(void);
u_short *fontGetMesAdr(u_short *str, u_short num);
void fontMessage(u_short *str);
void fontNextMessage(void);
int fontGetStatus(void);
void fontWide(u_short w, u_short h);
void fontAllCenterOn(void);
void fontAllCenterOff(void);
void fontShadowOff(void);
void fontCrushOn(void);
void fontCrushOff(void);