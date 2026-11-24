#include "sh2_common.h"
#include "sce/libvu0.h"

#include "Chacter/m3_play_event.h"
#include "Chacter/m3_sc.h"

#include "Collision/cl_main.h"

#include "data/fs_structs.h"
#include "data/daily.thu/data_chr_scu.h"
#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_wp.h"
#include "data/daily.thu/data_demo_machi.h"
#include "data/daily.thu/data_demo_saisho.h"
#include "data/daily.thu/data_pic_out.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/demoview.h"
#include "Event/item.h"
#include "Event/chara_data_load.h"

#include "GFW/sh2gfw_2d_filters.h"

#include "SH2_common/pad.h"
#include "SH2_common/sh2dt.h"

#include "sh2shd/sh2shd_shadow_model.h"

#include "view/vc_main.h"
#include "view/vc_util.h"

static int stg_town_east_EvProgShadowOfSomenthing(void);
static int stg_town_east_EvProgSandersBack(void);
static int stg_town_east_EvProgFirstMonsterStart(void);
static int stg_town_east_EvProgFirstMonsterCorpse(void);
static int stg_town_east_EvProgFirstMonsterEnd(void);
static int stg_town_east_EvProgBloodSwamp(void);
static int stg_town_east_EvProgGetApartGateKey(void);
static int stg_town_east_EvProgUseApartGateKey(void);
static int stg_town_east_EvProgLookMemoFalled(void);
static void stg_town_east_EvStageInit(void);
static int stg_town_east_EvCharaDataClear(void);
static void stg_town_east_EvRoomInit(void);
static void stg_town_east_EvAllTimeFunc(void);
static int stg_town_east_EvBgmControl(void);
static void stg_town_east_EvLockSetCb46(int* list);
static void stg_town_east_EvCorpseSetCb18(int* list);
static void stg_town_east_EvCorpseSetCb26(int* list); // @note: signature different from DWARF
static void stg_town_east_EvWallSetCb19(int* list);
static void stg_town_east_EvWallSetCb20(int* list);
static void stg_town_east_EvWallSetCb21(int* list);
static void stg_town_east_EvWallSetCb49(int* list);
static void stg_town_east_EvWallSetCb52(int* list);
static void stg_town_east_EvSignalControlCb27(int* list);
static void stg_town_east_EvSignalControlCb28(int* list);
static void stg_town_east_EvSignalControlCb29(int* list);
static void stg_town_east_EvSignalControlCb35(int* list);
static void stg_town_east_EvSignalControlCb36(int* list);
static void stg_town_east_EvSignalControlCb37(int* list);
static void stg_town_east_EvTapeSetCb11(int* list);
static void stg_town_east_EvTapeSetCb12(int* list);
static float stg_town_east_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm);
static void stg_town_east_CB_1stMoster_FogHosei(void);
static void stg_town_east_CB_1stMonster_Filter(void);
static void stg_town_east_Draw_CB_Tonnel(void);
static void stg_town_east_Monster1st_Look(void* sp, float* ambient);

static AnimeInfo stg_town_east_pjames_stage_anim[21] = { // size: 0xFC, address: 0x1F04E00
    {
        /* .name = */ 20001,
        /* .frame = */ 20,
        /* .speed = */ 1024,
        /* .start = */ 1024,
        /* .end = */ 1043,
        /* .loop = */ 0,
        /* .pad = */ 10,
    },
    {
        /* .name = */ 20007,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1044,
        /* .end = */ 1073,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20008,
        /* .frame = */ 15,
        /* .speed = */ 768,
        /* .start = */ 1074,
        /* .end = */ 1088,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20009,
        /* .frame = */ 15,
        /* .speed = */ 768,
        /* .start = */ 1089,
        /* .end = */ 1103,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20010,
        /* .frame = */ 30,
        /* .speed = */ 768,
        /* .start = */ 1104,
        /* .end = */ 1133,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20011,
        /* .frame = */ 30,
        /* .speed = */ 768,
        /* .start = */ 1134,
        /* .end = */ 1163,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20012,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1168,
        /* .end = */ 1178,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20013,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1183,
        /* .end = */ 1193,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20014,
        /* .frame = */ 30,
        /* .speed = */ 640,
        /* .start = */ 1194,
        /* .end = */ 1223,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20015,
        /* .frame = */ 30,
        /* .speed = */ 640,
        /* .start = */ 1224,
        /* .end = */ 1253,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20016,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1258,
        /* .end = */ 1268,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20017,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1273,
        /* .end = */ 1283,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20018,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1284,
        /* .end = */ 1313,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20019,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1314,
        /* .end = */ 1343,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20020,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1344,
        /* .end = */ 1373,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20025,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1378,
        /* .end = */ 1388,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20026,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1393,
        /* .end = */ 1403,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20027,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1404,
        /* .end = */ 1433,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20028,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1434,
        /* .end = */ 1463,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20037,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1464,
        /* .end = */ 1478,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        NULL
    }
};

static u_char stg_town_east_ev_pos[600]; // size: 0x258, address: 0x1F04F00

