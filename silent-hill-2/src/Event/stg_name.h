#ifndef STG_NAME_H
#define STG_NAME_H

#include "sh2_common.h"

/**
 * @note enum not found in dwarf information. Recovered partially from strings.
 */
typedef enum _Sh2GlobalCoord {
    Glb_crd_null        = 0,
    Glb_crd_forest      = 1,
    Glb_crd_town_east   = 2,
    Glb_crd_town_west   = 3,
    Glb_crd_lake        = 4,
    Glb_crd_ovservation = 5,

    /**
     * @brief "Extra" global coord. This includes `stage_toilet`.
     */
    Glb_crd_extra       = 6,

    Glb_crd_bowling     = 7,
    Glb_crd_heaven      = 8,
    Glb_crd_apart       = 9,
    Glb_crd_hospital    = 10,
    Glb_crd_delusion    = 11,
    Glb_crd_hotel_face  = 12,
    Glb_crd_hotel_back  = 13,
    Glb_crd_last_stage  = 14,
    Glb_crd_unknown_15  = 15,

    /**
     * @brief Born From A Wish mansion map areas.
     *
     * @interesting 
     * !! this was likely present in the v0.10 prototype! This suggests they
     * were already working on Born From A Wish.
     */
    Glb_crd_mansion   = 16,

    Glb_crd_num       = 17,
} Sh2GlobalCoord;

typedef struct Block {
    // Members
    short xz; // offset 0x0, size 0x2
    short block; // offset 0x2, size 0x2
} Block;

int RoomNameJms(void);
int RoomName(int glb_crd, float pos_x, float pos_z);
int BlockNumber(int* ret, int glb_crd, float pos_x, float pos_z);
int BgIsOut(int glb_crd);

#endif // STG_NAME_H
