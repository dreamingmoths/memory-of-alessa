#include "fileslist_bg.h"

struct FilesBgBlock * FilesGetBgBlock(enum STAGE_ID stg_id /* r2 */, int blk_id /* r2 */) {

    struct FilesBgStage * stg; // r4
    int tmp;
    int max_id; // r2

    tmp = *FilesBgStageMax;
    max_id = stg_id & 0xFF;

    if (max_id <= 0 || !(tmp > max_id)) {
        return 0;
    }

    stg = FilesBgStageList[max_id];
    tmp = *stg->block_max;

    if (blk_id < 0 || !(tmp > blk_id)) { 
        return 0;
    }

    return stg->block_list[blk_id];
}