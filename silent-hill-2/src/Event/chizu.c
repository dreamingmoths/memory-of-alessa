#include "Event/chizu.h"
#include "Event/event.h"
#include "Event/picture.h"

#include "Effect/screen_effect.h"

#include "Chacter/character.h"

#include "data/fs_structs.h"

#include "Fog/spack.h"

#include "Font/font.h"

#include "gamemain.h"

#include "GFW/sh2gfw_structs.h"

#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/dma/dma1cmd.h"

#include "SH2_common/sh2dt.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/pad.h"

#include "sound/sh_sound.h"

static int ChizuSelect(void);
static int ChizuPossessionCheck(int chizu);
static void ChizuFileLoad(int load_chizu);
static void ChizuDisplay(void);
static void ChizuMarkerDraw(void);
static void ChizuControl(void);
static void ChizuConnectArrowDraw(void);
static int ChizuConnectCheck(int chizu, int connect);
static void ChizuCurrentPositionDraw(void);
static void ChizuCurrentPositionCheck(float* px, float* py);

extern /* static */ int chizu_from; // size: 0x4, address: 0x116DB78
extern /* static */ int chizu_crnt; // size: 0x4, address: 0x116DB80
extern /* static */ int chizu_next; // size: 0x4, address: 0x116DB88
extern /* static */ float disp_rate; // size: 0x4, address: 0x116DB90
extern fsFileIndex* cursor_file; // size: 0x4, address: 0x116DB98
extern fsFileIndex* marker_file; // size: 0x4, address: 0x116DBA0
extern fsFileIndex* base_file; // size: 0x4, address: 0x116DBA8
extern int chizu_disp_step; // size: 0x4, address: 0x116DBB0
extern float chizu_center_y; // size: 0x4, address: 0x116DBB8
extern float chizu_center_x; // size: 0x4, address: 0x116DBC0

extern /* static */ Chizu_CurrentBlock chz_crt_block[190]; // size: 0x8E8, address: 0x33BEF0
extern /* static */ Chizu_ConnectInfo chz_connect[36]; // size: 0x90, address: 0x33C7E0

void ChizuMain(void) {
    
    
    while (TRUE) {
        switch (Sh2sys.step[SH2SYS_CONNECT]) {
            default:
            case 0:
                chizu_from = 1;
                Sh2sys.step[SH2SYS_CONNECT] = 2;
                
                
                
                break;            
            case 1:
                chizu_from = 0;
                Sh2sys.step[SH2SYS_CONNECT] = 2;
                
                
                
                break;
            case 2:
                disp_rate = 0.0f;
                chizu_crnt = 0;
                chizu_next = ChizuSelect();
                
                chizu_disp_step = 0;
                base_file = NULL;
                marker_file = NULL;
                cursor_file = NULL;
                
                
                if (ChizuPossessionCheck(chizu_next)) {
                    ChizuFileLoad(chizu_next);
                } else {
                    
                    
                    
                    chizu_next = 0;
                    if (GET_GAME_FLAG(GAME_FLAG_24)) {
                        ChizuFileLoad(1);
                    }
                }
                
                ScreenEffectFadeStart(1, 0.0f);
                Sh2sys.step[3] = 3;
                break;
            
            case 3:
                if (!ScreenEffectFadeCheck()) return;
                
                if (chizu_next == 0) {
                    ScreenEffectFadeStart(5, 0.0f);
                    fontMessageNum(msg_station, 3);
                    Sh2sys.step[SH2SYS_CONNECT] = 4;
                } else Sh2sys.step[SH2SYS_CONNECT] = 5;                
                break;
            
            
            case 4:
                if (fontGetStatus() != -2) return;                
                fontClear();
                ScreenEffectFadeStart(3, 0.0f);
                
                if (chizu_next == 0) {
                    if (!GET_GAME_FLAG(GAME_FLAG_24)) {
                        Sh2sys.step[SH2SYS_CONNECT] = 9;
                        
                    } else {
                        chizu_next = 1;
                        Sh2sys.step[SH2SYS_CONNECT] = 5;
                    }
                } else {
                    
                    Sh2sys.step[SH2SYS_CONNECT] = 5;
                }
                break;
            
            case 5:
                if (fsSync(1, -1) < 0) return;                
                if (!ScreenEffectFadeCheck()) return;                
                chizu_crnt = chizu_next;
                chizu_next = 0;
                SeCall(11031, 1.0f, 0);
                ScreenEffectFadeStart(4, 0.0f);
                if (chizu_crnt == ChizuSelect()) {
                    
                    ChizuCurrentPositionCheck(&chizu_center_x, &chizu_center_y);
                    
                    chizu_center_x *= 2.0f;
                    chizu_center_y *= 2.0f;
                } else {
                    chizu_center_x = 0.0f;
                    chizu_center_y = 0.0f;
                }
                Sh2sys.step[SH2SYS_CONNECT] = 6;
                break;
            
            case 6:
                ChizuDisplay();
                if (!ScreenEffectFadeCheck()) return;                
                Sh2sys.step[SH2SYS_CONNECT] = 7;
                return;
            
            case 7:
                ChizuDisplay();
                ChizuControl();
                if (chizu_next) {
                    ScreenEffectFadeStart(1, 0.0f);
                    Sh2sys.step[SH2SYS_CONNECT] = 8;
                }
                return;
            
            
            
            case 8:
                if (chizu_next == -1) Sh2sys.step[SH2SYS_CONNECT] = 9;
                else {
                    ChizuFileLoad(chizu_next);
                    Sh2sys.step[SH2SYS_CONNECT] = 5;
                }
                return;
            
            
            case 9:
                if (!ScreenEffectFadeCheck()) return;                
                if (chizu_from) {
                    
                    sh2sys_set_2(4);
                } else {
                    
                    
                    sh2sys_set_2(6);
                }
                
                ScreenEffectFadeStart(4, 0.0f);
                return;
        }
    }
}

