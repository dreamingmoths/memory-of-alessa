#include "sh2_common.h"
#include "sce/eekernel.h"
#include "mw/mw_stdarg.h"
#include "lib/wprtfsrc.h"
#include "lib/newlib/reent.h"

extern int wrap_printf_enable_f;
extern char* wrap_printf_eob;
extern int wrap_printf_help;
extern int wrap_printf_sid;
extern int wrap_printf_skip_f;

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", PollSemaAll);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", SignalSemaLimit);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", iSignalSemaLimit);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", CreateThread2);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", CreateSema2);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", shPollSemaAll);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", shSignalSemaLimit);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", ishSignalSemaLimit);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", shCreateThread2);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", shCreateSema2);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", iReleaseSema);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", ishReleaseSema);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", SignalSemaMax);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", shSignalSemaMax);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", printf_init);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", swap_printf_buf);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", printf_skip);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", printf_sub);

INCLUDE_ASM("asm/nonmatchings/lib/wprtfsrc", printf_enable);

const char rodata_14_0x003930C0[] = "for wrap print";

const char rodata_42_0x003930D0[] = "== pre printf begin ==\n%s== pre printf end ==\nwprtfsrc.c> enable printf.\n";

const char rodata_43_0x00393120[] = "%swprtfsrc.c> enable printf.\n";



int printf(const char* format, ...) {
    extern int vfprintf(char* stream, const char* format, ...);
    extern int vsprintf(char* stream, const char* format, ...);

    int skip = wrap_printf_skip_f;
    int ret;
    char* buf;
    int enable;
    va_list argp;

    if (skip) {
        ret = 0;
    } else {
        va_start(argp, format);
        WaitSema(wrap_printf_sid);
        
        if (wrap_printf_enable_f) {
            buf = swap_printf_buf();

            if (buf && *buf) {
                printf_sub(
                    wrap_printf_help 
                        ? "== iprintf begin ==\n%s== iprintf end ==\n" 
                        : "%s", buf
                );
            }

            ret = vfprintf(_impure_ptr->_stdout, format, argp);
        } else {
            ret = 0;

            DI();
            ret = wrap_printf_eob ? vsprintf(wrap_printf_eob, format, argp) : 0;
            wrap_printf_eob += ret;
            EI();
        }

        SignalSema(wrap_printf_sid);
    }

    return ret;
}

