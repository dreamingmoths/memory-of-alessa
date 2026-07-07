#ifndef DEMOVIEW_H
#define DEMOVIEW_H

#include "common.h"

#define DRAMA_DEMO_9  0x9
#define DRAMA_DEMO_D  0xD
#define DRAMA_DEMO_E  0xE
#define DRAMA_DEMO_21 0x21
#define DRAMA_DEMO_26 0x26
#define DRAMA_DEMO_2E 0x2E
#define DRAMA_DEMO_41 0x41
#define DRAMA_DEMO_42 0x42
#define DRAMA_DEMO_4A 0x4A
#define DRAMA_DEMO_4E 0x4E

// total size: 0x4
typedef struct DramaDemo_MessageTime {
    // Members
    u_short start; // offset 0x0, size 0x2
    u_short end;   // offset 0x2, size 0x2
} DramaDemo_MessageTime;

// total size: 0x28
typedef struct DramaDemo_PlayInfo {
    // Members
    int demo_no; // offset 0x0, size 0x4
    char* adr_dds_top; // offset 0x4, size 0x4
    short* adr_anim; // offset 0x8, size 0x4
    DramaDemo_MessageTime * adr_msg_time; // offset 0xC, size 0x4
    short msg_start; // offset 0x10, size 0x2
    short voice_sd_no; // offset 0x12, size 0x2
    int* adr_voice; // offset 0x14, size 0x4
    int stream_no; // offset 0x18, size 0x4
    float stream_start; // offset 0x1C, size 0x4
    float add_pos_x; // offset 0x20, size 0x4
    float add_pos_z; // offset 0x24, size 0x4
} DramaDemo_PlayInfo;

int DramaDemoMain(DramaDemo_PlayInfo* info);
void DramaDemoSkipLast(DramaDemo_PlayInfo* info);
void DramaDemoFade(void);
// int DramaDemoNumber(void); // @note: uncommenting this gives a mismatch // @todo: find a fix
void SubtitlesExec(DramaDemo_MessageTime* msg_time, int msg_no, int str_no, float timer);
void SubtitlesManager(void);

extern int sbt_msg_no;
extern DramaDemo_MessageTime* sbt_msg_time;
extern int sbt_str_no;
extern int demo_status;
extern float demo_frame; // size: 0x4, address: 0x1133C20
extern float total_demo_frame;

extern int demo_number;

extern u_short msg_buffer[];

#endif // DEMOVIEW_H