#ifdef NON_MATCHING
static int ChizuSelect(void) {
    SubCharacter* jms;
    int room;
    int work;
    
    jms = sh2jms.player;
    room = RoomName(0, jms->pos.x, jms->pos.z);
    work = chz_crt_block[room].chizu;
    
    
    switch (room) {
        case 0xF:
            if ((jms->pos.y > -750.0) ||
                ((jms->pos.x < -60000.0f) && (jms->pos.y > -1000.0f))) {
                work = 4;
            } else if ((jms->pos.y > -2350.0) ||
                       ((jms->pos.x < -60000.0f) && (jms->pos.y > -2600.0f))) {
                work = 5;
            } else {
                work = 6;
            }
            break;
        
        case 0x10:
            if (jms->pos.y > -900.0 ||
                (jms->pos.z > -19300.0f && jms->pos.y > -1150.0f)) {
                work = 4;
            } else if ((jms->pos.y > -2700.0) ||
                       (jms->pos.z > -19300.0f && jms->pos.y > -3450.0f)) {
                work = 5;
            } else {
                work = 6;
            }
            break;
        
        case 0x11:
            if (jms->pos.y > -900.0 ||
                ((jms->pos.z > -59300.0f) && (jms->pos.y > -1150.0f))) {
                work = 4;
            } else if ((jms->pos.y > -2700.0) ||
                       ((jms->pos.z > -59300.0f) && (jms->pos.y > -3450.0f))) {
                work = 5;
            } else {
                work = 6;
            }
            break;
        
        case 0x20:
            if ((jms->pos.z < -19200.0f) && (jms->pos.y > -1050.0f)) {
                work = 7;
            } else {
                work = 8;
            }
            break;
        case 0x92:
            if (jms->pos.y > -1400.0f) {
                
                work = 21;
            } else {
                
                
                work = 22;
            }
            break;
        
        case 0x21:
            if ((jms->pos.y < -855.0f) ||
                ((jms->pos.z > -99431.0f) && (jms->pos.y < -854.0f))) {
                work = 8;
            } else {
                
                
                work = 7;
            }
            break;
        
        case 0x29:
            if ((jms->pos.y > -950.0f) ||
                ((jms->pos.z > -100000.0f) && (jms->pos.y > -1200.0f))) {
                work = 12;
            } else {
                work = 13;
            }
            break;
        
        case 0x2A:
            if (GET_GAME_FLAG(GAME_FLAG_17)) work = 12;            
            if (GET_GAME_FLAG(GAME_FLAG_18) || GET_GAME_FLAG(GAME_FLAG_19)) 
                work = 13;            
            break;
        
        case 0x46:
            if (GET_GAME_FLAG(GAME_FLAG_17)) work = 14;            
            if (GET_GAME_FLAG(GAME_FLAG_18) || GET_GAME_FLAG(GAME_FLAG_19)) 
                work = 15;            
            break;        
        case 0x91:
        case 0xAB:
            if ((jms->pos.y < -920.0f) ||
                ((jms->pos.z < -20020.0f) && (jms->pos.y < -874.0f))) {
                work = 29;
            } else {
                work = 28;
            }
            
            break;
        
        
        case 0x47:
            if ((jms->pos.y >= -1000.0f) ||
                ((jms->pos.z > -219978.0f) && (jms->pos.y > -1001.0f))) {
                
                work = 14;
            } else {
                work = 15;
            }
            break;
        case 0x48:
            if ((jms->pos.y > -1000.0f) ||
                ((jms->pos.y < -1001.0f) && (jms->pos.z > -99992.0f) && (jms->pos.y >= -1000.0f))) {
                
                
                work = 12;
            } else {
                
                
                work = 15;
            }
            break;
    }
    
    
    if (GET_GAME_FLAG(GAME_FLAG_25) && GET_GAME_FLAG(GAME_FLAG_26)) {
        
        if ((4 <= work) && (work < 7)) {
            work += 5;
        } else if (7 <= work && work < 9) {
            work += 2;
        }
    }
    
    if (GET_GAME_FLAG(GAME_FLAG_31)) {
        if ((20 <= work) && (work < 28)) {
            work += 8;
        }
    }
    
    
    if (work == 17) {
        
        work = 16;
    }
    return work;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuSelect);
