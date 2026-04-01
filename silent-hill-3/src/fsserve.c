#include "fsserve.h"

int func_001533A0(char* arg0, int arg1) {
    int discard_s0;

    if ((arg1 < 0) && (arg0 == NULL) && (*arg0 == 0)) {
        return 0;
    }
    
    func_00153320();
    if (func_00172DD0(D_00357928) < 0) {
        discard_s0 = 0;
    } else {
        D_00488E40[0]++;
        D_00488E40[0] = D_00488E40[0] % 16;
        D_00488E50[D_00488E40[0]].unk20 = arg1;
        func_00130D70(&D_00488E50[D_00488E40[0]], arg0, 0x1F);
        D_00488E50[D_00488E40[0]].unk24 = 0;
        D_00488E50[D_00488E40[0]].unk28 = 0;
    }
    func_00172D70(D_00357928);
    return 1;
}

int func_00153530(int arg0, int arg1, int arg2) {
    int var_s0;
    int var_s2;
    int i;

    if (arg0 < 0) {
        return 0;
    }
    
    func_00153320();
    if (func_00172DD0(D_00357928) < 0) {
        var_s2 = 0;
    } else {
        var_s2 = 0;
        for (i = 0x10; i > 0; i--) {
            var_s0 = (D_00488E40[0]  + i) % 16;
            if ((arg0 == D_00488E50[var_s0].unk20) && D_00488E50[var_s0].unk0 != 0) {
                D_00488E50[var_s0].unk24 = arg1;
                D_00488E50[var_s0].unk28 = arg2;
                D_00488E50[var_s0].unk2C = 0;
                var_s2 = 1;
                break;
            }
        }
    }
    func_00172D70(D_00357928);
    return var_s2;
}


int func_001536D0(int arg0, int arg1) {
    int var_s0;
    int var_s2;
    int i;

    if (arg0 < 0) {
        return 0;
    }
    
    func_00153320();
    if (func_00172DD0(D_00357928) < 0) {
        var_s2 = 0;
    } else {
        var_s2 = 0;
        for (i = 0x10; i > 0; i--) {
            var_s0 = (D_00488E40[0]  + i) % 16;
            if ((arg0 == D_00488E50[var_s0].unk20) && D_00488E50[var_s0].unk0 != 0) {
                D_00488E50[var_s0].unk2C = arg1;
                var_s2 = 1;
                break;
            }
        }
    }
    
    func_00172D70(D_00357928);
    return var_s2;
}

int func_00153830(char *arg0, int arg1) {
    int i;

    if (arg1 < 0) {
        return 0;
    }

    for (i = 0; i < arg1; i += 0x10) {
        arg0[i] = ((i % 8) * 0x11) + 0x12;
    }
    
    return arg1;
}

int func_001538D0(char* arg0, int arg1, int arg2) {
    int temp_s0;
    
    func_00152C20();
    temp_s0 = func_00153930(arg0, arg1, arg2);
    func_00152C60();
    return temp_s0;
}


int func_00153930(char* arg0, int arg1, int arg2){
    int i;
    func_001532C0_arg0_struct sp50;
    int var_s2;
    int ret;
    int var_s3 = arg1 & 0x200000; 

    arg1 &= ~0x200000;
    i = 0;
    
    func_00152B50();
    
    for(;;){
        var_s2 = func_001532C0(&sp50, arg0, sizeof(func_001532C0_arg0_struct), i);
        if(var_s2 > 0){
            ret = func_00151DF0(&sp50, arg1, arg2);

            if(ret < 0){
                i++;
            }
            else{
                func_001533A0(arg0, ret);
                break;
            }
        }
        else{
            printf(&D_00357930, &D_00357940, 0x214);
            printf(&D_00357950, arg0, ret);
            ret = -1;
            break;
        }

    }

    if(var_s3 != 0){
        do{
            printf(&D_00357970, &sp50);
        }while(0);
    }

    func_00152B90();

    return ret;
}


int func_00153A70(int arg0, int arg1, int arg2) {
    int temp_s0;

    func_00152C20();
    temp_s0 = func_00153CF0(arg0, arg1, arg2);
    func_00152C60();
    return temp_s0;
}

