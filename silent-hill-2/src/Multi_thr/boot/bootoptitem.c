#include "sh2_common.h"

#include "debug.h"

#include "GFW/sh2_DrawEnvData.h"

#include "Multi_thr/boot/bootoptitem.h"
#include "Multi_thr/util/utilstr.h"

#include "Exec_Env/exec_env.h"
#include "Exec_Env/local_env.h"

#pragma divbyzerocheck off

static int getopt_h(void);
static int getopt_str(char* arg);
static int getopt_str2(char* arg, char* buf);
static void putopt_str(char* arg, int var);
static int getopt_I(char* arg);
static int getopt_B(char* arg);
static int getopt_D(char* arg);
static int getopt_H(char* arg);
static int getopt_v(char* arg);
static void putopt_v(char* arg, int var);
static int getopt_S(char* arg);
static void putopt_S(char* arg, int var);
static int getopt_int(char* arg, int var0);
static void putopt_int(char* arg, int var);
static int getopt_d(char* arg);
static void putopt_d(char* arg, int var);
static int getopt_X(char* arg);
static void putopt_X(char* arg, int var);
static int getopt_V(char* arg);
static void putopt_V(char* arg, int var);
static int getopt_F(char* arg);
static void putopt_F(char* arg, int var);
static int getopt_x(char* arg);
static void putopt_x(char* arg, int var);

extern /* static */ int opt_h_dummy;
extern char optI_strbuf[256];
extern char optB_strbuf[256];
extern char optD_strbuf[256];
extern char optH_strbuf[256];

BootOptItem BootOptItemList[20] = {
    {
        /* .var = */ &opt_h_dummy,
        /* .key = */ "h",
        /* .get = */ getopt_h,
        /* .put = */ NULL,
        /* .help = */ "\tprint this Help.\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_quick_boot,
        /* .key = */ "q",
        /* .get = */ NULL,
        /* .put = */ NULL,
        /* .help = */ "\tQuick boot(skip title)\n\t(not supported yet)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_skip_load_iop_mod,
        /* .key = */ "i",
        /* .get = */ NULL,
        /* .put = */ NULL,
        /* .help = */ "\tskip load Iop modules\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_skip_cd_check,
        /* .key = */ "c",
        /* .get = */ NULL,
        /* .put = */ NULL,
        /* .help = */ "\tskip Cd check(for use hd only)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_hd_merge_file,
        /* .key = */ "m",
        /* .get = */ NULL,
        /* .put = */ NULL,
        /* .help = */ "\tno-use Merge files\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_self_reboot_mode,
        /* .key = */ "r",
        /* .get = */ NULL,
        /* .put = */ NULL,
        /* .help = */ "\tself-Reboot flag(reserved)\n\t(not supported yet)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_verbose_level,
        /* .key = */ "v:",
        /* .get = */ getopt_v,
        /* .put = */ putopt_v,
        /* .help = */ " {0-9}\n\tVerbose level for verbose(level,format,...);\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_cdvd_media_type,
        /* .key = */ "S:",
        /* .get = */ getopt_S,
        /* .put = */ putopt_S,
        /* .help = */ "\tcd/dvd media Select\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_sound_data_from_hd,
        /* .key = */ "s",
        /* .get = */ NULL,
        /* .put = */ NULL,
        /* .help = */ "\tload 'sound.dat' from hd\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_auto_exit_time,
        /* .key = */ "X:",
        /* .get = */ getopt_X,
        /* .put = */ putopt_X,
        /* .help = */ "<timeout>\n\teXit if sleeping while <timeout> sec.\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_debug_flag,
        /* .key = */ "d:",
        /* .get = */ getopt_d,
        /* .put = */ putopt_d,
        /* .help = */ " {0x00000000-0xffffffff}\n\truntime Debug flag\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_video_mode,
        /* .key = */ "V:",
        /* .get = */ getopt_V,
        /* .put = */ putopt_V,
        /* .help = */ " {0|1}\n\tVideo mode\n\t0: NTSC (frame rate 60,disp height 448)\n\t1: PAL  (frame rate 50,disp height 512)\n\t(not supported yet)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_file_load_mode,
        /* .key = */ "F:",
        /* .get = */ getopt_F,
        /* .put = */ putopt_F,
        /* .help = */ " {0|1|2}\n\tFile load mode\n\t0:use CD always\n\t1:use CD, but use HD if not exist CD\n\t2:use HD, but use CD if not exist HD\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_exec_path_mode,
        /* .key = */ "x:",
        /* .get = */ getopt_x,
        /* .put = */ putopt_x,
        /* .help = */ " {0|1|2}\n\teXec path mode(\".bin\",\".cnf\")\n\t0:same as File load mode(-F)\n\t1:use CD always\n\t2:use HD always\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_host_path,
        /* .key = */ "H:",
        /* .get = */ getopt_H,
        /* .put = */ putopt_str,
        /* .help = */ " <directory>\n\tHost directory (prefix for all files)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_database_path,
        /* .key = */ "B:",
        /* .get = */ getopt_B,
        /* .put = */ putopt_str,
        /* .help = */ " <directory>\n\tdataBase(merge file) directory (prefix for all merge files)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_data_path,
        /* .key = */ "D:",
        /* .get = */ getopt_D,
        /* .put = */ putopt_str,
        /* .help = */ " <directory>\n\tData files directory (prefix for all data files)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_iop_path_hd,
        /* .key = */ "I:",
        /* .get = */ getopt_I,
        /* .put = */ putopt_str,
        /* .help = */ " <directory>\n\tIop modules directory for hd(prefix for all iop modules)\n",
        /* .set = */ false
    },
    {
        /* .var = */ &execEnv_reboot_file,
        /* .key = */ "R:",
        /* .get = */ getopt_str,
        /* .put = */ putopt_str,
        /* .help = */ " <elf-file>\n\tReboot by elf-file\n\t(not supported yet)\n",
        /* .set = */ false
    },
    {
        /* empty */
    }
};

