#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/playing_info.h"

#include "vec.h"

#include "Collision/cl_main.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter/sh2_character_manage.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/picture.h"
#include "Event/demoview.h"
#include "Event/chara_admin.h"
#include "Event/stg_name.h"

#include "Effect/screen_effect.h"
#include "sound/sh_sound.h"
#include "Multi_thr/filesys/fcread.h"
#include "GFW/sh2_DrawEnvData.h"
#include "view/vc_main.h"

#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_scu.h"
#include "data/daily.thu/data_chr_red.h"
#include "data/daily.thu/data_demo_ap_boss.h"
#include "data/daily.thu/data_pic_map.h"

#include "Chacter/anime.h"

static void stg_apart_stair_AP_Hosei_Light(void);
static int  stg_apart_stair_EvProgUseYardKey(void);
static int  stg_apart_stair_EvProgGetApartMap(void);
static int  stg_apart_stair_EvProgGetApartWestMap(void);
static int  stg_apart_stair_EvProgGetCannedJuice(void);
static int  stg_apart_stair_EvProgApartBoss(void);
static int  stg_apart_stair_EvProgApartBossSiren(void);
static int  stg_apart_stair_EvProgApartBossEnd(void);
static void stg_apart_stair_EvRoomInit(void);
static void stg_apart_stair_EvAllTimeFunc(void);

