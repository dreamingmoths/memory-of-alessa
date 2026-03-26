#include "amusement_01.h"
#include "Font/font.h"

int func_01F6D680_amusement_01(void) {
    int ret;

    // @todo is there a cleaner match?
    switch (D_01F74C88_amusement_01)
        case 0: {
            func_001C2290(2, 0.8f);
            D_01F74C98_amusement_01 = 45.0f;
            D_01F74CA0_amusement_01 = 150.0f;
            D_01F74C88_amusement_01++;
        }

    ret = func_0016C540(&D_01F74510_amusement_01, &D_01F74570_amusement_01);
    func_01F703B0_amusement_01(D_01F74C98_amusement_01, D_01F74CA0_amusement_01);

    switch (D_01F74C88_amusement_01)
        case 1:
            if (func_001643C0() > 438.0f) {
                D_01F74C98_amusement_01 = 50.0f;
                D_01F74CA0_amusement_01 = 100.0f;
                D_01F74C88_amusement_01++;
            }

    if (ret != 0) {
        D_01F74C88_amusement_01 = 0;
    }

    return ret;
}

void func_01F6D7A0_amusement_01(void) {
    func_0016C540(&D_01F74590_amusement_01, &D_01F745F0_amusement_01);
}

int func_01F6D7C0_amusement_01(void) {
    int audioIsPlaying;

    D_1D3169C |= 0x1000;

    // noping this function prevents the audio from playing
    audioIsPlaying = func_0016CF80(12, 50, &D_01F713D0_amusement_01);


    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }

    return audioIsPlaying;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6D840_amusement_01);

void func_01F6DC40_amusement_01(void) {
    func_001C0EB0(func_01F6DC70_amusement_01, 90, 1);
    D_01F74CB0_amusement_01 = 0;
}

static void func_01F6DC70_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4) {
    vec_copy(arg0, &D_01F74680_amusement_01);
    *arg1 = 1;
    vec_copy(arg2, &D_01F74670_amusement_01);
    *arg3 = 0;
    *arg4 = 0;
}

void func_01F6DCB0_amusement_01(void) {
    func_001C0EB0(func_01F6DCF0_amusement_01, 999999, 1);
    D_01F74CB0_amusement_01 = 0;
}

static void func_01F6DCF0_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4) {
    sceVu0FVECTOR sp60;

    func_0018FE60((__int128*) &sp60);
    sp60[1] += -700.0f;
    vec_copy(arg0, &D_01F74690_amusement_01[D_01F74CB0_amusement_01]);
    *arg1 = 1;
    if (D_01F74CB0_amusement_01 != 2) {    
        vec_copy(arg2, sp60);
    } else {
        vec_copy(arg2, D_01F74670_amusement_01);
    }
    *arg3 = 1;
    *arg4 = 0;
}

void func_01F6DDC0_amusement_01(void) {
    D_01F74CB0_amusement_01++;
}

int func_01F6DDE0_amusement_01(void) {
    float limit;
    int ret = 0;
    int i;
    float* cur;
    int state = D_01F74C88_amusement_01;

    switch (state) {
        case 0:
            func_01F6DC40_amusement_01();
            D_01F74D98_amusement_01 = 0;
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            for (i = 0; cur = D_01F74610_amusement_01[i], cur[0] != 0.0f; i++) {
                limit = D_01F74D98_amusement_01;
                if (cur[0] <= limit && cur[1] > limit) {
                    func_0016CA40(1);
                }
            }
            D_01F74D98_amusement_01++;
            if (D_01F74D98_amusement_01 < 90) {
                break;
            }
        case 2:
            ret = 1;
            D_01F74C88_amusement_01 = 0;
    }

    return ret;
}

