#ifndef CHARA_DATA_LOAD_H
#define CHARA_DATA_LOAD_H

#include "sh2_common.h"
#include "Chacter/character.h"
#include "data/fs_structs.h"

#define Category_null 0

// total size: 0xC
typedef struct CharaData_MemAdmin_One {
    // Members
    fsFileIndex* file; // offset 0x0, size 0x4
    u_long128* adress;       // offset 0x4, size 0x4
    int size;                // offset 0x8, size 0x4
} CharaData_MemAdmin_One;

// total size: 0x34
typedef struct CharaData_MemAdmin {
    // Members
    s_char category;                         // offset 0x0, size 0x1
    s_char priority;                         // offset 0x1, size 0x1
    short kind;                              // offset 0x2, size 0x2
    struct CharaData_MemAdmin_One model;     // offset 0x4, size 0xC
    struct CharaData_MemAdmin_One animation; // offset 0x10, size 0xC
    struct CharaData_MemAdmin_One shadow;    // offset 0x1C, size 0xC
    struct CharaData_MemAdmin_One cluster;   // offset 0x28, size 0xC
} CharaData_MemAdmin;

// total size: 0x8
typedef struct CharaData_ItemFile {
    // Members
    int kind;                // offset 0x0, size 0x4
    fsFileIndex* file; // offset 0x4, size 0x4
} CharaData_ItemFile;

// total size: 0xC
typedef struct CharaData_EntryList_One {
    // Members
    int load;                // offset 0x0, size 0x4
    fsFileIndex* file; // offset 0x4, size 0x4
    u_long* adress;          // offset 0x8, size 0x4
} CharaData_EntryList_One;

// total size: 0x14
typedef struct CharaData_WeaponFile {
    // Members
    short equip;                       // offset 0x0, size 0x2
    short kind;                        // offset 0x2, size 0x2
    fsFileIndex* james_anim;     // offset 0x4, size 0x4
    fsFileIndex* weapon_model;   // offset 0x8, size 0x4
    fsFileIndex* weapon_model_r; // offset 0xC, size 0x4
    fsFileIndex* shadow_model;   // offset 0x10, size 0x4
} CharaData_WeaponFile;

// total size: 0x38
typedef struct CharaData_EntryList {
    // Members
    int category;                             // offset 0x0, size 0x4
    short delete;                             // offset 0x4, size 0x2
    short kind;                               // offset 0x6, size 0x2
    struct CharaData_EntryList_One model;     // offset 0x8, size 0xC
    struct CharaData_EntryList_One animation; // offset 0x14, size 0xC
    struct CharaData_EntryList_One shadow;    // offset 0x20, size 0xC
    struct CharaData_EntryList_One cluster;   // offset 0x2C, size 0xC
} CharaData_EntryList;

// total size: 0x14
typedef struct CharaData_DemoList {
    // Members
    int kind;                     // offset 0x0, size 0x4
    union fsFileIndex* model;     // offset 0x4, size 0x4
    union fsFileIndex* animation; // offset 0x8, size 0x4
    union fsFileIndex* shadow;    // offset 0xC, size 0x4
    union fsFileIndex* cluster;   // offset 0x10, size 0x4
} CharaData_DemoList;

// total size: 0x10
typedef struct CharaData_StandardList {
    // Members
    int kind;                     // offset 0x0, size 0x4
    fsFileIndex* model;     // offset 0x4, size 0x4
    fsFileIndex* animation; // offset 0x8, size 0x4
    fsFileIndex* shadow;    // offset 0xC, size 0x4
} CharaData_StandardList;

// total size: 0x8
typedef struct CharaData_Extra {
    // Members
    u_long128* adress; // offset 0x0, size 0x4
    int size;          // offset 0x4, size 0x4
} CharaData_Extra;

void CharaDataLoadInit(void);
void CharaDataLoadItem(void);
void CharaDataLoadWeapon(void);
void CharaDataLoadEnemy(int kind);
void CharaDataLoadStage(void);
void CharaDataLoadRoom(int room);
void CharaDataLoadDemo(CharaData_DemoList* dlp, int status);
void CharaDataLoadCancel(CharaData_DemoList* dlp);
void CharaDataWeaponTranslation(int kind, fsFileIndex* file_anm, void* adr_anm, fsFileIndex* file_mdl, void* adr_mdl);
u_long128* CharaDataExtraTranslation(fsFileIndex* file, void* adress);
u_long128* CharaDataAnimSetExtra(int kind, fsFileIndex* file, u_long128* adress, int free);
u_long128* CharaDataAnimAdressExchange(SubCharacter* scp, u_long128* adr);
u_long128* CharaDataLoadExtra(fsFileIndex* file, int status);
void CharaDataDeleteAll(void);
void CharaDataDeleteOne(int kind);
void CharaDataDeleteExtra(void);
int CharaDataFileSearch(fsFileIndex** file, int kind);
void CharaDataBackLoadInit(void);
void CharaDataBackInit(CharaData_DemoList* dlp);

extern CharaData_MemAdmin mem_admin[32];
extern u_char chara_data_use[1024];
extern fsFileIndex* stage_anim;
extern u_long128 CHRDATA[];
extern u_long128* chara_adress;
extern CharaData_Extra chara_data_extra[8];

#endif // CHARA_DATA_LOAD_H
