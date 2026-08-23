#include "sh2_common.h"

#include "Event/chara_data_load.h"
#include "Event/stg_name.h"

#include "data/fs_structs.h"
#include "Multi_thr/filesys/fcread.h"
#include "FilesList/fileslist_bg.h"
#include "LoadBg/loadbg_chara.h"

#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"

#include "Chacter/character.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/chara_list.h"
#include "Chacter/chara_bound.h"
#include "Chacter/bg_chara.h"

typedef struct /* @anon4 */ {
    // total size: 0x24
    int now[2]; // offset 0x0, size 0x8
    void* nowp[2]; // offset 0x8, size 0x8
    int pre[2]; // offset 0x10, size 0x8
    void* prep[2]; // offset 0x18, size 0x8
    int cnt; // offset 0x20, size 0x4
} BgCharaManData;
extern sh2gfw_Model_Header* model[2]; // size: 0x8, address: 0x11EB538
extern BgCharaManData d_0x011EB510; // size: 0x24, address: 0x11EB510
#define d d_0x011EB510

#line 31
static int get_block_num(fsFileIndex* id /* r2 */) {
    u_long size;
    
    
    size = FcGetFileSize(id); // r3
    
    
    

    
    if (size != 0) return (((size + 0x3FFFF) / 0x40000)); return -1;
}

#line 45
int BgCharaGetBlockSize(fsFileIndex* id /* r2 */) {
    return get_block_num(id);
}

#line 50
static int BgCharaRelocateItemSet(int glb_crd /* r18 */, int mapno /* r19 */, int chara_id /* r2 */) {
    fsFileIndex* file[3]; // r29+0x50
    fsFileIndex* cid; // r16
    int result; // r2
    int n; // r17
    FilesBgBlock* bp; // r18
    fsFileIndex* p0; // r2
    fsFileIndex* p1; fsFileIndex* bp_3; s8* p1_2; s8* p1_3; s8* p1_4;
    if ((chara_id >> 8) != 3) return 0;
    result = CharaDataFileSearch(file, chara_id);
    cid = file[0];
    ASSERT_ON_LINE(result, 61);
    n = get_block_num(cid);
    bp = FilesGetBgBlock(glb_crd & 0xFF, mapno);
    ASSERT_ON_LINE(bp, 64);
    p0 = bp->ex0;
    if ((int) bp->ex0 & 0x80000000) {
        p0 = (fsFileIndex* ) ((int) bp->ex0 ^ 0x80000000);
    }
    p1 = bp->ex1;
    if ((int) bp->ex1 & 0x80000000) {
        p1 = (fsFileIndex* ) ((int) bp->ex1 ^ 0x80000000);
    }
    if (n == 1) {
        if ((bp->ex0 == NULL) || (p0 == cid)) {
            if (bp->ex0 == NULL) bp->ex0 = cid;
            return (int) bp->ex0 & 0x80000000 ? 0 : 1;
        } else if ((bp->ex1 == NULL) || (p1 == cid)) {
            if (bp->ex1 == NULL) bp->ex1 = cid;
            return !((int) bp->ex1 & 0x80000000) ? 1 : 0;
        }
        printf("error ex1 and ex2 full slot!", p1, bp->ex0, bp->ex1);
        printf("map %d\n", mapno);
        printf("ex0 %s\n", bp->ex0->index.name);
        printf("ex1 %s\n", bp->ex1->index.name);
        printf("add %s\n", cid->index.name);
    
    
    } else if (n == 2) {
        if (((bp->ex0 == NULL) || (p0 == cid)) && ((bp->ex1 == NULL) || (p1 == cid))) {
            if (bp->ex0 == NULL) bp->ex0 = cid;
            
            return (int) bp->ex0 & 0x80000000 ? 0 : 1;
        }
        printf("error bg chara over size", p1, bp->ex0, bp->ex1);
        printf("map %d\n", mapno);
        printf("ex0 %s\n", bp->ex0->index.name);
        printf("ex1 %s\n", bp->ex1->index.name);
        printf("add %s\n", cid->index.name);

        
    } else {
        printf("error bg chara over size", p1, bp->ex0, bp->ex1);
        printf("map %d\n", mapno);
        printf("ex0 %s\n", bp->ex0 ? bp->ex0->index.name : "nil");
        printf("ex1 %s\n", bp->ex1 ? bp->ex1->index.name : "nil");
        printf("add %s\n", cid ? cid->index.name : "nil");
    }
    
    return 1;
}

