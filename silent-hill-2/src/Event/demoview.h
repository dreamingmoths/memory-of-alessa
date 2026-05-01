#ifndef DEMOVIEW_H
#define DEMOVIEW_H

#include "common.h"

// total size: 0x4
typedef struct DramaDemo_MessageTime {
    // Members
    u_short start; // offset 0x0, size 0x2
    u_short end; // offset 0x2, size 0x2
} DramaDemo_MessageTime;

extern int sbt_msg_no;
extern DramaDemo_MessageTime* sbt_msg_time;
extern int sbt_str_no;
extern int demo_status;
extern u_short msg_buffer[];

#endif // DEMOVIEW_H