static Event_List stg_town_east_ev_list[48] = { // size: 0x300, address: 0x1F05160
    {
        /* .flag = */ 2555904,
        /* .cond = */ 1073786880,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 16423,
    },
    {
        /* .flag = */ 2818048,
        /* .cond = */ 1074704384,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 32768,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 538726400,
        /* .rslt0 = */ 1076498496,
        /* .rslt1 = */ 0,
    },
    {
        /* .flag = */ -2131034112,
        /* .cond = */ 540426240,
        /* .rslt0 = */ 1078079552,
        /* .rslt1 = */ 4195575,
    },
    {
        /* .flag = */ 16449536,
        /* .cond = */ 540426240,
        /* .rslt0 = */ 1078865984,
        /* .rslt1 = */ 4195575,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 542789636,
        /* .rslt0 = */ -1610612736,
        /* .rslt1 = */ 50425,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 543707140,
        /* .rslt0 = */ -1610612736,
        /* .rslt1 = */ 50425,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 544624640,
        /* .rslt0 = */ 1082413056,
        /* .rslt1 = */ 37748736,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 545542144,
        /* .rslt0 = */ 1081495552,
        /* .rslt1 = */ 37748736,
    },
    {
        /* .flag = */ -2131034112,
        /* .cond = */ 546447360,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 62898176,
    },
    {
        /* .flag = */ 3080192,
        /* .cond = */ 547254272,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 114735,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ -1601035912,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 131120,
    },
    {
        /* .flag = */ -2144337920,
        /* .cond = */ 546447360,
        /* .rslt0 = */ 1085542816,
        /* .rslt1 = */ 58720305,
    },
    {
        /* .flag = */ 3145728,
        /* .cond = */ 546447360,
        /* .rslt0 = */ -2147483648,
        /* .rslt1 = */ 58720256,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 549474304,
        /* .rslt0 = */ 1610612736,
        /* .rslt1 = */ 0,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 550375428,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 98348,
    },
    {
        /* .flag = */ 2850858,
        /* .cond = */ 551161856,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 81963,
    },
    {
        /* .flag = */ -2144665600,
        /* .cond = */ 551161856,
        /* .rslt0 = */ 1088839680,
        /* .rslt1 = */ 0,
    },
    {
        /* .flag = */ -2144665600,
        /* .cond = */ 551968768,
        /* .rslt0 = */ 1088032768,
        /* .rslt1 = */ 0,
    },
    {
        /* .flag = */ 2621440,
        /* .cond = */ 551968768,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 49192,
    },
    {
        /* .flag = */ -2144796630,
        /* .cond = */ 268435456,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 65578,
    },
    {
        /* .flag = */ 82444288,
        /* .cond = */ 1090039808,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1258,
    },
    {
        /* .flag = */ 2752512,
        /* .cond = */ 551161856,
        /* .rslt0 = */ 1610612736,
        /* .rslt1 = */ 98304,
    },
    {
        /* .flag = */ -2144731136,
        /* .cond = */ 554070016,
        /* .rslt0 = */ 1610612736,
        /* .rslt1 = */ 49152,
    },
    {
        /* .flag = */ 17104896,
        /* .cond = */ 555495428,
        /* .rslt0 = */ -2147483648,
        /* .rslt1 = */ 33555700,
    },
    {
        /* .flag = */ -2130378752,
        /* .cond = */ 555495424,
        /* .rslt0 = */ 1093157312,
        /* .rslt1 = */ 33555701,
    },
    {
        /* .flag = */ 1077084160,
        /* .cond = */ 557056004,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 147506,
    },
    {
        /* .flag = */ 1077215232,
        /* .cond = */ 557711364,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 147508,
    },
    {
        /* .flag = */ 1077346304,
        /* .cond = */ 558366724,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 147510,
    },
    {
        /* .flag = */ 1077477376,
        /* .cond = */ 559022084,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 147512,
    },
    {
        /* .flag = */ 1077608448,
        /* .cond = */ 559677444,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 147514,
    },
    {
        /* .flag = */ 1113784320,
        /* .cond = */ 560332804,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 148066,
    },
    {
        /* .flag = */ -2131034112,
        /* .cond = */ 561000448,
        /* .rslt0 = */ 1098662336,
        /* .rslt1 = */ 33555741,
    },
    {
        /* .flag = */ 16449536,
        /* .cond = */ 561000448,
        /* .rslt0 = */ -2147483648,
        /* .rslt1 = */ 33554432,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 562569220,
        /* .rslt0 = */ 1610612736,
        /* .rslt1 = */ 16384,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 563359748,
        /* .rslt0 = */ 1610612736,
        /* .rslt1 = */ 16384,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 564142080,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 62898176,
    },
    {
        /* .flag = */ 82575360,
        /* .cond = */ 1101844484,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1260,
    },
    {
        /* .flag = */ 82575360,
        /* .cond = */ 1103286276,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1260,
    },
    {
        /* .flag = */ 82968576,
        /* .cond = */ 1104719876,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1266,
    },
    {
        /* .flag = */ 82640896,
        /* .cond = */ 1105637380,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1261,
    },
    {
        /* .flag = */ 82706432,
        /* .cond = */ 1106554884,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1262,
    },
    {
        /* .flag = */ 82771968,
        /* .cond = */ 1107472388,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1263,
    },
    {
        /* .flag = */ 82837504,
        /* .cond = */ 1108389892,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1264,
    },
    {
        /* .flag = */ 82903040,
        /* .cond = */ 1109307396,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1265,
    },
    {
        /* .flag = */ 83034112,
        /* .cond = */ 1110233092,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1267,
    },
    {
        /* .flag = */ 83492864,
        /* .cond = */ 1111674884,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1274,
    },
    {
        NULL
    }
};

