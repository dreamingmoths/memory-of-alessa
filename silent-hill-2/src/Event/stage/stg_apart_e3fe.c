#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/playing_info.h"

#include "vec.h"

#include "sce/libgraph.h"

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
#include "Event/event_macros.h"

#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_macros.h"

#include "Effect/screen_effect.h"
#include "sound/sh_sound.h"
#include "Multi_thr/filesys/fcread.h"
#include "view/vc_main.h"

#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_scu.h"
#include "data/daily.thu/data_chr_red.h"
#include "data/daily.thu/data_demo_sankaku1.h"
#include "data/daily.thu/data_chr_mkn.h"
#include "data/daily.thu/data_chr_item.h"

#include "Chacter/anime.h"

static int stg_apart_e3fe_EvProgFirstMeetTrihead(void);
static int stg_apart_e3fe_EvProgGetYardKey(void);
static int stg_apart_e3fe_EvProgGetEmergencyKey(void);
static void stg_apart_e3fe_EvStageInit(void);
static int stg_apart_e3fe_EvCharaDataClear(int room);
static void stg_apart_e3fe_EvAllTimeFunc(void);
static void stg_apart_e3fe_ap18_ap21_Closet(void);
static void stg_apart_e3fe_ap18_ap21_HighLight(void);


AnimeInfo stg_apart_e3fe_pjames_stage_anim[21] = {
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
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 0,
        /* .pad = */ 0,
    }
};

u_int stg_apart_e3fe_ev_pos[62] = {
  0x476D8F02, 0x510D8000, 0x5FD0469A, 0xC6AF1BFA, 0x3B2C8000, 0x5FF9C7C6, 0xC6A8BF00, 0x8F408000, 0x6977C7C5, 
  0x573868B0, 0x8000C6A5, 0xC7C67406, 0x5E205204, 0x475F4DF1, 0xD7E18000, 0x487A4636, 0x80004766, 0x4628841F,
  0x93365FD0, 0x80004690, 0x4773D800, 0x45755FF8, 0x80004693, 0x476358C0, 0x6AA468B0, 0x477F487F, 0x841F8000, 
  0x5FD04628, 0x478B1000, 0xC0008000, 0x66404628, 0x600064B0, 0x8000476A, 0x46480000, 0x66406240, 0x476D8F02, 
  0x51038000, 0x5FD046CC, 0x476D8F01, 0x511C8000, 0x5FCF46FE, 0x476CDF31, 0xF87A8000, 0x5F5D4707, 0xC76C36CD, 
  0xFD81EA3F, 0x6013C6AB, 0x479A32FE, 0xE8008000, 0x5FD04628, 0xC7995E80, 0x9A02EB08, 0x604CC762, 0xC69AF603, 
  0x933D8000, 0x5E8FC7C5, 0xC69ACE08, 0xDA008000, 0x5E8FC7C0, 0xC6ADB5FB, 0x8E808000, 0x5F59C7C7 
};