#endif

static int ChizuPossessionCheck(int chizu) {
    switch (chizu) {
        default:
            return 1;
    
        case 1:
        case 2:
        case 3:
            if (GET_GAME_FLAG(GAME_FLAG_24)) return 1;
            
            break;
        case 4:
        case 5:
        case 6:
            if (GET_GAME_FLAG(GAME_FLAG_25)) return 1;
            
            break;
        
            case 9:
        case 10:
        case 11:
            if (GET_GAME_FLAG(GAME_FLAG_26) && GET_GAME_FLAG(GAME_FLAG_25))
                
                return 1;        
            break;
        case 7:
        case 8:
            if (GET_GAME_FLAG(GAME_FLAG_26)) return 1;
            
            break;
        case 14:
        case 15:
            if (!GET_GAME_FLAG(GAME_FLAG_215)) break;
            
        case 12:
        case 13:
            if (GET_GAME_FLAG(GAME_FLAG_27)) return 1;
            
            break;
        case 16:
        case 17:
            if (GET_GAME_FLAG(GAME_FLAG_28)) return 1;
            
            break;
        case 18:
        case 19:
            if (GET_GAME_FLAG(GAME_FLAG_29)) return 1;
            
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            if (!GET_GAME_FLAG(GAME_FLAG_476)) break;        
            else if (GET_GAME_FLAG(GAME_FLAG_30)) return 1;
        case 20:
        case 21:
        case 22:
        case 23:
            if (GET_GAME_FLAG(GAME_FLAG_30)) return 1;            
        case 28:
        case 29:
        case 30:
        case 31:
            if (GET_GAME_FLAG(GAME_FLAG_31)) return 1;
            
            break;
        case 32:
        case 33:
        case 34:
        case 35:
            if (GET_GAME_FLAG(GAME_FLAG_476)) 
                if (GET_GAME_FLAG(GAME_FLAG_31)) return 1;                        
        case 0: break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuFileLoad);

static void ChizuDisplay(void) {
    PicDraw_Data pic0;
    float u0;
    float v0;
    float u1;
    float v1;

    if (chizu_disp_step == 1) {
        disp_rate += shGetDT();
        if (disp_rate > 1.0f) {
            disp_rate = 1.0f;
            chizu_disp_step = 2;
        }
    } else if (chizu_disp_step == 3) {
        disp_rate -= shGetDT();
        if (disp_rate < 0.0f) {
            disp_rate = 0.0f;
            chizu_disp_step = 0;
        }
    }
    
    u0 = (256.0f + chizu_center_x) * disp_rate;
    v0 = (256.0f + chizu_center_y) * disp_rate;
    u1 = u0 + 512.0f * (2.0f - disp_rate);
    v1 = v0 + 512.0f * (2.0f - disp_rate);
    if (u0 < 0.0f) u0 = 0.0f;    
    if (v0 < 0.0f) v0 = 0.0f;
    if (u1 > 1023.0f) u1 = 1023.0f;    
    if (v1 > 1023.0f) v1 = 1023.0f;
    
    
    spkResetOT();
    
    PictureLoadImage(get_gp_data_buf_addr(), 0, -1, -1);
    
    shQzero(&pic0, sizeof(PicDraw_Data));
    
    picture_set_ap(&pic0, get_gp_data_buf_addr());
    pic0.otp = 1;    
    // @todo: add macro/inline
    pic0.us0 = FTOI4(u0); pic0.vt0 = FTOI4(v0); pic0.us1 = FTOI4(u1); pic0.vt1 = FTOI4(v1); pic0.status |= 4;
    PictureDraw(&pic0);
    
    ChizuMarkerDraw();
    ChizuConnectArrowDraw();
    
    
    
    if (chizu_crnt == ChizuSelect()) ChizuCurrentPositionDraw();
    
    d1cSend(spkDmaKick());
}

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuMarkerDraw);

