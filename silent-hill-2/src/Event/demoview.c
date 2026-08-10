#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/sh_vu0.h"

#include "vec.h"

#include "Chacter/character.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_maria.h"
#include "Chacter/m3_edb.h"
#include "Chacter/m3_dmaria.h"
#include "Chacter/m3_oni.h"
#include "Chacter/m3_pap.h"
#include "Chacter/m3_djames.h"
#include "Chacter/m3_ike.h"
#include "Chacter/m3_scu.h"
#include "Chacter/m3_angela.h"
#include "Chacter/m3_laura.h"
#include "Chacter/m3_play_event.h"
#include "Chacter/m3_eddie.h"
#include "Chacter/m3_boat.h"
#include "Chacter/m3_mary.h"
#include "Chacter/m3_inu.h"
#include "Chacter/m3_mkn.h"
#include "Chacter/m3_bgobj.h"
#include "Chacter/m3_red.h"
#include "Chacter/m3_bos.h"

#include "Event/demoview.h"
#include "Event/event.h"
#include "Event/picture.h"
#include "Event/chara_admin.h"
#include "Event/chara_data_load.h"

#include "view/vb_main.h"
#include "view/vc_main.h"
#include "view/vc_util.h"

#include "sound/sh_sd_call.h"
#include "Font/font.h"
#include "GFW/sh2gfw_2d_filters.h"

#pragma fast_fptosi on

static int DdsPlay(DramaDemo_PlayInfo* info);
static int DramaDemoInit(DramaDemo_PlayInfo* info);
static void RotationToInterest(float* position, float* rotation, float* interest, float* roll);
static short DdsReadShort(void);
static float DdsReadFloat2(void);
static float DdsReadFloat4(void);
static void DramaDemoAnimationStart(short* adr_anim);
static void DdsPlayKey(void);
static void DdsPlayCamera(void);
static void DdsPlayLight(int no);
static void DdsPlayCharacter(int no);

/* ================ data ================ */