Event_List stg_apart_e3fe_ev_list[22] = {
    {
        /* .flag = */ 5963776,
        /* .cond = */ 536887296,
        /* .rslt0 = */ 1342976000,
        /* .rslt1 = */ 4212094,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 536887296,
        /* .rslt0 = */ 1074540544,
        /* .rslt1 = */ 4194304,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 537669632,
        /* .rslt0 = */ 1073758208,
        /* .rslt1 = */ 4194304,
    },
    {
        /* .flag = */ 92864512,
        /* .cond = */ 1075359748,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1417,
    },
    {
        /* .flag = */ 92930048,
        /* .cond = */ 1075359748,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1418,
    },
    {
        /* .flag = */ 5832704,
        /* .cond = */ 539381764,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 32857,
    },
    {
        /* .flag = */ 6029312,
        /* .cond = */ 540278788,
        /* .rslt0 = */ 805306368,
        /* .rslt1 = */ 49244,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 540938240,
        /* .rslt0 = */ 1078599680,
        /* .rslt1 = */ 4195706,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 541728768,
        /* .rslt0 = */ 1077809152,
        /* .rslt1 = */ 4195706,
    },
    {
        /* .flag = */ 92733440,
        /* .cond = */ 1079422980,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1415,
    },
    {
        /* .flag = */ 92798976,
        /* .cond = */ 1079422980,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1416,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 543428608,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 8373627,
    },
    {
        /* .flag = */ 92012544,
        /* .cond = */ 1081126916,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1404,
    },
    {
        /* .flag = */ 92078080,
        /* .cond = */ 1082044420,
        /* .rslt0 = */ 268435456,
        /* .rslt1 = */ 1405,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 546062336,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 8373631,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 546848768,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 8373632,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 547627008,
        /* .rslt0 = */ 1085280640,
        /* .rslt1 = */ 16778625,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 549195776,
        /* .rslt0 = */ 1086857600,
        /* .rslt1 = */ 16778627,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 550768640,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 8372224,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 551559168,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 8372224,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 552341504,
        /* .rslt0 = */ -1879048192,
        /* .rslt1 = */ 8372224,
    },
    {
        /* .flag = */ 0,
        /* .cond = */ 0,
        /* .rslt0 = */ 0,
        /* .rslt1 = */ 0,
    }
};

Item_List stg_apart_e3fe_gi_list[5] = {
    {
        /* .posX = */ 22615.16f,
        /* .posZ = */ 59042.898f,
        /* .posY = */ 55968,
        /* .rotY = */ 15073,
        /* .st = */ 536871689,
    },
    {
        /* .posX = */ 22507.57f,
        /* .posZ = */ 59033.32f,
        /* .posY = */ 55968,
        /* .rotY = */ 15494,
        /* .st = */ 536871691,
    },
    {
        /* .posX = */ 21007.689f,
        /* .posZ = */ 59263.01f,
        /* .posY = */ 57026,
        /* .rotY = */ 48189,
        /* .st = */ 2684355341,
    },
    {
        /* .posX = */ 21891.169f,
        /* .posZ = */ 62063.789f,
        /* .posY = */ 56751,
        /* .rotY = */ 32768,
        /* .st = */ 2147484431,
    },
    {
        /* .posX = */ 0.0f,
        /* .posZ = */ 0.0f,
        /* .posY = */ 0,
        /* .rotY = */ 0,
        /* .st = */ 3758096384,
    }
};


int (*stg_apart_e3fe_ev_prog[4])() = { NULL, stg_apart_e3fe_EvProgFirstMeetTrihead, stg_apart_e3fe_EvProgGetYardKey, stg_apart_e3fe_EvProgGetEmergencyKey };

