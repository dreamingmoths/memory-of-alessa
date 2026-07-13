#ifndef PSS_READBUF_H
#define PSS_READBUF_H

#include "sce/eetypes.h"

#define READ_UNIT_SIZE (64*1024)
#define N_READ_UNIT     5

// ////////////////////////////////////////////////////////////////
//
// Read buffer
//
typedef struct {
    u_char data[N_READ_UNIT * READ_UNIT_SIZE];
    int put;
    int count;
    int size;
} ReadBuf;

// ////////////////////////////////////////////////////////////////
//
// Functions
//
void readBufCreate(ReadBuf *buff);
void readBufDelete(ReadBuf *buff);
int readBufBeginPut(ReadBuf *buff, u_char **ptr);
int readBufEndPut(ReadBuf *buff, int size);
int readBufBeginGet(ReadBuf *buff, u_char **ptr);
int readBufEndGet(ReadBuf *buff, int size);

#endif // PSS_READBUF_H
