// SDK video playback sample code.
// all credits to https://github.com/Mikompilation/Himuro/blob/828c49053f0d0a67694ae678463dfa3b770b6ef3/include/sce/mpeg/vibuf.h

#ifndef PSS_VIBUF_H
#define PSS_VIBUF_H

#include "libipu.h"
#include "mpeg/vibuf.h"
#include "mpeg/defs.h"
#include "common.h"
#include "eeregs.h"
#include "movie.h"
#include "eekernel.h"

int getFIFOindex(ViBuf *f, void *addr);
void setD3_CHCR(u_int val);
void setD4_CHCR(u_int val);
void scTag2(QWORD *q, void *addr, u_int id, u_int qwc);
int viBufCreate(ViBuf *f, u_long128 *data, u_long128 *tag, int size, TimeStamp *ts, int n_ts);
int viBufReset(ViBuf *f);
void viBufBeginPut(ViBuf *f, u_char **ptr0, int *len0, u_char **ptr1, int *len1);
void viBufEndPut(ViBuf *f, int size);
int viBufAddDMA(ViBuf *f);
int viBufStopDMA(ViBuf *f);
int viBufRestartDMA(ViBuf *f);
int viBufDelete(ViBuf *f);
int viBufIsActive(ViBuf *f);
int viBufCount(ViBuf *f);
void viBufFlush(ViBuf *f);
int viBufModifyPts(ViBuf *f, TimeStamp *new_ts);
int viBufPutTs(ViBuf *f, TimeStamp *ts);
int viBufGetTs(ViBuf *f, TimeStamp *ts);

#endif // PSS_VIBUF_H
