#include "sh2_common.h"

#include "debug.h"

#include "mw/mw_stdarg.h"

#include "Exec_Env/exec_env.h"

extern int vsprintf(char*, const char*, va_list);

int verbose(int level, char* format, ...) {
    int len;
    char buf[1024];
    va_list argp;
    va_start(argp, format);

    if (level <= 0) level = 1;


    
    if (level >= 9) level = 9;

    if (level <= execEnv_verbose_level) {
        
        
        len = vsprintf(buf, format, argp);
        if (len >= 1024u) {
            printf(DEBUG_TEXT("verbose strbuf overflow!!\n")
                   DEBUG_TEXT("%s")
                   DEBUG_TEXT("halted by error\n", buf));
            
            
            BLOCK_WHILE(1);
        }
        printf("%s", buf);
    
    
    }
}
