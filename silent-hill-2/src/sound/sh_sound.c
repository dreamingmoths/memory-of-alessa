#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"
#include "DBG/dbflag.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"
#include "debug.h"
#include "SH2_common/sh2sys.h"
#include "Chacter/character.h"
#include "Event/event.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/sh_character_battle.h"
#include "FilesList/fileslist_bg.h"
#include "SH2_common/sh2dt.h"
#include "Multi_thr/filesys/fcread.h"
#include "Chacter/chara_list.h"

#pragma fast_fptosi on

static int SeChange2Dto3D(int se /* r2 */);
static int SeChange3Dto2D(int se /* r2 */);

extern /* static */ int bgm_list[43][2] /* = {
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
} */;

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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallPos);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallPosChange);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallPosDirection);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallPosDistance);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallPosDistanceF);

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

INCLUDE_RODATA("asm/nonmatchings/sound/sh_sound", @1052_0x003901F0);

INCLUDE_RODATA("asm/nonmatchings/sound/sh_sound", @1053_0x00390210);

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

extern fsFileIndex* se_file_list_1329[35]; // @todo: Move this inside as a local variable https://github.com/dreamingmoths/memory-of-alessa/pull/212#discussion_r3482739416
void SeSoundEffect3dLoad(int data) {
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
                switch (Sh2sys.step[2]) {
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
                    se_2d_manage_data[i].base = float_max(se_2d_manage_data[i].base - shGetDT(), volume);
                } else if (se_2d_manage_data[i].base < volume) {
                    se_2d_manage_data[i].base = float_min(se_2d_manage_data[i].base + shGetDT(), volume);
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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", Se3dManager);

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
    vec_copy(se_3d_channel_data[i].pos, pos);
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

extern fsFileIndex* sdb_list[53];
extern u_char snd_data_buffer[20480];
void SeBgmChange(void) {
    int next;
    int room;

    if (dbFlag(1) == 0) {
        if (Sh2sys.step[0] == 2) {
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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeBgmManager);

int BgmPageSet(void) {
    int ret;
    SubCharacter* scp;
    float temp_f0;
    float temp_f2;

    if ((Sh2sys.step[2] >= 4) && (stage != NULL) && (stage->bgm_control != NULL)) {
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


INCLUDE_RODATA("asm/nonmatchings/sound/sh_sound", @1849);

INCLUDE_RODATA("asm/nonmatchings/sound/sh_sound", @1850);

INCLUDE_RODATA("asm/nonmatchings/sound/sh_sound", @1851);

INCLUDE_RODATA("asm/nonmatchings/sound/sh_sound", @1852_0x003904E0);
