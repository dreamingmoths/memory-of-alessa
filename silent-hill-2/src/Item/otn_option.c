#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/data_load.h"

#include "sce/libgraph.h"
#include "gs.h"

#include "Fog/spack.h"

#include "Font/font.h"
#include "Font/dic.h"

#include "sound/sh_sound.h"
#include "Item/otn_option.h"

static struct /* @anon2 */ {
    // total size: 0x7C
    u_char option_step; // offset 0x0, size 0x1
    u_char extra_mode; // offset 0x1, size 0x1
    short cursol; // offset 0x2, size 0x2
    float cursol_pos; // offset 0x4, size 0x4
    short fade; // offset 0x8, size 0x2
    u_char fade_flag; // offset 0xA, size 0x1
    float timer; // offset 0xC, size 0x4
    short hoge; // offset 0x10, size 0x2
    u_int ana_x; // offset 0x14, size 0x4
    u_int ana_y; // offset 0x18, size 0x4
    struct Pad_KeyConfig key_config_set; // offset 0x1C, size 0x60
} t; // size: 0x7C, address: 0x11B6A70

extern u_short msg_buffer[32768]; // size: 0x10000, address: 0x11B7040

extern char key_cur; // size: 0x1, address: 0x11B6A60
extern char key_cur2; // size: 0x1, address: 0x11B6A58
extern u_char key_rem[20]; // size: 0x14, address: 0x11B6A40

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", option_main);

void option_mainmain(void) {
    if (!t.fade_flag) {
        fade_in();
    }
    look_board();
    look_cur();
    if (!t.extra_mode) {
        if ((shPadTrigger(0, key_config.cancel)) && !t.fade) {
            t.fade_flag = 1;
        }
        if ((shPadTrigger(0, key_config.enter)) && !t.fade) {
            if (!t.cursol) {
                t.fade_flag = 2;
            }
            if (t.cursol == 1) {
                t.fade_flag = 3;
            }
            if (t.cursol == 2) {
                t.fade_flag = 4;
            }
            dword_struct_copy(&t.key_config_set, &key_config, sizeof(Pad_KeyConfig));
        }
        if (((shPadTrigger(0, PAD_KEY_L1)) || (shPadTrigger(0, PAD_KEY_R1))) && !t.fade) {
            t.fade_flag = 6;
        }
        switch (t.cursol) {
            case 3:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0x6E, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.control_type = 1 - playing.control_type;
                    }
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        SeCall(0x2710, 1.0f, 0);
                    }
                }
                break;
            case 4:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0x66, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if (((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) && (playing.vibration == 3)) {
                        playing.vibration = 0;
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.vibration++;
                    } else if (((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) && (!(playing.vibration))) {
                        playing.vibration = 3;
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) {
                        playing.vibration--;
                    }
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        SeCall(0x2710, 1.0f, 0);
                    }
                }
                break;
            case 5:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0x3A, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.auto_load = 1 - playing.auto_load;
                    }
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        SeCall(0x2710, 1.0f, 0);
                    }
                }
                break;
            case 6:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0x6E, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if (((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) && (playing.language == 1)) {
                        playing.language = 0;
                        DataLoadMessage(SH2_MES_FILE_OPTION);
                        fsSync(0, -1);
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.language++;
                        DataLoadMessage(SH2_MES_FILE_OPTION);
                        fsSync(0, -1);
                    } else if (((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) && (!(playing.language))) {
                        playing.language = 1;
                        DataLoadMessage(SH2_MES_FILE_OPTION);
                        fsSync(0, -1);
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) {
                        playing.language--;
                        DataLoadMessage(SH2_MES_FILE_OPTION);
                        fsSync(0, -1);
                    }
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        SeCall(0x2710, 1.0f, 0);
                    }
                }
                break;
            case 7:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0x3A, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.subtitles = 1 - playing.subtitles;
                    }
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        SeCall(0x2710, 1.0f, 0);
                    }
                }
                break;
            case 8:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0xDC, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if (((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) && (playing.sound == 2)) {
                        playing.sound = 0;
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.sound++;
                    } else if (((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) && (!(playing.sound))) {
                        playing.sound = 2;
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) {
                        playing.sound--;
                    }
                    if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        SeCall(0x2710, 1.0f, 0);
                    }
                }
                break;
            case 9:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0xC5, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if (((shPadRepeat(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && (!t.ana_x || ((t.ana_x > 0xf) && ((!(t.ana_x % 3))))))) && (playing.bgm_volume > 0)) {
                        playing.bgm_volume--;
                        SeMasterVolumeChange();
                        SeCall(0x4A49, 1.0f, 0);
                    }
                    if (((shPadRepeat(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && (!t.ana_x || ((t.ana_x > 0xf) && ((!(t.ana_x % 3))))))) && (playing.bgm_volume < 0xF)) {
                        playing.bgm_volume++;
                        SeMasterVolumeChange();
                        SeCall(0x4A49, 1.0f, 0);
                    }
                }
                break;
            case 10:
                allow_l(-5, (t.cursol * 0x1B) - 0x8C);
                allow_r(0xC5, (t.cursol * 0x1B) - 0x8C);
                if (!t.fade) {
                    if (((shPadRepeat(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && (!t.ana_x || ((t.ana_x > 0xf) && ((!(t.ana_x % 3))))))) && (playing.se_volume > 0)) {
                        playing.se_volume--;
                        SeMasterVolumeChange();
                        SeCall(0x4A49, 1.0f, 0);
                    }
                    if (((shPadRepeat(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && (!t.ana_x || ((t.ana_x > 0xf) && ((!(t.ana_x % 3))))))) && (playing.se_volume < 0xF)) {
                        playing.se_volume++;
                        SeMasterVolumeChange();
                        SeCall(0x4A49, 1.0f, 0);
                    }
                }
                break;
        }
        if (t.fade_flag == 1) {
            t.option_step = fade_out(6);
        }
        if (t.fade_flag == 2) {
            t.option_step = fade_out(3);
        }
        if (t.fade_flag == 3) {
            t.option_step = fade_out(5);
        }
        if (t.fade_flag == 4) {
            t.option_step = fade_out(4);
        }
        if (t.fade_flag == 6) {
            t.option_step = fade_out(2);
        }
        if ((ScreenEffectFadeCheck()) && (t.fade == 0xFF) && (t.option_step == 2)) {
            t.cursol = 0;
            t.extra_mode = 1;
        }
        look_bgm();
        look_se();
        return;
    }
    if (((shPadTrigger(0, key_config.cancel)) || (shPadTrigger(0, PAD_KEY_L1)) || (shPadTrigger(0, PAD_KEY_R1))) && !t.fade) {
        t.fade_flag = 1;
    }
    if (t.fade_flag == 1) {
        t.option_step = fade_out(2);
    }
    switch (t.cursol) {
        case 0:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x5C, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.weapon_control = 1 - playing.weapon_control;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
        case 1:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x65, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if (((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) && (playing.blood_color == 3)) {
                    playing.blood_color = 0;
                } else if ((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.blood_color++;
                } else if (((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) && (!(playing.blood_color))) {
                    playing.blood_color = 3;
                } else if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) {
                    playing.blood_color--;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
        case 2:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x65, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.view_control = 1 - playing.view_control;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
        case 3:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x65, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.retreat_turn = 1 - playing.retreat_turn;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
        case 4:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x65, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.walk_run_control = 1 - playing.walk_run_control;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
        case 5:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x78, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.view_mode = 1 - playing.view_mode;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
        case 6:
            allow_l(-5, (t.cursol * 0x1B) - 0x8C);
            allow_r(0x3D, (t.cursol * 0x1B) - 0x8C);
            if (!t.fade) {
                if (((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) && (playing.bullet_adjust == 6)) {
                    playing.bullet_adjust = 1;
                } else if ((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    playing.bullet_adjust++;
                } else if (((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) && (playing.bullet_adjust == 1)) {
                    playing.bullet_adjust = 6;
                } else if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) {
                    playing.bullet_adjust--;
                }
                if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || (shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                    SeCall(0x2710, 1.0f, 0);
                }
            }
            break;
    }
    if ((ScreenEffectFadeCheck()) && (t.fade == 0xFF) && (t.option_step == 2)) {
        t.cursol = 0;
        t.extra_mode = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", bright_main);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", print_config);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_check);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_type1);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_type2);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_type3);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_conf);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_conf_check);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_color);