static DramaDemo_AnimInfo anim_info[79] = {
    {
        /* .name = */                  "hhh_jms_pos",
        /* .kind = */                  HHH_JMS_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 1000,
        /* .end = */                   1165
    },
    {
        /* .name = */                  "hhl_jms_pos",
        /* .kind = */                  HHL_JMS_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 1166,
        /* .end = */                   1187
    },
    {
        /* .name = */                  "hll_jms_pos",
        /* .kind = */                  HLL_JMS_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 952,
        /* .end = */                   972
    },
    {
        /* .name = */                  "lll_jms_pos",
        /* .kind = */                  LLL_JMS_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 973,
        /* .end = */                   979
    },
    {
        /* .name = */                  "hhh_mar_pos",
        /* .kind = */                  HHH_MAR_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 3000,
        /* .end = */                   3029
    },
    {
        /* .name = */                  "lll_mar_pos",
        /* .kind = */                  LLL_MAR_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 42,
        /* .end = */                   46
    },
    {
        /* .name = */                  "lau_pos",
        /* .kind = */                  LAU_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 2500,
        /* .end = */                   2540
    },
    {
        /* .name = */                  "hhh_edi_pos",
        /* .kind = */                  HHH_EDI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 4503,
        /* .end = */                   4527
    },
    {
        /* .name = */                  "lll_edi_pos",
        /* .kind = */                  EN_LLL_EDI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6801,
        /* .end = */                   6801
    },
    {
        /* .name = */                  "agl_pos",
        /* .kind = */                  AGL_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 3500,
        /* .end = */                   3531
    },
    {
        /* .name = */                  "mry_pos",
        /* .kind = */                  MRY_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 4002,
        /* .end = */                   4020
    },
    {
        /* .name = */                  "mxx_pos",
        /* .kind = */                  HHH_MXX_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 4102,
        /* .end = */                   4110
    },
    {
        /* .name = */                  "inu_pos",
        /* .kind = */                  INU_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 4901,
        /* .end = */                   4902
    },
    {
        /* .name = */                  "boat_pos",
        /* .kind = */                  BOAT_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 56,
        /* .end = */                   58
    },
    {
        /* .name = */                  "scu_pos",
        /* .kind = */                  EN_SCU_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6003,
        /* .end = */                   6009
    },
    {
        /* .name = */                  "pap_pos",
        /* .kind = */                  EN_PAP_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6602,
        /* .end = */                   6607
    },
    {
        /* .name = */                  "red_pos",
        /* .kind = */                  EN_RED_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6300,
        /* .end = */                   6349
    },
    {
        /* .name = */                  "mkn_1_pos",
        /* .kind = */                  EN_MKN_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6102,
        /* .end = */                   6104
    },
    {
        /* .name = */                  "mkn_2_pos",
        /* .kind = */                  EN_MKN_CHARA_KIND,
        /* .id = */                    1,
        /* .start = */                 6105,
        /* .end = */                   6107
    },
    {
        /* .name = */                  "ike_1_pos",
        /* .kind = */                  EN_IKE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6502,
        /* .end = */                   6506
    },
    {
        /* .name = */                  "ike_2_pos",
        /* .kind = */                  EN_IKE_CHARA_KIND,
        /* .id = */                    1,
        /* .start = */                 6507,
        /* .end = */                   6511
    },
    {
        /* .name = */                  "oni_pos",
        /* .kind = */                  EN_ONI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6352,
        /* .end = */                   6353
    },
    {
        /* .name = */                  "oni_1_pos",
        /* .kind = */                  EN_ONI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6354,
        /* .end = */                   6356
    },
    {
        /* .name = */                  "oni_2_pos",
        /* .kind = */                  EN_ONI_CHARA_KIND,
        /* .id = */                    1,
        /* .start = */                 6357,
        /* .end = */                   6359
    },
    {
        /* .name = */                  "bos_pos",
        /* .kind = */                  EN_BOS_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 6701,
        /* .end = */                   6720
    },
    {
        /* .name = */                  "dmr_pos",
        /* .kind = */                  ITEM_DMR_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10163,
        /* .end = */                   10164
    },
    {
        /* .name = */                  "dm2_pos",
        /* .kind = */                  ITEM_DM2_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10165,
        /* .end = */                   10166
    },
    {
        /* .name = */                  "i_keycou_pos",
        /* .kind = */                  ITEM_I_KEYCOU_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10001,
        /* .end = */                   10001
    },
    {
        /* .name = */                  "i_radio_pos",
        /* .kind = */                  ITEM_I_RADIO_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10002,
        /* .end = */                   10018
    },
    {
        /* .name = */                  "i_kakuzai_pos",
        /* .kind = */                  ITEM_I_KAKUZAI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10019,
        /* .end = */                   10024
    },
    {
        /* .name = */                  "i_flight_pos",
        /* .kind = */                  ITEM_I_FLIGHT_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10035,
        /* .end = */                   10040
    },
    {
        /* .name = */                  "i_bear_pos",
        /* .kind = */                  ITEM_I_BEAR_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10025,
        /* .end = */                   10030
    },
    {
        /* .name = */                  "i_bear2_pos",
        /* .kind = */                  ITEM_I_BEAR2_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10031,
        /* .end = */                   10034
    },
    {
        /* .name = */                  "i_letter_pos",
        /* .kind = */                  ITEM_I_LETTER_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10041,
        /* .end = */                   10048
    },
    {
        /* .name = */                  "i_handgun_pos",
        /* .kind = */                  ITEM_I_HANDGUN_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10064,
        /* .end = */                   10066
    },
    {
        /* .name = */                  "i_magazine_pos",
        /* .kind = */                  ITEM_I_MAGAZINE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10067,
        /* .end = */                   10069
    },
    {
        /* .name = */                  "i_lring_pos",
        /* .kind = */                  ITEM_I_LRING_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10075,
        /* .end = */                   10076
    },
    {
        /* .name = */                  "i_purse_pos",
        /* .kind = */                  ITEM_I_PURSE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10096,
        /* .end = */                   10096
    },
    {
        /* .name = */                  "i_j_light_pos",
        /* .kind = */                  ITEM_I_J_LIGHT_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10100,
        /* .end = */                   10112
    },
    {
        /* .name = */                  "i_keyspe_pos",
        /* .kind = */                  ITEM_I_KEYSPE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10097,
        /* .end = */                   10099
    },
    {
        /* .name = */                  "i_mtablet_1_pos",
        /* .kind = */                  ITEM_I_MTABLET_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10122,
        /* .end = */                   10123
    },
    {
        /* .name = */                  "i_mtablet_2_pos",
        /* .kind = */                  ITEM_I_MTABLET_CHARA_KIND,
        /* .id = */                    1,
        /* .start = */                 10124,
        /* .end = */                   10125
    },
    {
        /* .name = */                  "i_mdrug_pos",
        /* .kind = */                  ITEM_I_MDRUG_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10120,
        /* .end = */                   10121
    },
    {
        /* .name = */                  "i_needle_pos",
        /* .kind = */                  ITEM_I_NEEDLE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10126,
        /* .end = */                   10126
    },
    {
        /* .name = */                  "i_keyelevator_p",
        /* .kind = */                  ITEM_I_KEYELEVATOR_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10127,
        /* .end = */                   10127
    },
    {
        /* .name = */                  "i_key_clock_pos",
        /* .kind = */                  ITEM_I_KEY_CLOCK_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10129,
        /* .end = */                   10131
    },
    {
        /* .name = */                  "i_photo_pos",
        /* .kind = */                  ITEM_I_PHOTO_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10150,
        /* .end = */                   10159
    },
    {
        /* .name = */                  "i_knife_pos",
        /* .kind = */                  ITEM_I_KNIFE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10140,
        /* .end = */                   10149
    },
    {
        /* .name = */                  "i_juice_pos",
        /* .kind = */                  ITEM_I_JUICE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10188,
        /* .end = */                   10188
    },
    {
        /* .name = */                  "i_video_pos",
        /* .kind = */                  ITEM_I_VIDEO_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10220,
        /* .end = */                   10220
    },
    {
        /* .name = */                  "i_colt_pos",
        /* .kind = */                  ITEM_I_COLT_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10175,
        /* .end = */                   10187
    },
    {
        /* .name = */                  "i_hari_pos",
        /* .kind = */                  ITEM_I_HARI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10213,
        /* .end = */                   10214
    },
    {
        /* .name = */                  "i_letterm_pos",
        /* .kind = */                  ITEM_I_LETTERM_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10228,
        /* .end = */                   10240
    },
    {
        /* .name = */                  "i_headphone_pos",
        /* .kind = */                  ITEM_I_HEADPHONE_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10246,
        /* .end = */                   10246
    },
    {
        /* .name = */                  "b_tel_pos",
        /* .kind = */                  ITEM_B_TEL_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10049,
        /* .end = */                   10054
    },
    {
        /* .name = */                  "b_d00_pos",
        /* .kind = */                  ITEM_B_D00_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10055,
        /* .end = */                   10060
    },
    {
        /* .name = */                  "b_d01_pos",
        /* .kind = */                  ITEM_B_D01_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10113,
        /* .end = */                   10119
    },
    {
        /* .name = */                  "b_d02_pos",
        /* .kind = */                  ITEM_B_D02_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10085,
        /* .end = */                   10094
    },
    {
        /* .name = */                  "b_d03_pos",
        /* .kind = */                  ITEM_B_D03_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10077,
        /* .end = */                   10078
    },
    {
        /* .name = */                  "b_d05_pos",
        /* .kind = */                  ITEM_B_D05_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10132,
        /* .end = */                   10134
    },
    {
        /* .name = */                  "b_rei_pos",
        /* .kind = */                  ITEM_B_REI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10070,
        /* .end = */                   10072
    },
    {
        /* .name = */                  "b_doo_pos",
        /* .kind = */                  ITEM_B_DOO_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10061,
        /* .end = */                   10063
    },
    {
        /* .name = */                  "b_pia_pos",
        /* .kind = */                  ITEM_B_PIA_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10079,
        /* .end = */                   10084
    },
    {
        /* .name = */                  "b_ami_pos",
        /* .kind = */                  ITEM_B_AMI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10095,
        /* .end = */                   10095
    },
    {
        /* .name = */                  "b_rop_pos",
        /* .kind = */                  ITEM_B_ROP_CHARA_KIND,
        /* .id = */                    6,
        /* .start = */                 10128,
        /* .end = */                   10128
    },
    {
        /* .name = */                  "b_clo_pos",
        /* .kind = */                  ITEM_B_CLO_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10136,
        /* .end = */                   10139
    },
    {
        /* .name = */                  "b_tan_pos",
        /* .kind = */                  ITEM_B_TAN_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10215,
        /* .end = */                   10216
    },
    {
        /* .name = */                  "b_dor_pos",
        /* .kind = */                  ITEM_B_DOR_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10217,
        /* .end = */                   10219
    },
    {
        /* .name = */                  "b_d08_pos",
        /* .kind = */                  ITEM_B_D08_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10189,
        /* .end = */                   10196
    },
    {
        /* .name = */                  "b_piz_pos",
        /* .kind = */                  ITEM_B_PIZ_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10197,
        /* .end = */                   10204
    },
    {
        /* .name = */                  "b_bol_pos",
        /* .kind = */                  ITEM_B_BOL_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10205,
        /* .end = */                   10212
    },
    {
        /* .name = */                  "b_ori_pos",
        /* .kind = */                  ITEM_ORI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10221,
        /* .end = */                   10221
    },
    {
        /* .name = */                  "b_d06_pos",
        /* .kind = */                  ITEM_B_D06_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10167,
        /* .end = */                   10170
    },
    {
        /* .name = */                  "b_sti_pos",
        /* .kind = */                  ITEM_B_STI_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10171,
        /* .end = */                   10174
    },
    {
        /* .name = */                  "b_d10_pos",
        /* .kind = */                  ITEM_B_D10_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10222,
        /* .end = */                   10227
    },
    {
        /* .name = */                  "b_hul_pos",
        /* .kind = */                  ITEM_B_HUL_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10242,
        /* .end = */                   10243
    },
    {
        /* .name = */                  "b_cha_pos",
        /* .kind = */                  ITEM_B_CHA_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10244,
        /* .end = */                   10245
    },
    {
        /* .name = */                  "mx2_pos",
        /* .kind = */                  ITEM_MX2_EARLY_DEMO_CHARA_KIND, /* @note: this model notably changed character kinds. in retail, she has 0x439 */
        /* .id = */                    0,
        /* .start = */                 10241,
        /* .end = */                   10241
    },
    {
        /* .name = */                  "b_do4_pos",
        /* .kind = */                  ITEM_B_DO4_CHARA_KIND,
        /* .id = */                    0,
        /* .start = */                 10160,
        /* .end = */                   10162
    }
};