AnimeInfo stg_apart_stair_pjames_stage_anim[24] = {
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
        /* .name = */ 20029,
        /* .frame = */ 15,
        /* .speed = */ 1024,
        /* .start = */ 1464,
        /* .end = */ 1478,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20030,
        /* .frame = */ 24,
        /* .speed = */ 2048,
        /* .start = */ 1479,
        /* .end = */ 1502,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20031,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1503,
        /* .end = */ 1532,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 20032,
        /* .frame = */ 30,
        /* .speed = */ 1024,
        /* .start = */ 1533,
        /* .end = */ 1562,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

/**
 * @note packed data format.
 * @todo: make a system to generate these.
 * see `tools/alessatool/kaitai/data/data_includes.py` for a full format string
 */
u_int stg_apart_stair_ev_pos[121] = {
    0x47C03072, 0xE5DEE6A4, 0x5F5DC7C0, 0x47C4E38D, 0x89CA8000, 0x5F5DC5C4, 
    0xC7C09400, 0xC0008000, 0x5A40C6A8, 0xC799D9C0, 0xFC3D8000, 0xD087C730, 
    0x8000C799, 0xC73114EF, 0xC799E8DA, 0x39368000, 0xF273C731, 0x8000C799, 
    0xC731211C, 0x47C1773A, 0x89198000, 0x5FCBC7C0, 0x4686C400, 0xF6008000, 
    0x5FBB46D1, 0xC7C65700, 0xA8008000, 0x5E40C6AC, 0x480A45BC, 0x631CE6C2, 
    0xB2A4C69A, 0x45BC5D00, 0xE6C2480A, 0xC69A631C, 0x5A18D883, 0x5D00B2A4, 
    0xC79AB779, 0x84748000, 0x5FD0C75C, 0xC79AB779, 0xF4798000, 0x5FCFC741, 
    0xC7996C39, 0x1D028000, 0x5FD0C730, 0xC7C07A66, 0x40028000, 0x5FD9C683, 
    0x47B9FD1F, 0x1B89D4C4, 0x5FD9C7A2, 0xC7C4D500, 0x7C008000, 0x6614C6B5, 
    0xC7CD2C7A, 0x2D478000, 0x630C45BB, 0xC79D2180, 0xFDFE8000, 0x630BC776, 
    0xC79E4C7A, 0x2D478000, 0x630C45BB, 0xC7C07B00, 0xB406E708, 0x5FC5C68C, 
    0xC7CC0D80, 0xE8008000, 0x604C4628, 0xC7C07B00, 0xB406EB08, 0x5FC5C68C,
    0x47583602, 0xE8008000, 0x5FD04628, 0xC7995E80, 0x9A02E707, 0x604CC762,
    0xC7995E80, 0x9A02EB08, 0x604CC762, 0x479A32FE, 0xE8008000, 0x5FD04628, 
    0xC76C36CD, 0xFD813F33, 0x6013C6AB, 0xC74263E3, 0xEFFF8000, 0xDF5DC72B, 
    0x36CD9E40, 0xE63EC76C, 0xC6ABFD81, 0xAC666013, 0x8000C7C1, 0x4707F878, 
    0x36CD5F5D, 0xEA3FC76C, 0xC6ABFD81, 0xDF316013, 0x8000476C, 0x4707F87A, 
    0x46405F5D, 0x8000480A, 0xC6A0AE05, 0x8CFD5FDF, 0x800047C2, 0xC76DBEFB, 
    0x46405FDF, 0xE6A4480A, 0xC694DCF8, 0x8D5A5FDF, 0x800047C2, 0xC68D8231, 
    0x50405FDF, 0xE9074808, 0xC693E90A, 0x28035F12, 0x80004807, 0xC69D6D27, 
    0x5FCB
};

/**
 * @note the interpretation of `ev_pos` depends on these flags. it's possible
 * this was also a generated table.
 */
Event_List stg_apart_stair_ev_list[36] = {
    {
        /* .flag = */ -0x7F6E0000,
        /* .cond = */ 0x20003000,
        /* .rslt0 = */ 0x400C4160,
        /* .rslt1 = */ 0x10005B2,
    },
    {
        /* .flag = */ 0x920000,
        /* .cond = */ 0x20003000,
        /* .rslt0 = */ -0x80000000,
        /* .rslt1 = */ 0x1000000,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20184000,
        /* .rslt0 = */ -0x60000000,
        /* .rslt1 = */ 0x14549,
    },
    {
        /* .flag = */ 0x5E0000,
        /* .cond = */ 0x20240004,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x1005E,
    },
    {
        /* .flag = */ 0x5E0000,
        /* .cond = */ 0x202E0004,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x1005E,
    },
    {
        /* .flag = */ 0x5E0000,
        /* .cond = */ 0x20380004,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x1005E,
    },
    {
        /* .flag = */ 0x5E0000,
        /* .cond = */ 0x20420004,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x1005E,
    },
    {
        /* .flag = */ 0x8F85B2,
        /* .cond = */ 0x10000000,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x1408F,
    },
    {
        /* .flag = */ -0x7F6FFF6F,
        /* .cond = */ 0x10000000,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x18091,
    },
    {
        /* .flag = */ -0x7F6DFF6D,
        /* .cond = */ 0x10000000,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x1C000,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x204C2000,
        /* .rslt0 = */ 0x405811C0,
        /* .rslt1 = */ 0x1000000,
    },
    {
        /* .flag = */ 0x190000,
        /* .cond = */ 0x20643000,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x8019,
    },
    {
        /* .flag = */ 0x1A0000,
        /* .cond = */ 0x20705004,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0xC01A,
    },
    {
        /* .flag = */ 0x1A0000,
        /* .cond = */ 0x207E6004,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0xC01A,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20903000,
        /* .rslt0 = */ -0x70000000,
        /* .rslt1 = */ 0x7FC53B,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x209C3000,
        /* .rslt0 = */ -0x70000000,
        /* .rslt1 = */ 0x7FC53C,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20A82000,
        /* .rslt0 = */ -0x70000000,
        /* .rslt1 = */ 0x7FC53D,
    },
    {
        /* .flag = */ -0x7FA60000,
        /* .cond = */ 0x20B42000,
        /* .rslt0 = */ 0x40C011A0,
        /* .rslt1 = */ 0x1000543,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ -0x5F4BDE54,
        /* .rslt0 = */ 0x30000000,
        /* .rslt1 = */ 0x405A,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20B42000,
        /* .rslt0 = */ -0x80000000,
        /* .rslt1 = */ 0x1000544,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20CC1000,
        /* .rslt0 = */ 0x40D821A0,
        /* .rslt1 = */ 0x1C00000,
    },
    {
        /* .flag = */ -0x7FC30000,
        /* .cond = */ 0x20E41000,
        /* .rslt0 = */ 0x40F021A0,
        /* .rslt1 = */ 0x1C00534,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20E41004,
        /* .rslt0 = */ 0x70000000,
        /* .rslt1 = */ 0x1FFC03D,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x20FC2000,
        /* .rslt0 = */ 0x410810E0,
        /* .rslt1 = */ 0x1000560,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21142000,
        /* .rslt0 = */ 0x41201100,
        /* .rslt1 = */ 0x1000582,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x212C2000,
        /* .rslt0 = */ -0x70000000,
        /* .rslt1 = */ 0x13F8561,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21382000,
        /* .rslt0 = */ 0x41441120,
        /* .rslt1 = */ 0x1000583,
    },
    {
        /* .flag = */ -0x7FC40000,
        /* .cond = */ 0x21501000,
        /* .rslt0 = */ 0x415C50C0,
        /* .rslt1 = */ 0x100053E,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21501000,
        /* .rslt0 = */ -0x80000000,
        /* .rslt1 = */ 0x100053F,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x216A1000,
        /* .rslt0 = */ 0x417620E0,
        /* .rslt1 = */ 0x100055F,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21821000,
        /* .rslt0 = */ 0x418E2120,
        /* .rslt1 = */ 0x1000581,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x219A4000,
        /* .rslt0 = */ 0x41A63140,
        /* .rslt1 = */ 0x100059C,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21B24000,
        /* .rslt0 = */ 0x41BE3160,
        /* .rslt1 = */ 0x10005B4,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21CA4000,
        /* .rslt0 = */ -0x70000000,
        /* .rslt1 = */ 0x23FC5B6,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x21D63000,
        /* .rslt0 = */ -0x70000000,
        /* .rslt1 = */ 0x13F859F,
    },
    {
        /* .flag = */ 0x0,
        /* .cond = */ 0x0,
        /* .rslt0 = */ 0x0,
        /* .rslt1 = */ 0x0,
    }
};

Item_List stg_apart_stair_gi_list[6] = {
    {
        /* .posX = */ -60082.898f,
        /* .posZ = */ -21225.91f,
        /* .posY = */ 60183,
        /* .rotY = */ 15452,
        /* .st = */ 536871697, // @todo format ST values
    },
    {
        /* .posX = */ -100185.007f,
        /* .posZ = */ -20166.859f,
        /* .posY = */ 56305,
        /* .rotY = */ 32768,
        /* .st = */ 2147484583,
    },
    {
        /* .posX = */ -100147.92f,
        /* .posZ = */ -20119.97f,
        /* .posY = */ 56303,
        /* .rotY = */ 32768,
        /* .st = */ 2147484791,
    },
    {
        /* .posX = */ -99666.578f,
        /* .posZ = */ -20003.619f,
        /* .posY = */ 52420,
        /* .rotY = */ 13242,
        /* .st = */ 2684355705,
    },
    {
        /* .posX = */ -78963.0f,
        /* .posZ = */ -45383.0f,
        /* .posY = */ 52479,
        /* .rotY = */ 46728,
        /* .st = */ 2684355347,
    },
    {
        /* .posX = */ 0.0f,
        /* .posZ = */ 0.0f,
        /* .posY = */ 0,
        /* .rotY = */ 0,
        /* .st = */ 3758096384,
    }
};

CL_HITPOLY_PLANE stg_apart_stair_clActWallList_ap88[2] = {
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_12,
        /* .flg = */ 0,
        /* .p = */ {99850.0f, -2605.1999f, -99415.0f, 1.0f, 
                    99850.0f, -1322.0f,    -99415.0f, 1.0f, 
                    99850.0f, -1322.0f, -98579.5f,    1.0f, 
                    99850.0f, -2605.1999f, -98579.5f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ MATERIAL_TYPE_0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 0.0f, 1.0f},
    }
};