void config_main(void) {
    int i;         // r29+36
    int j;         // r16
    int k;         // r29+40
    s_char buf[2]; // r29+44

    if (t.fade_flag == 0)
        fade_in();

    if (((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel))) && (t.fade == 0) && (key_cur == 0) && (key_cur2 == 0))
        t.fade_flag = 1;

    if (t.fade_flag == 1) {
        key_config        = t.key_config_set;
        key_config.attack = key_config.action;
        shPadSetGameKeyAssign();
        t.option_step = fade_out(2);
    }

    KeyConfigPitureStart();
    key_color(0);
    if ((key_cur2 == 0) && (key_cur == 0))
        fontSetColorDirect(128, 128, 128, 255);
    else
        fontSetColorDirect(32, 32, 32, 255);

    fontPrintStrNum(msg_buffer, 8U, 30, 60);
    if ((key_cur2 == 1) && (key_cur == 0))
        fontSetColorDirect(128, 128, 128, 255);
    else
        fontSetColorDirect(32, 32, 32, 255);

    sprintf(buf, "1");
    fontSetMes(0, dicSetStr(buf));
    fontPrintStrNum(msg_buffer, 9, 140, 60);
    if ((key_cur2 == 2) && (key_cur == 0))
        fontSetColorDirect(128, 128, 128, 255);
    else
        fontSetColorDirect(32, 32, 32, 255);

    sprintf(buf, "2");
    fontSetMes(0, dicSetStr(buf));
    fontPrintStrNum(msg_buffer, 9, 230, 60);
    if ((key_cur2 == 3) && (key_cur == 0))
        fontSetColorDirect(128, 128, 128, 255);
    else
        fontSetColorDirect(32, 32, 32, 255);

    sprintf(buf, "3");
    fontSetMes(0, dicSetStr(buf));
    fontPrintStrNum(msg_buffer, 9, 320, 60);
    if ((key_cur2 == 4) && (key_cur == 0))
        fontSetColorDirect(128, 128, 128, 255);
    else
        fontSetColorDirect(32, 32, 32, 255);

    fontPrintStrNum(msg_buffer, 24, 410, 60);
    key_color(1);
    fontPrintStrNum(msg_buffer, 10, 56, 102);
    key_color(2);
    fontPrintStrNum(msg_buffer, 11, 40, 129);
    key_color(3);
    fontPrintStrNum(msg_buffer, 12, 77, 156);
    key_color(4);
    fontPrintStrNum(msg_buffer, 19, 53, 183);
    key_color(5);
    fontPrintStrNum(msg_buffer, 18, 53, 210);
    key_color(6);
    fontPrintStrNum(msg_buffer, 13, 40, 237);
    key_color(7);
    fontPrintStrNum(msg_buffer, 16, 77, 264);
    key_color(8);
    fontPrintStrNum(msg_buffer, 15, 56, 291);
    key_color(9);
    fontPrintStrNum(msg_buffer, 21, 68, 318);
    key_color(10);
    fontPrintStrNum(msg_buffer, 17, 66, 345);
    key_color(11);
    fontPrintStrNum(msg_buffer, 14, 78, 372);
    key_color(12);
    fontPrintStrNum(msg_buffer, 22, 73, 399);
    key_color(13);
    fontPrintStrNum(msg_buffer, 20, 53, 426);

    for (i = 0; i < 14; i++) {
        k = 140;
        for (j = 0; j < 20; j++) {
            if (i == 1 && t.key_config_set.enter & (1 << j))
                print_config(j, &k, i);
            if (i == 2 && t.key_config_set.cancel & (1 << j))
                print_config(j, &k, i);
            if (i == 3 && t.key_config_set.skip & (1 << j))
                print_config(j, &k, i);
            if (i == 4 && t.key_config_set.right_move & (1 << j))
                print_config(j, &k, i);
            if (i == 5 && t.key_config_set.left_move & (1 << j))
                print_config(j, &k, i);
            if (i == 6 && t.key_config_set.action & (1 << j))
                print_config(j, &k, i);
            if (i == 7 && t.key_config_set.dash & (1 << j))
                print_config(j, &k, i);
            if (i == 8 && t.key_config_set.light & (1 << j))
                print_config(j, &k, i);
            if (i == 9 && t.key_config_set.item & (1 << j))
                print_config(j, &k, i);
            if (i == 10 && t.key_config_set.search_view & (1 << j))
                print_config(j, &k, i);
            if (i == 11 && t.key_config_set.ready & (1 << j))
                print_config(j, &k, i);
            if (i == 12 && t.key_config_set.map & (1 << j))
                print_config(j, &k, i);
            if (i == 13 && t.key_config_set.pause & (1 << j))
                print_config(j, &k, i);
            key_rem[j] = i;
        }
    }

    if ((key_cur == 0) && (key_cur2 == 1) && (shPadTrigger(0, key_config.enter)))
        key_type1();

    if ((key_cur == 0) && (key_cur2 == 2) && (shPadTrigger(0, key_config.enter)))
        key_type2();

    if ((key_cur == 0) && (key_cur2 == 3) && (shPadTrigger(0, key_config.enter)))
        key_type3();

    if ((key_cur == 0) && (key_cur2 == 4) && (shPadTrigger(0, key_config.enter)))
        t.key_config_set = key_config;

    if ((key_cur == 0) && (shPadTrigger(0, key_config.cancel)))
        key_cur2 = 0;

    switch (key_cur) {
        case 1:
            i = t.key_config_set.enter;
            if (i ^ key_check())
                i ^= key_check();
            key_conf(&i, &t.key_config_set.cancel, 1);
            if (i)
                t.key_config_set.enter = i;
            break;

        case 2:
            i = t.key_config_set.cancel;
            if (i ^ key_check())
                i ^= key_check();
            key_conf(&i, &t.key_config_set.enter, 1);
            if (i)
                t.key_config_set.cancel = i;
            break;

        case 3:
            t.key_config_set.skip ^= key_check();
            break;

        case 4:
            i = t.key_config_set.right_move;
            i ^= key_check();
            key_conf_check(4, &i);
            t.key_config_set.right_move = i;
            break;

        case 5:
            i = t.key_config_set.left_move;
            i ^= key_check();
            key_conf_check(5, &i);
            t.key_config_set.left_move = i;
            break;

        case 6:
            i = t.key_config_set.action;
            if (i ^ key_check())
                i ^= key_check();
            key_conf_check(6, &i);
            if (i)
                t.key_config_set.action = i;
            break;

        case 7:
            i = t.key_config_set.dash;
            i ^= key_check();
            key_conf_check(7, &i);
            t.key_config_set.dash = i;
            break;

        case 8:
            i = t.key_config_set.light;
            i ^= key_check();
            key_conf_check(8, &i);
            t.key_config_set.light = i;
            break;

        case 9:
            i = t.key_config_set.item;
            if (i ^ key_check())
                i ^= key_check();
            key_conf_check(9, &i);
            if (i)
                t.key_config_set.item = i;
            break;

        case 10:
            i = t.key_config_set.search_view;
            i ^= key_check();
            key_conf_check(10, &i);
            t.key_config_set.search_view = i;
            break;

        case 11:
            i = t.key_config_set.ready;
            if (i ^ key_check())
                i ^= key_check();
            key_conf_check(11, &i);
            if (i)
                t.key_config_set.ready = i;
            break;

        case 12:
            i = t.key_config_set.map;
            i ^= key_check();
            key_conf_check(12, &i);
            t.key_config_set.map = i;
            break;

        case 13:
            i = t.key_config_set.pause;
            i ^= key_check();
            key_conf_check(13, &i);
            t.key_config_set.pause = i;
            break;
    }

    if (ScreenEffectFadeCheck()) {
        if ((shPadRepeat(0, PAD_KEY_DPAD_DOWN)) || ((shPadPress(0, PAD_KEY_7) > 192) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0)))))
            key_cur++;

        if ((shPadRepeat(0, PAD_KEY_DPAD_UP)) || ((shPadPress(0, PAD_KEY_7) < 64) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0)))))
            key_cur--;

        if ((shPadRepeat(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, PAD_KEY_6) > 192) && ((t.ana_x == 0) || ((t.ana_x > 15) && ((t.ana_x % 3) == 0)))))
            key_cur2++;

        if ((shPadRepeat(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, PAD_KEY_6) < 64) && ((t.ana_x == 0) || ((t.ana_x > 15) && ((t.ana_x % 3) == 0)))))
            key_cur2--;

        if (key_cur > 13) key_cur = 0;
        if (key_cur < 0) key_cur = 13;
        if (key_cur2 > 4) key_cur2 = 0;
        if (key_cur2 < 0) key_cur2 = 4;
        if (key_cur) key_cur2 = 0;
    }
}

