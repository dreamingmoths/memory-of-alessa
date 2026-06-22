#include "Multi_thr/sys/init_mt_sys.h"
#include "Multi_thr/filesys/sh_cdvd.h"
#include "Multi_thr/filesys/fileserv.h"
#include "DBG/dbflag.h"

static void check_boot_file_name_in_system_cnf(char* bootfilename /* r2 */);
static void check_code_and_data_size(void);
static int prepare_data_mgf(void);
static void iop_mem_check(int mmode /* r16 */);
static void iop_mem_check_break(int fid);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/sys/init_mt_sys", check_code_and_data_size);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/sys/init_mt_sys", check_boot_file_name_in_system_cnf);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @34_0x00391A30);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @35_0x00391A50);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @36_0x00391A80);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @37_0x00391AA0);

const char rodata_79_0x00391AD0[] = "SLUS_202.28";

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @80_0x00391AE0);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @81);

void check_build_environment(char* bootfilename /* r16 */) {
    verbose(1, "init_mt_sys.c:174> CODE:%d\n", 0x4F04);
    verbose(1, "init_mt_sys.c:175> BOOT:%s\n", rodata_79_0x00391AD0);
    verbose(1, "init_mt_sys.c:176> MC FILE:%s\n", "BASLUS-20228");
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
    dbFlagReserve(0x100, "break at load module sequense for IOP memory check.");
    if (dbFlag(0x100) != 0) {
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

    if (dbFlag(0x100) != 0) {        
        fsSync(0, fid);
        break_flag = 1;
        count = 0;
        printf("init_mt_sys.c:241> Please break and modify flag(@0x%08x)\n", &break_flag);
        while (break_flag != 0) 
            count++;        
    }
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/sys/init_mt_sys", init_sh2_filesys);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/sys/init_mt_sys", init_sh2_dmac);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/sys/init_mt_sys", init_sh2_devsys);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @148);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @149_0x00391C80);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @150);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @151);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @152);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @153_0x00391D00);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @154_0x00391D20);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @155);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @156);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @157);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @158_0x00391DA0);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @159);

INCLUDE_RODATA("asm/nonmatchings/Multi_thr/sys/init_mt_sys", @160_0x00391DE0);

