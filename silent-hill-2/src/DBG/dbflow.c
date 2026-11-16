#include "DBG/dbflow.h"

static s_char* last_check = NULL; // size: 0x4, address: 0x11B69A0
static u_long check_count = 0; // size: 0x4, address: 0x11B69A8
static u_long prv_check_count = 0; // size: 0x4, address: 0x11B69B0
static u_long warn_check_count = 0; // size: 0x4, address: 0x11B69B8
static u_long warn_wait = 0; // size: 0x4, address: 0x11B69C0
static int check_halt = 0; // size: 0x4, address: 0x0
static long sleep_timeout = 0; // size: 0x4, address: 0x11B69C8
static long sleep_time = 0; // size: 0x4, address: 0x11B69D0
static long sleep_check_interval = 0; // size: 0x4, address: 0x0
static long sleep_max = 0; // size: 0x4, address: 0x11B69D8
static long sleep_max_report = 119; // size: 0x4, address: 0x34C1D0
static long call_count = 0; // size: 0x4, address: 0x11B69E0

void ___dbFlowSetCheckPoint(s_char* check_point /* r2 */) {
    check_count++;
    last_check = check_point;
}

int dbFlowCheck(void) {
    int ret = true;
    s_char* str = last_check;

    if (str) {

        if (prv_check_count == check_count) {
            if (warn_check_count != check_count) {
                ++warn_wait;
                if (warn_wait >= 120) {
                    if (!str) str = "(unknown)";
                    DEBUG_LOG_ON_LINE(54, "warning!! flow stopped after `%s'\n", str);

                    warn_check_count = check_count;
                }
            }
            ret = false;
        } else {

            if (prv_check_count == warn_check_count) {
                s_char* str = last_check;
                if (!str) str = "(unknown)";
                DEBUG_LOG_ON_LINE(76, "reach at `%s'\n", str);
            }
            warn_wait = 0;
        }
        prv_check_count = check_count;
    }
    return ret;
}

void dbFlowStartCheck(int enable /* r2 */) {
    if (enable) {
        sleep_timeout = execEnv_auto_exit_time * 60;
        return;
    }
    sleep_timeout = 0;
}

void dbFlowCheckSleepTime(int flow_ok /* r2 */) {
    int mode;         // r2
    int exec_timeout; // r2

    call_count++;
    if (flow_ok) {
        sleep_time = 0;
    } else {
        sleep_time++;
    }

    if (!(sleep_time <= sleep_max)) {
        sleep_max = sleep_time;
    }

    exec_timeout = sleep_timeout != 0;
    if (exec_timeout) {
        exec_timeout = sleep_time >= sleep_timeout;
    }

    if (
        (  !sleep_time
        || !__moddi3(call_count, 3600)
        || exec_timeout
        )
        && (sleep_max_report < sleep_max)
    ) {
        sleep_max_report = sleep_max;
    }
    if (exec_timeout) {
        sleep_time = 60;

        while (sleep_time > 0) {
            shSyncVStart(0);
            sleep_time--;
        }
        Exit(0);
    }
}
