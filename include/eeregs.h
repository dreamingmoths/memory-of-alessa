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

#define D1_CHCR         ((volatile u_int *)(0x10009000))
#define D1_MADR         ((volatile u_int *)(0x10009010))
#define D1_QWC          ((volatile u_int *)(0x10009020))
#define D1_TADR         ((volatile u_int *)(0x10009030))
#define D1_ASR0         ((volatile u_int *)(0x10009040))
#define D1_ASR1         ((volatile u_int *)(0x10009050))

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

/* GS Special */
#define GS_PMODE        ((volatile u_long *)(0x12000000))
#define GS_SMODE2       ((volatile u_long *)(0x12000020))
#define GS_DISPFB1      ((volatile u_long *)(0x12000070))
#define GS_DISPLAY1     ((volatile u_long *)(0x12000080))
#define GS_DISPFB2      ((volatile u_long *)(0x12000090))
#define GS_DISPLAY2     ((volatile u_long *)(0x120000a0))
#define GS_EXTBUF       ((volatile u_long *)(0x120000b0))
#define GS_EXTDATA      ((volatile u_long *)(0x120000c0))
#define GS_EXTWRITE     ((volatile u_long *)(0x120000d0))
#define GS_BGCOLOR      ((volatile u_long *)(0x120000e0))
#define GS_CSR          ((volatile u_long *)(0x12001000))
#define GS_IMR          ((volatile u_long *)(0x12001010))
#define GS_BUSDIR       ((volatile u_long *)(0x12001040))
#define GS_SIGLBLID     ((volatile u_long *)(0x12001080))

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
    unsigned DIR : 1; // Direction
    unsigned p0 : 1;
    unsigned MOD : 2; // Mode
    unsigned ASP : 2; // Address stack pointer
    unsigned TTE : 1; // Tag trasfer enable
    unsigned TIE : 1; // Tag interrupt enable
    unsigned STR : 1; // start
    unsigned p1 : 7;
    unsigned TAG : 16; // DMAtag
} tD_CHCR;

/*
 * GS_PMODE
 *  63            56              48              40              32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  31            24              16               8               0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                               |               |S|A|M|     |E|E|
 * |                               |       ALP     |L|M|M|CRTMD|N|N|
 * |                               |               |B|O|O|     |2|1|
 * |                               |               |G|D|D|     | | |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * bit definition
 */
#define GS_PMODE_EN1_M      (0x01 << 0)
#define GS_PMODE_EN2_M      (0x01 << 1)
#define GS_PMODE_CRTMD_M    (0x07 << 2)
#define GS_PMODE_MMOD_M     (0x01 << 5)
#define GS_PMODE_AMOD_M     (0x01 << 6)
#define GS_PMODE_SLBG_M     (0x01 << 7)
#define GS_PMODE_ALP_M      (0xff << 8)

#define GS_PMODE_EN1_O      ( 0)
#define GS_PMODE_EN2_O      ( 1)
#define GS_PMODE_CRTMD_O    ( 2)
#define GS_PMODE_MMOD_O     ( 5)
#define GS_PMODE_AMOD_O     ( 6)
#define GS_PMODE_SLBG_O     ( 7)
#define GS_PMODE_ALP_O      ( 8)

/*
 * Bitfield Structure
 */
typedef struct {
    unsigned EN1     : 1;   /* */
    unsigned EN2     : 1;   /* */
    unsigned CRTMD   : 3;   /* CRT mode */
    unsigned MMOD    : 1;   /* */
    unsigned AMOD    : 1;   /* */
    unsigned SLBG    : 1;   /* */
    unsigned ALP     : 8;   /* */
    unsigned p0      :16;   /* */
    unsigned int p1;    
} tGS_PMODE;


/*
 * GS_SMODE2
 *  63            56              48              40              32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  31            24              16               8               0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                       | D |F|I|
 * |                                                       | P |F|N|
 * |                                                       | M |M|T|
 * |                                                       | S |D| |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * bit definition
 */
#define GS_SMODE2_INT_M     (0x01 << 0)
#define GS_SMODE2_FFMD_M    (0x01 << 1)


#define GS_SMODE2_DPMS_M    (0x03 << 2)

#define GS_SMODE2_INT_O     ( 0)
#define GS_SMODE2_FFMD_O    ( 1)
#define GS_SMODE2_DPMS_O    ( 2)

/*
 * Bitfield Structure
 */
typedef struct {
    unsigned INT  : 1;  /* Interlace mode */
    unsigned FFMD : 1;  /* */
    unsigned DPMS : 2;  /* VESA DPMS mode */
    unsigned p0   :28;  /* */
    unsigned int p1;
} tGS_SMODE2;


/*
 * GS_DISPFB2
 *  63            56              48              40              32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                   |                     |                     |
 * |                   |        DBY          |         DBX         |
 * |                   |                     |                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  31            24              16               8               0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                       |         |           |                 |
 * |                       |   PSM   |     FBW   |      FBP        |
 * |                       |         |           |                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * bit definition
 */
#define GS_DISPFB2_FBP_M    (0x1ff << 0)
#define GS_DISPFB2_FBW_M    (0x3f  << 9)
#define GS_DISPFB2_PSM_M    (0x1f  <<15)
#define GS_DISPFB2_DBX_M    (0x7ffL<<32)
#define GS_DISPFB2_DBY_M    (0x7ffL<<43)

#define GS_DISPFB2_FBP_O    ( 0)
#define GS_DISPFB2_FBW_O    ( 9)
#define GS_DISPFB2_PSM_O    (15)
#define GS_DISPFB2_DBX_O    (32)
#define GS_DISPFB2_DBY_O    (43)


/*
 * Bitfield Structure
 */
