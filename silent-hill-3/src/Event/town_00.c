#include "town_00.h"

int func_01F6D680_town_00() {
    int var_s0  = 0;

    switch (state_town_00.x) {                   
    case 0:
        if (func_00190A20(2) != 0) {
            state_town_00.x += 1;
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
            state_town_00.x += 1;
        case 2:
            PlayerEventMove(&D_01F6DF70_town_00);
            if (func_00190690() != 0) {
                func_00190AD0();
                var_s0 = 1;
                state_town_00.x = 0;
            }
        }
        break;
    }
    return var_s0;
}


int func_01F6D7A0_town_00() {
    int var_s0 = 0;

    switch (state_town_00.x) {
    case 0:
        if (func_00190A20(2) != 0) {
            state_town_00.x += 1;
        }
        break;
    case 1:
        if (func_0016C1C0(0x19) != 0) {
            func_001908A0(&D_01F6DF80_town_00, &D_01F6DF88_town_00);
            D_01F6DF84_town_00 = 0;
            D_01F6DF80_town_00 -= 1000.0f;
            state_town_00.x += 1;
    case 2:
            PlayerEventMove(&D_01F6DF80_town_00);
            if (func_00190690() != 0) {
                func_00190AD0();
                var_s0 = 1;
                state_town_00.x = 0;
            }
        }
        break;
    }
    return var_s0;
}


void func_01F6D8A0_town_00() {
    int value;
    u_char action_level;
    SubCharacter* scp;
    int count = 0;

    int* cur;
    for (cur = &D_01F6DF90_town_00; *cur != 0; cur++) {
        scp = shCharacterGetSubCharacter(DOUBLE_HEAD_CHARA_ID, (short) *cur);
        if (!scp) {
            continue;
        }

        if (func_001E2110(scp) == 0) {
            count++;
        }

        value = *cur;

        if ((value == 0x101) || (value == 0x102)) {
            continue;
        }

        action_level = GetActionLevel(value);

        switch (action_level) {
            case 1:
                break;
            case 2:
                if (!GET_BIT(D_1D31684, 3)) {
                    shCharacter_Manage_Delete(DOUBLE_HEAD_CHARA_ID, (u_short) *cur);
                }
                break;
            default:
                if (action_level < 3) {
                    break;
                }
                if (GET_BIT(D_1D31684, 3) == 0) {
                    // ???
                } else if (3 >= count) {
                    continue;
                }
                shCharacter_Manage_Delete(DOUBLE_HEAD_CHARA_ID, (u_short) *cur);
        }
    }
    
}


void func_01F6D9D0_town_00() {
    state_town_00.x = 0;
    state_town_00.z = 0;
}


void func_01F6D9F0_town_00() {
    state_town_00.z = 1;
    func_01F6D8A0_town_00();
}



void func_01F6DA00_town_00() {
    if (state_town_00.z == 0) {
        func_01F6D9F0_town_00();
    }
    if (GET_BIT(D_1D31684, 3)) {
        func_001AF0B0();
        return;
    }
    func_001AED70();
}
