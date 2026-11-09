#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/playing_info.h"

#include "sce/libgraph.h"
#include "gs.h"

#include "Event/item.h"
#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/picture.h"

#include "Item/otn_option.h"
#include "Item/item_tgs_tmp.h"
#include "Item/otn_itemmain.h"

#include "data/daily.thu/data_pic_item.h"
#include "data/daily.thu/data_pic_etc.h"

#include "sound/sh_sound.h"
#include "Effect/screen_effect.h"
#include "Font/font.h"
#include "Fog/spack.h"
#include "FilesList/fileslist_bg.h"
#include "Multi_thr/filesys/fcread.h"

/* @todo: why does objdiff display this symbol as `unsigned short`? */
static struct /* @anon8 */ {
    // total size: 0x2A0
    u_char main_step; // offset 0x0, size 0x1
    u_char step; // offset 0x1, size 0x1
    u_char examine_step; // offset 0x2, size 0x1
    u_char pad_3[1];
    short turn_speed; // offset 0x4, size 0x2
    short command_cur; // offset 0x6, size 0x2
    short command_abe; // offset 0x8, size 0x2
    u_char pad_a[2];
    float command_move; // offset 0xC, size 0x4
    short gosa; // offset 0x10, size 0x2
    short cur_max; // offset 0x12, size 0x2
    u_char command_volume; // offset 0x14, size 0x1
    u_char command_light; // offset 0x15, size 0x1
    u_char prs_btn; // offset 0x16, size 0x1
    u_char prs_btn2; // offset 0x17, size 0x1
    u_char pad_18[8];
    float box[4][4]; // offset 0x20, size 0x40
    float boxblur[7][4][4]; // offset 0x60, size 0x1C0
    short item_no; // offset 0x220, size 0x2
    short item_kind; // offset 0x222, size 0x2
    short item_count; // offset 0x224, size 0x2
    u_char pad_226[2];
    float turnf; // offset 0x228, size 0x4
    int volume_time; // offset 0x22C, size 0x4
    float hp_time1; // offset 0x230, size 0x4
    float hp_time2; // offset 0x234, size 0x4
    float hp_abe; // offset 0x238, size 0x4
    float hp_kodo; // offset 0x23C, size 0x4
    float hp_abe2; // offset 0x240, size 0x4
    short allay_time; // offset 0x244, size 0x2
    u_char pad_246[2];
    float allay_abe; // offset 0x248, size 0x4
    float sprite_time; // offset 0x24C, size 0x4
    u_char use_item; // offset 0x250, size 0x1
    u_char pad_251[3];
    float weapon_scale[8]; // offset 0x254, size 0x20
    short combine[3]; // offset 0x274, size 0x6
    u_char pad_27a[2];
    float combine_abe; // offset 0x27C, size 0x4
    u_char shelf; // offset 0x280, size 0x1
    u_char pad_281[1];
    short use_item_kind; // offset 0x282, size 0x2
    u_char analog[4]; // offset 0x284, size 0x4
    float fade; // offset 0x288, size 0x4
    u_char fade_flag; // offset 0x28C, size 0x1
    u_char fade_step0; // offset 0x28D, size 0x1
    u_char fade_step1; // offset 0x28E, size 0x1
    u_char pad_28f[1];
    short examine_msg; // offset 0x290, size 0x2
    u_char pad_292[2];
    int seed; // offset 0x294, size 0x4
    u_char pad_298[2];
} t; // size: 0x2A0, address: 0x116E3D0

extern u_short msg_buffer[32768]; // size: 0x10000, address: 0x11B7040
extern int lcolor;


#define ITEM_SELECT_COUNT 75

struct /* @anon1 */ {
    // total size: 0x14
    u_char kind; // offset 0x0, size 0x1
    u_char count; // offset 0x1, size 0x1
    u_char del; // offset 0x2, size 0x1
    float pos[2]; // offset 0x4, size 0x8
    float rot; // offset 0xC, size 0x4
    float item_scale; // offset 0x10, size 0x4
} item_select[ITEM_SELECT_COUNT]; // size: 0x5DC, address: 0x116DDF0
int examine_rgb;

/* @todo find a place for these */
extern fsFileIndex data_pic_etc_p_laura_letter_tex[1];
extern fsFileIndex data_pic_etc_p_letterm_tex[1];
extern fsFileIndex data_pic_htl_p_redreling_tex[1];
extern fsFileIndex data_pic_out_p_lostmemory_tex[1];

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", itemmain);

#ifdef NON_MATCHING
#line 321
void itemmainmain(void) {
    // Range: 0x1CDDD0 -> 0x1CEC28
    int i; // r16
    int fog; // r17

    item_fade_in();
    item_fade_out();
    if (t.fade_flag == 2) {
        item_examine_fade_out();
    }
    
    if (shPadPress(0, PAD_KEY_6) > 192) {
        if (t.analog[2] < 2) t.analog[2]++;
    } else
        t.analog[2] = 0;
    if (shPadPress(0, PAD_KEY_6) < 64) {
        if (t.analog[1] < 2) t.analog[1]++;
    } else
        t.analog[1] = 0;
    if (shPadPress(0, PAD_KEY_7) > 192) {
        if (t.analog[0] < 2) t.analog[0]++;
    } else
        t.analog[0] = 0;
    if (shPadPress(0, PAD_KEY_7) < 64) {
        if (t.analog[3] < 2) t.analog[3]++;
    } else
        t.analog[3] = 0;

    
    t.shelf = GET_GAME_FLAG(416);
    
    
    item_turn();
    
    
    for (i = 0; i < t.item_count; i++)
        if (item_select[i].count)
            item_position(&item_select[i].pos[0], &item_select[i].pos[1], item_select[i].count, &item_select[i].rot);

    if (t.prs_btn2 != 0) t.turnf = 0.0f;
    else t.turnf += 0.02f;


    
    for (i = 0; i < t.item_count; i++) {
    
        if (item_select[i].count != 0) {
        
            
            fog = (int) (( -item_select[i].pos[1] - 300.0f) / 5.5);
            if (fog < 0) fog = 0;
            TgsItemPitureDraw(item_select[i].kind, item_select[i].pos[0] * 2.5, 0, fog, 5, (0.3f + (-item_select[i].pos[1] / 1666.0f)) * item_select[i].item_scale);







            
            if (item_select[i].del == 0) {
            
                if ((item_select[i].count == 5) && ((item_select[i].item_scale < 1.0f)))
                    item_select[i].item_scale += 0.1f;
                else if (item_select[i].count != 5 && item_select[i].item_scale > 0.8f)
                    item_select[i].item_scale = item_select[i].item_scale - 0.1f;
                if ((item_select[i].count == 5) && !(item_select[i].item_scale <= 1.0f))
                    item_select[i].item_scale = 1.0f;
                if (item_select[i].item_scale < 0.8f)
                    item_select[i].item_scale = 0.8f;
            } else
                item_select[i].item_scale -= 0.15f;
            if (item_select[i].item_scale < 0.0f) item_select[i].item_scale = 0.0f;

            if (item_select[i].count == 5) {
                
                t.item_kind = item_select[i].kind;
            }
            if (item_select[i].del != 0) {
                
                item_select[i].item_scale -= 0.15f;
                if (item_select[i].item_scale < 0.0f) {
                
                    item_select[i].item_scale = 0.0f;
                    item_select[i].kind = 0;
                    item_select[i].del = 0;
                }
            }
        }
    }


    
    if (item.equip == 4) t.weapon_scale[0] += 0.4f;
    else if (item.equip == 11) t.weapon_scale[1] += 0.4f;
    else if (item.equip == 6) t.weapon_scale[2] += 0.4f;
    else if (item.equip == 8) t.weapon_scale[3] += 0.4f;
    else if (item.equip == 10) t.weapon_scale[4] += 0.4f;
    else if (item.equip == 12) t.weapon_scale[5] += 0.4f;
    else if (item.equip == 13) t.weapon_scale[6] += 0.4f;
    else if (item.equip == 14) t.weapon_scale[7] += 0.4f;
    
    for (i = 0; i < 8; i++) {
        
        t.weapon_scale[i] -= 0.2f;
        if (t.weapon_scale[i] > 0.9f) t.weapon_scale[i] = 0.9f;
        if (t.weapon_scale[i] < 0.0f) t.weapon_scale[i] = 0.0f;
    }
    
    TgsItemPitureDraw(4, 0, -2144, 0x80, 1, t.weapon_scale[0]);
    TgsItemPitureDraw(11, 0, -2144, 0x80, 1, t.weapon_scale[1]);
    TgsItemPitureDraw(6, 0, -2144, 0x80, 1, t.weapon_scale[2]);
    TgsItemPitureDraw(8, 0, -2144, 0x80, 1, t.weapon_scale[3]);
    TgsItemPitureDraw(10, 0, -2144, 0x80, 1, t.weapon_scale[4]);
    TgsItemPitureDraw(12, 0, -2144, 0x80, 1, t.weapon_scale[5]);
    TgsItemPitureDraw(13, 0, -2144, 0x80, 1, t.weapon_scale[6]);
    TgsItemPitureDraw(14, 0, -2144, 0x80, 1, t.weapon_scale[7]);
    
    
    look_hp();
    
    
    if (t.fade_flag == 0) set_position(t.step);

    
    if ((t.box[0][0] == t.boxblur[1][0][0]) && (t.box[0][1] == t.boxblur[1][0][1])) t.prs_btn = 0;
    else t.prs_btn = 1;

    
    if (t.sprite_time >= 2.0f) t.sprite_time = 0.0f;
    if (t.prs_btn != 0) t.sprite_time = 0.0f;
    t.sprite_time += 0.04f;
    
    
    sprite();
    
    
    if (Sh2sys.step[2] == 6) font_print();

    
    if (t.fade_flag == 0) cur_step();

    
    look_combine();
    
    
    del_check();
    
    
    if (((t.command_abe == 0) && (t.step == 1)) || ((t.command_abe == 0) && (t.step == 12))) {
        
        t.command_cur = t.command_light = t.command_volume = 0;
    }
    
    look_command(t.gosa);
    
    
    if ((t.step == 6) || (t.step == 7))
        t.command_abe += 6;
    else t.command_abe -= 6;
    if (t.command_abe > 0x28) t.command_abe = 0x28;
    if (t.command_abe < 0) t.command_abe = 0;
    if (t.command_volume == 1) t.command_abe = 0;


    if ((int)(t.allay_abe) != 0) item_allay();

    
    if (t.step == 1)
        t.allay_abe += 4.0f;
    else t.allay_abe -= 4.0f;
    if (t.allay_abe > 32.0f) t.allay_abe = 32.0f;
    if (t.allay_abe < 0.0f) t.allay_abe = 0.0f;
    
    
    for (i = 6; i > 0; i--) t.boxblur[i] = *((sceVu0FMATRIX*)t.box + i);
    t.boxblur[0] = t.box;
    
    
    for (i = 0; i < 6; i++) {
        int value;
        t.boxblur[i][0][3] = (value = 20.0f * (1.0f - ((i / 7.0f))));
        t.boxblur[i][1][3] = t.boxblur[i][2][3] = t.boxblur[i][3][3] = value;
            
        look_zanzo(t.boxblur[i][0], t.boxblur[i][1], t.boxblur[i+1][0], t.boxblur[i+1][1]);
        look_zanzo(t.boxblur[i][1], t.boxblur[i][2], t.boxblur[i+1][1], t.boxblur[i+1][2]);
        look_zanzo(t.boxblur[i][2], t.boxblur[i][3], t.boxblur[i+1][2], t.boxblur[i+1][3]);
        look_zanzo(t.boxblur[i][3], t.boxblur[i][0], t.boxblur[i+1][3], t.boxblur[i+1][0]);
    
    
    
    
    
    }
    
    
    if ((t.step != 12) && (t.step != 13)) {
        lookline(t.box);
    }

    
    look_blackscr(1);


}
#else
INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", itemmainmain);
#endif