Model_List stg_apart_e3fe_mdl_list[4] = {
    {
        /* .kind = */ ITEM_X_KEYEMERG_CHARA_KIND,
        /* .id = */ 0,
        /* .flagOff = */ 89,
        /* .flagOn = */ 0,
        /* .pos = */ {-21050.0f, -426.00003f, -101465.0f, 0.0f},
        /* .rot = */ {1.570796f, -0.0f, 0.69813197f, 0.0f},
    },
    {
        /* .kind = */ ITEM_X_KEYCOURT_CHARA_KIND,
        /* .id = */ 0,
        /* .flagOff = */ 67,
        /* .flagOn = */ 0,
        /* .pos = */ {56560.535f, -3.4176599f, 11205.2656f, 0.0f},
        /* .rot = */ {-1.5973229f, -0.06904f, 0.18903799f, 0.0f},
    },
    {
        /* .kind = */ ITEM_X_KEYCOURT_CHARA_KIND,
        /* .id = */ 0,
        /* .flagOff = */ 92,
        /* .flagOn = */ 67,
        /* .pos = */ {57170.984f, -3.53376f, 11713.1845f, 0.0f},
        /* .rot = */ {-1.512634f, -0.053164f, 0.41216f, 0.0f},
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

Enemy_List stg_apart_e3fe_en_list[9] = {
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 78,
        /* .posX = */ 60500,
        /* .posZ = */ 30000,
        /* .posY = */ 0,
        /* .rotY = */ 0,
        /* .status = */ 0,
        /* .condition = */ 131,
    },
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 79,
        /* .posX = */ 60200,
        /* .posZ = */ 28000,
        /* .posY = */ 0,
        /* .rotY = */ -12867,
        /* .status = */ 0,
        /* .condition = */ 128,
    },
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 80,
        /* .posX = */ 74000,
        /* .posZ = */ 11200,
        /* .posY = */ 0,
        /* .rotY = */ 6433,
        /* .status = */ 0,
        /* .condition = */ 129,
    },
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 81,
        /* .posX = */ 51500,
        /* .posZ = */ 11300,
        /* .posY = */ 0,
        /* .rotY = */ -6433,
        /* .status = */ 0,
        /* .condition = */ 131,
    },
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 82,
        /* .posX = */ 17700,
        /* .posZ = */ 59400,
        /* .posY = */ 0,
        /* .rotY = */ -9650,
        /* .status = */ 0,
        /* .condition = */ 0,
    },
    {
        /* .kind = */ EN_SCU_CHARA_KIND,
        /* .id = */ 83,
        /* .posX = */ 18000,
        /* .posZ = */ 58900,
        /* .posY = */ 0,
        /* .rotY = */ 12867,
        /* .status = */ 0,
        /* .condition = */ 3,
    },
    {
        /* .kind = */ EN_MKN_CHARA_KIND,
        /* .id = */ 6,
        /* .posX = */ -21548,
        /* .posZ = */ -97828,
        /* .posY = */ -66,
        /* .rotY = */ 12867,
        /* .status = */ 13,
        /* .condition = */ 256,
    },
    {
        /* .kind = */ EN_MKN_CHARA_KIND,
        /* .id = */ 7,
        /* .posX = */ -21832,
        /* .posZ = */ -99490,
        /* .posY = */ -44,
        /* .rotY = */ 12867,
        /* .status = */ 14,
        /* .condition = */ 256,
    },
    {0}
};

GfwFunc stg_apart_e3fe_gfw_func = {
    /* .specDraw = */ stg_apart_e3fe_ap18_ap21_Closet,
    /* .preDraw = */ stg_apart_e3fe_ap18_ap21_HighLight,
    /* .postDraw = */ NULL,
    /* .charaDrawHook = */ NULL,
};

Stage_Data stage_apart_e3fe = {
    /* .evList = */ stg_apart_e3fe_ev_list,
    /* .evPos = */ stg_apart_e3fe_ev_pos,
    /* .evProg = */ stg_apart_e3fe_ev_prog,
    /* .giList = */ stg_apart_e3fe_gi_list,
    /* .mdlList = */ stg_apart_e3fe_mdl_list,
    /* .enList = */ stg_apart_e3fe_en_list,
    /* .stageInit = */ stg_apart_e3fe_EvStageInit,
    /* .roomInit = */ NULL,
    /* .alltimeFunc = */ stg_apart_e3fe_EvAllTimeFunc,
    /* .glbCrd = */ 9,
    /* .pcModel = */ 1,
    /* .stgAnimInfo = */ stg_apart_e3fe_pjames_stage_anim,
    /* .bgmControl = */ NULL,
    /* .gfwFunc = */ &stg_apart_e3fe_gfw_func,
    /* .charaDataClear = */ stg_apart_e3fe_EvCharaDataClear,
    /* .soundCallAfterLoad = */ NULL,
    /* .reserve11 = */ 0,
};

static u_char stg_apart_e3fe_cam_change = 0; // size: 0x1, address: 0x1F03080

//////////////