int func_01F6DF10_amusement_01(void) {
    int ret;
    f32 angle;
    SubCharacter* danny;
    ret = 0;

    // create Danny
    danny = shCharacterGetSubCharacter(DANNY_CHARA_ID, DANNY_ID);

    switch (D_01F74C88_amusement_01) {
        case 0:
            func_001DC9E0(danny, 1); // sets some status bit
            D_01F74C88_amusement_01++;
            func_001433A0(danny, 10015, 0); // sets an animation
            danny->rot.y = PI;
            func_001C2A70(1, 0.0f); // initializes a matrix?
            danny->pos.x = 18750.0f;
            danny->pos.z = 101000.0f;
            D_01F74D90_amusement_01 = 0;
            /* fallthrough */
        case 1:
            if (GET_BIT(D_1D3169C, 0x18)) {
                D_1D3169C |= 0x1000;
                func_001433A0(danny, 10016, 0);
                func_0019A940();
                D_01F74C88_amusement_01++;
        case 2:
                if (func_0019A9B0(0.2f) != 0) {
                    func_0015DCD0(1.0f, 10000.0f, 15303, &danny->pos.x, 0, 0);
                    D_01F74C88_amusement_01++;
        case 3:
                    angle = (&D_01F746C0_amusement_01)[D_01F74D90_amusement_01];
                    if (angle != 0.0f) {
                        func_001C2A70(1, TO_RAD(angle));
                        D_01F74D90_amusement_01++;
                    }
                    if (func_001DD9F0(danny) != 0) {
                        func_001433A0(danny, 10017, 0);
                        func_0019A940();
                        D_01F74C88_amusement_01++;
                    case 4:
                        if (func_0019A9B0(1.5f) != 0) {
                            D_01F74C88_amusement_01++;
                        }
                    }
                }
            }
            break;
        default:
            ret = func_0016CF80(0xE, 0x45, &D_01F71460_amusement_01);
            if (ret != 0) {
                D_1D3169C &= ~0x1000;
                func_0016CF70();
                D_01F74C88_amusement_01 = 0;
            }
        }
    return ret;
}

int func_01F6E1A0_amusement_01(void) {
    // entering the room with the metal spikes trap
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(15, 82, &D_01F714A0_amusement_01);

    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }

    return audioIsPlaying;
}

int func_01F6E220_amusement_01(void) {
    // going under the spikes
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(16, 86, &D_01F714D0_amusement_01);

    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }

    return audioIsPlaying;
}

