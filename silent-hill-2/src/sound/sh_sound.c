#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/sh_character_battle.h"
#include "Chacter/sh2_character_manage.h"

#include "data/fs_structs.h"
#include "data/daily.thu/data_sound_snd_data.h"
#include "data/daily.thu/data_sound_s_force.h"

#include "DBG/dbflag.h"

#include "debug.h"

#include "Event/event.h"

#include "Multi_thr/filesys/fcread.h"

#include "shared/Fog/fog.h" // added only for float_sign, should be probably moved somewhere else

#include "SH2_common/playing_info.h"
#include "sce/libvu0.h"
#include "SH2_common/sh_vu0.h"

#include "SH2_common/sh2dt.h"
#include "SH2_common/sh2sys.h"

#include "vec.h"

#include "view/vb_main.h"
#include "view/vc_main.h"

#pragma fast_fptosi on

static int SeChange2Dto3D(int se /* r2 */);
static int SeChange3Dto2D(int se /* r2 */);

int se_3d_channel_max;
Se_BgmBuffer bgm; // size: 0x4C, address: 0x10E5880
u_char snd_data_buffer[20480] __attribute__((aligned(64))); // size: 0x5000, address: 0x10E0880
float se_f_work;
Se2D_ManageData se_2d_manage_data[4]; // size: 0x100, address: 0x10E0750
Se3D_ChannelData se_3d_channel_data[8]; // size: 0x180, address: 0x10E05D0
int se_3d_channel_number;
int se_load_data;
int se_3d_load_data;
SOUND_WORK sound_work;

void SeWait(int wait /* r17 */) {
    int c; // r16

    if (!dbFlag(1)) {
        do {
            VERBOSE_ON_LINE(150, 4, ">>>>+++\n");
            c = wait;
            while (c > 0) {
                if (!shSdStat()) {
                    VERBOSE_ON_LINE(153, 4, "<<<<%d", c);
                    c--;
                }
                shSyncVEnd(0);
                shSdVSync();
            }
        } while (shSdStat());
        VERBOSE_ON_LINE(160, 4, "<<<<%d", c);
    }
}

void SeForceWait(void) {
    SeWait(0x3C);
}

void SeCallInit(int sect /* r18 */, int mmode /* r17 */, char* path /* r16 */) {
    if (!dbFlag(1)) {
        VERBOSE_ON_LINE(182, 2, "==========1\n");

        VERBOSE_ON_LINE(184, 2, "sector: %d\n", sect);
        if (path) {
            sd_setpath(path);
        }
        shSdInit();
        shSdCall(0x3E8, sect, mmode, 0);
        shSdCall(0x411, 0, 0, 0);
        VERBOSE_ON_LINE(194, 2, "==========2\n");
        shSdStat();
        SeForceWait();
    }
}

void SeCallReset(void) {
    int i; // r4
    
    if (!dbFlag(1)) {
        SeWait(3);
        shSdCall(0, 0, 0, 0);
        SeWait(3);
        shSd3dAllStop();
        SeWait(3);
    }
    for (i = 0; i < 4; i++) {
        se_2d_manage_data[i].sd = 0;
    }
    se_3d_channel_max = 4;
    se_3d_channel_number = 0;
    for (i = 0; i < 8; i++) {
        se_3d_channel_data[i].sd = 0;
    }
    shQzero(&bgm, sizeof(Se_BgmBuffer));
    if (!dbFlag(1)) {
        SeMasterVolumeChange();
        SeWait(3);
    }
    se_load_data = 0;
    se_3d_load_data = 0;
    shQzero(&sound_work, sizeof(SOUND_WORK));
}

int SeCall(int sd_no /* r17 */, float volume /* r20 */, int stereo /* r16 */) {
    int ret; // r2

    if (dbFlag(1)) {
        return 0x10;
    }
    if (!sd_no) {
        return 0xF;
    }
    ret = shSdCall(sd_no, stereo, 255.0f - (255.0f * volume), 0);
    if (ret != -1) {
        ret = 0x10;
    }
    return ret;
}

int SeCallPos(int sd_no, float volume, float* pos, int status) {
    int direction;
    int distance;
    int work;
    int ret;
    int i;

    if (sd_no == 0) return 15;
    
    if (dbFlag(1)) return 16;    
    
    if ((status & 8) && !(status & 3)) {
        for (i = 0; i < 4; i++) 
            if (sd_no == se_2d_manage_data[i].sd) return 15;                   
        for (i = 0; i < 4; i++) 
            if (se_2d_manage_data[i].sd == 0) break;        
        ASSERT_ON_LINE(i < 4, 281);
        se_2d_manage_data[i].sd = sd_no;
        se_2d_manage_data[i].room = RoomNameJms();
        if (pos != NULL) {
            shVectorCopy(se_2d_manage_data[i].pos, pos);
            se_2d_manage_data[i].pos_on = 1;
        } else se_2d_manage_data[i].pos_on = 0;        
        se_2d_manage_data[i].vol = volume;
        se_2d_manage_data[i].status = status;
        se_2d_manage_data[i].timer = 0.0f;
        se_2d_manage_data[i].base = 0.0f;
    }
    
    if ((status & 3) == 1) {
        if (se_3d_channel_max > se_3d_channel_number) {
            work = SeChange2Dto3D(sd_no);
            if (work) sd_no = work;            
        } else {
            sd_no = SeChange3Dto2D(sd_no);
            if (sd_no == 0) return 15;
            
        }
    }
    if ((status & 4) || (pos == NULL)) 
        distance = 255 - ftoi(255.0f * volume);
    else distance = SeCallPosDistance(volume, pos);    
    if (pos != NULL) direction = SeCallPosDirection(pos);
    else direction = 0;
    
    if (status & 8) {
        se_2d_manage_data[i].pre_dist = distance;
        se_2d_manage_data[i].pre_pan = direction;
    }
    
    if (sd_no >= 40000) {
        ret = shSd3dCall(sd_no, direction, distance, 1.0f, 0.0f);
        if (ret != -1) {
            se_3d_channel_data[ret].sd = sd_no;
            se_3d_channel_data[ret].status = status;
            shVectorCopy(se_3d_channel_data[ret].pos, pos);
            se_3d_channel_data[ret].vol = volume;
            se_3d_channel_data[ret].room = RoomNameJms();
            if ((status & 3) == 1) se_3d_channel_number++;            
        } else 
            if ((status & 3) == 1) {
                return SeCallPos(sd_no, volume, pos, status - (status & 3));
        }
    } else {
        
        
        ret = shSdCall(sd_no, direction, distance, 0);
        if (ret != -1) ret = 16;        
    }
    return ret;
}