/* ================ bss ================ */

int demo_status;        // size: 0x4, address: 0x1133C28
float demo_frame;       // size: 0x4, address: 0x1133C20
float total_demo_frame; // size: 0x4, address: 0x1133C18
int demo_number;        // size: 0x4, address: 0x1133C10
int demo_counter;       // size: 0x4, address: 0x1133C08

int sbt_msg_no; // size: 0x4, address: 0x1133C00

DdsFrame last;            // size: 0x360, address: 0x11338A0
DdsFrame next;            // size: 0x360, address: 0x1133540
DdsFrame base;            // size: 0x360, address: 0x11331E0
SubCharacter* chara_p[7]; // size: 0x1C, address: 0x11331C0

void* adr_dds;        // size: 0x4, address: 0x11331B0
short total_light;    // size: 0x2, address: 0x11331A8
short point_light;    // size: 0x2, address: 0x11331A0
short spot_light;     // size: 0x2, address: 0x1133198
short infinite_light; // size: 0x2, address: 0x1133190
int character_number; // size: 0x4, address: 0x1133188

u_short demo_anim_no;  // size: 0x2, address: 0x1133180
u_short demo_msg_no;   // size: 0x2, address: 0x1133178
u_short demo_voice_no; // size: 0x2, address: 0x1133170

float msg_frame; // size: 0x4, address: 0x1133168

DramaDemo_MessageTime* sbt_msg_time; // size: 0x4, address: 0x1133160
int sbt_str_no;                      // size: 0x4, address: 0x1133158
static float sbt_timer = 0.0f;       // size: 0x4, address: 0x1133148


/* ================ inlines & macros ================ */

#define DdsReadByte() (*(((s_char*) adr_dds)++))
static inline void DdsSkipBytes(int size) {
    (s_char*) adr_dds += size;
}
static inline void DdsReadString(s_char* buf) {
    strncpy(buf, (s_char*) adr_dds, 16);
    DdsSkipBytes(16);
}

static short DdsReadShort(void) {
    u_char c_work[2];
    
    c_work[0] = DdsReadByte();
    c_work[1] = DdsReadByte();
    
    return *(short*) c_work;
}