static void ChizuControl(void) {
    float anx; 
    float any;
    u_char lsx;
    u_char lsy;


    
    if (chizu_disp_step == 0) {
        if (shPadTrigger(0, key_config.enter)) chizu_disp_step = 1;
        else if (shPadTrigger(0, PAD_KEY_DPAD_UP)) {
            chizu_next = ChizuConnectCheck(chizu_crnt, 0);
        } else if (shPadTrigger(0, PAD_KEY_DPAD_DOWN)) {
            chizu_next = ChizuConnectCheck(chizu_crnt, 1);
        } else if (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) {
            chizu_next = ChizuConnectCheck(chizu_crnt, 2);
        } else if (shPadTrigger(0, PAD_KEY_DPAD_LEFT)) {
            chizu_next = ChizuConnectCheck(chizu_crnt, 3);
        }
    } else
        if (shPadTrigger(0, key_config.enter)) {
            if (chizu_disp_step == 3) chizu_disp_step = 1;
            else chizu_disp_step = 3;
    } else {
        lsx = shPadPress(0, PAD_KEY_6);
        if (lsx >= 0x9B) 
            anx = (lsx - 0x9B) / 100.0f;
        else if (lsx < 0x65) 
            anx = (lsx - 0x64) / 100.0f;
        else anx = 0.0f;        
        lsy = shPadPress(0, PAD_KEY_7);
        if (lsy >= 0x9B)
            any = (lsy - 0x9B) / 100.0f;
        else if (lsy < 0x65) 
            any = (lsy - 0x64) / 100.0f;
        else any = 0.0f;        
        if ((anx != 0.0f) || (any != 0.0f)) {
            chizu_center_x += 307.2f * anx * shGetDT();
            chizu_center_y += 384.0f * any * shGetDT();
        } else {
            if (shPadPress(0, PAD_KEY_DPAD_RIGHT)) {
                chizu_center_x += 307.2f * shGetDT();
            } else if (shPadPress(0, PAD_KEY_DPAD_LEFT)) {
                chizu_center_x -= 307.2f * shGetDT();
            }
            if (shPadPress(0, PAD_KEY_DPAD_UP)) {
                chizu_center_y -= 384.0f * shGetDT();
            } else if (shPadPress(0, PAD_KEY_DPAD_DOWN)) {
                chizu_center_y += 384.0f * shGetDT();
            }
        }
        if (chizu_center_x > 256.0f) chizu_center_x = 256.0f;        
        if (chizu_center_x < -256.0f) chizu_center_x = -256.0f;        
        if (chizu_center_y > 256.0f) chizu_center_y = 256.0f;        
        if (chizu_center_y < -256.0f) chizu_center_y = -256.0f;
        
    }
    
    
    if ((shPadTrigger(0, key_config.cancel)) || (shPadTrigger(0, key_config.map))) 
        chizu_next = -1;    
}

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuConnectArrowDraw);