#line 348
int SeCallPosChange(int sd_no, float volume, float* pos, int status) {
    int direction; 
    int distance;
    int ret;
    int work;
    int i;
   
    if (sd_no == 0) return 15;
    
    if (dbFlag(1)) return 16;
    
    if (pos == NULL) {
        direction = 0;
        distance = ftoi(255.0f - 255.0f * volume);
    } else {
        direction = SeCallPosDirection(pos);
        if (status & 4) 
            distance = 255 - ftoi(255.0f * volume);
        else distance = SeCallPosDistance(volume, pos);
        
    }
    if (status & 8) {
        for (i = 0; i < 4; i++)
            if (sd_no == se_2d_manage_data[i].sd) break;        
        work = ftoi(128.0f * shGetDT());
        if (distance < se_2d_manage_data[i].pre_dist - work) 
            distance = se_2d_manage_data[i].pre_dist - work;
        else if (work + se_2d_manage_data[i].pre_dist < distance) 
            distance = work + se_2d_manage_data[i].pre_dist;        
        se_2d_manage_data[i].pre_dist = distance;
        if (direction < se_2d_manage_data[i].pre_pan - work) 
            direction = se_2d_manage_data[i].pre_pan - work;
        else if (work + se_2d_manage_data[i].pre_pan < direction) 
            direction = work + se_2d_manage_data[i].pre_pan;
        se_2d_manage_data[i].pre_pan = direction;
    }
    ret = shSdSeChange(sd_no, direction, distance, 0);
    if (ret != -1) ret = 16;
    
    return ret;
}

int SeCallPosDirection(float* pos) {
    sceVu0FVECTOR fv; // r29
    sceVu0FVECTOR pos0; // r29+0x10
    float sign; // r29+0x20

    vec_copy_vu0(pos0, pos);
    vu0_transform_vector_alt(fv, pos0, VbWvsMatrix.wvm);
    fv[0] -= 750.0f;
    fv[1] = 0.0f;
    shNormalizeVector(fv, fv);
    sign = float_sign(-fv[0]);
    return (sign * (70.0f - (70.0f * fv[2])));
}

int SeCallPosDistance(float volume, float* pos) {
    sceVu0FVECTOR fvec; // r29
    sceVu0FVECTOR pos0; // r29+0x10
    float len; /* r29+0x20 */ float work_0; /* r29+0x20 */ float work_1; // r29+0x20


    vec_copy_vu0(pos0, pos);
    shSubVector(fvec, vcWork.cam_pos, &sh2jms.player->pos);
    len = vec3_lenght_alt(fvec);    
    work_0 = (len - 1500.0f) * 0.000100000005f;
    work_0 = 1.0f - shFloatMin(shFloatMax(0.0f, work_0), 1.0f);
    shSubVector(fvec, pos0, &sh2jms.player->pos);
    len = vec3_lenght_alt(fvec);    
    work_1 = (len - 1500.0f) * 0.000100000005f;
    work_1 = 1.0f - shFloatMin(shFloatMax(0.0f, work_1), 1.0f);

    return 255.0f - (volume * (255.0f * work_0 * work_1));
}

float SeCallPosDistanceF(float* pos) {
    sceVu0FVECTOR fvec; // r29
    sceVu0FVECTOR pos0; // r29+0x10
    float len; /* r29+0x20 */ float work_0; /* r29+0x20 */ float work_1; // r29+0x20


    vec_copy_vu0(pos0, pos);
    shSubVector(fvec, vcWork.cam_pos, &sh2jms.player->pos);
    len = vec3_lenght_alt(fvec);    
    work_0 = (len - 1500.0f) * 0.000100000005f;
    work_0 = 1.0f - shFloatMin(shFloatMax(0.0f, work_0), 1.0f);
    shSubVector(fvec, pos0, &sh2jms.player->pos);
    len = vec3_lenght_alt(fvec);    
    work_1 = (len - 1500.0f) * 0.000100000005f;
    work_1 = 1.0f - shFloatMin(shFloatMax(0.0f, work_1), 1.0f);

    return work_0 * work_1;
}

int Se3dPlayCheck(int sd_no /* r2 */) {
    int i; // r5

    for (i = 0; i < 8; i++) {
        if (se_3d_channel_data[i].sd == sd_no) {
            return 1;
        }
    }
    return 0;
}

void SeSoundLoad(void) {
    SeSoundEffectLoad(0);
    SeSoundEffect3dLoad(0);
    SeBgmChange();
}

