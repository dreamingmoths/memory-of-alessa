#include "item.h"

void ItemDataInit(void) {
    shQzero(&item, 0x34);
    ItemGet(0x11);
    ItemGet(0x12);
    item.light_switch = 1;
    item.radio_switch = 1;
    item.radio_volume = 0xC;
}

void ItemGet(int kind /* r16 */) {
    int num;
    int work;

    SET_FLAG(item.flag, kind);
    
    if ((kind != 0x11) && (kind != 0x12)) {
        GameItemGetCountUp();
    }

    switch (kind) {
        case 4: case 5:
            work = 10; break;
        case 6: case 7:
            work = 6; break;
        case 8: case 9:
            work = 4; break;
        case 10: work = 8; break;
        case 1:
        case 2:
        case 3: work = 1; break;
        default: return;
    }
    
    switch (kind) {
        case 5:
        case 7:
        case 9:
            work *= playing.bullet_adjust;
            break;
    }
    
    item.number[kind] = clamp(item.number[kind] + work, 999);
    return;
}

int ItemUse(int kind /* r2 */) {

    if (kind < 11) {
        if (item.number[kind] > 0) {
            item.number[kind]--;
            if (item.number[kind] != 0) {
                return 1;
            }
        }
    }

    if (kind < 0x4B) {        
        if ((((kind != 4) && (kind != 6)) && (kind != 8)) && (kind != 10)) {
            REMOVE_FLAG(item.flag, kind); 
        }
    } else {            
        switch (kind) {
            case 0x4B:
                //REMOVE_FLAG(item.flag + 1, 0);
                item.flag[1] &= ~1;
                //REMOVE_FLAG(item.flag + 1, 1);
                item.flag[1] &= ~2;
                break;
            case 0x4C:
                item.flag[1] &= 0xFFFBFFFF;
                item.flag[1] &= 0xFFF7FFFF;
                break;
            case 0x4D:
                item.flag[1] &= 0xFFDFFFFF;
                item.flag[1] &= 0xFFBFFFFF;
                break;
            case 0x4E:
                item.flag[1] &= 0xFEFFFFFF;
                item.flag[1] &= 0xFDFFFFFF;
                break;
            case 0x4F:
                item.flag[1] &= 0xFEFFFFFF;
                item.flag[1] &= 0xFBFFFFFF;
                break;
            case 0x50:
                item.flag[1] &= 0xFDFFFFFF;
                item.flag[1] &= 0xFBFFFFFF;
                break;
            case 0x51:
                item.flag[1] &= 0xFEFFFFFF;
                item.flag[1] &= 0xFDFFFFFF;
                item.flag[1] &= 0xFBFFFFFF;
                break;
            case 0x55:
                item.flag[1] &= 0xF7FFFFFF;
                item.flag[1] &= 0xEFFFFFFF;
                item.flag[1] &= 0xDFFFFFFF;
                break;
        }
    }
    return 0;
}

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

#line 198

int ItemWeaponReload(int kind, int use) {
    int work;
    int weapon;
    int bullet;

    if (kind == 0) { kind = item.equip; }

    switch (kind) {
        case 4: 
        case 6: 
        case 8:
            weapon = kind;
            kind++;
            break;
        case 5: 
        case 7:
        case 9:
            weapon = kind - 1;

            break;
        case 10:
            if (use == 0) { return 1; }
            item.number[10] = 8;
            return 8;
        default:
            return 1;
    }

    if (use == 0) { return item.number[kind]; }

    if (!GET_FLAG(item.flag, weapon)) { printf("item.c:230> assert:(%s)\n", "((*(item.flag+((weapon)>>5))>>((weapon)&31))&1)"); while (1); }

    item.number[kind] += item.number[weapon];
    item.number[weapon] = 0;

    switch (weapon) {
        default: case 4: 
            bullet = 10; break;
        case 6: bullet = 6; break;
        case 8: bullet = 4; break;
    }

    if (bullet >= item.number[kind]) {
        bullet = item.number[kind];
        REMOVE_FLAG(item.flag, kind);
    }

    item.number[weapon] += bullet;
    item.number[kind] -= bullet;
    return item.number[weapon];
}

int ItemMedicineUse(signed int kind) {

    if ((kind != HEALTH_DRINK) && (kind != FIRST_AID_KIT) && (kind != AMPOULE)) {
        return 0;
    }

    if (item.number[kind] == 0) {
        return 0;
    }

    ItemUse(kind);

    if (kind == HEALTH_DRINK) {
        sh2jms.player->battle.hp += 0.25f * sh2jms.player->battle.hp_max;
    } else if (kind == FIRST_AID_KIT) {
        sh2jms.player->battle.hp += 0.5f * sh2jms.player->battle.hp_max;
    } else {
        sh2jms.player->battle.hp += sh2jms.player->battle.hp_max;
        item.ampoule_efficacy = 600.0f;
    }

    if (sh2jms.player->battle.hp > sh2jms.player->battle.hp_max)
        sh2jms.player->battle.hp = sh2jms.player->battle.hp_max;

    return 1;
}

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