static Item_List gi_list[18] = { // size: 0x120, address: 0x1F05460
    {
        /* .posX = */ 3134.51f,
        /* .posZ = */ 29744.269f,
        /* .posY = */ 53824,
        /* .rotY = */ 32768,
        /* .st = */ 2147484457,
    },
    {
        /* .posX = */ -7424.31f,
        /* .posZ = */ -4462.06f,
        /* .posY = */ 54144,
        /* .rotY = */ 32768,
        /* .st = */ 2147484459,
    },
    {
        /* .posX = */ -7351.52f,
        /* .posZ = */ -4546.5f,
        /* .posY = */ 53664,
        /* .rotY = */ 32768,
        /* .st = */ 537920301,
    },
    {
        /* .posX = */ -31707.5f,
        /* .posZ = */ 14621.0195f,
        /* .posY = */ 53504,
        /* .rotY = */ 32768,
        /* .st = */ 2147484463,
    },
    {
        /* .posX = */ -28249.91f,
        /* .posZ = */ -24580.349f,
        /* .posY = */ 53344,
        /* .rotY = */ 32768,
        /* .st = */ 2147484467,
    },
    {
        /* .posX = */ -46008.53f,
        /* .posZ = */ -50619.21f,
        /* .posY = */ 52480,
        /* .rotY = */ 14671,
        /* .st = */ 1611662433,
    },
    {
        /* .posX = */ -54182.37f,
        /* .posZ = */ -49684.78f,
        /* .posY = */ 52480,
        /* .rotY = */ 47271,
        /* .st = */ 1611662435,
    },
    {
        /* .posX = */ -54250.28f,
        /* .posZ = */ -49724.39f,
        /* .posY = */ 52480,
        /* .rotY = */ 14659,
        /* .st = */ 1611662437,
    },
    {
        /* .posX = */ -46116.42f,
        /* .posZ = */ -50657.3f,
        /* .posY = */ 53119,
        /* .rotY = */ 14372,
        /* .st = */ 2684355687,
    },
    {
        /* .posX = */ -63134.89f,
        /* .posZ = */ 9542.2597f,
        /* .posY = */ 53343,
        /* .rotY = */ 32768,
        /* .st = */ 2147484777,
    },
    {
        /* .posX = */ -63219.16f,
        /* .posZ = */ 9586.6298f,
        /* .posY = */ 52480,
        /* .rotY = */ 14778,
        /* .st = */ 537920619,
    },
    {
        /* .posX = */ -72056.867f,
        /* .posZ = */ -62756.03f,
        /* .posY = */ 52480,
        /* .rotY = */ 14909,
        /* .st = */ 537920621,
    },
    {
        /* .posX = */ -72101.5f,
        /* .posZ = */ -62729.25f,
        /* .posY = */ 52480,
        /* .rotY = */ 45490,
        /* .st = */ 537920623,
    },
    {
        /* .posX = */ 39381.55f,
        /* .posZ = */ -45792.87f,
        /* .posY = */ 52158,
        /* .rotY = */ 15390,
        /* .st = */ 537920309,
    },
    {
        /* .posX = */ 24842.089f,
        /* .posZ = */ -47810.53f,
        /* .posY = */ 52991,
        /* .rotY = */ 15390,
        /* .st = */ 537920311,
    },
    {
        /* .posX = */ 39439.71f,
        /* .posZ = */ -45890.429f,
        /* .posY = */ 53183,
        /* .rotY = */ 32768,
        /* .st = */ 2147484473,
    },
    {
        /* .posX = */ 24907.009f,
        /* .posZ = */ -47896.0f,
        /* .posY = */ 0,
        /* .rotY = */ 46628,
        /* .st = */ 1074791227,
    },
    {
        /* .posX = */ 0.0f,
        /* .posZ = */ 0.0f,
        /* .posY = */ 0,
        /* .rotY = */ 0,
        /* .st = */ 3758096384,
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb11[8] = { // size: 0x280, address: 0x1F05580
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7642.5498f, -441.476f, 2368.445f, 1.0f, -7642.5498f, 6.7411999f, 2368.445f, 1.0f, -7361.2998f, 6.7411999f, 2070.62f, 1.0f, -7361.2998f, -441.68148f, 2070.62f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7345.85f, -441.68148f, 92.4645f, 1.0f, -7345.85f, 6.7411999f, 92.4645f, 1.0f, -7600.0498f, 6.7411999f, -4.6283397f, 1.0f, -7600.0498f, -441.68148f, -4.6283397f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7545.95f, -441.06549f, 3265.31f, 1.0f, -7545.95f, 6.7411999f, 3265.31f, 1.0f, -7642.5498f, 6.7411999f, 2368.445f, 1.0f, -7642.5498f, -441.476f, 2368.445f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7442.2998f, 6.7411999f, 459.401f, 1.0f, -7442.2998f, -441.68148f, 459.401f, 1.0f, -7537.2f, -441.68148f, 518.09497f, 1.0f, -7537.2f, 6.7411999f, 518.09497f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7545.95f, 6.7411999f, 3265.31f, 1.0f, -7545.95f, -441.06549f, 3265.31f, 1.0f, -7344.35f, -440.85998f, 3475.705f, 1.0f, -7344.35f, 6.7411999f, 3475.705f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7662.2f, 6.7411999f, 1611.84497f, 1.0f, -7662.2f, -441.68148f, 1611.84497f, 1.0f, -7498.25f, -441.68148f, 1734.67f, 1.0f, -7498.25f, 6.7411999f, 1734.67f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7537.2f, 6.7411999f, 518.09497f, 1.0f, -7537.2f, -441.68148f, 518.09497f, 1.0f, -7662.2f, -441.68148f, 1611.84497f, 1.0f, -7662.2f, 6.7411999f, 1611.84497f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
}; 

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb12[7] = { // size: 0x230, address: 0x1F05800
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7633.45f, 6.7411999f, -2194.665f, 1.0f, -7633.45f, -441.476f, -2194.665f, 1.0f, -7427.2f, -441.68148f, -1996.84497f, 1.0f, -7427.2f, 6.7411999f, -1996.84497f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7637.2f, 6.7411999f, -1511.84497f, 1.0f, -7637.2f, -441.68148f, -1511.84497f, 1.0f, -7587.2f, -441.68148f, 25.65575f, 1.0f, -7587.2f, 6.7411999f, 25.65575f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7720.95f, 6.7411999f, -3115.31f, 1.0f, -7720.95f, -441.06549f, -3115.31f, 1.0f, -7633.45f, -441.476f, -2194.665f, 1.0f, -7633.45f, 6.7411999f, -2194.665f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7462.2f, -441.68148f, -1649.34497f, 1.0f, -7462.2f, 6.7411999f, -1649.34497f, 1.0f, -7427.2f, 6.7411999f, -1996.84497f, 1.0f, -7427.2f, -441.68148f, -1996.84497f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7720.95f, -441.06549f, -3115.31f, 1.0f, -7720.95f, 6.7411999f, -3115.31f, 1.0f, -7452.2f, 6.7411999f, -3388.135f, 1.0f, -7452.2f, -440.85998f, -3388.135f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 12,
        /* .flg = */ 0,
        /* .p = */ {-7637.2f, -441.68148f, -1511.84497f, 1.0f, -7637.2f, 6.7411999f, -1511.84497f, 1.0f, -7462.2f, 6.7411999f, -1649.34497f, 1.0f, -7462.2f, -441.68148f, -1649.34497f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb18[4] = { // size: 0x140, address: 0x1F05A30
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {-34187.148f, 45.82125f, 38317.648f, 1.0f, -34187.148f, -321.8515f, 38317.648f, 1.0f, -34063.3f, -321.8515f, 39026.398f, 1.0f, -34063.3f, 45.82125f, 39026.398f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {-34705.1f, 45.82125f, 39026.398f, 1.0f, -34705.1f, -321.8515f, 39026.398f, 1.0f, -34583.75f, -321.8515f, 38294.648f, 1.0f, -34583.75f, 45.82125f, 38294.648f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {-34583.75f, 45.82125f, 38294.648f, 1.0f, -34583.75f, -321.8515f, 38294.648f, 1.0f, -34187.148f, -321.8515f, 38317.648f, 1.0f, -34187.148f, 45.82125f, 38317.648f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb19[10] = { // size: 0x320, address: 0x1F05B70
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-28560.0f, -1250.0f, 4065.0f, 1.0f, -29967.5f, -1250.0f, 4065.0f, 1.0f, -29967.5f, -2500.0f, 4065.0f, 1.0f, -28560.0f, -2500.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-31570.0f, -975.0f, 4065.0f, 1.0f, -30040.0f, -975.0f, 4065.0f, 1.0f, -30040.0f, 0.0f, 4065.0f, 1.0f, -31570.0f, 0.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-30040.0f, -975.0f, 4065.0f, 1.0f, -29967.5f, -975.0f, 4065.0f, 1.0f, -29967.5f, 0.0f, 4065.0f, 1.0f, -30040.0f, 0.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-30040.0f, -1250.0f, 4065.0f, 1.0f, -31570.0f, -1250.0f, 4065.0f, 1.0f, -31570.0f, -2500.0f, 4065.0f, 1.0f, -30040.0f, -2500.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-29967.5f, -1250.0f, 4065.0f, 1.0f, -30040.0f, -1250.0f, 4065.0f, 1.0f, -30040.0f, -2500.0f, 4065.0f, 1.0f, -29967.5f, -2500.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-29967.5f, -975.0f, 4065.0f, 1.0f, -28560.0f, -975.0f, 4065.0f, 1.0f, -28560.0f, 0.0f, 4065.0f, 1.0f, -29967.5f, 0.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-30040.0f, -975.0f, 4065.0f, 1.0f, -31570.0f, -975.0f, 4065.0f, 1.0f, -31570.0f, -1250.0f, 4065.0f, 1.0f, -30040.0f, -1250.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-29967.5f, -975.0f, 4065.0f, 1.0f, -30040.0f, -975.0f, 4065.0f, 1.0f, -30040.0f, -1250.0f, 4065.0f, 1.0f, -29967.5f, -1250.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-28560.0f, -975.0f, 4065.0f, 1.0f, -29967.5f, -975.0f, 4065.0f, 1.0f, -29967.5f, -1250.0f, 4065.0f, 1.0f, -28560.0f, -1250.0f, 4065.0f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb20[10] = { // size: 0x320, address: 0x1F05E90
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-31508.75f, -1250.0f, -4965.0f, 1.0f, -30041.25f, -1250.0f, -4965.0f, 1.0f, -30041.25f, -2500.0f, -4965.0f, 1.0f, -31508.75f, -2500.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-28498.75f, -975.0f, -4965.0f, 1.0f, -29968.75f, -975.0f, -4965.0f, 1.0f, -29968.75f, 0.0f, -4965.0f, 1.0f, -28498.75f, 0.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-29968.75f, -975.0f, -4965.0f, 1.0f, -30041.25f, -975.0f, -4965.0f, 1.0f, -30041.25f, 0.0f, -4965.0f, 1.0f, -29968.75f, 0.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-29968.75f, -1250.0f, -4965.0f, 1.0f, -28498.75f, -1250.0f, -4965.0f, 1.0f, -28498.75f, -2500.0f, -4965.0f, 1.0f, -29968.75f, -2500.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-30041.25f, -1250.0f, -4965.0f, 1.0f, -29968.75f, -1250.0f, -4965.0f, 1.0f, -29968.75f, -2500.0f, -4965.0f, 1.0f, -30041.25f, -2500.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 8,
        /* .flg = */ 0,
        /* .p = */ {-30041.25f, -975.0f, -4965.0f, 1.0f, -31508.75f, -975.0f, -4965.0f, 1.0f, -31508.75f, 0.0f, -4965.0f, 1.0f, -30041.25f, 0.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-29968.75f, -975.0f, -4965.0f, 1.0f, -28498.75f, -975.0f, -4965.0f, 1.0f, -28498.75f, -1250.0f, -4965.0f, 1.0f, -29968.75f, -1250.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-30041.25f, -975.0f, -4965.0f, 1.0f, -29968.75f, -975.0f, -4965.0f, 1.0f, -29968.75f, -1250.0f, -4965.0f, 1.0f, -30041.25f, -1250.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 5,
        /* .flg = */ 0,
        /* .p = */ {-31508.75f, -975.0f, -4965.0f, 1.0f, -30041.25f, -975.0f, -4965.0f, 1.0f, -30041.25f, -1250.0f, -4965.0f, 1.0f, -31508.75f, -1250.0f, -4965.0f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb21[2] = { // size: 0xA0, address: 0x1F061B0
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {-31567.699f, -11.0000495f, -35600.0f, 1.0f, -31567.699f, -3489.0f, -35600.0f, 1.0f, -28432.3f, -3489.0f, -35600.0f, 1.0f, -28432.3f, -11.0000495f, -35600.0f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb49[14] = { // size: 0x460, address: 0x1F06250
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {34514.3f, -1819.89f, 28316.4f, 1.0f, 34514.3f, 67.254997f, 28316.4f, 1.0f, 33964.6f, 67.254997f, 28250.9f, 1.0f, 33964.6f, -1819.89f, 28250.9f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {36617.898f, -1819.89f, 26473.599f, 1.0f, 36617.898f, 67.254997f, 26473.599f, 1.0f, 34514.3f, 67.254997f, 28316.4f, 1.0f, 34514.3f, -1819.89f, 28316.4f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {36634.148f, -1819.89f, 25912.349f, 1.0f, 36634.148f, 67.254997f, 25912.349f, 1.0f, 36617.898f, 67.254997f, 26473.599f, 1.0f, 36617.898f, -1819.89f, 26473.599f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {35610.398f, -1703.61499f, 27424.099f, 1.0f, 35610.398f, -1319.0849f, 27424.099f, 1.0f, 35436.949f, -1319.0849f, 27295.25f, 1.0f, 35436.949f, -1703.61499f, 27295.25f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {34625.898f, -1707.15f, 28373.449f, 1.0f, 34625.898f, -1322.61999f, 28373.449f, 1.0f, 34803.949f, -1319.0849f, 28505.5f, 1.0f, 34803.949f, -1703.61499f, 28505.5f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {35610.398f, -1319.0849f, 27424.099f, 1.0f, 35610.398f, -1703.61499f, 27424.099f, 1.0f, 34803.949f, -1703.61499f, 28505.5f, 1.0f, 34803.949f, -1319.0849f, 28505.5f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {36559.75f, -1701.665f, 27983.449f, 1.0f, 36559.75f, -9.500000305706635e-05f, 27983.449f, 1.0f, 36813.3f, -9.500000305706635e-05f, 27996.4f, 1.0f, 36813.3f, -1701.665f, 27996.4f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {36559.75f, -9.500000305706635e-05f, 27983.449f, 1.0f, 36559.75f, -1701.665f, 27983.449f, 1.0f, 36549.148f, -1701.665f, 26191.949f, 1.0f, 36549.148f, -9.500000305706635e-05f, 26191.949f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {36813.3f, -1701.665f, 27996.4f, 1.0f, 36813.3f, -9.500000305706635e-05f, 27996.4f, 1.0f, 37743.199f, -9.500000305706635e-05f, 26817.55f, 1.0f, 37743.199f, -1701.665f, 26817.55f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {35490.0f, 0.0f, 27327.199f, 1.0f, 35490.0f, -1704.925f, 27327.199f, 1.0f, 34586.5f, -1704.925f, 28527.349f, 1.0f, 34586.5f, 0.0f, 28527.349f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {35434.6f, -1704.925f, 27281.599f, 1.0f, 35434.6f, 0.0f, 27281.599f, 1.0f, 34382.3f, 0.0f, 28605.099f, 1.0f, 34382.3f, -1704.925f, 28605.099f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 9,
        /* .flg = */ 0,
        /* .p = */ {35434.6f, 0.0f, 27281.599f, 1.0f, 35434.6f, -1704.925f, 27281.599f, 1.0f, 35490.0f, -1704.925f, 27327.199f, 1.0f, 35490.0f, 0.0f, 27327.199f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static CL_HITPOLY_PLANE stg_town_east_clActWallList_cb52[2] = { // size: 0xA0, address: 0x1F066B0
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {28415.849f, 0.0f, -36050.0f, 1.0f, 28415.849f, -1150.0f, -36050.0f, 1.0f, 32204.65f, -1150.0f, -36050.0f, 1.0f, 32204.65f, 0.0f, -36050.0f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ 0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static int (*stg_town_east_ev_prog[10])() = { 
    NULL, 
    stg_town_east_EvProgShadowOfSomenthing,
    stg_town_east_EvProgSandersBack,
    stg_town_east_EvProgFirstMonsterStart,
    stg_town_east_EvProgFirstMonsterCorpse,
    stg_town_east_EvProgFirstMonsterEnd,
    stg_town_east_EvProgBloodSwamp,
    stg_town_east_EvProgGetApartGateKey,
    stg_town_east_EvProgUseApartGateKey,
    stg_town_east_EvProgLookMemoFalled
};

// static Model_List stg_town_east_mdl_list

// static Enemy_List stg_town_east_en_list

static GfwFunc stg_town_east_SpecialDrawFunctions = {
    /* .specDraw = */ stg_town_east_Draw_CB_Tonnel,
    /* .preDraw = */ stg_town_east_CB_1stMoster_FogHosei,
    /* .postDraw = */ stg_town_east_CB_1stMonster_Filter,
    /* .charaDrawHook = */ stg_town_east_Monster1st_Look,
};

Stage_Data stage_town_east = {
    /* .evList = */ stg_town_east_ev_list,
    /* .evPos = */ stg_town_east_ev_pos,
    /* .evProg = */ stg_town_east_ev_prog,
    /* .giList = */ stg_town_east_gi_list,
    /* .mdlList = */ stg_town_east_mdl_list,
    /* .enList = */ stg_town_east_en_list,
    /* .stageInit = */ stg_town_east_EvStageInit,
    /* .roomInit = */ stg_town_east_EvRoomInit,
    /* .alltimeFunc = */ stg_town_east_EvAllTimeFunc,
    /* .glbCrd = */ 2,
    /* .pcModel = */ 0,
    /* .stgAnimInfo = */ stg_town_east_pjames_stage_anim,
    /* .bgmControl = */ stg_town_east_EvBgmControl,
    /* .gfwFunc = */ stg_town_east_SpecialDrawFunctions,
    /* .charaDataClear = */ stg_town_east_EvCharaDataClear,
    /* .soundCallAfterLoad = */ NULL,
    /* .reserve11 = */ 0,
};

static u_long128* anim_adr; // size: 0x4, address: 0x1F08200
static char* dds_adr[4]; // size: 0x10, address: 0x1F07DD0
static u_long128* wp_mdl; // size: 0x4, address: 0x1F08208
static u_long128* wp_anm; // size: 0x4, address: 0x1F08210
static int sig_timer_b; // size: 0x4, address: 0x1F08218
static int sig_timer_b2; // size: 0x4, address: 0x1F08220
static int sig_num_a; // size: 0x4, address: 0x1F08228
static int sig_num_b; // size: 0x4, address: 0x1F08230

static int stg_town_east_EvProgShadowOfSomenthing(void) {
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos0); // @ 0x01F07E50
    UNMIGRATED(Event_CamSetData stg_town_east_cam_data_01F07DE0); // @ 0x01F07DE0
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos1); // @ 0x01F07E60
    UNMIGRATED(sceVu0FVECTOR stg_town_east_scu_pos_01F07E80); // @ 0x01F07E80
    UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_01F07E20); // @ 0x01F07E20
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos2); // @ 0x01F07E70
    sceVu0FVECTOR scu_rot; // r29+0x10

    
    
    
    
    
    
    
    
    demo_number = 5;
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_pos0, -QUARTER_TURN);
            EV_PROG_STEP(27);
    
        case 27:
            DramaDemoFade();
            vcSetEventCamParamRefView(stg_town_east_cam_data_01F07DE0.pos, NULL, stg_town_east_cam_data_01F07DE0.itr, NULL, stg_town_east_cam_data_01F07DE0.roll, 1);
            
            vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
            PlayerEventMove(stg_town_east_pos1);
            if (PlayerEventMoveIsEnd()) EV_PROG_STEP(30);            
            if (shPadTrigger(0, key_config.skip)) EV_PROG_STEP(13);            
            break;
        
        case 30:
            DramaDemoFade();
            if (EvSubMessage(28)) {
                stg_town_east_info_01F07E20.adr_dds_top = stg_town_east_dds_adr[3];
                *(u_long128*) scu_rot = 0;
                CharaWorkCreate(EN_SCU_CHARA_KIND, 0, stg_town_east_scu_pos_01F07E80, scu_rot, 17);
                ev_timer = 0.0f;
                EV_PROG_STEP(23);
            
            case 23:
                if (DramaDemoMain(&stg_town_east_info_01F07E20)) 
                    if (shPadTrigger(0, key_config.skip)) EV_PROG_STEP(13);
                    else EV_PROG_STEP(16);                                    
            }
            break;
        
        case 16:
            ev_timer += shGetDT();
            if (ev_timer > 3.0f) EV_PROG_STEP(31);            
            if (shPadTrigger(0, key_config.skip)) EV_PROG_STEP(13);            
            DramaDemoSkipLast(&stg_town_east_info_01F07E20);
            break;
        
        case 31:
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_pos2, 0.0f);
            vcReturnPreAutoCamWork(1);

        case 32:
            DramaDemoFade();
            if (EvSubMessage(29)) {
                EV_PROG_STEP(13);
                
                case 13:
                    shCharacter_Manage_Delete(NULL, EN_SCU_CHARA_KIND, 0);
                    shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_pos2, 0.0f);
                    vcReturnPreAutoCamWork(1);
                    SCNowPlayableEventSwitch(sh2jms.player, false);
                    PlayerEventMoveCancel();
                    return 1;
            }            
    }
    return 0;
}

static int stg_town_east_EvProgSandersBack(void) {
    UNMIGRATED(sceVu0FVECTOR stg_town_east_pos); // @ 0x01F08990
    
    switch (ev_p_step) {
        
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);

        case 10:
            if (EvSubMessage(30))
                EV_PROG_STEP(27);            
            break;
            
        case 27:
            stg_town_east_pos[0] = 500.0f + sh2jms.player->pos.x;
            stg_town_east_pos[1] = sh2jms.player->pos.y;
            stg_town_east_pos[2] = sh2jms.player->pos.z;
            stg_town_east_pos[3] = 0.0f;
            EV_PROG_STEP(28);

        case 28:
            PlayerEventMove(stg_town_east_pos);
            if (PlayerEventMoveIsEnd()) EV_PROG_STEP(13);             
            break;
        
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

static int stg_town_east_EvProgFirstMonsterStart(void) {
    UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_01F07EC0);
    UNMIGRATED(sceVu0FVECTOR stg_town_east_jms_pos_01F07EF0);
    UNMIGRATED(float stg_town_east_jms_rot_01F08238);
    UNMIGRATED(sceVu0FVECTOR stg_town_east_scu_pos_01F07F00);
    UNMIGRATED(sceVu0FVECTOR stg_town_east_scu_rot);



 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


    switch (ev_p_step) {
        case 0:
            stg_town_east_info_01F07EC0.adr_dds_top = *stg_town_east_dds_adr;
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_demo_saisho_scu_anm, stg_town_east_anim_adr, 0);
            
            shCharacter_Manage_Delete(NULL, EN_SCU_CHARA_KIND, 4);
            radio.event = 2;
            EV_PROG_STEP(22);
    
        
        case 22:
            if (DramaDemoMain(&stg_town_east_info_01F07EC0)) EV_PROG_STEP(13);            
            break;
        
        case 13:            
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, ITEM_I_KAKUZAI_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, ITEM_I_RADIO_CHARA_KIND, 0);
            ItemGet(WOODEN_PLANK);
            ItemGet(SH2_ITEM_RADIO);
            item.equip = WOODEN_PLANK;
            CharaDataWeaponTranslation(WEAPON_KAKUZAI_CHARA_KIND, data_chr_jms_jms_wpkaku_anm, stg_town_east_wp_anm, data_chr_wp_wp_kakuzai_mdl, stg_town_east_wp_mdl);
            
            
            ConnectCharaWorkWeapon();
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_jms_pos_01F07EF0, stg_town_east_jms_rot_01F08238);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_chr_scu_scu_anm, stg_town_east_anim_adr, 0);
            
            CharaAdminReCreate(EN_SCU_CHARA_KIND, 4, 0, stg_town_east_scu_pos_01F07F00, stg_town_east_scu_rot, 16);
            
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_518);
            return 1;
    }
    return 0;
}


static int stg_town_east_EvProgFirstMonsterCorpse(void) {
    UNMIGRATED(float stg_town_east_jms_rot_01F08240); // @ 0x01F08240
    UNMIGRATED(sceVu0FVECTOR stg_town_east_jms_pos_01F07F70); // @ 0x01F07F70
    UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_a_01F07F40); // @ 0x01F07F40
    SubCharacter* scp;




    
    
    
    
    
    
    
    
    
    
    
    
    switch (ev_p_step) {
        case 0:
            radio.event = 0;
            stg_town_east_info_a_01F07F40.adr_dds_top = stg_town_east_dds_adr[1];
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_demo_saisho_scu_anm, stg_town_east_anim_adr, 0);
            
            scp = shCharacterGetSubCharacter(EN_SCU_CHARA_KIND, 4);
            scp->status &= ~(1 << SCP_STATUS_BIT_4);
            UNSET_GAME_FLAG(GAME_FLAG_518);
            EV_PROG_STEP(23);
        
        
        case 23:            
            if (DramaDemoMain(&stg_town_east_info_a_01F07F40)) EV_PROG_STEP(13);            
            break;
            
        case 13:
            CharaDataDeleteOne(ITEM_I_KAKUZAI_CHARA_KIND);
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, EN_SCU_CHARA_KIND, 0);
            scp = shCharacterGetSubCharacter(EN_SCU_CHARA_KIND, 4);
            scp->status |= (1 << SCP_STATUS_BIT_4);
            stg_town_east_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_chr_scu_scu_anm, stg_town_east_anim_adr, 1);
            
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_jms_pos_01F07F70, stg_town_east_jms_rot_01F08240);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            return 1;
    }
    return 0;
}

UNMIGRATED(CharaData_DemoList stg_town_east_enemy_list_01F07FF0[3]); // @ 0x01F07FF0
UNMIGRATED(float stg_town_east_jms_rot_01F08040); // @ 0x01F08040
UNMIGRATED(sceVu0FVECTOR stg_town_east_jms_pos_01F08030); // @ 0x01F08030
UNMIGRATED(DramaDemo_PlayInfo stg_town_east_info_b_01F07FC0); // @ 0x01F07FC0
static int stg_town_east_EvProgFirstMonsterEnd(void) {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    switch (ev_p_step) {
        case 0:
            stg_town_east_info_b_01F07FC0.adr_dds_top = stg_town_east_dds_adr[2];
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(24); 
    
       
        case 24:
            if (DramaDemoMain(&stg_town_east_info_b_01F07FC0)) EV_PROG_STEP(13);            
            break;
            
        case 13:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_RADIO_CHARA_KIND);
            shCharacterSetPosAfterDemo(sh2jms.player, stg_town_east_jms_pos_01F08030, stg_town_east_jms_rot_01F08040);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            CharaDataDeleteExtra();
            CharaAdminBackLoadEnemy(stg_town_east_enemy_list_01F07FF0);
            return 1;
    }
    return 0;
}

static int stg_town_east_EvProgBloodSwamp(void) {
    
    if (GET_GAME_FLAG(GAME_FLAG_44)) EvSubPictureDisplay(&data_pic_out_p_swamp_tex, 5); else EvSubPictureDisplay(&data_pic_out_p_swamp_tex, 4);
    // Am I missing a really easy way to line match this that doesnt look stupid?



    
}

static int stg_town_east_EvProgGetApartGateKey(void) {
    return EvSubItemGetAndAnim(SH2_ITEM_APART_GATE_KEY, 18);
}

static int stg_town_east_EvProgUseApartGateKey(void) {
    return EvSubItemUse0(SH2_ITEM_APART_GATE_KEY, 19, SH2_SOUND_16502, 0, (sceVu0FVECTOR) { -107378.95f, -708.8825f, 3999.731f, 0.0f }, 1);
}

static int stg_town_east_EvProgLookMemoFalled(void) {
    int i;
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(20001);
            EV_PROG_STEP(16);
            /* fallthrough */
        case 16:
            if (ev_cancel) {
                ev_prog_flag_set = 0;
                EV_PROG_STEP(13);
            } else if (PlayerEventAnimeSuccessFrame()) {
                shCharacterAnimePause(sh2jms.player);
                if (GET_GAME_FLAG(GAME_FLAG_51)) {
                    if (!GET_GAME_FLAG(GAME_FLAG_50)) {
                        EV_PROG_STEP(30);
                    } else {
                        EV_PROG_STEP(31);
                    }
                } else if (!GET_GAME_FLAG(GAME_FLAG_52) && !GET_GAME_FLAG(GAME_FLAG_54) && !GET_GAME_FLAG(GAME_FLAG_56) && !GET_GAME_FLAG(GAME_FLAG_58) && !GET_GAME_FLAG(GAME_FLAG_610)) {
                    EV_PROG_STEP(30);
                } else {
                    EV_PROG_STEP(31);
                }
            }
            break;
        
        case 30:
            if (GET_GAME_FLAG(GAME_FLAG_51)) {
                if (!EvSubMessage(26)) break;
            } else {
                if (!EvSubMessage(27)) break;
            }        
            EV_PROG_STEP(31);
            case 31:
                if ((!GET_GAME_FLAG(GAME_FLAG_51) || EvSubMessage(20)) && (!GET_GAME_FLAG(GAME_FLAG_53) || EvSubMessage(21)) && (!GET_GAME_FLAG(GAME_FLAG_55) || EvSubMessage(22)) && (!GET_GAME_FLAG(GAME_FLAG_57) || EvSubMessage(23)) && (!GET_GAME_FLAG(GAME_FLAG_59) || EvSubMessage(24)) && (!GET_GAME_FLAG(GAME_FLAG_611) || EvSubMessage(25))) {
                    if (ev_cancel) {
                        EV_PROG_STEP(13);
                        break;
                    }
                    shCharacterAnimeRestart(sh2jms.player);
                    EV_PROG_STEP(1);
                case 1:
                    if ((shCharacterAnimeIsEnd(sh2jms.player)) && (ev_cancel == 0)) {
                        EV_PROG_STEP(13);
                        case 13:
                            i = 0;
                            while (i < 5) {
                                UNSET_GAME_FLAG((i * 2) + 51);
                                i++;
                            }
                            SCNowPlayableEventSwitch(sh2jms.player, false);
                            return 1;
                    }
                    break;
                }
    }
    return 0;
}

static void stg_town_east_EvStageInit(void) {
    if (GET_GAME_FLAG(GAME_FLAG_1303)) 
        SET_GAME_FLAG(GAME_FLAG_1269);    
    if (GET_GAME_FLAG(GAME_FLAG_1302))
        SET_GAME_FLAG(GAME_FLAG_1268);    
    if (GET_GAME_FLAG(GAME_FLAG_1266))
        SET_GAME_FLAG(GAME_FLAG_1295);
}

static int stg_town_east_EvCharaDataClear(void) {
    return !GET_GAME_FLAG(GAME_FLAG_43);
}

static void stg_town_east_EvRoomInit(void) {
    UNMIGRATED(/* static */ CharaData_DemoList stg_town_east_chara_01F08060[4]); // @ 0x01F08060
    
    
    
    
    
    
    
    
    
    
    
    
    if (!GET_GAME_FLAG(GAME_FLAG_43)) {
        CharaDataLoadDemo(stg_town_east_chara_01F08060, 0);
        stg_town_east_anim_adr = CharaDataLoadExtra(data_demo_saisho_scu_anm, 0x200);
        
        stg_town_east_dds_adr[0] = CharaDataLoadExtra(data_demo_saisho_saisho_dds, 0x200);
        
        stg_town_east_dds_adr[1] = CharaDataLoadExtra(data_demo_saisho_saisho_c_dds, 0x200);
        
        stg_town_east_dds_adr[2] = CharaDataLoadExtra(data_demo_saisho_saisho_d_dds, 0x200);
        
        stg_town_east_wp_anm = CharaDataLoadExtra(data_chr_jms_jms_wpkaku_anm, 0x200);
        
        stg_town_east_wp_mdl = CharaDataLoadExtra(data_chr_wp_wp_kakuzai_mdl, 0x200);
        
        stg_town_east_dds_adr[3] = CharaDataLoadExtra(data_demo_machi_machi_dds, 0x200);
        
        fsSync(0, -1);
        radio.event = 1; radio.pos[0] = 47716.9f; radio.pos[1] = -268.4f; radio.pos[2] = 49627.9f;
    }
}

static void stg_town_east_EvAllTimeFunc(void) {
    int disp_ctrl_list[129];
    int pos_x; int pos_z; int pos;
    int i; int j;
    
    disp_ctrl_list[0] = 0;
    pos_x = shFloatToInt(16.0f + (sh2jms.player->pos.x / 20000.0f));
    pos_z = shFloatToInt(16.0f + (sh2jms.player->pos.z / 20000.0f));
    
    stg_town_east_sig_timer_b += shGetDF();
    
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            pos = (pos_z + j) + ((pos_x + i) << 5);
            switch (pos) {
                case 0x231:
                    stg_town_east_EvWallSetCb49(disp_ctrl_list);
                    break;
                case 0x22E:
                    stg_town_east_EvWallSetCb52(disp_ctrl_list);
                    break;
                case 0x1F0:
                    stg_town_east_EvTapeSetCb11(disp_ctrl_list);
                    break;
                case 0x1EF:
                    stg_town_east_EvTapeSetCb12(disp_ctrl_list);
                    break;
                case 0x1D1:
                    stg_town_east_EvCorpseSetCb18(disp_ctrl_list);
                    break;
                case 0x1D0:
                    stg_town_east_EvWallSetCb19(disp_ctrl_list);
                    break;
                case 0x1CF:
                    stg_town_east_EvWallSetCb20(disp_ctrl_list);
                    break;
                case 0x1CE:
                    stg_town_east_EvWallSetCb21(disp_ctrl_list);
                    break;
                case 0x1B1:
                    stg_town_east_EvCorpseSetCb26(disp_ctrl_list);
                    break;
                case 0x1B0:
                    stg_town_east_EvSignalControlCb27(disp_ctrl_list);
                    break;
                case 0x1AF:
                    stg_town_east_EvSignalControlCb28(disp_ctrl_list);
                    break;
                case 0x1AE:
                    stg_town_east_EvSignalControlCb29(disp_ctrl_list);
                    break;
                case 0x190:
                    stg_town_east_EvSignalControlCb35(disp_ctrl_list);
                    break;
                case 0x18F:
                    stg_town_east_EvSignalControlCb36(disp_ctrl_list);
                    break;
                case 0x18E:
                    stg_town_east_EvSignalControlCb37(disp_ctrl_list);
                    break;
                case 0x150:
                    stg_town_east_EvLockSetCb46(disp_ctrl_list);
                    break;
            }
        }
    }
    EvDispControlModelExec(disp_ctrl_list);
}

static int stg_town_east_EvBgmControl(void) {
    if (GET_GAME_FLAG(GAME_FLAG_518)) {
        return 4;
    }
    return GET_GAME_FLAG(GAME_FLAG_41) != 0;
}

static void stg_town_east_EvLockSetCb46(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_49)) {
        EvDispControlModelEntry(list, 0x2E, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0x2E, 1);
}

static void stg_town_east_EvCorpseSetCb18(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        clAddDynamicWall(stg_town_east_clActWallList_cb18);
        EvDispControlModelEntry(list, 0x12, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0x12, -1);
}

static void stg_town_east_EvCorpseSetCb26(int* list) {
    return;
}

static void stg_town_east_EvWallSetCb19(int* list) {
    EvDispControlModelEntry(list, 0x13, -1); // @todo: add room id
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x13, 0);
        clAddDynamicWall(stg_town_east_clActWallList_cb19);
    }
}

static void stg_town_east_EvWallSetCb20(int* list) {
    EvDispControlModelEntry(list, 0x14, -1); // @todo: add room id
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x14, 0);
        clAddDynamicWall(stg_town_east_clActWallList_cb20);
    }
}

static void stg_town_east_EvWallSetCb21(int* list) {
    EvDispControlModelEntry(list, 0x15, -1);
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        clAddDynamicWall(stg_town_east_clActWallList_cb21);
        EvDispControlModelEntry(list, 0x15, 0);
        return;
    }
    sh2shd_add_map_to_shadow_off_work(0x15);
    sh2shd_off_obj(0x15, 8); // @todo: add room id and obj id
}

static void stg_town_east_EvWallSetCb49(int* list) {
    if (!GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x31, 1); // @todo: add room id
        clAddDynamicWall(&stg_town_east_clActWallList_cb49[4]);
        return;
    }
    EvDispControlModelEntry(list, 0x31, 0);
    clAddDynamicWall(stg_town_east_clActWallList_cb49);
}