#line 899
void position_main(void) {
    int i, j, rgb, fade;    // r16
    if (t.fade_flag == 0) fade_in();
    if ((shPadTrigger(0, key_config.cancel)) && (t.fade == 0)) t.fade_flag = 1;
    if (t.fade_flag == 1) t.option_step = fade_out(2);
    
    if (t.fade == 0) {
    
        
        #line 909
        if ((shPadRepeat(0, PAD_KEY_DPAD_DOWN)) || ((shPadPress(0, PAD_KEY_7) > 192) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0))))) playing.screen_position_y += 3;
        if ((shPadRepeat(0, PAD_KEY_DPAD_UP)) || ((shPadPress(0, PAD_KEY_7) < 64) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0))))) playing.screen_position_y -= 3;
        if (playing.screen_position_x < -22) playing.screen_position_x = -22;
        if (playing.screen_position_x > 22) playing.screen_position_x = 22;
        if (playing.screen_position_y < -24) playing.screen_position_y = -24;
        if (playing.screen_position_y > 24) playing.screen_position_y = 24;
        
        
        shGs_SetDefaultDispArea();
        shGs_TrimDispArea(playing.screen_position_x / 4, playing.screen_position_y / 3);
    }
    
    if (((int) (t.timer) % 40) < 20) do { fade = 0; } while (0); // @hack?
    
    if ((t.hoge == 0) || (t.hoge == 255)) {
        if (t.fade_flag == 0)
            if (shPadTrigger(0, key_config.enter) && t.fade == 0) t.hoge += 32;
    } else
        t.hoge += 32;
    if (t.hoge == 256) t.hoge = 255;
    if (t.hoge == 511) t.hoge = 0;
    if (t.hoge < 256) rgb = t.hoge;
    else rgb = 511 - t.hoge;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65528, 0);
            spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
            spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
            (*spack.pos++) = SCE_GS_PRIM_SPRITE;
            (*spack.pos++) = SCE_GS_SET_RGBAQ(rgb, rgb, rgb, 128, 0);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 64 - 256), zs(j * 64 - 256), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 64 - 192), zs(j * 64 - 192), zs(0), 255);
            spkCloseGiftag();
        }
    }

    for (i = 0; i < 23; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65532, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_PRIM_SPRITE;
        if ((i % 10) == 1)
            (*spack.pos++) = SCE_GS_SET_RGBAQ(255, 64, 64, 128, 0);
        else
            (*spack.pos++) = SCE_GS_SET_RGBAQ(255 - rgb, 255 - rgb, 255 - rgb, 128, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 24 - 265), zs(-270), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 24 - 263), zs(270), zs(0), 255);
        spkCloseGiftag();
    }

    for (i = 0; i < 17; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65532, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_PRIM_SPRITE;
        if ((i % 6) == 2)
            (*spack.pos++) = SCE_GS_SET_RGBAQ(255, 64, 64, 128, 0);
        else
            (*spack.pos++) = SCE_GS_SET_RGBAQ(255 - rgb, 255 - rgb, 255 - rgb, 128, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(-270), zs(i * 32 - 257), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(270), zs(i * 32 - 255), zs(0), 255);
        spkCloseGiftag();
    }

    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_PRIM_SPRITE;
    (*spack.pos++) = SCE_GS_SET_RGBAQ(255, 255, 255, 128, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-122), zs(48), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(122), zs(112), zs(0), 255);
    spkCloseGiftag();
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_PRIM_SPRITE;
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 0, 0, 128, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-120), zs(50), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(120), zs(110), zs(0), 255);
    spkCloseGiftag();

    allow_u(0, -165);
    allow_d(0, 165);
    allow_l(-230, 0);
    allow_r(230, 0);
}

