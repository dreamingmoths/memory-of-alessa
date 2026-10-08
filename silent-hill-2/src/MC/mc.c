#include "sh2_common.h"
#include "SH2_common/mem_share.h"
#include "MC/mc.h"

static void mcCodec(void);
static void mcAutoInfo(void);
static void mcJobSaveSystemData(void);
static void mcJobSaveIconSys(void);
static void mcJobLoadData(void);
static void mcJobCheckDir(void);
static void mcJobSearchDir2(void);
static void mcJobDeleteData(void);
static void mcJobNewDir(void);
static void mcJobLoadExtraData(void);
static void mcJobSaveData(void);
static void mcJobSearchDir(void);
static void mcJobSaveExtraData(void);
static void mcJobSaveIcon(void);
static void mcJobDeleteDir(void);
static void mcSearchDir(s_char port);
static void mcLoadData2(s_char port, short n);
static void mcSearchDir2(s_char port);
static u_int mcRot(u_int n, int s);
static void mcMakeDirDataSub(void);
static int cmpstr(s_char* str1, s_char* str2);
static void print_sc1(s_char st);
static void print_sc2(s_char st);
static void mcNextJob(void);
static void mcBreakJob(void);
static void mcBreakJob2(void);
static void mcPortError(); /* @note: `void` doesn't match with mcExec? */
static void mcDirBroken(void);
static void mcPortAbnormal(s_char port);
static void mcOpenWO(s_char* name);
static void mcOpenRO(s_char* name);
static void mcOpenRW(s_char* name);
static void mcSetDirName(s_char dn);
static void mcJoinDirName(s_char dn);
static void mcSetFileName(s_char dn, s_char fn);
static void mcSetExtraDirName(s_char* name);
static void mcSetExtraFileName(s_char* name);
static int mcExtSaveData(void);
static void mcEncodeStart(void);

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

static void print_sc1(s_char st) {
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
static void mcPortError() {
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
static void mcPortAbnormal(s_char port /* r2 */) {
    int i; // r8

    for (i = 0; i < 5; i++) {
        mcw->dirstatus[port][i] = 8;
        mcw->dirid[port][i]     = -1;
    }

    mcw->filemax[port] = 0;
    mcw->d_ent[port]   = 0;

    if (mcw->menu_port == port) mc.status |= (1 << MC_STATUS_01) | (1 << MC_STATUS_11);
}

MC_WORK* mcInit(void) {
    mc.status = MC_STATUS_00;

    mcw = (MC_WORK2* ) (MemShare_gp_data_buf + MCW_HEAP_ADDRESS);

    shQzero(mcw, sizeof(MC_WORK2));
    
    return &mc;
}

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @886_0x003994F0);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @887_0x00399520);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @888_0x00399550);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @889_0x00399570);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @902);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @924);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @934_0x003995D0);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @1077);


