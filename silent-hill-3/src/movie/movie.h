#ifndef MOVIE_H
#define MOVIE_H

#include "libcdvd.h"
#include "eekernel.h"

#define min(x, y) (((x) > (y))? (y): (x))
#define max(x, y) (((x) < (y))? (y): (x))

typedef struct {
	int play_event_no;
	int play_event_sta;
} MOVIE_WRK;

typedef union {
    u_long128 q;
    u_long l[2];
    u_int i[4];
    u_short s[8];
    u_char c[16];
} QWORD;

typedef struct {
    int isOnCD;
    int size;
    sceCdlFILE fp;
    u_char *iopBuf;
    int fd;
} StrFile;

extern u_int scene_bg_color;
extern MOVIE_WRK movie_wrk;
extern int thread_id;
extern u_int controller_val;
extern int videoDecTh;
extern int frd;
extern int play_mov_no;



#endif