#line 1002
void look_bgm(void) {
    int i, j, abe;
    if (t.cursol == 9) abe = true;
    else abe = false;
    for (i = 0; i < playing.bgm_volume; i++) {
        // draw bars up to the background music volume
        // first two "shining" outer bars, then the inner part
        for (j = 0; j < 2; j++) {
            spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65532, 0);
            spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
            spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
            if (abe) (*spack.pos++) = SCE_GS_PRIM_TRISTRIP;
            else (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
            if (j == 0) (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 176, 176, 64, 0);
            else (*spack.pos++) = SCE_GS_SET_RGBAQ(64, 64, 64, 64, 0);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 24), zs(92), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(94), zs(0), 255);
            if (j == 0) (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 15), zs(92), zs(0), 255);
            else (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 24), zs(115), zs(0), 255);
            if (j == 0) (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(94), zs(0), 255);
            else (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(113), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 15), zs(115), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(113), zs(0), 255);
            spkCloseGiftag();
        }
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        if (abe) (*spack.pos++) = SCE_GS_PRIM_TRISTRIP;
        else (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(128, 128, 128, 64, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(94), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(94), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(113), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(113), zs(0), 255);
        spkCloseGiftag();
    }
    // drawing the reamining bars without the first loop to show they're off
    for (i = playing.bgm_volume; i < 15; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        if (abe) (*spack.pos++) = SCE_GS_PRIM_TRISTRIP;
        else (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(80, 80, 80, 64, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(94), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(94), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(113), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(113), zs(0), 255);
        spkCloseGiftag();
    }
}

#line 1061
void look_se(void) {
    int i, j, abe;
    if (t.cursol == 10) abe = true;
    else abe = false;
    for (i = 0; i < playing.se_volume; i++) {
        // draw bars up to the sound volume
        // first two "shining" outer bars, then the inner part
        for (j = 0; j < 2; j++) {
            spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65532, 0);
            spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
            spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
            if (abe) (*spack.pos++) = SCE_GS_PRIM_TRISTRIP;
            else (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
            if (j == 0) (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 176, 176, 64, 0);
            else (*spack.pos++) = SCE_GS_SET_RGBAQ(64, 64, 64, 64, 0);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 24), zs(119), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(121), zs(0), 255);
            if (j == 0) (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 15), zs(119), zs(0), 255);
            else (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 24), zs(142), zs(0), 255);
            if (j == 0) (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(121), zs(0), 255);
            else (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(140), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 15), zs(142), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(140), zs(0), 255);
            spkCloseGiftag();
        }
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        if (abe) (*spack.pos++) = SCE_GS_PRIM_TRISTRIP;
        else (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(128, 128, 128, 64, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(121), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(121), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(140), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(140), zs(0), 255);
        spkCloseGiftag();
    }
    // drawing the reamining bars without the first loop to show they're off
    for (i = playing.se_volume; i < 15; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        if (abe) (*spack.pos++) = SCE_GS_PRIM_TRISTRIP;
        else (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(80, 80, 80, 64, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(121), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(121), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 17), zs(140), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 11 + 22), zs(140), zs(0), 255);
        spkCloseGiftag();
    }
}

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", option_near);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", fade_in);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", fade_out);

