#include "construct_00.h"

UNCURSE_CONSTRUCT_STAR();

int func_01F6D680_construct_00(void) {
    int ret;

    switch (D_01F6FA40_construct_00) {        
        case 0:
            func_00190A20(2);
        
            SeCall(1.0f, 0.0f, 0x32CA); // I hate you SeCall
        
            func_0013D250(0, &D_01F6F8B0_construct_00, 1.0f);
            D_01F6FA38_construct_00 = 0.0f;
            D_1D316AC[0] |= 0x20000000;
            D_01F6FA40_construct_00 += 1;
            /* fallthrough */
        
        case 1:
            D_01F6FA38_construct_00 +=  shGetDT();
            if (D_01F6FA38_construct_00 < 0.5f) {
                return 0;
            }
            D_01F6FA40_construct_00 += 1;
        
        default:
            ret = func_0016C540(&D_01F6F950_construct_00, &D_01F6F9B0_construct_00);
            if (ret == 1) {
                func_001C2290(5, 0.5f);
                D_1D316AC[0] &= 0xDFFFFFFF;
                func_00190A20(0);
            }            
    }

    return ret;
}

UNCURSE_CONSTRUCT_MOON();

int func_01F6D7E0_construct_00(void) { //check 3th floor sign
    float volume, zero;

    if (!GET_FLAG(D_1D31668, 0)) { 
        D_01F6FA00_construct_00 = 0;
        func_0016C3C0();
        D_1D31668[0] |= 1; 
        func_00190A20(2);
    }
    switch (D_01F6FA00_construct_00) {
        case 0:
            if (func_0016C1C0(0x19) == 0) {
                return 0;
            }
            D_01F6FA00_construct_00 += 1;
            func_0016C3C0();
    
            SeCall(1.0f, 0.0f, 0x4A52);
        default:
            if (func_0016C1C0(3) == 0) {
                return 0;
            }
            D_1D31668[0] &= ~1; 
            func_00190A20(0);
            return 1;
    }
}

int func_01F6D8D0_construct_00(void) { //check 4th floor
    if (!GET_FLAG(D_1D31668, 1)) { 
        D_01F6FA08_construct_00 = 0;
        func_0016C3C0();
        D_1D31668[0] |= 2;
        func_00190A20(2);
    }

    switch (D_01F6FA08_construct_00) {
        case 0:
            if (func_0016C1C0(0x1A) == 0) {
                return 0;
            }
            D_01F6FA08_construct_00 += 1;
            func_0016C3C0();
            SeCall(1.0f, 0.0f, 0x4A52);
        
        default:
            if (func_0016C1C0(3) == 0) {
                return 0;
            }
            D_1D31668[0] &= ~2;
            func_00190A20(0);
            return 1;    
    }  
}

int func_01F6D9C0_construct_00(void) {
    float var_f12;
    float var_f12_2;
    float temp_f0;

    if (!GET_FLAG(D_1D31664, 0x18)) {
        D_01F6FA30_construct_00 = 0;
        D_01F6FA28_construct_00 = 0.0f;
        D_1D31664[0] |= 0x01000000;
        func_00190A20(2);
    }
    switch (D_01F6FA30_construct_00) {
        case 0:
            if (func_0016C1C0(0x1B) == 0) {
                return 0;
            }
            if (func_0016CB70() == 0) {
                if (func_00151150(0, 1) != 0) {
                    var_f12 = 0.8f;
                } else {
                    var_f12 = 1.2f;
                }
                func_001C2290(3, var_f12);
                func_0016C1A0();
                D_01F6FA30_construct_00 = 1;
                
            case 1:
                if (func_001C2580(2) == 0) {
                    return 0;
                }
                SeCall(1.0f, 0.0f, 0x32C8);
                D_01F6FA30_construct_00 = 2;
                
            default:
                temp_f0 = D_01F6FA28_construct_00 + shGetDT();
                D_01F6FA28_construct_00 = temp_f0;
                if (temp_f0 < 5.3f) {
                    return 0;
                }
                if (func_00151150(0, 1) != 0) {
                    var_f12_2 = 0.8f;
                } else {
                    var_f12_2 = 1.2f;
                }
                func_001C2290(5, var_f12_2);
                func_0016C1B0();
                D_1D31664[0] |= 0x02000000;
        }
        func_00190A20(0);
        D_1D31664[0] &= 0xFEFFFFFF;
        return 1;
    }
}

