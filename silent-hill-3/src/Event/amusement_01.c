#include "amusement_01.h"
#include "Font/font.h"

static void func_01F6DCF0_amusement_01(u_long128 *arg0, int *arg1, u_long128 *arg2, int *arg3, int *arg4);
static void func_01F6F430_amusement_01(u_long128 *arg0, int *arg1, u_long128 *arg2, int *arg3, int *arg4);
static void func_01F6DC70_amusement_01(u_long128 *arg0, int *arg1, u_long128 *arg2, int *arg3, int *arg4);

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


int func_01F6D840_amusement_01(void) {
    sceVu0FVECTOR sp30;
    sceVu0FVECTOR sp40;
    sceVu0FVECTOR sp50;
    Amusement01Pair* entry;

    sp30 = D_01F74640_amusement_01;

    switch (D_01F74C88_amusement_01) {
        case 0:
            D_01F74DA8_amusement_01 = 0.0f;
            D_01F74DA0_amusement_01 = 0;
    
            D_1D3169C |= 0x1000;
    
            D_01F74CA8_amusement_01 = func_0016E0F0();

            D_1D316A0 &= 0x7FFFFFFF;
    
            D_01F74C88_amusement_01++;
            /* fallthrough */
    
        case 1: {
            float t;
    
            func_0016CF80(0xD,0x37,&D_01F71400_amusement_01);
    
            t = D_01F74DA8_amusement_01 + shGetDT();
            D_01F74DA8_amusement_01 = t;
    
            if (t < 14.5f)
                return 0;
    
            func_01F6DCB0_amusement_01();
            func_01F6DDC0_amusement_01();
    
            D_01F74C88_amusement_01++;
        }
    
        case 2: {
            float t;
    
            func_0016CF80(0xD,0x37,&D_01F71400_amusement_01);
    
            t = D_01F74DA8_amusement_01 + shGetDT();
            D_01F74DA8_amusement_01 = t;
    
            if (t < 31.0f)
                return 0;
    
            func_01F6DDC0_amusement_01();
    
            D_01F74C88_amusement_01++;
        }
    
        case 3: {
            float t;
    
            func_0016CF80(0xD,0x37,&D_01F71400_amusement_01);
    
            t = D_01F74DA8_amusement_01 + shGetDT();
            D_01F74DA8_amusement_01 = t;
    
            if (t < 48.0f)
                return 0;
    
            D_01F74DA8_amusement_01 = 0.0f;
    
            D_01F74C88_amusement_01++;
        }
    
        case 4: {
            int temp_s0 = func_0016CF80(0xD,0x37,&D_01F71400_amusement_01);
            int i;
    
            D_01F74DA8_amusement_01 += shGetDT();
            i = 0;

            while (entry = &D_01F74610_amusement_01[i], entry->start != 0.0f) {
                if (entry->start <= D_01F74DA8_amusement_01 && entry->end > D_01F74DA8_amusement_01) {
                    sp40 = D_01F74650_amusement_01;
                    sp50 = D_01F74660_amusement_01;
            
                    func_0016CA40(1); 
                    func_0016E150(1);
            
                    func_001C7C80(&sp40, &sp50, &sp30, 0x200);
            
                    D_1D316A0 |= 0x80000000;
                    break;
                } else {
                    D_1D316A0 &= 0x7FFFFFFF;
                    func_0016E150(0);
                }
                i++;
            }
    
            if (D_01F74DA0_amusement_01 == 0 && !(D_01F74DA8_amusement_01 < D_01F74610_amusement_01->start)) {
                func_0015DCD0(1.0f, 10000.0f, 0x3BC8, &sp30, 0, 0);
                D_01F74DA0_amusement_01 = 1;
            }
    
            if (temp_s0 == 0) {
                return 0;
            }
    
            func_0016CA80(1);
            func_0016E150(0);
    
            D_01F74C88_amusement_01 = 0;
            D_1D316A0 &= 0x7FFFFFFF;
            D_1D3169C &= ~0x1000;
    
            func_001C0EE0(0);
            func_0016CF70();
        }
            
        default:
            return 1;
    }
}

void func_01F6DC40_amusement_01(void) {
    func_001C0EB0(func_01F6DC70_amusement_01, 90, 1);
    D_01F74CB0_amusement_01 = 0;
}