void look_board(void) {
    spkOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
        SCE_GIF_PACKED_AD,
        0xFFFF0006,
        0
    );
    (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    (*spack.pos++) = SCE_GS_TEST_1;
    spkCloseOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8),
        GIF_REG(SCE_GS_PRIM,  0) |
        GIF_REG(SCE_GS_RGBAQ, 1) |
        GIF_REG(SCE_GS_XYZF2, 2) |
        GIF_REG(SCE_GS_XYZF2, 3) |
        GIF_REG(SCE_GS_XYZF2, 4) |
        GIF_REG(SCE_GS_XYZF2, 5) |
        GIF_REG(SCE_GS_XYZF2, 6) |
        GIF_REG(SCE_GS_XYZF2, 7)
    );
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, 0x20, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-210), zs(-165), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(210), zs(-165), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(-145), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(-145), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(155), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(155), zs(0), 255);
    spkCloseGiftag();
    spkOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
        SCE_GIF_PACKED_AD,
        0xFFFF0006,
        0
    );
    (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    (*spack.pos++) = SCE_GS_TEST_1;
    spkCloseOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 9),
        GIF_REG(SCE_GS_PRIM, 0)  |
        GIF_REG(SCE_GS_RGBAQ, 1) |
        GIF_REG(SCE_GS_XYZF2, 2) |
        GIF_REG(SCE_GS_XYZF2, 3) |
        GIF_REG(SCE_GS_XYZF2, 4) |
        GIF_REG(SCE_GS_XYZF2, 5) |
        GIF_REG(SCE_GS_XYZF2, 6) |
        GIF_REG(SCE_GS_XYZF2, 7) |
        GIF_REG(SCE_GS_XYZF2, 8)
    );
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x60, 0x60, 0xD0, 0x30, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-210), zs(-165), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(-145), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(155), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(155), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(-145), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(210), zs(-165), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-210), zs(-165), zs(0), 255);
    spkCloseGiftag();
    spkOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
        SCE_GIF_PACKED_AD,
        0xFFFF0006,
        0
    );
    (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    (*spack.pos++) = SCE_GS_TEST_1;
    spkCloseOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8),
        GIF_REG(SCE_GS_PRIM, 0)  |
        GIF_REG(SCE_GS_RGBAQ, 1) |
        GIF_REG(SCE_GS_XYZF2, 2) |
        GIF_REG(SCE_GS_XYZF2, 3) |
        GIF_REG(SCE_GS_XYZF2, 4) |
        GIF_REG(SCE_GS_XYZF2, 5) |
        GIF_REG(SCE_GS_XYZF2, 6) |
        GIF_REG(SCE_GS_XYZF2, 7)
    );
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, 0x20, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(161), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(161), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(185), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(185), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-210), zs(205), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(210), zs(205), zs(0), 255);
    spkCloseGiftag();
    spkOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
        SCE_GIF_PACKED_AD,
        0xFFFF0006,
        0);
    (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    (*spack.pos++) = SCE_GS_TEST_1;
    spkCloseOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 9),
        GIF_REG(SCE_GS_PRIM, 0)  |
        GIF_REG(SCE_GS_RGBAQ, 1) |
        GIF_REG(SCE_GS_XYZF2, 2) |
        GIF_REG(SCE_GS_XYZF2, 3) |
        GIF_REG(SCE_GS_XYZF2, 4) |
        GIF_REG(SCE_GS_XYZF2, 5) |
        GIF_REG(SCE_GS_XYZF2, 6) |
        GIF_REG(SCE_GS_XYZF2, 7) |
        GIF_REG(SCE_GS_XYZF2, 8)
    );
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x60, 0x60, 0xD0, 0x30, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(161), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(185), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-210), zs(205), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(210), zs(205), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(185), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(227), zs(161), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-227), zs(161), zs(0), 255);
    spkCloseGiftag();
    spkOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
        SCE_GIF_PACKED_AD,
        0xFFFF0006,
        0
    );
    (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    (*spack.pos++) = SCE_GS_TEST_1;
    spkCloseOpenDGiftag(
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 11),
        GIF_REG(SCE_GS_PRIM,  0)  |
        GIF_REG(SCE_GS_RGBAQ, 1)  |
        GIF_REG(SCE_GS_XYZF2, 2)  |
        GIF_REG(SCE_GS_XYZF2, 3)  |
        GIF_REG(SCE_GS_XYZF2, 4)  |
        GIF_REG(SCE_GS_XYZF2, 5)  |
        GIF_REG(SCE_GS_XYZF2, 6)  |
        GIF_REG(SCE_GS_XYZF2, 7)  |
        GIF_REG(SCE_GS_XYZF2, 8)  |
        GIF_REG(SCE_GS_XYZF2, 9)  |
        GIF_REG(SCE_GS_XYZF2, 10)
    );
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x60, 0x60, 0xD0, 0x30, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-212), zs(-170), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-232), zs(-147), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-232), zs(187), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-212), zs(210), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(212), zs(210), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(232), zs(187), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(232), zs(-147), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(212), zs(-170), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-212), zs(-170), zs(0), 255);
    spkCloseGiftag();
}

#ifdef NON_MATCHING
#line 1278
void look_cur(void) {
    int i;
    if (t.fade == 0) {
        if ((shPadRepeat(0, PAD_KEY_DPAD_DOWN) != 0) || ((shPadPress(0, PAD_KEY_7) > 192) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0))))) t.cursol++;
        if ((shPadRepeat(0, PAD_KEY_DPAD_UP) != 0) || ((shPadPress(0, PAD_KEY_7) < 64) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0))))) t.cursol--;
    }
    if (t.extra_mode == 0) {
        if (t.cursol < 0)  t.cursol = 10;
        if (t.cursol > 10) t.cursol = 0;
        if (t.fade == 0) 
            if ((shPadRepeat(0, PAD_KEY_DPAD_DOWN) != 0) || (shPadRepeat(0, PAD_KEY_DPAD_UP) != 0) || ((shPadPress(0, PAD_KEY_7) > 192) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0)))) || ((shPadPress(0, PAD_KEY_7) < 64) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0))))) 
                SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
    } else {

        if (t.cursol < 0) t.cursol = 6;
        if (t.cursol > 6) t.cursol = 0;
        if (t.fade == 0) 
            if ((shPadRepeat(0, PAD_KEY_DPAD_DOWN) != 0) || (shPadRepeat(0, PAD_KEY_DPAD_UP) != 0) || ((shPadPress(0, PAD_KEY_7) > 192) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0)))) || ((shPadPress(0, PAD_KEY_7) < 64) && ((t.ana_y == 0) || ((t.ana_y > 15) && ((t.ana_y % 3) == 0)))))
                SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
    }
    t.cursol_pos = option_near(2.0f, 1.0f, t.cursol_pos, 27 * t.cursol - 140);

    for (i = 0; i < 15; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65531, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 0, 0, 15 - i, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(-226), zs((int) t.cursol_pos + i), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(226), zs((int) t.cursol_pos + i + 1), zs(0), 255);
        spkCloseGiftag();

        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65531, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 0, 0, 15 - i, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(-226), zs((int) t.cursol_pos - i), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(226), zs(((int) t.cursol_pos - i) - 1), zs(0), 255);
        spkCloseGiftag();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_cur);
