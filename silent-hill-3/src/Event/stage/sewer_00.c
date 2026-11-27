#include "sewer_00.h"

int func_01F6D680_sewer_00() {
    int ret;
    float t;
    Q data0;
    Q data1;

    switch (D_01F6FE00_sewer_00) {
        case 0:
            func_00316C50(0);
            func_0016ECE0(2);
            func_001C2290(2, 0.0f);
            D_01F6FE00_sewer_00++;
    }

    ret = func_0016C540(D_01F6FB60_sewer_00, D_01F6FBC0_sewer_00);
    t   = func_001643C0();

    if (t < 64.0f) {
        func_0013D250(0, D_01F6F8F0_sewer_00, 1.0f);
    }

    switch (D_01F6FE00_sewer_00) {
        case 1:
            if (t >= 65.0f) {
                func_0013D250(0, D_01F6F930_sewer_00, 1.0f);
                D_01F6FE00_sewer_00++;
            }

            break;
        case 2:
            if (t >= 98.0f) {
                func_0013D250(0, D_01F6F9A0_sewer_00, 1.0f);
                D_01F6FE00_sewer_00++;
            }
    }

    if (func_001646F0() == 2) {
        data0 = D_01F6FBE0_sewer_00;
        data1 = D_01F6FE10_sewer_00;
        func_001DA020(1, &data0, &data1);
    }

    if (ret) {
        func_0013D280(0);
        D_01F6FE00_sewer_00 = 0;
        func_001C2290(5, 0.8f);
    }

    return ret;
}

int func_01F6D870_sewer_00() {
    switch (D_01F6FE00_sewer_00) {
        case 0:
            func_00190A20(2);
            func_0016CD00(D_01F6FBF0_sewer_00);
            func_001C2290(3, 0.8f);
            D_01F6FE00_sewer_00 = 1;
            /* fallthrough */
        case 1:
            if (!func_001C2580(2)) {
                return 0;
            }

            D_01F6FE00_sewer_00 = 2;
            func_001C2290(5, 0.8f);
            /* fallthrough */
        case 2:
            if (!func_0016BED0(195, 34)) {
                return 0;
            }

            D_01F6FE00_sewer_00 = 3;
            func_001C2290(5, 0.8f);
            /* fallthrough */
        case 3:
            func_00190A20(0);
    }

    D_01F6FE00_sewer_00 = 0;

    return 1;
}

int func_01F6D980_sewer_00() {
    switch (D_01F6FE60_sewer_00) {
        case 0:
            func_0016C3C0();
            func_00190A20(2);
            D_01F6FE60_sewer_00++;
            func_00317420(52);
            SeCall(11041, 1.0f, 0.0f);
            /* fallthrough */
        case 1:
            if (!func_0016C1C0(69)) {
                return 0;
            }

            func_0016C3C0();
            D_01F6FE60_sewer_00++;
            SeCall(11041, 1.0f, 0.0f);
            func_00317490(52, 0.2f);
            /* fallthrough */
        case 2:
            if (!func_0016C1C0(70)) {
                return 0;
            }

            func_00190A20(0);
            D_01F6FE60_sewer_00 = 0;
            func_003174B0(0.2f);
    }

    return 1;
}

