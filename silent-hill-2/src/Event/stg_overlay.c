#include "stg_overlay.h"

static fsFileIndex *StgOverlayGetFileID(StgName stg_name) {
    switch ((u_char) stg_name) {
        default:
            return NULL;
        case Stg_toilet:
            return &root_stage_toilet_bin;
        case Stg_observation:
            return &root_stage_observation_bin;
        case Stg_forest:
            return &root_stage_forest_bin;
        case Stg_town_east:
            return &root_stage_town_east_bin;
        case Stg_apart_e1f:
            return &root_stage_apart_e1f_bin;
        case Stg_apart_e2f:
            return &root_stage_apart_e2f_bin;
        case Stg_apart_e3fw:
            return &root_stage_apart_e3fw_bin;
        case Stg_apart_e3fe:
            return &root_stage_apart_e3fe_bin;
        case Stg_apart_w1f:
            return &root_stage_apart_w1f_bin;
        case Stg_apart_w2f:
            return &root_stage_apart_w2f_bin;
        case Stg_apart_stair:
            return &root_stage_apart_stair_bin;
        case Stg_apart_out:
            return &root_stage_apart_out_bin;
        case Stg_town_west:
            return &root_stage_town_west_bin;
        case Stg_bowling:
            return &root_stage_bowling_bin;
        case Stg_to_heaven:
            return &root_stage_to_heaven_bin;
        case Stg_heaven_night:
            return &root_stage_heaven_night_bin;
        case Stg_hospital_1f_f:
            return &root_stage_hospital_1f_f_bin;
        case Stg_hospital_2f_f:
            return &root_stage_hospital_2f_f_bin;
        case Stg_hospital_3f_f:
            return &root_stage_hospital_3f_f_bin;
        case Stg_hospital_rf_f:
            return &root_stage_hospital_rf_f_bin;
        case Stg_hospital_1fw_b:
            return &root_stage_hospital_1fw_b_bin;
        case Stg_hospital_1fe_b:
            return &root_stage_hospital_1fe_b_bin;
        case Stg_hospital_2f_b:
            return &root_stage_hospital_2f_b_bin;
        case Stg_hospital_3f_b:
            return &root_stage_hospital_3f_b_bin;
        case Stg_hospital_bf_b:
            return &root_stage_hospital_bf_b_bin;
        case Stg_hospital_pass:
            return &root_stage_hospital_pass_bin;
        case Stg_society:
            return &root_stage_society_bin;
        case Stg_delusion_2:
            return &root_stage_delusion_2_bin;
        case Stg_delusion_3:
            return &root_stage_delusion_3_bin;
        case Stg_prison_n:
            return &root_stage_prison_n_bin;
        case Stg_prison_s:
            return &root_stage_prison_s_bin;
        case Stg_prison_bf:
            return &root_stage_prison_bf_bin;
        case Stg_labyrinth_w:
            return &root_stage_labyrinth_w_bin;
        case Stg_labyrinth_e:
            return &root_stage_labyrinth_e_bin;
        case Stg_labyrinth_n:
            return &root_stage_labyrinth_n_bin;
        case Stg_eddie_boss:
            return &root_stage_eddie_boss_bin;
        case Stg_lake:
            return &root_stage_lake_bin;
        case Stg_hotel_bf_f:
            return &root_stage_hotel_bf_f_bin;
        case Stg_hotel_1f_f:
            return &root_stage_hotel_1f_f_bin;
        case Stg_hotel_2f_f:
            return &root_stage_hotel_2f_f_bin;
        case Stg_hotel_3f_f:
            return &root_stage_hotel_3f_f_bin;
        case Stg_hotel_bf_b:
            return &root_stage_hotel_bf_b_bin;
        case Stg_hotel_1f_b:
            return &root_stage_hotel_1f_b_bin;
        case Stg_hotel_2f_b:
            return &root_stage_hotel_2f_b_bin;
        case Stg_hotel_3f_b:
            return &root_stage_hotel_3f_b_bin;
        case Stg_hotel_fire:
            return &root_stage_hotel_fire_bin;
        case Stg_end_recovery:
            return &root_stage_end_recovery_bin;
        case Stg_end_maria:
            return &root_stage_end_maria_bin;
        case Stg_end_suicide:
            return &root_stage_end_suicide_bin;
        case Stg_end_rebirth:
            return &root_stage_end_rebirth_bin;
        case Stg_end_dog:
            return &root_stage_end_dog_bin;
    }
}