void func_01F6E2A0_amusement_01(void) {
    SubCharacter* heather;
    sceVu0FMATRIX matrix;
    sceVu0FVECTOR vec0;
    sceVu0FVECTOR vec1;
    float heather_x;
    float heather_z;
    int needs_crouch;
    float y_0;
    float y_2;
    float y_1;
    float y_3;
    float t;

    // controls the spikes
    switch (D_01F74C90_amusement_01) {
        case 0:
            D_01F74DC0_amusement_01 = 0.0f;
            D_01F74C90_amusement_01 = 1;
            D_1D3169C |= 0x1000;

            // this function seems to stop the previous audio.
            // noping it makes the audios overlap
            func_01F70750_amusement_01();

            // spikes falling noise
            SeCall(1.0f, 0.0f, 0x3BCA);
            /* fallthrough */

        case 1:
            // if playing on hard or extreme, you need to crouch to survive.
            // dunno what func_00190950 does though.
            if (func_00190950() != 1 && GetActionLevel() >= 3) {
                needs_crouch = 1;
            } else { 
                needs_crouch = 0;
            }

            D_01F74DC0_amusement_01 += 150.0f * (9.8f * shGetDT());

            // get matrix
            func_001C2AE0(1, &matrix);

            y_0 = matrix[3][1] + D_01F74DC0_amusement_01;
            matrix[3][1] = y_0;

            if (!(y_0 <= -1200.0f)) {
                if (needs_crouch == 0) {
                    matrix[3][1] = -1200.0f;
                } else {
                    matrix[3][1] = -1000.0f;
                }
            }
            
            // set matrix
            func_001C2A80(1, &matrix);

            // get matrix
            func_001C2AE0(2, &matrix);

            y_1 = matrix[3][1] + D_01F74DC0_amusement_01;
            matrix[3][1] = y_1;
            
            if (!(y_1 <= -1200.0f)) {
                if (needs_crouch != 0) {
                    matrix[3][1] = -1000.0f;
                    D_01F74C90_amusement_01 = 3;
                    func_001BE4B0(5);
                    func_0016CF70();
                } else {
                    matrix[3][1] = -1200.0f;
                    D_01F74C90_amusement_01 = 2;
                    D_01F74DB0_amusement_01 = 0.0f;
                    D_01F74DB8_amusement_01 = 0.0f;
                    func_001BE4B0(5);
                    func_0016CF70();
                    func_01F6E220_amusement_01();
                }
            }
            // set matrix
            func_001C2A80(2, &matrix);

            return;

        case 3:
            heather = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
            heather_x = heather->pos.x;
            vec1[0] = heather_x;
            vec0[0] = heather_x;
            heather_z = heather->pos.z;
            vec1[2] = heather_z;
            vec0[2] = heather_z;
            vec0[1] = heather->pos.y - 250.0f;
            vec1[1] = heather->pos.y;
            func_001E0130(NULL, &vec0, &vec1, 0xDC);
            D_01F74C90_amusement_01 = 4;
            D_1D3169C &= ~0x1000;
            fontClear();
            return;

        case 2:
            func_01F6E220_amusement_01();

            t = D_01F74DB8_amusement_01 + shGetDT();
            D_01F74DB8_amusement_01 = t;

            if (t < 1.0f) {
                return;
            }
    
            func_001BE4B0(0);
            D_01F74C90_amusement_01 = 5;

            func_001C2B80(1, &matrix);
            D_01F74DC0_amusement_01 = matrix[3][1];
            D_01F74D88_amusement_01 = SeCall(1.0f, 0.0f, 0x3BCB);
            /* fallthrough */

        case 5:
            func_01F6E220_amusement_01();

            func_001C2AE0(1, &matrix);
            y_2 = matrix[3][1] + (-250.0f * shGetDT());
            matrix[3][1] = y_2;
            if (y_2 < D_01F74DC0_amusement_01) {
                matrix[3][1] = D_01F74DC0_amusement_01;
            }
            func_001C2A80(1, &matrix);

            func_001C2AE0(2, &matrix);
            y_3 = matrix[3][1] + (-250.0f * shGetDT());
            matrix[3][1] = y_3;
            if (y_3 < D_01F74DC0_amusement_01) {
                func_0015DFC0(0x3BCB, D_01F74D88_amusement_01);
                matrix[3][1] = D_01F74DC0_amusement_01;
                D_01F74C90_amusement_01 = 6;
                D_01F74DB0_amusement_01 = 0.0f;
                D_01F74DB8_amusement_01 = 0.0f;
            }
            func_001C2A80(2, &matrix);
            return;

        case 6:
            if (func_01F6E220_amusement_01() != 0) {
                D_01F74C90_amusement_01 = 0;
                func_0016CF70();
                D_1D3169C &= 0xFDFFFFFF;
                D_1D31648 |= 0x40;
                D_1D31648 |= 0x20;
                D_1D3169C &= ~0x1000;
            }
            break;
    }
}

int func_01F6E710_amusement_01(void) {
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(17, 90, &D_01F71500_amusement_01);
    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }
    return audioIsPlaying;
}

int func_01F6E790_amusement_01(void) {
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(18, 95, &D_01F71530_amusement_01);
    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }
    return audioIsPlaying;
}