static inline float fast_fptosi(float x) {
    asm volatile("cvt.w.s %0, %0; cvt.s.w %0, %0": "+f"(x));
    return x;
}

// @note: very similar to GetSF in anime.c.
static float DdsReadFloat2(void) {
	int work;
	int coe;
	int exp;
	int sig;

    work = 0;
    ((s_char*)&work)[0] = DdsReadByte();
    ((s_char*)&work)[1] = DdsReadByte();

    sig = (work >> 15) & 0b1;
    exp = (work >> 10) & 0b11111;
    coe = work & 0b1111111111;
    exp += 0x70;
    coe <<= 13;
    exp <<= 23;
    
    work = (sig << 31) | exp | coe;
    
    return *(float*)&work;
}

static float DdsReadFloat4(void) {
    char c_work[4]; // r29+0xC

    c_work[0] = DdsReadByte();
    c_work[1] = DdsReadByte();
    c_work[2] = DdsReadByte();
    c_work[3] = DdsReadByte();
    
    return *(float *)c_work;
}

/* ================ code ================ */

#line 230
int DramaDemoMain(DramaDemo_PlayInfo* info) {
    static float stop_counter; // @ 0x01133150
    int ret; // r16

    /* large gap in line numbers */

    #line 263
    if (ev_s_step == 0) {
        DramaDemoInit(info);
    
        
        
        ev_s_step = 1;
    }
    SET_BIT(Sh2sys.main_status, 6);
    demo_number = info->demo_no;
    
    if (info->stream_no != 0) {
        if (!DdsGetFlag(DDS_FLAG_7)) {
            if (!(shSdStat() & 0xF0)) shSdCall(info->stream_no, 0, 0, 0);
            shResetDF();
            DdsSetFlag(DDS_FLAG_7);
        } else if (!DdsGetFlag(DDS_FLAG_8) && demo_frame >= info->stream_start) {
            // @todo: add macros
            if ((shSdStat() & 0xF0) == 0x40) {
                stop_counter += shGetDTreal();
                printf("Stream read stop: %5.3f\n", stop_counter);
                shSdCall(SH2_SOUND_1015, 0, 0, 0);
                shResetDF();
                DdsSetFlag(DDS_FLAG_8);
            } else {
                stop_counter += shGetDTreal();
                shSetDFZero();
            }
        }
    }

    
    ret = DdsPlay(info);
    if (!DdsGetFlag(DDS_FLAG_9) && shPadTrigger(0, key_config.skip)) {
        ret = 1;
        fontClear();
        shSdCall(SH2_SOUND_1012, 0, 0, 0);
    }
    return ret;
}

#line 308
static int DramaDemoInit(DramaDemo_PlayInfo* info /* r18 */) {
    sceVu0FVECTOR dummy[2]; // r29+0x40
    s_char buf[32]; // r29+0x60
    u_short s_work; // r2 @note present in dwarf, unused here
    u_char c_work; // r2
    int i; // r16
    int j; // r17
    dummy[0][0] = sh2jms.player->pos.x;
    dummy[0][1] = sh2jms.player->pos.y;
    dummy[0][2] = sh2jms.player->pos.z;
    dummy[0][3] = 1.0f;
    vu0_unit_vector(dummy[1]);
    adr_dds = info->adr_dds_top;

    
    ASSERT(!strncmp( adr_dds , "dds" , 3 ));


    
    DdsSkipBytes(16);
    total_demo_frame = (float) DdsReadShort();
    DdsSkipBytes(2);
    point_light = DdsReadByte();
    spot_light = DdsReadByte();
    infinite_light = DdsReadByte();
    DdsSkipBytes(1);
    character_number = DdsReadByte();
    for (i = 0; i < character_number; i++) {
        DdsReadString(buf);
        for (j = 0; ; j++) {
            if (strcmp(buf, anim_info[j].name) != 0) continue;
            chara_p[i] = shCharacterGetSubCharacter(anim_info[j].kind, anim_info[j].id);
            
            if (chara_p[i] == NULL) {
                chara_p[i] = CharaWorkCreate(anim_info[j].kind, anim_info[j].id, dummy[0], dummy[1], 0);
            }
            
            ASSERT(chara_p[i] != 0);
        
            break;
        }
    }

    
    shQzero(&base, sizeof(DdsFrame));
    shQzero(&next, sizeof(DdsFrame));
    demo_frame = msg_frame = 0.0f;
    demo_counter = 0;
    
    total_light = point_light + spot_light + infinite_light;
    ASSERT(total_light <= 6);
    
    demo_status = 0;
    demo_anim_no = 0;
    demo_msg_no = 0;
    demo_voice_no = 0;
    
    DdsReadShort();
    while (1) { 
        c_work = DdsReadByte();
        if (c_work == 0xFF) break;
        if (c_work == 0) DdsPlayKey();
        else if (c_work == 1) DdsPlayCamera();
        else if (c_work - 2 < total_light)
            DdsPlayLight(c_work - 2);
        else DdsPlayCharacter(c_work - total_light - 2);
    }
    if (DdsGetFlag(DDS_FLAG_START)) {
        DramaDemoAnimationStart(info->adr_anim);
        DdsUnsetFlag(DDS_FLAG_START);
    }
    memcpy(&last, &next, sizeof(DdsFrame));
    
    
    
    
    
    
    
    return 1;
}