sceVu0FVECTOR stg_apart_stair_colvec = { 0.3f, 0.3f, 0.3f, 0.0f };
sceVu0FVECTOR stg_apart_stair_colref = { 1.0f, 1.0f, 1.0f, 0.0f };
sceVu0FVECTOR stg_apart_stair_ldir = { 0.0f, 0.0f, 1.0f, 0.0f };

DynamicLight stg_apart_stair_DynamicLW = {
    /* .nowCamDir = */ {0},
    /* .beforeCamDir = */ {0},
    /* .nowDir = */ {1.0f, 0.0f, 0.0f, 0.0f},
    /* .beforeDir = */ {1.0f, 0.0f, 0.0f, 0.0f},
};

int (*stg_apart_stair_ev_prog[8])() = { 
    NULL, 
    stg_apart_stair_EvProgUseYardKey,
    stg_apart_stair_EvProgGetApartMap,
    stg_apart_stair_EvProgGetApartWestMap,
    stg_apart_stair_EvProgGetCannedJuice,
    stg_apart_stair_EvProgApartBoss, 
    stg_apart_stair_EvProgApartBossSiren, 
    stg_apart_stair_EvProgApartBossEnd
};

Model_List stg_apart_stair_mdl_list[2] = {
    {
        /* .kind = */ 1837,
        /* .id = */ 0,
        /* .flagOff = */ 94,
        /* .flagOn = */ 0,
        /* .pos = */ {-78787.0f, -29.999998f, -45339.023f, 0.0f},
        /* .rot = */ {-3.141592f, -0.929592f, -3.141592f, 0.0f},
    },
    {
        /* .kind = */ 0,
        /* .id = */ 0,
        /* .flagOff = */ 0,
        /* .flagOn = */ 0,
        /* .pos = */ {0.0f, 0.0f, 0.0f, 1.0f},
        /* .rot = */ {0.0f, 0.0f, 0.0f, 1.0f},
    }
};

