#ifndef MC_H
#define MC_H

#include "SH2_common/playing_info.h"
#include "sce/eetypes.h"

#define MC_STATUS_FLAG_0 0x0
#define MC_STATUS_FLAG_1 0x1
#define MC_STATUS_FLAG_2 0x2
#define MC_STATUS_FLAG_3 0x3
#define MC_STATUS_FLAG_4 0x4
#define MC_STATUS_FLAG_5 0x5
#define MC_STATUS_FLAG_6 0x6
#define MC_STATUS_FLAG_7 0x7
#define MC_STATUS_FLAG_8 0x8
#define MC_STATUS_FLAG_9 0x9
#define MC_STATUS_FLAG_A 0xA
#define MC_STATUS_FLAG_B 0xB

#define MC_MAXFILES 0xF
#define MCW_SET_MENU_STEP(_step) \
    do {                         \
        mcw->menu_step = _step;  \
        mcw->menu_sstep = 0;     \
    } while (0)
#define MCW_SET_MENU_SSTEP() do { mcw->menu_sstep++; } while (0)

typedef struct MC_FILEINFO {
    // total size: 0x14
    u_char dirid;      // offset 0x0, size 0x1
    u_char fileid;     // offset 0x1, size 0x1
    u_char scene;      // offset 0x2, size 0x1
    u_char b_level;    // offset 0x3, size 0x1
    u_char r_level;    // offset 0x4, size 0x1
    u_char status;     // offset 0x5, size 0x1
    u_short savecount; // offset 0x6, size 0x2
    float time;        // offset 0x8, size 0x4
    float total_time;  // offset 0xC, size 0x4
    u_int csum;        // offset 0x10, size 0x4
} MC_FILEINFO;

typedef struct MC_DIRDATA {
    // total size: 0x400
    char message[28];            // offset 0x0, size 0x1C
    u_int flag;                  // offset 0x1C, size 0x4
    struct MC_FILEINFO file[15]; // offset 0x20, size 0x12C
    struct Playing_Info playing; // offset 0x14C, size 0x8C
    int lastsave;                // offset 0x1D8, size 0x4
    u_int id;                    // offset 0x1DC, size 0x4
    u_int csum[4];               // offset 0x1E0, size 0x10
    u_int pad[130];              // offset 0x1F0, size 0x208
    u_long csum_all;             // offset 0x3F8, size 0x4
} MC_DIRDATA;

typedef struct MC_SAVEDATA {
    // total size: 0x2000
    u_int csum1;       // offset 0x0, size 0x4
    u_int csum2;       // offset 0x4, size 0x4
    u_char data[8168]; // offset 0x8, size 0x1FE8
    u_int csum3;       // offset 0x1FF0, size 0x4
    u_int pad;         // offset 0x1FF4, size 0x4
    u_long csum4;      // offset 0x1FF8, size 0x4
} MC_SAVEDATA;

typedef struct MC_JOBS {
    // total size: 0x4
    char job;   // offset 0x0, size 0x1
    char port;  // offset 0x1, size 0x1
    short data; // offset 0x2, size 0x2
} MC_JOBS;

typedef struct MC_CODEC_DATA {
    // total size: 0x50
    u_char key1[24]; // offset 0x0, size 0x18
    u_char key2[16]; // offset 0x18, size 0x10
    int mode;        // offset 0x28, size 0x4
    int step;        // offset 0x2C, size 0x4
    u_long* pos;     // offset 0x30, size 0x4
    int count;       // offset 0x34, size 0x4
    int zcount;      // offset 0x38, size 0x4
    u_int csum1;     // offset 0x3C, size 0x4
    u_int csum2;     // offset 0x40, size 0x4
    u_long csum4;    // offset 0x48, size 0x4
} MC_CODEC_DATA;

typedef struct MC_WORK {
    // total size: 0xC
    u_short status;  // offset 0x0, size 0x2
    char ls_port;    // offset 0x2, size 0x1
    char ls_dir;     // offset 0x3, size 0x1
    char ls_file;    // offset 0x4, size 0x1
    u_int ls_dir_id; // offset 0x8, size 0x4
} MC_WORK;

