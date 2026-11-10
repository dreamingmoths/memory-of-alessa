#ifndef SH2GFW_LIGHTSET_H
#define SH2GFW_LIGHTSET_H

#include "sh2_common.h"
#include "sce/eetypes.h"

#define DEMO_MAX_PARALLEL_LIGHT 3
#define DEMO_MAX_POINT_LIGHT 3

// total size: 0x1B0
typedef struct DemoLight_Work {
    // Members
    short Parallel[DEMO_MAX_PARALLEL_LIGHT]; // offset 0x0, size 0x6
    short Parallel_Cid[DEMO_MAX_PARALLEL_LIGHT]; // offset 0x6, size 0x6
    short Point[DEMO_MAX_POINT_LIGHT]; // offset 0xC, size 0x6
    short Point_Cid[DEMO_MAX_POINT_LIGHT]; // offset 0x12, size 0x6
    short Spot; // offset 0x18, size 0x2
    short Amb; // offset 0x1A, size 0x2
    short Ref; // offset 0x1C, size 0x2
    sceVu0FVECTOR demo_p_light0; // offset 0x20, size 0x10
    sceVu0FVECTOR demo_p_color0; // offset 0x30, size 0x10
    sceVu0FVECTOR demo_p_light1; // offset 0x40, size 0x10
    sceVu0FVECTOR demo_p_color1; // offset 0x50, size 0x10
    sceVu0FVECTOR demo_p_light2; // offset 0x60, size 0x10
    sceVu0FVECTOR demo_p_color2; // offset 0x70, size 0x10
    sceVu0FVECTOR demo_ambient; // offset 0x80, size 0x10
    sceVu0FVECTOR demo_VertexAmbient; // offset 0x90, size 0x10
    sceVu0FVECTOR demo_BaseAmbient; // offset 0xA0, size 0x10
    sceVu0FVECTOR demo_BaseVertexColor; // offset 0xB0, size 0x10
    sceVu0FVECTOR demo_spotcol; // offset 0xC0, size 0x10
    sceVu0FVECTOR demo_spotdir; // offset 0xD0, size 0x10
    sceVu0FVECTOR demo_spotpos; // offset 0xE0, size 0x10
    sceVu0FVECTOR demo_spotdecay; // offset 0xF0, size 0x10
    sceVu0FVECTOR demo_pointcol0; // offset 0x100, size 0x10
    sceVu0FVECTOR demo_pointpos0; // offset 0x110, size 0x10
    sceVu0FVECTOR demo_pointdecay0; // offset 0x120, size 0x10
    sceVu0FVECTOR demo_pointcol1; // offset 0x130, size 0x10
    sceVu0FVECTOR demo_pointpos1; // offset 0x140, size 0x10
    sceVu0FVECTOR demo_pointdecay1; // offset 0x150, size 0x10
    sceVu0FVECTOR demo_pointcol2; // offset 0x160, size 0x10
    sceVu0FVECTOR demo_pointpos2; // offset 0x170, size 0x10
    sceVu0FVECTOR demo_pointdecay2; // offset 0x180, size 0x10
    sceVu0FVECTOR demo_RefLight_dir; // offset 0x190, size 0x10
    sceVu0FVECTOR demo_RefLight_col; // offset 0x1A0, size 0x10
} DemoLight_Work;

// total size: 0x30
typedef struct AAA {
    // Members
    sceVu0FVECTOR col; // offset 0x0, size 0x10
    sceVu0FVECTOR pos; // offset 0x10, size 0x10
    sceVu0FVECTOR decay; // offset 0x20, size 0x10
} AAA;

void sh2gfw_Init_DemoLight_Work(void);
int sh2gfw_Set_DemoRefrectionHighLight(float* dir, float* col);
int sh2gfw_Get_DemoRefrectionHightLight(float* dir, float* col);
int sh2gfw_Check_DemoRefrectionHightLight(void);
int sh2gfw_Set_PallarelLight(float* dir, float* color, int n);
int sh2gfw_Check_ParallelDemoLight(int n);
int sh2gfw_Get_ParallelDemoLight(int n, float* dir, float* col);
void sh2gfw_Revive_ParallelDemoLight(int n);
void sh2gfw_Set_DemoPointLight(int n, float* pos, float* col, float falloff_start, float falloff_end);
int sh2gfw_Check_DemoPointLight(void);
int sh2gfw_Get_DemoPointLight(int n, float* pos, float* col, float* decay);
int sh2gfw_Check_DemoSpotLight(void);
void sh2gfw_Get_DemoSpotParm(float* svt);
void sh2gfw_Get_DemoSpotPosDirCol(float* pos, float* dir, float* col);
void sh2gfw_Set_SpotLight(float* dir, float* pos, float* color, int unused, float falloff_start, float falloff_end, float spread_pi); // @note: singature different from DWARF
void sh2gfw_setparal3LGT_blk(void* pbman, float* light_dir0, float* light_dir1, float* light_dir2, float* col0, float* col1, float* col2, float* ambient);
void sh2gfw_LightSet_ForBG(void* pb_man);
void sh2gfw_Store_SpotLight(void);
void sh2gfw_setsp1para2LGT_blk(void* pbman, void* sm, float* light0, float* color0, float* light1, float* color1, float* amb);
int sh2gfw_Get_NightOrDay(void);
int SetLightMode(int nod);
void Get_DemoOrPresetLight(float* pl, float* pc, int g);
void Get_DemoOrPresetAmbient(float* ab);
void sh2gfw_Set_JmsSpot_OnOrOff(void);

#endif // SH2GFW_LIGHTSET_H
