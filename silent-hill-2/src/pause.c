#include "sh2_common.h"

#include "sce/libgraph.h"

#include "gs.h"

#include "shGs/sh2gfw_GS_NewLoopEnv.h"

#include "GFW/sh2gfw_macros.h"

#include "pause.h"

static void __DrawRect(int x0, int y0, int x1, int y1);
static void* draw_rect(void* pkt, int x, int y, int w, int h, int, int);
static void* draw_belt(void* pkt, int y, int h, int z, u_int c);

static PAUSE_TYPE pause_type = PAUSE_TYPE_NONE; // size: 0x1, address: 0x1F01C28

/* @note unused: static int pause_disable = FALSE; */

#line 41
int PauseSetType(int type) {
    int ret = pause_type; // r2
    pause_type = type;
    return ret;
}

#line 52
static void __DrawRect(int x0, int y0, int x1, int y1) {
    static Q_WORDDATA KARI_OBI[16]; // @ 0x01F01CD0
    int id = FALSE; // r2


    
    SET_DMATAG(KARI_OBI, id, DMAcnt | 10, 0, 0, SCE_VIF1_SET_DIRECT(10, 0));

    
    SET_GIFTAG(KARI_OBI, id, SCE_GIF_SET_TAG(1, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);

    #line 73
    SET_ADDRESS_DATA(KARI_OBI, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_GREATER, 1, 0, 0, 0, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));


    KARI_OBI[id].ul64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0), SCE_GIF_PACKED, 3);
    KARI_OBI[id++].ul64[1] = GIF_REGLIST(SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_XYZ2);


    SET_QWORD_U32(KARI_OBI, id, 0, 0, 0, 2);

    KARI_OBI[id].ul64[0] = SH_GIF_PACK_XY(16 * (x0 + 1792), 16 * (y0 + 1792)), KARI_OBI[id++].ul64[1] = 16; // @todo Q4 macro does not match here
    KARI_OBI[id].ul64[0] = SH_GIF_PACK_XY(16 * (x1 + 2304), 16 * (y1 + 1792)), KARI_OBI[id++].ul64[1] = 16; // @todo Q4 macro does not match here
   
    SET_QWORD_U32(KARI_OBI, id, DMAend, 0, 0, 0);
    
    d1cSend(&KARI_OBI);
    d1sSync(0, -1);
}

#line 120
static void* draw_rect(void* pkt, int x, int y, int w, int h, int, int) {
    #line 122
    __DrawRect(x, y, x + w, y + h);

    #line 223
    return pkt;
}

#line 228
static void* draw_belt(void* pkt, int y, int h, int z, u_int c) {
    return draw_rect(pkt, 0, y, 512, h, z, c);
}

static u_long128 buffer[9]; // size: 0x90, address: 0x1F01C40

#line 235
int PauseDisp(void) {
    static s_char m_please_insert[37] = "\\c\\hPlease insert Silent Hill 2 disc"; // @ 0x0037DA20
    static s_char m_paused[11] = "\\c\\hPaused"; // @ 0x0037DA48
    static s_char m_wrong_disc[15] = "\\c\\hWrong disc"; // @ 0x0037DA58
    static s_char m_not_connect[29] = "\\c\\hController not connected"; // @ 0x0037DA70
    static s_char m_not_insert[22] = "\\c\\hDisc not inserted"; // @ 0x0037DA90
    static s_char m_tray_open[19] = "\\c\\hDisc tray open"; // @ 0x0037DAB0
    static s_char m_now_loding[16] = "\\c\\hNow loading"; // @ 0x0037DAD0
    static s_char m_please_wait[16] = "\\c\\hPlease wait"; // @ 0x0037DAE0
    static s_char m_checking[18] = "\\c\\hChecking disc"; // @ 0x0037DAF0
    static int force_pause = FALSE; // @ 0x01F01C30
    static int count = 0; // @ 0x01F01C38
    int ret = TRUE; // r16
    u_long128* packet = buffer; // r17
    u_long128* pkt; // r2
    int pz; // r2
    int ccolor; // r18
    int belt; // r19
    s_char* mes; // r20
    u_int bcolor; // r2

    count += TRUE;
    switch (pause_type) {
        default:
            break;

        case PAUSE_TYPE_NONE:
            count = 0;
            ret = FALSE;
            force_pause = FALSE;
    }

    if (ret) {
        ccolor = 0;
        belt = FALSE;
        mes = NULL;
        sh2gfw_Set_PauseRetain();
        kari_drawloop_main_2dSYNC();

        switch (pause_type) {
            case PAUSE_TYPE_NONE:
            case PAUSE_TYPE_UNDEFINED:
                break;

            case PAUSE_TYPE_GAME_PAUSE:
                belt = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                mes = m_paused;
                break;

            case PAUSE_TYPE_NOW_LOADING:
                belt = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                if ((count * 2) & 256) {
                    mes = m_please_wait;
                } else {
                    mes = m_now_loding;
                }
                break;

            case PAUSE_TYPE_LOAD_DELAY:
                belt = TRUE;
                break;

            case PAUSE_TYPE_TRAY_OPEN:
                force_pause = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                if ((count * 2) & 256) {
                    mes = m_please_insert;
                } else {
                    mes = m_tray_open;
                }
                break;

            case PAUSE_TYPE_DISC_EMPTY:
                force_pause = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                if ((count * 2) & 256) {
                    mes = m_please_insert;
                } else {
                    mes = m_not_insert;
                }
                break;

            case PAUSE_TYPE_DISC_CHECK:
                force_pause = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                mes = m_checking;
                break;

            case PAUSE_TYPE_DISC_ILLEGAL:
                force_pause = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                if ((count * 2) & 256) {
                    mes = m_please_insert;
                } else {
                    mes = m_wrong_disc;
                }
                break;

            case PAUSE_TYPE_PAD_DISCONNECT:
                force_pause = TRUE;
                ccolor = (count * 2) & 255;
                if (ccolor > 128) {
                    ccolor = 255 - ccolor;
                }
                if ((count * 2) & 256) {
                    mes = m_paused;
                } else {
                    mes = m_not_connect;
                }
        }

        if (force_pause) belt = TRUE;

        if (mes != NULL) {
            if (belt) {
                bcolor =  COLOR_RGBA(255, 255, 255, 8);
                draw_belt(packet, 256, 32, 16, bcolor);
            }
            sh2gfw_InclimentLoopCounter(&shGs_AllEnv);
            fontSetColorDirect(ccolor & 255, ccolor & 255, ccolor & 255, 128);
            fontPrintStr(dicSetStr(mes), 256, 256);
            fjFontDrawExecVif1();
            fontClear();
            sh2gfw_DeclimentLoopCounter(&shGs_AllEnv);
        }
    } else {
        sh2gfw_Reset_PauseRetain();
    }

    pause_type = FALSE;

    return ret;
}