#line 131
static int getopt_h(void) {
    BootOptItem* item;
    for (item = BootOptItemList; item->var != NULL; item++) {
        char* help = item->help;
        if (help) printf("-%c%s", item->key[0], help);
    }
    return 0;
}


static int getopt_str(char* arg /* r2 */) {
    return (int) arg;
}


static int getopt_str2(char* arg /* r2 */, char* buf /* r16 */) {
    int len = 0;
    char* str = buf;
    len += UtilStrCpyL(str, arg, 255);
    if (str[len - 1] == '-') {
        len--;
        
        
        
        
        len += UtilStrCpyL(str + len, "daily.thu/", 255 - len);
        str[len] = 0;
        DEBUG_LOG_ON_LINE(158, "set default data path: %s\n", str);
    
    } else {
        str[len] = 0; 
    }    
    return (int) str;
}






static void putopt_str(char* arg /* r16 */, int var /* r2 */) {
    int len;
    len = UtilStrCpyL(arg, (char*) var, 255);
    arg[len] = 0;
}






static int getopt_I(char* arg /* r2 */) {
    return getopt_str2(arg, optI_strbuf);
}


static int getopt_B(char* arg /* r2 */) {
    return getopt_str2(arg, optB_strbuf);
}


static int getopt_D(char* arg /* r2 */) {
    return getopt_str2(arg, optD_strbuf);
}


static int getopt_H(char* arg /* r2 */) {
    return getopt_str2(arg, optH_strbuf);
}



static int getopt_v(char* arg /* r2 */) {
    int var = *arg - '0'; // r2
    if (var < 0) var = 0;
    if (var > 9) var = 9;
    execEnv_verbose_level = var;
    return var;
}


static void putopt_v(char* arg /* r2 */, int var /* r2 */) {
    if (var < 0) var = 0;
    if (var > 9) var = 9;
    arg[0] = var + '0';
    arg[1] = '\0';
}



static int getopt_S(char* arg /* r2 */) {
    int var = *arg - '0'; // r2
    if (var < 0) var = 0;
    if (var > 1) var = 1;
    execEnv_cdvd_media_type = var;
    return var;
}