static void DramaDemoAnimationStart(short* adr_anim /* r17 */) {
    short anim; // r4
    int i, j, k; // r16, r6, r8

    if (adr_anim == NULL) return;

    for (i = 0; i < character_number; i++) {
        anim = adr_anim[demo_anim_no];
        for (j = 0; true; j++) {
            if (anim_info[j].start <= anim && anim_info[j].end >= anim) 
                break;
        }
        for (k = 0; true; k++) {
            if (chara_p[k]->kind == anim_info[j].kind && chara_p[k]->id == anim_info[j].id)
                break;
        }

        switch (anim_info[j].kind) {
            case HHH_JMS_CHARA_KIND:
            case HHL_JMS_CHARA_KIND:
                shCharacterHumanDJAMESAnimeSet(chara_p[k], anim);
                break;
            case HLL_JMS_CHARA_KIND:
            case LLL_JMS_CHARA_KIND:
                shCharacterHumanPJAMESAnimeSet(chara_p[k], anim);
                break;
            case HHH_MAR_CHARA_KIND:
                shCharacterHumanDMARAnimeSet(chara_p[k], anim);
                break;
            case LLL_MAR_CHARA_KIND:
                shCharacterHumanMARAnimeSet(chara_p[k], anim);
                break;
            case LAU_CHARA_KIND:
                shCharacterHumanLAUAnimeSet(chara_p[k], anim);
                break;
            case AGL_CHARA_KIND:
                shCharacterHumanAGLAnimeSet(chara_p[k], anim);
                break;
            case HHH_EDI_CHARA_KIND:
                shCharacterHumanEDIAnimeSet(chara_p[k], anim);
                break;
            case MRY_CHARA_KIND:
                shCharacterHumanMRYAnimeSet(chara_p[k], anim);
                break;
            case INU_CHARA_KIND:
                shCharacterHumanINUAnimeSet(chara_p[k], anim);
                break;
            case BOAT_CHARA_KIND:
                shCharacterHumanBOTAnimeSet(chara_p[k], anim);
                break;
            case EN_SCU_CHARA_KIND:
                shCharacterEnemySCUAnimeSet(chara_p[k], anim);
                break;
            case EN_PAP_CHARA_KIND:
                shCharacterEnemyPAPAnimeSet(chara_p[k], anim);
                break;
            case EN_RED_CHARA_KIND:
                shCharacterEnemyREDAnimeSet(chara_p[k], anim);
                break;
            case EN_MKN_CHARA_KIND:
                shCharacterEnemyMKNAnimeSet(chara_p[k], anim);
                break;
            case EN_IKE_CHARA_KIND:
                shCharacterEnemyIKEAnimeSet(chara_p[k], anim);
                break;
            case EN_ONI_CHARA_KIND:
                shCharacterEnemyONIAnimeSet(chara_p[k], anim);
                break;
            case EN_LLL_EDI_CHARA_KIND:
                shCharacterEnemyEDBAnimeSet(chara_p[k], anim);
                break;
            case EN_BOS_CHARA_KIND:
                shCharacterEnemyBOSAnimeSet(chara_p[k], anim);
                break;
            default:
                shCharacterObjectAnimeSet(chara_p[k], anim);
                break;
        }

        demo_anim_no++;
    }
}

