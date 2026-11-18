#include "sound/sd0712/ee/sd_call.h"
#include "sce/sifrpc.h"
#include "sce/sifdev.h"
#include "sce/libsdr.h"
#include "sce/sdrcmd.h"
#include "sce/sdmacro.h"

#define TRANS_CHANNEL 1

extern void* malloc(int); //@note: if not defined, compiler will assume return type of int :/

static void sd_sendpath(void);

static int SdSifInit(void);

static int SdSifCall(int n, int ssize, int rsize);

static void SdSifRet(void*);

static int Sd3dInit(void);

static void Sd3dSteMono(int mode);

static void Sd3dMode(int pmode);

static int Sd3dMalloc(void);

static void Sd3dExec(void);

static void Sd3dSetMVol(int vol);

static int Sd3dPrePlay(int call, int arg1, int arg2, float arg3, float arg4);

static void Sd3dPlay(int call, int arg1, int arg2, float arg3, float arg4, int no);

enum SD_CALL_CALLS {
    SD_CALL_INIT    = 1000,
    SD_3D_MONO_ON   = 1005,
    SD_3D_MONO_OFF  = 1006,
    SD_3D_MODE_OFF  = 1041,
    SD_3D_MODE_ON   = 1040,
    SD_3D_SET_VOL   = 1025,
};

static int dpath = 0; // size: 0x4, address: 0x1013B90
static int sdsif_rdata[64]; // size: 0x100, address: 0x10E0380
static int sdsif_idata[64] __attribute__(( aligned(64) )); // size: 0x100, address: 0x10E0280
static u_char sd_stat_core0[24]; // size: 0x18, address: 0x10E0230
static u_char sd_stat_core1[24]; // size: 0x18, address: 0x10E0210
static sceSifClientData sdsif_bd; // size: 0x28, address: 0x10E01E0
static int sd_str_status[2]; // size: 0x8, address: 0x10E01D0
static int sd_read_status; // size: 0x4, address: 0x10E01C8
volatile static int sd_stat_timer; // size: 0x4, address: 0x10E01C0
static SdCallData sd_call_data[64]; // size: 0x400, address: 0x10DFDC0
volatile static int sd_que; // size: 0x4, address: 0x10DFDB0
static int se_mvol; // size: 0x4, address: 0x10DFDA8
static int gDataTopAddr; // size: 0x4, address: 0x10DFDA0
static int gcount; // size: 0x4, address: 0x10DFD98
static int idout; // size: 0x4, address: 0x10DFD90
static u_char* gDataIOPPtr[2]; // size: 0x8, address: 0x10DFD88
static int se_stemono; // size: 0x4, address: 0x10DFD80
static SdEnv env3d[8]; // size: 0x100, address: 0x10DFC80
static SdEnv dmy_env; // size: 0x20, address: 0x10DFC60
static SdEnvBuf out_buf_env; // size: 0x10, address: 0x10DFC50
static SdEnvBuf in_buf_env[8]; // size: 0x80, address: 0x10DFBD0
static SdEnvBuf dmy_buf_env; // size: 0x10, address: 0x10DFBC0
static short ibuf[409600] __attribute__(( aligned(64) )); // size: 0xC8000, address: 0x1017BC0
static short obuf[8192]; // size: 0x4000, address: 0x1013BA0