static void stg_town_east_EvWallSetCb52(int* list) {
    sh2shd_add_map_to_shadow_off_work(0x34);
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x34, 1);
        clAddDynamicWall(stg_town_east_clActWallList_cb52);
        sh2shd_off_obj(0x34, 0x37); // @todo: add room id and obj id
        return;
    }
    EvDispControlModelEntry(list, 0x34, 0);
    sh2shd_off_obj(0x34, 0x36);
}

static void stg_town_east_EvSignalControlCb27(int* list) {
    int i;

    
    
    
    
    
    
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1200) stg_town_east_sig_num_b = 3;
    else if ((stg_town_east_sig_timer_b % 3100) < 1500) stg_town_east_sig_num_b = 2;
    else stg_town_east_sig_num_b = 1;
    i = stg_town_east_sig_num_b;
    if (stg_town_east_sig_timer_b2 < stg_town_east_sig_timer_b) {
        stg_town_east_sig_num_b = 0;
        stg_town_east_sig_timer_b2 += (shRandI() % 1000) + 400;
    }
    
    if (stg_town_east_sig_num_b == 1) 
        EvDispControlModelEntry(list, 0x1B, 2);
    else if (stg_town_east_sig_num_b == 2)
        EvDispControlModelEntry(list, 0x1B, 1);
    else if (stg_town_east_sig_num_b == 3) 
        EvDispControlModelEntry(list, 0x1B, 0);
    else
        EvDispControlModelEntry(list, 0x1B, 5);
    
    stg_town_east_sig_num_b = i;
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_a = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2700) stg_town_east_sig_num_a = 0;
    else stg_town_east_sig_num_a = 1;
    
    if (stg_town_east_sig_num_a == 1)
        EvDispControlModelEntry(list, 0x1B, 3);
    else 
        EvDispControlModelEntry(list, 0x1B, 4);
}