void SeSoundEffectLoad(int data) {
    int room;

    if (!dbFlag(1)) {
        room = RoomNameJms();
        if (data == 0) {
            switch (playing.stage) { // Is this StgName?
                case 0x0:
                    data = 5023;
                    break;
                case 0x5:
                    if (GET_GAME_FLAG(GAME_FLAG_251)) {
                        data = 5025;
                    } else {
                        data = 5024;
                    }
                    break;
                case 0xE:
                    if (GET_GAME_FLAG(GAME_FLAG_251)) {
                        data = 5027;
                    } else {
                        data = 5026;
                    }
                    break;
                case 0x4:
                    data = 5007;
                    break;
                case 0x6:
                case 0x7:
                case 0x8:
                case 0x9:
                case 0xD:
                    data = 5000;
                    break;
                case 0xA:
                case 0xB:
                    data = 5002;
                    break;
                case 0xC:
                    data = 5001;
                    break;
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                    data = 5009;
                    break;
                case 0x17:
                case 0x18:
                case 0x19:
                case 0x1A:
                case 0x1B:
                    data = 5008;
                    break;
                case 0x16:
                    if (room == 0x30) {
                        data = 5015;
                    } else {
                        data = 5008;
                    }
                    break;
                case 0x1D:
                case 0x1E:
                    data = 5004;
                    break;
                case 0x1F:
                    data = 5020;
                    break;
                case 0x20:
                    data = 5021;
                    break;
                case 0x22:
                    data = 5018;
                    break;
                case 0x23:
                case 0x24:
                    data = 5016;
                    break;
                case 0x25:
                    data = 5005;
                    break;
                case 0x26:
                    data = 5019;
                    break;
                case 0x27:
                case 0x2B:
                case 0x2F:
                    data = 5014;
                    break;
                case 0x28:
                    data = 5011;
                    break;
                case 0x2C:
                    data = 5010;
                    break;
                case 0x29:
                case 0x2D:
                    data = 5012;
                    break;
                case 0x2A:
                case 0x2E:
                    data = 5013;
                    break;
                case 0x30:
                case 0x31:
                case 0x32:
                case 0x33:
                    data = 5006;
                    break;
            }
        }
        if ((data) && (data != se_load_data)) {
            se_load_data = data;
            shSdCall(0x3F2, 0, 0, 0);
            shSdCall(data, 0, 0, 0);
        }
    }
}

void SeSoundEffect3dLoad(int data) {
    static fsFileIndex* se_file_list_1329[35] = { NULL, data_sound_s_force_town_east_a_sfc, data_sound_s_force_town_east_b_sfc, data_sound_s_force_town_west_a_sfc, data_sound_s_force_town_west_b_sfc, data_sound_s_force_apart_e1f_sfc, data_sound_s_force_apart_e2f_sfc, data_sound_s_force_apart_e3f_sfc, data_sound_s_force_apart_w1f_sfc, data_sound_s_force_apart_w2f_sfc, data_sound_s_force_apart_stair_sfc, data_sound_s_force_hospital_1f_f_sfc, data_sound_s_force_hospital_2f_f_sfc, data_sound_s_force_hospital_3f_f_sfc, data_sound_s_force_hospital_rf_f_sfc, data_sound_s_force_iketani_sfc, data_sound_s_force_hospital_1f_b_sfc, data_sound_s_force_hospital_2f_b_sfc, data_sound_s_force_hospital_3f_b_sfc, data_sound_s_force_hospital_bf_b_sfc, data_sound_s_force_hospital_pass_sfc, data_sound_s_force_delusion_2_sfc, data_sound_s_force_delusion_3_sfc, data_sound_s_force_prison_sfc, data_sound_s_force_labyrinth_w_sfc, data_sound_s_force_labyrinth_e_sfc, data_sound_s_force_labyrinth_n_sfc, data_sound_s_force_eddie_boss_sfc, data_sound_s_force_hotel_bf_f_sfc, data_sound_s_force_hotel_1f_f_sfc, data_sound_s_force_hotel_2f_f_sfc, data_sound_s_force_hotel_bf_b_sfc, data_sound_s_force_hotel_1f_b_sfc, data_sound_s_force_hotel_2f_b_sfc, NULL };
    int room;
    int i;

    if (dbFlag(1U) == 0) {
        room = RoomNameJms();
        if (data == 0) {
            switch (playing.stage) {
                case 0x5:
                    if (GET_GAME_FLAG(GAME_FLAG_251)) {
                        data = 2;
                    } else {
                        data = 1;
                    }
                    break;
                case 0xE:
                    if (GET_GAME_FLAG(GAME_FLAG_251)) {
                        data = 4;
                    } else {
                        data = 3;
                    }
                    break;
                case 0x6:
                    data = 5;
                    break;
                case 0x7:
                    data = 6;
                    break;
                case 0x9:
                    data = 7;
                    break;
                case 0x8:
                    data = 7;
                    break;
                case 0xA:
                    data = 8;
                    break;
                case 0xB:
                    data = 9;
                    break;
                case 0xC:
                    data = 10;
                    break;
                case 0x12:
                    data = 11;
                    break;
                case 0x13:
                    data = 12;
                    break;
                case 0x14:
                    data = 13;
                    break;
                case 0x15:
                    data = 14;
                    break;
                case 0x16:
                    if (room == 0x30) {
                        data = 15;
                    } else {
                        data = 16;
                    }
                    break;
                case 0x17:
                    data = 16;
                    break;
                case 0x18:
                    data = 17;
                    break;
                case 0x19:
                    data = 18;
                    break;
                case 0x1A:
                    data = 19;
                    break;
                case 0x1B:
                    data = 20;
                    break;
                case 0x1D:
                    data = 21;
                    break;
                case 0x1E:
                    data = 22;
                    break;
                case 0x1F:
                case 0x20:
                    data = 23;
                    break;
                case 0x22:
                    data = 26;
                    break;
                case 0x23:
                    data = 26;
                    break;
                case 0x24:
                    data = 26;
                    break;
                case 0x25:
                    data = 27;
                    break;
                case 0x27:
                    data = 28;
                    break;
                case 0x28:
                    data = 29;
                    break;
                case 0x29:
                    data = 30;
                    break;
                case 0x2B:
                    data = 31;
                    break;
                case 0x2C:
                    data = 32;
                    break;
                case 0x2D:
                    data = 33;
                    break;
                case 0x30:
                case 0x31:
                case 0x32:
                case 0x33:
                    data = 34;
                    break;
            }
        }
        if (data && (data != se_3d_load_data)) {
            se_3d_load_data = data;
            shSd3dAllStop();
            for (i = 0; i < 8; i++) {
                se_3d_channel_data[i].sd = 0;
            }
            FcRead(se_file_list_1329[data], shSd3dAdrs());
        }
    }
}

void SeSoundManager(void) {
    Se2dManager();
    Se3dManager();
    SeBgmManager();
}