#ifdef NON_MATCHING
static int DdsPlay(DramaDemo_PlayInfo * info /* r16 */) {
    sceVu0FVECTOR position; // r29+0x50
    sceVu0FVECTOR interest; // r29+0x60
    sceVu0FVECTOR color; // r29+0x70
    sceVu0FVECTOR normal; // r29+0x80
    float falloff_s; // r29+0x90
    float falloff_e; // r29+0x90
    float cone; // r29+0x90
    float roll; // r29+0x90
    float plane; // r21
    float frm_dcm; // r20
    float next_data_frame; // r2
    u_short s_work; // r4
    u_char c_work; // @note not in dwarf
    u_char node_no; // r2
    int i; // r17
    int j; // r18
    int k; // r4
    DramaDemo_MessageTime* temp_v1_3;
    f32 var_f2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v1_2;
    u8 temp_v1;
    void* temp_a2;
    void* temp_v1_4; void* temp_v1_5; void* temp_v1_6; float tmp;
    DramaDemoFade();
    
    if(fptosi(last.frame) < fptosi(demo_frame)) {
        if (DdsGetFlag(DDS_FLAG_START)) {
            DramaDemoAnimationStart(info->adr_anim);
            DdsUnsetFlag(DDS_FLAG_START);
        }
    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        DdsUnsetFlag(DDS_FLAG_0);
        while (true) {
            DdsUnsetFlag(DDS_FLAG_FLOAT32);
        
            s_work = DdsReadShort();
            DdsSkipBytes(-2);
            next_data_frame = s_work;
            
            if (s_work == 0xFFFF) break;
            if ((next_data_frame > (1.0f + demo_frame))) break;
            
            memcpy(&last, &next, sizeof(DdsFrame));
            DdsSkipBytes(2);
            while (1) {
                c_work = DdsReadByte();
                if (c_work == 0xFF) break;
                if (c_work == 0) DdsPlayKey();
                else if (c_work == 1) DdsPlayCamera();
                else if (c_work - 2 < total_light)
                    DdsPlayLight(c_work - 2);
                else DdsPlayCharacter(c_work - total_light - 2);
            }
        }
    }

    if (playing.subtitles == true) {
        if (info->adr_msg_time != NULL) {
            if ((int) msg_frame > (int) info->adr_msg_time[demo_msg_no].end) {
                
                fontClear();
                demo_msg_no++;
                DdsUnsetFlag(DDS_SUBTITLES_SHOWN);
            }
            if ((int) msg_frame > ((int) info->adr_msg_time[demo_msg_no].start) && !(DdsGetFlag(DDS_SUBTITLES_SHOWN))) {
                
                fontMessageNum(msg_buffer, info->msg_start + demo_msg_no);
                demo_status |= 8;
            }
        }
    }
    
    if (demo_status & 1) frm_dcm = 0.0f;
    else frm_dcm = demo_frame - fast_fptosi(fast_fptosi(demo_frame));

    
    for (i = 0; i < 3; i++) {
        position[i] = next.camera.position[i] * frm_dcm + last.camera.position[i] * (1.0f - frm_dcm);
        interest[i] = next.camera.interest[i] * frm_dcm + last.camera.interest[i] * (1.0f - frm_dcm);
    }
    position[0] += info->add_pos_x;
    position[2] += info->add_pos_z;
    interest[0] += info->add_pos_x;
    interest[2] += info->add_pos_z;
    position[3] = interest[3] = 1.0f;
    roll =  next.camera.roll * frm_dcm + last.camera.roll * (1.0f - frm_dcm);
    plane = next.camera.plane * frm_dcm + last.camera.plane * (1.0f - frm_dcm);
    vcSetEventCamParamRefView(position, NULL, interest, NULL, plane, 1);
    
    
    VbScreenInfo.scr_z = 1.14702f * roll;
    vbCalcViewScreenMatrix();
    vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
    
    
    for (i = 0, j = 0; j < point_light; i++, j++) {
        if (next.light[i].visible == 0) continue;
        for (k = 0; k < 3; k++) {
            position[k] = next.light[j].position[k] * frm_dcm  + last.light[j].position[k] * (1.0f - frm_dcm);
            color[k] = next.light[j].color[k] * frm_dcm + last.light[j].color[k] * (1.0f - frm_dcm);
        }
        falloff_s = next.light[i].falloff[0] * frm_dcm + last.light[i].falloff[0] * (1.0f - frm_dcm);
        falloff_e = next.light[i].falloff[1] * frm_dcm + last.light[i].falloff[1] * (1.0f - frm_dcm);
        sh2gfw_Set_DemoPointLight(j, position, color,  falloff_s, falloff_e);
    
    }
    for (j = 0; j < spot_light; i++, j++) {
        if (next.light[i].visible == 0) continue;
        for (k = 0; k < 3; k++) {
            position[k] = next.light[j].position[k] * frm_dcm  + last.light[j].position[k] * (1.0f - frm_dcm);
            interest[k] = next.light[j].interest[k] * frm_dcm + last.light[j].interest[k] * (1.0f - frm_dcm);
            color[k] = next.light[j].color[k] * frm_dcm + last.light[j].color[k] * (1.0f - frm_dcm);
        }
        vu0_sub_vector(normal, interest, position);
        vec_normalize(normal, normal);
        falloff_s = next.light[i].falloff[0] * frm_dcm + last.light[i].falloff[0] * (1.0f - frm_dcm);                             
        falloff_e = next.light[i].falloff[1] * frm_dcm + last.light[i].falloff[1] * (1.0f - frm_dcm);
        cone = next.light[i].cone[0] * frm_dcm + last.light[i].cone[0] * (1.0f - frm_dcm);
        position[3] = 1.0f;
        normal[3] = 0.0f;
        sh2gfw_Set_SpotLight(normal, position, color, 0, falloff_s, falloff_e, cone);
    
    }
    for (j = 0; j < infinite_light; i++, j++) {
        if (next.light[i].visible == 0) continue;
        for (k = 0; k < 3; k++) {
            position[k] = next.light[j].position[k] * frm_dcm + last.light[j].position[k] * (1.0f - frm_dcm);
            color[k] = next.light[j].color[k] * frm_dcm + last.light[j].color[k] * (1.0f - frm_dcm);
        }
        vec_zero(normal);
        vu0_sub_vector(normal, normal, position);
        vec_normalize(normal, normal);
        normal[3] = 0;
        sh2gfw_Set_PallarelLight(normal, color, j + 1);
    }

    
    for (i = 0; i < character_number; i++) {
        chara_p[i]->pos.x = info->add_pos_x + next.character[i].position[0] * frm_dcm + last.character[i].position[0] * (1.0f - frm_dcm);
        
        
        chara_p[i]->pos.y = next.character[i].position[1] * frm_dcm + last.character[i].position[1] * (1.0f - frm_dcm);
        
        
        chara_p[i]->pos.z = next.character[i].position[2] * frm_dcm + info->add_pos_z + last.character[i].position[2] * (1.0f - frm_dcm) ;

        
        chara_p[i]->rot.y = PI;
    }

    
    last.frame = demo_frame;
    if (DdsGetFlag(DDS_FLAG_5) && (((shSdStat() & 0xF0) == 0x10) || ((shSdStat() & 0xF0) == 0x50))) {
        
        shResetDF();
        DdsUnsetFlag(DDS_FLAG_5);
    }
    if (demo_frame < total_demo_frame) {
        demo_frame += 30.0f * shGetDT();
        demo_counter++;
    }
    msg_frame += 30.0f * shGetDT();
    // ??? lmao
    if (demo_frame >= total_demo_frame) return 1;
    if ((demo_frame - (tmp = (int) fast_fptosi((demo_frame)))) > 0.9999f) // demo_frame = 1.0f +  (float)(int)(float)(int)(float)(int) (float) (int) demo_frame; 
        demo_frame = 1.0f + ((int)(fast_fptosi(tmp))); 
    if ((msg_frame) -  fast_fptosi(fast_fptosi((msg_frame))) > 0.9999f)
        msg_frame = 1.0f + fast_fptosi((msg_frame));
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsPlay);
#endif

