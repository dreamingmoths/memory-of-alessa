// work/sh2(CVS全取得)/src/connect.c
typedef struct _SH2_SYS
{
    // total size: 0x30
    u_int step[8];      // offset 0x0, size 0x20
    u_int pre_playable; // offset 0x20, size 0x4
    int main_status;    // offset 0x24, size 0x4
    u_int soft_reset;   // offset 0x28, size 0x4
    u_int frame_cnt;    // offset 0x2C, size 0x4
} SH2_SYS;
extern SH2_SYS Sh2sys;