#line 534
void cur_step(void) {
    int i = 0; // @note unused

    switch (t.step) {
        case 0:
            t.step++;
            break;

        case 1:
            if (!t.prs_btn) {
                if (shPadPress(0, PAD_KEY_DPAD_DOWN) || t.analog[PAD_ANALOG_DOWN]) {
                    t.step = 4;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
                }
                if (shPadPress(0, PAD_KEY_DPAD_UP) || t.analog[PAD_ANALOG_UP]) {
                    if (item.equip) {
                        t.step = 5;
                        SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
                    }
                }
                if (shPadTrigger(0, key_config.enter) && !shPadPress(0, PAD_KEY_DPAD_LEFT) && !shPadPress(0, PAD_KEY_DPAD_RIGHT) && (t.analog[PAD_ANALOG_LEFT] == 0) && (t.analog[PAD_ANALOG_RIGHT] == 0) && (t.use_item == 0) && (t.item_kind) && (command_kind((short) t.item_kind) || t.shelf)) {
                    t.step = 6;
                    examine_file_load();
                    SeCall(SH_SOUND_ENTER_SELECTION_10002, 1.0f, 0);
                }
            }
            if (!t.prs_btn2) {
                if (shPadPress(0, PAD_KEY_DPAD_RIGHT) || t.analog[PAD_ANALOG_RIGHT]) {
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, -30);
                    t.item_no++;
                    t.prs_btn2 = 1;
                    if (t.item_no == t.item_count) {
                        t.item_no = 0;
                    }
                    if (shPadPress(0, PAD_KEY_DPAD_RIGHT)) {
                        t.turn_speed = 64;
                    } else {
                        t.turn_speed = shPadPress(0, PAD_KEY_6) - 192;
                    }
                }
                if (shPadPress(0, PAD_KEY_DPAD_LEFT) || t.analog[PAD_ANALOG_LEFT]) {
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 30);
                    t.item_no--;
                    t.prs_btn2 = 1;
                    if (t.item_no == -1) {
                        t.item_no = t.item_count - 1;
                    }
                    if (shPadPress(0, PAD_KEY_DPAD_LEFT)) {
                        t.turn_speed = 64;
                    } else {
                        t.turn_speed = -(shPadPress(0, PAD_KEY_6) - 64);
                    }
                }
            }
            if ((shPadTrigger(0, key_config.cancel)) && (!t.prs_btn) && (!t.prs_btn2) && (t.combine[0] == 0)) {
                t.fade_flag  = 1;
                t.fade_step0 = 1;
                t.fade_step1 = 6;
            }
            if (shPadTrigger(0, key_config.cancel)) {
                t.combine[0] = t.combine[1] = t.combine[2] = 0;
                return;
            }
            break;

        case 2:
            if (!t.prs_btn) {
                if (shPadPress(0, PAD_KEY_DPAD_RIGHT) || t.analog[PAD_ANALOG_RIGHT]) {
                    t.step = 4;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 60);
                }
                if (shPadPress(0, PAD_KEY_DPAD_UP) || t.analog[PAD_ANALOG_UP]) {
                    t.step = 1;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 60);
                }
            }
            if (shPadPress(0, key_config.enter)) {
                t.fade_flag  = 1;
                t.fade_step0 = 7;
                t.fade_step1 = 2;
            }
            if ((shPadTrigger(0, key_config.cancel)) && (!t.prs_btn) && (!t.prs_btn2) && (t.combine[0] == 0)) {
                t.fade_flag  = 1;
                t.fade_step0 = 1;
                t.fade_step1 = 6;
            }
            if (shPadTrigger(0, key_config.cancel)) {
                t.combine[0] = t.combine[1] = t.combine[2] = 0;
                return;
            }
            break;

        case 3:
            if (!t.prs_btn) {
                if (shPadPress(0, PAD_KEY_DPAD_LEFT) || t.analog[PAD_ANALOG_LEFT]) {
                    t.step = 4;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, -60);
                }
                if (shPadPress(0, PAD_KEY_DPAD_UP) || t.analog[PAD_ANALOG_UP]) {
                    t.step = 1;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
                }
            }
            if ((shPadTrigger(0, key_config.enter)) && MemoCommandCheck()) {
                t.fade_flag  = 1;
                t.fade_step0 = 8;
                t.fade_step1 = 0;
            }
            if ((shPadTrigger(0, key_config.cancel)) && (!t.prs_btn) && (!t.prs_btn2) && (t.combine[0] == 0)) {
                t.fade_flag  = 1;
                t.fade_step0 = 1;
                t.fade_step1 = 6;
            }
            if (shPadTrigger(0, key_config.cancel)) {
                t.combine[0] = t.combine[1] = t.combine[2] = 0;
                return;
            }
            break;

        case 4:
            if (!t.prs_btn) {
                if (shPadPress(0, PAD_KEY_DPAD_LEFT) || t.analog[PAD_ANALOG_LEFT]) {
                    t.step = 2;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 20);
                }
                if ((shPadPress(0, PAD_KEY_DPAD_RIGHT) || t.analog[PAD_ANALOG_RIGHT]) && MemoCommandCheck()) {
                    t.step = 3;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, -20);
                }
                if (shPadPress(0, PAD_KEY_DPAD_UP) || t.analog[PAD_ANALOG_UP]) {
                    t.step = 1;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
                }
                if (shPadPress(0, key_config.enter)) {
                    t.fade_flag  = 1;
                    t.fade_step0 = 5;
                    t.fade_step1 = 1;
                }
            }
            if ((shPadTrigger(0, key_config.cancel)) && (!t.prs_btn) && (!t.prs_btn2) && (t.combine[0] == 0)) {
                t.fade_flag  = 1;
                t.fade_step0 = 1;
                t.fade_step1 = 6;
            }
            if (shPadTrigger(0, key_config.cancel)) {
                t.combine[0] = t.combine[1] = t.combine[2] = 0;
                return;
            }
            break;

        case 5:
            if (!t.prs_btn) {
                if (shPadPress(0, PAD_KEY_DPAD_DOWN) || t.analog[PAD_ANALOG_DOWN]) {
                    t.step = 1;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
                }
                if (shPadPress(0, key_config.enter)) {
                    t.step = 7;
                    SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
                }
            }
            if ((shPadTrigger(0, key_config.cancel)) && (!t.prs_btn) && (!t.prs_btn2)) {
                t.step = 1;
                SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 60);
                return;
            }
            break;

        case 6:
            command_main(command_kind((s32) t.item_kind));
            if ((!t.prs_btn) && (shPadPress(0, key_config.cancel)) && (t.use_item == 0)) {
                t.command_volume = 0;
                t.step           = 1;
                SeCall(SH_SOUND_CANCEL_SELECTION_10003, 1.0f, -30);
                return;
            }
            break;

        case 7:
            weapon_command_main(command_kind((s32) item.equip));
            if ((!t.prs_btn) && (shPadPress(0, key_config.cancel))) {
                t.command_volume = 0;
                t.step           = 1;
                SeCall(SH_SOUND_CANCEL_SELECTION_10003, 1.0f, -30);
                return;
            }
            break;

        case 8:
            if (!t.prs_btn) {
                t.step = 1;
                SeCall(SH_SOUND_ENTER_SELECTION_10002, 1.0f, 30);
                return;
            }
            break;

        case 9:
            if (!t.prs_btn) {
                t.step = 1;
                return;
            }
            break;

        case 11:
            if ((shPadTrigger(0, key_config.enter)) && (t.use_item == 0)) {
                t.step = 1;
                return;
            }
            break;

        case 12:
            examine2_main();
            if (shPadTrigger(0, key_config.enter) || shPadTrigger(0, key_config.cancel)) {
                t.step = 13;
                if (t.item_kind == SH2_ITEM_48) {
                    FcRead(data_pic_item_x_coinelder_ura_tex, layer_adr);
                } else if (t.item_kind == SH2_ITEM_49) {
                    FcRead(data_pic_item_x_coinprisoner_ura_tex, layer_adr);
                } else if (t.item_kind == COIN_OF_SNAKE) {
                    FcRead(data_pic_item_x_coinsnake_ura_tex, layer_adr);
                }
            }
            break;

        case 13:
            examine2_main();
            if (!t.prs_btn) {
                if ((t.item_kind == SH2_ITEM_48 || t.item_kind == SH2_ITEM_49 || t.item_kind == COIN_OF_SNAKE) && t.examine_step == 1) {
                    if (fsSync(1, -1) >= 0) {
                        t.step = 12;
                        t.examine_step++;
                    }
                } else {
                    t.step         = 1;
                    t.examine_step = 0;
                }
                SeCall(SH_SOUND_ENTER_SELECTION_10002, 1.0f, 30);
            }
            break;
    }
}