static struct Stage_Data *StgOverlayGetStageData(StgName stg_name) {
    switch ((u_char) stg_name) {
    default:
        return &stage_tgs_trial;
    case Stg_toilet:
        return &stage_toilet;
    case Stg_observation:
        return &stage_observation;
    case Stg_forest:
        return &stage_forest;
    case Stg_town_east:
        return &stage_town_east;
    case Stg_apart_e1f:
        return &stage_apart_e1f;
    case Stg_apart_e2f:
        return &stage_apart_e2f;
    case Stg_apart_e3fw:
        return &stage_toilet;
    case Stg_apart_e3fe:
        return &stage_apart_e3fe;
    case Stg_apart_w1f:
        return &stage_apart_w1f;
    case Stg_apart_w2f:
        return &stage_apart_w2f;
    case Stg_apart_stair:
        return &stage_apart_stair;
    case Stg_apart_out:
        return &stage_apart_out;
    case Stg_town_west:
        return &stage_town_west;
    case Stg_bowling:
        return &stage_bowling;
    case Stg_to_heaven:
        return &stage_to_heaven;
    case Stg_heaven_night:
        return &stage_heaven_night;
    case Stg_hospital_1f_f:
        return &stage_hospital_1f_f;
    case Stg_hospital_2f_f:
        return &stage_hospital_2f_f;
    case Stg_hospital_3f_f:
        return &stage_hospital_3f_f;
    case Stg_hospital_rf_f:
        return &stage_hospital_rf_f;
    case Stg_hospital_1fw_b:
        return &stage_hospital_1fw_b;
    case Stg_hospital_1fe_b:
        return &stage_hospital_1fe_b;
    case Stg_hospital_2f_b:
        return &stage_hospital_2f_b;
    case Stg_hospital_3f_b:
        return &stage_hospital_3f_b;
    case Stg_hospital_bf_b:
        return &stage_hospital_bf_b;
    case Stg_hospital_pass:
        return &stage_hospital_pass;
    case Stg_society:
        return &stage_society;
    case Stg_delusion_2:
        return &stage_delusion_2;
    case Stg_delusion_3:
        return &stage_delusion_3;
    case Stg_prison_n:
        return &stage_prison_n;
    case Stg_prison_s:
        return &stage_prison_s;
    case Stg_prison_bf:
        return &stage_prison_bf;
    case Stg_labyrinth_w:
        return &stage_labyrinth_w;
    case Stg_labyrinth_e:
        return &stage_labyrinth_e;
    case Stg_labyrinth_n:
        return &stage_labyrinth_n;
    case Stg_eddie_boss:
        return &stage_eddie_boss;
    case Stg_lake:
        return &stage_lake;
    case Stg_hotel_bf_f:
        return &stage_hotel_bf_f;
    case Stg_hotel_1f_f:
        return &stage_hotel_1f_f;
    case Stg_hotel_2f_f:
        return &stage_hotel_2f_f;
    case Stg_hotel_3f_f:
        return &stage_hotel_3f_f;
    case Stg_hotel_bf_b:
        return &stage_hotel_bf_b;
    case Stg_hotel_1f_b:
        return &stage_hotel_1f_b;
    case Stg_hotel_2f_b:
        return &stage_hotel_2f_b;
    case Stg_hotel_3f_b:
        return &stage_hotel_3f_b;
    case Stg_hotel_fire:
        return &stage_hotel_fire;
    case Stg_end_recovery:
        return &stage_end_recovery;
    case Stg_end_maria:
        return &stage_end_maria;
    case Stg_end_suicide:
        return &stage_end_suicide;
    case Stg_end_rebirth:
        return &stage_end_maria;
    case Stg_end_dog:
        return &stage_end_dog;
    }
}
                        
void StgOverlay(void) {
    fsFileIndex *stage_bin;
    char *addr;
    int size;

    stage_bin = StgOverlayGetFileID(playing.stage);

    if (last_stage_bin != stage_bin) {
        last_stage_bin = stage_bin;
        if (stage_bin != 0) {
            void* overlay_load_addr = D_1F01E00;
            int fid;
            mwOverlayHeader* ovl = overlay_load_addr;
        
            FlushCache(2);

            for (;;) {
                fid = FcRead(stage_bin, overlay_load_addr);
                if (fid != -1) break;

                shSyncVEnd(0);
            }

            fsSync(0, fid);

            addr = overlay_load_addr;
            addr += 0x80;
            addr += ovl->sz_text;
            addr += ovl->sz_data;
            size = ovl->sz_bss;
            UtilMemSet(addr, 0, size);

            MWNotifyOverlayLoaded(overlay_load_addr);
        }        
    } else {
        verbose(3, "stg_overlay.c:352> stage data is already loaded.\n");
    }

    stage = StgOverlayGetStageData(playing.stage);
}

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_toilet_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_observation_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_forest_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_town_east_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_e1f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_e2f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_e3fw_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_e3fe_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_w1f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_w2f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_stair_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_apart_out_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_town_west_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_bowling_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_to_heaven_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_heaven_night_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_1f_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_2f_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_3f_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_rf_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_1fw_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_1fe_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_2f_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_3f_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_bf_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hospital_pass_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_society_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_delusion_2_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_delusion_3_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_prison_n_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_prison_s_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_prison_bf_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_labyrinth_w_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_labyrinth_e_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_labyrinth_n_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_eddie_boss_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_lake_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_bf_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_1f_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_2f_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_3f_f_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_bf_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_1f_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_2f_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_3f_b_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_hotel_fire_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_end_recovery_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_end_maria_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_end_suicide_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_end_rebirth_bin);

INCLUDE_RODATA("asm/nonmatchings/Event/stg_overlay", root_stage_end_dog_bin);