int stg_apart_e3fe_EvProgFirstMeetTrihead(void) { 
    static u_short stg_apart_e3fe_first_anim[21] = { 1020, 6302, 6102, 6105, 10061, 10064, 10067, 1021, 6303, 6103, 6106, 10062, 10065, 10068, 1022, 6304, 6104, 6107, 10063, 10066, 10069 };

    static DramaDemo_MessageTime stg_apart_e3fe_first_msg[2] = {
        {        
            /* .start = */ 2116,
            /* .end = */ 2155,
        },
        {
            /* .start = */ 0xffff,
            /* .end = */ 0xffff,
        }
    };
   static DramaDemo_PlayInfo stg_apart_e3fe_first = {
        /* .demoNo = */ 14,
        /* .adrDdsTop = */ MemShare_gp_data_buf,
        /* .adrAnim = */ stg_apart_e3fe_first_anim,
        /* .adrMsgTime = */ stg_apart_e3fe_first_msg,
        /* .msgStart = */ 0,
        /* .voiceSdNo = */ 0,
        /* .adrVoice = */ NULL,
        /* .streamNo = */ 60076,
        /* .streamStart = */ 25.0f,
        /* .addPosX = */ 0.0f,
        /* .addPosZ = */ 0.0f,
    }; // @ 0x01F02CE0
    static CharaData_DemoList stg_apart_e3fe_first_data[7] = {
        {
            /* .kind = */ EN_MKN_CHARA_KIND,
            /* .model = */ data_chr_mkn_mkn_mdl,
            /* .animation = */ data_demo_sankaku1_mkn_anm,
            /* .shadow = */ data_chr_mkn_mkn_kg1,
            /* .cluster = */ NULL,
        },
        {
            /* .kind = */ ITEM_B_DOO_CHARA_KIND,
            /* .model = */ data_chr_item_b_doo_mdl,
            /* .animation = */ data_demo_sankaku1_b_doo_anm,
            /* .shadow = */ NULL,
            /* .cluster = */ NULL,
        },
        {
            /* .kind = */ HHH_JMS_CHARA_KIND,
            /* .model = */ data_chr_jms_hhh_jms_mdl,
            /* .animation = */ data_demo_sankaku1_hhh_jms_anm,
            /* .shadow = */ data_chr_jms_hhh_jms_kg1,
            /* .cluster = */ data_demo_sankaku1_hhh_jms_cls,
        },
        {
            /* .kind = */ EN_RED_CHARA_KIND,
            /* .model = */ data_chr_red_red_mdl,
            /* .animation = */ data_demo_sankaku1_red_anm,
            /* .shadow = */ data_chr_red_red_kg1,
            /* .cluster = */ NULL,
        },
        {
            /* .kind = */ ITEM_I_HANDGUN_CHARA_KIND,
            /* .model = */ data_chr_item_i_handgun_mdl,
            /* .animation = */ data_demo_sankaku1_i_handgun_anm,
            /* .shadow = */ NULL,
            /* .cluster = */ NULL,
        },
        {
            /* .kind = */ ITEM_I_MAGAZINE_CHARA_KIND,
            /* .model = */ data_chr_item_i_magazine_mdl,
            /* .animation = */ data_demo_sankaku1_i_magazine_anm,
            /* .shadow = */ NULL,
            /* .cluster = */ NULL,
        }
    }; // @ 0x01F02D10
    static sceVu0FMATRIX vec = {
        { -21548.099f, -66.19f, -97828.0f, 0.0f  },
        { 0.0f, PI, 0.0f, 0.0f                   },
        { -21832.349f, -43.685f, -99490.0f, 0.0f },
        { 0.0f, PI, 0.0f, 0.0f                   },
    }; // @ 0x01F02DA0
    u_long128* adr; // r16

    switch (ev_p_step) {
        case 0:
            FcRead(data_demo_sankaku1_sankaku_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_e3fe_first_data, 0);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, 1);
            CharaWorkCreate(EN_RED_CHARA_KIND, 0, (sceVu0FVECTOR) {0.0f, 0.0f, 0.0f, 1.0f}, (sceVu0FVECTOR) {0.0f, 0.0f, 0.0f, 1.0f}, 0);
            shCharacterSetWeaponRED(shCharacterGetSubCharacter(EN_RED_CHARA_KIND, 0), 0);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain(&stg_apart_e3fe_first)) {
                ScreenEffectFadeStart(2, 0.0f);
                EV_PROG_STEP(4);
            }
            break;
        case 4:
            DramaDemoSkipLast(&stg_apart_e3fe_first);
            if (ScreenEffectFadeCheck()) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            SeCallPos(16006, 1.0f, (sceVu0FVECTOR) {-21300.0f, -550.0f, -101150.0f, 0.0f}, 0);
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(EN_RED_CHARA_KIND);
            CharaDataDeleteOne(ITEM_B_DOO_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_HANDGUN_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_MAGAZINE_CHARA_KIND);
            CharaAdminPlayableDisplay(1);
            SCNowDemoEventSwitch(sh2jms.player, 0);
            shCharacterPlayerModelToPlayable();
            adr = CharaDataLoadExtra(data_chr_mkn_mkn_anm, 1 << SCP_STATUS_BIT_10);
            fsSync(0, -1);
            CharaDataAnimSetExtra(EN_MKN_CHARA_KIND, data_chr_mkn_mkn_anm, adr, 1);
            CharaAdminReCreate(EN_MKN_CHARA_KIND, 6, 0, vec[0], vec[1], (1 << SCP_STATUS_BIT_0) | (1 << SCP_STATUS_BIT_ANIME_TYPE) | (1 << SCP_STATUS_BIT_3));
            CharaAdminReCreate(EN_MKN_CHARA_KIND, 7, 1, vec[2], vec[3], (1 << SCP_STATUS_BIT_1) | (1 << SCP_STATUS_BIT_ANIME_TYPE) | (1 << SCP_STATUS_BIT_3));
            sh2jms.player->pos.x = -21300.0f;
            sh2jms.player->pos.z = -100950.0f;
            sh2jms.player->rot.y = 0.0f;
            vcReturnPreAutoCamWork(1);
            ScreenEffectFadeStart(4, 0.0f);
            SET_GAME_FLAG(GAME_FLAG_91);
            return true;
    }

    return false;
}