static int ChizuConnectCheck(int chizu, int connect) {
    int work;

    switch (connect) {
        default:
        case 0:             work = chz_connect[chizu].up;     break;
        case 1:             work = chz_connect[chizu].down;   break;
        case 2:             work = chz_connect[chizu].right;  break;
        case 3:             work = chz_connect[chizu].left;   break;
    }
    
    
    if (work == 0) return 0;
    
    if ((connect == 2) || (connect == 3)) {
        
        switch (work) {
            case 1:
                if ((chizu_crnt > 0) && (chizu_crnt < 4)) 
                    return 0;                
                break;            
            case 9:
                if ((4 <= chizu_crnt) && (chizu_crnt < 12)) 
                    return 0;                
                break;
            case 12:
                if ((12 <= chizu_crnt) && (chizu_crnt < 16)) 
                    return 0;                
                break;
            case 16:
                if ((16 <= chizu_crnt) && (chizu_crnt < 20)) 
                    return 0;                
                break;
            case 21:
                if ((20 <= chizu_crnt) && (chizu_crnt < 24)) 
                    return 0;                
                break;
            case 29:
                if ((28 <= chizu_crnt) && (chizu_crnt < 32)) 
                    return 0;                
                break;
        }
        
        if (ChizuPossessionCheck(work)) return work;
        
        if (work == 9) {
            if (ChizuPossessionCheck(4))
                return 4;            
            if (ChizuPossessionCheck(7))
                return 7;            
        } else if (work == 16) {
            if (ChizuPossessionCheck(18))
                return 18;            
        } else if (work == 29) {
            if (ChizuPossessionCheck(21))
                return 21;
            
        }
        return ChizuConnectCheck(work, connect);
    }
    return ChizuPossessionCheck(work) ? work : 0;


}

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuCurrentPositionDraw);

#define SET_MAP_POSITION(_x, _z) do { \
    *px = (_x * jms->pos.x) + chz_crt_block[room].cp_x; \
    *py = chz_crt_block[room].cp_y - (_z * jms->pos.z); \
} while (0);

