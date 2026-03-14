#ifndef FSSERVE_H
#define FSSERVE_H

#include "common.h"
#include "sif.h"

typedef struct unk_00488E50
{
    char unk0;
    char unk1;
    char unk2;
    char unk3;
    u_char unk4[0x1C];
    int unk20;
    int unk24;
    int unk28;
    int unk2C;
} unk_00488E50;

typedef struct func_001532C0_arg0_struct{
    char unk0[0x200];
}func_001532C0_arg0_struct;

void func_00154CD0(int arg2);
int func_00172EF0(u_short, void (*)(int), int);

int func_001533A0(char* arg0, int arg1);
int func_00153530(int arg0, int arg1, int arg2);
int func_001536D0(int arg0, int arg1);
int func_00153830(char *arg0, int arg1);
int func_001538D0(char* arg0, int arg1, int arg2);
int func_00153A70(int arg0, int arg1, int arg2);
int func_00153AD0(int arg0, int arg1, int arg2);
int func_00153BA0(char* arg0, u32 arg1);
int func_00153CA0(char* arg0, u32 arg1);
int func_00153ED0(int arg0, int arg1, int arg2);
int func_00153F30(int arg0, int arg1, int arg2);
int func_00153F70(int arg0, int arg1, int arg2);
int func_00153FD0(int arg0, int arg1, int arg2);
int func_00154010(int arg0);
int func_00154060(int arg0);
int func_00154090(int arg0, int arg1);
int func_001540E0(int arg0, int arg1);
int func_00154110(int arg0, int* arg1);
int func_00154160(int arg0, int* arg1);
int func_00154240(char* arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
void func_001542B0();
int func_00154500(char* arg0, int arg1, int arg2, int arg3, int arg4);
int func_00154570(char* arg0, int arg1, int arg2, int arg3, int arg4);
void func_00154620(char* arg0, int arg1, int arg2, int arg3, int arg4);
int func_00154680(char* arg0, int arg1, int arg2);
int func_00154710(char* arg0, int arg1, int arg2);
int func_00154750(char* arg0, int arg1, int arg2);
int func_001547A0(char* arg0, int arg1, int arg2);
int func_00154800(int arg0);
int func_00154850(int arg0);
int func_00154890(int* arg0);
int func_00154B10(int* arg0);
int func_00154C30(int arg0, int arg1, int arg2);
int func_00154C90(int arg0, int arg1, int arg2);
int func_00154D10(u_short arg0);


extern int D_00488E40[];
extern char D_00484E40[];
extern char *D_00357978; // = (void*)&D_00488E40;
extern int D_00357980;  // = 0x4000;
extern unk_00488E50 D_00488E50[];
extern int D_00357928;
extern char* D_00357930; // "%s: %d: "
extern char* D_00357940; // "fsserve.c"
extern int D_00357950;
extern int D_00357970; // "%s"
extern char* D_00357988; // "Stat   : "
extern char* D_00357998; // "Load   : "
extern char* D_003579B0; // "can't find file: %s"

#endif