int func_01F6DBC0_construct_00(void) {
    int var_s0;
    var_s0 = 0;
    if (!GET_FLAG(D_1D31664, 0x1B)) {
        func_00317420(0x18);
        D_01F6FA20_construct_00 = 0;
        D_1D31664[0] |= 0x08000000;
    }
    switch (D_01F6FA20_construct_00) {              
        case 0:
            func_00190A20(5);
            D_01F6FA20_construct_00 = 1;
            /* fallthrough */
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_00317490(0x18, 0.2f);
            SeCall(1.0f, 0.0f, 0x2B21);
            D_1D31664[0] |= 0x10000000;
            D_01F6FA20_construct_00 = 2;
    
        case 2:
            if (func_0016C1C0(0x34) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_003174B0(0.2f);
            D_01F6FA20_construct_00 = 3;
            break;    
        case 3:
            func_00190A20(6);
            D_01F6FA20_construct_00 = 4;
    
        case 4:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F6FA20_construct_00 = 5;
        default:
            D_1D31664[0] &= 0xF7FFFFFF;
            func_00190A20(0);
            var_s0 = 1;
    }
    return var_s0;
}

int func_01F6DD90_construct_00(void) {
    sceVu0FVECTOR sp20;
    sceVu0FVECTOR sp10;
    float var_f12;
    float var_f12_2;
    float temp_f0;

    if (!GET_FLAG(D_1D31664, 0x1E)) {
        D_01F6FA18_construct_00 = 0;
        D_01F6FA10_construct_00 = 0.0f;
        if (func_00151150(0, 1) != 0) {
            var_f12 = 0.8f;
        } else {
            var_f12 = 1.2f;
        }
        func_001C2290(3, var_f12);
        D_1D31664[0] |= 0x40000000;
        func_00190A20(2);
    }

    switch (D_01F6FA18_construct_00) {
        case 0:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            func_0018FE60((u_long128*)&sp20);
            func_0018FE80((u_long128*)&sp10);

            if (sp20[0] < 19960.0f) {
                if (sp20[2] > 21140.0f && sp20[2] < 22400.0f) {
                    sp20[0] = 19960.0f;
                }
            }
            
            func_00190000(&sp20, sp20[5]);
            SeCall(1.0f, 0.0f, 0x32C9);
            D_01F6FA18_construct_00 += 1;
        
    }
    
    temp_f0 = D_01F6FA10_construct_00 + shGetDT();
    D_01F6FA10_construct_00 = temp_f0;
    if (temp_f0 < 1.0f) {
        return 0;
    }
    if (func_00151150(0, 1) != 0) {
        var_f12_2 = 0.8f;
    } else {
        var_f12_2 = 1.2f;
    }
    func_001C2290(5, var_f12_2);
    func_00311A30();
    func_00190A20(0);
    D_1D31664[0] &= 0xBFFFFFFF;
    return 1;
}

void func_01F6DFB0_construct_00(void) {
    float temp_f1;
    float var_f20;
    float *tmp = (float*) D_01D31640;
    var_f20 = func_001E08A0();
    switch (func_0016DC80()) {
        case 3:
            var_f20 *= 4.0f;
            break;
        case 0xC:
        case 0xD:
        case 0xA:
            var_f20 /= 4.0f;
            break;
        case 0xB:
            var_f20 *= 1.5f;
            break;
        case 9:
        case 6:
            var_f20 = 0.0f;
            break;
        }

    temp_f1 = tmp[0x28C / 4] - var_f20;
    tmp[0x28C / 4] = temp_f1;
    if (temp_f1 <= 0.0f) {
        D_1D31664[0] |= 0x20000000;
    }
}

void func_01F6E0B0_construct_00(void) {

    if (!GET_FLAG(D_1D31668, 2)) {
        D_1D318CC[0] = 0x43960000;
        D_1D31668[0] |= 4;
        func_00316C50(0);
        func_0016ECE0(3);
    }
    switch (RoomName()) {
        case 0x66:
            D_01F6FA40_construct_00 = 0;
            break;
        case 0x63:    
            D_1D31708[0] |= 0x80000000;
            D_1D3170C[0] |= 1;
            if (GET_FLAG(D_1D316AC, 0x1C)) {
                func_00190A20(0);
                D_1D316AC[0] &= 0xEFFFFFFF;
                break;
            }
        break;
        case 0x65:
            D_1D31708[0] |= 0x04000000;
            D_1D31708[0] |= 0x08000000;
            break;
        case 0x69:
            break;
    }
}

void func_01F6E1E0_construct_00(void) {

    switch (RoomName()) {
        case 0x69:
            if (!GET_FLAG(D_1D31664, 0x1F)) {
                D_1D31708[0] |= 0x100000;
                D_1D31708[0] &= 0xFF7FFFFF;
                func_0016CA40(2);
                clAddDynamicWall(&D_01F6F500_construct_00);
                func_00189F00(0x11);
                func_00189FA0(0x11, 0x15);
            } else {
                D_1D31708[0] &= 0xFFEFFFFF;
                func_0016CA40(3);
                clAddDynamicFloor(&D_01F6EE70_construct_00);
                clAddDynamicWall(&D_01F6F5A0_construct_00);
                if (!GET_FLAG(D_1D31664, 0x1C)) {
                    func_0016CA40(0x10);
                    D_1D31708[0] |= 0x800000;
                } else {
                    D_1D31708[0] &= 0xFF7FFFFF;
                }
            }
            if (!GET_FLAG(D_1D31664, 0x1D)) {
                func_01F6DFB0_construct_00();
            }
            if (!GET_FLAG(D_1D31664, 0x19)) {
                func_0016CA40(1);
                clAddDynamicWall(&D_01F6F190_construct_00);
                D_1D31708[0] |= 0x400000;
                D_1D31708[0] &= 0xFFDFFFFF;
                if (func_00190950() != 0) {
                    clAddDynamicWall(&D_01F6F2D0_construct_00);
                    break;
                }
                break;
            }
            clAddDynamicFloor(&D_01F6EDD0_construct_00);
            if (func_001909B0() != 0) {
                clAddDynamicWall(&D_01F6F2D0_construct_00);
            }
            func_00189F00(0x11);
            func_00189FA0(0x11, 0x14);
            D_1D31708[0] |= 0x200000;
            D_1D31708[0] &= 0xFFBFFFFF;
            break;
        case 0x67:
            if (func_00190950() != 0) {
                clAddDynamicWall(&D_01F6F6E0_construct_00);
            }
            break;
    }
}