static void func_01F6DC70_amusement_01(u_long128* arg0, int* arg1, u_long128* arg2, int* arg3, int* arg4) {
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

static void func_01F6DCF0_amusement_01(u_long128* arg0, int* arg1, u_long128* arg2, int* arg3, int* arg4) {
    sceVu0FVECTOR sp60;

    func_0018FE60((u_long128*) &sp60);
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
    Amusement01Pair* cur;
    int state = D_01F74C88_amusement_01;

    switch (state) {
        case 0:
            func_01F6DC40_amusement_01();
            D_01F74D98_amusement_01 = 0;
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            for (i = 0; cur = &D_01F74610_amusement_01[i], cur->start != 0.0f; i++) {
                limit = D_01F74D98_amusement_01;
                if (cur->start <= limit && cur->end > limit) {
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
                    func_0015DCD0(1.0f, 10000.0f, 15303, &danny->pos, 0, 0);
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

void func_01F6F430_amusement_01(u_long128* arg0, int* arg1, u_long128* arg2, int* arg3, int* arg4) {
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

int func_01F6F7A0_amusement_01(void) {
    SubCharacter* heather;
    float temp_f0;
    float temp_f1;
    int temp_s1;

    heather = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
    switch (D_01F74C88_amusement_01) {
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
                func_0013D250(0, &D_01F74370_amusement_01, 1.0f);
            }
            temp_f1 = D_01F74D10_amusement_01->fv[0];
            if (!(temp_f1 <= 0.0f) && (temp_f1 <= temp_f0)) {
                func_0013D250(0, (int*) D_01F74D10_amusement_01->u32[1], 1.0f);
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

UNCURSE_AMUSEMENT_MOON();

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

void func_01F703B0_amusement_01(float fparg0, float fparg1) {
    sceVu0FMATRIX matrix0;
    sceVu0FMATRIX matrix1;
    sceVu0FMATRIX matrix2;
    sceVu0FMATRIX matrix3;
    sceVu0FMATRIX matrix4;
    sceVu0FMATRIX matrix5;
    sceVu0FMATRIX matrix6;

    D_01F74CE8_amusement_01 += (fparg0 * shGetDT());
    if (D_01F74CE8_amusement_01 > 180.0f) {
        D_01F74CE8_amusement_01 -= 360.0f; 
    }

    D_01F74CF0_amusement_01 -= (fparg1 * shGetDT());
    if (D_01F74CF0_amusement_01 < -180.0f) {
        D_01F74CF0_amusement_01 += 360.0f;
    }

    func_001C2AE0(1, matrix0);
    func_001C2AE0(2, matrix1);
    sceVu0UnitMatrix(matrix2);
    func_00121300(matrix2, matrix2, TO_RAD(D_01F74CE8_amusement_01));

    mat_copy(matrix3, func_001AFE30(3, 1)->matrix);
    shMulMatrix(matrix2, matrix3, matrix2);
    func_001C2A80(1, matrix2);
    mat_copy(matrix0, matrix2);

    asm("
        lq $t0, 0(%0)
        lq $t1, 0x10(%0)
        lq $t2, 0x20(%0)
        lqc2 $vf4, 0x30(%0)
        pextlw $t3, $t1, $t0
        pextuw $t4, $t1, $t0
        pextlw $t5, $zero, $t2
        pextuw $t6, $zero, $t2
        pcpyld $t0, $t5, $t3
        pcpyud $t1, $t3, $t5
        pcpyld $t2, $t6, $t4
        qmtc2 $t0, $vf5
        qmtc2 $t1, $vf6
        qmtc2 $t2, $vf7
        vmulax.xyz $acc, $vf5, $vf4x
        vmadday.xyz $acc, $vf6, $vf4y
        vmaddz.xyz $vf4, $vf7, $vf4z
        sq $t0, 0(%1)
        sq $t1, 0x10(%1)
        vsub.xyz $vf4, $vf0xyz, $vf4xyz
        sq $t2, 0x20(%1)
        sqc2 $vf4, 0x30(%1)
    " : : "r"(matrix3), "r"(matrix4));

    sceVu0UnitMatrix(matrix2);
    sceVu0UnitMatrix(matrix6);
    sceVu0UnitMatrix(matrix5);
    shRotMatrixY(matrix5, matrix5, TO_RAD(D_01F74CF0_amusement_01));

    mat_copy(matrix1, func_001AFE30(3, 2)->matrix);
    shMulMatrix(matrix2, matrix4, matrix1);
    shMulMatrix(matrix2, matrix2, matrix5);
    shMulMatrix(matrix2, matrix0[0], matrix2);
    func_001C2A80(2, matrix2);

    mat_copy(matrix1, func_001AFE30(3, 3)->matrix);
    shMulMatrix(matrix2, matrix4, matrix1);
    shMulMatrix(matrix2, matrix2, matrix5);
    shMulMatrix(matrix2, matrix0, matrix2);
    func_001C2A80(3, matrix2);

    mat_copy(matrix1, func_001AFE30(3, 4)->matrix);
    shMulMatrix(matrix2, matrix4, matrix1);
    shMulMatrix(matrix2, matrix2, matrix5);
    shMulMatrix(matrix2, matrix0[0], matrix2);
    func_001C2A80(4, matrix2);

    func_0018A260(0xE2);
    func_0018A310(0xE2, 0x134, 2);
    func_0018A310(0xE2, 0x135, 3);
    func_0018A310(0xE2, 0x136, 4);
}

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


UNCURSE_AMUSEMENT_BLOOD();

void func_01F70A90_amusement_01(void) {
    sceVu0FMATRIX sp10;
    sceVu0FMATRIX sp50;
    sceVu0FMATRIX* sp90;
    sceVu0FVECTOR spA0;
    sceVu0FMATRIX spB0;
    float angle;
    float t;
    u_int flags;
    u_int flag_d;
    short room_name;

    if (D_01F74CF8_amusement_01 == 0) {
        func_01F709D0_amusement_01();
    }
    room_name = RoomName();
    switch (room_name) {
        case 0xD8:
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F73D40_amusement_01);
                clAddDynamicWall(&D_01F73C50_amusement_01);
                clAddDynamicWall(&D_01F73E80_amusement_01);
                clAddDynamicWall(&D_01F73B60_amusement_01);
                clAddDynamicWall(&D_01F73480_amusement_01);
                clAddDynamicWall(&D_01F738E0_amusement_01);
                clAddDynamicWall(&D_01F735C0_amusement_01);
                clAddDynamicWall(&D_01F737A0_amusement_01);
                break;
            }
            break;

        case 0xDA:
            if (!(GET_BIT(D_1D31648, 2)) && (func_01F6D7C0_amusement_01())) {
                D_1D31648 |= 4;
                break;
            }
            break;

        case BORLEY_HAUNTED_MANSION_DINING_ROOM:
            if (!(GET_BIT(D_1D31648, 3))) {
                if (func_01F6D840_amusement_01()) {
                    D_1D31648 |= 8;
                    break;
                }
            }
            break;

        case BORLEY_HAUNTED_MANSION_DANNY_ROOM:
            if (!(GET_BIT(D_1D31648, 4)) && func_01F6DF10_amusement_01()) {
                D_1D31648 |= 0x10;
            }
            if (GET_BIT(D_1D3169C, 0x18)) {
                clAddDynamicWall(&D_01F72DA0_amusement_01);
            }
            if (!(D_01F74DB0_amusement_01 <= -(0.5f * shGetDT())) && (D_01F74DB0_amusement_01 < (0.5f * shGetDT()))) {
                func_001C2B80(2, &sp10);
                func_0015DCD0(1.0f, 10000.0f, 0x3BC9, &sp10[3], 0, 0);
            }
            t = D_01F74DB0_amusement_01 + shGetDT();
            D_01F74DB0_amusement_01 = t;
            angle = shAngleRegulate(t);
            D_01F74DB0_amusement_01 = angle;
            func_001C2A70(2, TO_RAD(1.5f * shSinF(angle)));
            break;
    
        case BORLEY_HAUNTED_MANSION_SPIKE_ROOM: {
            u_int flags_0;
            u_int flags_1;

            flags_0 = D_1D3169C;
            if (GET_BIT(flags_0, 0x19)) {
                if (!GET_BIT(D_1D31648, 6)) {
                    func_01F6E2A0_amusement_01();
                    break;
                }
                break;
            }

            flags_1 = D_1D31648;
            if (!GET_BIT(flags_1, 5)) {
                if (func_01F6E1A0_amusement_01()) {
                    D_1D31648 |= 0x20;
                    break;
                }
                break;
            }

            if (GET_BIT(flags_0, 0x1A) && !GET_BIT(flags_1, 7) && func_01F6E710_amusement_01()) {
                D_1D31648 |= 0x80;
                break;
            }

            break;
        } 
        case BORLEY_HAUNTED_MANSION_MAZE_1_ROOM:
            if (!GET_BIT(D_1D31648, 8) && (func_01F6E790_amusement_01())) {
                D_1D31648 |= 0x100;
            }
            if (!GET_BIT(D_1D3169C, 0x1C) && func_01F6E810_amusement_01()) {
                D_1D3169C |= 0x10000000;
            }
            if (GET_BIT(D_1D316A0, 4)) {
                func_01F6E9A0_amusement_01();
                break;
            }
            break;

        case BORLEY_HAUNTED_MANSION_MAZE_2_ROOM:
            if (GET_BIT(D_1D316A0, 4)) {
                func_01F6E9A0_amusement_01();
                break;
            }
            break;

        case 0xE0:
            if (!GET_BIT(D_1D31648, 0x1A)) {
                func_001C2B80(4, &sp50);
                sp50[3][1] += 2000.0f;
                func_001C2A80(4, &sp50);
            }
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F73F20_amusement_01);
            }
            if (GET_BIT(D_1D31648, 0x1A)) {
                clAddDynamicWall(&D_01F741A0_amusement_01);
            }
            if (func_001643D0() != 0x3D) {
                if (GET_BIT(D_1D31648, 0x1A)) {
                    func_0016CA40(4);
                } else {
                    flags = D_1D3169C;
                    flag_d = GET_BIT(flags, 0xD);
                    if ((flag_d) && (GET_BIT(flags, 0xE))) {
                        func_0016CA40(2);
                    } else if (flag_d) {
                        func_0016CA40(3);
                    } else if (GET_BIT(flags, 0xE)) {
                        func_0016CA40(1);
                    }
                }
                if (GET_BIT(D_1D31648, 0x1A)) {
                    func_001C2A60(1, 0.0f);
                    func_001C2A60(2, 0.0f);
                    func_001C2A60(3, 0.0f);
                    func_001C2A60(4, 0.0f);
                    func_001C2A60(5, TO_RAD(25));
                    sceVu0UnitMatrix(&spB0);
                    shRotMatrixX(&spB0, &spB0, QUARTER_TURN);
                    shRotMatrixY(&spB0, &spB0, TO_RAD(119));
                    func_0016CBD0(&sp90, &spA0, 0xE);
                    mat_copy(sp10, sp90);
                    sp10[3][1] -= 540.0f;
                    sp10[3][0] -= 35.0f;
                    shMulMatrix(&sp10, &sp10, &spB0);
                    func_001C2A80(6, &sp10);
                }
                if (!(GET_BIT(D_1D3169C, 0x10))) {
                    func_0016CA40(5);
                    clAddDynamicWall(&D_01F74010_amusement_01);
                    break;
                }
                func_0016CA40(0xF);
                break;
            }
            break;

        case 0xE1:
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F74290_amusement_01);
                break;
            }
            break;

        case 0xE2:
            if (!(GET_BIT(D_1D3169C, 0xF))) {
                func_0016CA40(0xB);
            }
            if (!(GET_BIT(D_1D3169C, 0x10))) {
                func_0016CA40(0xA);
                break;
            }
            break;

        case 0xE3:
            if (GET_BIT(D_1D31648, 0x1E)) {
                func_01F70390_amusement_01();
            }
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F72F30_amusement_01);
                clAddDynamicWall(&D_01F72FD0_amusement_01);
                clAddDynamicWall(&D_01F73070_amusement_01);
                clAddDynamicWall(&D_01F73160_amusement_01);
                clAddDynamicWall(&D_01F73250_amusement_01);
            }
            clAddDynamicWall(&D_01F73340_amusement_01);
            break;

        case 0xE5:
            if (!(GET_BIT(D_1D3169C, 0x11))) {
                func_0016CA40(8);
            }
            if (!(GET_BIT(D_1D3169C, 0x12))) {
                func_0016CA40(9);
                break;
            }
            break;

        case 0xE6:
            if (GET_BIT(D_1D3169C, 0x14)) {
                func_0016CA40(6);
            }
            if (GET_BIT(D_1D3169C, 0x15)) {
                func_0016CA40(7);
            }
            break;

        case 0xE4:
        case 0xE7:
            break;
    }
}
