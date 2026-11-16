#ifndef LIB_WPRTFSRC_H
#define LIB_WPRTFSRC_H

typedef int print_t(const char* format, ...);

int PollSemaAll(int sid);

int SignalSemaLimit(int sid);

int iSignalSemaLimit(int sid);

int CreateThread2(void (*entry)(void*), void* stack, int stackSize, int prio, u_int option);

int CreateSema2(int init, int max, const s_char* option);

int shPollSemaAll(int sid);

int shSignalSemaLimit(int sid);

int ishSignalSemaLimit(int sid);

int shCreateThread2(void (*entry)(void*), void* stack, int stackSize, int prio, u_int option);

int shCreateSema2(int init, int max, u_int option);

int iReleaseSema(int sid);

int ishReleaseSema(int sid);

void SignalSemaMax(int sid);

void shSignalSemaMax(int sid);

void printf_init(void* buf_addr, int buf_size, int help);

char* swap_printf_buf(void);

void printf_skip(int skip);

print_t printf_sub;

void printf_enable(void);

print_t printf;

#endif // LIB_wprtfsrc_H