int func_00153AD0(int arg0, int arg1, int arg2) {
    sceSifDmaData dma;
    int var_s1;
    int var_s0;
    
    var_s0 = 0;
    dma.data = arg1;
    dma.addr = arg0;
    dma.size = arg2;
    dma.mode = 0;
    
    FlushCache(WRITEBACK_DCACHE);
    while ((var_s1 = sceSifSetDma(&dma, 1)) == 0) {
        func_00154D10(0xA);
        var_s0++;
    }
    
    while (sceSifDmaStat(var_s1) >= 0) {
        func_00154D10(0xA);
        var_s0++;
    }
    return var_s0;
}

int func_00153BA0(char* arg0, u_int arg1){
    u_int temp_s1;
    int ret = 1;

    if(arg0 == NULL){
        arg0 = D_00484E40;
        arg1 = 0x4000;
    }
    else{
        if((u_int)arg0 & 0x3F){
            ret = 0;
        }
        if(arg1 & 0x7FF){
            ret = 0;
        } 

        temp_s1 = (u_int)arg0 & 0x3F;
        
        arg1 -= temp_s1;
        arg0 += temp_s1;
        
        arg1 &= ~0x7FF;

        if(arg1 <= 0x4000){
            ret = 0;
        }
        if(ret == 0){
            arg0 = D_00484E40;
            D_00357980 = 0x4000;
        }
    }

    D_00357978 = arg0;
    D_00357980 = arg1;
    return ret;
}

int func_00153CA0(char* arg0, u_int arg1){
    int ret;
    
    func_00152C20();
    ret = func_00153BA0(arg0, arg1);
    func_00152C60();
    
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153CF0);

int func_00153ED0(int arg0, int arg1, int arg2){
    int ret;

    func_00152C20();
    ret = func_00153F30(arg0, arg1, arg2); 
    func_00152C60();
    
    return ret;
}

int func_00153F30(int arg0, int arg1, int arg2){
    return func_001520D0(arg0, arg1, arg2);
}

int func_00153F70(int arg0, int arg1, int arg2){
    int ret;

    func_00152C20();
    ret = func_00153FD0(arg0, arg1, arg2);
    func_00152C60();
    
    return ret;
}

int func_00153FD0(int arg0, int arg1, int arg2){
    return func_00152160(arg0, arg1, arg2);
}
 
int func_00154010(int arg0){
    int ret;

    func_00152C20();
    ret = func_00154060(arg0);
    func_00152C60();

    return ret;
}

int func_00154060(int arg0){
    return func_00152240(arg0);
}

int func_00154090(int arg0, int arg1){
    int ret;

    func_00152C20();
    ret = func_001540E0(arg0, arg1);
    func_00152C60();

    return ret;
}

int func_001540E0(int arg0, int arg1){
    return func_001522D0(arg0, arg1);
}

int func_00154110(int arg0, int* arg1){
    int ret;

    func_00152C20();
    ret = func_00154160(arg0, arg1);
    func_00152C60();

    return ret;
}

int func_00154160(int arg0, int* arg1){
    int ret;
    int var_s0;
    func_001532C0_arg0_struct sp40;
    int i = 0;
    int var_s2;
    
    printf(&D_00357988);
    func_00152B50();
    
    for(;;){
        var_s2 = func_001532C0(&sp40, arg0, sizeof(func_001532C0_arg0_struct), i);
        if(var_s2 > 0){
            ret = func_001523C0(&sp40, arg1);

            if(ret < 0){
                i++;
            }
            else{
                printf(&D_00357970, &sp40);
                break;
            }
        }
        else{
            ret = -1;
            break;
        }
    }

    func_00152B90();
    return ret;
}

int func_00154240(char* arg0, int arg1, int arg2, int arg3, int arg4, int arg5){
    int ret;
    
    func_00152C20();
    ret = func_001542C0(arg0, arg1, arg2, arg3, arg4, arg5);
    func_00152C60();

    return ret;
}

void func_001542B0(){
    
}

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001542C0);

int func_00154500(char* arg0, int arg1, int arg2, int arg3, int arg4){
    int ret;

    func_00152C20();
    ret = func_00154570(arg0, arg1, arg2, arg3, arg4);
    func_00152C60();

    return ret;
}

int func_00154570(char* arg0, int arg1, int arg2, int arg3, int arg4){
    int ret;
    
    arg1 &= ~0x26C0;
    arg1 &= ~3;

    if(arg2 == 0){
        printf(&D_00357998);
        arg1 |= 0x200000;
    }

    ret = func_001542C0(arg0, arg1, 0, arg2, arg3, arg4);

    return ret;
}