static void stg_town_east_EvSignalControlCb28(int* list) {
    int i;

    if ((stg_town_east_sig_timer_b % 3100) < 1200) stg_town_east_sig_num_b = 3;
    else if ((stg_town_east_sig_timer_b % 3100) < 1500) stg_town_east_sig_num_b = 2;
    else stg_town_east_sig_num_b = 1;
    i = stg_town_east_sig_num_b;
    if (stg_town_east_sig_timer_b2 < stg_town_east_sig_timer_b) {
        stg_town_east_sig_num_b = 0;
        stg_town_east_sig_timer_b2 += shRandI() % 1000 + 400;
    }
    
    if (stg_town_east_sig_num_b == 1) 
        EvDispControlModelEntry(list, 0x1C, 2);
    else if (stg_town_east_sig_num_b == 2)
        EvDispControlModelEntry(list, 0x1C, 1);
    else if (stg_town_east_sig_num_b == 3)
        EvDispControlModelEntry(list, 0x1C, 0);
    else
        EvDispControlModelEntry(list, 0x1C, 5);
    
    stg_town_east_sig_num_b = i;
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_a = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2700) stg_town_east_sig_num_a = 0;
    else stg_town_east_sig_num_a = 1;
    
    if (stg_town_east_sig_num_a == 1) 
        EvDispControlModelEntry(list, 0x1C, 3);
    else 
        EvDispControlModelEntry(list, 0x1C, 4);
}