static int stg_apart_e3fe_EvProgGetYardKey(void) {
    return EvSubItemGetAndAnim(26, 1);
}

static int stg_apart_e3fe_EvProgGetEmergencyKey(void) {
    return EvSubItemGetAndAnim(27, 2);
}

static void stg_apart_e3fe_EvStageInit(void) {
    stg_apart_e3fe_cam_change = 0;
}

static int stg_apart_e3fe_EvCharaDataClear(int room) {
    if ((room == 19) && !(GET_GAME_FLAG(GAME_FLAG_91))) { // @todo: add room define
        return 1;
    }
    return 0;
}

Event_CamSetData stg_apart_e3fe_cam_data_01F02E10 = {
    /* .pos = */  {-20820.0f, -530.0f, -101460.0f, 0.0f},
    /* .itr = */  {-20820.996f, -529.97546f, -101459.929f, 0.0f},
    /* .rot = */  {0.0f},
    /* .roll = */  0.098177f,
};

void stg_apart_e3fe_EvAllTimeFunc(void) {
    int disp_ctrl_list[3]; // r29+0x10


    disp_ctrl_list[0] = 0;
    switch (RoomNameJms()) {
        default:
            break;
        case 19:
            if (GET_GAME_FLAG(GAME_FLAG_91)) { 
                EvDispControlModelEntry(disp_ctrl_list, 19, 0);
                if (sh2jms.player->pos.x > -21600.0f && sh2jms.player->pos.z < -101150.0f) {
                    if (!GET_GAME_FLAG(GAME_FLAG_89)) {
                        vcSetEventCamParamRefView(stg_apart_e3fe_cam_data_01F02E10.pos, NULL, stg_apart_e3fe_cam_data_01F02E10.itr, NULL, stg_apart_e3fe_cam_data_01F02E10.roll, 1);
                        vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
                        stg_apart_e3fe_cam_change = 1;
                    }
                } else if (stg_apart_e3fe_cam_change) {
                    vcReturnPreAutoCamWork(1);
                    stg_apart_e3fe_cam_change = 0;
                }
            } else {
                sh2shd_add_map_to_shadow_off_work(18);
                sh2shd_off_obj(18, 33);
                EvDispControlModelEntry(disp_ctrl_list, 19, -1);
            }
            break;
        }
        EvDispControlModelExec(disp_ctrl_list);
    }
    
