#ifndef SH_SOUND_H
#define SH_SOUND_H

#include "sh2_common.h"
#include "sce/eetypes.h"

// total size: 0xC this was an anon
typedef struct Change_List {
    // Members
    int sd_se; // offset 0x0, size 0x4
    int sd_3d; // offset 0x4, size 0x4
    int file;  // offset 0x8, size 0x4
} Change_List;

// total size: 0x8
typedef struct Se_TrackBuffer {
    // Members
    u_char status;        // offset 0x0, size 0x1
    u_char fade_in_type;  // offset 0x1, size 0x1
    u_char fade_out_type; // offset 0x2, size 0x1
    u_char pad;           // offset 0x3, size 0x1
    float volume;         // offset 0x4, size 0x4
} Se_TrackBuffer;

// total size: 0x4C
typedef struct Se_BgmBuffer {
    // Members
    int current;             // offset 0x0, size 0x4
    int next;                // offset 0x4, size 0x4
    int read;                // offset 0x8, size 0x4
    int sdb_no;              // offset 0xC, size 0x4
    float volume;            // offset 0x10, size 0x4
    Se_TrackBuffer track[7]; // offset 0x14, size 0x38
} Se_BgmBuffer;

// total size: 0x40
typedef struct Se2D_ManageData {
    // Members
    int sd;                                    // offset 0x0, size 0x4
    sceVu0FVECTOR pos;                         // offset 0x10, size 0x10
    float vol;                                 // offset 0x20, size 0x4
    short room;                                // offset 0x24, size 0x2
    u_char pos_on;                             // offset 0x26, size 0x1
    u_char pre_dist;                           // offset 0x27, size 0x1
    short pre_pan;                             // offset 0x28, size 0x2
    short status;                              // offset 0x2A, size 0x2
    float timer;                               // offset 0x2C, size 0x4
    float base;                                // offset 0x30, size 0x4
} Se2D_ManageData;

// total size: 0x30
typedef struct Se3D_ChannelData {
    // Members
    int sd;                                    // offset 0x0, size 0x4
    int room;                                  // offset 0x4, size 0x4
    int status;                                // offset 0x8, size 0x4
    sceVu0FVECTOR pos;                         // offset 0x10, size 0x10
    float vol;                                 // offset 0x20, size 0x4
} Se3D_ChannelData;

// total size: 0x20
typedef struct _SND_ROAD_AREA {
    // Members
    float x0;     // offset 0x0, size 0x4
    float z0;     // offset 0x4, size 0x4
    float x1;     // offset 0x8, size 0x4
    float z1;     // offset 0xC, size 0x4
    float x2;     // offset 0x10, size 0x4
    float z2;     // offset 0x14, size 0x4
    float min_hy; // offset 0x18, size 0x4
    float max_hy; // offset 0x1C, size 0x4
} SND_ROAD_AREA;

// total size: 0x40
typedef struct _SOUND_DATA {
    // Members
    SND_ROAD_AREA lim_sw; // offset 0x0, size 0x20
    int flags;            // offset 0x20, size 0x4
    int chanstat[7];      // offset 0x24, size 0x1C
} SOUND_DATA;

// total size: 0x1C
typedef struct _NEAR_SOUND_DATA {
    // Members
    char inVol[7];  // offset 0x0, size 0x7
    char outVol[7]; // offset 0x7, size 0x7
    int errCode;    // offset 0x10, size 0x4
    int absIndex;   // offset 0x14, size 0x4
    float len;      // offset 0x18, size 0x4
} NEAR_SOUND_DATA;

// total size: 0x120
typedef struct _SOUND_WORK {
    // Members
    SOUND_DATA* sound_ary;                           // offset 0x0, size 0x4
    sceVu0FVECTOR chara_pos;                         // offset 0x10, size 0x10
    float half_w;                                    // offset 0x20, size 0x4
    int page;                                        // offset 0x24, size 0x4
    int near_sound_num;                              // offset 0x28, size 0x4
    NEAR_SOUND_DATA near_sound_ary[8];               // offset 0x2C, size 0xE0
    int on_num;                                      // offset 0x10C, size 0x4
    char on_chan[7];                                 // offset 0x110, size 0x7
    int absNum;                                      // offset 0x118, size 0x4
    int nearindex;                                   // offset 0x11C, size 0x4
} SOUND_WORK;

void SeWait(int wait);
void SeForceWait(void);
void SeCallInit(int sect, int mmode, char* path);
void SeCallReset(void);
int SeCall(int sd_no, float volume, int stereo);
int SeCallPos(int sd_no, float volume, float* pos, int status);
int SeCallPosChange(int sd_no, float volume, float* pos, int status);
int SeCallPosDirection(float* pos);
int SeCallPosDistance(float volume, float* pos);
float SeCallPosDistanceF(float* pos);
int Se3dPlayCheck(int sd_no);
void SeSoundLoad(void);
void SeSoundEffectLoad(int data);
void SeSoundEffect3dLoad(int data);
void SeSoundManager(void);
void Se2dManager(void);
void Se2dManageDataVolumeChange(int sd, float vol);
float Se2dManageDataTimer(int sd, int clear);
void Se3dManager(void);
int Se3dControl(int sd_no, float volume, float* pos);
void SeStop(int sd_no);
void SeBgmChange(void);
void SeBgmCall(int bgm_no);
void SeBgmManager(void);
int BgmPageSet(void);
void SeMasterVolumeChange(void);

extern void sd_setpath(char* dp /* r2 */); // M:\select\sound\sd0712\ee\sd_call.c we need to find a home for lil bro

#endif // SH_SOUND_H