static void stg_town_east_EvSignalControlCb29(int* list) {
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1200) stg_town_east_sig_num_b = 3;
    else if ((stg_town_east_sig_timer_b % 3100) < 1500) stg_town_east_sig_num_b = 2;
    else stg_town_east_sig_num_b = 1;
    
    
    
    
    
    
    if (stg_town_east_sig_num_b == 1) 
        EvDispControlModelEntry(list, 0x1D, 2);
    else if (stg_town_east_sig_num_b == 2)
        EvDispControlModelEntry(list, 0x1D, 1);
    else if (stg_town_east_sig_num_b == 3)
        EvDispControlModelEntry(list, 0x1D, 0);
    else
        EvDispControlModelEntry(list, 0x1D, 5);
    
    
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_a = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2700) stg_town_east_sig_num_a = 0;
    else stg_town_east_sig_num_a = 1;
    
    if (stg_town_east_sig_num_a == 1) 
        EvDispControlModelEntry(list, 0x1D, 3);
    else 
        EvDispControlModelEntry(list, 0x1D, 4);
}

static void stg_town_east_EvSignalControlCb35(int* list) {
    int i;

    
    
    
    
    
    
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1200) stg_town_east_sig_num_b = 3;
    else if ((stg_town_east_sig_timer_b % 3100) < 1500) stg_town_east_sig_num_b = 2;
    else stg_town_east_sig_num_b = 1;
    i = stg_town_east_sig_num_b;
    if (stg_town_east_sig_timer_b2 < stg_town_east_sig_timer_b) {
        stg_town_east_sig_num_b = 0;
        stg_town_east_sig_timer_b2 += shRandI() % 1000 + 400;
    }
    
    if (stg_town_east_sig_num_b == 1) 
        EvDispControlModelEntry(list, 0x23, 2);
    else if (stg_town_east_sig_num_b == 2)
        EvDispControlModelEntry(list, 0x23, 1);
    else if (stg_town_east_sig_num_b == 3)
        EvDispControlModelEntry(list, 0x23, 0);
    else
        EvDispControlModelEntry(list, 0x23, 5);
    
    stg_town_east_sig_num_b = i;
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_a = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2700) stg_town_east_sig_num_a = 0;
    else stg_town_east_sig_num_a = 1;
    
    if (stg_town_east_sig_num_a == 1) 
        EvDispControlModelEntry(list, 0x23, 3);
    else 
        EvDispControlModelEntry(list, 0x23, 4);
}

