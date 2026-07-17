#include "common.h"
#include "main.h"
#include "sce/eeregs.h"

int main(int argc, s_char* argv[]) {
    int temp_s1;
    int temp_v0;
    int run = 1;

    func_0019B450();

    db_watch_point = (DB_WATCH_POINT *)0x02000000;

    PrintSectionSizes();
    func_001E4E10();
    func_0012BD80();
    func_0012C980();
    func_0012CED0();
    func_001D9350();
    func_00337AB0();
    sh3_initFilesys(*argv);
    func_00172FA0();
    func_0012CEF0();
    func_00156370(0);
    func_00156380();
    temp_s1 = func_00156B50(7);
    func_00281D80(temp_s1, func_00156B80(7));
    sh3_InitSif(0);
    sh3_InitAdx();
    sh3_AllocIopHeap();
    func_00282090(1);
    func_00195A40();
    func_0012DC50();

    do {
        *T0_COUNT = 0;
        switch (func_0012D080()) { 
        case 0:
            func_0019B540(19);
            func_0019B540(20);
            func_0012BDC0();
            func_001D9500();
            func_0012DCA0();
            func_00195B90();
            func_0019B540(19);
            func_0012CFE0(2);
            break;
        case 2:
            func_001D9090(1);
            *T0_COUNT = 0;
            func_001E5170();
            GameMain();
            func_0012DCB0(2);
            func_0012DCB0(0);
            func_001D90D0();
            func_0015DB70();
            func_001D9190();
            func_00195490();
            func_0013A780();
            D_003D44A8 = *T0_COUNT;
            func_00156390();
            func_00156AC0();
            func_00130640(0);
            shSetDF(func_00130650());
            func_001D91D0();
            func_0013CE70();
            D_003D44A0 = *T0_COUNT;
            if (func_0012C9B0() != 0) {
                func_0012CFE0(3);
            }
            break;
        case 3:
            if (func_00151150(0, 1) != 0) {
                dSync(1, 0, 1);
                dSync(2, 0, 1);
                sceDmaSync(sceDmaGetChan(0), 0, 0);
                func_0019B540(10);
                func_0012CFE0(0);
                if (func_0019B580(17) != 0) {
                    run = 0;
                }
            }
            break;
        case 4:
            break;
        }
    } while (run);
    return 0;
}
