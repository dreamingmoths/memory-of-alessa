#include "common.h"
#include "main.h"
#include "wasteland.h"

int main(int argc, s8** argv) {
    int temp_s1;
    int temp_v0;
    int run;

    run = 1;

    func_0019B450();

    db_watch_point = (DB_WATCH_POINT *)0x02000000;

    func_00156480();
    func_001E4E10();
    func_0012BD80();
    func_0012C980();
    func_0012CED0();
    func_001D9350();
    func_00337AB0();
    func_0012BDF0(*argv);
    func_00172FA0();
    func_0012CEF0();
    func_00156370(0);
    func_00156380();
    temp_s1 = func_00156B50(7);
    func_00281D80(temp_s1, func_00156B80(7));
    func_001E4E30(0);
    func_001E2830();
    func_001E5050();
    func_00282090(1);
    func_00195A40();
    func_0012DC50();

    do {
        *(int* )0x10000000 = 0;
        switch (func_0012D080()) { 
        case 0:
            func_0019B540(0x13);
            func_0019B540(0x14);
            func_0012BDC0();
            func_001D9500();
            func_0012DCA0();
            func_00195B90();
            func_0019B540(0x13);
            func_0012CFE0(2);
            break;
        case 2:
            func_001D9090(1);
            *(int* )0x10000000 = 0;
            func_001E5170();
            func_00194480();
            func_0012DCB0(2);
            func_0012DCB0(0);
            func_001D90D0();
            func_0015DB70();
            func_001D9190();
            func_00195490();
            func_0013A780();
            D_003D44A8 = *(int* )0x10000000;
            func_00156390();
            func_00156AC0();
            func_00130640(0);
            func_0019A7D0(func_00130650());
            func_001D91D0();
            func_0013CE70();
            D_003D44A0 = *(int* )0x10000000;
            if (func_0012C9B0() != 0) {
                func_0012CFE0(3);
            }
            break;
        case 3:
            if (func_00151150(0, 1) != 0) {
                func_0019BBD0(1, 0, 1);
                func_0019BBD0(2, 0, 1);
                sceDmaSync(sceDmaGetChan(0), 0, 0);
                func_0019B540(0xA);
                func_0012CFE0(0);
                if (func_0019B580(0x11) != 0) {
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
