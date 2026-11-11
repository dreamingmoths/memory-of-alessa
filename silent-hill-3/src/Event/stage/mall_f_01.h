#ifndef MALL_F_01
#define MALL_F_01

#include "Event/picture.h"
#include "gs.h"
#include "vec.h"

typedef struct {
    // total size: 0x8
    float unk0; // offset 0x0, size 0x4
    int*  unk4; // offset 0x4, size 0x4
} D_01F72758_struct;

typedef struct {
    // total size: 0x8
    float unk0; // offset 0x0, size 0x4
    int*  unk4; // offset 0x4, size 0x4
} D_01F727E0_struct;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
} D_01F72894_struct;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
} D_01F7290C_struct;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
} D_01F72910_struct;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
} D_01F72974_struct;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
} D_01F72990_struct;

typedef struct _Shakespeare_Puzzle_Work {
    // total size: 0xB2C
    PicLoadImage_Data      pic_loads[2];       // offset 0x0,   size 0x20
    PicDraw_Data           pic_quads[16];      // offset 0x20,  size 0x440
    u_char                 unk460[0x484];      // offset 0x460, size 0x484
    PicDraw_Data           selection_books[5]; // offset 0x8E4, size 0x154
    u_char                 unkA38[0x88];       // offset 0xA38, size 0x88
    int                    solution_order[5];  // offset 0xAC0, size 0x14
    int                    placed_order[5];    // offset 0xAD4, size 0x14
    int                    formed_digits[4];   // offset 0xAE8, size 0x10
    int                    selection_slots[5]; // offset 0xAF8, size 0x14
    int                    step;               // offset 0xB0C, size 0x4
    int                    placed_count;       // offset 0xB10, size 0x4
    int                    interactive_mode;   // offset 0xB14, size 0x4
    int                    riddle_level;       // offset 0xB18, size 0x4
    int                    selected_book;      // offset 0xB1C, size 0x4
    int                    message_id;         // offset 0xB20, size 0x4
    u_char                 unkB24[0x4];        // offset 0xB24, size 0x4
    float                  book_blink;         // offset 0xB28, size 0x4
} Shakespeare_Puzzle_Work;

typedef struct _Shakespeare_Keypad_Work {
    // total size: 0x8B4
    PicLoadImage_Data pic_loads[2];     // offset 0x0,   size 0x20
    PicDraw_Data      pic_quads[11];    // offset 0x20,  size 0x2EC
    u_char            unk30C[0x594];    // offset 0x30C, size 0x594
    int               step;             // offset 0x8A0, size 0x4
    float             key_blink;        // offset 0x8A4, size 0x4
    int               last_pressed_key; // offset 0x8A8, size 0x4
    int               correct_password; // offset 0x8AC, size 0x4
    u_int             entered_code;     // offset 0x8B0, size 0x4
} Shakespeare_Keypad_Work;

void func_001C2290(int, float);
void func_0019B4B0(int);
int func_001C2580(int);
int func_0016C540(int*, int*);
float func_001643C0(void);
void func_0013D250(int, int*, float);
void func_0013D280(int);
void func_003272C0(void);
int shRandI(void);
float shRandF(void);
void func_003272E0(void);
int func_001646C0(void);
void func_001602D0(int, int, int, float);
void func_003272D0(void);
void func_0016C3C0(void);
void func_00317420(int);
int func_00190A20(int);
int func_0016C1C0(int);
int func_00168440(void);
void SeCall(int, float, float);
void ItemGet(u_int);
void func_00317490(int, float);
void func_003174B0(float);
int func_0012CFA0(void);
int func_0012D080(void);
int func_0012CFC0(void);
u_char GetRiddleLevel(void);
int func_0016BED0(int, int);
void shQzero(void*, u_int);
void func_002A2E70(sceVu0FVECTOR*);
u_short func_002A47C0(float, float);
void func_0029F330(float*, float*);
int func_001DE5B0(void (*)(), void*, int);
u_short* GetMessageStation(void);
void PlayerResultTimerCountUp(void);
void fontClear(void);
u_short* fontGetMesAdr(u_short*, u_short);
u_short fontPrintStrMain(u_short**, int);
int func_0013D080(int, int, int, int);
float shGetDT(void);
void func_0029F3D0(int);
void func_0029F9B0(void);
void func_002A45F0(void);
u_short func_002A4640(u_short, float, float, float, float);
void* func_00156410(int);
void func_0016C1B0(void);
void func_0016BBF0(void);
void func_0016C1A0(void);
void func_0016F550(int, int);
int func_00151150(int, int);
void func_0029FA30(void);
void func_0016BC00(int);
int RoomName(void);
void clAddDynamicWall(int*);
void func_0016CBD0(sceVu0FMATRIX*[], sceVu0FMATRIX*[], int);
int func_0019B580(int);
void func_001B3F20(sceVu0FVECTOR*);
void func_001B3F30(sceVu0FVECTOR*);
void func_001C2A80(int, sceVu0FMATRIX*);
void func_001C7BC0(sceVu0FVECTOR*, sceVu0FVECTOR*, sceVu0FVECTOR*, int);
int func_00199C70(int);

