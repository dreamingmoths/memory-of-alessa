#include "Multi_thr/sys/init_mt_sys.h"
#include "Multi_thr/filesys/sh_cdvd.h"
#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/loadinit/loadinit.h"
#include "Multi_thr/dma/dma1serv.h"
#include "Multi_thr/dma/dma2serv.h"
#include "Exec_Env/exec_env.h"
#include "DBG/dbflag.h"

static void check_boot_file_name_in_system_cnf(s_char* bootfilename /* r2 */);
static void check_code_and_data_size(void);
static int prepare_data_mgf(void);
static void iop_mem_check(int mmode /* r16 */);
static void iop_mem_check_break(int fid);

//@todo: these belong elsewhere
extern char _ovl_start_addr[]; // size: 0x0, address: 0x1F01E00
extern char _ovl_align_addr[]; // size: 0x0, address: 0x1F08E00
extern char _end[];            // size: 0x0, address: 0x1FA0000

u_long128 ADDR_STACK_DISP[512];     // size: 0x2000, address: 0x0
u_long128 ADDR_STACK_MC[384];       // size: 0x1800, address: 0x0
u_long128 ADDR_STACK_FS_BG[512];    // size: 0x2000, address: 0x116B280
u_long128 ADDR_STACK_FS_CB[512];    // size: 0x2000, address: 0x1169280
u_long128 ADDR_STACK_LI[512];       // size: 0x2000, address: 0x1167280
u_long128 ADDR_STACK_PAD[512];      // size: 0x2000, address: 0x1165280
u_long128 ADDR_STACK_VB_S[256];     // size: 0x1000, address: 0x1164280
u_long128 ADDR_STACK_VB_E[512];     // size: 0x2000, address: 0x1162280
u_long128 ADDR_STACK_DMA_GIF[256];  // size: 0x1000, address: 0x1161280
u_long128 ADDR_STACK_DMA_VIF1[256]; // size: 0x1000, address: 0x1160280
u_long128 ADDR_QUEUE_FS_BG[512];    // size: 0x2000, address: 0x115E280
u_long128 ADDR_QUEUE_LI[128];       // size: 0x800,  address: 0x115DA80
u_long128 ADDR_QUEUE_DMA_GIF[512];  // size: 0x2000, address: 0x115BA80
u_long128 ADDR_QUEUE_DMA_VIF1[512]; // size: 0x2000, address: 0x1159A80


void check_code_and_data_size(void) {
    ASSERT_ON_LINE(("code+data size over",(_ovl_start_addr<=_end)), 130);
    ASSERT_ON_LINE(("code+data size over",(_ovl_align_addr<=_end)), 132);
}

static void check_boot_file_name_in_system_cnf(s_char* bootfilename /* r2 */) {
    s_char* dirchp; // r6 a2
    s_char* search; // r7 a3
    s_char* filename; // r2 v0

    if (bootfilename != NULL) {
        filename = bootfilename;

        search = bootfilename;
        dirchp = NULL;
        for (; *search != '\0'; search++) {
            switch((s_char)*search) {
                case ':':
                case '/':
                case '\\':
                    dirchp = search;
                    break;
                default:
                    break;
            }
        }

        if (dirchp != NULL) filename = dirchp + 1;



        search = "SLUS_202.28";
        for (; *search == *filename; search++, filename++) {
            if (*search == '\0') break;
        }
        ASSERT_ON_LINE(*search=='\0' && ( *filename=='\0' || *filename==';' ), 167);
    }
}

void check_build_environment(char* bootfilename /* r16 */) {
    VERBOSE_ON_LINE(174, 1, "CODE:%d\n", 20228);
    VERBOSE_ON_LINE(175, 1, "BOOT:%s\n", "SLUS_202.28");
    VERBOSE_ON_LINE(176, 1, "MC FILE:%s\n", "BASLUS-20228");
    check_code_and_data_size();
    check_boot_file_name_in_system_cnf(bootfilename);
}

static int prepare_data_mgf(void) {
    int fid; // r2 
   
    fid = FcRead(data_bg_mgf, NULL);
    fid = FcRead(data_chr_mgf, NULL);
    fid = FcRead(data_etc_mgf, NULL);
    fid = FcRead(data_menu_mgf, NULL);
    fid = FcRead(data_movie_mgf, NULL);
    fid = FcRead(data_pic_mgf, NULL);
    fid = FcRead(data_sound_mgf, NULL);
 
    return fid;    
}

static void iop_mem_check(int mmode /* r16 */) {
    dbFlagReserve(256, "break at load module sequense for IOP memory check.");
    if (dbFlag(256)) {
        shSifRebootIopR("host0:ioprp.img");
        shSifInit();
        shSifLoadModuleR("host0:mem2MB.irx", 0, ""); // not 100% sure about these value
        shSifRebootIopR("host0:ioprp.img");
        shCdInitR(0, mmode);
        execEnv_skip_load_iop_mod = 1;
    }
}

