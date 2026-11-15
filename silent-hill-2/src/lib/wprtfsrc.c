#include "sh2_common.h"
#include "sce/eekernel.h"
#include "mw/mw_stdarg.h"
#include "lib/wprtfsrc.h"
#include "lib/newlib/reent.h"
#include "Chacter/skelton.h"

extern void* _gp;

static int wrap_printf_enable_f;
static int wrap_printf_skip_f;
static int wrap_printf_help;
static int wrap_printf_buf_idx;
static int wrap_printf_buf_size;
static char* wrap_printf_buf[2];
static char* wrap_printf_eob;

static int wrap_printf_sid = -1;

int PollSemaAll(int sid) {
    return shPollSemaAll(sid);
}

int SignalSemaLimit(int sid) {
    return shSignalSemaLimit(sid);
}

int iSignalSemaLimit(int sid) {
    return ishSignalSemaLimit(sid);
}

int CreateThread2(void (*entry)(void*), void* stack, int stackSize, int prio, u_int option) {
    return shCreateThread2(entry, stack, stackSize, prio, option);
}

int CreateSema2(int init, int max, const s_char* option) {
    return shCreateSema2(init, max, (u_int) option);
}

int shPollSemaAll(int sid) {
    int ret;

    ret = PollSema(sid);
    if (ret != -1)
        BLOCK_WHILE(PollSema(sid) != -1);
    return ret;
}

int shSignalSemaLimit(int sid) {
    SemaParam sema[1];
    int ret;

    ret = ReferSemaStatus(sid, sema);
    if (ret != -1) {
        if (sema->currentCount < sema->maxCount) {
            ret = SignalSema(sid);
        } else {
            ret = -1;
        }
    }
    return ret;
}

int ishSignalSemaLimit(int sid) {
    SemaParam sema[1];
    int ret;

    ret = iReferSemaStatus(sid, sema);
    if (ret != -1) {
        if (sema->currentCount < sema->maxCount) {
            ret = iSignalSema(sid);
        } else {
            ret = -1;
        }
    }
    return ret;
}

int shCreateThread2(void (*entry)(void*), void* stack, int stackSize, int prio, u_int option) {
    ThreadParam thread[1];

    thread->entry        = entry;
    thread->stack        = stack;
    thread->stackSize    = stackSize;
    thread->initPriority = prio;
    thread->option       = option;
    thread->gpReg        = &_gp;

    return CreateThread(thread);
}

int shCreateSema2(int init, int max, u_int option) {
    SemaParam sema[1];

    sema->initCount = init;
    sema->maxCount  = max;
    sema->option    = option;

    return CreateSema(sema);
}

int iReleaseSema(int sid) {
    return ishReleaseSema(sid);
}

int ishReleaseSema(int sid) {
    SemaParam sema[1];
    int wait;

    if (iReferSemaStatus(sid, sema) != -1) {
        wait = sema->numWaitThreads;
        while (wait > 0) {
            if (iSignalSema(sid) == -1)
                break;
            --wait;
        }
    }
    return sid;
}

void SignalSemaMax(int sid) {
    shSignalSemaMax(sid);
}

void shSignalSemaMax(int sid) {
    SemaParam sema[1];
    int wait;

    if (ReferSemaStatus(sid, sema) != -1) {
        wait = sema->maxCount - sema->currentCount;
        while (wait > 0) {
            if (SignalSema(sid) == -1)
                break;
            --wait;
        }
    }
}

void printf_init(void* buf_addr, int buf_size, int help) {
    SemaParam sema[1];

    if (wrap_printf_sid == -1) {

        sema->initCount = 0;
        sema->maxCount  = 0;
        sema->option    = (u_int) "for wrap print"; // >:\

        wrap_printf_sid = CreateSema(sema);
    } else {
        WaitSema(wrap_printf_sid);
    }

    if (buf_size == 0) {
        buf_addr = NULL;
    }
    if (buf_addr == NULL) {
        buf_size = 0;
    }

    wrap_printf_help     = help;
    wrap_printf_enable_f = 0;
    wrap_printf_buf_idx  = 0;
    wrap_printf_buf_size = buf_size / 2;

    wrap_printf_buf[0] = buf_addr;
    wrap_printf_buf[1] = (s_char*) buf_addr + wrap_printf_buf_size;

    if (wrap_printf_buf_size != 0) {
        *wrap_printf_buf[0] = NULL;
        *wrap_printf_buf[1] = NULL;
    }

    wrap_printf_eob = wrap_printf_buf[0];
    SignalSema(wrap_printf_sid);
}

char* swap_printf_buf(void) {
    char* buf;

    DI();
    buf = NULL;

    if (
        (wrap_printf_buf_size != 0) && (wrap_printf_eob != wrap_printf_buf)) {
        strncpy(wrap_printf_buf[!wrap_printf_buf_idx],
                wrap_printf_buf[wrap_printf_buf_idx],
                wrap_printf_buf_size);

        buf = wrap_printf_buf[wrap_printf_buf_idx];

        wrap_printf_buf_idx                   = !wrap_printf_buf_idx;
        wrap_printf_eob                       = wrap_printf_buf[wrap_printf_buf_idx];
        *wrap_printf_buf[wrap_printf_buf_idx] = NULL;
    }
    EI();
    return buf;
}

void printf_skip(int skip) {
    wrap_printf_skip_f = skip;
}

int printf_sub(const char* format, ...) {
    extern int vfprintf(char* stream, const char* format, ...);

    va_list argp;

    if (wrap_printf_skip_f) {
        return 0;
    }

    va_start(argp, format);

    return vfprintf(_impure_ptr->_stdout, format, argp);
}

void printf_enable(void) {
    const char* format;
    char* buf;

    WaitSema(wrap_printf_sid);

    wrap_printf_enable_f = 1;
    buf                  = swap_printf_buf();

    SignalSema(wrap_printf_sid);

    if (buf && *buf) {
        if (wrap_printf_help) {
            format = "== pre printf begin ==\n%s== pre printf end ==\nwprtfsrc.c> enable printf.\n";
        } else {
            format = "%swprtfsrc.c> enable printf.\n";
        }

        printf_sub(format, buf);
    }
}

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
                        : "%s",
                    buf);
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