void func_00154620(char* arg0, int arg1, int arg2, int arg3, int arg4){
    arg3 |= 0xD0000000;

    func_00154570(arg0, arg1, arg2, arg3, arg4);
}

int func_00154680(char* arg0, int arg1, int arg2){
    int ret;
    int i = 0;

    while(arg0[i] != 0){
        i++;
    }

    func_00152C20();
    ret = func_00154710(arg0, arg1, arg2); 
    func_00152C60();

    return ret;
}

int func_00154710(char* arg0, int arg1, int arg2){
    return func_00154570(arg0, arg1, 0, arg2, -1);
}


int func_00154750(char* arg0, int arg1, int arg2) {
    arg2 |= 0xD0000000;
    func_00154710(arg0, arg1, arg2); 
} 

int func_001547A0(char* arg0, int arg1, int arg2) {
    int ret;

    func_00152C20();
    ret = func_00154750(arg0, arg1, arg2);
    func_00152C60();
    return ret;
}

int func_00154800(int arg0) {
    int ret;

    func_00152C20();
    ret = func_00154850(arg0);
    func_00152C60();

    return ret;
}

int func_00154850(int arg0){
    int sp10[0x15];

    return func_00154160(arg0, sp10) >= 0;
}

int func_00154890(int* arg0) {
    int ret;

    func_00152C20();
    ret = func_001548E0(arg0);
    func_00152C60();

    return ret;
}

int func_001548E0(int arg0){
    int sp10[0x15];

    if(func_00154160(arg0, sp10) < 0){
        printf(&D_00357930, &D_00357940, 0x475);
        printf(&D_003579B0, arg0);
    }

    return sp10[8];
}

int func_00154950(int arg0, int arg1, int arg2){
    int ret;

    func_00152C20();
    ret = func_001549B0(arg0, arg1, arg2);
    func_00152C60();

    return ret;
}


int func_001549B0(int arg0, func_001532C0_arg0_struct* arg1, int arg2){
    int ret;
    int var_s2;
    char** var_s4;
    char** var_s5;
    int i = 0;
    int sp70[24];
    int* temp;
    
    if(arg1 != 0 && arg2 > 0){
        func_00152B50();

        for(;;){
            var_s2 = func_001532C0(arg1, arg0, arg2, i);
            if(var_s2 > 0){
                temp = sp70;
                
                ret = func_001523C0(arg1, temp);

                if(ret < 0){
                    i++;
                }
                else{
                    ret = func_00130EA0(arg1);
                    break;
                }
            }
            else{
                ret = -1;
                break;
            }
        }
        
        func_00152B90();
    }
    else{
        if(arg2 > 0){
            var_s4 = &D_003579C8;
        }
        else{
            var_s4 = &D_003579D0;
        }
        if(arg1 != 0){
            var_s5 = &D_003579C8;
        }
        else{
            var_s5 = &D_003579E0;
        }

        printf(&D_003579F8, var_s5, var_s4);
        ret = -1;
    }

    return ret;
}

int func_00154B10(int* arg0) {
    int ret;

    func_00152C20();
    ret = func_00154B60(arg0);
    func_00152C60();

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154B60);

int func_00154C30(int arg0, int arg1, int arg2) {
    int ret;

    func_00152C20();
    ret = func_00154C90(arg0, arg1, arg2);
    func_00152C60();

    return ret;
}


int func_00154C90(int arg0, int arg1, int arg2) {
    func_00154DB0(arg0, arg1, arg2);
}

void func_00154CD0(int arg0, int arg1, int arg2){
    int sp0 = arg2;
    
    func_00172E90(sp0);
    ExitHandler();
}

int func_00154D10(u_short arg0) {
    int temp_v0;
    int ret;

    ret = 0;
    temp_v0 = func_00172C90(1, 0, 0);
    if (temp_v0 >= 0) {
        if (func_00172EF0(arg0, func_00154CD0, temp_v0) >= -1) {
            func_00172DD0(temp_v0);
            ret = 1;
        }
        func_00172D10(temp_v0);
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154DB0);

int func_00155080(int arg0){
    int ret;

    func_00152C20();
    ret = LoadAr(arg0);
    func_00152C60();

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/fsserve", LoadAr);