static void stg_town_east_EvSignalControlCb36(int* list) {
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1200) stg_town_east_sig_num_b = 3;
    else if ((stg_town_east_sig_timer_b % 3100) < 1500) stg_town_east_sig_num_b = 2;
    else stg_town_east_sig_num_b = 1;
    
    
    
    
    
    
    if (stg_town_east_sig_num_b == 1) 
        EvDispControlModelEntry(list, 0x24, 2);
    else if (stg_town_east_sig_num_b == 2)
        EvDispControlModelEntry(list, 0x24, 1);
    else if (stg_town_east_sig_num_b == 3)
        EvDispControlModelEntry(list, 0x24, 0);
    else
        EvDispControlModelEntry(list, 0x24, 5);
    
    
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_a = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2700) stg_town_east_sig_num_a = 0;
    else stg_town_east_sig_num_a = 1;
    
    if (stg_town_east_sig_num_a == 1)
        EvDispControlModelEntry(list, 0x24, 3);
    else
        EvDispControlModelEntry(list, 0x24, 4);
}

static void stg_town_east_EvSignalControlCb37(int* list) {
    int i; // r2 // @note: idk how they used it

    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0x25, 0);
    }  
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_b = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2750) stg_town_east_sig_num_b = 3;
    else if ((stg_town_east_sig_timer_b % 3100) < 3050) stg_town_east_sig_num_b = 2;
    else stg_town_east_sig_num_b = 1;
    
    if (stg_town_east_sig_timer_b2 < stg_town_east_sig_timer_b) {
        stg_town_east_sig_num_b = 0;
        stg_town_east_sig_timer_b2 += shRandI() % 1000 + 400;
    }
    
    if (stg_town_east_sig_num_b == 1) 
        EvDispControlModelEntry(list, 0x25, 3);
    else if (stg_town_east_sig_num_b == 2)
        EvDispControlModelEntry(list, 0x25, 2);
    else if (stg_town_east_sig_num_b == 3)
        EvDispControlModelEntry(list, 0x25, 1);
    else 
        EvDispControlModelEntry(list, 0x25, 6);
    
    
    
    
    if ((stg_town_east_sig_timer_b % 3100) < 1800) stg_town_east_sig_num_a = 1;
    else if ((stg_town_east_sig_timer_b % 3100) < 2700) stg_town_east_sig_num_a = 0;
    else stg_town_east_sig_num_a = 1;
    
    if (stg_town_east_sig_num_a == 1)
        EvDispControlModelEntry(list, 0x25, 4);
    else
        EvDispControlModelEntry(list, 0x25, 5);
}

