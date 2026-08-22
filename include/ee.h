#ifndef ALESSA_EMOTION_ENGINE_H
#define ALESSA_EMOTION_ENGINE_H

#define DMArefe (0<<28)
#define DMAcnt  (1<<28)
#define DMAnext (2<<28)
#define DMAref  (3<<28)
#define DMArefs (4<<28)
#define DMAcall (5<<28)
#define DMAret  (6<<28)
#define DMAend  (7<<28)

#define UNCACHED(p) ((char*)((u_int)p | 0x20000000))
#define READ_UNCACHED(addr) ((((u_int)(addr)) & 0x0fffffff) | 0x20000000)
#define UNCACHED_POINTER(addr) ((void*) ((((u_int)(addr)) & 0x0fffffff) | 0x20000000))
#define MAIN_RAM_POINTER(addr) ((void*) (((u_int)(addr)) & 0x0fffffff))

#define SCRATCHPAD_START 0x70000000

#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

#endif // ALESSA_EMOTION_ENGINE_H