GfwFunc stg_apart_stair_SpecialDrawFunctions = {
    /* .specDraw = */ NULL,
    /* .preDraw = */ stg_apart_stair_AP_Hosei_Light,
    /* .postDraw = */ NULL,
    /* .charaDrawHook = */ NULL,
};

Enemy_List stg_apart_stair_en_list[2] = {
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 9,
        /* .posX = */ 100800,
        /* .posZ = */ -101000,
        /* .posY = */ -1700,
        /* .rotY = */ -6433,
        /* .status = */ 13,
        /* .condition = */ 320,
    },
    {0}
};

Stage_Data stage_apart_stair = {
    /* .evList = */ stg_apart_stair_ev_list,
    /* .evPos = */ stg_apart_stair_ev_pos,
    /* .evProg = */ stg_apart_stair_ev_prog,
    /* .giList = */ stg_apart_stair_gi_list,
    /* .mdlList = */ stg_apart_stair_mdl_list,
    /* .enList = */ stg_apart_stair_en_list,
    /* .stageInit = */ NULL,
    /* .roomInit = */ stg_apart_stair_EvRoomInit,
    /* .alltimeFunc = */ stg_apart_stair_EvAllTimeFunc,
    /* .glbCrd = */ Glb_crd_apart,
    /* .pcModel = */ 1,
    /* .stgAnimInfo = */ stg_apart_stair_pjames_stage_anim,
    /* .bgmControl = */ NULL,
    /* .gfwFunc = */ &stg_apart_stair_SpecialDrawFunctions,
    /* .charaDataClear = */ NULL,
    /* .soundCallAfterLoad = */ NULL,
    /* .reserve11 = */ 0,
};

