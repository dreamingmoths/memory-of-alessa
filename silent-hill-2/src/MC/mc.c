#include "common.h"
#include "MC/mc.h"

#define MC_STATUS_01 1
#define MC_STATUS_11 11

extern s_char sc1;
extern s_char sc2;

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @837);

#line 201
/* static */ int cmpstr(s_char* str1, s_char* str2) {
    while (*str1 == *str2) {
        if (*str1 == '\0') return true;
        str1++;
        str2++;
    }
    return false;
}

static void print_sc1(char st) {
    if (sc1 == st) return;
    sc1 = st;
    switch (st) {
        case 0:
            printf("mc start check: now checking\n");
            break;
        case 1:
            printf("mc start check: OK\n");
            break;
        case 2:
            printf("mc start check: autoload slot 1\n");
            break;
        case 3:
            printf("mc start check: autoload slot 2\n");
            break;
        case 4:
            printf("mc start check: autoload end\n");
            break;
        case -1:
            printf("mc start check: no card\n");
            break;
        case -2:
            printf("mc start check: empty block\n");
            break;
        case -3:
            printf("mc start check: autoload failure\n");
            break;
    }
}

#line 247
/* static */ void print_sc2(s_char st /* r2 */) {
    if (sc2 == st) return;
    sc2 = st;
    switch (st) {
        case 0:
            printf("mc start check2: now checking or no data\n");
            break;
        case 1:
            printf("mc start check2: load & continue\n");
            break;
        case 2:
            printf("mc start check2: continue only\n");
            break;
        case 3:
            printf("mc start check2: load only\n");
            break;
    }
}

#line 270
/* static */ void mcNextJob(void) {
    mcw->job = 0;
    mcw->job_num = (mcw->job_num + 1) % 16;
}

#line 279
/* static */ void mcBreakJob(void) {
    printf("break %d:%d result:%d\n", mcw->job, mcw->job_step, mcw->result);
    mcNextJob();
    mcw->job_num = mcw->job_end;
    mc.status |= 1 << MC_STATUS_01;
}

#line 291
/* static */ void mcBreakJob2(void) {
    printf("break %d:%d result:%d\n", mcw->job, mcw->job_step, mcw->result);
    mcNextJob();
    mcw->job_num = mcw->job_end;
    mc.status |= 1 << MC_STATUS_11;
}

#line 303
static void mcPortError(void) {
    int i; // r5

    printf("port error:%d %d:%d result:%d\n", mcw->job_port, mcw->job, mcw->job_step, mcw->result);

    mcNextJob();

    for (i = 0; i < 5; i++) {
        mcw->dirstatus[mcw->job_port][i] = 0;
        mcw->dirid[mcw->job_port][i]     = -1;
    }

    mcSetGetInfo(mcw->job_port);
    if (mcw->menu_port == mcw->job_port) mc.status |= (1 << MC_STATUS_01) | (1 << MC_STATUS_11);
}

#line 321
static void mcDirBroken(void) {
    int fn; // r2

    printf("dir broken %d:%d\n", mcw->job, mcw->job_step);
    
    mcw->job_step = -1;
    
    mcw->dirstatus[mcw->port][mcw->dirnum] = 6;
    mcw->dirid[mcw->port][mcw->dirnum]     = -1;
    
    fn = mcw->files;
    mcw->files = fn + 1;
    mcw->tmpinfo[fn].savecount = 1;
    mcw->tmpinfo[fn].dirid = mcw->dirnum;
    mcw->tmpinfo[fn].status = 0x80;

    mcSetGetInfo2(mcw->port);
}

#line 336
static void mcPortAbnormal(char port /* r2 */) {
    int i; // r8

    for (i = 0; i < 5; i++) {
        mcw->dirstatus[port][i] = 8;
        mcw->dirid[port][i]     = -1;
    }

    mcw->filemax[port] = 0;
    mcw->d_ent[port]   = 0;

    if (mcw->menu_port == port) mc.status |= (1 << MC_STATUS_01) | (1 << MC_STATUS_11);
}

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcInit);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @886_0x003994F0);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @887_0x00399520);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @888_0x00399550);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @889_0x00399570);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @902);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @924);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @934_0x003995D0);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @1077);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcExec);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetJob);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcAutoInfo);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetGetInfo);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetGetInfo2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCheckAll);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcStepInit);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcStartCheck);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcStartCheck2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCheckDir);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @1094_0x00399640);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @1536);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobCheckDir);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSearchDir);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSearchDir);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSearchDir2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSearchDir2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcGetDt);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcFormat);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCheckStatus);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCheckCanSave);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobNewDir);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcOpenWO);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcOpenRO);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcOpenRW);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSaveIconSys);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSaveIconSys);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSaveIcon);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSaveIcon);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSaveData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSaveData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcLoadData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobLoadData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcLoadData2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcDeleteData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobDeleteData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobDeleteDir);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSaveSystemData);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2264);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2265);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobSaveExtraData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobLoadExtraData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetDirName);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJoinDirName);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetFileName);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetExtraDirName);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetExtraFileName);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcMakeSaveData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcExtSaveData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcEncodeStart);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcDecodeStart);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcRot);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCodecAll);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCodec);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcMakeDirData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcMakeDirData2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcMakeDirData3);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcMakeDirDataSub);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcExtDirData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcLoadIconData);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCheckEndLoadIconData);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2429);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2494);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2544);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2654);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2655);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2656);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2657);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2658);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2816);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2817);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2818);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2819);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2820);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2821);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @2822);
