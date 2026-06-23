#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "sound/sh_sound.h"
#include "Item/otn_option.h"

static struct /* @anon2 */ {
    // total size: 0x7C
    unsigned char option_step; // offset 0x0, size 0x1
    unsigned char extra_mode; // offset 0x1, size 0x1
    signed short cursol; // offset 0x2, size 0x2
    float cursol_pos; // offset 0x4, size 0x4
    signed short fade; // offset 0x8, size 0x2
    unsigned char fade_flag; // offset 0xA, size 0x1
    float timer; // offset 0xC, size 0x4
    signed short hoge; // offset 0x10, size 0x2
    unsigned int ana_x; // offset 0x14, size 0x4
    unsigned int ana_y; // offset 0x18, size 0x4
    struct Pad_KeyConfig key_config_set; // offset 0x1C, size 0x60
} t; // size: 0x7C, address: 0x11B6A70

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
                        DataLoadMessage(2);
                        fsSync(0, -1);
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_RIGHT)) || ((shPadPress(0, 0x40) > 0xC0) && !t.ana_x)) {
                        playing.language++;
                        DataLoadMessage(2);
                        fsSync(0, -1);
                    } else if (((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) && (!(playing.language))) {
                        playing.language = 1;
                        DataLoadMessage(2);
                        fsSync(0, -1);
                    } else if ((shPadTrigger(0, PAD_KEY_DPAD_LEFT)) || ((shPadPress(0, 0x40) <= 0x3f) && !t.ana_x)) {
                        playing.language--;
                        DataLoadMessage(2);
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

INCLUDE_RODATA("asm/nonmatchings/Item/otn_option", @1735);

INCLUDE_RODATA("asm/nonmatchings/Item/otn_option", @1736);

INCLUDE_RODATA("asm/nonmatchings/Item/otn_option", @1737);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", config_main);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", position_main);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_bgm);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_se);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", option_near);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", fade_in);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", fade_out);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_board);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_cur);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_u);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_d);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_l);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_r);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", KeyConfigPictureLoad);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", KeyConfigPitureStart);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", key_draw);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", option_font);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_scr);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", zs);

INCLUDE_RODATA("asm/nonmatchings/Item/otn_option", @2788);

INCLUDE_RODATA("asm/nonmatchings/Item/otn_option", @2789);

INCLUDE_RODATA("asm/nonmatchings/Item/otn_option", @2790);
