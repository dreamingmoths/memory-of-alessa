#ifndef PSS_MAIN_H
#define PSS_MAIN_H

void pssSystemColdInit(void);

void pssSetWorkAddress(void* p0, void* p1, void* p2, void* p3, void* p4, void* p5);

void pssInit(void);

void pssExit(void);

int pssSetControlData(int ctrl, union fsFileIndex* id, int frame);

int pssMain(void);

void switchThread(void);

int pssGetPssStatus(void);

int pssGetPssAbortFlag(void);

int pssGetMaskSwitch(void);

void pssSetMaskSwitch(int flg);

void pssCheckMovieCancel(void);

void pssSetSubTitleData(u_short* msg_bufp, void* adr_msg_time, int msg_start);

void ErrMessage(char* message);

void proceedAudio(void);

#endif // PSS_MAIN_H