static void putopt_S(char* arg /* r2 */, int var /* r2 */) {
    if (var < 0) var = 0;
    if (var > 1) var = 1;
    arg[0] = var + '0';
    arg[1] = '\0';
}


static int getopt_int(char* arg /* r2 */, int var0 /* r17 */) {
    int var; // r29+0x3C
    int op; // r16
    op = *arg;
    
    if (op >= '0' && op <= '9') {
        op = '=';
    } else {
        arg++;
    }
    
    sscanf(arg, "%i", &var);
    
    switch (op) {
        default:
        case '=': var0   =   var; break;
        case '#':                 break;
        case '!': var0   = !var0; break;
        case '~': var0   = ~var0; break;
        case '+': var0  +=   var; break;
        case '-': var0  -=   var; break;
        case '*': var0  *=   var; break;
        case '/': var0  /=   var; break;
        case '%': var0  %=   var; break;
        case '|': var0  |=   var; break;
        case '^': var0  ^=   var; break;
        case '&': var0  &=   var; break;
        case '<': var0 <<=   var; break;
        case '>': var0 >>=   var; break;
    }
    return var0;
}


static void putopt_int(char* arg /* r2 */, int var /* r2 */) {
    sprintf(arg, "=0x%08x", var);
}



static int getopt_d(char* arg /* r2 */) {
    int var = execEnv_debug_flag;
    int flag = getopt_int(arg, var); // @note: not in dwarf, but matches line numbers (reusing var doesn't work?)
    execEnv_debug_flag = flag;
    if (flag & (1 << 5)) {
        Env_ctl.stat_ctl_2.uc8[0] = (4 - (flag & 0b1110)) >> 1;
    }
    return; // they forgor to return something?
}


static void putopt_d(char* arg /* r2 */, int var /* r2 */) {
    putopt_int(arg, var);
}


static int getopt_X(char* arg /* r2 */) {
    int var = execEnv_auto_exit_time; // r2
    return getopt_int(arg, execEnv_auto_exit_time);
}


static void putopt_X(char* arg /* r2 */, int var /* r2 */) {
    putopt_int(arg, var);
}



static int getopt_V(char* arg /* r2 */) {
    int ret; // @note not in dwarf
    int var = *arg - '0'; // r2
    if (var) {
        ret = 3;
        execEnv_frame_rate = 50;
        execEnv_disp_height = 512;;
    } else {
        ret = 2;
        execEnv_frame_rate = 60;
        execEnv_disp_height = 448;
    }
    return ret;
}







static void putopt_V(char* arg /* r2 */, int var /* r2 */) {
    arg[0] = (var == 3 ? 1 : 0) + '0';
    arg[1] = '\0';
}


static int getopt_F(char* arg /* r2 */) {
    int var; // r2
    int mode; // r2
    var = *arg - '0';
    if (var > 2) var = 2;
    else if (var < 0) var = 0;



    mode = var; /* @note some removed code here, maybe */



    return var;
}


static void putopt_F(char* arg /* r2 */, int var /* r2 */) {
    int mode; // r3
    int i; // r2 @note present in dwarf, unused here
    mode = var & 0xf;
    if (mode > 2) mode = 2;
    else if (mode < 0) mode = 0;
    arg[0] = mode + '0';

    
    /* some removed code here, maybe */
    
    
    
    arg[1] = '\0';
}


static int getopt_x(char* arg /* r2 */) {
    int var; // r2
    int mode; // r2
    var = *arg - '0';
    if (var > 2) var = 2;
    else if (var < 0) var = 0;
    
    
    
    mode = var; /* @note some removed code here, maybe */
    
    
    
    return var;
}


static void putopt_x(char* arg /* r2 */, int var /* r2 */) {
    int mode; // r3
    int i; // r2
    mode = var & 0xf;
    if (mode > 2) mode = 2;
    else if (mode < 0) mode = 0;
    arg[0] = mode + '0';

    
    /* some removed code here, maybe */
    
    
    
    arg[1] = '\0';
}