void Se2dManager(void) {
    int room;
    int i;
    float volume;

    if (sh2jms.player != NULL) {
        room = RoomNameJms();
    } else {
        room = 0;
    }
    for (i = 0; i < 4; i++) {
        if (se_2d_manage_data[i].sd != 0) {
            if ((room != 0) && (room != se_2d_manage_data[i].room)) {
                SeStop(se_2d_manage_data[i].sd);
            } else {
                switch (Sh2sys.step[SH2SYS_PLAYABLE_MAIN]) {
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        volume = 0.5f;
                        break;
                    case 0xE:
                    default: {
                        int demo = DramaDemoNumber();
                        if ((demo != 2) && (demo != 0xE) && (demo != 1) && (demo != 0)) {
                            volume = 0.7f;
                        } else {
                            volume = 1.0f;
                        }
                        break;
                    }
                }
                if (!(se_2d_manage_data[i].base <= volume)) {
                    se_2d_manage_data[i].base = shFloatMax(se_2d_manage_data[i].base - shGetDT(), volume);
                } else if (se_2d_manage_data[i].base < volume) {
                    se_2d_manage_data[i].base = shFloatMin(se_2d_manage_data[i].base + shGetDT(), volume);
                }
                if (se_2d_manage_data[i].pos_on != 0) {
                    SeCallPosChange(se_2d_manage_data[i].sd, se_2d_manage_data[i].vol * se_2d_manage_data[i].base, se_2d_manage_data[i].pos, se_2d_manage_data[i].status);
                } else {
                    SeCallPosChange(se_2d_manage_data[i].sd, se_2d_manage_data[i].vol * se_2d_manage_data[i].base, 0, se_2d_manage_data[i].status);
                }
                se_2d_manage_data[i].timer += shGetDT();
            }
        }
    }
}

void Se2dManageDataVolumeChange(int sd /* r2 */, float vol /* r29+0x10 */) {
    int i; // r6

    for (i = 0; i < 4; i++) {
        if (se_2d_manage_data[i].sd == sd) {
            break;
        }
    }
    if (i == 4) {
        return;
    }
    if (vol < 0.0f) {
        SeStop(sd);
        return;
    }
    if (vol > 1.0f) {
        vol = 1.0f;
    }
    se_2d_manage_data[i].vol = vol;
}

float Se2dManageDataTimer(int sd /* r2 */, int clear /* r2 */) {
    int i; // r6
    
    for (i = 0; i < 4; i++) {
        if (se_2d_manage_data[i].sd == sd) {
            break;
        }       
    }
    if (i == 4) {
        return -1.0f;
    }
    if (clear) {
        se_2d_manage_data[i].timer = 0.0f;
    }
    return se_2d_manage_data[i].timer;
}

void Se3dManager(void) {
    int direction;
    int distance;
    int ret; 
    int room;
    int i;

    if (dbFlag(1)) return;
      
    room = RoomNameJms();
    
    for (i = 0; i < 8; i++) {
        if (se_3d_channel_data[i].sd) {
            if (room != se_3d_channel_data[i].room) {
                SeStop(se_3d_channel_data[i].sd);
            } else {
                
                direction = SeCallPosDirection(se_3d_channel_data[i].pos);
                if (se_3d_channel_data[i].status & 4) 
                    distance = 255 - ftoi(255.0f * se_3d_channel_data[i].vol);
                else distance = SeCallPosDistance(se_3d_channel_data[i].vol, se_3d_channel_data[i].pos);
                
                ret = shSd3dMove(i, direction, distance, 0.0f, 0.0f);
                if (ret == -1) {
                    se_3d_channel_data[i].sd = 0;
                    if ((se_3d_channel_data[i].status & 3) == 1) 
                        se_3d_channel_number -= 1;                    
                }
            }
        }
    }
    
}

int Se3dControl(int sd_no /* r17 */, float volume /* r20 */, float* pos /* r16 */) {
    int i; // r4

    if (dbFlag(1)) {
        return 0x10;
    }
    if (!sd_no) {
        return 0xF;
    }
    for (i = 0; i < 8; i++) {
        if (se_3d_channel_data[i].sd == sd_no) {
            break;
        }
    }
    if (i == 8) {
        return -1;
    }
    shVectorCopy(se_3d_channel_data[i].pos, pos);
    se_3d_channel_data[i].vol = volume;
    return 0x10;
}

void SeStop(int sd_no /* r18 */) {
    int i; // r16
    int work; // r2
    
    if (dbFlag(1)) {
        return;
    }
    if (!sd_no) {
        return;
    }
    if (sd_no < 0x9C40) {
        shSdSeStop(sd_no);
        for (i = 0; i < 4; i++) {
            if (se_2d_manage_data[i].sd == sd_no) {
                break;
            }
        }
        if (i != 4) {
            se_2d_manage_data[i].sd = 0;
        }
        sd_no = SeChange2Dto3D(sd_no);
        if (!sd_no) {
            return;
        }
    } else {
        work = SeChange3Dto2D(sd_no);
        if (work) {
            shSdSeStop(work);
        }
    }
    for (i = 0; i < 8; i++) {
        if (se_3d_channel_data[i].sd == sd_no) {
            shSd3dStop(i);
            se_3d_channel_data[i].sd = 0;
            if ((se_3d_channel_data[i].status & 3) == 1) {
                se_3d_channel_number--;
            }
        }
    }
}