typedef struct {
    unsigned FBP: 9;    /* Base pointer */
    unsigned FBW: 6;    /* Buffer width */
    unsigned PSM: 5;    /* Pixel store mode */
    unsigned p0 :12;
    unsigned DBX:11;    /* */
    unsigned DBY:11;    /* */
    unsigned p1 :10;
} tGS_DISPFB2;


/*
 * GS_DISPLAY2
 *  63            56              48              40              32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                 |                     |                       |
 * |                 |        DH           |         DW            |
 * |                 |                     |                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  31            24              16               8               0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |     |MA |       |                     |                       |
 * |     | GV|  MAGH |        DY           |          DX           |
 * |     |   |       |                     |                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * bit definition
 */
#define GS_DISPLAY2_DX_M    (0xfff << 0)
#define GS_DISPLAY2_DY_M    (0x7ff <<12)
#define GS_DISPLAY2_MAGH_M  (0x0f  <<23)
#define GS_DISPLAY2_MAGV_M  (0x03  <<27)
#define GS_DISPLAY2_DW_M    (0xfffL<<32)
#define GS_DISPLAY2_DH_M    (0x7ffL<<44)

#define GS_DISPLAY2_DX_O    ( 0)
#define GS_DISPLAY2_DY_O    (12)
#define GS_DISPLAY2_MAGH_O  (23)
#define GS_DISPLAY2_MAGV_O  (27)
#define GS_DISPLAY2_DW_O    (32)
#define GS_DISPLAY2_DH_O    (44)


/*
 * Bitfield Structure
 */
typedef struct {
    unsigned DX  :12;   /* */
    unsigned DY  :11;   /* */
    unsigned MAGH: 4;   /* */
    unsigned MAGV: 2;   /* */
    unsigned p0  : 3;
    unsigned DW  :12;   /* */
    unsigned DH  :11;   /* */
    unsigned p1  : 9;
} tGS_DISPLAY2;

/*
 * GS_BGCOLOR
 *  63            56              48              40              32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  31            24              16               8               0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               |               |               |               |
 * |               |       B       |       G       |       R       |
 * |               |               |               |               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * bit definition
 */
#define GS_BGCOLOR_R_M      (0xff<< 0)
#define GS_BGCOLOR_G_M      (0xff<< 8)
#define GS_BGCOLOR_B_M      (0xff<<16)

#define GS_BGCOLOR_R_O      ( 0)
#define GS_BGCOLOR_G_O      ( 8)
#define GS_BGCOLOR_B_O      (16)


/*
 * Bitfield Structure
 */
typedef struct {
    unsigned R : 8;     /* Background color Bulue */
    unsigned G : 8;     /* Background color Green */
    unsigned B : 8;     /* Background color Red */
    unsigned p0: 8;
    unsigned int p1;
} tGS_BGCOLOR;


/*
 * GS_CSR
 *  63            56              48              40              32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  31            24              16               8               0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               |               | F |F|N|   |R|F| | | |E|V|H|F|S|
 * |               |               | I |I|F|   |E|L| | | |D|S|S|I|I|
 * |     ID        |     REV       | F |E|I|   |S|U| |0|0|W|I|I|N|G|
 * |               |               | O |L|E|   |E|S| | | |I|N|N|I|N|
 * |               |               |   |D|L|   |T|H| | | |N|T|T|S|A|
 * |               |               |   | |D|   | | | | | |T| | |H|L|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * bit definition
 */
#define GS_CSR_SIGNAL_M     (0x01<< 0)
#define GS_CSR_FINISH_M     (0x01<< 1)
#define GS_CSR_HSINT_M      (0x01<< 2)
#define GS_CSR_VSINT_M      (0x01<< 3)
#define GS_CSR_EDWINT_M     (0x01<< 4)
#define GS_CSR_FLUSH_M      (0x01<< 8)
#define GS_CSR_RESET_M      (0x01<< 9)
#define GS_CSR_NFIELD_M     (0x01<<12)
#define GS_CSR_FIELD_M      (0x01<<13)
#define GS_CSR_FIFO_M       (0x03<<14)
#define GS_CSR_REV_M        (0xff<<16)
#define GS_CSR_ID_M         (0xff<<24)

#define GS_CSR_SIGNAL_O     ( 0)
#define GS_CSR_FINISH_O     ( 1)
#define GS_CSR_HSINT_O      ( 2)
#define GS_CSR_VSINT_O      ( 3)
#define GS_CSR_EDWINT_O     ( 4)
#define GS_CSR_FLUSH_O      ( 8)
#define GS_CSR_RESET_O      ( 9)
#define GS_CSR_NFIELD_O     (12)
#define GS_CSR_FIELD_O      (13)
#define GS_CSR_FIFO_O       (14)
#define GS_CSR_REV_O        (16)
#define GS_CSR_ID_O         (24)

/*
 * Bitfield Structure
 */
typedef struct {
    unsigned SIGNAL : 1;    /* SIGNAL event */
    unsigned FINISH : 1;    /* FINISH event */
    unsigned HSINT  : 1;    /* HSync interrupt */
    unsigned VSINT  : 1;    /* VSync interrupt */
    unsigned EDWINT : 1;    /* */
    unsigned p0     : 3;
    unsigned FLUSH  : 1;    /* */
    unsigned RESET  : 1;    /* GS system reset */
    unsigned p1     : 2;
    unsigned NFIELD : 1;    /* NFIELD output */
    unsigned FIELD  : 1;    /* */
    unsigned FIFO   : 2;    /* Host interface FIFO status */
    unsigned REV    : 8;    /* GS revision number */
    unsigned ID     : 8;    /* GS ID */
    unsigned int p2;
} tGS_CSR;

#endif EE_REGS_H