static Sd3dDataStruct Sd3dData[258] = { // size: 0x2040, address: 0x2B6530,
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 149110,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 149120,
        /* .size = */ 15984,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 165104,
        /* .size = */ 56402,
        /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 221520,
        /* .size = */ 44738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 266272,
        /* .size = */ 49708,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 315984,
        /* .size = */ 87876,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 403872,
        /* .size = */ 101826,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 123068,
        /* .sr = */ 44100,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 123072,
        /* .size = */ 73076,
        /* .sr = */ 44100,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 196160,
        /* .size = */ 49602,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 245776,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 271120,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 287104,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 343520,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 388272,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 437984,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 525872,
         /* .size = */ 101826,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 69980,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 69984,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 95328,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 111312,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 167728,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 212480,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 262192,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 350080,
         /* .size = */ 101826,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 25344,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 41328,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 97744,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 172288,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 214896,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 280048,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 327712,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 387856,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 25344,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 70096,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 119808,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 207696,
         /* .size = */ 101826,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 309536,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 384080,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 426688,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 491840,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 539504,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 182600,
         /* .sr = */ 44100,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 182608,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 207952,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 223936,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 15984,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 72400,
         /* .size = */ 122620,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 195024,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 239776,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 289488,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 377376,
        /* .size = */ 101826,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 158026,
        /* .sr = */ 16820,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 158032,
        /* .size = */ 15984,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 174016,
        /* .size = */ 56402,
        /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 230432,
        /* .size = */ 122620,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 353056,
        /* .size = */ 44738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 397808,
        /* .size = */ 49708,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 447520,
        /* .size = */ 87876,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 535408,
        /* .size = */ 101826,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 16406,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 77338,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 77344,
        /* .size = */ 74038,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 151392,
        /* .size = */ 69296,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 220688,
        /* .size = */ 61966,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 282656,
        /* .size = */ 185216,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 15744,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 54000,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 85952,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 160496,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 203104,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 268256,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 315920,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 376064,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 25344,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 41088,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 79344,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 111296,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 185840,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 228448,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 293600,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 341264,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 401408,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 15744,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 54000,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 85952,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 160496,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 203104,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 268256,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 315920,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 376064,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 25344,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 41088,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 79344,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 111296,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 185840,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 228448,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 293600,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 341264,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 401408,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 159596,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 159600,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 175344,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 213600,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 245552,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 320096,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 362704,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 427856,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 475520,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 535664,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 25344,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 41088,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 79344,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 111296,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 185840,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 228448,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 293600,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 341264,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 401408,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 72680,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 72688,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 88432,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 126688,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 158640,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 233184,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 275792,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 340944,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 388608,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 448752,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 74544,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 117152,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 182304,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 229968,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 290112,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 25344,
        /* .size = */ 15738,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 41088,
        /* .size = */ 38252,
        /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 79344,
        /* .size = */ 31946,
        /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 111296,
        /* .size = */ 74530,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 185840,
        /* .size = */ 42604,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 228448,
        /* .size = */ 65138,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 293600,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 341264,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 401408,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 16238,
        /* .sr = */ 20000,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 16240,
        /* .size = */ 20154,
        /* .sr = */ 20000,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 36400,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 61744,
        /* .size = */ 47654,
        /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 109408,
        /* .size = */ 60134,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 169552,
        /* .size = */ 103000,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 0,
        /* .size = */ 25336,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
        /* .ofst = */ 25344,
        /* .size = */ 35312,
        /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 60656,
         /* .size = */ 77896,
         /* .sr = */ 15250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 25344,
         /* .size = */ 35312,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 60656,
         /* .size = */ 77896,
         /* .sr = */ 15250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 127454,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 127456,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 152800,
         /* .size = */ 35312,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 188112,
         /* .size = */ 77896,
         /* .sr = */ 15250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 266016,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 313680,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 373824,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 145680,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 25344,
         /* .size = */ 35312,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 60656,
         /* .size = */ 77896,
         /* .sr = */ 15250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 84626,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 84640,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 109984,
         /* .size = */ 35312,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 145296,
         /* .size = */ 77896,
         /* .sr = */ 15250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 51496,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 51504,
         /* .size = */ 112892,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 164400,
         /* .size = */ 185216,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 15984,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 72400,
         /* .size = */ 35312,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 107712,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 182256,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 224864,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 290016,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 337680,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 397824,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 81842,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 81856,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 97840,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 154256,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 228800,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 271408,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 336560,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 384224,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 444368,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 16238,
         /* .sr = */ 20000,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 16240,
         /* .size = */ 20154,
         /* .sr = */ 20000,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 36400,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 52384,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 108800,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 153552,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 203264,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 291152,
         /* .size = */ 101826,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 15984,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 72400,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 117152,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 166864,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 254752,
         /* .size = */ 101826,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 356592,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 431136,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 473744,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 538896,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 586560,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 15984,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 72400,
         /* .size = */ 44738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 117152,
         /* .size = */ 49708,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 166864,
         /* .size = */ 87876,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 254752,
         /* .size = */ 101826,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 25344,
         /* .size = */ 33788,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 59136,
         /* .size = */ 15738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 74880,
         /* .size = */ 38252,
         /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 113136,
         /* .size = */ 31946,
         /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 145088,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 219632,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 262240,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 327392,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 375056,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 435200,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 25336,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 25344,
         /* .size = */ 33788,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 59136,
         /* .size = */ 15984,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 75120,
         /* .size = */ 56402,
         /* .sr = */ 15682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 131536,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 206080,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 248688,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 313840,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 361504,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 421648,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 0,
         /* .size = */ 16238,
         /* .sr = */ 20000,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 16240,
         /* .size = */ 20154,
         /* .sr = */ 20000,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 36400,
         /* .size = */ 15738,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 52144,
         /* .size = */ 38252,
         /* .sr = */ 11050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 90400,
         /* .size = */ 31946,
         /* .sr = */ 18250,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 122352,
         /* .size = */ 74530,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 196896,
         /* .size = */ 42604,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 239504,
         /* .size = */ 65138,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 304656,
         /* .size = */ 47654,
         /* .sr = */ 25682,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 352320,
         /* .size = */ 60134,
         /* .sr = */ 22050,
    },
    {
        /* .loop = */ 0,
         /* .ofst = */ 412464,
         /* .size = */ 103000,
         /* .sr = */ 22050,
    }
};