void command_main(int command_step) {

    
    switch (command_step) {
    
        case 1:
            t.gosa = -143;
            t.cur_max = 1;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn)
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else {
                    if (t.command_cur == t.shelf) {
                        if (t.combine[0] == 0) event_item_use(t.item_kind);
                        else if ((t.item_kind == (short) t.combine[0]) && !t.combine[1]) event_item_use(t.item_kind);
                        else if ((t.item_kind == (short) t.combine[0]) || (t.item_kind == t.combine[1])) combine_item_use(0);
                        else combine_item_use(t.item_kind);

                        if (!t.use_item) t.step = 1;
                        SeCall(10002, 1.0f, -30);
                    } else {
                        
                        if (t.combine[0] == 0) t.combine[0] = t.item_kind;
                        else if (!t.combine[1] && (short) t.combine[0] != t.item_kind) t.combine[1] = t.item_kind;
                        else if ((t.combine[1]) && (short) t.combine[0] != t.item_kind && (short) t.combine[1] != t.item_kind) t.combine[2] = t.item_kind;
                        else if (t.combine[1]) combine_item_use(0);
                        if (!t.use_item) t.step = 1;
                        SeCall(10002, 1.0f, -30);
                    }
                }
            break;
        case 2:
            t.gosa = -133 - (t.shelf * 10);
            t.cur_max = t.shelf;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn)
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else {
                    
                    ItemMedicineUse(t.item_kind);
                    t.step = 8;
                    SeCall(10002, 1.0f, -30);
                }
            
            break;
        case 3:
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                if (t.shelf && !t.command_cur) {
                    if (t.item_kind == item.equip) item.equip = 0;
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else {
                    
                    if (item.equip != t.item_kind)
                        item.equip = t.item_kind;
                    else
                        item.equip = 0;
                    t.step = 9;
                    SeCall(10002, 1.0f, -30);
                }
            }
            t.gosa = -133 - (t.shelf * 10);
            t.cur_max = t.shelf;
            break;
        case 4:
            t.gosa = -143 - (t.shelf * 15);
            t.cur_max = t.shelf + 1;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                if (t.shelf && !t.command_cur) {
                    if (t.item_kind == item.equip) item.equip = 0;
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else
                    if (t.command_cur == t.shelf) {
                        if (item.equip != t.item_kind)
                            item.equip = t.item_kind;
                        else
                            item.equip = 0;
                        t.step = 9;
                    } else {
                        
                        ItemWeaponReload(t.item_kind, 1);
                        t.step = 1;
                    }
                SeCall(10002, 1.0f, -30);
            }
            break;
        case 5:
            t.gosa = -133 - (t.shelf * 10);
            t.cur_max = t.shelf;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else {
                    
                    if (GET_FLAG(item.flag, t.item_kind - 1)) ItemWeaponReload(t.item_kind, 1);
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                }
            }
            break;
        case 6:
            if (t.command_light == 0) {
                
                if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                    if (t.shelf && !t.command_cur) {
                        if (!t.use_item) t.use_item = 8;
                        item.event_use[0] = t.item_kind;
                        ItemPutForShelf();
                        item_select[kind_no(t.item_kind)].del = 1;
                        t.step = 1;
                        SeCall(10002, 1.0f, -30);
                    } else {
                        
                        t.command_cur = 0;
                        t.command_light = 1;
                        SeCall(10002, 1.0f, -30);
                    }
                }
                t.gosa = -133 - (t.shelf * 10);
                t.cur_max = t.shelf;
            } else {

                
                if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                    if (t.command_cur == 0) item.light_switch = 1;
                    else item.light_switch = 0;
                    t.command_light = 0;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                }
                t.gosa = -135;
                t.cur_max = 1;
            }
            break;
        case 7:
            if (t.command_volume == 0) {
                if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                    if (t.shelf && !t.command_cur) {
                        if (!t.use_item) t.use_item = 8;
                        item.event_use[0] = t.item_kind;
                        ItemPutForShelf();
                        item_select[kind_no(t.item_kind)].del = 1;
                        t.step = 1;
                        SeCall(10002, 1.0f, -30);
                    } else 
                        if (t.command_cur == t.shelf) {
                            t.command_cur = 0;
                            t.command_volume = 2;
                            SeCall(10002, 1.0f, -30);
                        } else {
                            
                            t.command_cur = 0;
                            t.command_volume = 1;
                            SeCall(10002, 1.0f, -30);
                        }
                }
            } else
                if (t.command_volume == 2) {
                    if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn) {
                        if (t.command_cur == 0) {
                            item.radio_switch = 1;
                            t.command_volume = 0;
                            t.step = 1;
                            SeCall(10002, 1.0f, -30);
                        } else {
                            
                            item.radio_switch = 0;
                            t.command_volume = 0;
                            t.step = 1;
                            SeCall(10002, 1.0f, -30);
                        }
                    }
                } else {
                    
                    if ((shPadPress(0, PAD_KEY_DPAD_RIGHT)) || (shPadPress(0, PAD_KEY_DPAD_LEFT)) || t.analog[1] || t.analog[2]) t.volume_time++;
                    else t.volume_time = 0;
                    
                    if (((shPadPress(0, PAD_KEY_DPAD_RIGHT)) || t.analog[2]) 
                        && ((((t.volume_time % 20) == 1) && (t.volume_time < 20)) || (((t.volume_time % 3) == 1) && (t.volume_time >= 20))))
                        if (item.radio_volume < 15) {
                            item.radio_volume++;
                            SeCall(19017, (4.0f + item.radio_volume) / 20.0f, -30);
                        }
                    
                    if (((shPadPress(0, PAD_KEY_DPAD_LEFT)) || t.analog[1]) 
                        && ((((t.volume_time % 20) == 1) && (t.volume_time < 20)) || (((t.volume_time % 3) == 1) && (t.volume_time >= 20))))
                        if ((item.radio_volume > 0)) {
                            item.radio_volume--;
                            SeCall(19017, (4.0f + item.radio_volume) / 20.0f, -30);
                        }
                    if ((shPadTrigger(0, key_config.enter)) && !t.volume_time) {
                        t.command_volume = 0;
                        t.step = 1;
                        SeCall(10002, 1.0f, -30);
                    }
                    look_volume();
                }
            if (t.command_volume == 0) 
                t.gosa = -143 - (t.shelf * 15), t.cur_max = t.shelf + 1;
            else if (t.command_volume == 1) t.gosa = -135, t.cur_max = 0;
            else t.gosa = -135, t.cur_max = 1;
            break;
        
        case 8:
            t.gosa = -143 - (t.shelf * 15);
            t.cur_max = t.shelf + 1;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn && !t.use_item) {
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else
                    if (t.command_cur == t.shelf) {

                        
                        event_item_use(t.item_kind);
                        if (!t.use_item) t.step = 1;
                        SeCall(10002, 1.0f, -30);
                    } else {
                        
                        t.use_item = 4;
                        t.step = 11;
                        SeCall(10002, 1.0f, -30);
                    }
            }
            break;
        case 9:
            t.gosa = -143 - (t.shelf * 15);
            t.cur_max = t.shelf + 1;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn && !t.use_item) {
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else 
                    if (t.command_cur == t.shelf) {
                        
                        
                        event_item_use(t.item_kind);
                        SeCall(10002, 1.0f, -30);
                    } else {
                        
                        t.fade_flag = 2;
                        ScreenEffectFadeStart(1, 0.5f);
                        if (t.item_kind == 18) {
                                t.examine_msg = 184;
                                FcRead(data_pic_etc_p_letterm_tex, get_gp_data_buf_addr());
                        } else 
                            if (t.item_kind == 19) {
                                    t.examine_msg = 185;
                                    FcRead(data_pic_etc_p_laura_letter_tex, get_gp_data_buf_addr());
                            } else 
                                if (t.item_kind == 71) {
                                        t.examine_msg = 186;
                                        FcRead(data_pic_out_p_lostmemory_tex, get_gp_data_buf_addr());
                                } else 
                                    if (t.item_kind == 72) {
                                            t.examine_msg = 187;
                                            FcRead(data_pic_htl_p_redreling_tex, get_gp_data_buf_addr());
                                    }
                        SeCall(10002, 1.0f, -30);
                    }
            }
            break;
    
        case 10:
            t.gosa = -158;
            t.cur_max = 2;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn && !t.use_item) {
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else 
                    if (t.command_cur == t.shelf) {
                        if (t.combine[0] == 0) event_item_use(t.item_kind);
                        else if ((t.item_kind == (short) t.combine[0]) && !t.combine[1]) event_item_use(t.item_kind);
                        else if ((t.item_kind == (short) t.combine[0]) || (t.item_kind == t.combine[1])) combine_item_use(0);
                        else combine_item_use(t.item_kind);
                        SeCall(10002, 1.0f, -30);
                    } else 
                        if (!t.shelf && (t.command_cur == 1)) {
                            if (t.combine[0] == 0) t.combine[0] = t.item_kind;
                            else if (!t.combine[1] && ((short) t.combine[0] != t.item_kind)) t.combine[1] = t.item_kind;
                            else if ((t.combine[1]) && ((short) t.combine[0] != t.item_kind) && ((short) t.combine[1] != t.item_kind)) t.combine[2] = t.item_kind;
                            else if (t.combine[1]) combine_item_use(0);
                            if (!t.use_item) t.step = 1;
                            SeCall(10002, 1.0f, -30);
                        } else {
                            
                            t.step = 12;
                            SeCall(10002, 1.0f, -30);
                        }
            }
            break;
        case 11:
            t.gosa = -143 - (t.shelf * 15);
            t.cur_max = t.shelf + 1;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn && !t.use_item) {
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                } else 
                    if (t.command_cur == t.shelf) {
                        if (t.combine[0] == 0) event_item_use(t.item_kind);
                        else if ((t.item_kind == (short) t.combine[0]) && !t.combine[1]) event_item_use(t.item_kind);
                        else if ((t.item_kind == (short) t.combine[0]) || (t.item_kind == t.combine[1])) combine_item_use(0);
                        else combine_item_use(t.item_kind);
                        SeCall(10002, 1.0f, -30);
                    } else {
                        
                        t.step = 12;
                        SeCall(10002, 1.0f, -30);
                    }
            }
            break;


        
        default:
            t.gosa = -133;
            t.cur_max = 0;
            if ((shPadTrigger(0, key_config.enter)) && !t.prs_btn && !t.use_item)
                if (t.shelf && !t.command_cur) {
                    if (!t.use_item) t.use_item = 8;
                    item.event_use[0] = t.item_kind;
                    ItemPutForShelf();
                    item_select[kind_no(t.item_kind)].del = 1;
                    t.step = 1;
                    SeCall(10002, 1.0f, -30);
                }
            break;
        
        case 12:
            break;
    }
    if (((shPadTrigger(0, PAD_KEY_DPAD_DOWN)) || (t.analog[0] == 1)) && !t.use_item)
        if (t.command_cur < t.cur_max) {
            t.command_cur++;
            SeCall(10000, 1.0f, -30);                
        }
    if (((shPadTrigger(0, PAD_KEY_DPAD_UP)) || (t.analog[3] == 1)) && !t.use_item)
        if (t.command_cur > 0) {
            t.command_cur--;
            SeCall(10000, 1.0f, -30);
        }

    
}

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", weapon_command_main);

