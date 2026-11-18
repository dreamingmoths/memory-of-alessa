#ifndef SD_CALL_H
#define SD_CALL_H

#include "sh2_common.h"

typedef struct SdCallData {
    // Members
    u_int call;   // offset 0x0, size 0x4
    u_int direct; // offset 0x4, size 0x4
    u_int dist;   // offset 0x8, size 0x4
    u_int pitch;  // offset 0xC, size 0x4
} SdCallData;

typedef struct {
    // Members
    void* base;  // offset 0x0, size 0x4
    int size;    // offset 0x4, size 0x4
    int pointer; // offset 0x8, size 0x4
    int mode;    // offset 0xC, size 0x4
} SdEnvBuf;

typedef struct {
    // Members
    int angle1;          // offset 0x0, size 0x4
    int angle2;          // offset 0x4, size 0x4
    int mode;            // offset 0x8, size 0x4
    float level;         // offset 0xC, size 0x4
    float minlevel;      // offset 0x10, size 0x4
    float pitch;         // offset 0x14, size 0x4
    float cutoff;        // offset 0x18, size 0x4
    sceVu0FVECTOR(*pos); // offset 0x1C, size 0x4
} SdEnv;

// total size: 0x20
typedef struct Sd3dDataStruct {
    // Members
    u_char loop; // offset 0x0, size 0x1
    u_long ofst; // offset 0x8, size 0x4
    u_long size; // offset 0x10, size 0x4
    u_long sr;   // offset 0x18, size 0x4
} Sd3dDataStruct;

int sd_call(int call, int direct, int dist, int pitch);

int sd_se_stop(int call);

int sd_se_change(int call, int direct, int dist, int pitch);

int sd_track(int track, int vol);

int sd_radio(int ch, int vol, int pan, int pitch);

int sd_stat(void);

void sd_setpath(s_char* dp);

void sd_vsync(void);

int sd_3d_call(int call, int arg1, int arg2, float arg3, float arg4);

int sd_3d_move(int no, int arg1, int arg2, float arg3, float arg4);

void sd_3d_allstop(void);

void sd_3d_stop(int no);

void* sd_3d_adrs(void);

#endif // SD_CALL_H
