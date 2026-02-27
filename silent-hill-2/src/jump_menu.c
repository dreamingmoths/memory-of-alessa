#include "jump_menu.h"

void JumpMenuPosNormal(void) {
    if (user_data.flg != 0) {
        user_data.flg = 0;
    }
}

void CheckModeJumpDataSet(void) {
    int i;
    float dummy[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    if (jump_after_data_set == 0) {
        jump_after_data_set = 1;
        ItemGet(0x11);
        ItemGet(0x12);
        item.light_switch = 1;
        if ((jump_menu_select != 0xB) && (jump_menu_select != 0xC) && (jump_menu_select != 0x30) && (jump_menu_select != 0xA) && (jump_menu_select != 9) && (jump_menu_select != 8) && (jump_menu_select != 7) && (jump_menu_select != 0xD) && (jump_menu_select != 0)) {
            ItemGet(4);
            i = 0;
            for(i = 0; i < 9; i++) {
                ItemGet(5);
            }
            ItemGet(6);
            i = 0;
            for(i = 0; i < 9; i++) {
                ItemGet(7);
            }
            ItemGet(8);
            i = 0;
            for(i = 0; i < 9; i++) {
                ItemGet(9);
            }
            ItemGet(0xA);
            ItemGet(0xB);
            ItemGet(0xC);
            ItemGet(0xD);
            ItemGet(0xE);
            i = 0;
            for(i = 0; i < 0x10; i++) {
                ItemGet(1);
            }
            for(i = 0; i < 0x10; i++) {
                ItemGet(2);
            }
            ItemGet(0xF);
            ItemGet(0x10);
            game_flag.flag[1] = game_flag.flag[1] | 1;
            game_flag.flag[0] |= 0x01000000;
            game_flag.flag[0] |= 0x02000000;
            game_flag.flag[0] |= 0x04000000;
            game_flag.flag[0] |= 0x08000000;
            game_flag.flag[0] |= 0x10000000;
            game_flag.flag[0] |= 0x20000000;
            game_flag.flag[0] |= 0x40000000;
            game_flag.flag[0] |= 0x80000000;
        }
        switch (jump_menu_select) {                 /* irregular */
        case 0x10:
            game_flag.flag[1] = game_flag.flag[1] & ~1;
            return;
        case 0x6:
            game_flag.flag[0] |= 0x8000;
            game_flag.flag[4] = game_flag.flag[4] | 0x400000;
            game_flag.flag[5] = game_flag.flag[5] | 0x40;
            return;
        case 0x7:
            ItemGet(0xB);
            ItemGet(0x10);
            for(i = 0; i < 0x10; i++) {
                ItemGet(1);
            }
            item.equip = 0xB;
            return;
        case 0x8:
            game_flag.flag[0] |= 0x8000;
            ItemGet(0xB);
            ItemGet(4);
            i = 0;
            for(i = 0; i < 9; i++) {
                ItemGet(5);
            }
            ItemGet(0xC);
            ItemGet(0x10);
            ItemGet(0xF);
            i = 0;
            for(i = 0; i < 0x10; i++) {
                ItemGet(1);
            }
            item.equip = 4;
            return;
        case 0x62:
            game_flag.flag[0] |= 0x400;
            return;
        case 0x9:
            ItemGet(0xB);
            ItemGet(4);
            for(i = 0; i < 9; i++) {
                ItemGet(5);
            }

            ItemGet(6);
            for (i = 0; i < 9; i++) {
                ItemGet(7);
            }
            ItemGet(0xC);
            ItemGet(0x10);
            ItemGet(0xF);
            for(i=0; i < 0x10; i++) {
                ItemGet(1);
            }
            item.equip = 4;
            ItemGet(0x34);
            return;
        case 0xA:
            ItemGet(4);
            for(i = 0; i < 9; i++) {
                ItemGet(5);
            }

            ItemGet(6);
            for(i = 0; i < 9; i++) {
                ItemGet(7);
            }
            ItemGet(8);
            i = 0;
            for(i = 0; i < 9; i++) {
                ItemGet(9);
            }

            ItemGet(0xA);
            ItemGet(0xB);
            ItemGet(0xC);
            ItemGet(0xD);

            for(i = 0; i < 0x10; i++) {
                ItemGet(1);
            }

            ItemGet(0xF);
            ItemGet(0x10);
            item.equip = 4;
            return;
        case 0xB:
            ItemGet(4);

            for(i = 0; i < 3; i++) {
                ItemGet(5);
            }

            ItemGet(0xB);

            for(i = 0; i < 5; i++) {
                ItemGet(1);
            }


            for(i = 0; i <= 0; i++) {
                ItemGet(2);
            }
            ItemGet(0x10);

            item.equip = 4;
            game_flag.flag[0] |= 0x02000000;
            game_flag.flag[2] = game_flag.flag[2] | 4;
            game_flag.flag[1] = game_flag.flag[1] | 8;
            game_flag.flag[1] = game_flag.flag[1] | 0x100;
            game_flag.flag[1] = game_flag.flag[1] | 0x200;
            game_flag.flag[1] = game_flag.flag[1] | 0x800;
            game_flag.flag[1] = game_flag.flag[1] | 0x20000;
            game_flag.flag[2] = game_flag.flag[2] | 8;
            playing.riddle_level = 0;
            return;
        case 0xC:
            ItemGet(4);
            i = 0;
            for(i = 0; i < 3; i++) {
                ItemGet(5);
            }
            ItemGet(6);
            i = 0;
            for(i = 0; i <= 0; i++) {
                ItemGet(7);
            }
            ItemGet(0xB);
            ItemGet(0xC);
            i = 0;
            for(i = 0; i < 8; i++) {
                ItemGet(1);
            }
            i = 0;
            for(i = 0; i < 2; i++) {
                ItemGet(2);
            }
            ItemGet(0xF);
            ItemGet(0x10);
            item.equip = 4;
            game_flag.flag[0] |= 0x10000000;
            game_flag.flag[1] = game_flag.flag[1] | 8;
            playing.riddle_level = 0;
            return;
        case 0x13:
        case 0x1F:
        case 0x21:
        case 0x23:
        case 0x25:
            game_flag.flag[7] = game_flag.flag[7] | 0x08000000;
            game_flag.flag[1] = game_flag.flag[1] | 0x800;
            return;
        case 0x27:
            game_flag.flag[0] |= 0x1000;
            return;
        case 0x2B:
            game_flag.flag[2] = game_flag.flag[2] | 0x80000000;
            return;
        case 0x2F:
            ItemGet(0x19);
            game_flag.flag[2] = game_flag.flag[2] | 0x20;
            return;
        case 0x30:
            game_flag.flag[2] = game_flag.flag[2] | 0x10;
            game_flag.flag[0] |= 0x80;
            return;
        case 0x36:
            ItemGet(0x2E);
            return;
        case 0x37:
            ItemGet(0x1B);
            return;
        case 0x34:
            game_flag.flag[2] = game_flag.flag[2] | 8;
            return;
        case 0x3F:
            game_flag.flag[4] = game_flag.flag[4] | 0x400000;
            return;
        case 0x40:
            game_flag.flag[4] = game_flag.flag[4] | 0x400000;
            game_flag.flag[4] = game_flag.flag[4] | 0x01000000;
            game_flag.flag[0] |= 0x8000;
            return;
        case 0x45:
            game_flag.flag[4] = game_flag.flag[4] | 0x400000;
            game_flag.flag[0] |= 0x8000;
            game_flag.flag[5] = game_flag.flag[5] | 4;
            game_flag.flag[5] = game_flag.flag[5] | 0x10;
            game_flag.flag[5] = game_flag.flag[5] | 0x40;
            return;
        case 0x46:
        case 0x49:
            game_flag.flag[0] |= 0x8000;
            return;
        case 0x4E:
            ItemGet(0x22);
            return;
        case 0x52:
            ItemGet(0x20);
            ItemGet(0x21);
            return;
        case 0x58:
            ItemGet(0x23);
            return;
        case 0x59:
            game_flag.flag[0] |= 0x8000;
            ItemGet(0x35);
            ItemGet(0x36);
            return;
        case 0x5F:
            game_flag.flag[0] |= 0x8000;
            return;
        case 0x3C:
            ItemGet(0x1C);
            return;
        case 0x39:
            game_flag.flag[2] = game_flag.flag[2] | 0x200000;
            return;
        case 0x3A:
            game_flag.flag[3] = game_flag.flag[3] | 0x2000;
            return;
        case 0x3B:
            ItemGet(0x2F);
            ItemGet(0x30);
            ItemGet(0x31);
            return;
        case 0x3D:
            ItemGet(0x1D);
            return;
        case 0x3E:
            game_flag.flag[4] = game_flag.flag[4] | 0x40000;
            return;
        case 0x42:
            game_flag.flag[4] = game_flag.flag[4] | 0x400000;
            game_flag.flag[5] = game_flag.flag[5] | 4;
            game_flag.flag[4] = game_flag.flag[4] | 0x04000000;
            game_flag.flag[4] = game_flag.flag[4] | 0x10000000;
            game_flag.flag[4] = game_flag.flag[4] | 0x20000000;
            return;
        case 0x43:
            game_flag.flag[0] |= 0x8000;
            return;
        case 0x53:
            ItemGet(0x32);
            ItemGet(0x33);
            return;
        case 0x4F:
            playing.riddle_level = 0;
            ItemGet(0x22);
            return;
        case 0x50:
        case 0x5B:
            game_flag.flag[0] |= 0x8000;
            return;
        case 0x55:
            game_flag.flag[6] = game_flag.flag[6] | 0x400000;
            return;
        case 0x5D:
            game_flag.flag[7] = game_flag.flag[7] | 0x100;
            return;
        case 0x56:
            game_flag.flag[6] = game_flag.flag[6] | 0x40000000;
            return;
        case 0x61:
            game_flag.flag[7] = game_flag.flag[7] | 0x08000000;
            game_flag.flag[4] = game_flag.flag[4] | 0x400000;
            ItemGet(0x37);
            return;
        case 0x63:
            game_flag.flag[0] |= 0x400;
            return;
        case 0x65:
            game_flag.flag[8] = game_flag.flag[8] | 0x200;
            return;
        case 0x66:
            ItemGet(0x34);
            return;
        case 0x67:
            ItemGet(0x26);
            return;
        case 0x68:
            game_flag.flag[8] = game_flag.flag[8] | 0x40000;
            return;
        case 0x6B:
            ItemGet(0x38);
            ItemGet(0x39);
            ItemGet(0x3A);
            return;
        case 0x6C:
            ItemGet(0x3C);
            ItemGet(0x3D);
            ItemGet(0x3B);
            return;
        case 0x72:
            ItemGet(0x3E);
            return;
        case 0x79:
            ItemGet(0x27);
            return;
        case 0x81:
            ItemGet(0x42);
            ItemGet(0x40);
            ItemGet(0x41);
            return;
        case 0x84:
            ItemGet(0x11);
            ItemGet(0x12);
            ItemGet(0x13);
            ItemGet(0x15);
            ItemGet(0x16);
            ItemGet(0x1E);
            ItemGet(0x28);
            ItemGet(0x3F);
            ItemGet(0x40);
            ItemGet(0x41);
            ItemGet(0x47);
            ItemGet(0x49);
            ItemGet(0x4A);
            game_flag.flag[0xC] = game_flag.flag[0xC] | 0x80000000;
            return;
        case 0x82:
            ItemGet(0x2C);
            return;
        case 0x83:
            ItemGet(0x3F);
            return;
        case 0x88:
            ItemGet(0x2D);
            return;
        case 0x89:
            ItemGet(0x14);
            return;
        case 0x86:
            ItemGet(0x43);
            ItemGet(0x2B);
            return;
        case 0x92:
            game_flag.flag[0xF] = game_flag.flag[0xF] | 8;
            game_flag.flag[0xF] = game_flag.flag[0xF] | 0x10;
            ItemGet(0x46);
            ItemGet(0x45);
            return;
        case 0x93:
            game_flag.flag[0] |= 0x400;
            item.flag[0] &= 0xFFFF7FFF;
            return;
        case 0x8B:
            ItemGet(0x16);
            game_flag.flag[0] |= 0x800;
            /* fallthrough */
        case 0x8C:
        case 0x8E:
        case 0x8F:
        case 0x91:
            item.flag[0] &= 0xFFFF7FFF;
            break;
        }
    }
}