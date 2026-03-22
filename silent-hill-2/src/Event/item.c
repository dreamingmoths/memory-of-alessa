#include "item.h"

void ItemDataInit(void) {
    shQzero(&item, 0x34);
    ItemGet(0x11);
    ItemGet(0x12);
    item.light_switch = 1;
    item.radio_switch = 1;
    item.radio_volume = 0xC;
}

INCLUDE_ASM("asm/nonmatchings/Event/item", ItemGet);

INCLUDE_ASM("asm/nonmatchings/Event/item", ItemUse);

int ItemWeaponShoot(signed int kind /* r16 */, signed int use /* r2 */) {
    if (kind == 0) {
        kind = item.equip;
    }
    if ((kind != 0xA) && (kind != 8) && (kind != 6) && (kind != 4)) {
        return 1;
    }
    if (!GET_FLAG(item.flag, kind)) {
        return 0;
    }
    if (use != 0) {
        ItemUse(kind);
    }
    return item.number[kind];
}

INCLUDE_ASM("asm/nonmatchings/Event/item", ItemWeaponReload);

INCLUDE_ASM("asm/nonmatchings/Event/item", ItemMedicineUse);

float ItemAmpolueEfficacy(void) {
    float work = item.ampoule_efficacy;
    
    if (work == 0.0f) return 0.0f;
    if (work > 300.0f) return 1.0f;
    return work / 300.0f;
}

int ItemEventCheck(signed int kind_0 /* r2 */, signed int kind_1 /* r2 */, signed int kind_2 /* r2 */) {
    int use_item;

    use_item = ItemCombinationUseCheck(kind_0, kind_1, kind_2);
    if (use_item == 0) {
        return -2;
    }
    return EventCheck(0, use_item, 1);
}

#line 357
int ItemCombinationUseCheck(int kind_0, int kind_1, int kind_2) {
    int i;
    int kind_x;

    if (kind_1 < kind_0) { kind_x = kind_0; kind_0 = kind_1; kind_1 = kind_x; }
    if (kind_2 < kind_0) { kind_x = kind_0; kind_0 = kind_2; kind_2 = kind_x; }
    if (kind_2 < kind_1) { kind_x = kind_1; kind_1 = kind_2; kind_2 = kind_x; }
    
    
    if (kind_1 == 0) {
        kind_x = kind_2;
    } else {
        kind_x = 0;
        for (i = 0; i < 11; i++) {
            if (kind_0 == cmb_check_1042[i][0] 
                && kind_1 == cmb_check_1042[i][1]
                && kind_2 == cmb_check_1042[i][2]) {
                kind_x = cmb_check_1042[i][3];
                break;
            }
        }
    }
    return kind_x;
}

void ItemPutForShelf(void) {
    stage->ev_prog[1]();;
}