#line 112
static inline MapIdNo(int value) { return (u_short) value; }
static void BgCharaRelocateItemSetXZ(int glb_crd /* r18 */, float x /* r29+0x50 */, float z /* r29+0x50 */, int chara_id /* r17 */) {
    int block[4]; // r29+0x40
    int result; // r2
    float r; // r29+0x50
    int mapid; // r2
    
    BlockNumber(block, glb_crd, x, z);
    ASSERT(MapIdNo(block[0]));
    mapid = MapIdNo(block[0]);
    r = CharaGetBoundR(chara_id);
    BgCharaRelocateItemSet(glb_crd, mapid, chara_id);
















   
}

#line 144
void BgCharaRelocateSet(int glb_crd /* r2 */, float x /* r29+0x10 */, float z /* r29+0x10 */, int chara_id /* r2 */) {
    BgCharaRelocateItemSetXZ(glb_crd, x, z, chara_id);
}

#line 151
int BgCharaIsId(int chara_id /* r2 */) {
    return (chara_id >> 8) == 3;
}

#line 155
void* BgCharaIsLoad(int chara_id /* r2 */) {
    int i; // r3
    
    if (!(chara_id >> 8) == OBJECT_SKELETAL_OUTDOOR_CHARA_KIND) {
        return NULL;
    }
    for (i = 0; i < 2; i++) {
        if (chara_id != d.now[i]) continue;
        if (LoadBgCharaIsLoadSlot(i)) {
            return d.nowp[i];
        }


        else break;
    }
    return NULL;
}

#line 174
static void init(void* adr /* r2 */, int chara_id /* r17 */) {
    SubCharacter* scp; // r16
    sh2gfw_ModelDrawInit_for_BackgroundLoad(chara_id, adr, NULL, NULL, 0);
    scp = shCharacter_Manage_GetCharacterList();
    for (; scp != NULL; scp = scp->next)
        if (scp->kind == chara_id)
            shCharacter_Manage_SetDataAdresss(scp);
}

#line 189
void BgCharaManInit(void) {
    memset(&d, 0, sizeof(BgCharaManData));
}

#line 194
void BgCharaMan(int cnt /* r2 */) {
    int i; // r16

    d.cnt = cnt;
    if (cnt == 0) {
        LoadBgGetUraCharaSlot(model, model + 1);
        
        for (i = 0; i < 2; i++) {
            d.prep[i] = d.nowp[i];
            d.pre[i] = d.now[i];
            d.nowp[i] = model[i];
            d.now[i] = model[i] != NULL ? model[i]->chara_id : 0;
            if (d.pre[i] != d.now[i]) {
                if (d.now[i] != 0) {
                    init(d.nowp[i], d.now[i]);
                    printf("slot%d(%d)init ok %p\n", i, d.now[i], d.nowp[i]);
                } else if (d.pre[i] != 0) {
                    printf("slot%d(%d)del ok %p\n", i, d.pre[i], d.prep[i]);
                }
            }
        }
    }
}

#line 219
void BgCharaDelSlot(int slot /* r2 */) {
    d.prep[slot] = d.nowp[slot];
    d.pre[slot] = d.now[slot];
    d.now[slot] = 0;
    d.nowp[slot] = NULL;
}

#line 227
int BgCharaGetSlotId(int slot /* r2 */) {
    return d.now[slot];
}
