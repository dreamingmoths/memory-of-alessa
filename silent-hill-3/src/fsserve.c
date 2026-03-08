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

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153930);


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

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153BA0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153CA0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153CF0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153ED0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153F30);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153F70);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00153FD0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154010);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154060);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154090);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001540E0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154110);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154160);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154240);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001542B0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001542C0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154500);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154570);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154620);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154680);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154710);

int func_00154750(int arg0, int arg1, int arg2) {
    arg2 |= 0xD0000000;
    func_00154710(arg0, arg1, arg2);
}

int func_001547A0(int arg0, int arg1, int arg2) {
    int ret;

    func_00152C20();
    ret = func_00154750(arg0, arg1, arg2);
    func_00152C60();
    return ret;
}

int func_00154800(int* arg0) {
    int ret;

    func_00152C20();
    ret = func_00154850(arg0);
    func_00152C60();

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154850);

int func_00154890(int* arg0) {
    int ret;

    func_00152C20();
    ret = func_001548E0(arg0);
    func_00152C60();

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001548E0);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154950);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001549B0);

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


INCLUDE_ASM("asm/nonmatchings/fsserve", func_00154CD0);

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

INCLUDE_ASM("asm/nonmatchings/fsserve", func_00155080);

INCLUDE_ASM("asm/nonmatchings/fsserve", func_001550D0);
