#include "Event/chara_data_load.h"
#include "Event/event.h"
#include "SH2_common/sh_vu0.h"
#include "connect.h"

extern /* static */ struct CharaData_ItemFile bullet_and_drug_file[6];
extern /* static */ struct CharaData_StandardList enemy_list[15];
extern /* static */ struct CharaData_WeaponFile weapon_file[10];

static void CharaDataInfoFreeSub(struct CharaData_MemAdmin_One* maop);
static void CharaDataUseFree(u_long128* adr, int size);

void CharaDataLoadInit(void) {
    shQzero(&mem_admin, sizeof(mem_admin));
    
    shQzero(&chara_data_use, sizeof(chara_data_use));     
    stage_anim = NULL;



    
    chara_adress = CHRDATA;
    
}

void CharaDataLoadItem(void) {
    struct CharaData_EntryList entry_list[6]; // r29+0x10
    int i; // r6

    
    shQzero(&entry_list, sizeof(entry_list));
    for (i = 0; i < 6; i++) {
        entry_list[i].category = 1;
        entry_list[i].kind = bullet_and_drug_file[i].kind;
        entry_list[i].model.file = bullet_and_drug_file[i].file;
    }
    CharaDataLoadExec(entry_list, 6, 0);
}

void CharaDataLoadWeapon(void) {
    struct CharaData_EntryList entry_list[3]; // r29+0x20
    int i; // r3
    
    for (i = 0; weapon_file[i].equip != -1; i++)
        if (weapon_file[i].equip == item.equip) break;
    ASSERT_ON_LINE(weapon_file[i].equip != -1, 639);
    
    shQzero(&entry_list, sizeof(entry_list));

    
    entry_list[0].category = 2;    
    if (stage->pc_model == 1) entry_list[0].kind = 0x101;        
    else entry_list[0].kind = 0x100;        
    entry_list[0].animation.file = weapon_file[i].james_anim;

    
    entry_list[1].category = 3;
    entry_list[1].kind = weapon_file[i].kind;
    entry_list[1].model.file = weapon_file[i].weapon_model;
    entry_list[1].shadow.file = weapon_file[i].shadow_model;
    
    if (GET_BIT(Sh2sys.main_status, 4)) {
        entry_list[2].category = 4;
        entry_list[2].kind = weapon_file[i].kind + 0x20;
        entry_list[2].model.file = weapon_file[i].weapon_model_r;
        CharaDataLoadExec(&entry_list, 3, 0);
    } else {
        CharaDataLoadExec(&entry_list, 2, 0);
    }
}

void CharaDataLoadEnemy(int kind /* r2 */) {
    struct CharaData_EntryList entry_list; // r29+0x30
    int i; // r5

    for (i = 0; enemy_list[i].kind != 0; i++)
        if(enemy_list[i].kind == kind) break;
    if (enemy_list[i].kind == 0) return;
        
    shQzero(&entry_list, sizeof(CharaData_EntryList));
    entry_list.category = 4;
    entry_list.kind = enemy_list[i].kind;
    entry_list.model.file = enemy_list[i].model;
    entry_list.animation.file = enemy_list[i].animation;
    entry_list.shadow.file = enemy_list[i].shadow;        
    
    CharaDataLoadExec(entry_list, 1, 0);
}

void CharaDataLoadStage(void) {
    struct CharaData_EntryList entry_list[2]; // r29+0x20
    int i; // r3
    
    for (i = 0; weapon_file[i].equip != -1; i++)
        if (weapon_file[i].equip == item.equip) break;    
    ASSERT_ON_LINE(weapon_file[i].equip != -1, 699);

    shQzero(entry_list, sizeof(entry_list));
    
    entry_list[0].category = 2;
    if (stage->pc_model == 1) {
        entry_list[0].kind = 0x101;
        entry_list[0].model.file = data_chr_jms_hll_jms_mdl;
    } else {
        entry_list[0].kind = 0x100;
        entry_list[0].model.file = data_chr_jms_lll_jms_mdl;
    }
    entry_list[0].animation.file = weapon_file[i].james_anim;
    entry_list[0].shadow.file = data_chr_jms_hhh_jms_kg1;
    
    entry_list[1].category = 3;
    entry_list[1].kind = weapon_file[i].kind;    
    entry_list[1].model.file = weapon_file[i].weapon_model;
    entry_list[1].animation.file = data_chr_wp_jms_weapon_anm;
    entry_list[1].shadow.file = weapon_file[i].shadow_model;
    
    CharaDataLoadExec(entry_list, 2, 0);
}

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadRoom);

void CharaDataLoadDemo(struct CharaData_DemoList* dlp, int status) {
    struct CharaData_EntryList entry_list[32]; // r29+0x40
    int entry_number; // r16
    int i; // r5

    entry_number = 0;
    shQzero(&entry_list, sizeof(entry_list));

    
    for (i = 0; dlp != NULL && dlp[i].kind != 0;  i++) {
        entry_list[entry_number].category = 4;
        entry_list[entry_number].kind = dlp[i].kind;
        entry_list[entry_number].model.file = dlp[i].model;
        entry_list[entry_number].animation.file = dlp[i].animation;
        entry_list[entry_number].shadow.file = dlp[i].shadow;
        entry_list[entry_number].cluster.file = dlp[i].cluster;
        entry_number++;
    }
    
    CharaDataLoadExec(entry_list, entry_number, status);
}

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadCancel);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExec);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExecItem);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExecJames);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExecWeapon);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExecStandard);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExecStandardSub0);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataWeaponTranslation);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataExtraTranslation);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataAnimSetExtra);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataAnimAdressExchange);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataLoadExtra);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataFreeSearch);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDeleteNoUseOne);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataDeleteAll);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataDeleteOne);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataInfoFree);

static void CharaDataInfoFreeSub(struct CharaData_MemAdmin_One* maop) {

    if (((u_int) maop->adress >= (u_int) chara_adress) && ((u_int) maop->adress < (u_int) (chara_adress + 0x80000))) {
        CharaDataUseFree(maop->adress, maop->size);
    }
    shQzero(maop, sizeof(CharaData_MemAdmin_One));
}

static void CharaDataUseFree(u_long128* adr, int size) { // not line matched
    int work; // r4
    int i; // r6

    if (adr == NULL || adr < chara_adress) return;
    
    work = (adr - chara_adress) >> 9;

    for (i = 0; i < (size >> 13); i++)
        chara_data_use[i + work] = 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataDeleteExtra);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataFileSearch);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataBackLoadInit);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", CharaDataBackInit);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", SeekMemAdminCtgry);

INCLUDE_ASM("asm/nonmatchings/Event/chara_data_load", SeekMemAdminKind);