void item_main_setup(void) {
    int i; // r2
    int j; // r3

    t.main_step = 0;
    t.step = 0;
    t.examine_step = 0;
    t.turn_speed = 0;
    t.command_cur = 0;
    t.command_abe = 0;
    t.command_move = 0.0f;
    t.gosa = -0x8F, t.cur_max = 0;
    t.command_volume = 0;
    t.command_light = 0;
    t.item_no = 0;
    t.item_kind = 0;
    t.item_count = 0;
    t.turnf = 0.0f;
    t.volume_time = 0;
    t.hp_time1 = -150.0f;
    t.hp_time2 = 0.0f;
    t.hp_abe = 0.0f;
    t.allay_time = 0;
    t.allay_abe = 0.0f;
    t.sprite_time = 0.0f;
    t.use_item = 0;
    t.weapon_scale[1] = 0.0f, t.weapon_scale[0] = 0.0f;
    t.combine[2] = 0, t.combine[1] = 0, t.combine[0] = 0;
    t.fade = 1.0f;
    t.fade_flag = 0;
    t.fade_step0 = 0;
    
    for (i = 0; i < 0x4B; i++) {
        item_select[i].kind = 0;
        item_select[i].count = 0;
        item_select[i].del = 0;
        item_select[i].rot = 0;
        item_select[i].item_scale = 0;
    }
    
    
    set_position(t.step);
    for (j = 0; j < 6; j++) {
        
        for (i = 6; i > 0; i--) t.boxblur[i] = *((sceVu0FMATRIX*)t.box + i);
        
        t.boxblur[0] = t.box;
    }
    j = 0;
    t.item_count = 0;
    for (i = 0; i < ITEM_SELECT_COUNT; i++)
        if (GET_FLAG(item.flag, i)) {
            
            item_select[j++].kind = i;
            t.item_count++;
        }
    if (t.item_count < 9) t.item_count = 9;
    t.item_no = t.item_count - 5;
    
    for (i = 0; i < t.item_count; i++) {
    
        if (!item.last_cursor) break;
        if ((u_char) item.last_cursor == item_select[i].kind) {
            t.item_no = i - 5;
            if (t.item_no < 0) t.item_no += t.item_count;
            break;
        }
    }
    
    item_turn();
    
    
    if (item.equip == 4) t.weapon_scale[0] = 0.9f;
    else if (item.equip == 0xB) t.weapon_scale[1] = 0.9f;

    enWaitAllInsect();

}

#ifdef NON_MATCHING
void set_position(int step) {
    switch (step) {
        case 0:
            t.box[0][0] = -120.0f;
            t.box[0][1] = -120.0f;
            t.box[0][3] = 255.0f;
            t.box[1][0] = -120.0f;
            t.box[1][1] = 120.0f;
            t.box[1][3] = 255.0f;
            t.box[2][0] = 120.0f;
            t.box[2][1] = 120.0f;
            t.box[2][3] = 255.0f;
            t.box[3][0] = 120.0f;
            t.box[3][1] = -120.0f;
            t.box[3][3] = 255.0f;
            return;
        case 1:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -55.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], -65.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -55.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], 65.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 55.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], 65.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 55.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], -65.0f);
            return;
        case 2:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -240.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], 173.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -240.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], 203.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], -80.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], 203.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], -80.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], 173.0f);
            return;
        case 4:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -80.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], 173.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -80.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], 203.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 80.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], 203.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 80.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], 173.0f);
            return;
        case 3:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], 80.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], 173.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], 80.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], 203.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 240.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], 203.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 240.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], 173.0f);
            return;
        case 5:
        case 9:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -80.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], -203.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -80.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], -63.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 80.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], -63.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 80.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], -203.0f);
            return;
        case 6:
        case 7:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], 80.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], -203.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], 80.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], -80.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 240.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], -80.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 240.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], -203.0f);
            return;
        case 8:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -240.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], -203.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -240.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], -60.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], -80.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], -60.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], -80.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], -203.0f);
            return;
        case 11:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -230.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], 80.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -230.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], 170.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 230.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], 170.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 230.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], 80.0f);
            return;
        case 12:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -100.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], -150.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -100.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], 50.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 100.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], 50.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 100.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], -150.0f);
            return;
        case 13:
            t.box[0][0] = move_near(2.0f, 1.0f, t.box[0][0], -55.0f);
            t.box[0][1] = move_near(2.0f, 1.0f, t.box[0][1], -52.0f);
            t.box[1][0] = move_near(2.0f, 1.0f, t.box[1][0], -55.0f);
            t.box[1][1] = move_near(2.0f, 1.0f, t.box[1][1], -48.0f);
            t.box[2][0] = move_near(2.0f, 1.0f, t.box[2][0], 55.0f);
            t.box[2][1] = move_near(2.0f, 1.0f, t.box[2][1], -48.0f);
            t.box[3][0] = move_near(2.0f, 1.0f, t.box[3][0], 55.0f);
            t.box[3][1] = move_near(2.0f, 1.0f, t.box[3][1], -52.0f);
    }
}
#else
const char __pad_0x00392ee8[] = "\0\0\0\0"; /* @hack temporary fix to align rodata */
INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", set_position);
#endif

#line 1437
void item_turn(void) {
    int i;
    int j;

    for (i = 0; i < t.item_count; i++)
        item_select[i].count = 0;

    for (i = t.item_no, j = 0; i < t.item_no + 10; i++, j++) {
        
        if (i < t.item_count)
            item_select[i].count = j;
        else
            item_select[i - t.item_count].count = j;
    }
}

