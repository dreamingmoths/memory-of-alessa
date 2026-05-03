#ifndef EE_REGS_H
#define EE_REGS_H

/* TIMER */
#define T0_COUNT          ((volatile u_int *)(0x10000000))
#define T0_MODE           ((volatile u_int *)(0x10000010))
#define T0_COMP           ((volatile u_int *)(0x10000020))
#define T0_HOLD           ((volatile u_int *)(0x10000030))
#define T1_COUNT          ((volatile u_int *)(0x10000800))
#define T1_MODE           ((volatile u_int *)(0x10000810))
#define T1_COMP           ((volatile u_int *)(0x10000820))
#define T1_HOLD           ((volatile u_int *)(0x10000830))
#define T2_COUNT          ((volatile u_int *)(0x10001000))
#define T2_MODE           ((volatile u_int *)(0x10001010))
#define T2_COMP           ((volatile u_int *)(0x10001020))
#define T3_COUNT          ((volatile u_int *)(0x10001800))
#define T3_MODE           ((volatile u_int *)(0x10001810))
#define T3_COMP           ((volatile u_int *)(0x10001820))

#define D0_CHCR  		  ((volatile u_int *)(0x10008000))
#define D0_MADR  		  ((volatile u_int *)(0x10008010))
#define D0_QWC   		  ((volatile u_int *)(0x10008020))
#define D0_TADR  		  ((volatile u_int *)(0x10008030))
#define D0_ASR0  		  ((volatile u_int *)(0x10008040))
#define D0_ASR1  		  ((volatile u_int *)(0x10008050))

#define D_ENABLER         ((volatile u_int *)(0x1000f520))
#define D_ENABLEW         ((volatile u_int *)(0x1000f590))
#define D3_CHCR           ((volatile u_int *)(0x1000b000))
#define D4_CHCR           ((volatile u_int *)(0x1000b400))

#define D3_CHCR           ((volatile u_int *)(0x1000b000))
#define D3_MADR           ((volatile u_int *)(0x1000b010))
#define D3_QWC            ((volatile u_int *)(0x1000b020))

#define D4_CHCR           ((volatile u_int *)(0x1000b400))
#define D4_MADR           ((volatile u_int *)(0x1000b410))
#define D4_QWC            ((volatile u_int *)(0x1000b420))
#define D4_TADR           ((volatile u_int *)(0x1000b430))

/* VU0 */
#define VU0_MICRO         ((volatile u_long *)(0x11000000))
#define VU0_MEM           ((volatile u_long128 *)(0x11004000))

/* VU1 */
#define VU1_MICRO         ((volatile u_long *)(0x11008000))
#define VU1_MEM           ((volatile u_long128 *)(0x1100c000))

/* IPU */
#define IPU_CMD           ((volatile u_int *)(0x10002000))
#define IPU_CTRL          ((volatile u_int *)(0x10002010))
#define IPU_BP            ((volatile u_int *)(0x10002020))

#define DGET_IPU_CTRL()   (*IPU_CTRL)
#define DPUT_IPU_CMD(x)   (*IPU_CMD = (x))

#define DGET_IPU_CTRL()   (*IPU_CTRL)
#define DGET_IPU_BP()     (*IPU_BP)

//
// Bitfield Structure
//
typedef struct {
	unsigned DIR: 1;	// Direction
	unsigned p0 : 1;
	unsigned MOD: 2;	// Mode
	unsigned ASP: 2;	// Address stack pointer
	unsigned TTE: 1;	// Tag trasfer enable
	unsigned TIE: 1;	// Tag interrupt enable
	unsigned STR: 1;	// start
	unsigned p1 : 7;
	unsigned TAG:16;	// DMAtag
} tD_CHCR;

#endif EE_REGS_H
