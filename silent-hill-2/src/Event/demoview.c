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

#include "Event/event.h"
#include "Event/demoview.h"
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

/* ========= data ========= */

static DramaDemo_AnimInfo anim_info[79]; // size: 0xC58, address: 0x2BA080

/* ========= bss ========= */

int demo_status; // size: 0x4, address: 0x1133C28
float demo_frame; // size: 0x4, address: 0x1133C20
float total_demo_frame; // size: 0x4, address: 0x1133C18
int demo_number; // size: 0x4, address: 0x1133C10
int demo_counter; // size: 0x4, address: 0x1133C08

int sbt_msg_no;       // size: 0x4, address: 0x1133C00

DdsFrame last; // size: 0x360, address: 0x11338A0
DdsFrame next; // size: 0x360, address: 0x1133540
DdsFrame base; // size: 0x360, address: 0x11331E0
SubCharacter* chara_p[7]; // size: 0x1C, address: 0x11331C0


void* adr_dds; // size: 0x4, address: 0x11331B0
short total_light; // size: 0x2, address: 0x11331A8
short point_light; // size: 0x2, address: 0x11331A0
short spot_light; // size: 0x2, address: 0x1133198
short infinite_light; // size: 0x2, address: 0x1133190
int character_number; // size: 0x4, address: 0x1133188

u_short demo_anim_no; // size: 0x2, address: 0x1133180
u_short demo_msg_no; // size: 0x2, address: 0x1133178
u_short demo_voice_no; // size: 0x2, address: 0x1133170

float msg_frame; // size: 0x4, address: 0x1133168

DramaDemo_MessageTime* sbt_msg_time; // size: 0x4, address: 0x1133160
int sbt_str_no; // size: 0x4, address: 0x1133158
float sbt_timer = 0.0f; // size: 0x4, address: 0x1133148

static inline float fast_fptosi(float x) {
    asm volatile("cvt.w.s %0, %0; cvt.s.w %0, %0": "+f"(x));
    return x;
}

static inline void DdsSkipBytes(int size) {
    (s_char*) adr_dds += size;
}
static inline void DdsReadString(s_char* buf) {
    strncpy(buf, (s_char*) adr_dds, 16);
    DdsSkipBytes(16);
}
#define DdsReadByte() (*(((s_char*) adr_dds)++))