#ifdef HOLY_CANDLE
#line 1459
void item_position(sceVu0FVECTOR f0, sceVu0FVECTOR f1, int count, sceVu0FVECTOR r0) {
    r0[0] = move_near(20.0f, 110.0f + t.turn_speed, 1000.0f * *r0, count * 1000);
    r0[0] /= 1000.0f;
    
    if ((count - *r0) > 1.5f || (count - *r0) < -1.5f) *r0 = count;

    f0[0] = sin(((PI * (*r0 - 5.0f)) / 5.0f) / 1.6f) * 1500.0;
    f1[0] = -cos(((PI * (*r0 - 5.0f)) / 5.0f) / 1.6f) * 1000.0;
    
    if (count == *r0 && count == 5) t.prs_btn2 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", item_position)
#endif

#line 1485
int move_near(float f0, float f1, float f2, float f3) {
    float f;
    if (f2 < f3) {
        f = f2 + (((f3 - f2) / f0) * (30.0f * shGetDT()));
        f = f + (f1 * (30.0f * shGetDT()));
        if (f >= f3) f = f3;
    }
    else {
        f = f2 - (((f2 - f3) / f0) * (30.0f * shGetDT()));
        f = f - (f1 * (30.0f * shGetDT()));
        if (f <= f3) f = f3;
    }
    return f;
}

#line 1519
int command_kind(int kind) {
    switch (kind) {
        case SH2_ITEM_22:
        case APART_202_KEY:
        case SH2_ITEM_30:
        case SH2_ITEM_31:
        case SH2_ITEM_32:
        case SH2_ITEM_34:
        case SH2_ITEM_35:
        case SH2_ITEM_36:
        case SH2_ITEM_37:
        case SH2_ITEM_39:
        case SH2_ITEM_41:
        case SH2_ITEM_42:
        case SH2_ITEM_43:
        case SH2_ITEM_44:
        case SH2_ITEM_45:
        case SH2_ITEM_46:
        case SH2_ITEM_50:
        case SH2_ITEM_NEEDLE:
        case SH2_ITEM_52:
        case SH2_ITEM_55:
        case SH2_ITEM_59:
        case SH2_ITEM_60:
        case SH2_ITEM_61:
        case SH2_ITEM_62:
        case SH2_ITEM_63:
        case SH2_ITEM_64:
        case SH2_ITEM_65:
        case SH2_ITEM_66:
        case SH2_ITEM_67:
        case SH2_ITEM_68:
        case SH2_ITEM_69:
        case SH2_ITEM_70:
        case SH2_ITEM_73:
            return 1;

        case HEALTH_DRINK:
        case FIRST_AID_KIT:
        case AMPOULE:
            return 2;

        case SH2_ITEM_10:
        case WOODEN_PLANK:
        case SH2_ITEM_12:
        case SH2_ITEM_13:
        case CHAINSAW:
            return 3;

        case SH2_ITEM_04:
        case SH2_ITEM_06:
        case SH2_ITEM_08:
            return 4;

        case SH2_ITEM_05:
        case SH2_ITEM_07:
        case SH2_ITEM_09:
            return 5;

        case SH2_ITEM_15:
            return 6;

        case SH2_ITEM_RADIO:
            return 7;

        case SH2_ITEM_20:
        case SH2_ITEM_21:
        case SH2_ITEM_26:
        case SH2_ITEM_27:
        case SH2_ITEM_28:
        case SH2_ITEM_40:
        case SH2_ITEM_74:
            return 8;

        case SH2_ITEM_18:
        case SH2_ITEM_19:
        case SH2_ITEM_71:
        case SH2_ITEM_72:
            return 9;

        case APART_GATE_KEY:
        case SH2_ITEM_25:
        case SH2_ITEM_29:
        case SH2_ITEM_33:
        case SH2_ITEM_38:
        case COIN_OF_SNAKE:
        case SH2_ITEM_48:
        case SH2_ITEM_49:
        case SH2_ITEM_53:
        case SH2_ITEM_54:
        case SH2_ITEM_56:
        case SH2_ITEM_57:
        case SH2_ITEM_58:
            return 10;

        case SH2_ITEM_17:
            return 11;

        default:
            return 0;
    }
}

#line 1617
void del_check(void) {
    int i;
    for (i = 0; i < t.item_count; i++) {
        
        switch (item_select[i].kind) {
            default: break;
            case 1:
            case 2:
            case 3:
            case 5:
            case 7:
            case 9:
                if (item.number[item_select[i].kind] == 0) {
                    item_select[kind_no(item_select[i].kind)].del = true;
                }
        }
    }
}

#line 1641
int kind_no(int kind) {
    int i;

    for (i = 0; i < t.item_count; i++)
        if (kind == item_select[i].kind) 
            return i;

    return 0;
}

#line 1670
void event_item_use(int kind) {
    if (ItemEventCheck(kind, 0, 0) != -1) {
        
        item.event_use[0] = kind; item.event_use[1] = 0; item.event_use[2] = 0; // @note possible macro
        t.fade_flag = 1;
        t.fade_step0 = 1;
        t.fade_step1 = 6;
        
    } else 
        t.use_item = 1;
}

#line 1686
void combine_item_use(int kind) {
    if (ItemEventCheck(kind, t.combine[0], t.combine[1]) != -1 && ItemEventCheck(kind, t.combine[0], t.combine[1]) != -2) {
        item.event_use[0] = kind;
        item.event_use[1] = t.combine[0];
        item.event_use[2] = t.combine[1];
        t.fade_flag = 1;
        t.fade_step0 = 1;
        t.fade_step1 = 6;
    } else if (ItemEventCheck(kind, t.combine[0], t.combine[1]) != -1) {
        t.use_item = 3;
    } else {
        t.use_item = 1;
    }
    if (t.combine[1]) {
        t.combine[2] = (s16) kind;
        return;
    }
    t.combine[1] = (s16) kind;
}

#line 1715
void examine_main(void) {
    static PicDraw_Data i_pic;

    #line 1719
    switch (t.examine_step) {
        default: break;
        
        case 0:
            fontClear();
            examine_rgb = 128;
            PictureLoadImage(get_gp_data_buf_addr(), 0, -1, -1);
            
            shQzero(&i_pic, sizeof(i_pic));
            
            picture_set_ap(&i_pic, get_gp_data_buf_addr());
            picture_set_alpha(&i_pic, 128);
            
            i_pic.r = 128; i_pic.g = 128; i_pic.b = 128; i_pic.status |= 16;
            i_pic.otp = 1;
            PictureDraw(&i_pic);
            
            look_blackscr(1);
            if (shPadTrigger(0, key_config.enter) || shPadTrigger(0, key_config.cancel))
                t.examine_step = 1;
            break;
        
        case 1:
            if (examine_rgb > 69) /* @epic */ examine_rgb = (int) (examine_rgb - (300.0f * shGetDT()));
            PictureLoadImage(get_gp_data_buf_addr(), 0, -1, -1);
            
            shQzero(&i_pic, sizeof(i_pic));
            
            picture_set_ap(&i_pic, get_gp_data_buf_addr());
            picture_set_alpha(&i_pic, 128);            
            i_pic.r = examine_rgb; i_pic.g = examine_rgb; i_pic.b = examine_rgb; i_pic.status |= 16;
            i_pic.otp = 1;
            PictureDraw(&i_pic);
            
            look_blackscr(1);
            if (!EvSubMessage(t.examine_msg))
                break;
            t.examine_step = 2;
            ScreenEffectFadeStart(1, 0.0f);
            item_main_setup();
            TgsItemPictureLoad();
            
            break;
        
        case 2:
            if (!ScreenEffectFadeCheck())
                break;
            t.examine_step = 0;
            t.main_step = 1;
            break;
    }
}

#line 1778
void examine_file_load(void) {
    layer_adr = (sh2gfw_AREA_HEAD*) (get_gp_data_buf_addr() + ((FcGetFileSize(data_pic_etc_itemmenu2_tex) + 0x7FF) & ~0x7FF));

    switch (t.item_kind) {
        case COIN_OF_SNAKE:
            FcRead(data_pic_item_x_coinsnake_tex, layer_adr);
            return;

        case SH2_ITEM_48:
            FcRead(data_pic_item_x_coinelder_tex, layer_adr);
            return;

        case SH2_ITEM_49:
            FcRead(data_pic_item_x_coinprisoner_tex, layer_adr);
            return;

        case SH2_ITEM_25:
            FcRead(data_pic_item_x_keyclock_tex, layer_adr);
            return;

        case SH2_ITEM_56:
            FcRead(data_pic_item_x_plate_kick_tex, layer_adr);
            return;

        case SH2_ITEM_57:
            FcRead(data_pic_item_x_plate_pig_tex, layer_adr);
            return;

        case SH2_ITEM_58:
            FcRead(data_pic_item_x_plate_female_tex, layer_adr);
            return;

        case APART_GATE_KEY:
            FcRead(data_pic_item_x_keygate_tex, layer_adr);
            return;

        case SH2_ITEM_29:
            FcRead(data_pic_item_x_keynorth_tex, layer_adr);
            return;

        case SH2_ITEM_33:
            FcRead(data_pic_item_x_keyrapis_tex, layer_adr);
            return;

        case SH2_ITEM_38:
            FcRead(data_pic_item_x_keyspiral_tex, layer_adr);
            return;

        case SH2_ITEM_54:
            FcRead(data_pic_item_x_ringlead_tex, layer_adr);
            return;

        case SH2_ITEM_53:
            FcRead(data_pic_item_x_ringopper_tex, layer_adr);
            return;

        case SH2_ITEM_17:
            FcRead(data_pic_item_x_mary_p_tex, layer_adr);
            return;
    }
}

#ifdef HOLY_CANDLE
#line 1836
void examine2_main(void) {
    static PicDraw_Data i_pic; // @ 0x0116DD50
    static int i; // @ 0x0116DD48

    switch (t.examine_step) {
        case 0:

            if (fsSync(1, -1) >= 0)
                t.examine_step++;
            if (t.item_kind == SH2_ITEM_29   || 
                t.item_kind == SH2_ITEM_25   || 
                t.item_kind == SH2_ITEM_38   || 
                t.item_kind == COIN_OF_SNAKE || 
                t.item_kind == SH2_ITEM_48   || 
                t.item_kind == SH2_ITEM_49)
                t.use_item = 7;
            if (t.item_kind == SH2_ITEM_25 && !GET_GAME_FLAG(GAME_FLAG_77))
                
                t.use_item = 0;
            
            if (t.item_kind == APART_GATE_KEY)
                SET_GAME_FLAG(GAME_FLAG_1270);
            break;

        case 1:
        case 2:
            PictureLoadImage(layer_adr, 6, -1, -1);
            
            shQzero(&i_pic, sizeof(PicDraw_Data));
            
            picture_set_ap(&i_pic, layer_adr);
            picture_set_alpha(&i_pic, 128);
            
            i_pic.x0 = (int) (t.box[0][0]) * 16; i_pic.y0 = (int) (t.box[0][1]) * 16; i_pic.x1 = (int) (t.box[2][0]) * 16; i_pic.y1 = (int) (t.box[2][1]) * 16; i_pic.status |= 2;
            i_pic.r = 128; i_pic.g = 128; i_pic.b = 128; i_pic.status |= 16;
            i_pic.otp = 7;
            PictureDraw(&i_pic);
            break;
    }
    #define COL(i) ((lcolor * (3 - i)) + 30)
    for (i = 0; i < 4; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65535, 0);
        (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1); (*spack.pos++) = SCE_GS_TEST_1;
        spkCloseOpenDGiftag(
            SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_SET_PRIM(SCE_GS_PRIM_POINT, 0, 0, 0, 0, 0, 0, 0, 0), SCE_GIF_REGLIST, 7),
            GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2)
        );
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, 0, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(COL(i), COL(i), COL(i), 32, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[0][0] - i), zs(t.box[0][1] - i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[1][0] - i), zs(t.box[1][1] + i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[2][0] + i), zs(t.box[2][1] + i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[3][0] + i), zs(t.box[3][1] - i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[0][0] - i), zs(t.box[0][1] - i), zs(-10), 255);
        spkCloseGiftag();

        spkOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65535, 0);
        (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
        (*spack.pos++) = SCE_GS_TEST_1;
        spkCloseOpenDGiftag(
            SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_SET_PRIM(SCE_GS_PRIM_POINT, 0, 0, 0, 0, 0, 0, 0, 0), SCE_GIF_REGLIST, 7),
            GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2)
        );
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, 0, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(COL(i), COL(i), COL(i), 32, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[0][0] + i), zs(t.box[0][1] + i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[1][0] + i), zs(t.box[1][1] - i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[2][0] - i), zs(t.box[2][1] - i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[3][0] - i), zs(t.box[3][1] + i), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(t.box[0][0] + i), zs(t.box[0][1] + i), zs(-10), 255);
        spkCloseGiftag();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", examine2_main);
/* static */ PicDraw_Data i_pic_2178; // @ 0x0116DD50
/* static */ int i_2179; // @ 0x0116DD48
#endif