int func_01F6E810_amusement_01(void) {
    float angle_0;
    float angle_1;

    switch (D_01F74C80_amusement_01) {
    case 0:
        func_001C2A60(0xB, QUARTER_TURN);
        D_01F74C80_amusement_01++;
        D_01F74DB0_amusement_01 = QUARTER_TURN;
        /* fallthrough */
    case 1:
        if (GET_BIT(D_1D3169C, 0x1B)) {
            D_01F74C80_amusement_01++;
    case 2:
            angle_1 = D_01F74DB0_amusement_01 + (3.0f * shGetDT());
            D_01F74DB0_amusement_01 = angle_1;
            if ((angle_1 < -PI / 4) && !(angle_1 < -QUARTER_TURN)) {
                D_01F74DB0_amusement_01 = -QUARTER_TURN;
                D_01F74C80_amusement_01++;
            }
            angle_0 = shAngleRegulate(D_01F74DB0_amusement_01);
            D_01F74DB0_amusement_01 = angle_0;
            func_001C2A60(0xB, TO_RAD(45.0f + (45.0f * shSinF(angle_0))));
        }
    default:
        break;
    case 3:
        D_01F74C80_amusement_01 = 0;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6E9A0_amusement_01);

void func_01F6F3C0_amusement_01(void) {
    func_001C18C0(&D_01F748B0_amusement_01);
    D_01F748C8_amusement_01 = 409.57602f + D_01F748B8_amusement_01;
    func_001C0EB0(func_01F6F430_amusement_01, 999999, 0);
    D_01F74D18_amusement_01 = 2;
}

void func_01F6F430_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4) {
    sceVu0FVECTOR sp0;
    sceVu0FVECTOR sp10;
    
    sp0 = D_01F748D0_amusement_01;
    sp10 = D_01F748E0_amusement_01;

    if (D_01F74D18_amusement_01 != 0) {
        vec_copy(arg0, &D_01F748B0_amusement_01);
        *arg1 = 0;
        vec_copy(arg2, &D_01F748C0_amusement_01);
        *arg3 = 0;
        *arg4 = 0;
        D_01F74D18_amusement_01--;
    } else {
        vec_copy(arg0, &sp0);
        *arg1 = 1;
        vec_copy(arg2, &sp10);
        *arg3 = 1;
        *arg4 = 0;
    }
}

int func_01F6F4E0_amusement_01(void) {
    SubCharacter* scp;
    int ret = func_0016C540(&D_01F748F0_amusement_01, &D_01F74950_amusement_01);
    scp = shCharacterGetSubCharacter(DOUGLAS_CC_CHARA_ID, 0x178);
    if (ret != 0) {
        if (func_0019A9B0(2.0f) != 0) {
            scp->pos.x = -59676.0f;
            scp->pos.y = -8.4108f;
            scp->pos.z = 58407.0f;
            scp->rot.y = PI;
            func_001DC9E0(scp, 1);
            func_001C2290(5, 0.5f);
            func_00160AF0(10);
            return 1;
        }
    } else {
        func_0019A940();
        func_001DC9E0(scp, 0);
    }
    return 0;
}

int func_01F6F5C0_amusement_01(void) {
    int ret = func_0016C540(&D_01F74970_amusement_01, &D_01F749D0_amusement_01);
    SubCharacter* scp;
    switch (D_01F74C88_amusement_01) {              /* irregular */
    case 0:
        func_001C2290(3, 0.5f);
        D_01F74C88_amusement_01 += 1;
        /* fallthrough */
    case 1:
        scp = shCharacterGetSubCharacter(DOUGLAS_CC_CHARA_ID, 0x178);
        break;
    }
    if (ret != 0) {
        scp->pos.x = -59676.0f;
        scp->pos.y = -8.4108f;
        scp->pos.z = 58407.0f;
        scp->rot.y = PI;
        func_001DC9E0(scp, 1);
        func_001C2290(5, 0.5f);
        D_01F74C88_amusement_01 = 0;
    } else {
        func_001DC9E0(scp, 0);
    }
    return ret;
}