#endif

#line 1326
void allow_u(int x, int y) {
    int rgb;
    if (((int) t.timer % 40) < 20) rgb = ((int) t.timer % 40) * 3;
    else rgb = 120 - (((int) t.timer % 40) * 3);
    if (shPadPress(0, PAD_KEY_DPAD_UP) || shPadPress(0, PAD_KEY_7) < 64) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 100, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x), zs(y - 2), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 22), zs(y + 13), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 22), zs(y + 13), zs(0), 255);
        spkCloseGiftag();
        return;
    }
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 50, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x), zs(y), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 17), zs(y + 13), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 17), zs(y + 13), zs(0), 255);
    spkCloseGiftag();
}

#line 1354
void allow_d(int x, int y) {
    int rgb;
    if (((int) t.timer % 40) < 20) rgb = ((int) t.timer % 40) * 3;
    else rgb = 120 - (((int) t.timer % 40) * 3);
    if (shPadPress(0, PAD_KEY_DPAD_DOWN) || shPadPress(0, PAD_KEY_7) > 192) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 100, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x), zs(y + 2), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 22), zs(y - 13), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 22), zs(y - 13), zs(0), 255);
        spkCloseGiftag();
        return;
    }
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 50, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x), zs(y), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 17), zs(y - 13), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 17), zs(y - 13), zs(0), 255);
    spkCloseGiftag();
}

#line 1382
void allow_l(int x, int y) {
    int rgb;
    if (((int) t.timer % 40) < 20) rgb = ((int) t.timer % 40) * 3;
    else rgb = 120 - (((int) t.timer % 40) * 3);
    if (shPadPress(0, PAD_KEY_DPAD_LEFT) || shPadPress(0, PAD_KEY_6) < 64) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 100, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 2), zs(y), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 12), zs(y - 23), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 12), zs(y + 23), zs(0), 255);
        spkCloseGiftag();
        return;
    }
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 50, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x), zs(y), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 12), zs(y - 18), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 12), zs(y + 18), zs(0), 255);
    spkCloseGiftag();
}

#line 1410
void allow_r(int x, int y) {
    int rgb;
    if (((int) t.timer % 40) < 20) rgb = ((int) t.timer % 40) * 3;
    else rgb = 120 - (((int) t.timer % 40) * 3);
    if (shPadPress(0, PAD_KEY_DPAD_RIGHT) || shPadPress(0, PAD_KEY_6) > 192) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 100, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x + 2), zs(y), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 12), zs(y - 23), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 12), zs(y + 23), zs(0), 255);
        spkCloseGiftag();
        return;
    }
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65533, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(176, 160, 255, rgb + 50, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x), zs(y), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 12), zs(y - 18), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(x - 12), zs(y + 18), zs(0), 255);
    spkCloseGiftag();
}

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", KeyConfigPictureLoad);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", KeyConfigPitureStart);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_draw);