void font_print(void) {
    int i;   // r2
    float f; // r20
    int kind;
    f = (1.0 - t.fade) * 128.0 * (1.0 - t.fade);
    fontSetColorDirect((u_char) f, (u_char) f, (u_char) f, 255);
    fontCrushOn();
    if (((t.item_kind != 0) || (t.use_item == 8)) && ((t.step == 1) || (t.step == 6) || (t.step == 9) || (t.step == 8) || (t.step == 11) || (t.step == 12) || (t.step == 13))) {
        if ((t.item_kind != 0) && (t.use_item == 0)) {
            kage_font(msg_buffer, ((((short) t.item_kind - 1) * 2) + 20), 20, 325);
        }
        if (t.use_item == 0) {
            kage_font(msg_buffer, (((t.item_kind - 1) * 2) + 21), 45, 360);
        } else {
            if ((u_char) t.use_item == 1) {
                kage_font(msg_buffer, 16, 45, 360);
                if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, key_config.cancel) != 0)) {
                    t.step       = 1;
                    t.prs_btn    = 1;
                    t.use_item   = 0;
                    t.combine[2] = 0;
                    t.combine[1] = 0;
                    t.combine[0] = 0;
                }
            } else if ((u_char) t.use_item == 2) {
                kage_font(msg_buffer, 17, 45, 360);
                if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, key_config.cancel) != 0)) {
                    t.step       = 1;
                    t.prs_btn    = 1;
                    t.use_item   = 0;
                    t.combine[2] = 0;
                    t.combine[1] = 0;
                    t.combine[0] = 0;
                }
            } else if ((u_char) t.use_item == 3) {
                kage_font(msg_buffer, 18, 45, 360);
                if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, key_config.cancel) != 0)) {
                    t.step       = 1;
                    t.prs_btn    = 1;
                    t.use_item   = 0;
                    t.combine[2] = 0;
                    t.combine[1] = 0;
                    t.combine[0] = 0;
                }
            } else if ((u_char) t.use_item == 4) {
                t.use_item++;
            } else if ((u_char) t.use_item == 5) {
                if (t.item_kind == 21) {
                    t.use_item++;
                } else if (t.item_kind == 28) {
                    t.use_item++;
                } else if (t.item_kind == 40) {
                    t.use_item++;
                } else if (t.item_kind == 74) {
                    t.use_item++;
                } else if (t.item_kind == 26) {
                    t.use_item++;
                } else if (t.item_kind == 20) {
                    kage_font(msg_buffer, 181, 45, 340);
                    if ((shPadTrigger(0, key_config.enter) != 0) && (!t.prs_btn)) {
                        t.use_item++;
                    }
                } else if (t.item_kind == 27) {
                    kage_font(msg_buffer, 175, 45, 340);
                    if ((shPadTrigger(0, key_config.enter) != 0) && (!t.prs_btn)) {
                        t.use_item++;
                    }
                } else {
                    t.use_item++;
                }
            } else if ((u_char) t.use_item == 6) {
                if (t.item_kind == 21) {
                    kage_font(msg_buffer, 168, 45, 340);
                } else if (t.item_kind == 28) {
                    kage_font(msg_buffer, 177, 45, 340);
                } else if (t.item_kind == 40) {
                    kage_font(msg_buffer, 180, 45, 340);
                } else if (t.item_kind == 74) {
                    kage_font(msg_buffer, 183, 45, 340);
                } else if (t.item_kind == 26) {
                    kage_font(msg_buffer, 173, 45, 340);
                } else if (t.item_kind == 20) {
                    kage_font(msg_buffer, 182, 45, 340);
                } else if (t.item_kind == 27) {
                    kage_font(msg_buffer, 174, 45, 340);
                } else {
                    t.step     = 1;
                    t.use_item = 0;
                }
                if (((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, key_config.cancel) != 0)) && (!t.prs_btn)) {
                    t.step     = 1;
                    t.use_item = 0;
                    t.prs_btn  = 1;
                }
            } else if ((u_char) t.use_item == 7) {
                if (t.item_kind == 29) {
                    kage_font(msg_buffer, 178, 45, 340);
                } else if (t.item_kind == 25) {
                    kage_font(msg_buffer, 169, 45, 340);
                } else if (t.item_kind == 38) {
                    kage_font(msg_buffer, 179, 45, 340);
                } else if (t.item_kind == 47) {
                    kage_font(msg_buffer, 170, 45, 340);
                } else if (t.item_kind == 48) {
                    kage_font(msg_buffer, 171, 45, 340);
                } else if (t.item_kind == 49) {
                    kage_font(msg_buffer, 172, 45, 340);
                }
                if (t.step == 1) {
                    t.use_item = 0;
                }
            } else if ((u_char) t.use_item == 8) {
                if (t.item_kind != 0) {
                    t.use_item_kind = t.item_kind;
                }
                if ((t.item_kind == t.use_item_kind) || (t.item_kind == 0)) {
                    if (t.use_item_kind == 1) {
                        fontPrintStrNum(msg_buffer, 190, 45, 360);
                    }
                    if (t.use_item_kind == 2) {
                        fontPrintStrNum(msg_buffer, 191, 45, 360);
                    }
                    if (t.use_item_kind == 3) {
                        fontPrintStrNum(msg_buffer, 192, 45, 360);
                    }
                    if (t.use_item_kind == 4) {
                        fontPrintStrNum(msg_buffer, 193, 45, 360);
                    }
                    if (t.use_item_kind == 5) {
                        fontPrintStrNum(msg_buffer, 194, 45, 360);
                    }
                    if (t.use_item_kind == 6) {
                        fontPrintStrNum(msg_buffer, 195, 45, 360);
                    }
                    if (t.use_item_kind == 7) {
                        fontPrintStrNum(msg_buffer, 196, 45, 360);
                    }
                    if (t.use_item_kind == 8) {
                        fontPrintStrNum(msg_buffer, 197, 45, 360);
                    }
                    if (t.use_item_kind == 9) {
                        fontPrintStrNum(msg_buffer, 198, 45, 360);
                    }
                    if (t.use_item_kind == 10) {
                        fontPrintStrNum(msg_buffer, 199, 45, 360);
                    }
                    if (t.use_item_kind == 11) {
                        fontPrintStrNum(msg_buffer, 200, 45, 360);
                    }
                    if (t.use_item_kind == 12) {
                        fontPrintStrNum(msg_buffer, 201, 45, 360);
                    }
                    if (t.use_item_kind == 13) {
                        fontPrintStrNum(msg_buffer, 202, 45, 360);
                    }
                    if (t.use_item_kind == 14) {
                        fontPrintStrNum(msg_buffer, 203, 45, 360);
                    }
                    if (t.use_item_kind == 15) {
                        fontPrintStrNum(msg_buffer, 204, 45, 360);
                    }
                    if (t.use_item_kind == 16) {
                        fontPrintStrNum(msg_buffer, 205, 45, 360);
                    }
                    if (t.use_item_kind == 17) {
                        fontPrintStrNum(msg_buffer, 206, 45, 360);
                    }
                    if (t.use_item_kind == 18) {
                        fontPrintStrNum(msg_buffer, 207, 45, 360);
                    }
                    if (t.use_item_kind == 19) {
                        fontPrintStrNum(msg_buffer, 208, 45, 360);
                    }
                    if (t.use_item_kind == 21) {
                        fontPrintStrNum(msg_buffer, 209, 45, 360);
                    }
                    if (t.use_item_kind == 22) {
                        fontPrintStrNum(msg_buffer, 218, 45, 360);
                    }
                    if (t.use_item_kind == 30) {
                        fontPrintStrNum(msg_buffer, 210, 45, 360);
                    }
                    if (t.use_item_kind == 40) {
                        fontPrintStrNum(msg_buffer, 211, 45, 360);
                    }
                    if (t.use_item_kind == 63) {
                        fontPrintStrNum(msg_buffer, 212, 45, 360);
                    }
                    if (t.use_item_kind == 64) {
                        fontPrintStrNum(msg_buffer, 213, 45, 360);
                    }
                    if (t.use_item_kind == 65) {
                        fontPrintStrNum(msg_buffer, 214, 45, 360);
                    }
                    if (t.use_item_kind == 71) {
                        fontPrintStrNum(msg_buffer, 215, 45, 360);
                    }
                    if (t.use_item_kind == 73) {
                        fontPrintStrNum(msg_buffer, 216, 45, 360);
                    }
                    if (t.use_item_kind == 74) {
                        fontPrintStrNum(msg_buffer, 217, 45, 360);
                    }
                }
                if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, key_config.cancel) != 0) || (shPadTrigger(0, 2048) != 0) || (shPadTrigger(0, 1024) != 0) || (t.analog[0] == 1) || (t.analog[3] == 1) || (t.prs_btn2 != 0)) {
                    t.use_item = 0;
                }
            } else {
                t.use_item = 0;
            }
        }
    } else if ((item.equip != 0) && ((t.step == 5) || (t.step == 7))) {
        kage_font(msg_buffer, ((((item.equip & 255) - 1) * 2) + 20) & 65535, 20, 325);
        kage_font(msg_buffer, (((item.equip - 1) * 2) + 21) & 65535, 45, 360);
    }
    fontCrushOff();
    i = (u_char) f / 4;
    fontSetColorDirect(i, i, i, 255);
    if (MemoCommandCheck() == 0) {
        fontPrintStrNum(msg_buffer, 11, 391, 428);
    }
    fontSetColorDirect(f, f, f, 255);
    fontPrintStrNum(msg_buffer, 9U, 64, 428);
    fontPrintStrNum(msg_buffer, 10, 240, 428);
    if (MemoCommandCheck() != 0) {
        fontPrintStrNum(msg_buffer, 11, 391, 428);
    }
    fontPrintStrNum(msg_buffer, 12, 69, 50);
    fontPrintStrNum(msg_buffer, 13, 205, 50);
    fontPrintStrNum(msg_buffer, 14, 368, 50);
    if ((t.step == 6) || (t.step == 7)) {
        fontSetColorDirect(f, f, f, 255);
    } else {
        fontSetColorDirect(i, i, i, 255);
    }
    if ((t.step != 7) && (t.step != 5)) {
        kind = command_kind(t.item_kind);
    } else {
        kind = command_kind(item.equip);
    }
    if (t.shelf != 0) {
        switch (kind) { /* switch 5 */
            case 1:     /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 95);
                fontPrintStrNum(msg_buffer, 0U, 360, 120);
                break;
            case 2: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 95);
                fontPrintStrNum(msg_buffer, 0U, 360, 120);
                break;
            case 3: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 95);
                if ((item.equip != t.item_kind) && (t.step != 7) && (t.step != 5)) {
                    fontPrintStrNum(msg_buffer, 7U, 360, 120);
                } else {
                    fontPrintStrNum(msg_buffer, 8U, 360, 120);
                }
                break;
            case 4: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 80);
                if ((item.equip != t.item_kind) && (t.step != 7) && (t.step != 5)) {
                    fontPrintStrNum(msg_buffer, 7U, 360, 105);
                } else {
                    fontPrintStrNum(msg_buffer, 8U, 360, 105);
                }
                fontPrintStrNum(msg_buffer, 1U, 360, 130);
                break;
            case 5: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 95);
                fontPrintStrNum(msg_buffer, 1U, 360, 120);
                break;
            case 6: /* switch 5 */
                if (t.command_light == 0) {
                    fontPrintStrNum(msg_buffer, 19, 350, 95);
                    fontPrintStrNum(msg_buffer, 3U, 350, 120);
                } else {
                    fontPrintStrNum(msg_buffer, 3U, 350, 80);
                    fontPrintStrNum(msg_buffer, 4U, 360, 105);
                    fontPrintStrNum(msg_buffer, 5U, 360, 130);
                }
                break;
            case 7: /* switch 5 */
                if (t.command_volume == 0) {
                    fontPrintStrNum(msg_buffer, 19, 350, 80);
                    fontPrintStrNum(msg_buffer, 3U, 350, 105);
                    fontPrintStrNum(msg_buffer, 2U, 350, 130);
                } else if (t.command_volume == 2) {
                    fontPrintStrNum(msg_buffer, 3U, 350, 80);
                    fontPrintStrNum(msg_buffer, 4U, 360, 105);
                    fontPrintStrNum(msg_buffer, 5U, 360, 130);
                } else {
                    fontPrintStrNum(msg_buffer, 2U, 350, 90);
                }
                break;
            case 8: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 80);
                fontPrintStrNum(msg_buffer, 0U, 360, 105);
                fontPrintStrNum(msg_buffer, 6U, 360, 130);
                break;
            case 9: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 80);
                fontPrintStrNum(msg_buffer, 0U, 360, 105);
                fontPrintStrNum(msg_buffer, 6U, 360, 130);
                break;
            case 10: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 80);
                fontPrintStrNum(msg_buffer, 0U, 360, 105);
                fontPrintStrNum(msg_buffer, 6U, 360, 130);
                break;
            case 11: /* switch 5 */
                fontPrintStrNum(msg_buffer, 19, 360, 80);
                fontPrintStrNum(msg_buffer, 0U, 360, 105);
                fontPrintStrNum(msg_buffer, 6U, 360, 130);
                break;
        }
    } else {
        switch (kind) { /* switch 6 */
            case 1:     /* switch 6 */
                fontPrintStrNum(msg_buffer, 0U, 360, 95);
                fontPrintStrNum(msg_buffer, 15, 360, 120);
                break;
            case 2: /* switch 6 */
                fontPrintStrNum(msg_buffer, 0U, 360, 105);
                break;
            case 3: /* switch 6 */
                if ((item.equip != t.item_kind) && (t.step != 7) && (t.step != 5)) {
                    fontPrintStrNum(msg_buffer, 7U, 360, 105);
                } else {
                    fontPrintStrNum(msg_buffer, 8U, 360, 105);
                }
                break;
            case 4: /* switch 6 */
                if ((item.equip != t.item_kind) && (t.step != 7) && (t.step != 5)) {
                    fontPrintStrNum(msg_buffer, 7U, 360, 95);
                } else {
                    fontPrintStrNum(msg_buffer, 8U, 360, 95);
                }
                fontPrintStrNum(msg_buffer, 1U, 360, 120);
                break;
            case 5: /* switch 6 */
                fontPrintStrNum(msg_buffer, 1U, 360, 105);
                break;
            case 6: /* switch 6 */
                if (t.command_light == 0) {
                    fontPrintStrNum(msg_buffer, 3U, 350, 105);
                } else {
                    fontPrintStrNum(msg_buffer, 3U, 350, 80);
                    fontPrintStrNum(msg_buffer, 4U, 360, 105);
                    fontPrintStrNum(msg_buffer, 5U, 360, 130);
                }
                break;
            case 7: /* switch 6 */
                if (t.command_volume == 0) {
                    fontPrintStrNum(msg_buffer, 3U, 350, 95);
                    fontPrintStrNum(msg_buffer, 2U, 350, 120);
                } else if (t.command_volume == 2) {
                    fontPrintStrNum(msg_buffer, 3U, 350, 80);
                    fontPrintStrNum(msg_buffer, 4U, 360, 105);
                    fontPrintStrNum(msg_buffer, 5U, 360, 130);
                } else {
                    fontPrintStrNum(msg_buffer, 2U, 350, 90);
                }
                break;
            case 8: /* switch 6 */
                fontPrintStrNum(msg_buffer, 0U, 360, 95);
                fontPrintStrNum(msg_buffer, 6U, 360, 120);
                break;
            case 9: /* switch 6 */
                fontPrintStrNum(msg_buffer, 0U, 360, 95);
                fontPrintStrNum(msg_buffer, 6U, 360, 120);
                break;
            case 10: /* switch 6 */
                fontPrintStrNum(msg_buffer, 0U, 360, 80);
                fontPrintStrNum(msg_buffer, 15, 360, 105);
                fontPrintStrNum(msg_buffer, 6U, 360, 130);
                break;
            case 11: /* switch 6 */
                fontPrintStrNum(msg_buffer, 0U, 360, 95);
                fontPrintStrNum(msg_buffer, 6U, 360, 120);
                break;
        }
    }
    fontSetColorDirect((u_char) f, (u_char) f, (u_char) f, 255);
    if ((t.item_kind != 0) && ((command_kind((short) t.item_kind) == 2) || (command_kind((s32) t.item_kind) == 4) || (command_kind((s32) t.item_kind) == 5)) && (!t.prs_btn2)) {
        if (item.number[t.item_kind] < 10) {
            fontPrintDec(item.number[t.item_kind], 236, 289, 3, 0);
            stock_line(31, 0);
        } else if (item.number[t.item_kind] < 100) {
            fontPrintDec(item.number[t.item_kind], 243, 289, 3, 0);
            stock_line(45, 0);
        } else {
            fontPrintDec(item.number[t.item_kind], 250, 289, 3, 0);
            stock_line(59, 0);
        }
    }
    if (!t.prs_btn2) {
        if (t.item_kind == 15) {
            if (item.light_switch != 0) {
                fontPrintStrNum(msg_buffer, 4U, 264, 290);
            } else {
                fontPrintStrNum(msg_buffer, 5U, 261, 290);
            }
            stock_line(50, 0);
        } else if (t.item_kind == 16) {
            if (item.radio_switch != 0) {
                fontPrintStrNum(msg_buffer, 4U, 264, 290);
            } else {
                fontPrintStrNum(msg_buffer, 5U, 261, 290);
            }
            stock_line(50, 0);
        }
    }
    if (t.step != 12) {
        switch (item.equip) {
            case 4:
            case 6:
            case 8:
                break;
            default:
                return;
        }
        if (item.number[item.equip] < 10) {
            fontPrintDec(item.number[item.equip], 262, 160, 3, 0);
            stock_line(31, 1);
            return;
        }
        fontPrintDec(item.number[item.equip], 269, 160, 3, 0);
        stock_line(45, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", kage_font);

#line 2302
void lookline(sceVu0FMATRIX box) {
    #define BOX_ALPHA() ((int) box[0][3])

    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 7), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    
    // disable alpha blending when alpha is full
    if (BOX_ALPHA() == 255)
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_FALSE /* alpha blending */, 0, 0, 0, 0);
    else
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);;

    // draw the item selection box
    (*spack.pos++) = SCE_GS_SET_RGBAQ(48, 96, 240, BOX_ALPHA(), 0);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[0][0]), zs(box[0][1]), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[1][0]), zs(box[1][1]), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[2][0]), zs(box[2][1]), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[3][0]), zs(box[3][1]), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[0][0]), zs(box[0][1]), zs(0), 1);
    spkCloseGiftag();

    // draws two little corners on either side of the diagonal of the rectangle when no button is pressed
    if (BOX_ALPHA() == 255 && !t.prs_btn && !t.prs_btn2) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, SCE_GS_SET_PRIM(SCE_GS_PRIM_POINT, 0, 0, 0, 0, 0, 0, 0, 0), SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_FALSE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(48, 96, 240, BOX_ALPHA(), 0); // @info already checked that it's 255, so redundant
        (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[1][0] - 6.0f), zs(box[1][1] - (box[1][1] - box[0][1]) / 2.0f), zs(0), 1);
        (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[0][0] - 6.0f), zs(box[0][1] - 6.0f), zs(0), 1);
        (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[3][0] - (box[3][0] - box[0][0]) / 2.0f), zs(box[3][1] - 6.0f), zs(0), 1);
        spkCloseGiftag();

        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, SCE_GS_SET_PRIM(SCE_GS_PRIM_POINT, 0, 0, 0, 0, 0, 0, 0, 0), SCE_GIF_REGLIST, 5), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_FALSE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(48, 96, 240, BOX_ALPHA(), 0); // @info already checked that it's 255, so redundant
        (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[1][0] + (box[3][0] - box[0][0]) / 2.0f), zs(box[1][1] + 5.0f), zs(0), 1);
        (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[2][0] + 6.0f), zs(box[2][1] + 5.0f), zs(0), 1);
        (*spack.pos++) = SCE_GS_SET_XYZF2(zs(box[3][0] + 6.0f), zs(box[3][1] + (box[1][1] - box[0][1]) / 2.0f), zs(0), 1);
        spkCloseGiftag();
    }
}

