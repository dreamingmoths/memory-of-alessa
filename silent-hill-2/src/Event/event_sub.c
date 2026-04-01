#include "event_sub.h"

int EvSubMessage(int msg /* r2 */) {
    switch (ev_s_step) { 
        case 0:
            fontMessageNum(msg_buffer, msg);
            ev_s_step += 1;
            break;
        case 1:
            if ((fontGetStatus() != -1) || (ev_cancel != 0)) {
                if (ev_cancel != 0) {
                    ev_prog_flag_set = 0;
                }
                fontClear();
                ev_s_step += 1;
            }
            break;
        case 2:
            return 1;           
    }
    return 0;
}

int EvSubQuestion(int msg)  {
    switch (ev_s_step) {
        case 0:
            fontMessageNum(msg_buffer, msg);
            ev_s_step += 1;
            break;    
        case 1:
            if (fontGetStatus() != -1) {
                fontClear();
                ev_s_step += 1;
            }
            break;
        case 2:
            return 1;
    }
    return 0;
}

signed int EvSubItemUse0(int kind /* r19 */, int message /* r20 */, int se /* r18 */, int stereo /* r17 */, float * pos /* r16 */, int xxx /* r2 */) {

    switch (ev_s_step) {
        case 0:
            if (xxx != 0) {
                SCNowPlayableEventSwitch(sh2jms.player, 1);
            }
            ItemUse(kind);
            fontMessageNum(msg_buffer, message);
            if ((se != 0) && (ItemUseSeTiming(kind, 0) != 0)) {
                if (pos != 0) {

                    SeCallPos(se, 1.0f, pos, 0);
                } else {
                    SeCall(se, 1.0f, stereo);
                }
            }
            ev_s_step += 1;
            break;
        case 1:
            if (fontGetStatus() == -2) {
                fontClear();
                if ((se != 0) && (ItemUseSeTiming(kind, 1) != 0)) {
                    if (pos != 0) {
                        SeCallPos(se, 1.0f, pos, 0);
                    } else {
                        SeCall(se, 1.0f, stereo);
                    }
                }
                ev_s_step += 1;
            }
            break;
        case 2:
            if (xxx != 0) {
                SCNowPlayableEventSwitch(sh2jms.player, 0);
            }
            return 1;
    }
    return 0;
}

signed int ItemUseSeTiming(int kind, int boa) {
    switch (kind) {
        case 0x38:
        case 0x39:
        case 0x3A:
            if (boa == 0) {
                return 0;
            }
            break;
        default:
            if (boa != 0) {
                return 0;
            }
            break;
    }
    return 1;
}

int EvSubItemGet(int kind /* r16 */, int message /* r2 */)  {
    switch (ev_s_step) {
        case 0:
            fontMessageNum(msg_buffer, message);
            ev_s_step += 1;
            break;
        case 1:
            if (fontGetStatus() == -2) {
                ItemGet(kind);
                shCharacter_Manage_Delete(0, item_to_chara[kind], 0);
                fontClear();
                ev_s_step += 1;
            }
            break;
        case 2:
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubItemGetAndAnim);

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubFileLoadAndFadeOut);

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubPictureDisplayAndFadeIn);

int EvSubPictureDisplayOnly() {

    struct PicDraw_Data pic;
    
    PictureLoadImage((struct sh2gfw_AREA_HEAD *) get_gp_data_buf_addr(), 0, -1, -1);
    shQzero(&pic, 0x44);
    pic.ap = (struct sh2gfw_AREA_HEAD *) get_gp_data_buf_addr();
    pic.tex = -1;
    pic.clut = -1;
    pic.status |= 1;
    pic.otp = 1;
    PictureDraw(&pic);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubPictureDisplayAndFadeOut);

signed int EvSubPictureDisplay(union fsFileIndex * file /* r16 */, int msg /* r17 */) {
    switch (ev_s_step) {
        case 0:
            FcRead(file, get_gp_data_buf_addr());
            ScreenEffectFadeStart(1, 0);
            EvSubPictureInit();
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            ev_s_step = 4;
            break;
    
        case 4:
            if ((fsSync(1, -1) >= 0) && (ScreenEffectFadeCheck() != 0)) {
                ScreenEffectFadeStart(4, 0);
                ev_s_step = 7;
            }
            break;
        case 7:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck() != 0) {
                ev_s_step = 2;
            }
            break;
        case 2:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, key_config.cancel) != 0)) {
                fontMessageNum(msg_buffer, msg);
                ev_s_step = 3;
            }
            break;
        case 3:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (fontGetStatus() == -2) {
                fontClear();
                ScreenEffectFadeStart(2, 0);
                ev_s_step = 6;
            }
            break;
        case 6:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck() != 0) {
                ev_s_step = 0xB;
            }
            break;
        case 11:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            ScreenEffectFadeStart(4, 0);
            return 1;
        }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubMapGet);

void EvSubPictureLayer(int x0 /* r20 */, int y0 /* r19 */, int x1 /* r18 */, int y1 /* r17 */, int alpha /* r16 */) {

    struct PicDraw_Data pic;
    
    PictureLoadImage((struct sh2gfw_AREA_HEAD *)layer_adr, 2, -1, -1);
    shQzero(&pic, 0x44);
    pic.ap = (struct sh2gfw_AREA_HEAD *) layer_adr;
    pic.tex = -1;
    pic.clut = -1;
    pic.status |= 1;
    pic.otp = 3;
    pic.x0 = x0;
    pic.y0 = y0;
    pic.x1 = x1;
    pic.y1 = y1;
    pic.status |= 2;
    pic.a = alpha;
    pic.alpha_a = 0;
    pic.alpha_b = 1;
    pic.alpha_c = 0;
    pic.alpha_d = 1;
    pic.alpha_fix = 0x80;
    pic.status |= 0x20;
    PictureDraw(&pic);
}

void EvSubPictureFilter(void) {
    ev_filter_on = 1;
}

void EvSubPictureInit(void) {
    ev_filter_on = 0;
    ev_filter = 0.0f;
}

void EvSubPictureStart(void) {
    sh2gfw_Black_Clear();
    Sh2sys.main_status |=  1;
}

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubPictureEnd);

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubPictureCursor);

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvDispControlModelEntry);

void EvDispControlModelExec(int * list /* r16 */) {

    switch (BgIsOut(0)) {
        default:
            sh2gfw_Init_DispOnOffObj();
            for (; *list != 0; list = list + 2) {
                sh2gfw_FastSet_DispOnOffObj(*list,list[1]);
            }
            break;
        case 0:
            for (; *list != 0; list = list + 2) {
                sh2gfw_Set_DispOnOffObj(*list,list[1]);
            }
    }
  return;
}

INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubMovieReady);

int EvSubMovieStart(int demo /* r16 */) {

    int movie = MovieWaitReady();
    
    if ((movie != 0) && (demo != 0) && ((shGs_AllEnv.loop3 % 3U) == 1)) {
        sh2gfw_Set_PauseRetain();
        Sh2sys.step[2] = 0xE;
        Sh2sys.step[3] = 0;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
        return 1;
    }
    return 0;
}

void EvSubMovieEnd(void) {
    Sh2sys.soft_reset = 1;
    sh2gfw_Reset_FilterCommand();
}
