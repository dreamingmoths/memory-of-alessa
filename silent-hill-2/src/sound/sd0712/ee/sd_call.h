#ifndef SD_CALL_H
#define SD_CALL_H

#include "sh2_common.h"

typedef struct SdCallData {
    u_int call;
    u_int direct;
    u_int dist;
    u_int pitch;
} SdCallData;

typedef struct {
    void* base;
    int size;
    int pointer;
    int mode;
} SdEnvBuf;

typedef struct {
    int angle1;
    int angle2;
    int mode;
    float level;
    float minlevel;
    float pitch;
    float cutoff;
    sceVu0FVECTOR(*pos);
} SdEnv;

typedef struct Sd3dDataStruct {
    u_char loop;
    u_long ofst;
    u_long size;
    u_long sr;
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
