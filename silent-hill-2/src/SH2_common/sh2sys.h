#ifndef SH2SYS_H
#define SH2SYS_H

#include "sce/eetypes.h"

typedef struct _SH2_SYS {
    // total size: 0x30
    u_int step[8];      // offset 0x0, size 0x20
    u_int pre_playable; // offset 0x20, size 0x4
    int main_status;    // offset 0x24, size 0x4
    u_int soft_reset;   // offset 0x28, size 0x4
    u_int frame_cnt;    // offset 0x2C, size 0x4
} SH2_SYS;

extern SH2_SYS Sh2sys;

static inline void sh2sys_step_2() {
    Sh2sys.step[2]++;
    Sh2sys.step[3] = 0;
    Sh2sys.step[4] = 0;
    Sh2sys.step[5] = 0;
    Sh2sys.step[6] = 0;
    Sh2sys.step[7] = 0;
}
static inline void sh2sys_step_3() {
    Sh2sys.step[3]++;
    Sh2sys.step[4] = 0;
    Sh2sys.step[5] = 0;
    Sh2sys.step[6] = 0;
    Sh2sys.step[7] = 0;
}
static inline void sh2sys_set_2(int value) {
    Sh2sys.step[2] = value;
    Sh2sys.step[3] = 0;
    Sh2sys.step[4] = 0;
    Sh2sys.step[5] = 0;
    Sh2sys.step[6] = 0;
    Sh2sys.step[7] = 0;
}
static inline void sh2sys_set_3(int value) {
    Sh2sys.step[3] = value;
    Sh2sys.step[4] = 0;
    Sh2sys.step[5] = 0;
    Sh2sys.step[6] = 0;
    Sh2sys.step[7] = 0;
}
static inline void sh2sys_set_0(int value) {
    Sh2sys.step[0] = value;
    Sh2sys.step[1] = 0;
    Sh2sys.step[2] = 0;
    Sh2sys.step[3] = 0;
    Sh2sys.step[4] = 0;
    Sh2sys.step[5] = 0;
    Sh2sys.step[6] = 0;
    Sh2sys.step[7] = 0;
}

#endif // SH2SYS_H