int func_01F6F6C0_amusement_01(void) {
    int ret = 0;
    switch (D_01F74C88_amusement_01) {
    case 0:
        if (func_0016C540(&D_01F749F0_amusement_01, &D_01F74A50_amusement_01) != 0) {
            D_01F74C88_amusement_01++;
        case 1:
            if (func_00160520(2) != 0) {
                ret = 1;
            }
        }
        break;
    }
    if (ret != 0) {
        func_001602D0(0x273A, 3, 1, 1.0f);
        func_001C2290(5, 0.5f);
        D_01F74C88_amusement_01 = 0;
        D_1D316AC &= 0xDFFFFFFF;
    }
    return ret;
}

#ifdef NON_MATCHING
int func_01F6F7A0_amusement_01(void) {
    SubCharacter* heather;
    float temp_f0;
    float temp_f1;
    int temp_s1;

    heather = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
    switch (D_01F74C88_amusement_01) {              /* irregular */
        case 0:
            func_00190A20(2);
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            if (func_0016C1C0(0x95) == 0) {
                return 0;
            }
            if (func_0016CB70() == 1) {
                func_00190A20(0);
                D_01F74C88_amusement_01 = 0;
                return 1;
            }
            D_01F74D10_amusement_01 = &D_01F74A70_amusement_01;
            func_0016C3C0();
            func_001C2290(3, 0.5f);
            D_01F74D08_amusement_01 = func_0016E650(0x22);
            D_01F74C88_amusement_01 = 2;
        case 2:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            func_001DC9E0(heather, 0);
            D_01F74C88_amusement_01 = 3;
        case 3:
            temp_s1 = func_0016C540(&D_01F74A90_amusement_01, &D_01F74AF0_amusement_01);
            temp_f0 = func_001643C0();
            if (temp_f0 >= 10.0f) {
                func_0013D250(0, (int) &D_01F74370_amusement_01, 1.0f);
            }
            temp_f1 = D_01F74D10_amusement_01->fv[0];
            if (!(temp_f1 <= 0.0f) && (temp_f1 <= temp_f0)) {
                func_0013D250(0, D_01F74D10_amusement_01->u32[1], 1.0f);
                D_01F74D10_amusement_01++;
            }
            if (temp_s1 == 0) {
                return 0;
            }
            func_001C2290(5, 0.5f);
            func_0016E400(0x22, D_01F74D08_amusement_01);
            D_01F74C88_amusement_01 += 1;
        case 4:
            func_00190A20(0);
            func_0013D280(0);
            func_001DC9E0(heather, 1);
            D_01F74C88_amusement_01 = 0;
            D_1D31648 |= 0x04000000;
    default:
        return 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F7A0_amusement_01);
#endif

int func_01F6FA20_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
        case 0:
            func_00190A20(2);
            D_1D3169C |= 0x2000;
            if (GET_BIT(D_1D3169C, 0xE)) {
                func_0016D8F0(0x47);
                D_01F74C88_amusement_01 = 3;
                return 0;
            }
            D_01F74C88_amusement_01++;
    
        case 1:
            D_01F74C88_amusement_01++;
    
        case 2:
            if (func_0016C1C0(0xC2) == 0) {
                return 0;
            }
            D_01F74C88_amusement_01 = 0;
    
        default:
            break;
    
        case 3:
            if (func_0016C1C0(0xC4) == 0) {
                return 0;
            }
            D_01F74C88_amusement_01 = 0;
            D_1D316A0 |= 0x40000000;
    }

    func_00190A20(0);
    return 1;
}

int func_01F6FB50_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
        case 0:
            func_00190A20(2);
            D_1D3169C |= 0x4000;
            if (GET_BIT(D_1D3169C, 0xD)) {
                func_0016D8F0(0x47);
                D_01F74C88_amusement_01 = 3;
                return 0;
            }
            D_01F74C88_amusement_01 += 1;
        case 1:
            D_01F74C88_amusement_01 += 1;
        case 2:
            if (func_0016C1C0(0xC3) == 0) {
                return 0;
            }
            D_01F74C88_amusement_01 = 0;
        default:
            break;
        case 3:
            if (func_0016C1C0(0xC5) == 0) {
                return 0;
            }
            D_01F74C88_amusement_01 = 0;
            D_1D316A0 |= 0x40000000;
    }
    func_00190A20(0);
    return 1;
}