// @todo add `#define`s
void option_font(void) {
    char buf[4]; // r29+40
    char buf2[4]; // r29+44
    float f = 255.0f; // r29+48
    int c = (u_char )f / 4;; // @note: not in dwarf

    fontSetColorDirect(c, c, c, 255);
    if (t.option_step == 2) {
        if (t.extra_mode == 0) {
            fontPrintStrNum(msg_buffer, 72, 180, 52);
            
            fontSetColorDirect(c, c, c, 96);
            fontPrintStrNum(msg_buffer, 2,  180, 100);
            fontPrintStrNum(msg_buffer, 25, 190, 127);
            fontPrintStrNum(msg_buffer, 6,  195, 154);
            fontPrintStrNum(msg_buffer, 84, 119, 181);
            fontPrintStrNum(msg_buffer, 28, 152, 208);
            fontPrintStrNum(msg_buffer, 32, 145, 235);
            fontPrintStrNum(msg_buffer, 76, 151, 262);
            fontPrintStrNum(msg_buffer, 74, 161, 289);
            fontPrintStrNum(msg_buffer, 34, 187, 316);
            fontPrintStrNum(msg_buffer, 40, 120, 343);
            fontPrintStrNum(msg_buffer, 42, 142, 370);
            
            fontSetColorDirect(c, c, c, 255);
            if (t.cursol == 0) {
                fontPrintStrNum(msg_buffer, 2,  178, 98);
            }
            if (t.cursol == 1) {
                fontPrintStrNum(msg_buffer, 25, 188, 125);
            }
            if (t.cursol == 2) {
                fontPrintStrNum(msg_buffer, 6,  193, 152);
            }
            if (t.cursol == 3) {
                fontPrintStrNum(msg_buffer, 84, 117, 179);
            }
            if (t.cursol == 4) {
                fontPrintStrNum(msg_buffer, 28, 150, 206);
            }
            if (t.cursol == 5) {
                fontPrintStrNum(msg_buffer, 32, 143, 233);
            }
            if (t.cursol == 6) {
                fontPrintStrNum(msg_buffer, 76, 149, 260);
            }
            if (t.cursol == 7) {
                fontPrintStrNum(msg_buffer, 74, 159, 287);
            }
            if (t.cursol == 8) {
                fontPrintStrNum(msg_buffer, 34, 185, 314);
            }
            if (t.cursol == 9) {
                fontPrintStrNum(msg_buffer, 40, 118, 341);
            }
            if (t.cursol == 10) {
                fontPrintStrNum(msg_buffer, 42, 140, 368);
            }
            
            fontSetColorDirect(c, c, c, 96);
            if (playing.control_type == 0) {
                fontPrintStrNum(msg_buffer, 85, 270, 181);
            } else if (playing.control_type == 1) {
                fontPrintStrNum(msg_buffer, 86, 270, 181);
            }
            if (playing.vibration == 0) {
                fontPrintStrNum(msg_buffer, 69, 270, 208);
            } else if (playing.vibration == 1) {
                fontPrintStrNum(msg_buffer, 30, 270, 208);
            } else if (playing.vibration == 2) {
                fontPrintStrNum(msg_buffer, 70, 270, 208);
            } else if (playing.vibration == 3) {
                fontPrintStrNum(msg_buffer, 31, 270, 208);
            }
            if (playing.auto_load != 0) {
                fontPrintStrNum(msg_buffer, 68, 270, 235);
            } else {
                fontPrintStrNum(msg_buffer, 69, 270, 235);
            }
            if (playing.language == 0) {   
                fontPrintStrNum(msg_buffer, 78, 270, 262);
            } else if (playing.language == 1) {   
                fontPrintStrNum(msg_buffer, 79, 270, 262);
            } else if (playing.language == 2) {   
                fontPrintStrNum(msg_buffer, 81, 270, 262);
            } else if (playing.language == 3) {   
                fontPrintStrNum(msg_buffer, 80, 270, 262);
            } else if (playing.language == 4) {   
                fontPrintStrNum(msg_buffer, 82, 270, 262);
            } else if (playing.language == 5) {   
                fontPrintStrNum(msg_buffer, 83, 270, 262);
            }
            if (playing.subtitles != 0) {
                fontPrintStrNum(msg_buffer, 68, 270, 289);
            } else {
                fontPrintStrNum(msg_buffer, 69, 270, 289);
            }
            if (playing.sound == 0) {
                fontPrintStrNum(msg_buffer, 37, 270, 316);
            } else if (playing.sound == 1) {
                fontPrintStrNum(msg_buffer, 38, 270, 316);
            } else {
                fontPrintStrNum(msg_buffer, 39, 270, 316);
            }
            
            fontSetColorDirect(c, c, c, 255);
            if (t.cursol == 3) {
                if (playing.control_type == 0) {
                    fontPrintStrNum(msg_buffer, 85, 268, 179);
                } else if (playing.control_type == 1) {
                    fontPrintStrNum(msg_buffer, 86, 268, 179);
                }
            }
            if (t.cursol == 4) {
                if (playing.vibration == 0) {
                    fontPrintStrNum(msg_buffer, 69, 268, 206);
                } else if (playing.vibration == 1) {
                    fontPrintStrNum(msg_buffer, 30, 268, 206);
                } else if (playing.vibration == 2) {
                    fontPrintStrNum(msg_buffer, 70, 268, 206);
                } else if (playing.vibration == 3) {
                    fontPrintStrNum(msg_buffer, 31, 268, 206);
                }
            }
            if (t.cursol == 5) {
                if (playing.auto_load != 0) {
                    fontPrintStrNum(msg_buffer, 68, 268, 233);
                } else {
                    fontPrintStrNum(msg_buffer, 69, 268, 233);
                }
            }
            if (t.cursol == 6) {
                if (playing.language == 0) {
                    fontPrintStrNum(msg_buffer, 78, 268, 260);
                } else if (playing.language == 1) {   
                    fontPrintStrNum(msg_buffer, 79, 268, 260);
                } else if (playing.language == 2) {   
                    fontPrintStrNum(msg_buffer, 81, 268, 260);
                } else if (playing.language == 3) {   
                    fontPrintStrNum(msg_buffer, 80, 268, 260);
                } else if (playing.language == 4) {   
                    fontPrintStrNum(msg_buffer, 82, 268, 260);
                } else if (playing.language == 5) {   
                    fontPrintStrNum(msg_buffer, 83, 268, 260);
                }
            }
            if (t.cursol == 7) {
                if (playing.subtitles != 0) {
                    fontPrintStrNum(msg_buffer, 68, 268, 287);
                } else {
                    fontPrintStrNum(msg_buffer, 69, 268, 287);
                }
            }
            if (t.cursol == 8) {
                if (playing.sound == 0) {
                    fontPrintStrNum(msg_buffer, 37, 268, 314);
                } else if (playing.sound == 1) {
                    fontPrintStrNum(msg_buffer, 38, 268, 314);
                } else {
                    fontPrintStrNum(msg_buffer, 39, 268, 314);
                }
            }
            if (t.cursol == 0) {
                fontPrintStrNum(msg_buffer, 3,  70, 422);
            }
            if (t.cursol == 1) {
                fontPrintStrNum(msg_buffer, 26, 70, 422);
            }
            if (t.cursol == 2) {
                fontPrintStrNum(msg_buffer, 7,  70, 422);
            }
            if (t.cursol == 3) {
                fontPrintStrNum(msg_buffer, 87, 70, 422);
            }
            if (t.cursol == 4) {
                fontPrintStrNum(msg_buffer, 29, 70, 422);
            }
            if (t.cursol == 5) {
                fontPrintStrNum(msg_buffer, 33, 70, 422);
            }
            if (t.cursol == 6) {
                fontPrintStrNum(msg_buffer, 77, 70, 422);
            }
            if (t.cursol == 7) {
                fontPrintStrNum(msg_buffer, 75, 70, 422);
            }
            if (t.cursol == 8) {
                fontPrintStrNum(msg_buffer, 35, 70, 422);
            }
            if (t.cursol == 9) {
                fontPrintStrNum(msg_buffer, 41, 70, 422);
            }
            if (t.cursol == 10) {
                fontPrintStrNum(msg_buffer, 43, 70, 422);
                return;
            }
        } else {
            fontPrintStrNum(msg_buffer, 73, 120, 52);
            
            fontSetColorDirect(c, c, c, 96);
            fontPrintStrNum(msg_buffer, 44, 91, 100);
            fontPrintStrNum(msg_buffer, 48, 130, 127);
            fontPrintStrNum(msg_buffer, 53, 118, 154);
            fontPrintStrNum(msg_buffer, 55, 123, 181);
            fontPrintStrNum(msg_buffer, 57, 68, 208);
            fontPrintStrNum(msg_buffer, 61, 137, 235);
            fontPrintStrNum(msg_buffer, 65, 117, 262);
            
            fontSetColorDirect(c, c, c, 255);
            if (t.cursol == 0) {
                fontPrintStrNum(msg_buffer, 44, 89, 98);
            }
            if (t.cursol == 1) {
                fontPrintStrNum(msg_buffer, 48, 128, 125);
            }
            if (t.cursol == 2) {
                fontPrintStrNum(msg_buffer, 53, 116, 152);
            }
            if (t.cursol == 3) {
                fontPrintStrNum(msg_buffer, 55, 121, 179);
            }
            if (t.cursol == 4) {
                fontPrintStrNum(msg_buffer, 57, 66, 206);
            }
            if (t.cursol == 5) {
                fontPrintStrNum(msg_buffer, 61, 135, 233);
            }
            if (t.cursol == 6) {
                fontPrintStrNum(msg_buffer, 65, 115, 260);
            }
            
            fontSetColorDirect(c, c, c, 96);
            if (playing.weapon_control != 0) {
                fontPrintStrNum(msg_buffer, 47, 270, 100);
            } else {
                fontPrintStrNum(msg_buffer, 46, 270, 100);
            }
            if (playing.blood_color == 0) {
                fontPrintStrNum(msg_buffer, 70, 270, 127);
            } else if (playing.blood_color == 1) {
                fontPrintStrNum(msg_buffer, 50, 270, 127);
            } else if (playing.blood_color == 2) {
                fontPrintStrNum(msg_buffer, 51, 270, 127);
            } else if (playing.blood_color == 3) {
                fontPrintStrNum(msg_buffer, 52, 270, 127);
            }
            if (playing.view_control != 0) {
                fontPrintStrNum(msg_buffer, 71, 270, 154);
            } else {
                fontPrintStrNum(msg_buffer, 70, 270, 154);
            }
            if (playing.retreat_turn != 0) {
                fontPrintStrNum(msg_buffer, 71, 270, 181);
            } else {
                fontPrintStrNum(msg_buffer, 70, 270, 181);
            }
            if (playing.walk_run_control != 0) {
                fontPrintStrNum(msg_buffer, 71, 270, 208);
            } else {
                fontPrintStrNum(msg_buffer, 70, 270, 208);
            }
            if (playing.view_mode != 0) {
                fontPrintStrNum(msg_buffer, 64, 270, 235);
            } else {
                fontPrintStrNum(msg_buffer, 63, 270, 235);
            }
            sprintf(buf, "%d", playing.bullet_adjust);
            fontSetMes(0, dicSetStr(buf));
            fontPrintStrNum(msg_buffer, 67, 270, 262);
            
            fontSetColorDirect(c, c, c, 255);
            if (t.cursol == 0) {
                if (playing.weapon_control != 0) {
                    fontPrintStrNum(msg_buffer, 47, 268, 98);
                } else {
                    fontPrintStrNum(msg_buffer, 46, 268, 98);
                }
            }
            if (t.cursol == 1) {
                if (playing.blood_color == 0) {
                    fontPrintStrNum(msg_buffer, 70, 268, 125);
                } else if (playing.blood_color == 1) {
                    fontPrintStrNum(msg_buffer, 50, 268, 125);
                } else if (playing.blood_color == 2) {
                    fontPrintStrNum(msg_buffer, 51, 268, 125);
                } else if (playing.blood_color == 3) {
                    fontPrintStrNum(msg_buffer, 52, 268, 125);
                }
            }
            if (t.cursol == 2) {
                if (playing.view_control != 0) {
                    fontPrintStrNum(msg_buffer, 71, 268, 152);
                } else {
                    fontPrintStrNum(msg_buffer, 70, 268, 152);
                }
            }
            if (t.cursol == 3) {
                if (playing.retreat_turn != 0) {
                    fontPrintStrNum(msg_buffer, 71, 268, 179);
                } else {
                    fontPrintStrNum(msg_buffer, 70, 268, 179);
                }
            }
            if (t.cursol == 4) {
                if (playing.walk_run_control != 0) {
                    fontPrintStrNum(msg_buffer, 71, 268, 206);
                } else {
                    fontPrintStrNum(msg_buffer, 70, 268, 206);
                }
            }
            if (t.cursol == 5) {
                if (playing.view_mode != 0) {
                    fontPrintStrNum(msg_buffer, 64, 268, 233);
                } else {
                    fontPrintStrNum(msg_buffer, 63, 268, 233);
                }
            }
            if (t.cursol == 6) {
                sprintf(buf, "%d", playing.bullet_adjust);
                fontSetMes(0, dicSetStr(buf));
                fontPrintStrNum(msg_buffer, 67, 268, 260);
            }
            if (t.cursol == 0) {
                fontPrintStrNum(msg_buffer, 45, 80, 422);
            }
            if (t.cursol == 1) {
                fontPrintStrNum(msg_buffer, 49, 80, 422);
            }
            if (t.cursol == 2) {
                fontPrintStrNum(msg_buffer, 54, 80, 422);
            }
            if (t.cursol == 3) {
                fontPrintStrNum(msg_buffer, 56, 80, 422);
            }
            if (t.cursol == 4) {
                fontPrintStrNum(msg_buffer, 58, 80, 422);
            }
            if (t.cursol == 5) {
                fontPrintStrNum(msg_buffer, 62, 80, 422);
            }
            if (t.cursol == 6) {
                fontPrintStrNum(msg_buffer, 66, 80, 422);
                return;
            }
        }
    } else if (t.option_step == 3) {
        fontPrintStrNum(msg_buffer, 4,  25, 100);
        sprintf(buf, "%2d", playing.brightness_level);
        fontSetMes(0, dicSetStr(buf));
        fontPrintStrNum(msg_buffer, 5,  160, 420);
        return;
    } else if (t.option_step == 5) {
        sprintf(buf, "%3d", playing.screen_position_x / 2);
        sprintf(buf2, "%3d", playing.screen_position_y / 3);
        fontSetMes(0, dicSetStr(buf));
        fontSetMes(1, dicSetStr(buf2));
        fontPrintStrNum(msg_buffer, 27, 155, 320);
    }
}

// @info see look_blackscr in otn_itemmain
#line 1705
void look_scr(void) {
    int i;
    int j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -MAX_INT + 4, 0);
            spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
            spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
            (*spack.pos++) = SCE_GS_PRIM_SPRITE;
            (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 0, 0, 128, 0);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 64 - 256), zs(j * 64 - 256), zs(0), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 64 - 192), zs(j * 64 - 192), zs(0), 255);
            spkCloseGiftag();
        }
    }
}

int zs(int hoge) {
    return (hoge + 2048) * 16;
}
