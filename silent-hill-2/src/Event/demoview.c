#include "Event/demoview.h"
#include "SH2_common/sh2dt.h"
#include "sound/sh_sd_call.h"
#include "Font/font.h"
#include "SH2_common/playing_info.h"

extern /* static */ float sbt_timer; 

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsReadShort);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsReadFloat2);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsReadFloat4);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DramaDemoMain);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DramaDemoInit);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DramaDemoAnimationStart);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsPlay);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsPlayKey);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsPlayCamera);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsPlayLight);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DdsPlayCharacter);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DramaDemoSkipLast);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", RotationToInterest);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DramaDemoFade);

INCLUDE_ASM("asm/nonmatchings/Event/demoview", DramaDemoNumber);

void SubtitlesExec(DramaDemo_MessageTime* msg_time /* r2 */, int msg_no /* r2 */, int str_no /* r2 */, float timer /* r29 */)  {
    sbt_msg_time = msg_time;
    sbt_msg_no = msg_no;
    sbt_str_no = str_no;
    sbt_timer = timer;
}

void SubtitlesManager(void) {
    if (sbt_msg_no) {
        if (!sbt_str_no && !(shSdStat() & 0xF0)) {
            sbt_msg_no = 0;
            return;
        }
        if (!sbt_str_no || !(shSdStat() & 0xF0)) {
            if (sbt_str_no) {
                shSdCall(sbt_str_no, 0, 0, 0);
                sbt_str_no = 0;
            }
            if (sbt_timer == 0.0f) {
                if ((shSdStat() & 0xF0) != 0x40) {
                    return;
                }
                shSdCall(0x3F7, 0, 0, 0);
                UNSET_BIT(demo_status, 3);
            }
            sbt_timer += 30.0f * shGetDT();
            if (playing.subtitles) {
                if ((int) sbt_timer > sbt_msg_time->end) {
                    fontClear();
                    sbt_msg_time++;
                    UNSET_BIT(demo_status, 3);
                }
                if (((int) sbt_timer > sbt_msg_time->start) && !GET_BIT(demo_status, 3)) {
                    fontMessageNum(msg_buffer, sbt_msg_no);
                    sbt_msg_no++;
                    SET_BIT(demo_status, 8);
                }
            }
        }
    }
}