static void stg_apart_stair_AP_Hosei_Light(void) {
    int* mp = Get_NowMapId(); // r2
    Q_WORDDATA tmp; // r29+0x10
    float inner; // r29+0x50
    float factor; // r29+0x50

    switch (*mp) {
        case 0x9000A:
            tmp = Env_ctl.compo_shadow_col;
            tmp.ui32[3] = 10;
            sh2gfw_Set_FilterData(sh2gfw_Get_NightOrDay(), 0, &tmp);
            Env_ctl.camera_parms[3] = 50.0f;
            break;
        
        case 0x90058: {
            sceVu0FVECTOR tmp;
            sceVu0FVECTOR plane; // r29+0x30
            sceVu0FVECTOR aimdir; // r29+0x40
            if (DramaDemoNumber() == 19) {
                sh2gfw_Set_DemoRefrectionHighLight(stg_apart_stair_ldir, stg_apart_stair_colref);
                break;
            }
            
            sceVu0CopyVector(stg_apart_stair_DynamicLW.BeforeCamDir, stg_apart_stair_DynamicLW.NowCamDir);
            sceVu0CopyVector(stg_apart_stair_DynamicLW.BeforeDir, stg_apart_stair_DynamicLW.NowDir);
            sh2gde_Get_EyeDir(&stg_apart_stair_DynamicLW);
            inner /* inner product */ = shVectorDotProductXyz(stg_apart_stair_DynamicLW.NowCamDir, stg_apart_stair_DynamicLW.BeforeDir);
            shVectorCrossProduct(plane, stg_apart_stair_DynamicLW.NowCamDir, stg_apart_stair_DynamicLW.BeforeDir);
            shNormalizeVector(plane, plane);
            shVectorCrossProduct(aimdir, stg_apart_stair_DynamicLW.BeforeDir, plane);
            factor = 0.1f / (2.0f + inner);
            if (factor < 0.0333f) {
                factor = 0;
            }
            shScaleVector(aimdir, aimdir, factor);
            shAddVector(tmp, aimdir, stg_apart_stair_DynamicLW.BeforeDir);
            shNormalizeVector(tmp,stg_apart_stair_DynamicLW.NowDir);
            sh2gfw_Set_DemoRefrectionHighLight(stg_apart_stair_DynamicLW.NowDir, stg_apart_stair_colref);
            sh2gfw_Set_PallarelLight(stg_apart_stair_DynamicLW.NowDir, stg_apart_stair_colvec, 1);
            break;
        }
    }
}

#line 122
static int stg_apart_stair_EvProgUseYardKey(void) {
    EvSubItemUse0(SH2_ITEM_26,     4,
                  SH2_SOUND_19025, 0,
                  (sceVu0FVECTOR){-98800.0f, -500.0f, -16800.0f, 0.0f}, 1);
}

#line 132
static int stg_apart_stair_EvProgGetApartMap(void) {
    EvSubMapGet(data_pic_map_apartmape1f_tex,
                2);
}

#line 141
static int stg_apart_stair_EvProgGetApartWestMap(void) {
    EvSubMapGet(data_pic_map_apartmapw_tex,
                3);
}

#line 149
static int stg_apart_stair_EvProgGetCannedJuice(void) {
    EvSubItemGetAndAnim(46, // kind
                        1); // message
}