static void iop_mem_check_break(int fid) {
    int break_flag; // r29+0x2C
    int count; // r16

    if (dbFlag(256)) {
        fsSync(0, fid);
        break_flag = 1;
        count = 0;
        printf(DEBUG_TEXT_ON_LINE(241, "Please break and modify flag(@0x%08x)\n", &break_flag));
        while (break_flag != 0) 
            count++;        
    }
}

int init_sh2_filesys(void) {
    int fid; // r17
    int mmode; // r16
    ChangeThreadPriority(GetThreadId(), 32);
    utilExclInit();

    shSyncVEndInit();
    shSyncVStartInit();


    mmode = 2;
    if (execEnv_cdvd_media_type) {
        mmode = 1;
    }




    shCdInitR(0, mmode);

    iop_mem_check(mmode);

    if (!execEnv_skip_load_iop_mod) {
        shSifInit();

        shIopReplaceMod("iop/lib224/ioprp.img");
        execEnv_skip_load_iop_mod = 1;

        shCdInitR(0, mmode);
    }

    printf_enable();


    fsInit(28,
           ADDR_STACK_FS_BG,
           sizeof(ADDR_STACK_FS_BG),
           ADDR_QUEUE_FS_BG, sizeof(ADDR_QUEUE_FS_BG));

    lisInit(30,
            ADDR_STACK_LI,
            sizeof(ADDR_STACK_LI),
            ADDR_QUEUE_LI, sizeof(ADDR_QUEUE_LI));
    fcSifInit();







    fcIopLoadMod("iop/lib224/sio2man.irx");




    fcIopLoadMod("iop/lib224/padman.irx");

    fcIopLoadMod("iop/lib224/mcman.irx");
    fid = fcIopLoadMod("iop/lib224/mcserv.irx");



    iop_mem_check_break(fid);


    if (!dbFlag(1)) {
        fcIopLoadMod("iop/lib224/libsd.irx");
        fcIopLoadMod("iop/lib224/sdrdrv.irx");
    }

    if (!dbFlag(1)) {

        fcIopLoadMod(execEnv_sound_data_from_hd
        ? "iop/sd0712/sd_hd.irx"
        : "iop/sd0712/sd_cd.irx");
    }




    if (!dbFlag(1)) {

        fcIopLoadMod("iop/sd0712/sdstr.irx");
        fcIopLoadMod(execEnv_sound_data_from_hd
        ? "iop/sd0712/soundhd.irx"
        : "iop/sd0712/soundcd.irx");
    }







    fcHdInit(1);

    fcDiskSelect(execEnv_file_load_mode & 3);
    fcExecDevSelect(execEnv_exec_path_mode & 3);


    fcSetParamForSystemCnf(execEnv_skip_cd_check);

    fsSync(0, -1);
    if (!dbFlag(1)) {
        int sect; // r17


        char buf[256] = "host0:./sound.dat"; // r29+0x40
        char* path; // r18
        sceCdlFILE fp[1]; // r29+0x140


        shPathMakeIop(buf, "iop/sd0712/sound.dat");


        if (!execEnv_sound_data_from_hd) {


            shCdSearchFile(fp, buf);



            sect = fp->lsn;
            path = NULL;
        } else {
            sect = 0;

            path = buf;
        }


        sceCdSync(0);
        SeCallInit(sect, mmode, path);
        shSdSifInit();
        sceCdSync(0);
    }


    fcCdInitW(8, ADDR_STACK_FS_CB, sizeof(ADDR_STACK_FS_CB));

    fcCdCheckDisk(1);

    fid = prepare_data_mgf();



    ThreadVbeStart(ADDR_STACK_VB_E,
                   sizeof(ADDR_STACK_VB_E),
                   4, 0, -1);
    ThreadVbsStart(ADDR_STACK_VB_S,
                   sizeof(ADDR_STACK_VB_S),
                   2, 0, -1);
    return fid;
}

void init_sh2_dmac(void) {

    texSlotInit();
    d1sInit(6, ADDR_STACK_DMA_VIF1, sizeof(ADDR_STACK_DMA_VIF1), ADDR_QUEUE_DMA_VIF1, sizeof(ADDR_QUEUE_DMA_VIF1));


    d1cInit();
    d2sInit(6, ADDR_STACK_DMA_GIF, sizeof(ADDR_STACK_DMA_GIF), ADDR_QUEUE_DMA_GIF, sizeof(ADDR_QUEUE_DMA_GIF));


    d2cInit();
}

int init_sh2_devsys(void) {
    int sid_pad; // r16
    int sid_pad_fin; // r17















    sid_pad = CreateSema2(0, 256, NULL);





    fsSync(0, -1);









    sid_pad_fin = ThreadPadStart(ADDR_STACK_PAD, sizeof(ADDR_STACK_PAD), 6, 0, sid_pad);













    SignalSemaMax(sid_pad);
    SignalSema(WaitSema(sid_pad_fin));








    return sid_pad_fin;


}