// @todo: add room names
static void ChizuCurrentPositionCheck(float* px, float* py) {
    SubCharacter* jms;
    int room = RoomNameJms(); // r18
    float tmp; // r29+0x70

    jms = sh2jms.player;

    switch (RoomNameJms()) {                              /* switch 1 */
        default:                                        /* switch 1 */
            // single precision
            SET_MAP_POSITION(0.00142f, 0.00196f);
            return;
        case 0x3:                                       /* switch 1 */
            // double precision
            SET_MAP_POSITION(0.00053, 0.00079);
            return;
        case 0x1:                                       /* switch 1 */
        case 0x2:                                       /* switch 1 */
        case 0x5:                                       /* switch 1 */
        case 0x6:                                       /* switch 1 */
        case 0x9:                                       /* switch 1 */
        case 0xA:                                       /* switch 1 */
        case 0xB:                                       /* switch 1 */
        case 0xC:                                       /* switch 1 */
        case 0xD:                                       /* switch 1 */
            *px = chz_crt_block[room].cp_x;
            *py = chz_crt_block[room].cp_y;
            return;
        case 0x8:
            if ((jms->pos.x> 30453.578906) && (jms->pos.x < 35960.0f)) {
                if (jms->pos.z >= -60828.847656 && (jms->pos.z <= -59016.0f)) {
                    *px = 212.4619f;
                    *py = 183.76071f;
                    return;
                }
            }
            SET_MAP_POSITION(0.00146f, 0.00196f);
            return;
        case 0x78:                                      /* switch 1 */
        case 0x79:                                      /* switch 1 */
        case 0x7A:                                      /* switch 1 */
        case 0x7B:                                      /* switch 1 */
        case 0x7C:                                      /* switch 1 */
        case 0x7D:                                      /* switch 1 */
        case 0x7E:                                      /* switch 1 */
        case 0x7F:                                      /* switch 1 */
        case 0x80:                                      /* switch 1 */
        case 0x81:                                      /* switch 1 */
        case 0x82:                                      /* switch 1 */
        case 0x83:                                      /* switch 1 */
        case 0x84:                                      /* switch 1 */
        case 0x85:                                      /* switch 1 */
        case 0x86:                                      /* switch 1 */
        case 0x87:                                      /* switch 1 */
        case 0x88:                                      /* switch 1 */
        case 0x89:                                      /* switch 1 */
        case 0x8A:                                      /* switch 1 */
        case 0x8B:                                      /* switch 1 */
        case 0x8C:                                      /* switch 1 */
        case 0x8D:                                      /* switch 1 */
            SET_MAP_POSITION(0.01007f, 0.0089f);
            tmp = *px;
            *px = -*py;
            *py = tmp;
            return;
        case 0x66:                                      /* switch 1 */
        case 0x67:                                      /* switch 1 */
        case 0x68:                                      /* switch 1 */
        case 0x69:                                      /* switch 1 */
        case 0x6A:                                      /* switch 1 */
        case 0x6B:                                      /* switch 1 */
        case 0x6C:                                      /* switch 1 */
        case 0x6D:                                      /* switch 1 */
        case 0x6E:                                      /* switch 1 */
        case 0x6F:                                      /* switch 1 */
        case 0x70:                                      /* switch 1 */
        case 0x71:                                      /* switch 1 */
        case 0x73:                                      /* switch 1 */
        case 0x74:                                      /* switch 1 */
            SET_MAP_POSITION(0.01377f, 0.010408f);
            tmp = *px;
            *px = *py;
            *py = -tmp;
            return;
        case 0x72:                                      /* switch 1 */
            SET_MAP_POSITION(0.01377f, 0.009988f);
            tmp = *px;
            *px = *py;
            *py = -tmp;
            return;
        case 0x20:                                      /* switch 1 */
        case 0x21:                                      /* switch 1 */
        case 0x22:                                      /* switch 1 */
        case 0x23:                                      /* switch 1 */
        case 0x24:                                      /* switch 1 */
        case 0x27:                                      /* switch 1 */
        case 0x28:                                      /* switch 1 */
            SET_MAP_POSITION(0.0087f, 0.0096f);
            if (!(GET_GAME_FLAG(GAME_FLAG_25)) && ((GET_GAME_FLAG(GAME_FLAG_26)) == 1)) {
                switch (chizu_crnt) {                   /* switch 2; irregular */
                case 7:                                 /* switch 2 */
                    *px += 24.965286f;
                    return;
                case 8:                                 /* switch 2 */
                    *px += 164.96529f;
                    return;
                }
            }
            break;
        case 0x25:                                      /* switch 1 */
        case 0x26:                                      /* switch 1 */
            SET_MAP_POSITION(0.00801f, 0.01037f);
            if (!(GET_GAME_FLAG(GAME_FLAG_25)) && ((GET_GAME_FLAG(GAME_FLAG_26)) == 1)) {
                switch (chizu_crnt) {                   /* switch 3; irregular */
                case 7:                                 /* switch 3 */
                    *px += 16.965286f;
                    return;
                case 8:                                 /* switch 3 */
                    *px += 158.96529f;
                    return;
                }
            }
            break;
        case 0xF:                                       /* switch 1 */
        case 0x10:                                      /* switch 1 */
        case 0x11:                                      /* switch 1 */
        case 0x13:                                      /* switch 1 */
        case 0x14:                                      /* switch 1 */
        case 0x16:                                      /* switch 1 */
        case 0x17:                                      /* switch 1 */
        case 0x18:                                      /* switch 1 */
        case 0x19:                                      /* switch 1 */
        case 0x1A:                                      /* switch 1 */
        case 0x1B:                                      /* switch 1 */
        case 0x1C:                                      /* switch 1 */
        case 0x1D:                                      /* switch 1 */
        case 0x1E:                                      /* switch 1 */
            SET_MAP_POSITION(0.0087f, 0.0096f);
            return;
        case 0x7:                                       /* switch 1 */
        case 0x12:                                      /* switch 1 */
        case 0x15:                                      /* switch 1 */
        case 0x1F:                                      /* switch 1 */
            SET_MAP_POSITION(0.00801f, 0.01037f);
            return;
        case 0x92:                                      /* switch 1 */
        case 0xA2:                                      /* switch 1 */
        case 0xAC:                                      /* switch 1 */
            SET_MAP_POSITION(0.0164f, 0.0209f);
            return;
        case 0x99:                                      /* switch 1 */
        case 0x9A:                                      /* switch 1 */
        case 0x9F:                                      /* switch 1 */
        case 0xA0:                                      /* switch 1 */
        case 0xA1:                                      /* switch 1 */
        case 0xA3:                                      /* switch 1 */
        case 0xA8:                                      /* switch 1 */
        case 0xA9:                                      /* switch 1 */
        case 0xAD:                                      /* switch 1 */
        case 0xAE:                                      /* switch 1 */
        case 0xAF:                                      /* switch 1 */
        case 0xB1:                                      /* switch 1 */
        case 0xB2:                                      /* switch 1 */
        case 0xB5:                                      /* switch 1 */
        case 0xB8:                                      /* switch 1 */
        case 0xB9:                                      /* switch 1 */
            SET_MAP_POSITION(0.01607f, 0.0207f);
            return;
        case 0x91:                                      /* switch 1 */
        case 0x93:                                      /* switch 1 */
        case 0x94:                                      /* switch 1 */
        case 0x95:                                      /* switch 1 */
        case 0x96:                                      /* switch 1 */
        case 0x97:                                      /* switch 1 */
        case 0x98:                                      /* switch 1 */
        case 0x9B:                                      /* switch 1 */
        case 0x9C:                                      /* switch 1 */
        case 0x9D:                                      /* switch 1 */
        case 0x9E:                                      /* switch 1 */
        case 0xA5:                                      /* switch 1 */
        case 0xA6:                                      /* switch 1 */
        case 0xA7:                                      /* switch 1 */
        case 0xAB:                                      /* switch 1 */
        case 0xB0:                                      /* switch 1 */
        case 0xB6:                                      /* switch 1 */
        case 0xB7:                                      /* switch 1 */
            SET_MAP_POSITION(0.0164f, 0.01875f);
            return;
        case 0x2B:                                      /* switch 1 */
        case 0x2C:                                      /* switch 1 */
        case 0x2D:                                      /* switch 1 */
        case 0x2E:                                      /* switch 1 */
        case 0x2F:                                      /* switch 1 */
        case 0x31:                                      /* switch 1 */
        case 0x32:                                      /* switch 1 */
        case 0x33:                                      /* switch 1 */
        case 0x34:                                      /* switch 1 */
        case 0x35:                                      /* switch 1 */
        case 0x36:                                      /* switch 1 */
        case 0x37:                                      /* switch 1 */
        case 0x38:                                      /* switch 1 */
        case 0x39:                                      /* switch 1 */
        case 0x3A:                                      /* switch 1 */
        case 0x3C:                                      /* switch 1 */
        case 0x3D:                                      /* switch 1 */
        case 0x3E:                                      /* switch 1 */
        case 0x3F:                                      /* switch 1 */
        case 0x40:                                      /* switch 1 */
        case 0x41:                                      /* switch 1 */
        case 0x42:                                      /* switch 1 */
        case 0x43:                                      /* switch 1 */
        case 0x44:                                      /* switch 1 */
        case 0x45:                                      /* switch 1 */
        case 0x49:                                      /* switch 1 */
        case 0x4A:                                      /* switch 1 */
        case 0x4B:                                      /* switch 1 */
        case 0x4C:                                      /* switch 1 */
        case 0x4D:                                      /* switch 1 */
        case 0x4E:                                      /* switch 1 */
        case 0x4F:                                      /* switch 1 */
        case 0x50:                                      /* switch 1 */
        case 0x51:                                      /* switch 1 */
        case 0x52:                                      /* switch 1 */
        case 0x53:                                      /* switch 1 */
        case 0x54:                                      /* switch 1 */
        case 0x55:                                      /* switch 1 */
        case 0x56:                                      /* switch 1 */
        case 0x57:                                      /* switch 1 */
        case 0x58:                                      /* switch 1 */
        case 0x59:                                      /* switch 1 */
            SET_MAP_POSITION(0.01477f, 0.019658f);
            return;
        case 0x3B:                                      /* switch 1 */
            SET_MAP_POSITION(0.014716f, 0.019583f);
            return;
        case 0x29:                                      /* switch 1 */
            if (jms->pos.y > -950.0f || ((jms->pos.z > -100000.0f) && jms->pos.y > -1200.0f)) {
                *px = 879.80005f + (0.013396f * jms->pos.x);
                *py = -1988.8f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y > -2950.0f) || ((jms->pos.z > -100000.0f) && (jms->pos.y > -3200.0f))) {
                *px = 916.2002f + (0.013396f * jms->pos.x);
                *py = -1847.7001f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y > -4950.0f) || ((jms->pos.z > -100000.0f) && (jms->pos.y > -5200.0f))) {
                *px = 916.40015f + (0.013396f * jms->pos.x);
                *py = -2086.5996f - (0.019375f * jms->pos.z);
                return;
            }
            *px = 631.7003f + (0.013396f * jms->pos.x);
            *py = -1956.7996f - (0.019375f * jms->pos.z);
            return;
        case 0x2A:                                      /* switch 1 */
            if (GET_GAME_FLAG(GAME_FLAG_19)) {
                *px = 1421.101f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 531.00037f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_18)) {
                *px = 1421.101f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 289.90015f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_17)) {
                *px = 1385.2999f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 426.99988f;
                return;
            }
            break;
        case 0x46:                                      /* switch 1 */
            if (GET_GAME_FLAG(GAME_FLAG_19)) {
                *px = 240.9f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 6029.8965f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_18)) {
                *px = 238.69986f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 5789.196f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_17)) {
                *px = 203.69986f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 5931.196f;
                return;
            }
            break;
        case 0x48:                                      /* switch 1 */
            if ((jms->pos.y >= 1700.0f)) {
                *px = 0.0f;
                *py = -1000.0f;
                return;
            }
            if ((jms->pos.y > -1000.0f) || ((jms->pos.y < -1001.0f) && (jms->pos.z > -99992.0f) && (jms->pos.y >= -1000.0f))) {
                *px = 1404.0f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 4336.0f;
                return;
            }
            if ((jms->pos.y > -3000.0f) || ((jms->pos.y < -3001.0f) && (jms->pos.z > -100009.0f) && (jms->pos.y >= -3000.0f))) {
                *px = 1438.0f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 4191.0f;
                return;
            }
            *px = 1438.0f + (0.01477f * sh2jms.player->pos.x);
            *py = 6.0f + ((0.019658f * -sh2jms.player->pos.z) - 4432.0f);
            return;
        case 0x47:                        
            if ((jms->pos.y >= 1001.0f) || ((jms->pos.y >= 1000.0f) && (jms->pos.z > -220067.0f))) {
                *px = 878.0f + (0.013396f * jms->pos.x);
                *py = -31.899994f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y >= -1000.0f) || ((jms->pos.z > -219978.0f)) && (jms->pos.y > -1001.0f)) {
                *px = 878.80005f + (0.013396f * jms->pos.x);
                *py = -211.9f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y >= -2998.0f) || ((jms->pos.z > -220003.0f) && (jms->pos.y > -3000.0f))) {
                *px = 915.0f + (0.013396f * jms->pos.x);
                *py = -73.899994f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y > -5000.0f) || ((jms->pos.z > -220011.0f) && (jms->pos.y >= -5000.0f))) {
                *px = 915.0f + (0.013396f * jms->pos.x);
                *py = -313.9f - (0.019375f * jms->pos.z);
                return;
            }
            *px = 630.0f + (0.013396f * jms->pos.x);
            *py = -183.9f - (0.019375f * jms->pos.z);
            break;
        }
}

#undef SET_MAP_POSITION