typedef struct MC_WORK2 {
    // total size: 0x4240
    struct MC_DIRDATA dirdata;   // offset 0x0, size 0x400
    struct MC_SAVEDATA savedata; // offset 0x400, size 0x2000
    struct /* @anon3 */ {
        // total size: 0x40
        struct /* @anon4 */ {
            // total size: 0x8
            u_char Resv2; // offset 0x0, size 0x1
            u_char Sec;   // offset 0x1, size 0x1
            u_char Min;   // offset 0x2, size 0x1
            u_char Hour;  // offset 0x3, size 0x1
            u_char Day;   // offset 0x4, size 0x1
            u_char Month; // offset 0x5, size 0x1
            u_short Year; // offset 0x6, size 0x2
        } _Create;        // offset 0x0, size 0x8
        struct /* @anon5 */ {
            // total size: 0x8
            u_char Resv2;               // offset 0x0, size 0x1
            u_char Sec;                 // offset 0x1, size 0x1
            u_char Min;                 // offset 0x2, size 0x1
            u_char Hour;                // offset 0x3, size 0x1
            u_char Day;                 // offset 0x4, size 0x1
            u_char Month;               // offset 0x5, size 0x1
            u_short Year;               // offset 0x6, size 0x2
        } _Modify;                      // offset 0x8, size 0x8
        u_int FileSizeByte;             // offset 0x10, size 0x4
        u_short AttrFile;               // offset 0x14, size 0x2
        u_short Reserve1;               // offset 0x16, size 0x2
        u_int Reserve2;                 // offset 0x18, size 0x4
        u_int PdaAplNo;                 // offset 0x1C, size 0x4
        u_char EntryName[32];           // offset 0x20, size 0x20
    } dirtbl[20];                       // offset 0x2400, size 0x500
    struct MC_FILEINFO tmpinfo[75];     // offset 0x2900, size 0x5DC
    struct MC_FILEINFO fileinfo[3][75]; // offset 0x2EDC, size 0x1194
    struct MC_JOBS jobs[16];            // offset 0x4070, size 0x40
    char port;                          // offset 0x40B0, size 0x1
    char dirnum;                        // offset 0x40B1, size 0x1
    char files;                         // offset 0x40B2, size 0x1
    char tbl_files;                     // offset 0x40B3, size 0x1
    char job;                           // offset 0x40B4, size 0x1
    char job_port;                      // offset 0x40B5, size 0x1
    char job_data;                      // offset 0x40B6, size 0x1
    char job_step;                      // offset 0x40B7, size 0x1
    char job_num;                       // offset 0x40B8, size 0x1
    char job_end;                       // offset 0x40B9, size 0x1
    int result;                         // offset 0x40BC, size 0x4
    int type[2];                        // offset 0x40C0, size 0x8
    int free[2];                        // offset 0x40C8, size 0x8
    int format[2];                      // offset 0x40D0, size 0x8
    int info[2];                        // offset 0x40D8, size 0x8
    u_char d_ent[2];                    // offset 0x40E0, size 0x2
    char portstatus[3];                 // offset 0x40E2, size 0x3
    char dirstatus[3][5];               // offset 0x40E5, size 0xF
    char filemax[3];                    // offset 0x40F4, size 0x3
    char tmp_status[3];                 // offset 0x40F7, size 0x3
    int type_old;                       // offset 0x40FC, size 0x4
    short retry;                        // offset 0x4100, size 0x2
    short info_count;                   // offset 0x4102, size 0x2
    int fd;                             // offset 0x4104, size 0x4
    int fid[2];                         // offset 0x4108, size 0x8
    short autoload;                     // offset 0x4110, size 0x2
    char saveload;                      // offset 0x4112, size 0x1
    char menu_step;                     // offset 0x4113, size 0x1
    char menu_sstep;                    // offset 0x4114, size 0x1
    char menu_base[3];                  // offset 0x4115, size 0x3
    char menu_num[3];                   // offset 0x4118, size 0x3
    char tmp_num;                       // offset 0x411B, size 0x1
    char menu_info;                     // offset 0x411C, size 0x1
    char menu_infotype;                 // offset 0x411D, size 0x1
    char menu_timer;                    // offset 0x411E, size 0x1
    char menu_port;                     // offset 0x411F, size 0x1
    char menu_yesno;                    // offset 0x4120, size 0x1
    char menu_newdir;                   // offset 0x4121, size 0x1
    char menu_bk;                       // offset 0x4122, size 0x1
    float menu_scroll;                  // offset 0x4124, size 0x4
    float menu_count;                   // offset 0x4128, size 0x4
    float menu_an_count;                // offset 0x412C, size 0x4
    char extra_name[8];                 // offset 0x4130, size 0x8
    char* extra_adr;                    // offset 0x4138, size 0x4
    int extra_size;                     // offset 0x413C, size 0x4
    u_int dirid[3][5];                  // offset 0x4140, size 0x3C
    u_int dirid_new;                    // offset 0x417C, size 0x4
    char fname[64];                     // offset 0x4180, size 0x40
    u_long dtime[2];                    // offset 0x41C0, size 0x8
    struct MC_FILEINFO* loaddata;       // offset 0x41D0, size 0x4
    struct MC_CODEC_DATA cd;            // offset 0x41D8, size 0x50
} MC_WORK2;

extern MC_WORK mc;    // size: 0xC, address: 0x11E8388
extern MC_WORK2* mcw; // size: 0x4, address: 0x11E8380

MC_WORK* mcInit(void);

void mcExec(void);

void mcSetJob(char job, char port, short data);

void mcSetGetInfo(char port);

void mcSetGetInfo2(char port);

void mcCheckAll(void);

void mcStepInit(void);

int mcStartCheck(void);

int mcStartCheck2(void);

void mcCheckDir(char port);

void mcFormat(char port);

int mcCheckStatus(char port);

int mcCheckCanSave(char port);

void mcSaveIconSys(char port, char dn);

void mcSaveIcon(char port, char dn);

void mcSaveData(char port, char dn, char fn);

void mcLoadData(char port, char dn, char fn);

void mcDeleteData(char port, char dn, char fn);

void mcMakeSaveData(void);

void mcDecodeStart(void);

void mcCodecAll(void);

void mcMakeDirData(char port, char dn, char fn);

void mcMakeDirData2(char port, char dn, char fn);

void mcMakeDirData3(void);

int mcExtDirData(void);

void mcLoadIconData(void);

int mcCheckEndLoadIconData(void);

#endif // MC_H
