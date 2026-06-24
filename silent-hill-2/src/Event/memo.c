#include "Event/memo.h"
#include "Event/event.h"
#include "Event/picture.h"
#include "Effect/screen_effect.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/playing_info.h"
#include "gamemain.h"
#include "Multi_thr/filesys/fcread.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "Font/font.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/data_load.h"
#include "Multi_thr/filesys/fileserv.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2dt.h"

extern /* static */ struct Memo_Data data[45];  // size: 0x2D0, address: 0x34CED0

static void MemoInit(void);
static void MemoSelect(void);
static void MemoDisplay(void);
static void MemoEnd(void);
static void MemoPictureLoad(union fsFileIndex* file0, union fsFileIndex* file1);
static void MemoPictureBaseDraw(int rgb /* r16 */);
static void MemoSelectBarDraw(int msg /* r2 */, int y /* r16 */);
static void MemoPictureLayerDraw(int rgb); // apperently this takes an argument
static void MemoPictureLayerDrawSafeLock(void);
static void MemoPictureLayerDrawGuruguru(void);
static void MemoPictureLayerDrawAngelRing(void);
static void MemoPictureLayerDrawHair(void);
static void MemoPictureLayerDrawTablet(void);
static void MemoMessageWallet(void);

void MemoMain(void) {
    switch (Sh2sys.step[3]) {
        default:
        case 0: MemoInit(); break;            
        case 1: MemoSelect(); break;           
        case 2: MemoDisplay(); break;
        case 3: MemoEnd(); break;                       
    }
}

int MemoCommandCheck(void) {
    int i; // r5
    for (i = 0; i < 45; i++) 
        if (GET_FLAG(game_flag.flag, data[i].flag)) return 1;
    
    return 0;
}

static void MemoInit(void) { // not line matched (need to add macros/inlines)
    int i; // r5
    
    switch (Sh2sys.step[4]) { 
        case 0:
            select = playing.memo_select;
            list_point = select;
            for (i = 0; select >= i; i++) {
                if (!GET_FLAG(game_flag.flag, data[i].flag)) {
                    list_point--;
                }
            }
            if (list_point < 0) {
                list_point = 0;
            }
            disp_point = 0;
            DataLoadMessage(3);
            FcRead(data_pic_etc_p_memo_tex, (void*)get_gp_data_buf_addr());
            Sh2sys.step[4]++;
            Sh2sys.step[5] = 0;
            Sh2sys.step[6] = 0;
            Sh2sys.step[7] = 0;
            /* fallthrough */
        case 1:
            if (fsSync(1, -1) >= 0) {
                Sh2sys.step[4]++;
                Sh2sys.step[5] = 0;
                Sh2sys.step[6] = 0;
                Sh2sys.step[7] = 0;
            case 2:
                if (ScreenEffectFadeCheck() != 0) {
                    Sh2sys.step[4]++;
                    Sh2sys.step[5] = 0;
                    Sh2sys.step[6] = 0;
                    Sh2sys.step[7] = 0;
                case 3:
                    ScreenEffectFadeStart(4, 0.0f);
                    Sh2sys.step[3] = 1;
                    Sh2sys.step[4] = 0;
                    Sh2sys.step[5] = 0;
                    Sh2sys.step[6] = 0;
                    Sh2sys.step[7] = 0;
                }
            }
            return;
        }
}

