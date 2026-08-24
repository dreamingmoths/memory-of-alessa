#include "sh2_common.h"
#include "sce/eekernel.h"

extern /* static */ int pssSema; // size: 0x4, address: 0x37B4A0

static int CreateSemaPss(void);

void PssBreakPoint(void) {
    /* empty */
}

static signed int CreateSemaPss(void) {
    SemaParam param; // r29+0x10
    param.initCount = 1;
    param.maxCount = 1;
    param.option = 0;
    CreateSema(&param);
}

int WaitSemaPss(void) {
    if (pssSema == -1) {
        pssSema = CreateSemaPss();
        ASSERT_ON_LINE(pssSema!=-1, 34);
    }
    return WaitSema(pssSema);
}

int SignalSemaPss(void) {
    SignalSema(pssSema);
}
