#include "sh2_common.h"

#include "debug.h"

#include "mw/mw_stdarg.h"

#include "Exec_Env/exec_env.h"

extern int vsprintf(char*, const char*, va_list);

int verbose(int level /* r2 */, char* format /* r29+0x420 */, ...) {
    int len; // r2
    char buf[1024]; // r29+0x10
    va_list argp;
    va_start(argp, format); // r2

    if (level <= 0) level = 1;


    
    if (level >= 9) level = 9;

    if (level <= execEnv_verbose_level) {
        
        
        len = vsprintf(buf, format, argp);
        if (len >= 0x400u) {
            printf(DEBUG_TEXT("verbose strbuf overflow!!\n")
                   DEBUG_TEXT("%s")
                   DEBUG_TEXT("halted by error\n", &buf));
            
            
            BLOCK_WHILE(1);
        }
        printf("%s", buf);
    
    
    }
}
