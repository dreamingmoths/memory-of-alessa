#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "MC/mc.h"
#include "MC/mc_menu.h"
#include "Font/fj_man.h"
#include "Effect/screen_effect.h"


int mcSaveMenu(void) {
    int i;
    s_char port = mcw->menu_port;
    s_char n;

    if ((mc.status & (1 << MC_STATUS_FLAG_2)) == 0 || !Sh2sys.step[3]) {
        mcInit();
        mc.status |= (1 << MC_STATUS_FLAG_2);
    }

    switch (mcw->menu_step) {
        case 0:
            mcw->saveload = 0;
            mcLoadMenuData();
            SetSaveData();
            mcMakeSaveData();
            mcCheckAll();
            mc.status &= 0xfeff;
            MCW_SET_MENU_STEP(1);
            sh2sys_step_3();
            break;

        case 1:
            if ((mc.status & (1 << MC_STATUS_FLAG_5)) == 0) {
                if (fsSync(1, mcw->fid[0]) >= 0) {
                    mc.status |= (1 << MC_STATUS_FLAG_5);
                }
            } else {
                if (fsSync(1, mcw->fid[1]) >= 0) {
                    mc.status |= (1 << MC_STATUS_FLAG_6);
                    ScreenEffectFadeStart(12, 1.5);
                    mc.status |= (1 << MC_STATUS_FLAG_3);
                    MCW_SET_MENU_STEP(2);
                    mcLoadIconData();
                }
            }
            break;

        case 2:
            if (((mcw->dirstatus[port][0] == 8) || (mcw->dirstatus[port][0] == 0)) &&
                ((mcw->portstatus[port] == 2 || (mcw->portstatus[port] == 3)))) {
                mcw->dirstatus[port][0] = 1;
                mcCheckDir(port);
            }
            mcw->menu_info = -2;
            for (i = 0; i < 5; i = i + 1) {
                if (mcw->dirstatus[port][i] == 1) {
                    mcw->menu_info = 27;
                    break;

                }
            }
            if ((mcw->menu_info == -2)) {
                switch (mcSelectData()) {
                    case 1:
                        if (mcCheckEndLoadIconData()) {
                            n = mcw->portstatus[port];
                            if (n == 4) {
                                MCW_SET_MENU_STEP(3);
                                mcSoundDecide();
                            } else if ((n != 2) && (n != 3)) {
                                mcSoundError();
                            } else {
                                n = mcw->menu_num[port];
                                if (n < mcw->filemax[port]) {
                                    if (((mcw->fileinfo[mcw->menu_port][n].status & 0x80)) ||
                                        (mcw->dirstatus[port][mcw->fileinfo[mcw->menu_port][n].dirid] == 6)) {
                                        mcSoundError();
                                    } else {
                                        MCW_SET_MENU_STEP(5);
                                        mcSoundDecide();
                                    }
                                } else {
                                    n = mcCheckCanSave(port);
                                    if (n < 2) {
                                        MCW_SET_MENU_STEP(4);
                                        mcSoundDecide();
                                    } else {
                                        mcSoundError();
                                    }
                                }
                            }
                        }
                        break;

                    case 2:
                        mc.status |= 1 << MC_STATUS_FLAG_8;
                        MCW_SET_MENU_STEP(-1);
                        break;

                    case 3:
                        if (mcw->menu_num[port] < mcw->filemax[port]) {
                            MCW_SET_MENU_STEP(9);
                            mcSoundDecide();
                        } else {
                            mcSoundError();
                        }
                    case 4:
                    case 5:
                    case 6:
                        break;

                }
            }
            break;

        case 3:
            if (mcw->menu_sstep == 0) {
                mc.status |= 1 << MC_STATUS_FLAG_8;
                mcw->menu_yesno = 2;
                mcw->menu_info = 0x1e;
                MCW_SET_MENU_SSTEP();
            } else if (mcw->menu_sstep == 2) {
                if ((mc.status & 2)) {
                    MCW_SET_MENU_STEP(8);
                } else {
                    if ((mcw->portstatus[port] == 2) || (port == 2)) {
                        for (i = 0; i < 5; i++) {
                            mcw->dirstatus[port][i] = 2;
                        }
                        MCW_SET_MENU_STEP(4);
                    } else if (1 < mcw->portstatus[port]) {
                        MCW_SET_MENU_STEP(8);
                    }
                }
                break;

            }
            
            if (mcw->portstatus[port] != 4) {
                MCW_SET_MENU_STEP(2);
                mcw->menu_yesno = 0;
            } else {
                switch (mcTellYesNo()) {
                    case 1:
                        Sh2sys.soft_reset = 0;
                        mcFormat(port);
                        mcw->menu_info = 37;
                        mcw->menu_sstep = 2;
                        break;

                    case 2:
                        MCW_SET_MENU_STEP(2);
                }
            }
            break;

        case 4:
            if (mcw->menu_sstep == 0) {
                int p;
                int cond;
                Sh2sys.soft_reset = 0;

                if ((mcw->menu_num[port] < mcw->filemax[port])) {
                    mcSaveData(port, mcw->fileinfo[mcw->menu_port][mcw->menu_num[port]].dirid,
                               mcw->fileinfo[mcw->menu_port][mcw->menu_num[port]].fileid);
                } else {
                    for (n = 0; n < MC_MAXFILES; n++) {
                        i = 0;
                        while (i < mcw->filemax[port]) {
                            if ((mcw->fileinfo[mcw->menu_port][i].dirid == mcw->menu_newdir) &&
                                (mcw->fileinfo[mcw->menu_port][i].fileid == n)) {
                                i = -1;
                                break;

                            }
                            i++;
                        }
                        if (i != -1) {
                            mcSaveData(port, mcw->menu_newdir, n);
                            break;

                        }
                    }
                    fjAssert(n < MC_MAXFILES, __FILE__, 0x1cb);
                }

                mc.status |= 1 << MC_STATUS_FLAG_8;
                mcw->menu_info = 39;
                mcw->menu_bk = 1;
                MCW_SET_MENU_SSTEP();
            }
            if ((mc.status & 2)) {
                mcw->menu_step = 7;
                mcw->menu_sstep = 0;
            } else {
                if ((mc.status & 1)) {
                    MCW_SET_MENU_STEP(6);
                }
            }
            break;

        case 5:
            if (mcCheckStatus(port)) {

                MCW_SET_MENU_STEP(2);
                mcw->menu_yesno = 0;
            } else {
                if (mcw->menu_sstep == 0) {
                    mcw->menu_yesno = 2;
                    mcw->menu_info = 46;
                    MCW_SET_MENU_SSTEP();
                }
                switch (mcTellYesNo()) {
                    case 1:
                        MCW_SET_MENU_STEP(4);
                        break;

                    case 2:
                        MCW_SET_MENU_STEP(2);
                        break;

                }
            }
            break;

        case 6:
            if (mcCheckStatus(port)) {

                MCW_SET_MENU_STEP(2);
            } else {
                if (mcw->menu_sstep == 0) {
                    Sh2sys.soft_reset = 1;
                    mcw->menu_info = 40;
                    mcw->menu_timer = 90;
                    MCW_SET_MENU_SSTEP();
                }
                if (mcCheckTimer()) {
                    for (i = 0; i < 5; i++) {
                        if (mcw->dirstatus[port][i] == 1)
                            break;

                    }
                    if (i == 5) {
                        mcw->saveload = 1;
                        mc.status &= 0xfeff;
                        MCW_SET_MENU_STEP(2);
                    }
                }
            }
            break;

        case 7:
            if (mcw->menu_sstep == 0) {
                mcSoundError();
                Sh2sys.soft_reset = 1;
                mcw->menu_info = 41;
                mcw->menu_timer = 90;
                MCW_SET_MENU_SSTEP();
            }
            if (mcCheckTimer()) {
                mc.status &= 0xfeff;
                MCW_SET_MENU_STEP(2);
            }
            break;

        case 8:
            if (mcw->menu_sstep == 0) {
                mcSoundError();
                Sh2sys.soft_reset = 1;
                mcw->menu_info = 38;
                mcw->menu_timer = 90;
                MCW_SET_MENU_SSTEP();
            }
            if (mcCheckTimer()) {
                mc.status &= 0xfeff;
                MCW_SET_MENU_STEP(2);
            }
            break;

        case 9:
            if (mcCheckStatus(port)) {

                MCW_SET_MENU_STEP(2);
                mcw->menu_yesno = 0;
            } else {
                if (mcw->menu_sstep == 0) {
                    mcw->menu_yesno = 2;
                    mcw->menu_info = 66;
                    MCW_SET_MENU_SSTEP();
                }
                switch (mcTellYesNo()) {
                    case 1:
                        mcw->menu_step = 10;
                        mcw->menu_sstep = 0;
                        break;

                    case 2:
                        MCW_SET_MENU_STEP(2);
                        break;

                }
            }
            break;

        case 10:
            if (mcw->menu_sstep == 0) {
                Sh2sys.soft_reset = 0;
                mcDeleteData(port, mcw->fileinfo[mcw->menu_port][mcw->menu_num[port]].dirid,
                             mcw->fileinfo[mcw->menu_port][mcw->menu_num[port]].fileid);
                mc.status |= 1 << MC_STATUS_FLAG_8;
                mcw->menu_info = 67;
                MCW_SET_MENU_SSTEP();
            }
            if ((mc.status & 2)) {

                mcw->menu_step = 12;
                mcw->menu_sstep = 0;
            } else {
                if ((mc.status & 1)) {
                    if (4 <= --mcw->filemax[port]) {
                        if (mcw->menu_base[port] >= (mcw->filemax[port] - 4)) {
                            mcw->menu_base[port]--;
                        }
                    }
                    mcw->menu_step = 11;
                    mcw->menu_sstep = 0;
                }
            }
            break;

        case 11:
            if (mcCheckStatus(port)) {
                MCW_SET_MENU_STEP(2);
            } else {
                if (mcw->menu_sstep == 0) {
                    Sh2sys.soft_reset = 1;
                    mcw->menu_info = 68;
                    mcw->menu_timer = 90;
                    MCW_SET_MENU_SSTEP();
                }
                if (mcCheckTimer()) {
                    mc.status &= 0xfeff;
                    mcw->saveload = 1;
                    MCW_SET_MENU_STEP(2);
                }
            }
            break;

        case 12:
            if (mcw->menu_sstep == 0) {
                mcSoundError();
                Sh2sys.soft_reset = 1;
                mcw->menu_info = 69;
                mcw->menu_timer = 90;
                MCW_SET_MENU_SSTEP();
            }
            if (mcCheckTimer()) {
                mc.status &= 0xfeff;
                MCW_SET_MENU_STEP(2);
            }
            break;

        case 13:
            if (mcw->menu_sstep == 0) {
                mcw->menu_info = 47;
                MCW_SET_MENU_SSTEP();
            }
            switch (mcTellYesNo()) {
                case 1:
                    mc.status |= 1 << MC_STATUS_FLAG_8;
                    mcw->menu_info = -1;
                    MCW_SET_MENU_STEP(-1);
                    break;

                case 2:
                    do {
                        MCW_SET_MENU_STEP(2);

                    } while (0);
                    break;

            }
            break;

    }
    mcExec();
    if (mcMenuControl()) {
        fontClear();
        sh2sys_set_2(1);
        sh2sys_set_3(6);
        mcStepInit();
        return 1;
    }
    mcDrawMenu();
    return 0;
}

const char __pad_0x003999c8[] = "\0\0\0\0"; /* @hack temporary fix to align rodata */

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcLoadMenu);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcAfterLoadMenu);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcCheckTimer);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcMenuControl);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcTellYesNo);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSelectData);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcGetBlinkAlpha);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcPutMes);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcPutMes2);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcPutBigFont);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawMenu);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawFrame);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawSlot);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawPlace);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawAddInfo);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawWarning);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawStatus);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawBG);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDrawBGWord);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcDmaKick);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcLoadMenuData);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSoundCursor);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSoundDecide);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSoundSelect);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSoundCancel);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSoundError);

INCLUDE_ASM("asm/nonmatchings/MC/mc_menu", mcSoundStart);

INCLUDE_RODATA("asm/nonmatchings/MC/mc_menu", @1933);

INCLUDE_RODATA("asm/nonmatchings/MC/mc_menu", @2000);

INCLUDE_RODATA("asm/nonmatchings/MC/mc_menu", @2001);

INCLUDE_RODATA("asm/nonmatchings/MC/mc_menu", @2002);

INCLUDE_RODATA("asm/nonmatchings/MC/mc_menu", @2003);