#line 157
static int stg_apart_stair_EvProgApartBoss(void) {
    static DramaDemo_MessageTime stg_apart_stair_boss_anim[2] = {
        {
            /* .start = */ 1171,
            /* .end = */ 6306,
        },
        {
            /* .start = */ 6009,
            /* .end = */ 0,
        }
    };
    static DramaDemo_PlayInfo stg_apart_stair_boss = {
        /* .demoNo = */ 19,
        /* .adrDdsTop = */ MemShare_gp_data_buf,
        /* .adrAnim = */ stg_apart_stair_boss_anim,
        /* .adrMsgTime = */ NULL,
        /* .msgStart = */ 0,
        /* .voiceSdNo = */ 0,
        /* .adrVoice = */ NULL,
        /* .streamNo = */ 60002,
        /* .streamStart = */ 0.0f,
        /* .addPosX = */ 0.0f,
        /* .addPosZ = */ 0.0f,
    }; // @ 0x01F03270
    static CharaData_DemoList stg_apart_stair_chara_data_01F032A0[4] = {
        {
            /* .kind = */ HHL_JMS_CHARA_KIND,
            /* .model = */ data_chr_jms_hhl_jms_mdl,
            /* .animation = */ data_demo_ap_boss_hhl_jms_anm,
            /* .shadow = */ data_chr_jms_hhh_jms_kg1,
            /* .cluster = */ data_demo_ap_boss_hhl_jms_cls,
        },
        {
            /* .kind = */ EN_RED_CHARA_KIND,
            /* .model = */ data_chr_red_red_mdl,
            /* .animation = */ data_chr_red_red_anm,
            /* .shadow = */ data_chr_red_red_kg1,
            /* .cluster = */ NULL,
        },
        {
            /* .kind = */ EN_SCU_CHARA_KIND,
            /* .model = */ data_chr_scu_scu_mdl,
            /* .animation = */ data_chr_scu_scu_anm,
            /* .shadow = */ data_chr_scu_scu_kg1,
            /* .cluster = */ NULL,
        },
        {
            /* .kind = */ 0,
            /* .model = */ NULL,
            /* .animation = */ NULL,
            /* .shadow = */ NULL,
            /* .cluster = */ NULL,
        }
    }; // @ 0x01F032A0
    static sceVu0FMATRIX stg_apart_stair_vec_01F032F0 = {
        { 99846.148f, -2202.7399f, -100531.95f, 0.0f },
        { 0.0f, -1.3744399f, 0.0f, 0.0f },
        { 100242.95f, -1731.02f, -100380.95f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    }; // @ 0x01F032F0
    static u_long128* stg_apart_stair_red_play_anim_adr; // @ 0x01F03408
    static u_long128* stg_apart_stair_scu_play_anim_adr; // @ 0x01F03400
    int ret; // r16

    #line 187
    switch (ev_p_step) {
        case 0:
            FcRead(data_demo_ap_boss_ap_boss_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_stair_chara_data_01F032A0, 0);
            stg_apart_stair_red_play_anim_adr = (u_long128*) &MemShare_gp_data_buf[(FcGetFileSize(data_demo_ap_boss_ap_boss_dds) + 0x7FF) & ~0x7FF]; // @todo: add align macro
            
            stg_apart_stair_scu_play_anim_adr = stg_apart_stair_red_play_anim_adr + ((FcGetFileSize(data_demo_ap_boss_red_anm) + 0x7FF) & ~0x7FF);
            
            FcRead(data_demo_ap_boss_red_anm, stg_apart_stair_red_play_anim_adr);
            FcRead(data_demo_ap_boss_scu_anm, stg_apart_stair_scu_play_anim_adr);
            fsSync(0, -1);
            stg_apart_stair_red_play_anim_adr = CharaDataAnimSetExtra(EN_RED_CHARA_KIND, data_demo_ap_boss_red_anm, stg_apart_stair_red_play_anim_adr, 0);
            
            stg_apart_stair_scu_play_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_demo_ap_boss_scu_anm, stg_apart_stair_scu_play_anim_adr, 0);
            
            SCNowDemoEventSwitch(sh2jms.player, true);
            CharaAdminPlayableDisplay(0);
            EV_PROG_STEP(22);
            break;
        
        case 22:
            ret = DramaDemoMain(&stg_apart_stair_boss);
            shCharacterSetWeaponRED(shCharacterGetSubCharacter(EN_RED_CHARA_KIND, 0), 1);
        
            if (ret) EV_PROG_STEP(13);
            break;
        
        case 13:
            CharaDataDeleteOne(HHL_JMS_CHARA_KIND);
            SCNowDemoEventSwitch(sh2jms.player, 0);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            CharaDataAnimSetExtra(EN_RED_CHARA_KIND, data_chr_red_red_anm, stg_apart_stair_red_play_anim_adr, 1);
        
            CharaAdminReCreate(EN_RED_CHARA_KIND, 8, 0, stg_apart_stair_vec_01F032F0[0], stg_apart_stair_vec_01F032F0[1], 6);
            
            CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_chr_scu_scu_anm, stg_apart_stair_scu_play_anim_adr, 1);
            
            CharaAdminReCreate(EN_SCU_CHARA_KIND, 9, 0, stg_apart_stair_vec_01F032F0[2], stg_apart_stair_vec_01F032F0[3], 13);
            
            
            sh2sys_set_2(11);
            ScreenEffectFadeStart(1, 1.0f);
            
            return true;
    }
    return false;
}

#line 240
static int stg_apart_stair_EvProgApartBossSiren(void) {
    SeCallPos(SH2_SOUND_10006, 0.0f, NULL, 8);
    return true;
}

