#include "sh2_common.h"
#include "connect.h"
#include "DBG/dbflow.h"

typedef union DB_WATCH_POINT
{
    char code0x00000001[1];
    char code0x00000002[2];
    char code0x00000004[4];
    char code0x00000008[8];
    char code0x00000010[16];
    char code0x00000020[32];
    char code0x00000040[64];
    char code0x00000080[128];
    char code0x00000100[256];
    char code0x00000200[512];
    char code0x00000400[1024];
    char code0x00000800[2048];
    char code0x00001000[4096];
    char code0x00002000[8192];
    char code0x00004000[16384];
    char code0x00008000[32768];
    char code0x00010000[65536];
    char code0x00020000[131072];
    char code0x00040000[262144];
    char code0x00080000[524288];
    char code0x00100000[1048576];
    char code0x00200000[2097152];
    char code0x00400000[4194304];
    char code0x00800000[8388608];
    char code0x01000000[16777216];
    char code0x02000000[33554432];
    char code0x04000000[67108864];
} DB_WATCH_POINT;
extern DB_WATCH_POINT *db_watch_point;

void GameKeyCheck();

int main(int argc, char** argv) {
    int db_test_dvd;
    u32 step;

    if (argc < 2) {
        printf_skip(1);
    }
    else if (*argv[1] != '-') {
        argv[1] = *argv;
        argc -= 1;
        argv++;
        printf_skip(1);
    }
    else {
        wrap_printf_init();
    }








    BootOptGet(argc, argv);

    db_watch_point = (DB_WATCH_POINT *)0x02000000;

    db_test_dvd = dbFlag(0x10) != 0;



    
    dbSwitchAllInit(dbFlagSet(0x10) != 0);



    
    systemColdInit();


    
    check_build_environment(*argv);

    Sh2sys.step[0] = 0, Sh2sys.step[1] = 0,
    Sh2sys.step[2] = 0, Sh2sys.step[3] = 0,
    Sh2sys.step[4] = 0, Sh2sys.step[5] = 0,
    Sh2sys.step[6] = 0, Sh2sys.step[7] = 0;

    
    dbFlowStartCheck(1);

    while (1) {
        step = Sh2sys.step[0];
        ___dbFlowSetCheckPoint("`main loop.'(main.c:149)");
        switch (step) {
        case 0:
        case 1:
        case 2:
            ___dbFlowSetCheckPoint("`before hot init'(main.c:154)");
            if (systemHotInit() != 0) {
                dbSwitchDispEnable(db_test_dvd);
                Sh2sys.step[0] = 3, Sh2sys.step[1] = 0,
                Sh2sys.step[2] = 0, Sh2sys.step[3] = 0,
                Sh2sys.step[4] = 0, Sh2sys.step[5] = 0,
                Sh2sys.step[6] = 0, Sh2sys.step[7] = 0;
                switch (step) {                      
                case 0:   
                                    Sh2sys.step[1] = 1,
                Sh2sys.step[2] = 0, Sh2sys.step[3] = 0,
                Sh2sys.step[4] = 0, Sh2sys.step[5] = 0,
                Sh2sys.step[6] = 0, Sh2sys.step[7] = 0;
                    break;
                case 1:   
                case 2:
                                    Sh2sys.step[1] = 6,
                Sh2sys.step[2] = 0, Sh2sys.step[3] = 0,
                Sh2sys.step[4] = 0, Sh2sys.step[5] = 0,
                Sh2sys.step[6] = 0, Sh2sys.step[7] = 0;
                    break;
                }
            }
            ___dbFlowSetCheckPoint("`after hot init'(main.c:173)");
            break;
        case 3:
            DrawLopp_Pre();
            dbFreeze();
            ___dbFlowSetCheckPoint("`before game main'(main.c:180)");
            GameMain();
            ___dbFlowSetCheckPoint("`after game main'(main.c:182)");
            dbSwitchAllPrint();
            DrawLopp_Post();
            GameKeyCheck();
            break;
        }
        ___dbFlowSetCheckPoint("`before SE vsync'(main.c:189)");
        Sh2sys.frame_cnt = Sh2sys.frame_cnt + 1;
        ___dbFlowSetCheckPoint("`after SE vsync'(main.c:192)");
    }
}
