#include "sound/sh_sound.h"
#include "DBG/dbflag.h"

static int SeChange2Dto3D(int se /* r2 */);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeWait);

void SeForceWait(void) {
    SeWait(0x3C);
}

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallInit);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCallReset);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeCall);

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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", Se2dManageDataVolumeChange);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", Se2dManageDataTimer);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", Se3dManager);

int Se3dControl(int sd_no /* r17 */, float volume /* r20 */, float* pos /* r16 */) {
    int i; // r4

    if (dbFlag(1)) {
        return 0x10;
    }
    if (sd_no == 0) {
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

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeStop);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeBgmChange);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeBgmCall);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeBgmManager);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", BgmPageSet);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeMasterVolumeChange);

static int SeChange2Dto3D(int se /* r2 */) {
    int i; // r5

    if (se >= 0x9C40) {
        return se;
    }
    for (i = 0; change_list[i].sd_se != 0; i++) {
        if (se_3d_load_data == change_list[i].file && se == change_list[i].sd_se) {
            return change_list[i].sd_3d;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sound/sh_sound", SeChange3Dto2D);