#line 383
void mcExec(void) {
    s_char port; // r2
    short jd; // r2
    s_char n; // r16
    s_char tmp; // @note not in dwarf
    if (mcw->cd.mode != 0)





        
        mcCodec();

    
    
    
    
    if (mcw->portstatus[0] == 0)
        mcSetGetInfo(0);

    if (mcw->portstatus[1] == 0)
        mcSetGetInfo(1);


    if (mcw->job == 0) {
        mcw->job_step = 0;
        if (mcw->job_num != mcw->job_end) {
            mcw->job = mcw->jobs[mcw->job_num].job;
            mcw->job_data = (jd = (s_char) mcw->jobs[mcw->job_num].data);
            mcw->job_port = (port = mcw->jobs[mcw->job_num].port);
            switch (mcw->job) {
                case MC_JOB_01:
                    mcw->type_old = mcw->type[port] | (mcw->format[port] << 4);
                    mcw->retry = 0;
                    sceMcGetInfo(port, 0, &mcw->type[port], NULL, &mcw->format[port]);
                    
                    mcw->job_step = 1;
                    break;
                case MC_JOB_CHECK:
                    mcw->type_old = mcw->type[port] | (mcw->format[port] << 4);
                    mcw->retry = 0;
                    sceMcGetInfo(port, 0, &mcw->type[port], &mcw->free[port], &mcw->format[port]);
                    
                    mcw->job_step = 1;
                    break;
                case MC_JOB_END:
                    sceMcGetInfo(port, 0, NULL, NULL, NULL);
                    mc.status &= ~(1 << MC_STATUS_01);
                    mcw->job_step = 1;
                    break;
                
                
                
                
                
                
                case 0:
                    mcNextJob();
                    return;
            }
        }
    }
    
    if (mcw->job == 0) {
        if (mc.status & (1 << MC_STATUS_03)) mcw->info_count++;
        if (mcw->info_count >= 5) {
            mcAutoInfo();
        }
        return;
    }
    
    if (sceMcSync(1, NULL, &mcw->result)) {
        port = mcw->job_port;


        
        
        switch (mcw->job) {
            case MC_JOB_01:
                if (mcw->result != 0) {
                    mcSetGetInfo(port);
                    mcNextJob();
                    return;
                }
            case MC_JOB_CHECK:
                if (mcw->job_step == 2) {
                    if (mcw->result < 0) {
                        mcSetGetInfo(port);
                        mcNextJob();
                        return;
                    }
                    if (mcw->result) {
                        mcw->d_ent[port] |= 1;
                    } else {
                        mcw->d_ent[port] &= ~1;
                    }
                    if (mcw->free[port] < (((mcw->d_ent[port] & 1) ? 0 : 1)) + 93) {
                        tmp = 3;
                    } else {
                        tmp = 2;
                    }
                    mcw->portstatus[port] = tmp;
                    mcNextJob();
                    return;
                }
                mcw->info_count = 0;
                mcw->info[port] = mcw->result;
                if (((mcw->result < 0) || (mcw->type_old != (mcw->type[port] | (mcw->format[port] << 4))) || (mcw->format[port] == 0)) && ++mcw->retry < MC_MAX_RETRIES) {
                    
                    mcw->type_old = mcw->type[port] | (mcw->format[port] << 4);
                    if (mcw->job == 1) {
                        sceMcGetInfo(port, 0, &mcw->type[port], NULL, &mcw->format[port]);
                        
                        return;
                    } else sceMcGetInfo(port, 0, &mcw->type[port], &mcw->free[port], &mcw->format[port]);
                    
                    
                    return;
                }
                n = 0;
                switch (mcw->type[port]) {
                    case 1:
                        mcPortAbnormal(port);
                        n = 6;
                        break;
                    case 3:
                        mcPortAbnormal(port);
                        n = 7;
                        break;
                    case 0:
                        mcPortAbnormal(port);
                        n = 5;
                        break;
                    case 2:
                        if (mcw->format[port] == 0) {
                            mcPortAbnormal(port);
                            n = 4;
                        } else if (mcw->job == 2) {
                            n = mcw->portstatus[port];
                            sceMcGetEntSpace(port, 0, ".");
                            mcw->job_step = 2;
                        } else if (mcw->free[port] < ((mcw->d_ent[port] & 1) ? 0 : 1) + 93) {
                            n = 3;
                        } else {
                            n = 2;}
                        break;
                }
                
                mcw->portstatus[port] = n;
                if (mcw->job_step != 2) {
                    mcNextJob();
                
                    return;
                }
                break;
        
            
            
            case MC_JOB_CHECK_DIRECTORY:
                mcJobCheckDir();
                break;
            case MC_JOB_SEARCH_DIRECTORY:
                mcJobSearchDir();
                break;
            case MC_JOB_SEARCH_DIRECTORY2:
                mcJobSearchDir2();
                break;
            case MC_JOB_NEW_DIRECTORY:
                mcJobNewDir();
                break;
            case MC_JOB_SAVE_ICON_SYS:
                mcJobSaveIconSys();
                break;
            case MC_JOB_SAVE_ICON:
                mcJobSaveIcon();
                break;
            case MC_JOB_SAVE_DATA:
                mcJobSaveData();
                break;
            case MC_JOB_LOAD_DATA:
                mcJobLoadData();
                break;
            case MC_JOB_SAVE_SYSTEM_DATA:
                mcJobSaveSystemData();
                break;
            case MC_JOB_SAVE_EXTRA_DATA:
                mcJobSaveExtraData();
                break;
            case MC_JOB_LOAD_EXTRA_DATA:
                mcJobLoadExtraData();
                break;
            case MC_JOB_DELETE_DATA:
                mcJobDeleteData();
                break;
            case MC_JOB_DELETE_DIRECTORY:
                mcJobDeleteDir();
                break;
            case MC_JOB_END:
                if (mcw->result < 0 || (mc.status & (1 << MC_STATUS_01))) {
                    mcPortError(port);
                } else {
                  
                    switch (mcw->job_step++) {
                        case 1:
                            sceMcFormat(port, 0);
                            break;
                        case 2:
                            mcSetGetInfo(port);
                            mcNextJob();
                            break;
                    }
                }
                break;
    
            default:               
                mcNextJob();
                break;
        }
    }
}

#line 630
void mcSetJob(s_char job, s_char port, short data) {
    if ((mcw->job_end + 1) % 16 == mcw->job_num) {
        printf("mcSetJob: buffer over!\n");
        return;
    }
    mcw->jobs[mcw->job_end].job = job;
    mcw->jobs[mcw->job_end].port = port;
    mcw->jobs[mcw->job_end].data = data;
    mcw->job_end = (mcw->job_end + 1) % 16;
}