int func_01F6FC80_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {              /* irregular */
        case 0:
            func_00190A20(5);
            D_01F74C88_amusement_01 = 1;
            func_00317420(0x46U);
            /* fallthrough */
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F74C88_amusement_01 = 2;
            D_1D3169C |= 0x8000;
            ItemGet(0x46U);
            SeCall(1.0f, 0.0f, 0x2B21);
            func_00317490(0x46, 0.2f);
        case 2:
            if (func_0016C1C0(0xBF) == 0) {
                return 0;
            }
            func_00190A20(6);
            func_003174B0(0.2f);
            D_01F74C88_amusement_01 = 3;
        case 3:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

int func_01F6FDC0_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
        case 0:
            D_01F74C88_amusement_01 = 1;
            func_00317420(0x47U);
            /* fallthrough */
        case 1:
            D_01F74C88_amusement_01 = 2;
            D_1D3169C |= 0x10000;
            ItemGet(0x47U);
            SeCall(1.0f, 0.0f, 0x2B21);
            func_00317490(0x47, 0.2f);
            /* fallthrough */
        case 2:
            if (func_0016C1C0(0xC1) == 0) {
                return 0;
            }
            func_003174B0(0.2f);
            D_01F74C88_amusement_01 = 3;
        case 3:
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

#ifdef NON_MATCHING
int func_01F6FED0_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
    case 0:
        func_00190A20(2);
        func_001C2290(3, 0.8f);
        D_01F74C88_amusement_01 = 1;
        /* fallthrough */
    case 1:
        if (func_001C2580(2) == 0) {
            return 0;
        }
        SeCall(1.0f, 0.0f, 0x3BC4);
        D_01F74C88_amusement_01 = 2;
        func_001C2290(5, 0.8f);
    case 2:
        if (func_0016BED0(0x4A, 0xA1) == 0) {
            return 0;
        }
        D_01F74C88_amusement_01 = 3;
        func_001C2290(5, 0.8f);
    case 3:
        if (func_001C2580(4) == 0) {
            return 0;
        }
        func_00190A20(0);
    default:
        D_01F74C88_amusement_01 = 0;
        return 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FED0_amusement_01);
#endif

int func_01F70000_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
    case 0:
        func_00190A20(5);
        D_01F74C88_amusement_01 = 1;
        D_01F74D00_amusement_01 = -1;
        if ((GetRiddleLevel() & 0xFF) < 2) {
            D_01F74D00_amusement_01 = 0xA8;
        }
    case 1:
        if (func_00190C00() == 0) {
            return 0;
        }
        if (GET_BIT(D_1D3169C, 0x16)) {
            func_001C2290(3, 0.8f);
            D_01F74C88_amusement_01 = 3;
            return 0;
        }
        D_01F74C88_amusement_01 = 2;
    case 2:
        if (func_0016C1C0(0xA7) == 0) {
            return 0;
        }
        func_0016C3C0();
        func_001C2290(3, 0.8f);
        D_01F74C88_amusement_01 = 3;
    case 3:
        if (func_0016BED0(0x4B, D_01F74D00_amusement_01) == 0) {
            return 0;
        }
        func_001C2290(5, 0.8f);
        func_00190A20(6);
        D_01F74C88_amusement_01 = 4;
    case 4:
        if (func_00190C00() == 0) {
            return 0;
        }
        func_00190A20(0);
        D_01F74C88_amusement_01 = 0;
    default:
        return 1;
    }
}

