#ifndef MOVIE_MAIN_H
#define MOVIE_MAIN_H

#include "sh2_common.h"

void movieSetSubTitleData(u_short* msg_bufp, void* adr_msg_time, int msg_start);
void MoviePreSet(union fsFileIndex* id);
void MovieTitlePreSet(union fsFileIndex* id);
void MovieInit(void);
int MovieMain(void);
int MovieWaitReady(void);
void MoviePlayFromReady(void);
int MovieCheckSleep(void);
int MoviePlayOPMovie(void);
int movieGetLastExitStatus(void);

#endif // MOVIE_MAIN_H