static void MemoSelect(void) { // not line matched
    short list[45][2]; // r29+0x60
    int list_number; // r16
    int work; // r17
    int alpha; // r2
    int i; // r18
    int j; // r19

    list_number = 0;
    for (i = 0; i < 45; i++) {
        if (GET_FLAG(game_flag.flag, data[i].flag)) {
            list[list_number][0] = i;
            list[list_number][1] = data[i].msg_label;
            list_number++;
        }
    }
    if (shPadTrigger(0, key_config.enter)) {
        Sh2sys.step[3] = 2;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
    } else if (shPadTrigger(0, key_config.cancel)) {
        Sh2sys.step[3] = 3;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
    } else if (shPadRepeat(0, PAD_KEY_DPAD_UP)) {
        list_point--;
        if (list_point < 0) {
            list_point = list_number - 1;
        }
        disp_point++;
        if (3 < disp_point) {
            disp_point = 3;
        }
    } else if (shPadRepeat(0, PAD_KEY_DPAD_DOWN)) {
        list_point++;
        if (list_point >= list_number) {
            list_point = 0;
        }
        disp_point--;
        if (disp_point < -3) {
            disp_point = -3;
        }
    }
    select = list[list_point][0];
    MemoPictureBaseDraw(0x60);
    fontClear();
    if (list_number < 12) {
        for (i = 0; i < list_number; i++) {
            work = 0x100 - (list_number << 4) + (i << 5);
            fontPrintStrNum(msg_buffer, list[i][1], 0x100, work);
            if (i == list_point) {
                MemoSelectBarDraw(list[i][1], work);
            }
        }
    } else {
        for (i = 0; i < 13; i++) {
            j = list_point + disp_point - 6 + i;
            if (j < 0) {
                j += list_number;
            }
            if (j >= list_number) {
                j -= list_number;
            }
            work = (i << 5) + 0x30;
            switch (i) {
                default:
                    alpha = 0x80;
                    break;
                
                case 2:
                case 10:
                    alpha = 0x40;
                    break;
                
                case 1:
                case 11:
                    alpha = 0x20;
                    break;
                
                case 0:
                case 12:
                    alpha = 0x10;
                    break;

            }
            fontSetAlpha(alpha);
            fontPrintStrNum(msg_buffer, list[j][1], 0x100, work);
            if (j == list_point) {
                MemoSelectBarDraw(list[j][1], work);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/memo", MemoDisplay);

static void MemoEnd(void) { // not line matched  (need to add macros/inlines)
    playing.memo_select = select;
    ScreenEffectFadeStart(1, 0.0f);
    Sh2sys.step[2] = 6;
    Sh2sys.step[3] = 0;
    Sh2sys.step[4] = 0;
    Sh2sys.step[5] = 0;
    Sh2sys.step[6] = 0;
    Sh2sys.step[7] = 0;
}

static void MemoPictureLoad(union fsFileIndex* file0, union fsFileIndex* file1) { // line matched
    ASSERT_ON_LINE(file0 || !file1, 475);

    switch (select) {
        
        case 17:
            if (!GET_GAME_FLAG(GAME_FLAG_607)) file0 = file1 = NULL;            
            break;
        
        case 31:
            if (!GET_GAME_FLAG(GAME_FLAG_171)) file0 = file1 = NULL;            
            break;
        
        case 32:    
            if (!GET_GAME_FLAG(GAME_FLAG_227) && !GET_GAME_FLAG(GAME_FLAG_228))
                file0 = file1 = NULL;            
            break;
    }
    
    if (file0 != NULL) {
        FcRead(file0, (void*)get_gp_data_buf_addr());
        layer_adr = (char*)(get_gp_data_buf_addr() + ((FcGetFileSize(file0) + 0x7FF) & ~0x7FF));
    }
    if (file1 != NULL) {
        FcRead(file1, layer_adr);
    }
}

static void MemoPictureBaseDraw(int rgb /* r16 */) { // not line matched (need to add macros/inlines)
    struct PicDraw_Data pic; // r29+0x20
    
    sh2gfw_Black_Clear();
    PictureLoadImage((struct sh2gfw_AREA_HEAD*)get_gp_data_buf_addr(), 0, -1, -1);
    
    shQzero(&pic, sizeof(struct PicDraw_Data));
    
    pic.ap = (struct sh2gfw_AREA_HEAD*) get_gp_data_buf_addr();
    pic.clut = pic.tex = -1;
    pic.status |= 1;
    pic.otp = 1;
    pic.b = pic.g = pic.r = rgb;
    pic.status |= 0x10;
    PictureDraw((struct PicDraw_Data*) &pic);
}

static void MemoSelectBarDraw(int msg /* r2 */, int y /* r16 */) { // not line matched (need to add macros/inlines)
    struct PicDraw_Data pic; // r29+0x30
    int wl[8]; // r29+0x80    
    int w; // r17

    fontGetMesWidth(wl, fontGetMesAdr(msg_buffer, msg & 0xFFFF));
    w = (wl[0] >> 1) + 4;

    
    shQzero(&pic, sizeof(struct PicDraw_Data));
    pic.otp = 8;
    
    pic.x0 = w * -0x10;
    pic.y0 = (y - 0x100) * 0x10;
    pic.x1 = w * 0x10;
    pic.y1 = (y - 0xE0) * 0x10;
    pic.status |= 2;
    pic.r = 0x20;
    pic.g = 0x60;
    pic.b = 0x20;
    pic.status |= 0x10;
    pic.a = 0x40;
    pic.alpha_a = 0;
    pic.alpha_b = 1;
    pic.alpha_c = 0;
    pic.alpha_d = 1;
    pic.alpha_fix = 0x80;
    pic.status |= 0x20;
    PictureDraw(&pic);
}

static void MemoPictureLayerDraw(int rgb) { // apperently this takes an argument
    switch (select) {
        case 17:
            if (GET_GAME_FLAG(GAME_FLAG_607)) 
                MemoPictureLayerDrawSafeLock();
            break;
        case 30: MemoPictureLayerDrawGuruguru(); break;
        case 32:
            if (GET_GAME_FLAG(GAME_FLAG_227) || GET_GAME_FLAG(GAME_FLAG_228))
                
                MemoPictureLayerDrawAngelRing();            
            break;
        case 31: MemoPictureLayerDrawHair(); break;
        case 36: MemoPictureLayerDrawTablet(); break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/memo", MemoPictureLayerDrawSafeLock);

INCLUDE_ASM("asm/nonmatchings/Event/memo", MemoPictureLayerDrawGuruguru);

static void MemoPictureLayerDrawAngelRing(void) { // not line matched (need to add macros/inlines)
    struct PicDraw_Data pic; // r29+0x20
    
    PictureLoadImage((struct sh2gfw_AREA_HEAD*) layer_adr, 2, -1, -1);
    shQzero(&pic, sizeof(struct PicDraw_Data));
    pic.ap = (struct sh2gfw_AREA_HEAD*) layer_adr;
    pic.tex = -1;
    pic.clut = -1;
    pic.status |= 1;
    if (GET_GAME_FLAG(GAME_FLAG_227)) {
        pic.x0 = 0x939;
        pic.y0 = 0x635;
        pic.x1 = 0xA39;
        pic.y1 = 0x735;
        pic.status |= 2;
        pic.us0 = 0;
        pic.vt0 = 0;
        pic.us1 = 0xF0;
        pic.vt1 = 0xF0;
        pic.status |= 4;
        pic.otp = 3;
        pic.a = 0x80;
        pic.alpha_a = 0;
        pic.alpha_b = 1;
        pic.alpha_c = 0;
        pic.alpha_d = 1;
        pic.alpha_fix = 0x80;
        pic.status |= 0x20;
        PictureDraw((struct PicDraw_Data*) &pic);
    }
    if (GET_GAME_FLAG(GAME_FLAG_228)) {
        pic.x0 = 0x472;
        pic.y0 = 6;
        pic.x1 = 0x572;
        pic.y1 = 0x106;
        pic.status |= 2;
        pic.us0 = 0x100;
        pic.vt0 = 0;
        pic.us1 = 0x1F0;
        pic.vt1 = 0xF0;
        pic.status |= 4;
        pic.otp = 3;
        pic.a = 0x80;
        pic.alpha_a = 0;
        pic.alpha_b = 1;
        pic.alpha_c = 0;
        pic.alpha_d = 1;
        pic.alpha_fix = 0x80;
        pic.status |= 0x20;
        PictureDraw((struct PicDraw_Data*) &pic);
    }
}

static void MemoPictureLayerDrawHair(void) { // not line matched (need to add macros/inlines)
    struct PicDraw_Data pic; // r29+0x10
    PictureLoadImage((struct sh2gfw_AREA_HEAD* ) layer_adr, 2, -1, -1);
    shQzero(&pic, sizeof(struct PicDraw_Data));
    pic.ap = (struct sh2gfw_AREA_HEAD*) layer_adr;
    pic.tex = -1;
    pic.clut = -1;
    pic.status |= 1;
    pic.otp = 3;
    pic.a = 0x80;
    pic.alpha_a = 0;
    pic.alpha_b = 1;
    pic.alpha_c = 0;
    pic.alpha_d = 1;
    pic.alpha_fix = 0x80;
    pic.status |= 0x20;
    pic.x0 = -0x470;
    pic.y0 = -0x340;     
    pic.x1 = 0xB90;       
    pic.y1 = 0xC0;        
    pic.status |= 2;
    PictureDraw(&pic);
}

INCLUDE_ASM("asm/nonmatchings/Event/memo", MemoPictureLayerDrawTablet);

INCLUDE_ASM("asm/nonmatchings/Event/memo", MemoMessageWallet);