int sd_call(int call, int direct, int dist, int pitch) {
    static int sdinitflag; // @ 0x01013B98




    switch (call) {
        case SD_CALL_INIT:

            if (!sdinitflag) {

                sd_que = -1;
                Sd3dInit();
                SdSifInit();
                sdinitflag = true;
                sd_str_status[0] = 0;
                sd_str_status[1] = 0;
                sd_read_status   = 15;
                if (dpath) sd_sendpath();
            }
            break;
        case SD_3D_MONO_ON:
            Sd3dSteMono(1);
            break;
        case SD_3D_MONO_OFF:
            Sd3dSteMono(0);
            break;
        case SD_3D_MODE_OFF:
            Sd3dMode(0);
            break;
        case SD_3D_MODE_ON:
            Sd3dMode(1);
            break;
        case SD_3D_SET_VOL:
            Sd3dSetMVol(direct);
            break;
        default:
            if ((call >= 60000) && (call < 60087)) {

                sd_str_status[0] = 2;
                sd_str_status[1] = 2;
                sd_stat_timer = 5;
            }
            if ((call >= 5000) && (call < 5079)) {

                sd_read_status = 1;
                sd_stat_timer = 5;
            }
    }


    if (sd_que < 0x40) {

        sd_que++;
        sd_call_data[sd_que].call = call;
        sd_call_data[sd_que].direct = direct;
        sd_call_data[sd_que].dist = dist;
        sd_call_data[sd_que].pitch = pitch;
        return 0;
    } else {


        return -1;
    }
}





int sd_se_stop(int call) {

    if ((call < 10000) || (call > 19999)) return -2;
    return sd_call(call + 10000, 0, 0, 0);
}






int sd_se_change(int call, int direct, int dist, int pitch) {

    if ((call < 10000) || (call > 19999)) return -2;
    return sd_call(call + 20000, direct, dist, pitch);
}





int sd_track(int track, int vol) {

    return sd_call(1021, track, vol, 0);
}






int sd_radio(int ch, int vol, int pan, int pitch) {

    return sd_call(ch + 1030, vol, pan, pitch);
}








int sd_stat(void) {
    int stat = sd_read_status; // r2
    stat |= sd_str_status[0] << 4;
    stat |= sd_str_status[1] << 8;



    return stat;
}





void sd_setpath(s_char* dp) {
    dpath = 1;
    strcpy(sd_call_data, dp);


}


static void sd_sendpath(void) {
    BLOCK_WHILE(sceSifCheckStatRpc(&sdsif_bd) == 1);

    sceSifCallRpc(&sdsif_bd, 1501, 0, sd_call_data, 256, sdsif_rdata, NULL, SdSifRet, sdsif_idata);










}





void sd_vsync(void) {
    int i; // r16












    if (sd_stat_timer > 0) sd_stat_timer--;

    i = 0;


    while (SdSifCall(sd_que + 1, (sd_que + 1) * 16, 256) == -1) {


        i++;
        if (i >= 600001) break;
    }

    sd_que = -1;
}