static void stg_town_east_EvTapeSetCb11(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0xB, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0xB, 1);
    clAddDynamicWall(stg_town_east_clActWallList_cb11);
}

/* static */ void stg_town_east_EvTapeSetCb12(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0xC, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0xC, 1);
    clAddDynamicWall(stg_town_east_clActWallList_cb12);
}

static float stg_town_east_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_CB_1stMoster_FogHosei);

static void stg_town_east_CB_1stMonster_Filter(void) {
    FilterParams* pfp;
    sceVu0FVECTOR campos;
    
    vwGetViewPosition(campos);
    if ((campos[2] < 50000.0f) && (campos[1] > -2000.0f) && ((DramaDemoNumber() == 6) || (DramaDemoNumber() == 7))) {
        pfp = sh2gfw_Get_FilterCommandParams();
        sh2gfw_Reset_FilterCommand();
        shGsFilterWork.GsFilterKind = 6;
        pfp->SoftIter = 3;
        pfp->SoftCit = 25;
        pfp->SoftAref = 216;
        pfp->SoftShift = -4;
        pfp->base_Ix = -8;
        pfp->base_Iy = -8;
        return;
    }
    if (shGsFilterWork.GsFilterKind < 15) {
        sh2gfw_Reset_FilterCommand();
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Draw_CB_Tonnel);

#ifdef NON_MATCHING
static void stg_town_east_Monster1st_Look(void* sp, float* ambient) {
    SubCharacter* scp;
    float fac;
    float ftmp;

    if (DramaDemoNumber() == 6 || DramaDemoNumber() == 7) {
        scp = sp;
        if (scp->pos.z >= 49000.0f) {
            fac = stg_town_east_LinearTrim(0.1f, 1.0f, 53000.0f, 49000.0f, scp->pos.z);            
            ftmp = ambient[3];
            sceVu0ScaleVector(ambient, ambient, fac);
            ambient[3] = ftmp;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Monster1st_Look);
#endif
