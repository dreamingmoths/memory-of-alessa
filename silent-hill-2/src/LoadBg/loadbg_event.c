#include "LoadBg/loadbg_event.h"

static void initwork(void);
static loadBgMem_File* getfilelist(void);
static loadBgMem_Sect* getfreesect(void);
static loadBgMem_Sect* getsect(void* adr);
static loadBgMem_Sect* setsect(void* adr, int size);
static void addsectlist(loadBgMem_Sect* sect);

// @todo: migrate bss

static void initwork(void) {
    memset(d.filelist, 0, sizeof(d.filelist));
    d.SectList[0] = 0;
}

static loadBgMem_File* getfilelist(void) {
    int i;

    for (i = 0; i < 1024; i++) {
        if (d.filelist[i].file == NULL) {
            return &d.filelist[i];
        }    
    }
    return NULL;
}

static loadBgMem_Sect* getfreesect(void) {
    int i;

    for (i = 0; i < 1024; i++) {
        if (d.SectListBuf[i].ofsE == 0) {
            return &d.SectListBuf[i];
        }
    }
    ASSERT_ON_LINE(0, 64);

}

static loadBgMem_Sect* getsect(void* adr) { // not line matched
    int i; // r3
    loadBgMem_Sect* p; // r2        

    for (i = 0; i < 1024; i++) {
        if (d.ctrl.Buffer + i * 0x2000 == adr) {
            p = getfreesect();
            p->ofsS = i << 13;
            return p;
        }  
    
    }

    ASSERT_ON_LINE(0, 81);
}

static loadBgMem_Sect* setsect(void* adr, int size) {
    loadBgMem_Sect* p;
    
    p = getsect(adr);

    ASSERT_ON_LINE(!p->ofsE, 91);
    p->ofsE = p->ofsS + (size + 0x1FFF) / 0x2000 * 0x2000;
    return p;
}

static void addsectlist(loadBgMem_Sect* sect) {
    int i;
    loadBgMem_Sect** l = d.SectList;     
    
    for (i = 0; ((i < 100) && (*l != NULL)); i++, l++) {
    }
    ASSERT_ON_LINE(!(*l && i==100), 112);
    *l = sect;
    
    *(l + 1) = 0;
}

void LoadBgEventInit(void* adr, u_int size) {
    int Units;

    ASSERT_ON_LINE(!((unsigned int)adr&0x3), 149);
    Units = (size + 0x1FFF) / 0x2000;
    _loadBgMem_InitLoad(&d.ctrl, 0x2000, Units, d.UnitLArray, d.UnitRArray,adr);
    
    
    
    
    _loadBgMem_InitCache(&d.cache, 0x2000, 4, d.UnitCArray, d.c_buf);
    
    
    
    
    
    
    
    initwork();
}

void LoadBgEventFileLoad(fsFileIndex* fileid, void* adr) {
    loadBgMem_Sect* p; // r5
    int size; // r16
    
    size = FcGetFileSize(fileid);
    p = setsect(adr, size);
    ASSERT_ON_LINE(p, 175);
    p->files = 1;
    p->filelist = getfilelist();
    ASSERT_ON_LINE(p->filelist, 178);
    p->filelist->file = fileid;
    p->filelist->ofsE = size;
    addsectlist(p);
}

void LoadBgEventLoadSync(void) {
    _loadBgMem_ClearRequest(&d.ctrl);
    loadBgMem_SetRequest(&d.ctrl, d.SectList);
    _loadBgMem_SyncLoadUnits(&d.ctrl);
    
    loadBgMem_LoadRequest(&d.ctrl, &d.cache, 2, 2, 0, 0, 0, 0);








}

int LoadBgEventListCnt(void) {
    int i; // r2
    loadBgMem_Sect** p = d.SectList; // r4
    for (i = 0; (*p != NULL) && (i < 100); i++, p++) {
    }
    return i;
}

int LoadBgEventLoadCnt(void) {
    int cnt; // r2
    
    
    _loadBgMem_ClearRequest(&d.ctrl);
    loadBgMem_SetRequest(&d.ctrl, d.SectList);
    _loadBgMem_SyncLoadUnits(&d.ctrl);
    
    cnt = loadBgMem_CheckRequest(&d.ctrl, NULL);
    return cnt;
}

int LoadBgEventIsLoad(void) {
    return !LoadBgEventLoadCnt();
}

void LoadBgEventDispose(void) {
    initwork();
    
}