static int SdSifInit(void) {
    int i; // r3




    sceSifInitRpc(0);
    while(true) {






        if (sceSifBindRpc(&sdsif_bd, 21, 0) < 0) {



            printf("SoundDrv. bind error\n");

            BLOCK_WHILE(true);
        }
        if (sdsif_bd.serve != NULL) break;
        i = 65536;
        BLOCK_WHILE(i--);
    }
    FlushCache(0);
    return 0;
}





static int SdSifCall(int n, int ssize, int rsize) {



    if (sceSifCheckStatRpc(&sdsif_bd) == 1) return -1;




















    return sceSifCallRpc(&sdsif_bd, n, SIF_RPCM_NOWAIT, sd_call_data, ssize, sdsif_rdata, rsize, SdSifRet, sdsif_idata);
}







static void SdSifRet(void*) {
    int i; // r5
    for (i = 0; i < 24; i++) {

        sd_stat_core0[i] = (&sdsif_rdata[2])[i];
    }
    for (i = 0; i < 24; i++) {

        sd_stat_core1[i] = (&sdsif_rdata[26])[i];
    }


    if (sd_stat_timer <= 0) {
        sd_read_status = sdsif_rdata[1] & 0xF;
        sd_str_status[0] = (sdsif_rdata[1] & 0xF0) >> 4;
        sd_str_status[1] = (sdsif_rdata[1] & 0xF00) >> 8;
    }   }






















































static int Sd3dInit(void) {
    void* gpbuffwork; // r2
    int i; // r16
    int idvs, gCallbackThreadID; // r2
    int trans_flag; // r29+0x2C
    for (i = 0; i < 120; i++) {

        sceGsSyncV(0);
    }

    gcount = 1;
    Sd3dSteMono(1);
    idvs = shdVsInit();


    out_buf_env.base    = obuf;
    out_buf_env.size    = (sizeof(obuf) / sizeof(short)) / 2;
    out_buf_env.pointer = NULL;
    out_buf_env.mode    = 2;


    idout = shdVsOpenOutput(idvs, &out_buf_env);

    dmy_env.minlevel    = 1.0f;
    dmy_env.mode        = 0;
    dmy_buf_env.base    = ibuf;
    dmy_buf_env.size    = sizeof(ibuf)/sizeof(short);
    dmy_buf_env.pointer = NULL;
    dmy_buf_env.mode    = 2;

    for (i = 0; i < 8; i++) {


        env3d[i].angle1   = 0;
        env3d[i].angle2   = 0;
        env3d[i].pitch    = 0.91875f;
        env3d[i].cutoff   = 1.0f;
        env3d[i].level    = 1.0f;
        env3d[i].minlevel = -1.0f;
        env3d[i].pos      = 0;
        env3d[i].mode     = 6;

        in_buf_env[i].base      = ibuf;
        in_buf_env[i].size      = sizeof(ibuf)/sizeof(short);
        in_buf_env[i].pointer   = NULL;
        in_buf_env[i].mode      = 0;
    }

    shdVsSetOutWork(idout, malloc(10240), 5120);



    shdVsOpenInput(idout, &dmy_buf_env, &dmy_env, 0);

    for (i = 0; i < 8; i++) {


        shdVsOpenInput(idout, in_buf_env[i], env3d[i], 0);
    }


    gpbuffwork = malloc(288); //@note: where is this used?








    sceSdRemoteInit();

    gCallbackThreadID = sceSdRemoteCallbackInit(5);

    if (Sd3dMalloc() < 0) {

        printf("Sd3dMalloc Error\n");
        return -1;
    }

    sceSdRemote(1, rSdInit, 0);

    for (i = 0; i < 2; i++) {

        sceSdRemote(1, rSdSetParam, i | SD_P_MVOLL, 0x3FFF);
        sceSdRemote(1, rSdSetParam, i | SD_P_MVOLR, 0x3FFF);
        sceSdRemote(1, rSdSetParam, i | SD_P_MMIX, ~(SD_MMIX_MINEL | SD_MMIX_MINER));
    }



    trans_flag = 0;
    sceSdRemote(1, rSdSetTransIntrHandler, 1, Sd3dExec, &trans_flag);




    sceSdRemote(1, rSdBlockTrans, 1, SD_BLOCK_LOOP, gDataTopAddr, 0x8000);

    sceSdRemote(1, rSdSetParam, TRANS_CHANNEL | SD_P_BVOLL, 0x3FFF);
    sceSdRemote(1, rSdSetParam, TRANS_CHANNEL | SD_P_BVOLR, 0x3FFF);

    Sd3dMode(0);
    Sd3dSetMVol(127);

    return 0;
}



