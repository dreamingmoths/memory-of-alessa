#include "Event/chara_data_load.h"
#include "Event/event.h"
#include "SH2_common/sh_vu0.h"
#include "connect.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"
#include "Chacter/sh2_character_manage.h"
#include "LoadBg/loadbg_event.h"

extern /* static */ CharaData_ItemFile bullet_and_drug_file[6];
extern /* static */ CharaData_StandardList enemy_list[15];
extern /* static */ CharaData_WeaponFile weapon_file[10];
extern /* static */ CharaData_StandardList item_list[168];

static int CharaDeleteNoUseOne(void);
static void CharaDataInfoFree(CharaData_MemAdmin* admin_p, int del);
static void CharaDataInfoFreeSub(CharaData_MemAdmin_One* maop);
static void CharaDataUseFree(u_long128* adr, int size);
static int SeekMemAdminCtgry(int category /* r16 */);
static int SeekMemAdminKind(int kind /* r2 */);

void CharaDataLoadInit(void) {
    shQzero(&mem_admin, sizeof(mem_admin));
    
    shQzero(&chara_data_use, sizeof(chara_data_use));     
    stage_anim = NULL;



    
    chara_adress = CHRDATA;
    
}

void CharaDataLoadItem(void) {
    CharaData_EntryList entry_list[6]; // r29+0x10
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
    CharaData_EntryList entry_list[3]; // r29+0x20
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
    CharaData_EntryList entry_list; // r29+0x30
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
    CharaData_EntryList entry_list[2]; // r29+0x20
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

void CharaDataLoadDemo(CharaData_DemoList* dlp, int status) {
    CharaData_EntryList entry_list[32]; // r29+0x40
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

void CharaDataLoadCancel(CharaData_DemoList* dlp) {

    
    sh2gfw_Cancel_LOADCharaModelData();
    if (dlp == NULL) return;    
    for (; dlp->kind != 0; dlp++) CharaDataDeleteOne(dlp->kind);    
}

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

static int CharaDeleteNoUseOne(void) { // not line matched
    int del_prio; // r3
    int del_no; // r4
    int i; // r5
   
    del_no = -1;
    del_prio = 2;
    for (i = 0; i < 32; i++) {        
        if (mem_admin[i].category != 0) {
            
            if (mem_admin[i].priority > del_prio) {
                del_prio = mem_admin[i].priority;
                del_no = i;
            }
        }
    }
    if (del_no == -1) return 0;    
    CharaDataInfoFree(&mem_admin[del_no], 0xF);
    return 1;
}


void CharaDataDeleteAll(void) {
    int i;
    
    for (i = 0; i < 32; i++) 
        if (mem_admin[i].category == 4) {
            CharaDataInfoFree(&mem_admin[i], 0xF);
        }
}


void CharaDataDeleteOne(int kind) { // not line matched
    SubCharacter* scp; // r2
    SubCharacter* next; // r16
    int i; // r16

    

    for (scp = shCharacter_Manage_GetCharacterList(); scp != NULL; scp = next) {
        next = scp->next;
        if ((scp->kind == kind) && (scp->kind != 0x100) && (scp->kind != 0x101) && ((scp->kind >> 8) != 8)) {            
            shCharacter_Manage_Delete(scp, 0, 0);
        }    
    }

    for (i = 0; i < 32; i++) {
        if (kind == mem_admin[i].kind) {
            CharaDataInfoFree(&mem_admin[i], 0xF);
        }
    }
}

static void CharaDataInfoFree(CharaData_MemAdmin* admin_p, int del) {
    if ((admin_p->model.file != NULL) && (del & 1)) {
        CharaDataInfoFreeSub(&admin_p->model);
    }
    if ((admin_p->animation.file != NULL) && (del & 2)) {
        CharaDataInfoFreeSub(&admin_p->animation);
    }
    if ((admin_p->shadow.file != NULL) && (del & 4)) {
        CharaDataInfoFreeSub(&admin_p->shadow);
    }
    if ((admin_p->cluster.file != NULL) && (del & 8)) {
        CharaDataInfoFreeSub(&admin_p->cluster);
    }
    if (del == 0xF) {
        sh2gfw_Delete_Model_from_CharaID(admin_p->kind);
        shQzero(admin_p, sizeof(CharaData_MemAdmin));
    }
}

static void CharaDataInfoFreeSub(CharaData_MemAdmin_One* maop) {

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

void CharaDataDeleteExtra(void) {
    int i;
    
    for (i = 0; i < 8; i++) {
        if (chara_data_extra[i].adress != NULL) CharaDataUseFree(chara_data_extra[i].adress,
                                                                 chara_data_extra[i].size);
    }    
    shQzero(chara_data_extra, sizeof(chara_data_extra));
    
}

int CharaDataFileSearch(union fsFileIndex** file /* r2 */, int kind /* r2 */) {
    int i; // r3
    for (i = 0; item_list[i].kind != 0; i++) {
        if (item_list[i].kind == kind) {
            file[0] = item_list[i].model;
            file[1] = item_list[i].animation;
            file[2] = item_list[i].shadow;
            return 1;
        }
    }
    return 0;
}

void CharaDataBackLoadInit(void) {
    LoadBgEventInit(chara_adress, 0x800000);
}

void CharaDataBackInit(CharaData_DemoList* dlp /* r18 */) {
    struct SubCharacter * scp; // r16
    int i; // r16    
    int j; // r19
    for (i = 0; dlp != NULL && dlp[i].kind != 0; i++) {
        j = SeekMemAdminKind(dlp[i].kind);
        sh2gfw_Delete_Model_from_CharaID(dlp[i].kind);
        sh2gfw_ModelDrawInit_for_BackgroundLoad(
            dlp[i].kind,
            mem_admin[j].model.adress,
            mem_admin[j].animation.adress,
            mem_admin[j].cluster.adress,
            mem_admin[j].shadow.adress);
    }
    for (scp = shCharacter_Manage_GetCharacterList(); scp != NULL; scp = scp->next) 
        shCharacter_Manage_SetDataAdresss(scp);
    
}

static int SeekMemAdminCtgry(int category /* r16 */) {
    int i; // r2

    for (i = 0; i < 32; i++) 
        if (mem_admin[i].category == category) break;    
    if (31 >= i) return i;

    
    if (category == CATEGORY_NULL) CharaDeleteNoUseOne();

    
    for (i = 0; i < 32; i++) 
        if (mem_admin[i].category == category) break;            
    
    ASSERT_ON_LINE(category != CATEGORY_NULL || i < 32, 1791);
    return i;
}

static int SeekMemAdminKind(int kind /* r2 */) {
    int i; // r2
    for (i = 0; i < 32; i++) 
        if (kind == mem_admin[i].kind) break;            
    return i;
}
