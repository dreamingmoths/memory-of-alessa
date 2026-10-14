#include "FilesList/fileslist_bg.h"

// @todo: migrate data (this might take a while T.T)

/*
static FilesBgStage FilesBgStage_ap[1] = { {FilesBgBlockList_ap, FilesBgBlockMax_ap, NULL, NULL} }; // size: 0x10, address: 0x3400E0
static FilesBgStage FilesBgStage_bw[1] = { {FilesBgBlockList_bw, FilesBgBlockMax_bw, NULL, NULL} }; // size: 0x10, address: 0x3400F0
static FilesBgStage FilesBgStage_ca[1] = { {FilesBgBlockList_ca, FilesBgBlockMax_ca, NULL, NULL} }; // size: 0x10, address: 0x340100
static FilesBgStage FilesBgStage_cb[1] = { {FilesBgBlockList_cb, FilesBgBlockMax_cb, NULL, NULL} }; // size: 0x10, address: 0x340110
static FilesBgStage FilesBgStage_cc[1] = { {FilesBgBlockList_cc, FilesBgBlockMax_cc, NULL, NULL} }; // size: 0x10, address: 0x340120
static FilesBgStage FilesBgStage_cd[1] = { {FilesBgBlockList_cd, FilesBgBlockMax_cd, NULL, NULL} }; // size: 0x10, address: 0x340130
static FilesBgStage FilesBgStage_er[1] = { {FilesBgBlockList_er, FilesBgBlockMax_er, NULL, NULL} }; // size: 0x10, address: 0x340140
static FilesBgStage FilesBgStage_hp[1] = { {FilesBgBlockList_hp, FilesBgBlockMax_hp, NULL, NULL} }; // size: 0x10, address: 0x340150
static FilesBgStage FilesBgStage_ps[1] = { {FilesBgBlockList_ps, FilesBgBlockMax_ps, NULL, NULL} }; // size: 0x10, address: 0x340160
static FilesBgStage FilesBgStage_qp[1] = { {FilesBgBlockList_qp, FilesBgBlockMax_qp, NULL, NULL} }; // size: 0x10, address: 0x340170
static FilesBgStage FilesBgStage_qt[1] = { {FilesBgBlockList_qt, FilesBgBlockMax_qt, NULL, NULL} }; // size: 0x10, address: 0x340180
static FilesBgStage FilesBgStage_rr[1] = { {FilesBgBlockList_rr, FilesBgBlockMax_rr, NULL, NULL} }; // size: 0x10, address: 0x340190
static FilesBgStage FilesBgStage_ru[1] = { {FilesBgBlockList_ru, FilesBgBlockMax_ru, NULL, NULL} }; // size: 0x10, address: 0x3401A0
static FilesBgStage FilesBgStage_th[1] = { {FilesBgBlockList_th, FilesBgBlockMax_th, NULL, NULL} }; // size: 0x10, address: 0x3401B0
static FilesBgStage FilesBgStage_ob[1] = { {FilesBgBlockList_ob, FilesBgBlockMax_ob, NULL, NULL} }; // size: 0x10, address: 0x3401C0
static FilesBgStage FilesBgStage_ma[1] = { {FilesBgBlockList_ma, FilesBgBlockMax_ma, NULL, NULL} }; // size: 0x10, address: 0x3401D0

static FilesBgStage* FilesBgStageList[BG_ID_num] = {  // size: 0x44, address: 0x3401E0
    NULL,
    FilesBgStage_ca,
    FilesBgStage_cb,
    FilesBgStage_cc,
    FilesBgStage_cd,
    FilesBgStage_ob,
    FilesBgStage_er,
    FilesBgStage_bw,
    FilesBgStage_th,
    FilesBgStage_ap,
    FilesBgStage_hp,
    FilesBgStage_ps,
    FilesBgStage_rr,
    FilesBgStage_ru,
    FilesBgStage_qp,
    FilesBgStage_qt,
    FilesBgStage_ma,
};

static int FilesBgStageMax[1] = { BG_ID_num }; // size: 0x4, address: 0x340228
*/

FilesBgBlock* FilesGetBgBlock(STAGE_ID stg_id, int blk_id) {
    FilesBgStage* stg;
    int max_id = FilesBgStageMax[0];
    if ((stg_id <= 0) || (max_id <= stg_id)) return NULL;    
    stg = FilesBgStageList[stg_id];
    
    max_id = *stg->block_max;
    if ((blk_id < 0) || (max_id <= blk_id)) return NULL;    
    return stg->block_list[blk_id];
}