static fsFileIndex* sdb_list[53] = { data_sound_snd_data_null_sdb, data_sound_snd_data_tgs_trial_sdb, data_sound_snd_data_toilet_sdb, data_sound_snd_data_observation_sdb, data_sound_snd_data_forest_sdb, data_sound_snd_data_town_east_sdb, data_sound_snd_data_apart_e1f_sdb, data_sound_snd_data_apart_e2f_sdb, data_sound_snd_data_apart_e3fw_sdb, data_sound_snd_data_apart_e3fe_sdb, data_sound_snd_data_apart_w1f_sdb, data_sound_snd_data_apart_w2f_sdb, data_sound_snd_data_apart_stair_sdb, data_sound_snd_data_apart_out_sdb, data_sound_snd_data_town_west_sdb, data_sound_snd_data_bowling_sdb, data_sound_snd_data_to_heaven_sdb, data_sound_snd_data_heaven_night_sdb, data_sound_snd_data_hospital_1f_f_sdb, data_sound_snd_data_hospital_2f_f_sdb, data_sound_snd_data_hospital_3f_f_sdb, data_sound_snd_data_hospital_rf_f_sdb, data_sound_snd_data_hospital_1fw_b_sdb, data_sound_snd_data_hospital_1fe_b_sdb, data_sound_snd_data_hospital_2f_b_sdb, data_sound_snd_data_hospital_3f_b_sdb, data_sound_snd_data_hospital_bf_b_sdb, data_sound_snd_data_hospital_pass_sdb, data_sound_snd_data_society_sdb, data_sound_snd_data_delusion_2_sdb, data_sound_snd_data_delusion_3_sdb, data_sound_snd_data_prison_n_sdb, data_sound_snd_data_prison_s_sdb, data_sound_snd_data_prison_bf_sdb, data_sound_snd_data_labyrinth_w_sdb, data_sound_snd_data_labyrinth_e_sdb, data_sound_snd_data_labyrinth_n_sdb, data_sound_snd_data_eddie_boss_sdb, data_sound_snd_data_lake_sdb, data_sound_snd_data_hotel_bf_f_sdb, data_sound_snd_data_hotel_1f_f_sdb, data_sound_snd_data_hotel_2f_f_sdb, data_sound_snd_data_hotel_3f_f_sdb, data_sound_snd_data_hotel_bf_b_sdb, data_sound_snd_data_hotel_1f_b_sdb, data_sound_snd_data_hotel_2f_b_sdb, data_sound_snd_data_hotel_3f_b_sdb, data_sound_snd_data_hotel_fire_sdb, data_sound_snd_data_end_recovery_sdb, data_sound_snd_data_end_maria_sdb, data_sound_snd_data_end_suicide_sdb, data_sound_snd_data_end_rebirth_sdb, data_sound_snd_data_end_dog_sdb };

void SeBgmChange(void) {
    int next;
    int room;

    if (dbFlag(1) == 0) {
        if (Sh2sys.step[SH2SYS_MAIN] == 2) {
            shQzero(&snd_data_buffer, 0x5000);
            FcRead(sdb_list[0], &snd_data_buffer);
            fsSync(0, -1);
            bgm.sdb_no = 0;
        } else {
            next = playing.stage;
            if (bgm.sdb_no != next) {
                shQzero(&snd_data_buffer, 0x5000);
                FcRead(sdb_list[next], &snd_data_buffer);
                bgm.sdb_no = next;
            }
        }
        room = RoomNameJms();
        switch (playing.stage) {
            case 0x2:
            case 0x3:
            case 0x4:
                if (GET_GAME_FLAG(GAME_FLAG_39)) {
                    SeBgmCall(0);
                    return;
                }
                if (GET_GAME_FLAG(GAME_FLAG_36)) {
                    SeBgmCall(3);
                    return;
                }
                SeBgmCall(1);
                return;
            case 0x5:
                SeBgmCall(3);
                return;
            case 0x6:
                if (!GET_GAME_FLAG(GAME_FLAG_85) && (room == 0x1E)) {
                    SeBgmCall(7);
                    return;
                }
                if (GET_GAME_FLAG(GAME_FLAG_91)) {
                    SeBgmCall(9);
                    return;
                }
                SeBgmCall(4);
                return;
            case 0x7:
            case 0x8:
                if (GET_GAME_FLAG(GAME_FLAG_91)) {
                    SeBgmCall(9);
                    return;
                }
                SeBgmCall(5);
                return;
            case 0x9:
                if (GET_GAME_FLAG(GAME_FLAG_91)) {
                    SeBgmCall(9);
                    return;
                }
                SeBgmCall(6);
                return;
            case 0xA:
                if (!GET_GAME_FLAG(GAME_FLAG_109) && (room == 0x24)) {
                    SeBgmCall(8);
                    return;
                }
                SeBgmCall(0xA);
                return;
            case 0xB:
                SeBgmCall(0xA);
                return;
            case 0xC:
                SeBgmCall(0xC);
                return;
            case 0xE:
                if (GET_GAME_FLAG(GAME_FLAG_162)) {
                    SeBgmCall(0xE);
                    return;
                }
                SeBgmCall(0xB);
                return;
            case 0xF:
            case 0x10:
                SeBgmCall(0xE);
                return;
            case 0x11:
                SeBgmCall(0xF);
                return;
            case 0x12:
                SeBgmCall(0x10);
                return;
            case 0x13:
            case 0x15:
                SeBgmCall(0x10);
                return;
            case 0x14:
                SeBgmCall(0x11);
                return;
            case 0x16:
                if (room == 0x34) {
                    SeBgmCall(0x12);
                    return;
                }
                if (room == 0x30) {
                    SeBgmCall(0x13);
                    return;
                }
                SeBgmCall(0x14);
                return;
            case 0x17:
                SeBgmCall(0x17);
                return;
            case 0x18:
                SeBgmCall(0x14);
                return;
            case 0x19:
                SeBgmCall(0x15);
                return;
            case 0x1B:
                SeBgmCall(0x16);
                return;
            case 0x1D:
            case 0x1E:
                SeBgmCall(0x18);
                return;
            case 0x1F:
            case 0x20:
                SeBgmCall(0x19);
                return;
            case 0x21:
                SeBgmCall(0x1A);
                return;
            case 0x22:
            case 0x23:
                SeBgmCall(0x1B);
                return;
            case 0x24:
                if (GET_GAME_FLAG(GAME_FLAG_368) || (room == 0x89)) {
                    SeBgmCall(0x1E);
                    return;
                }
                SeBgmCall(0x1B);
                return;
            case 0x25:
                SeBgmCall(0x1F);
                return;
            case 0x26:
                SeBgmCall(0x20);
                return;
            case 0x27:
                SeBgmCall(0x23);
                return;
            case 0x28:
                if (!GET_GAME_FLAG(GAME_FLAG_472)) {
                    SeBgmCall(0x23);
                    return;
                }
                SeBgmCall(0x22);
                return;
            case 0x29:
            case 0x2A:
                SeBgmCall(0x24);
                return;
            case 0x2B:
                SeBgmCall(0x26);
                /* fallthrough */
            case 0x2C:
                if (room == 0xAC) {
                    SeBgmCall(0x27);
                    return;
                }
                SeBgmCall(0x26);
                return;
            case 0x2D:
            case 0x2E:
                SeBgmCall(0x28);
                return;
            case 0x2F:
                SeBgmCall(0x29);
                return;
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
                SeBgmCall(0x28);
                return;
            default:
                SeBgmCall(0);
                break;
        }
    }
}

