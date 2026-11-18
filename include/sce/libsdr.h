#ifndef LIB_SDR_H
#define LIB_SDR_H

extern int sceSdRemoteInit( void );
extern int sceSdRemote(int arg, ...);
extern int sceSdRemoteCallbackInit(int priority);
extern int sceSdTransToIOP(void *buff, u_int sendAddr, u_int size, u_int isBlock);

#endif // LIB_SDR_H
