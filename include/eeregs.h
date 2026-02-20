#ifndef EE_REGS_H
#define EE_REGS_H

#define T0_COUNT ((volatile u32 *)(0x10000000))

#define D0_CHCR         ((volatile u_int *)(0x10008000))
#define D0_MADR         ((volatile u_int *)(0x10008010))
#define D0_QWC          ((volatile u_int *)(0x10008020))
#define D0_TADR         ((volatile u_int *)(0x10008030))
#define D0_ASR0         ((volatile u_int *)(0x10008040))
#define D0_ASR1         ((volatile u_int *)(0x10008050))

#endif EE_REGS_H
