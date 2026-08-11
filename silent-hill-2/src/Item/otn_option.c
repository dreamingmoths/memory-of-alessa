#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/data_load.h"

#include "sce/libgraph.h"

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

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_cur);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_u);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_d);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_l);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", allow_r);

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

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", look_scr);

INCLUDE_ASM("asm/nonmatchings/Item/otn_option", zs);
