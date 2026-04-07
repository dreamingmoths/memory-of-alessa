#include "sh2_common.h"
#include "connect.h"
#include "DBG/dbflow.h"
#include "main.h"

int main(int argc, char** argv) {
    int db_test_dvd;
    u_int step;

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
        dbFlowSetCheckPoint("`main loop.'(main.c:149)");
        switch (step) {
        case 0:
        case 1:
        case 2:
            dbFlowSetCheckPoint("`before hot init'(main.c:154)");
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
            dbFlowSetCheckPoint("`after hot init'(main.c:173)");
            break;
        case 3:
            DrawLopp_Pre();
            dbFreeze();
            dbFlowSetCheckPoint("`before game main'(main.c:180)");
            GameMain();
            dbFlowSetCheckPoint("`after game main'(main.c:182)");
            dbSwitchAllPrint();
            DrawLopp_Post();
            GameKeyCheck();
            break;
        }
        dbFlowSetCheckPoint("`before SE vsync'(main.c:189)");
        Sh2sys.frame_cnt = Sh2sys.frame_cnt + 1;
        dbFlowSetCheckPoint("`after SE vsync'(main.c:192)");
    }
}
