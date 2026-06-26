#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/pad.h"
#include "GFW/sh2_DrawEnvData.h"
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
        dbFlowSetCheckPointOnLine("main loop.", 149);
        switch (step) {
        case 0:
        case 1:
        case 2:
            dbFlowSetCheckPointOnLine("before hot init", 154);
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
            dbFlowSetCheckPointOnLine("after hot init", 173);
            break;
        case 3:
            DrawLopp_Pre();
            dbFreeze();
            dbFlowSetCheckPointOnLine("before game main", 180);
            GameMain();
            dbFlowSetCheckPointOnLine("after game main", 182);
            dbSwitchAllPrint();
            DrawLopp_Post();
            GameKeyCheck();
            break;
        }
        dbFlowSetCheckPointOnLine("before SE vsync", 189);
        Sh2sys.frame_cnt = Sh2sys.frame_cnt + 1;
        dbFlowSetCheckPointOnLine("after SE vsync", 192);
    }
}

void GameKeyCheck(void) {
    if (Sh2sys.soft_reset &&
        shPadPress(0, PAD_KEY_START) && shPadPress(0, PAD_KEY_SELECT) &&
        shPadPress(0, PAD_KEY_L1) && shPadPress(0, PAD_KEY_R1)) {
        fsSync(0, -1);
        lisSync(0, -1);
        Sh2sys.step[0] = 2;
        Sh2sys.step[1] = 0;
        Sh2sys.step[2] = 0;
        Sh2sys.step[3] = 0;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
        Env_ctl.stat_ctl_1.ui32[0] <<= 8;
        Env_ctl.stat_ctl_1.uc8[0] = 0;
    }
}