static void Sd3dSteMono(int mode) {
    se_stemono = mode;
}



static void Sd3dMode(int pmode) {
    shdVsSetPlayMode(pmode);
}



static int Sd3dMalloc(void) {
    sceSifInitIopHeap();
    gDataTopAddr = (u_int)sceSifAllocIopHeap(0x8000);

    if (gDataTopAddr < 0) {

        printf("\nCan't alloc heap \n");
        return -1;
    }
    gDataIOPPtr[0] = (u_char*) gDataTopAddr;
    gDataIOPPtr[1] = gDataIOPPtr[0] + 0x4000;

    memset(obuf, 0, sizeof(obuf));

    sceSdTransToIOP(obuf, (u_int)gDataIOPPtr[0], sizeof(obuf), 1);

    sceSdTransToIOP(obuf, (u_int)gDataIOPPtr[1], sizeof(obuf), 1);


    return 1;
}





static void Sd3dExec(void) {
    gcount ^= 1;
    shdVsProc3DMSI(idout, 4096);
    FlushCache(0);
    sceSdTransToIOP(obuf, (u_int)gDataIOPPtr[gcount], sizeof(obuf), 0);


}





static void Sd3dSetMVol(int vol) {
    se_mvol = vol;


}





int sd_3d_call(int call, int arg1, int arg2, float arg3, float arg4) {



    if ((call >= 40000) && (call < 40258)) {

        return Sd3dPrePlay(call, arg1, arg2, arg3, arg4);
    }
    return -1;
}




static int Sd3dPrePlay(int call /* r2 */, int arg1 /* r2 */, int arg2 /* r2 */, float arg3 /* r29+0x20 */, float arg4 /* r29+0x20 */) {
    int ret; // r2
    int i; // r16
    ret = -1;
    for (i = 0; i < 8; i++) {

        if (in_buf_env[i].mode == 0) {

            Sd3dPlay(call, arg1, arg2, arg3, arg4, i);
            ret = i;
            break;
        }
    }
    return ret;
}




static void Sd3dPlay(int call /* r2 */, int arg1 /* r2 */, int arg2 /* r2 */, float arg3 /* r20 */, float arg4 /* unused */, int no /* r2 */) {
    u_char loop; // r16
    u_long ofst, size, sr; // r2
    int temp = ~7; //@note: not in dwarf
    loop = Sd3dData[call-40000].loop;
    ofst = Sd3dData[call-40000].ofst;
    size = Sd3dData[call-40000].size;
    sr   = Sd3dData[call-40000].sr;




    in_buf_env[no].base = (void*)((u_long)ibuf + ofst);
    in_buf_env[no].size = (size/2) & temp;
    in_buf_env[no].pointer = NULL;
    in_buf_env[no].mode = 0;

    env3d[no].angle1 = 0;

    if (se_stemono == 1)
        env3d[no].angle2 = arg1;
    else
        env3d[no].angle2 = 0;

    env3d[no].level = ((1.0f - (arg2 / 256.0f)) * se_mvol) / 127.0f;
    env3d[no].pitch = sr / 48000.0f;
    env3d[no].cutoff = arg3;

    if (loop)
        in_buf_env[no].mode = 2;
    else
        in_buf_env[no].mode = 1;


}






int sd_3d_move(int no, int arg1, int arg2, float arg3, float arg4 /* unused */) {

    if (in_buf_env[no].mode == 0) return -1;

    if (se_stemono == 1)
        env3d[no].angle2 = arg1;
    else
        env3d[no].angle2 = 0;

    env3d[no].cutoff = arg3;

    env3d[no].level = (1.0f - (arg2 / 256.0f)) * se_mvol / 127.0f;
    return 0;
}






void sd_3d_allstop(void) {
    int i; // r16
    for (i = 0; i < 8; i++) {

        sd_3d_stop(i);
    }
}


void sd_3d_stop(int no) {
    in_buf_env[no].mode = 0;
    memset(obuf, 0, sizeof(obuf));

}






















void* sd_3d_adrs(void) {return ibuf;}