void SeBgmCall(int bgm_no /* r2 */) {
    // @todo: identify values (and are they decimal?)
    static int bgm_list[43][2] = { 
        { 0x0000, 0x0000 },
        { 0x13C9, 0xC3C2 },
        { 0x13B9, 0xC365 },
        { 0x13CA, 0xC3C3 },
        { 0x13A6, 0xC352 },
        { 0x13CD, 0xC3C6 },
        { 0x13BD, 0xC3B7 },
        { 0x13A4, 0xC350 },
        { 0x13B1, 0xC35D },
        { 0x13BB, 0xC3B5 },
        { 0x13BC, 0xC3B6 },
        { 0x13CC, 0xC3C5 },
        { 0x13D4, 0xC3CD },
        { 0x13A7, 0xC353 },
        { 0x13A8, 0xC354 },
        { 0x13B5, 0xC361 },
        { 0x13CE, 0xC3C7 },
        { 0x13C5, 0xC3BF },
        { 0x13D2, 0xC3CB },
        { 0x13B3, 0xC35F },
        { 0x13BF, 0xC3B9 },
        { 0x13BA, 0xC3B4 },
        { 0x13C0, 0xC3BA },
        { 0x13B8, 0xC364 },
        { 0x13C1, 0xC3BB },
        { 0x13C4, 0xC3BE },
        { 0x13C3, 0xC3BD },
        { 0x13CB, 0xC3C4 },
        { 0x13B2, 0xC35E },
        { 0x13D6, 0xC3D0 },
        { 0x13B7, 0xC363 },
        { 0x13CF, 0xC3C8 },
        { 0x13D5, 0xC3CE },
        { 0x13B4, 0xC360 },
        { 0x13C6, 0xC3C0 },
        { 0x13C7, 0xC3CF },
        { 0x13D0, 0xC3C9 },
        { 0x13AC, 0xC358 },
        { 0x13C2, 0xC3BC },
        { 0x13D3, 0xC3CC },
        { 0x13D1, 0xC3CA },
        { 0x13C8, 0xC3C1 },
        { 0x13A5, 0xC351 }
    };
    int i; // r5
    
    if (bgm.current == bgm_list[bgm_no][1]) {
        return;
    }

    bgm.next = bgm_list[bgm_no][1];
    bgm.read = bgm_list[bgm_no][0];

    for (i = 0; i < 7; i++) {
        if (bgm.track[i].status != 0) {
            if (bgm.track[i].status == 3) {
                if (bgm.track[i].fade_out_type == 3) {
                    bgm.track[i].fade_out_type = 1;
                }
            } else {
                bgm.track[i].status = 3;
                bgm.track[i].fade_out_type = 1;
            }
        }
    }
}

void SeBgmManager(void) {
    static int bgm_read_check_1704 = 0; // @ 0x010E0480
    static int fade_prio_1702[5] = { 0, 2, 3, 1, 4 };
    static float track_fade_time_1703[5] = { 0.0f, 3.0f, 1.5f, 6.0f, 0.0f };
    float volume; // r29+0x30
    int in; // r3
    int out; // r4
    int work; // r2
    int i; // r16    
    int j; // r5

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    if ((bgm.current != bgm.next) && (bgm.next != 0)) {
        for (i = 0; i < 7; i++) 
            if (bgm.track[i].status)  break;
            
        
        
        if (i == 7) {
            shSdCall(0x3F3, 0, 0, 0);
            shSdCall(bgm.read, 0, 0, 0);
            bgm.current = bgm.next;
            bgm_read_check_1704 = 0;
        }
    } else if (bgm.read != 0) {    
        if (!(shSdStat() & 0xF)) {
            shSdCall(bgm.next, 0x7F, 0, 0);
            bgm.read = 0;
            for (i = 0; i < 7; i++) shSdTrack(i + 1, 0);            
        }
    }
    
    
    if ((bgm.current != 0) && (bgm.read == 0)) {
    
        
        
        sound_work.sound_ary = (SOUND_DATA*) snd_data_buffer;
        
        if (sh2jms.player == NULL) shUnitVector(sound_work.chara_pos);
        else {
            sound_work.chara_pos[0] = sh2jms.player->pos.x;
            sound_work.chara_pos[1] = sh2jms.player->pos.y;
            sound_work.chara_pos[2] = sh2jms.player->pos.z;
            sound_work.chara_pos[3] = 1.0f;
        }
        sound_work.half_w = 50.0f;
        sound_work.page = BgmPageSet();
        if (Sh2sys.step[2] == 4) 
            sndGetSoundAryByCharaPos(&sound_work);
        ASSERT_ON_LINE(sound_work.on_num <= 7, 1256);
        for (i = 0; i < 7; i++) {
            in = out = 0;
            
            for (j = 0; j < sound_work.near_sound_num; j++) {
                work = sound_work.near_sound_ary[j].inVol[i];
                if (fade_prio_1702[in] < fade_prio_1702[work]) in = work;
                work = sound_work.near_sound_ary[j].outVol[i];
                if (fade_prio_1702[out] < fade_prio_1702[work]) out = work;
            }
            ASSERT_ON_LINE(in == 0 || ( in != 0 && out != 0 ), 1266);
            if (in == 0) {
                if (bgm.track[i].status) 
                    bgm.track[i].status = 3;                
            } else 
                if ((bgm.track[i].status == 0) ||
                    (bgm.track[i].status == 3)) {                
                bgm.track[i].status = 1;
                bgm.track[i].fade_in_type = in;
                bgm.track[i].fade_out_type = out;
            }
        
        }
    }
    
    
    for (i = 0; i < 7; i++) {
        if (bgm.track[i].status == 1) {
            if (bgm.track[i].fade_in_type == 4) 
                bgm.track[i].volume = 1.0f;
            else bgm.track[i].volume += shGetDT() / track_fade_time_1703[bgm.track[i].fade_in_type];
            
            if (bgm.track[i].volume >= 1.0f) {
                bgm.track[i].status = 2;
                bgm.track[i].volume = 1.0f;
            }
            shSdTrack(i + 1, ftoi(127.0f * bgm.track[i].volume));
        } else if (bgm.track[i].status == 3) {
            if (bgm.track[i].fade_out_type == 4) 
                bgm.track[i].volume = 0.0f;
            else bgm.track[i].volume -= shGetDT() / track_fade_time_1703[bgm.track[i].fade_out_type];
            
            if (bgm.track[i].volume <= 0.0f) {
                bgm.track[i].status = 0;
                bgm.track[i].volume = 0.0f;
            }
            shSdTrack(i + 1, ftoi(127.0f * bgm.track[i].volume));
        }
    
    
    
    
    
    
    
    
    
    }
    
    switch (Sh2sys.step[SH2SYS_PLAYABLE_MAIN]) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            volume = 0.5f; break;
        case 14:
        default:
            switch (DramaDemoNumber()) {
                default:
                    volume = 0.7f; break;
                case 0:
                case 1:
                case 14:
                case 2:
                    volume = 1.0f; break;
            }
            break;
    }
    if (bgm.volume > volume) {
        bgm.volume = shFloatMax(bgm.volume - shGetDT() / 2.0f, volume);
        shSdCall(0x3FC, ftoi(127.0f * bgm.volume), 0, 0);
    }
    else if (bgm.volume < volume) {
        bgm.volume = shFloatMin(bgm.volume + shGetDT() / 2.0f, volume);
        shSdCall(0x3FC, ftoi(127.0f * bgm.volume), 0, 0);
    }
}