#line 676
void DdsPlayKey(void) {
    u_char c_work;

    while (1) {
        c_work = DdsReadByte();
        switch (c_work) {
            case DDS_PLAY_KEY_16:
                DdsSetFlag(DDS_FLAG_0);
                DdsSetFlag(DDS_FLAG_FLOAT32);
                break;
            case DDS_PLAY_KEY_17:
                DdsSetFlag(DDS_FLAG_START);
                break;
            case DDS_PLAY_KEY_20:
                DdsSetFlag(DDS_FLAG_4);
                break;
            case 18:
            case 19:
                break;
            case DDS_PLAY_KEY_BREAK /* 0xB (break?) */:
                return;
        }
    }
}

#line 708
static void DdsPlayCamera(void) {
    sceVu0FVECTOR camera_rotation; // r29+0x10
    u_char c_work; // r2
    int i; // r7

    while (1) {
        c_work = DdsReadByte();
        switch (c_work) {
            case DDS_PLAY_CAMERA_POSITION:
                if (DdsGetFlag(DDS_FLAG_FLOAT32)) {
                    for (i = 0; i < 3; i++) {
                        next.camera.position[i] = base.camera.position[i] = DdsReadFloat4();

                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.camera.position[i] = base.camera.position[i] + DdsReadFloat2();
                    
                    }
                }
                break;
            
            case DDS_PLAY_CAMERA_INTEREST:
                if (DdsGetFlag(DDS_FLAG_FLOAT32)) {
                    for (i = 0; i < 3; i++) {
                        next.camera.interest[i] = base.camera.interest[i] = DdsReadFloat4();
                    
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.camera.interest[i] = base.camera.interest[i] + DdsReadFloat2();
                    
                    }
                }
                break;
            
            case DDS_PLAY_CAMERA_ROTATION:
                camera_rotation[0] = DdsReadFloat2();
                camera_rotation[1] = DdsReadFloat2();
                camera_rotation[2] = DdsReadFloat2();
                camera_rotation[3] = 0;
                RotationToInterest(next.camera.position, camera_rotation, next.camera.interest, &next.camera.roll);
            
                
                break;
            
            case DDS_PLAY_CAMERA_ROLL:
                next.camera.roll = DdsReadFloat2();
                break;
            
            case DDS_PLAY_CAMERA_PLANE:
                next.camera.plane = DdsReadFloat4();
                break;
        
            
            case DDS_PLAY_CAMERA_8:
            case DDS_PLAY_CAMERA_9:
            case DDS_PLAY_CAMERA_10:
            case DDS_PLAY_CAMERA_11:
            default:
                return;
        }
    }
}


#line 772
static void DdsPlayLight(int no /* r16 */) {
    float light_rotation[4]; // r29+0x20
    u_char c_work; // r2
    int i; // r7

    while (1) {
        c_work = DdsReadByte();
        switch (c_work) {
            case DDS_PLAY_LIGHT_POSITION:
                if (DdsGetFlag(DDS_FLAG_FLOAT32)) {
                    for (i = 0; i < 3; i++) {
                        next.light[no].position[i] = base.light[no].position[i] = DdsReadFloat4();
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.light[no].position[i] = base.light[no].position[i] + DdsReadFloat2();
                    }
                }
                break;
            case DDS_PLAY_LIGHT_INTEREST:
                if (DdsGetFlag(DDS_FLAG_FLOAT32)) {
                    for (i = 0; i < 3; i++) {
                        next.light[no].interest[i] = base.light[no].interest[i] = DdsReadFloat4();
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.light[no].interest[i] = base.light[no].interest[i] + DdsReadFloat2();
                    }
                }
                break;
            case DDS_PLAY_LIGHT_ROTATION:
                light_rotation[0] = DdsReadFloat2();
                light_rotation[1] = DdsReadFloat2();
                light_rotation[2] = DdsReadFloat2();
                light_rotation[3] = 0;
                RotationToInterest(next.light[no].position, light_rotation, next.light[no].interest, NULL);
                break;
            case DDS_PLAY_LIGHT_COLOR:
                next.light[no].color[0] = DdsReadFloat2();
                next.light[no].color[1] = DdsReadFloat2();
                next.light[no].color[2] = DdsReadFloat2();
                break;
            case DDS_PLAY_LIGHT_FALLOFF:
                next.light[no].falloff[0] = DdsReadFloat2();
                next.light[no].falloff[1] = DdsReadFloat2();
                break;
            case DDS_PLAY_LIGHT_CONE:
                next.light[no].cone[0] = DdsReadFloat2();
                next.light[no].cone[1] = DdsReadFloat2();
                break;
            case DDS_PLAY_LIGHT_VISIBLE:
                next.light[no].visible = true;
                break;
            case DDS_PLAY_LIGHT_INVISIBLE:
                next.light[no].visible = false;
                break;
            case DDS_PLAY_LIGHT_11:
            default:
                return;
        }
    }
}

#line 851
static void DdsPlayCharacter(int no /* r8 */) {
    u_char c_work; // r2
    int i; // r7

    while (1) {
        c_work = DdsReadByte();
        switch (c_work) {
            case DDS_PLAY_CHARACTER_VISIBLE:
                next.character[no].visible = true;
                break;
            case DDS_PLAY_CHARACTER_INVISIBLE:
                next.character[no].visible = false;
                break;
            case DDS_PLAY_CHARACTER_POSITION:
                if (DdsGetFlag(DDS_FLAG_FLOAT32)) {
                    for (i = 0; i < 3; i++) {
                        next.character[no].position[i] = base.character[no].position[i] = DdsReadFloat4();
                        
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.character[no].position[i] = base.character[no].position[i] + DdsReadFloat2();
                    }
                }
                break;
            default:
            case DDS_PLAY_CHARACTER_11:
                return;
        }
    }
}