float stg_apart_e3fe_ap18_ap24_ClosetData[32][4] = {
    { -21550.0f, -900.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 128.0f },
    { -21050.0f, -900.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 128.0f },
    { -21550.0f, -828.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 64.0f },
    { -21050.0f, -828.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 64.0f },
    { -21550.0f, -780.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 64.0f },
    { -21050.0f, -780.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 64.0f },
    { -21550.0f, -708.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 128.0f },
    { -21050.0f, -708.0f, -101250.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 128.0f },
};

void stg_apart_e3fe_ap18_ap21_Closet(void) {
    static Q_WORDDATA stg_apart_e3fe_OutputVertex[54]; // size: 0x360, address: 0x1F03430
    static Q_WORDDATA stg_apart_e3fe_ScissorVertex[54]; // size: 0x360, address: 0x1F030D0
    static Q_WORDDATA env[4]; // @ 0x01F03090
    Q_WORDDATA* kickbuf __attribute__((aligned(16))) = stg_apart_e3fe_OutputVertex; // r29+0x20
    Q_WORDDATA* scikickbuf __attribute__((aligned(16))) = stg_apart_e3fe_ScissorVertex; // r29+0x30
    int i, id = 0; // r16 @note id not in dwarf
    
    if (!GET_BIT(Sh2sys.main_status, 6)) {
        Env_ctl.camera_parms[3] = 100.0f;
        return;
    }
    Env_ctl.camera_parms[3] = 100.0f;
    if ((demo_frame < 360.5f) || !(demo_frame < 1698.0f)) {
        return;
    }










    
    
    SET_DMATAG(env, id, DMAcnt | 2, 0, SCE_VIF1_SET_FLUSH(0), SCE_VIF1_SET_DIRECT(2, 0));
    SET_GIFTAG(env, id, SCE_GIF_SET_TAG(1, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(env, id, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 96));
    env[3].ui32[0] = DMAend; env[3].ui32[1] = 0; env[3].ul64[1] = 0;
    for (i = 0; i < 2; i++) {
        MakeScissorPacket(
            stg_apart_e3fe_ap18_ap24_ClosetData[i * (sizeof(stg_apart_e3fe_ap18_ap24_ClosetData) / sizeof(sceVu0FVECTOR) / 2)], 
            (void** ) &kickbuf, (void** ) &scikickbuf, 0, 
            SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, SCE_GS_TRUE /* gourand shading */, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0), 4
        );
    }
    SET_DMA_END(kickbuf);
    SET_DMA_END(scikickbuf);
    d1cSend(env);
    d1cSend(stg_apart_e3fe_OutputVertex);
    d1cSend(stg_apart_e3fe_ScissorVertex);
}


static void stg_apart_e3fe_ap18_ap21_HighLight(void) {
    static sceVu0FVECTOR stg_apart_e3fe_hcol ={ 1.0f, 1.0f, 1.0f, 0.0f };
    static sceVu0FVECTOR stg_apart_e3fe_hdir = { -0.198358997f, 0.319f, 0.92799997f, 0.0f }; 

    if ((DramaDemoNumber() == 14) && (demo_frame >= 360.5f)) {
        sh2gfw_Set_DemoRefrectionHighLight(stg_apart_e3fe_hdir, stg_apart_e3fe_hcol);
    }
}