static short DdsReadShort(void) {
    u_char c_work[2];
    
    c_work[0] = DdsReadByte();
    c_work[1] = DdsReadByte();
    
    return *(short *)c_work;
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
        if (!GET_BIT(demo_status, 7)) {
            if (!(shSdStat() & 0xF0)) shSdCall(info->stream_no, 0, 0, 0);
            shResetDF();
            SET_BIT(demo_status, 7);
        } else if (!GET_BIT(demo_status, 8) && demo_frame >= info->stream_start) {
            // @todo: add macros
            if ((shSdStat() & 0xF0) == 0x40) {
                stop_counter += shGetDTreal();
                printf("Stream read stop: %5.3f\n", stop_counter);
                shSdCall(SH2_SOUND_1015, 0, 0, 0);
                shResetDF();
                SET_BIT(demo_status, 8);
            } else {
                stop_counter += shGetDTreal();
                shSetDFZero();
            }
        }
    }

    
    ret = DdsPlay(info);
    if (!GET_BIT(demo_status, 9) && shPadTrigger(0, key_config.skip)) {
        ret = 1;
        fontClear();
        shSdCall(SH2_SOUND_1012, 0, 0, 0);
    }
    return ret;
}

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
    if (GET_BIT(demo_status, 2)) {
        DramaDemoAnimationStart(info->adr_anim);
        UNSET_BIT(demo_status, 2);
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
        if (GET_BIT(demo_status, 2)) {
            DramaDemoAnimationStart(info->adr_anim);
            UNSET_BIT(demo_status, 2);
        }
    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        UNSET_BIT(demo_status, 0);
        while (true) {
            UNSET_BIT(demo_status, 1);
        
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
                UNSET_BIT(demo_status, 3);
            }
            if ((int) msg_frame > ((int) info->adr_msg_time[demo_msg_no].start) && !(GET_BIT(demo_status, 3))) {
                
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
    if (GET_BIT(demo_status, 5) && (((shSdStat() & 0xF0) == 0x10) || ((shSdStat() & 0xF0) == 0x50))) {
        
        shResetDF();
        UNSET_BIT(demo_status, 5);
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
            case 16:
                SET_BIT(demo_status, 0);
                SET_BIT(demo_status, 1);
                break;
            case 17:
                SET_BIT(demo_status, 2);
                break;
            case 20:
                SET_BIT(demo_status, 4);
                break;
            case 18:
            case 19:
                break;
            case 11 /* 0xB (break?) */:
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
            case 3:
                if (GET_BIT(demo_status, 1)) {
                    for (i = 0; i < 3; i++) {
                        next.camera.position[i] = base.camera.position[i] = DdsReadFloat4();

                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.camera.position[i] = base.camera.position[i] + DdsReadFloat2();
                    
                    }
                }
                break;
            
            case 4:
                if (GET_BIT(demo_status, 1)) {
                    for (i = 0; i < 3; i++) {
                        next.camera.interest[i] = base.camera.interest[i] = DdsReadFloat4();
                    
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.camera.interest[i] = base.camera.interest[i] + DdsReadFloat2();
                    
                    }
                }
                break;
            
            case 5:
                camera_rotation[0] = DdsReadFloat2();
                camera_rotation[1] = DdsReadFloat2();
                camera_rotation[2] = DdsReadFloat2();
                camera_rotation[3] = 0;
                RotationToInterest(next.camera.position, camera_rotation, next.camera.interest, &next.camera.roll);
            
                
                break;
            
            case 6:
                next.camera.roll = DdsReadFloat2();
                break;
            
            case 7:
                next.camera.plane = DdsReadFloat4();
                break;
        
            
            case 8:
            case 9:
            case 10:
            case 11:
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
            case 3:
                if (GET_BIT(demo_status, 1)) {
                    for (i = 0; i < 3; i++) {
                        next.light[no].position[i] = base.light[no].position[i] = DdsReadFloat4();
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.light[no].position[i] = base.light[no].position[i] + DdsReadFloat2();
                    }
                }
                break;
            case 4:
                if (GET_BIT(demo_status, 1)) {
                    for (i = 0; i < 3; i++) {
                        next.light[no].interest[i] = base.light[no].interest[i] = DdsReadFloat4();
                    }
                } else {
                    for (i = 0; i < 3; i++) {
                        next.light[no].interest[i] = base.light[no].interest[i] + DdsReadFloat2();
                    }
                }
                break;
            case 5:
                light_rotation[0] = DdsReadFloat2();
                light_rotation[1] = DdsReadFloat2();
                light_rotation[2] = DdsReadFloat2();
                light_rotation[3] = 0;
                RotationToInterest(next.light[no].position, light_rotation, next.light[no].interest, NULL);
                break;
            case 8:
                next.light[no].color[0] = DdsReadFloat2();
                next.light[no].color[1] = DdsReadFloat2();
                next.light[no].color[2] = DdsReadFloat2();
                break;
            case 9:
                next.light[no].falloff[0] = DdsReadFloat2();
                next.light[no].falloff[1] = DdsReadFloat2();
                break;
            case 10:
                next.light[no].cone[0] = DdsReadFloat2();
                next.light[no].cone[1] = DdsReadFloat2();
                break;
            case 1:
                next.light[no].visible = true;
                break;
            case 2:
                next.light[no].visible = false;
                break;
            case 11:
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
            case 1:
                next.character[no].visible = true;
                break;
            case 2:
                next.character[no].visible = false;
                break;
            case 3:
                if (GET_BIT(demo_status, 1)) {
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
            case 11:
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
            if (GET_BIT(demo_status, 2)) {
                DramaDemoAnimationStart(info->adr_anim);
                UNSET_BIT(demo_status, 2);
            }

            UNSET_BIT(demo_status, 0);
        
            s_work = DdsReadShort();
            DdsSkipBytes(-2);
            
            if (s_work == 0xFFFF) break;
            
            memcpy(&last, &next, sizeof(DdsFrame));
            DdsSkipBytes(2);
            while (1) {
                UNSET_BIT(demo_status, 1);
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
                UNSET_BIT(demo_status, 3);
            }
            sbt_timer += 30.0f * shGetDT();
            if (playing.subtitles) {
                if ((int) sbt_timer > sbt_msg_time->end) {
                    fontClear();
                    sbt_msg_time++;
                    UNSET_BIT(demo_status, 3);
                }
                if (((int) sbt_timer > sbt_msg_time->start) && !GET_BIT(demo_status, 3)) {
                    fontMessageNum(msg_buffer, sbt_msg_no);
                    sbt_msg_no++;
                    SET_BIT(demo_status, 3);
                }
            }
        }
    }
}
