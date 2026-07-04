#ifndef SH2_DRAWENVDATA_H
#define SH2_DRAWENVDATA_H

#include "sh2_common.h"

typedef struct sh2gfw_SPOTL_MATRIX {
    // total size: 0x40
    union Q_WORDDATA color;     // offset 0x0, size 0x10
    union Q_WORDDATA dirvec;    // offset 0x10, size 0x10
    union Q_WORDDATA position;  // offset 0x20, size 0x10
    union Q_WORDDATA decayparm; // offset 0x30, size 0x10
} sh2gfw_SPOTL_MATRIX;
typedef struct sh2gfw_POINTL_MATRIX {
    // total size: 0x30
    union Q_WORDDATA color;     // offset 0x0, size 0x10
    union Q_WORDDATA position;  // offset 0x10, size 0x10
    union Q_WORDDATA decayparm; // offset 0x20, size 0x10
} sh2gfw_POINTL_MATRIX;

typedef struct sh2gfw_Env_ctl {
    // total size: 0x3F0
    float camera_p[4];                   // offset 0x0, size 0x10
    float camera_zd[4];                  // offset 0x10, size 0x10
    float camera_yd[4];                  // offset 0x20, size 0x10
    float camera_rot[4];                 // offset 0x30, size 0x10
    float camera_ido[4];                 // offset 0x40, size 0x10
    float camera_parms[4];               // offset 0x50, size 0x10
    float camera_parms2[4];              // offset 0x60, size 0x10
    float camera_mat[4][4];              // offset 0x70, size 0x40
    float objclip_mat[4][4];             // offset 0xB0, size 0x40
    union Q_WORDDATA block_index;        // offset 0xF0, size 0x10
    float p_light0[4];                   // offset 0x100, size 0x10
    float p_light1[4];                   // offset 0x110, size 0x10
    float p_light2[4];                   // offset 0x120, size 0x10
    float p_color0[4];                   // offset 0x130, size 0x10
    float p_color1[4];                   // offset 0x140, size 0x10
    float p_color2[4];                   // offset 0x150, size 0x10
    float ambient[4];                    // offset 0x160, size 0x10
    float VertexAmbient[4];              // offset 0x170, size 0x10
    float BaseAmbient[4];                // offset 0x180, size 0x10
    float BaseVertexColor[4];            // offset 0x190, size 0x10
    float spot0_Wpos[4];                 // offset 0x1A0, size 0x10
    float spot0_Wdir[4];                 // offset 0x1B0, size 0x10
    struct sh2gfw_SPOTL_MATRIX SpotL0;   // offset 0x1C0, size 0x40
    float spot1_Wpos[4];                 // offset 0x200, size 0x10
    float spot1_Wdir[4];                 // offset 0x210, size 0x10
    struct sh2gfw_SPOTL_MATRIX SpotL1;   // offset 0x220, size 0x40
    float CharacterLightFactor[4];       // offset 0x260, size 0x10
    float CharacterLightFactor_Other[4]; // offset 0x270, size 0x10
    struct sh2gfw_SPOTL_MATRIX SpotL2;   // offset 0x280, size 0x40
    float point0_localpos[4];            // offset 0x2C0, size 0x10
    struct sh2gfw_POINTL_MATRIX PointL0; // offset 0x2D0, size 0x30
    unsigned short light_mode;           // offset 0x300, size 0x2
    unsigned short weather_mode;         // offset 0x302, size 0x2
    unsigned short time_mode;            // offset 0x304, size 0x2
    unsigned short now_block;            // offset 0x306, size 0x2
    unsigned short mode_buf[4];          // offset 0x308, size 0x8
    union Q_WORDDATA stat_ctl_1;         // offset 0x310, size 0x10
    union Q_WORDDATA stat_ctl_2;         // offset 0x320, size 0x10
    union Q_WORDDATA fogcolor;           // offset 0x330, size 0x10
    union Q_WORDDATA fogparm;            // offset 0x340, size 0x10
    union Q_WORDDATA MoveFogColor;       // offset 0x350, size 0x10
    union Q_WORDDATA clearcolor;         // offset 0x360, size 0x10
    union Q_WORDDATA random_seeds;       // offset 0x370, size 0x10
    union Q_WORDDATA compo_shadow_env;   // offset 0x380, size 0x10
    union Q_WORDDATA compo_shadow_test;  // offset 0x390, size 0x10
    union Q_WORDDATA compo_shadow_alp;   // offset 0x3A0, size 0x10
    union Q_WORDDATA compo_shadow_col;   // offset 0x3B0, size 0x10
    union Q_WORDDATA compo_Fill_col;     // offset 0x3C0, size 0x10
    union Q_WORDDATA NoiseCondition;     // offset 0x3D0, size 0x10
    union Q_WORDDATA CopyFilterColor;    // offset 0x3E0, size 0x10
} sh2gfw_Env_ctl;