int BgmPageSet(void) {
    int ret;
    SubCharacter* scp;
    float temp_f0;
    float temp_f2;

    if ((Sh2sys.step[SH2SYS_PLAYABLE_MAIN] >= 4) && (stage != NULL) && (stage->bgm_control != NULL)) {
        ret = stage->bgm_control();
    } else {
        ret = 0;
    }
    if (ret >= 6) {
        return ret;
    }
    if (ret > 3) {
        return ret;
    }

    scp = shCharacter_Manage_GetCharacterList();
    while (scp != NULL) {
        if (IS_SCP_ENEMY(scp) &&
            ((scp->battle.status >> 0xA) & 1) &&
            !((scp->battle.status >> 1) & 1)) {
            temp_f2 = scp->pos.x - sh2jms.player->pos.x;
            temp_f2 = temp_f2 * temp_f2; // Do we have square macros?
            temp_f0 = scp->pos.z - sh2jms.player->pos.z;
            temp_f0 = temp_f0 * temp_f0;
            if (temp_f2 + temp_f0 < 3.6e7f) {
                break;
            }
        }
        scp = scp->next;
    }
    if (scp != NULL) {
        return 3;
    }

    if ((sh2jms.player != NULL) && (shBattleGetJamesHP_Rate() < 0.2f)) {
        return 2;
    }

    return ret;
}

void SeMasterVolumeChange(void) {
    if (!dbFlag(1)) {
        shSdCall(0x402, playing.bgm_volume * 8, 0, 0);
        shSdCall(0x401, playing.se_volume * 8, 0, 0);
    }
}

