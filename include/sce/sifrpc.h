#ifndef SIFRPC_H
#define SIFRPC_H

#define SIF_RPCM_NOWAIT		0x01	// execute asynchronously
#define SIF_RPCM_NOWBDC		0x02	/* don't write back to d-cache */

typedef struct _sif_rpc_data {
    void* paddr;       /* packet address */
    unsigned int pid;  /* packet id */
    int tid;           /* thread id */
    unsigned int mode; /* call mode */
} sceSifRpcData;

typedef void (*sceSifEndFunc)(void*);

typedef struct _sif_client_data {
    struct _sif_rpc_data rpcd;
    unsigned int command;
    void* buff;
    void* cbuff;
    sceSifEndFunc func;
    void* para;
    struct _sif_serve_data* serve;
} sceSifClientData;

typedef struct _sif_receive_data {
    struct _sif_rpc_data rpcd;
    void* src;
    void* dest;
    int size;
} sceSifReceiveData;

typedef void* (*sceSifRpcFunc)(unsigned int, void*, int);

typedef struct _sif_serve_data {
    unsigned int command;
    sceSifRpcFunc func;
    void* buff;
    int size;
    sceSifRpcFunc cfunc;
    void* cbuff;
    int csize;
    sceSifClientData* client;
    void* paddr;
    unsigned int fno;
    void* receive;
    int rsize;
    int rmode;
    unsigned int rid;
    struct _sif_serve_data* link;
    struct _sif_serve_data* next;
    struct _sif_queue_data* base;
} sceSifServeData;

typedef struct _sif_queue_data {
    int key;
    int active;
    struct _sif_serve_data* link;
    struct _sif_serve_data* start;
    struct _sif_serve_data* end;
    struct _sif_queue_data* next;
} sceSifQueueData;

void sceSifInitRpc(u_int mode);
int sceSifBindRpc(sceSifClientData*, u_int, u_int);
int sceSifCallRpc(sceSifClientData*, u_int, u_int, void*, int, void*, int, sceSifEndFunc, void*);
int sceSifCheckStatRpc(sceSifRpcData*);

#endif // SIFRPC_H
