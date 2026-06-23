#include "fileslist_bg.h"

#ifdef NON_MATCHING
FilesBgBlock* FilesGetBgBlock(STAGE_ID stg_id /* r2 */, int blk_id /* r2 */) {

    FilesBgStage* stg; // r4
    int tmp = FilesBgStageMax[0];
    int max_id = stg_id & 0xFF; // r2

    if (max_id <= 0 || tmp <= max_id) {
        return 0;
    }

    stg = FilesBgStageList[max_id];
    tmp = *stg->block_max;

    if (blk_id < 0 || !(tmp > blk_id)) { 
        return 0;
    }

    return stg->block_list[blk_id];
}
#else
INCLUDE_ASM("asm/nonmatchings/FilesList/fileslist_bg", FilesGetBgBlock)
#endif
