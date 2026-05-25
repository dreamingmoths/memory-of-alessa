#ifndef CHARA_DATA_LOAD_H
#define CHARA_DATA_LOAD_H

#include "sh2_common.h"
#include "FilesList/fileslist_bg.h"

#define CATEGORY_NULL 0

// total size: 0xC
typedef struct CharaData_MemAdmin_One {
    // Members
    union fsFileIndex* file; // offset 0x0, size 0x4
    u_long128* adress; // offset 0x4, size 0x4
    int size; // offset 0x8, size 0x4
} CharaData_MemAdmin_One;

// total size: 0x34
typedef struct CharaData_MemAdmin {
    // Members
    s_char category; // offset 0x0, size 0x1
    s_char priority; // offset 0x1, size 0x1
    short kind; // offset 0x2, size 0x2
    struct CharaData_MemAdmin_One model; // offset 0x4, size 0xC
    struct CharaData_MemAdmin_One animation; // offset 0x10, size 0xC
    struct CharaData_MemAdmin_One shadow; // offset 0x1C, size 0xC
    struct CharaData_MemAdmin_One cluster; // offset 0x28, size 0xC
} CharaData_MemAdmin;

// total size: 0x8
typedef struct CharaData_ItemFile {
    // Members
    int kind; // offset 0x0, size 0x4
    union fsFileIndex* file; // offset 0x4, size 0x4
} CharaData_ItemFile;

// total size: 0xC
typedef struct CharaData_EntryList_One {
    // Members
    int load; // offset 0x0, size 0x4
    union fsFileIndex* file; // offset 0x4, size 0x4
    u_long* adress; // offset 0x8, size 0x4
} CharaData_EntryList_One;

// total size: 0x14
typedef struct CharaData_WeaponFile {
    // Members
    short equip; // offset 0x0, size 0x2
    short kind; // offset 0x2, size 0x2
    union fsFileIndex* james_anim; // offset 0x4, size 0x4
    union fsFileIndex* weapon_model; // offset 0x8, size 0x4
    union fsFileIndex* weapon_model_r; // offset 0xC, size 0x4
    union fsFileIndex* shadow_model; // offset 0x10, size 0x4
} CharaData_WeaponFile;

// total size: 0x38
typedef struct CharaData_EntryList {
    // Members
    int category; // offset 0x0, size 0x4
    short delete; // offset 0x4, size 0x2
    short kind; // offset 0x6, size 0x2
    struct CharaData_EntryList_One model; // offset 0x8, size 0xC
    struct CharaData_EntryList_One animation; // offset 0x14, size 0xC
    struct CharaData_EntryList_One shadow; // offset 0x20, size 0xC
    struct CharaData_EntryList_One cluster; // offset 0x2C, size 0xC
} CharaData_EntryList;

// total size: 0x14
typedef struct CharaData_DemoList {
    // Members
    int kind; // offset 0x0, size 0x4
    union fsFileIndex * model; // offset 0x4, size 0x4
    union fsFileIndex * animation; // offset 0x8, size 0x4
    union fsFileIndex * shadow; // offset 0xC, size 0x4
    union fsFileIndex * cluster; // offset 0x10, size 0x4
} CharaData_DemoList;

// total size: 0x10
typedef struct CharaData_StandardList {
    // Members
    int kind; // offset 0x0, size 0x4
    union fsFileIndex* model; // offset 0x4, size 0x4
    union fsFileIndex* animation; // offset 0x8, size 0x4
    union fsFileIndex* shadow; // offset 0xC, size 0x4
} CharaData_StandardList;

// total size: 0x8
typedef struct CharaData_Extra {
    // Members
    u_long128* adress; // offset 0x0, size 0x4
    int size; // offset 0x4, size 0x4
} CharaData_Extra;

struct CharaData_MemAdmin mem_admin[32];
u_char chara_data_use[1024];
union fsFileIndex* stage_anim;
u_long128 CHRDATA[];
u_long128* chara_adress;
struct CharaData_Extra chara_data_extra[8];

union fsFileIndex data_chr_wp_jms_weapon_anm[1]; // size: 0x8, address: 0x3A1088
union fsFileIndex data_chr_jms_hhh_jms_kg1[1]; // size: 0x8, address: 0x3A0D68
union fsFileIndex data_chr_jms_lll_jms_mdl[1]; // size: 0x8, address: 0x3A0F80
union fsFileIndex data_chr_jms_hll_jms_mdl[1]; // size: 0x8, address: 0x3A0D90
union fsFileIndex data_chr_jms_rlll_jms_mdl[1]; // size: 0x8, address: 0x3A0F98
union fsFileIndex data_chr_jms_rhll_jms_mdl[1]; // size: 0x8, address: 0x3A0F90

void CharaDataLoadInit(void);
void CharaDataLoadItem(void);
void CharaDataLoadWeapon(void);
void CharaDataLoadEnemy(int kind /* r2 */);
void CharaDataLoadStage(void);

void CharaDataLoadDemo(CharaData_DemoList* dlp, int status);
void CharaDataLoadCancel(CharaData_DemoList* dlp);

void CharaDataDeleteAll(void);
void CharaDataDeleteOne(int kind);
void CharaDataDeleteExtra(void);
int CharaDataFileSearch(union fsFileIndex** file /* r2 */, int kind /* r2 */);
void CharaDataBackLoadInit(void);
void CharaDataBackInit(CharaData_DemoList* dlp /* r18 */);

#endif // CHARA_DATA_LOAD_H