#line 656
static void mcAutoInfo(void) {
    int num; // r6
    int job; // r2
    int cp[2]; // r29+0x28

    mcw->info_count = 0;
    cp[0] = cp[1] = 0;
    num = mcw->job_num;

    while (num != mcw->job_end) {
        if ((mcw->jobs[num].job - 1) < 2u) {
            cp[mcw->jobs[num].port] = 1;
        }

        num = (num + 1) % 16;
    }
    if (cp[0] == 0) {
        mcSetJob(1, 0, 0);
    }
    if (cp[1] == 0) {
        mcSetJob(1, 1, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetGetInfo);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcSetGetInfo2);

void mcCheckAll(void) {
    int port; // r5
    int i; // r6

    mcw->job_end = 0;
    mcw->job_num = 0;
    mcw->job = 0;

    for (port = 0; port < 2; port++) {
        mcw->portstatus[0] = 1;
        for (i = 0; i < 5; i++) {
            mcw->dirstatus[port][i] = 1;
        }
    }
    
    mcw->portstatus[2] = 0;
    
    mcSetGetInfo(0);
    mcSetGetInfo(1);
    mcCheckDir(0);
    mcCheckDir(1);
}

void mcStepInit(void) {
    mc.status &= ~(1 << MC_STATUS_02);
}

#line 749
int mcStartCheck(void) {
    int i, n; // r16, r5
    s_char p1, p2; // r2, r5
    mcExec();
    if (!(mc.status & (1 << MC_STATUS_02))) {
        mcInit();
        mc.status |= (1 << MC_STATUS_02);
    }
    switch (mcw->menu_step) {
        case 0:
            for (i = 0; i < 2; i++) {
                mcSetGetInfo(i);
                mcw->portstatus[i] = 1;
            }
            mcw->autoload = -1;
            mcw->menu_step++;
            break;
        case 1:
            p1 = mcw->portstatus[0];
            p2 = mcw->portstatus[1];
            if (p1 >= 5) {
                mcw->menu_info |= 1;
                if (p2 >= 5) {
                    
                    mcw->tmp_status[0] = mcw->portstatus[0];
                    mcw->tmp_status[1] = mcw->portstatus[1];
                    mc.status |= 8;
                    mcw->menu_step = 4;
                    
                    print_sc1(-1);
                    
                    return -1;
                }
            } else if (p2 >= 5) {
                mcw->menu_info |= 2;
            }
            if (p1 == 4) {
            
                mcw->menu_info |= 5;
            }
            if (p2 == 4) {
                
                mcw->menu_info |= 10;
            }
            if ((mcw->menu_info & 3) == 3) {
                if (mcw->menu_info & 0xC) {
                    mcw->menu_step = 0;
             
                    print_sc1(1);
                    
                    return 1;
                }
                mcw->tmp_status[0] = mcw->portstatus[0];
                mcw->tmp_status[1] = mcw->portstatus[1];
                mc.status |= (1 << MC_STATUS_03);
                mcw->menu_step = 4;
                
                print_sc1(-2);
                
                return -2;
            }
            
            if (((p1 == 2) || (p1 == 3)) && !(mcw->menu_info & 1)) {
            
                mcSearchDir(0);
                mcw->menu_step = 2;
            }
            if (((p2 == 2) || (p2 == 3)) && !(mcw->menu_info & 2)) {
                
                mcSearchDir(1);
                mcw->menu_step = 2;
            }
            break;
        case 2:
            if (mcw->dirnum < 5) break;
            if (mcw->menu_num[0] != -1) {
                
                mcw->autoload = mcw->menu_num[0] + mcw->port * 75; // @todo what is the 75 is here?
                mcLoadData2(mcw->port, mcw->menu_num[0]);
                mcw->menu_step = 3;
                print_sc1(0);
                return 0;
            }
            n = 0;
            for (i = 0; i < 5; i++) {
                s_char stat = mcw->dirstatus[mcw->port][i]; // @note: not in dwarf
                if (stat >= 6) n++;
            }
            if (n < 5) {
                mcw->menu_info |= 4 << mcw->port;
            }
            mcw->menu_info |= 1 << mcw->port;
            mcw->menu_step = 1;
            break;
        case 3:
            if (mc.status & 2) {
                mcw->tmp_status[0] = mcw->portstatus[0];
                mcw->tmp_status[1] = mcw->portstatus[1];
                mc.status |= 8;
                mcw->menu_step = 4;
                
                print_sc1(-3);
                
                return -3;
            } else if (mc.status & (1 << MC_STATUS_00)) {
                mcw->menu_step = 0;
                
                print_sc1(4);
                
                return 4;
            }
            
            print_sc1(mcw->port + 2);
            
            return mcw->port + 2;
        
        case 4:
            if (mcw->tmp_status[0] != mcw->portstatus[0] || mcw->tmp_status[1] != mcw->portstatus[1]) {
                
                mcStepInit();
            }
            break;
    }
    print_sc1(0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcStartCheck2);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcCheckDir);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @1094_0x00399640);

INCLUDE_RODATA("asm/nonmatchings/MC/mc", @1536);

INCLUDE_ASM("asm/nonmatchings/MC/mc", mcJobCheckDir);

static void mcSearchDir(s_char port) {
    mcw->dirnum = 0;
    mcSetJob(4, port, 0);
}

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