#line 249
static int stg_apart_stair_EvProgApartBossEnd(void) {
    static sceVu0FVECTOR light = { 0.3f, 0.90549999f, 0.3f, 0.0f }; // @ 0x01F03330
    static sceVu0FVECTOR clr = { 2.2f, 2.2f, 2.4f, 0.0f }; // @ 0x01F03340
    static Event_CamSetData cam_data = {
        /* .pos = */ {99438.0f, -3961.0f, -100124.0f, 0.0f},
        /* .itr = */ {99438.375f, -3960.1298f, -100123.687f, 0.0f},
        /* .rot = */ {0.0f, 0.0f, 0.0f, 0.0f},
        /* .roll = */ TO_RAD(11.2500257f),
    }; // @ 0x01F03350

    #line 258
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            CharaAdminPlayableDisplay(0);
            shCharacter_Manage_Delete(NULL, EN_RED_CHARA_KIND, 8);
            SeCallPos(SH2_SOUND_19023, 1.0f, (sceVu0FVECTOR) {98804.95312f, -450.0f, -98578.19531, 0.0f}, 4);

            
            SeCallPos(SH2_SOUND_16021, 0.0f, (sceVu0FVECTOR) {98804.95312f, -450.0f, -98578.19531, 0.0f}, 12);
            
            
            ev_timer = 0.0f;
            SET_GAME_FLAG(GAME_FLAG_147);
            EV_PROG_STEP(22);
            /* fallthrough */
        
        case 22:
            DramaDemoFade();
        
            vcSetEventCamParamRefView(cam_data.pos, NULL, cam_data.itr, NULL, cam_data.roll, 1);
            
            vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
            sh2gfw_Set_PallarelLight(light, clr, 2);
            ev_timer += shGetDT();
            if (ev_timer > 4.0f) EV_PROG_STEP(13);
            break;

        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_148);
            Se2dManageDataTimer(SH2_SOUND_10006, 1);
            return true;
    }
    return false;
}

#line 300
static void stg_apart_stair_EvRoomInit(void) {
    UNSET_GAME_FLAG(GAME_FLAG_87);
}

#line 306
static void stg_apart_stair_EvAllTimeFunc(void) {
    float vol; // r29+0x20
    float time; // r29+0x20
    int disp_ctrl_list[3]; // r29+0x10
    int work; // r2

    disp_ctrl_list[0] = 0;
    
    switch (RoomNameJms()) {  
        case 16:
            work = !GET_GAME_FLAG(GAME_FLAG_25) ? 0 : -1;
            
            EvDispControlModelEntry(disp_ctrl_list, 25, work);
            break;
        case 32:
            work = !GET_GAME_FLAG(GAME_FLAG_26) ? 0 : -1;
            
            EvDispControlModelEntry(disp_ctrl_list, 110, work);
            break;
        case 33:
            if (!GET_GAME_FLAG(GAME_FLAG_148))
                clAddDynamicWall(stg_apart_stair_clActWallList_ap88);
            if (!GET_GAME_FLAG(GAME_FLAG_149) && 
                 GET_GAME_FLAG(GAME_FLAG_148)) {
                SET_GAME_FLAG(GAME_FLAG_149);
                SeStop(SH2_SOUND_10006);
            }
            time = Se2dManageDataTimer(SH2_SOUND_10006, 0);
            if (time >= 0.0f) {
                if GET_GAME_FLAG(GAME_FLAG_148) vol = 1.0f - time / 3.4f; // @info this if & else are missing from the line numbers
                else vol = time / 2.2f;
            
                Se2dManageDataVolumeChange(SH2_SOUND_10006, vol);
            }
            time = Se2dManageDataTimer(SH2_SOUND_16021, 0);
            if (time >= 0.0f) {
                if (time < 4.5f) vol = 2.0f * time;
                else vol = 1.0f - ((time - 4.5f) / 1.5f);
                Se2dManageDataVolumeChange(SH2_SOUND_16021, vol);
            }
            break;
    }
    EvDispControlModelExec(disp_ctrl_list);
}