#line 2353
void item_allay(void) {
    int rgb; 

    if (350 < t.allay_time) t.allay_time = 50;
    
    rgb = t.allay_time < 200 ? t.allay_time : 400 - t.allay_time;
    t.allay_time += 30.0f * (6.0f * shGetDT());
   
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(rgb, rgb, rgb, (int) t.allay_abe, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(78), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(78), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(0), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(112), zs(0), zs(0), 1);
    spkCloseGiftag();
    
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(rgb, rgb, rgb, (int) t.allay_abe, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-78), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-78), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(0), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-112), zs(0), zs(0), 1);
    spkCloseGiftag();



    
    spkOpenDGiftag( SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, (int) t.allay_abe * 5, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(78), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(78), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(0), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(78), zs(-11), zs(0), 1);
    spkCloseGiftag();

    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, (int) t.allay_abe * 5, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(112), zs(0), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(95), zs(-11), zs(0), 1);
    spkCloseGiftag();

    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, (int) t.allay_abe * 5, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-78), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-78), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(0), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-78), zs(-11), zs(0), 1);
    spkCloseGiftag();

    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, (int) t.allay_abe * 5, 0);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(-11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(11), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-112), zs(0), zs(0), 1);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-95), zs(-11), zs(0), 1);
    spkCloseGiftag();

}

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", sprite);