int func_01F6D680_mall_f_01(void);
int func_01F6D820_mall_f_01(void);
int func_01F6DA20_mall_f_01(void);
int func_01F6DA70_mall_f_01(void);
int func_01F6DBD0_mall_f_01(void);
int func_01F6DCC0_mall_f_01(void);
void func_01F6DDB0_mall_f_01(void);
void func_01F6DF00_mall_f_01(Shakespeare_Puzzle_Work* work);
void func_01F6DF90_mall_f_01(Shakespeare_Puzzle_Work* work);
void func_01F6DFE0_mall_f_01(Shakespeare_Puzzle_Work* work, int slot_index);
void func_01F6E3F0_mall_f_01(Shakespeare_Puzzle_Work* work, int slot_index);
void func_01F6E630_mall_f_01(Shakespeare_Puzzle_Work* work);
int func_01F6E6E0_mall_f_01(Shakespeare_Puzzle_Work* work);
int func_01F6E700_mall_f_01(void);
int func_01F6E730_mall_f_01(Shakespeare_Puzzle_Work* work);
void func_01F6E9E0_mall_f_01(Shakespeare_Puzzle_Work* work, int arg1);
int func_01F6EE40_mall_f_01(int arg0);
int func_01F6F1C0_mall_f_01(void);
int func_01F6F1D0_mall_f_01(void);
int func_01F6F1E0_mall_f_01(void);
int func_01F6F1F0_mall_f_01(void);
int func_01F6F200_mall_f_01(void);
int func_01F6F210_mall_f_01(void);
void func_01F6F220_mall_f_01(Shakespeare_Keypad_Work* work);
void func_01F6F2B0_mall_f_01(Shakespeare_Keypad_Work* work);
void func_01F6F300_mall_f_01(Shakespeare_Keypad_Work* work, int key);
void func_01F6F510_mall_f_01(Shakespeare_Keypad_Work* work);
int func_01F6F5A0_mall_f_01(void);
int func_01F6F5D0_mall_f_01(Shakespeare_Keypad_Work* work);
void func_01F6F720_mall_f_01(Shakespeare_Keypad_Work* work);
int func_01F6F810_mall_f_01(void);
int func_01F6FB30_mall_f_01(void);
int func_01F6FCB0_mall_f_01(void);
int func_01F6FD00_mall_f_01(void);
int func_01F6FDA0_mall_f_01(void);
int func_01F6FED0_mall_f_01(void);
void func_01F70070_mall_f_01(void);
void func_01F70160_mall_f_01(void);
void func_01F70720_mall_f_01(void);

extern int D_01F72BC8_mall_f_01;
extern int D_01F72760_mall_f_01;
extern int D_01F727C0_mall_f_01;
extern u_int D_1D31644;
extern u_int D_1D31784;
extern int D_01F72810_mall_f_01;
extern int D_01F72870_mall_f_01;
extern int D_01F72BB8_mall_f_01;
extern float D_01F72BB0_mall_f_01;
extern int D_01F72890_mall_f_01;
extern int D_01F728F0_mall_f_01;
extern u_int D_1D3164C;
extern int D_01F72B80_mall_f_01;
extern u_int D_1D31BF4;
extern u_int D_1D316F0;
extern u_int D_1D31650;
extern u_int D_1D31700;
extern u_int D_01D31640[];
extern u_int D_01D319F0[];
extern u_int D_1D318C0;
extern int D_01F72B88_mall_f_01;
extern float D_01F72B90_mall_f_01;
extern int D_01F72BA8_mall_f_01;
extern int D_01F72B98_mall_f_01;
extern int D_01F72BA0_mall_f_01;
extern int D_01F72310_mall_f_01;
extern int D_01F72400_mall_f_01;
extern sceVu0FVECTOR D_01F72AB0_mall_f_01;
extern sceVu0FVECTOR D_01F72AC0_mall_f_01;
extern sceVu0FVECTOR D_01F72AD0_mall_f_01;
extern sceVu0FVECTOR D_01F72AE0_mall_f_01;
extern u_int D_1D316FC;
extern u_int D_1D318C4;
extern u_int D_1D318C8;

extern D_01F72758_struct* D_01F72BC0_mall_f_01;
extern D_01F72758_struct D_01F72758_mall_f_01;

extern D_01F727E0_struct D_01F727E0_mall_f_01;

extern D_01F72894_struct D_01F72894_mall_f_01[];

extern D_01F7290C_struct D_01F7290C_mall_f_01[];

extern D_01F72910_struct D_01F72910_mall_f_01[];

extern D_01F72974_struct D_01F72974_mall_f_01[];

extern D_01F72990_struct D_01F72990_mall_f_01[];

#endif