int func_01F701B0_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
        case 0:
            func_00190A20(2);
            D_1D3169C |= 0x100000;
            SeCall(1.0f, 0.0f, 0x3BC5);
            if (GET_BIT(D_1D3169C, 0x15)) {
                SeCall(1.0f, 0.0f, 0x4A3B);
            }
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            if (func_0016C1C0(0xC8) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

int func_01F702A0_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
        case 0:
            func_00190A20(2);
            D_1D3169C |= 0x200000;
            SeCall(1.0f, 0.0f, 0x3BC5);
            if (GET_BIT(D_1D3169C, 0x14)) {
                SeCall(1.0f, 0.0f, 0x4A3B);
            }
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            if (func_0016C1C0(0xC0) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

void func_01F70390_amusement_01(void) {
    func_01F703B0_amusement_01(20.0f, 40.0f);
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F703B0_amusement_01);

int func_01F70750_amusement_01(void) {
    func_0015E780(2);
    func_0016CF70();
    return 1;
}

void func_01F70780_amusement_01(void) {
    long id;
    int count;
    int* cur;
    SubCharacter* scp;

    count = 0;
    for (cur = D_01F74B10_amusement_01; *cur != 0; cur++) {
        scp = shCharacterGetSubCharacter(PENDULUM_CHARA_ID, *cur);
        if (scp != 0) {
            if (func_001E2110(scp) == 0) {
                count++;
            }
            if ((*cur != 0x182) && (*cur != 0x183)) {
                if (!(GET_BIT(D_1D3169C, 0xF))) {
                    shCharacter_Manage_Delete(PENDULUM_CHARA_ID, *cur);
                } else if ((1 < (GetActionLevel())) && (2 < count)) {
                    shCharacter_Manage_Delete(PENDULUM_CHARA_ID, *cur);
                }
            }
        }
    }
}

void func_01F70870_amusement_01(void) {
    short room;

    D_01F74CF8_amusement_01 = 0;
    room = RoomName();
    D_01F74C88_amusement_01 = 0;
    D_01F74DB0_amusement_01 = 0;
    D_1D3169C &= ~0x1000;

    switch (room) {
        case 0xD8:
        case 0xD9:
        case 0xDA:
        case 0xE0:
        case 0xE1:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
            break;
        
        case BORLEY_HAUNTED_MANSION_DINING_ROOM:
            if (func_001646F0() != 0) {
                func_00164810();
            }
            break;
        case BORLEY_HAUNTED_MANSION_DANNY_ROOM:
            if (func_001646F0() != 0) {
                func_00164810();
            }
            break;
        case BORLEY_HAUNTED_MANSION_SPIKE_ROOM:
            if (func_001646F0() != 0) {
                func_00164810();
            }
            D_01F74C90_amusement_01 = 0;
            break;
        case BORLEY_HAUNTED_MANSION_MAZE_1_ROOM:
            if (func_001646F0() != 0) {
                func_00164810();
            }
            D_01F74C80_amusement_01 = 0;
            D_01F74CB8_amusement_01 = 0;
            D_1D316A0 &= ~0x10;
            break;
        case BORLEY_HAUNTED_MANSION_MAZE_2_ROOM:
            if (func_001646F0() != 0) {
                func_00164810();
            }
            D_01F74CB8_amusement_01 = 0;
            D_1D316A0 &= ~0x10;
        }
}

void func_01F709D0_amusement_01(void) {
    SubCharacter* douglas;
    short room;

    D_01F74CF8_amusement_01 = 1;
    room = RoomName();
    switch (room) {
    case 0xE1:
        func_01F70780_amusement_01();
        break;
    case 0xE3:
        if (GET_BIT(D_1D31648, 0x1A)) {
            douglas = shCharacterGetSubCharacter(DOUGLAS_CC_CHARA_ID, 0x178);
            douglas->pos.x = -59676.0f;
            douglas->pos.y = -8.4108f;
            douglas->pos.z = 58407.0f;
            douglas->rot.y = PI;
            func_001DC9E0(douglas, 1);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70A90_amusement_01);
