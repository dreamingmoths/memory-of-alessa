#include "town_00.h"

s32 func_01F6D680_town_00(void) {
    s32 var_s0;

    var_s0 = 0;
    switch (D_01F6E000_town_00) {                   
    case 0:
        if (func_00190A20(2) != 0) {
            D_01F6E000_town_00 += 1;
        }
        break;
    case 1:
        if (func_0016C1C0(0x1A) != 0) {
            func_001908A0(&D_01F6DF70_town_00, &D_01F6DF78_town_00);
            D_01F6DF74_town_00 = 0;
            D_01F6DF70_town_00 += 1000.0f;
            if (!(D_01F6DF78_town_00 <= 83500.0f)) {
                D_01F6DF78_town_00 = 83500.0f;
            }
            D_01F6E000_town_00 += 1;
        case 2:
            PlayerEventMove(&D_01F6DF70_town_00);
            if (func_00190690() != 0) {
                func_00190AD0();
                var_s0 = 1;
                D_01F6E000_town_00 = 0;
            }
        }
        break;
    }
    return var_s0;
}


s32 func_01F6D7A0_town_00(void) {
    s32 var_s0 = 0;

    switch (D_01F6E000_town_00) {                   /* irregular */
    case 0:
        if (func_00190A20(2) != 0) {
            D_01F6E000_town_00 += 1;
        }
        break;
    case 1:
        if (func_0016C1C0(0x19) != 0) {
            func_001908A0(&D_01F6DF80_town_00, &D_01F6DF88_town_00);
            D_01F6DF84_town_00 = 0;
            D_01F6DF80_town_00 -= 1000.0f;
            D_01F6E000_town_00 += 1;
    case 2:
            PlayerEventMove(&D_01F6DF80_town_00);
            if (func_00190690() != 0) {
                func_00190AD0();
                var_s0 = 1;
                D_01F6E000_town_00 = 0;
            }
        }
        break;
    }
    return var_s0;
}


void func_01F6D8A0_town_00(void) {
    s32 value;
    u8 byte;
    s32 temp_v0;
    s32 count;
    s32* cur;

    count = 0;

    for (cur = &D_01F6DF90_town_00; *cur != 0; cur++) {
        temp_v0 = func_0012FD80(0x200, (s16)*cur);
        if (!temp_v0) {
            continue;
        }

        if (func_001E2110(temp_v0) == 0) {
            count++;
        }

        value = *cur;

        if ((value == 0x101) || (value == 0x102)) {
            continue;
        }

        byte = func_00199770(value);

        switch (byte) {
            case 1:
                break;
            case 2:
                if (!((D_1D31684 >> 3) & 1)) {
                    shCharacter_Manage_Delete(0x200, (u16) *cur);
                }
                break;
            default:
                if (byte < 3) {
                    break;
                }
                if (((D_1D31684 >> 3) & 1) == 0) {
                    // ???
                } else if (3 >= count) {
                    continue;
                }
                shCharacter_Manage_Delete(0x200, (u16) *cur);
        }
    }
    
}


void func_01F6D9D0_town_00(void) {
    D_01F6E000_town_00 = 0;
    D_01F6E008_town_00 = 0;
}


void func_01F6D9F0_town_00(void) {
    D_01F6E008_town_00 = 1;
    func_01F6D8A0_town_00();
}



void func_01F6DA00_town_00(void) {
    if (D_01F6E008_town_00 == 0) {
        func_01F6D9F0_town_00();
    }
    if (((u32) D_1D31684 >> 3) & 1) {
        func_001AF0B0();
        return;
    }
    func_001AED70();
}
