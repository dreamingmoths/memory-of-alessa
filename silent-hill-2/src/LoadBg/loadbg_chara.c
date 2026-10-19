#include "sh2_common.h"
#include "SH2_common/mem_share.h"

#include "Chacter/character.h"
#include "Chacter/sh2_character_manage.h"

#include "LoadBg/loadbg_mem.h"
#include "LoadBg/loadbg_chara.h"

#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"

#include "data/fs_structs.h"
#include "Event/event.h"
#include "Event/stg_name.h"
#include "FilesList/fileslist_bg.h"

typedef struct {
    // Members
    loadBgMem_LoadCtrl ctrl; // offset 0x0, size 0x18
    loadBgMem_UnitL UnitLArray[16]; // offset 0x18, size 0x100
    loadBgMem_UnitR UnitRArray[16]; // offset 0x118, size 0x100
    loadBgMem_CacheCtrl cache; // offset 0x218, size 0x18
    loadBgMem_UnitC UnitCArray[8]; // offset 0x230, size 0x80
    loadBgMem_Sect* SectList[3]; // offset 0x2B0, size 0xC
    loadBgMem_Sect SectListBuf[2]; // offset 0x2BC, size 0x28
    loadBgMem_File filelist[2]; // offset 0x2E4, size 0x20
    loadBgMem_Sect* CheckList[2]; // offset 0x304, size 0x8
    int memflg; // offset 0x30C, size 0x4
    loadBgMem_LoadCtrl* ctrlp; // offset 0x310, size 0x4
} LoadBgCharaData;

extern /* static */ LoadBgCharaData d_0x0037B5C0;
#define d d_0x0037B5C0

#line 59
static void initwork(void) {
    memset(d.filelist, 0, sizeof(d.filelist));
    d.SectList[0] = NULL;
    d.memflg = 0;
}

#line 86
static void memspy(void) {
    char* adr; // r2
    
    
    adr = MemShareGetBgCharaWorkAddr();
    if (adr == NULL) {
        printf("first bg NULL\n");
        d.ctrlp = NULL;
        adr = MemShareGetBgCharaWorkAddr();
    }
    if (adr == NULL) {
        printf("bg adr NULL\n");
        d.ctrlp = NULL;
        return;
    }
    if (d.ctrlp == 0) {
        printf("init adr NULL\n");
    
        
        LoadBgCharaInit();
    }
}

#line 115
static void subcharaupdate(int chara_id /* r17 */) {
    SubCharacter* scp; // r16
    
    scp = shCharacter_Manage_GetCharacterList();
    for (; scp != NULL; scp = scp->next) 
        if (scp->kind == chara_id) 
            shCharacter_Manage_SetDataAdresss(scp);         
}

#line 125
static void init_clean(void) {
    int i; // r16
    int id; // r17
    for (i = 0; i < 2; i++) {
        if (d.filelist[i].file != NULL && LoadBgCharaIsLoadSlot(i)) {
            
            
            
            id = BgCharaGetSlotId(i);
            if (id != 0) {
                printf("slot%d(%d) clear\n", i, id);
                sh2gfw_Delete_Model_from_CharaID(id);
                subcharaupdate(id);
                BgCharaDelSlot(i);
            }
        }
    }
}

#line 145
void LoadBgCharaInit(void) {
    char* adr; // r16
    char* cadr; // r17
    
    printf("init bg chara\n");
    MemShareGetBgCharaWorkAddr();
    adr = MemShareGetBgCharaWorkAddr();
    ASSERT_ON_LINE(adr, 152);
    cadr = adr + 0x80000;      
    ASSERT_ON_LINE(!((unsigned int)adr&0x3), 154);    
    init_clean();
    initwork();
    _loadBgMem_InitLoad(&d.ctrl, 0x8000, 16, d.UnitLArray, d.UnitRArray, adr);    
    
    
    
    
    _loadBgMem_InitCache(&d.cache, 0x8000, 8, d.UnitCArray, cadr);
    
    
    
    
    
    d.SectList[0] = &d.SectListBuf[0];
    d.SectList[1] = &d.SectListBuf[1];
    d.SectList[2] = NULL;
    d.ctrlp = &d.ctrl;
    BgCharaManInit();
}

#line 176
int LoadBgCharaIsLoad(void) {
    int cnt; // r2
    

    _loadBgMem_ClearRequest(d.ctrlp);
    loadBgMem_SetRequest(d.ctrlp,d.SectList);
    _loadBgMem_SyncLoadUnits(d.ctrlp);
    
    cnt = loadBgMem_CheckRequest(d.ctrlp, NULL);
    return !cnt || !d.ctrlp;
}

#define MAXSECT 2
#line 189
int LoadBgCharaIsLoadSlot(int no) {
    int cnt; // r2
    
    ASSERT_ON_LINE(no>=0 && no<MAXSECT, 192);
    d.CheckList[0] = &d.SectListBuf[no];
    
    _loadBgMem_ClearRequest(d.ctrlp);
    loadBgMem_SetRequest(d.ctrlp, d.CheckList);
    _loadBgMem_SyncLoadUnits(d.ctrlp);
    
    cnt = loadBgMem_CheckRequest(d.ctrlp, NULL);
    return !cnt || !d.ctrlp;
}