int func_01F6DAB0_sewer_00() {
    sceVu0FMATRIX sp10;
    SubCharacter* heather;

    while (1) {
        switch (D_01F6FE20_sewer_00) {
            case 0:
                func_00190A20(2);

                if (GET_BIT(D_1D31664, 2)) {
                    func_001C2290(2, 0.0f);
                    D_01F6FE20_sewer_00 = 3;
                    continue;
                }

                D_01F6FE20_sewer_00++;
                /* fallthrough */
            case 1:
                if (!func_0016C1C0(25)) {
                    return 0;
                }

                func_0016C3C0();

                if (!func_0016CB70()) {
                    if (GET_BIT(D_1D31660, 21)) {
                        func_001C2290(3, 0.8f);
                        D_01F6FE20_sewer_00 = 3;
                        func_0013D250(0, D_01F6F9F0_sewer_00, 1.0f);
                        SET_BIT(D_1D31664, 2);
                        func_00316C50(0);
                        SeCall(12800, 1.0f, 0.0f);
                        D_01F6FE30_sewer_00 = func_0016E0F0();
                    } else {
                        D_01F6FE20_sewer_00++;
                    }
                } else {
                    D_01F6FE20_sewer_00 = 4;
                }

                continue;
            case 2:
                if (GET_BIT(D_1D31660, 24)) {
                    if (!func_0016C1C0(27)) {
                        return 0;
                    }

                    func_0016C3C0();
                    D_01F6FE20_sewer_00 = 4;
                } else {
                    if (!func_0016C1C0(26)) {
                        return 0;
                    }

                    func_0016C3C0();
                    D_01F6FE20_sewer_00 = 4;
                }

                continue;
            case 3:
                if (!func_0016C540(D_01F6FC00_sewer_00, D_01F6FC60_sewer_00)) {
                    D_01F6FE28_sewer_00 = 1;
                    heather             = shCharacterGetSubCharacter(HEATHER_CHARA_KIND, -1);
                    func_001DC9E0(heather, 0);

                    if (func_001643C0() >= 10.0f) {
                        func_0013D250(0, D_01F6FA30_sewer_00, 1.0f);
                    }

                    return 0;
                }

                heather = shCharacterGetSubCharacter(HEATHER_CHARA_KIND, -1);
                func_001DC9E0(heather, 1);
                func_0016D0E0(12802, D_01F6FE58_sewer_00);
                D_01F6FE58_sewer_00 = -1;
                func_0016E400(34, D_01F6FE30_sewer_00);
                func_0013D280(0);
                SET_BIT(D_1D31644, 26);
                SET_BIT(D_1D31660, 20);
                sceVu0UnitMatrix(sp10);
                sp10[3][0] = 0.0f;
                sp10[3][1] = 0.0f;
                sp10[3][2] = 0.0f;
                sp10[3][3] = 0.0f;
                func_001C2A80(1, sp10);
                func_001C2A80(2, sp10);
                func_001C2A80(3, sp10);
                D_01F6FE20_sewer_00 = 4;
                func_001C2290(5, 0.8f);
                /* fallthrough */
            case 4:
                D_01F6FE28_sewer_00 = 0;
                func_0016C3C0();
                func_00190A20(0);
                D_01F6FE20_sewer_00 = 0;

                return 1;
        }
    }
}

int func_01F6DE40_sewer_00() {
    int ret = 0;

    switch (D_01F6FE00_sewer_00) {
        case 0:
            func_00190A20(2);
            /* fallthrough */
        case 1:
            ret = func_0016BED0(81, 42);

            if (ret) {
                func_00190A20(0);
                D_01F6FE00_sewer_00 = 0;
            }
    }

    return ret;
}

void func_01F6DEC0_sewer_00() {
    int var_s0 = 0;
    int* temp;
    SubCharacter* numb_body;

    for (temp = D_01F6FC80_sewer_00; temp[0]; temp++) {
        numb_body = shCharacterGetSubCharacter(NUMB_BODY_CHARA_KIND, temp[0]);

        if (numb_body != NULL) {
            if (!func_001E2110(numb_body)) {
                var_s0++;
            }

            if (temp[0] != 143 && temp[0] != 144) {
                if (!GET_BIT(D_1D31660, 18)) {
                    shCharacter_Manage_Delete(NUMB_BODY_CHARA_KIND, temp[0]);
                } else if (GetActionLevel() >= 2 && var_s0 > 3) {
                    shCharacter_Manage_Delete(NUMB_BODY_CHARA_KIND, temp[0]);
                }
            }
        }
    }

    var_s0 = 0;

    for (temp = D_01F6FC98_sewer_00; temp[0]; temp++) {
        numb_body = shCharacterGetSubCharacter(NUMB_BODY_CHARA_KIND, temp[0]);

        if (numb_body != NULL) {
            if (!func_001E2110(numb_body)) {
                var_s0++;
            }

            if (temp[0] != 142) {
                if (!GET_BIT(D_1D31660, 18)) {
                    shCharacter_Manage_Delete(NUMB_BODY_CHARA_KIND, temp[0]);
                } else if (GetActionLevel() >= 3 && var_s0 > 1) {
                    shCharacter_Manage_Delete(NUMB_BODY_CHARA_KIND, temp[0]);
                }
            }
        }
    }
}