void DramaDemoSkipLast(DramaDemo_PlayInfo * info /* r16 */) {
    sceVu0FVECTOR position; // r29+0x40
    sceVu0FVECTOR interest; // r29+0x50
    float roll; // r29+0x60
    float plane; // r20
    u_short s_work; // r2
    u_char node_no; // r2
    int i; // r3

    DramaDemoFade();
    demo_frame = total_demo_frame;
    
    if(fptosi(last.frame) < fptosi(demo_frame)) {
        while (true) {
            if (DdsGetFlag(DDS_FLAG_START)) {
                DramaDemoAnimationStart(info->adr_anim);
                DdsUnsetFlag(DDS_FLAG_START);
            }

            DdsUnsetFlag(DDS_FLAG_0);
        
            s_work = DdsReadShort();
            DdsSkipBytes(-2);
            
            if (s_work == 0xFFFF) break;
            
            memcpy(&last, &next, sizeof(DdsFrame));
            DdsSkipBytes(2);
            while (1) {
                DdsUnsetFlag(DDS_FLAG_FLOAT32);
                node_no = DdsReadByte();
                if (node_no == 0xFF) break;
                if (node_no == 0) DdsPlayKey();
                else if (node_no == 1) DdsPlayCamera();
                else if (node_no - 2 < total_light)
                    DdsPlayLight(node_no - 2);
                else DdsPlayCharacter(node_no - total_light - 2);
            }
        }
    }

    
    demo_status |= (1 << 6);
    
    for (i = 0; i < 3; i++) {
        position[i] = last.camera.position[i];
        interest[i] = last.camera.interest[i];
    }
    position[3] = interest[3] = 0.0f;
    roll =  last.camera.roll;
    plane = last.camera.plane;
    vcSetEventCamParamRefView(position, NULL, interest, NULL, roll, 1);
    
    
    VbScreenInfo.scr_z = 1.14702f * plane;
    vbCalcViewScreenMatrix();
    vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);

    
    for (i = 0; i < character_number; i++) {
        chara_p[i]->pos.x =  last.character[i].position[0];
        
        
        chara_p[i]->pos.y = last.character[i].position[1];
        
        
        chara_p[i]->pos.z =  last.character[i].position[2];

        
        chara_p[i]->rot.y = PI;
    }

    
    last.frame = demo_frame;
}

static void RotationToInterest(float* position /* r19 */, float* rotation /* r18 */, float* interest /* r17 */, float* roll /* r16 */) {
    float matrix[4][4]; // r29+0x50
    float vector[4]; // r29+0x90
    vu0_unit_matrix(matrix);
    shRotMatrixZ(matrix, matrix, rotation[2]);
    shRotMatrixX(matrix, matrix, rotation[0]);
    shRotMatrixY(matrix, matrix, rotation[1]);
    vu0_unit_vector(vector);
    vector[2] = 1.0f;
    vu0_unit_vector(matrix[3]);
    vu0_transform_vector_alt(interest, vector, matrix);
    vu0_add_vector(interest, interest, position);
    if (roll != NULL) {
        roll[0] = rotation[2];
    }
}

void DramaDemoFade(void) { // @todo: add inlines
    PicDraw_Data pic;

    if (Check_Filter_Soft() == 0) {
        
        
        shQzero(&pic, sizeof(PicDraw_Data));
        pic.r = 0;
        pic.g = 0;
        pic.b = 0;
        pic.status |= 0x10;
        pic.test_ate = 0;
        pic.test_atst = 0;
        pic.test_aref = 0;
        pic.test_afail = 0;
        pic.test_date = 0;
        pic.test_datm = 0;
        pic.test_zte = 1;
        pic.test_ztst = 1;
        pic.status |= 0x40;
        pic.x0 = -4096;
        pic.y0 = -4096;
        pic.x1 = 4096;
        pic.y1 = -3072;
        pic.status |= 2;
        PictureDraw(&pic);
        pic.x0 = -4096;
        pic.y0 = 3072;
        pic.x1 = 4096;
        pic.y1 = 4096;
        pic.status |= 2;
        PictureDraw(&pic);
    }
}

int DramaDemoNumber(void) {
    return demo_number;
}

void SubtitlesExec(DramaDemo_MessageTime* msg_time /* r2 */, int msg_no /* r2 */, int str_no /* r2 */, float timer /* r29 */)  {
    sbt_msg_time = msg_time;
    sbt_msg_no = msg_no;
    sbt_str_no = str_no;
    sbt_timer = timer;
}

void SubtitlesManager(void) {
    if (sbt_msg_no) {
        if (!sbt_str_no && !(shSdStat() & 0xF0)) {
            sbt_msg_no = 0;
            return;
        }
        if (!sbt_str_no || !(shSdStat() & 0xF0)) {
            if (sbt_str_no) {
                shSdCall(sbt_str_no, 0, 0, 0);
                sbt_str_no = 0;
            }
            if (sbt_timer == 0.0f) {
                if ((shSdStat() & 0xF0) != 0x40) {
                    return;
                }
                shSdCall(SH2_SOUND_1015, 0, 0, 0);
                DdsUnsetFlag(DDS_FLAG_SUBTITLES_SHOWN);
            }
            sbt_timer += 30.0f * shGetDT();
            if (playing.subtitles) {
                if ((int) sbt_timer > sbt_msg_time->end) {
                    fontClear();
                    sbt_msg_time++;
                    DdsUnsetFlag(DDS_FLAG_SUBTITLES_SHOWN);
                }
                if (((int) sbt_timer > sbt_msg_time->start) && !DdsGetFlag(DDS_FLAG_SUBTITLES_SHOWN)) {
                    fontMessageNum(msg_buffer, sbt_msg_no);
                    sbt_msg_no++;
                    DdsSetFlag(DDS_FLAG_SUBTITLES_SHOWN);
                }
            }
        }
    }
}
