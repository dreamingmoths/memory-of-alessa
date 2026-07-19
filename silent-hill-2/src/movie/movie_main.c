#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/mem_share.h"

#include "movie/movie_main.h"
#include "movie/pss_main.h"

#include "data/fs_structs.h"
#include "LoadBg/loadbg_2x2.h"
#include "Multi_thr/filesys/fileserv.h"

static void movieSubPreSet(union fsFileIndex* id, void* wk);
static int MovieSelectSlot(union fsFileIndex* id);

/* @todo: generate data headers */
extern fsFileIndex data_movie_deai_pss[1];
extern fsFileIndex data_movie_end_dog_pss[1];
extern fsFileIndex data_movie_gero_pss[1];
extern fsFileIndex data_movie_hei_pss[1];
extern fsFileIndex data_movie_knife_pss[1];
extern fsFileIndex data_movie_korosu_a_pss[1];
extern fsFileIndex data_movie_korosu_b_pss[1];
extern fsFileIndex data_movie_murder_pss[1];
extern fsFileIndex data_movie_open_bgm_pss[1];
extern fsFileIndex data_movie_rouya_pss[1];
extern fsFileIndex data_movie_saikai_pss[1];
extern fsFileIndex data_movie_toilet_pss[1];
extern fsFileIndex data_movie_open_voc_pss[1];
extern fsFileIndex data_movie_ending_pss[1];
extern fsFileIndex data_movie_hakaba_pss[1];

/* @todo: migrate data */
extern int movieExecDummy;
extern int movieLastExitStatus;
extern fsFileIndex* movieLastFile;
extern u_long128 work[5040]; // @ 0x01202FC0
extern u_long128 work_730[5040]; // @ 0x01202FC0

int MovieSelectSlot(fsFileIndex* id) {
    int slot;

    slot =
        id == data_movie_deai_pss       ? loadBg2x2_GetSlotOutdoor(1, 4)
        : id == data_movie_end_dog_pss  ? 0
        : id == data_movie_ending_pss   ? 0
        : id == data_movie_gero_pss     ? loadBg2x2_GetFreeSlotIndoor(0x1E)
        : id == data_movie_hakaba_pss   ? loadBg2x2_GetSlotOutdoor(0, -1)
        : id == data_movie_hei_pss      ? loadBg2x2_GetSlotOutdoor(0, 1)
        : id == data_movie_knife_pss    ? loadBg2x2_GetFreeSlotIndoor(0x24)
        : id == data_movie_korosu_a_pss ? loadBg2x2_GetFreeSlotIndoor(0x6C)
        : id == data_movie_korosu_b_pss ? loadBg2x2_GetFreeSlotIndoor(0x6C)
        : id == data_movie_murder_pss   ? loadBg2x2_GetFreeSlotIndoor(0xA2)
        : id == data_movie_open_bgm_pss ? -1
        : id == data_movie_open_voc_pss ? -1
        : id == data_movie_rouya_pss    ? loadBg2x2_GetFreeSlotIndoor(0x89)
        : id == data_movie_saikai_pss   ? loadBg2x2_GetFreeSlotIndoor(0x59)
        : id == data_movie_toilet_pss   ? loadBg2x2_GetFreeSlotIndoor(1)
                                        : -1;

    ASSERT_ON_LINE(0<=slot&&slot<8, 61);

    return slot;
}

void MoviePreSet(fsFileIndex* id) {
    int slot = MovieSelectSlot(id);
    MemShareAllocateEventMovie(slot);

    movieSubPreSet(id, NULL);
}

void MovieTitlePreSet(fsFileIndex* id) {
    MemShareAllocateTitleMovie();
    movieSubPreSet(id, NULL);
}

void MovieInit(void) {
    pssSystemColdInit();
    movieLastExitStatus = 0;
    movieExecDummy      = 0;
}

int MovieMain(void) {
    int result;
    int ret = 0;

    if (movieExecDummy == 0) {

        pssInit();
        pssSetMaskSwitch(0);
        do {

            pssCheckMovieCancel();
            pssSetControlData(2, NULL, 0);

            if (movieLastFile != data_movie_gero_pss) {
                SeBgmManager();
            }
        } while (result = pssMain());
        
        do {
            if (pssGetPssAbortFlag() == 1)
                ret = -1;
            else
                ret = 0;
        } while (0); // @hack? there's a `nop` on line 127 in the proto.

        movieLastExitStatus = ret;
    }

    shSetDF(2);
    return ret;
}

int MovieWaitReady(void) {
    return movieExecDummy ? 1 : 1;
}

void MoviePlayFromReady(void) {
    pssSetControlData(2, NULL, 0);
}

int MovieCheckSleep(void) {
    return pssGetPssStatus() == 0;
}

int MoviePlayOPMovie(void) {
    int ret = 1;

    switch (Sh2sys.step[2]) { /* irregular */
        case 0:
            MemShareWaitRealloc(0);
            MovieTitlePreSet(data_movie_open_voc_pss);
            sh2sys_step_2();
            break;

        case 1:
            if (MovieWaitReady()) {
                sh2sys_step_2();
            }
            break;

        case 2:
            if (movieExecDummy) {
                ret = 0;
            } else {
                pssInit();
                pssSetMaskSwitch(1);
                pssSetControlData(2, NULL, 0);
                movieSetSubTitleData(NULL, NULL, 0);
                do {
                    pssCheckMovieCancel();
                    pssSetControlData(2, NULL, 0);
                } while (pssMain());
                if (pssGetPssAbortFlag() == 1) {
                    ret = -1;
                } else {
                    ret = 0;
                }
                pssExit();
            }
            break;
    }
    movieLastExitStatus = ret;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/movie/movie_main", movieSubPreSet);

int movieGetLastExitStatus(void) {
    return movieLastExitStatus == -1 ^ 1;
}

void movieSetSubTitleData(u16* msg_bufp, void* adr_msg_time, int msg_start) {
    pssSetSubTitleData(msg_bufp, adr_msg_time, msg_start);
}