void func_01F6E060_sewer_00() {
    D_01F6FE50_sewer_00 = 0;
    D_01F6FE00_sewer_00 = 0;

    switch ((short) RoomName()) {
        case 0x47:
            func_001BE4B0(0);
            func_0013D280(0);
            break;
        case 0x54:
            D_01F6FE20_sewer_00 = 0;
            D_01F6FE28_sewer_00 = 0;

            if (GET_BIT(D_1D316AC, 28)) {
                func_00190A20(0);
                UNSET_BIT(D_1D316AC, 28);
            }

            break;
        case 0x55:
            D_01F6FE60_sewer_00 = 0;
            /* fallthrough */
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x56:
            break;
    }
}

void func_01F6E130_sewer_00() {
    sceVu0FMATRIX sp10;
    float sp50[4];

    D_01F6FE50_sewer_00 = 1;

    switch ((short) RoomName()) {
        case 0x47:
            func_001433A0(shCharacterGetSubCharacter(BG_SYA_CHARA_KIND, 130), 10019, 0);
            break;
        case 0x4F:
            func_01F6DEC0_sewer_00();
            break;
        case 0x54:
            D_01F6FE20_sewer_00 = 0;
            D_01F6FE28_sewer_00 = 0;
            sceVu0UnitMatrix(sp10);
            sp10[3][0] = 0.0f;
            sp10[3][1] = 0.0f;
            sp10[3][2] = 0.0f;
            sp10[3][3] = 0.0f;
            func_001C2A80(1, sp10);
            func_001C2A80(2, sp10);
            func_001C2A80(3, sp10);

            if (!GET_BIT(D_1D31644, 26)) {
                sp50                = D_01F6FCB0_sewer_00;
                D_01F6FE58_sewer_00 = func_0016D240(1.0f, 1000.0f, 12802, sp50, 0, 0);
            } else {
                D_01F6FE58_sewer_00 = -1;
            }

            break;
        case 0x55:
            D_01F6FE60_sewer_00 = 0;
            /* fallthrough */
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x56:
            break;
    }
}

void func_01F6E270_sewer_00() {
    sceVu0FMATRIX* sp30[4];
    sceVu0FMATRIX* sp40[4];
    sceVu0FMATRIX sp50;
    sceVu0FVECTOR sp90;
    float spA0[4];
    SubCharacter* bg_sya;
    sceVu0FVECTOR* p_sp80;
    int temp_t0;

    if (!D_01F6FE50_sewer_00) {
        func_01F6E130_sewer_00();
    }

    switch ((short) RoomName()) {
        case 0x47:
            if (GET_BIT(D_1D31644, 7)) {
                sp90 = D_01F6FE40_sewer_00;
                func_0016CA40(1);
                p_sp80     = sp50[3];
                *p_sp80[0] = 0.0f;
                sp50[3][1] = 0.0f;
                sp50[3][2] = 0.0f;
                sp50[3][3] = 0.0f;
                func_001C2A80(1, sp50);
                bg_sya = shCharacterGetSubCharacter(BG_SYA_CHARA_KIND, 130);
                func_0016CBD0(sp30, sp40, 4);
                shMatrixCopy(sp50, sp30[0]);
                shVectorCopy(&bg_sya->pos, p_sp80);
                func_0016CC50(521, 0, sp30[0], sp90);
                shVectorCopy(&bg_sya->rot, sp90);
                func_001DC9E0(bg_sya, 1);
            }

            break;
        case 0x4E:
            if (!GET_BIT(D_1D31660, 15)) {
                func_0016CA40(2);
            }

            if (!GET_BIT(D_1D31660, 16)) {
                func_0016CA40(1);
            }

            break;
        case 0x50:
            if (!GET_BIT(D_1D31660, 18)) {
                func_0016CA40(9);
            }

            break;
        case 0x51:
            if (func_00190950() == 1) {
                clAddDynamicWall(D_01F6F850_sewer_00);
            }

            break;
        case 0x54:
            if (!GET_BIT(D_1D31660, 21)) {
                func_0016CA40(1);
            } else {
                func_0016CA40(2);
            }

            if (!D_01F6FE28_sewer_00) {
                func_0016CA40(3);
            }

            temp_t0 = D_01F6FE58_sewer_00;

            if (temp_t0 != -1) {
                spA0 = D_01F6FCC0_sewer_00;
                func_0016D170(12802, spA0, 0, 0, 1.0f, 1000.0f, temp_t0);
            }

            /* fallthrough */
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4F:
        case 0x52:
        case 0x53:
        case 0x55:
        case 0x56:
            break;
    }
}