void look_command(int gosa) {
    int k;

    t.command_move = move_near(2.0f, 0.2f, 1000.0f * t.command_move, 1000.0f * t.command_cur);
    t.command_move /= 1000.0f;

    for (k = 0; k < 6; k++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, (t.command_abe / 2) * (6 - k), (t.command_abe / 4) * (6 - k), 32, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(90.0f  + (k * k) / 10), zs(k + ((26.0f * t.command_move) + gosa)), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(230.0f - (k * k) / 10), zs(1.0f + (k + ((26.0f * t.command_move) + gosa))), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(90.0f  + (k * k) / 10), zs(26.0f * t.command_move + gosa - k), zs(-10), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(230.0f - (k * k) / 10), zs(26.0f * t.command_move + gosa - k - 1.0f), zs(-10), 255);
        spkCloseGiftag();
    }
}

#line 2497
void look_volume(void) {
    int i;
    
    for (i = 0; i < 16; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2), -65533, 0);
        (*spack.pos++) = SCE_GS_PRIM_SPRITE;
        if (i <= item.radio_volume) {
            (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 176, 0, 32, 0);
        } else {
            (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 48, 0, 32, 0);
        }
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 7 + 105), zs(-120), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 7 + 109), zs(-100), zs(0), 255);
        spkCloseGiftag();
    }
}

#line 2523
void look_hp(void) {
    int z, i, j, j0, j1, r, g, b; // @todo arguments are quite wrong and confusing
    float j_hp, j_max;
    j_hp = sh2jms.player->battle.hp;
    j_max = sh2jms.player->battle.hp_max;
    
    

    #define HP_PERCENT() (j_hp / j_max)
    
    
    t.hp_time1 -= 30.0f * shGetDT();
    t.hp_time2 += 30.0f * ((1.4f + ((1.0f - HP_PERCENT()) / 0.7f)) * shGetDT());
    if (t.hp_time2 > -70.0f) t.hp_time2 = -210.0f;
    t.hp_abe -= 0.034f + ((1.0f - HP_PERCENT()) / 25.0f);
    if (t.hp_abe < 0.0f) {
        t.hp_abe = 1.0f;
        
        t.hp_time1 = t.hp_time2;
    }
    fptosi(2048.0f + t.hp_time2); // @hack?

    t.hp_kodo += shGetDT() / 2.0f;
    if (t.hp_kodo > 0.2f + HP_PERCENT()) {
        t.hp_kodo = 0.0f;
    }
    if ((t.hp_kodo < 0.1f) && (j_hp < (0.8f * j_max)))
        t.hp_abe2 = 1.0f - (6.0f * t.hp_kodo);
    else if ((t.hp_kodo < 0.2f) && (j_hp < (0.8f * j_max))) 
        t.hp_abe2 = (6.0f * t.hp_kodo) - 0.2f;
    else t.hp_abe2 = 1.0f;



    #define COL() 160.0f * t.hp_abe2
    #define COLDIFF()  (t.hp_abe2 * (160.0f * (1.0f - ((2.0f * j_hp) / j_max))))

    
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -MAX_INT + 2, 0);
    
    (*spack.pos++) = 0; (*spack.pos++) = SCE_GS_TEXFLUSH;
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1); (*spack.pos++) = SCE_GS_TEST_1;
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 7), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_TEX0_1, SCE_GS_RGBAQ, SCE_GS_ST, SCE_GS_XYZF2, SCE_GS_ST, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1 /* texture mapping */, 0, 0, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_TEX0(13312, 1, 0, 6, 6, 1, 0, 0, 0, 0, 0, 0);

    if (j_hp < j_max / 2.0f)
        (*spack.pos++) = SCE_GS_SET_RGBAQ(COL(), COL() - COLDIFF(), COL() - COLDIFF(), 160, FLOAT_ONE);
    else
        (*spack.pos++) = SCE_GS_SET_RGBAQ(COL(), COL(), COL(), 160, FLOAT_ONE);
    (*spack.pos++) = SCE_GS_SET_ST(0.0f, 0.0f);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-230), zs(-175), 0, 255);
    (*spack.pos++) = SCE_GS_SET_ST(FLOAT_ONE, FLOAT_ONE);
    (*spack.pos++) = SCE_GS_SET_XYZF(zs(-90), zs(-70), 0, 255);
    spkCloseGiftag();
    
    // randomly create lines on the screen.
    // the lower your health is, the more chances for lines there are, up to 10 per frame.
    for (i = 0; i < 10.0f - 10.0f * HP_PERCENT(); i++) {
        int z;
        srand(t.seed++);
        j = (rand() % 140) - 230;
        j0 = (rand() % 105) - 173;
        j1 = rand() % 105;
        z = rand() % 6;
        
        if (z <= 0) {
            if (j + j1 > -90) j1 = -90 - j; // if their sum is larger than -90, ensure it sums to -90
            spkOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -MAX_INT + 3, 0);
            
            (*spack.pos++) = 0; (*spack.pos++) = SCE_GS_TEXFLUSH;
            spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
            (*spack.pos++) = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1); (*spack.pos++) = SCE_GS_TEST_1;
            spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 7), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_TEX0_1, SCE_GS_RGBAQ, SCE_GS_ST, SCE_GS_XYZF2, SCE_GS_ST, SCE_GS_XYZF2));
            (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1 /* texture mapping */, 0, 0, 0, 0, 0, 0);
            (*spack.pos++) = SCE_GS_SET_TEX0(13312, 1, 0, 6, 6, 1, 0, 0, 0, 0, 0, 0);
            
            
            if (j_hp < j_max / 2.0f)
                (*spack.pos++) = SCE_GS_SET_RGBAQ(COL(), COL() - COLDIFF(), COL() - COLDIFF(), 160, FLOAT_ONE);
            else
                (*spack.pos++) = SCE_GS_SET_RGBAQ(COL(), COL(), COL(), 160, FLOAT_ONE);
            // @weird numbers?
            (*spack.pos++) = SCE_GS_SET_ST(1040187400.0f + 24117248.0f * ((j + 230) / 140.0f), 1040187400.0f + 24117248.0f * ((j0 + 175) / 105.0f));
            (*spack.pos++) = SCE_GS_SET_RGBAQ(zs(j), 0, zs(j0 - 2), 0, 0xff000000);
            (*spack.pos++) = SCE_GS_SET_ST(1040187400.0f + 24117248.0f * (((j + j1) + 230) / 140.0f), 1041236000.0f + 24117248.0f * ((j0 + 175) / 105.0f));
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(j + j1), zs(j0), 0, 255);
            spkCloseGiftag();
        }
    }
}

#line 2627
void stock_line(int leftx, int hoge) {
    int i;

    for (i = 0; i < 2; i++) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
        spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
        spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
        (*spack.pos++) = SCE_GS_PRIM_SPRITE;
        (*spack.pos++) = SCE_GS_SET_RGBAQ(160, 160, 160, 255, 0);
        if (hoge == 0) {
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(50 - (i * leftx)), zs(50), zs(0), 255);
        } else {
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(76 - (i * leftx)), zs(-80), zs(0), 255);
        }
        if (hoge == 0) {
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(38 - (i * leftx)), zs(52), zs(0), 255);
        } else {
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(64 - (i * leftx)), zs(-78), zs(0), 255);
        }
        spkCloseGiftag();
    }
}


#ifdef HOLY_CANDLE
static inline void drawItemImage(int index, int location) {
    // @note scope needed for match
    { short type = t.combine[index]; if (type) TgsItemPitureDraw(type, location, 1072, 128, 100, 0.4f); }
}

#line 2652
void look_combine(void) {
    int i;
    drawItemImage(0, 1920);
    drawItemImage(1, 2720);
    drawItemImage(2, 3520);
    
    if (t.combine[0]) t.combine_abe += 4.0f * shGetDT();
    else t.combine_abe -= 4.0f * shGetDT();
    if (t.combine_abe > 1.0f) t.combine_abe = 1.0f;
    else if (t.combine_abe < 0.0f) t.combine_abe = 0.0f;

    for (i = 0; i < 3; i++) {
        // draw each combined item type
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2), -MAX_INT + 2, 0);
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);;
        (*spack.pos++) = SCE_GS_SET_RGBAQ(16, 48, 16, 80.0f * t.combine_abe, 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 100), zs(45), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 140), zs(95), zs(0), 255);
        spkCloseGiftag();
        
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 7), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2), -MAX_INT + 2, 0);
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        (*spack.pos++) = SCE_GS_SET_RGBAQ(64, 128, 64, (80.0f * t.combine_abe), 0);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 100), zs(45), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 100), zs(95), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 140), zs(95), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 140), zs(45), zs(0), 255);
        (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 50 + 100), zs(45), zs(0), 255);
        spkCloseGiftag();
    }
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", look_combine);
#endif

// ざんぞう (zanzō) afterimage
#line 2691
void look_zanzo(sceVu0FVECTOR za0, sceVu0FVECTOR za1, sceVu0FVECTOR za2, sceVu0FVECTOR za3) {
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65534, 0);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);

    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2, SCE_GS_XYZF2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    if (t.step != 12 && t.step != 13)
        (*spack.pos++) = SCE_GS_SET_RGBAQ(48, 96, 240, (int) za0[3], 0);
    else 
        (*spack.pos++) = SCE_GS_SET_RGBAQ(140, 140, 140, 2 * (int) za0[3], 0);

    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(za0[0]), zs(za0[1]), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(za1[0]), zs(za1[1]), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(za2[0]), zs(za2[1]), zs(0), 255);
    (*spack.pos++) = SCE_GS_SET_XYZF2(zs(za3[0]), zs(za3[1]), zs(0), 255);
    spkCloseGiftag();
}

#line 2711
void look_blackscr(int num) {
    int i;
    int j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (num == 0) {
                spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -65535, 0);
                spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
                spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2));
            } else {
                spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_XYZF2), -MAX_INT, 0);
            }
            (*spack.pos++) = SCE_GS_PRIM_SPRITE;
            (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 0, 0, 128, 0);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 64 - 256), zs(j * 64 - 256), zs(-100), 255);
            (*spack.pos++) = SCE_GS_SET_XYZF(zs(i * 64 - 192), zs(j * 64 - 192), zs(-100), 255);
            spkCloseGiftag();
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", item_fade_in);

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", item_fade_out);

INCLUDE_ASM("asm/nonmatchings/Item/otn_itemmain", item_examine_fade_out);