// total size: 0x1F0
typedef struct DrawEnvData {
    // Members
    int map_id_name; // offset 0x0, size 0x4
    char parallelLNum; // offset 0x4, size 0x1
    char FakeSpotNum; // offset 0x5, size 0x1
    char FakePointNum; // offset 0x6, size 0x1
    char pointLNum; // offset 0x7, size 0x1
    char spotLNum; // offset 0x8, size 0x1
    char NightOrDay; // offset 0x9, size 0x1
    short ShadowColor; // offset 0xA, size 0x2
    short ShadowForceLightNo; // offset 0xC, size 0x2
    short ShadowDarkNess; // offset 0xE, size 0x2
    float pLight_Dir0[4]; // offset 0x10, size 0x10
    float pLight_Col0[4]; // offset 0x20, size 0x10
    float pLight_Dir1[4]; // offset 0x30, size 0x10
    float pLight_Col1[4]; // offset 0x40, size 0x10
    float pLight_Dir2[4]; // offset 0x50, size 0x10
    float pLight_Col2[4]; // offset 0x60, size 0x10
    float SpotCol0[4]; // offset 0x70, size 0x10
    float SpotDecayParm0[4]; // offset 0x80, size 0x10
    float SpotParm[4]; // offset 0x90, size 0x10
    float FogParm[4]; // offset 0xA0, size 0x10
    float Ld_0[4]; // offset 0xB0, size 0x10
    float Ld_1[4]; // offset 0xC0, size 0x10
    float Ld_2[4]; // offset 0xD0, size 0x10
    float Ld_3[4]; // offset 0xE0, size 0x10
    float Ld_4[4]; // offset 0xF0, size 0x10
    float Ld_5[4]; // offset 0x100, size 0x10
    float Ld_6[4]; // offset 0x110, size 0x10
    float Ld_7[4]; // offset 0x120, size 0x10
    float Ld_8[4]; // offset 0x130, size 0x10
    float Ld_9[4]; // offset 0x140, size 0x10
    float Ld_A[4]; // offset 0x150, size 0x10
    float Ld_B[4]; // offset 0x160, size 0x10
    float Ld_C[4]; // offset 0x170, size 0x10
    float Ld_D[4]; // offset 0x180, size 0x10
    float Ld_E[4]; // offset 0x190, size 0x10
    float MoveFogCol[4]; // offset 0x1A0, size 0x10
    float Ambient[4]; // offset 0x1B0, size 0x10
    float BaseAmbient[4]; // offset 0x1C0, size 0x10
    float BaseColor[4]; // offset 0x1D0, size 0x10
    float VertexAmbient[4]; // offset 0x1E0, size 0x10
} DrawEnvData;

extern sh2gfw_Env_ctl Env_ctl; // size: 0x3F0, address: 0x2AD780 Env_ctl;

void* Get_NowDrawEnvData(void);

int Get_NowParallelNum(void);

int Get_NowFakePointNum(void);

int Get_NowFakeSpotNum(void);

int Check_NowSpotFakeOrJms(void);

int Get_NowRoomShadowDense(void);

int Get_NowRoomShadowColor(void);

void* Get_NowRoomShadowForceLight(int* ltype);

int Check_IgnoreJmsSpot_for_Shadow(void);

int* Get_NowMapId(void);

void Get_NowPallarelCol(float* pdir, int nn);

void Set_DrawEnvData(int mapid, int NightOrDay);

void SetupDrawEnvData(void);

#endif // SH2_DRAWENVDATA_H