static int nowpos(void) {
    int glb_crd; // r2
    float px; float pz; 
    float dx; float dz; 
    int nowid = 0; // r2    
    sceVu0IVECTOR mapid; // r29+0x10
    
    if (sh2jms.player != NULL) {
        dx = 15.0f * sh2jms.pos.x;
        dz = 15.0f * sh2jms.pos.z;
        dx = shFloatClamp(dx, -1000.0f, 1000.0f);
        dz = shFloatClamp(dz, -1000.0f, 1000.0f);        
        dx = dz = 0.0f; // wtf?
        px = sh2jms.player->pos.x + dx;
        pz = sh2jms.player->pos.z + dz;
        if (stage != NULL) {
            glb_crd = stage->glb_crd;
            BlockNumber(mapid, glb_crd, px, pz);
            nowid = mapid[0];
        }
    }
    return nowid;
}



int LoadBgCharaIsMapEdge(void) {
    float px; float pz; int x; int z;

    px = sh2jms.player->pos.x;
    pz = sh2jms.player->pos.z;
    
    px = fabsf(px);
    pz = fabsf(pz);
    x = ftoi(px);
    z = ftoi(pz);
    x %= 20000;
    z %= 20000;
    if ((x > 2750.0f) && (x < 17250.0f))
        if ((z > 2750.0f) && (z < 17250.0f)) 
            return 0;
    
    
    return 1;
}

static void olddel(fsFileIndex* id /* r17 */, int slot /* r16 */) {
    struct sh2gfw_Model_Header* p; // r17  
    if (LoadBgCharaIsLoadSlot(slot) &&
        (d.filelist[slot].file != NULL) &&
        (d.filelist[slot].file != id)) {
        
        p = d.filelist[slot].addr;
        ASSERT_ON_LINE(p, 257);
        if (p->chara_id != 0) {
            printf("slot%d(%d) clear\n", slot, p->chara_id);
            sh2gfw_Delete_Model_from_CharaID(p->chara_id);
            subcharaupdate(p->chara_id);
            BgCharaDelSlot(slot);
        }
    }
}


static int chkslot(void** tmp, void* ex) {
    if (ex != NULL) {
        if (ex == d.filelist[0].file) {
            tmp[0] = ex;
        } else if (ex == d.filelist[1].file) {
            tmp[1] = ex;
        } else {
            return 1;
        }
    }
    return 0;
}


static void setslot(FilesBgBlock* bgfiles) {
    void* tmpslot[2] = { NULL }; // r29+0x48
    int exchg[2] = {0}; // r29+0x50 bss
    int slot; // r2    
    void* tbl[2] = {bgfiles->ex0, bgfiles->ex1}; // r29+0x58
    
    
    
    
    if (bgfiles != NULL) {
        if (tbl[0] != NULL) {
            exchg[0] = chkslot(tmpslot, tbl[0]);
        }
        if (tbl[1] != NULL) {
            exchg[1] = chkslot(tmpslot, tbl[1]);
        }
        if (exchg[0] != 0) {
            slot = tmpslot[0] ? 1 : 0;
            olddel(tbl[0], slot);
            d.filelist[slot].file = tbl[0];
            d.filelist[slot].ofsE = FcGetFileSize(tbl[0]);
            printf("slot%d(%s) load start\n", slot, ((fsFileIndex*) tbl[0])->index.name);
            if (BgCharaGetBlockSize(tbl[0]) == 2) {
                slot = slot ? 0 : 1;
                printf("big block slot%d clear\n", slot);
                olddel(tbl[0], slot);
                d.filelist[slot].file = NULL;
                d.filelist[slot].ofsE = 0;
            }
        }
        
        if ((exchg[1] != 0) && (tbl[0] != tbl[1])) {
            slot = (tmpslot[0] || exchg[0]) ? 1 : 0;
            olddel(tbl[1], slot);
            d.filelist[slot].file = tbl[1];
            d.filelist[slot].ofsE = FcGetFileSize(tbl[1]);
            printf("slot%d(%s) load start\n", slot, ((fsFileIndex*) tbl[1])->index.name);
        }
    }









}



void LoadBgCharaLoadSync(void) {
    int mapid; // r2
    int glb_crd; // r2
    int mapblock; // r2
    FilesBgBlock* bgfiles; // r16    
    int cnt; // r2


    memspy();
    
    
    mapid = nowpos();
    if (mapid != 0) {
        glb_crd = (mapid >> 16) & 0xFFFF;
        mapblock = mapid & 0xFFFF;
        bgfiles = FilesGetBgBlock(glb_crd, mapblock);
    }
    setslot(bgfiles);
    _loadBgMem_ClearRequest(d.ctrlp);
    loadBgMem_SetRequest(d.ctrlp, d.SectList);
    _loadBgMem_SyncLoadUnits(d.ctrlp);
    
    cnt = loadBgMem_LoadRequest(d.ctrlp,
                                &d.cache,
                                2,
                                1,
                                NULL,
                                NULL,
                                NULL,
                                NULL);
    
    
    BgCharaMan(cnt);
}

#line 372
void LoadBgGetUraCharaSlot(void** slot0, void** slot1) {
    if (d.ctrlp != NULL) {
        *slot0 = d.filelist[0].file ? d.filelist[0].addr : NULL;
        *slot1 = d.filelist[1].file ? d.filelist[1].addr : NULL;
    }


}
