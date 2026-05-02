#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"
#include "DBG/dbflag.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"
#include "debug.h"

static int SeChange2Dto3D(int se /* r2 */);
static int SeChange3Dto2D(int se /* r2 */);

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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeSoundEffectLoad);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeSoundEffect3dLoad);

void SeSoundManager(void) {
    Se2dManager();
    Se3dManager();
    SeBgmManager();
}

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", Se2dManager);

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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeBgmChange);

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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", BgmPageSet);

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