Change_List change_list[242] = {
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40221,
        /* .file = */ 1,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40220,
        /* .file = */ 1,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40224,
        /* .file = */ 1,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40225,
        /* .file = */ 1,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40222,
        /* .file = */ 1,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40223,
        /* .file = */ 1,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40226,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40231,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40232,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40233,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40234,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40235,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40236,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40228,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40229,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40230,
        /* .file = */ 2,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40237,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40241,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40242,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40243,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40244,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40245,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40246,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40240,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40239,
        /* .file = */ 3,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40252,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40253,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40254,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40255,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40256,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40257,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40249,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40250,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40251,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 12250,
        /* .sd3d = */ 40247,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 12251,
        /* .sd3d = */ 40248,
        /* .file = */ 4,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40005,
        /* .file = */ 5,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40006,
        /* .file = */ 5,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40003,
        /* .file = */ 5,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40004,
        /* .file = */ 5,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40002,
        /* .file = */ 5,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40001,
        /* .file = */ 5,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40012,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40011,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40015,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40016,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40013,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40014,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40010,
        /* .file = */ 6,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40023,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40024,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40021,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40022,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40020,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40019,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40018,
        /* .file = */ 7,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40039,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40040,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40041,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40042,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40043,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40034,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40037,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40038,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40035,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40036,
        /* .file = */ 8,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40045,
        /* .file = */ 9,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40047,
        /* .file = */ 9,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40046,
        /* .file = */ 9,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40025,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40027,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40026,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40028,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40029,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40030,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40031,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40032,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40033,
        /* .file = */ 10,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40078,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40082,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40083,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40084,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40085,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40086,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40087,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40079,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40080,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40081,
        /* .file = */ 11,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40097,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40101,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40102,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40103,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40104,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40105,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40106,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40098,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40099,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40100,
        /* .file = */ 12,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40117,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40121,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40122,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40123,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40124,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40125,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40126,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40118,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40119,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40120,
        /* .file = */ 13,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40143,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40147,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40148,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40149,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40150,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40151,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40152,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40144,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40145,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40146,
        /* .file = */ 14,
    },
    {
        /* .sdSe = */ 18500,
        /* .sd3d = */ 40181,
        /* .file = */ 15,
    },
    {
        /* .sdSe = */ 18512,
        /* .sd3d = */ 40182,
        /* .file = */ 15,
    },
    {
        /* .sdSe = */ 18508,
        /* .sd3d = */ 40180,
        /* .file = */ 15,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40072,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40073,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40074,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40075,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40076,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40077,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40069,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40070,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40071,
        /* .file = */ 16,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40091,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40092,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40093,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40094,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40095,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40096,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40088,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40089,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40090,
        /* .file = */ 17,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40111,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40112,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40113,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40114,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40115,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40116,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40108,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40109,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40110,
        /* .file = */ 18,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40131,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40132,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40133,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40134,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40135,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40136,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 12100,
        /* .sd3d = */ 40128,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 12103,
        /* .sd3d = */ 40129,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 12107,
        /* .sd3d = */ 40130,
        /* .file = */ 19,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40137,
        /* .file = */ 20,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40138,
        /* .file = */ 20,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40139,
        /* .file = */ 20,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40140,
        /* .file = */ 20,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40141,
        /* .file = */ 20,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40142,
        /* .file = */ 20,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40049,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40048,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40053,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40054,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40051,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40052,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40057,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40056,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40061,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40062,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40059,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40060,
        /* .file = */ 21,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40210,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40209,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40213,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40214,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40211,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40212,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40215,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40216,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40217,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40218,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40219,
        /* .file = */ 23,
    },
    {
        /* .sdSe = */ 12250,
        /* .sd3d = */ 40201,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12251,
        /* .sd3d = */ 40202,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40204,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40203,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12200,
        /* .sd3d = */ 40207,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12201,
        /* .sd3d = */ 40208,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12208,
        /* .sd3d = */ 40205,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 12209,
        /* .sd3d = */ 40206,
        /* .file = */ 24,
    },
    {
        /* .sdSe = */ 18300,
        /* .sd3d = */ 40185,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40184,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40183,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40186,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40187,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40188,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40189,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40190,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40191,
        /* .file = */ 25,
    },
    {
        /* .sdSe = */ 12009,
        /* .sd3d = */ 40194,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 12019,
        /* .sd3d = */ 40193,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 16100,
        /* .sd3d = */ 40195,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 16102,
        /* .sd3d = */ 40196,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 16104,
        /* .sd3d = */ 40197,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40198,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40199,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40200,
        /* .file = */ 26,
    },
    {
        /* .sdSe = */ 18200,
        /* .sd3d = */ 40063,
        /* .file = */ 27,
    },
    {
        /* .sdSe = */ 18300,
        /* .sd3d = */ 40178,
        /* .file = */ 28,
    },
    {
        /* .sdSe = */ 18307,
        /* .sd3d = */ 40179,
        /* .file = */ 28,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40177,
        /* .file = */ 28,
    },
    {
        /* .sdSe = */ 18300,
        /* .sd3d = */ 40160,
        /* .file = */ 29,
    },
    {
        /* .sdSe = */ 18307,
        /* .sd3d = */ 40161,
        /* .file = */ 29,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40159,
        /* .file = */ 29,
    },
    {
        /* .sdSe = */ 18300,
        /* .sd3d = */ 40167,
        /* .file = */ 30,
    },
    {
        /* .sdSe = */ 18307,
        /* .sd3d = */ 40168,
        /* .file = */ 30,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40166,
        /* .file = */ 30,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40169,
        /* .file = */ 30,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40170,
        /* .file = */ 30,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40171,
        /* .file = */ 30,
    },
    {
        /* .sdSe = */ 18300,
        /* .sd3d = */ 40174,
        /* .file = */ 31,
    },
    {
        /* .sdSe = */ 18307,
        /* .sd3d = */ 40175,
        /* .file = */ 31,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40173,
        /* .file = */ 31,
    },
    {
        /* .sdSe = */ 16113,
        /* .sd3d = */ 40156,
        /* .file = */ 32,
    },
    {
        /* .sdSe = */ 16118,
        /* .sd3d = */ 40157,
        /* .file = */ 32,
    },
    {
        /* .sdSe = */ 16119,
        /* .sd3d = */ 40158,
        /* .file = */ 32,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40155,
        /* .file = */ 32,
    },
    {
        /* .sdSe = */ 12250,
        /* .sd3d = */ 40153,
        /* .file = */ 32,
    },
    {
        /* .sdSe = */ 12251,
        /* .sd3d = */ 40154,
        /* .file = */ 32,
    },
    {
        /* .sdSe = */ 18300,
        /* .sd3d = */ 40163,
        /* .file = */ 33,
    },
    {
        /* .sdSe = */ 18307,
        /* .sd3d = */ 40164,
        /* .file = */ 33,
    },
    {
        /* .sdSe = */ 12500,
        /* .sd3d = */ 40162,
        /* .file = */ 33,
    },
    {
        /* .sdSe = */ 18850,
        /* .sd3d = */ 40066,
        /* .file = */ 34,
    },
    {
        /* .sdSe = */ 18851,
        /* .sd3d = */ 40067,
        /* .file = */ 34,
    },
    {
        /* .sdSe = */ 18858,
        /* .sd3d = */ 40064,
        /* .file = */ 34,
    },
    {
        /* .sdSe = */ 18859,
        /* .sd3d = */ 40065,
        /* .file = */ 34,
    },
    {
        /* .sdSe = */ 18862,
        /* .sd3d = */ 40068,
        /* .file = */ 34,
    },
    {
        /* .sdSe = */ 0,
        /* .sd3d = */ 0,
        /* .file = */ 0,
    }
};

static int SeChange2Dto3D(int se /* r2 */) {
    int i; // r5

    if (se >= 0x9C40) {
        return se;
    }
    for (i = 0; change_list[i].sd_se; i++) {
        if (se_3d_load_data == change_list[i].file && se == change_list[i].sd_se) {
            return change_list[i].sd_3d;
        }
    }
    return 0;
}

static int SeChange3Dto2D(int se /* r2 */) {
    int i; // r3
    
    if (se < 0x9C40) {
        return se;
    }
    for (i = 0; change_list[i].sd_3d; i++) {
        if (change_list[i].sd_3d == se) {
            return change_list[i].sd_se;
        }        
    }
    return 0;
}
