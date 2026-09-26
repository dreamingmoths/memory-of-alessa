#include "LoadBg/loadbg_cld.h"
#include "DBG/verbose.h"

static loadBgCLD_Ctrl lbCLD_Ctrl = {0};

static int _loadBgCLD_Delete(int slot);
static int _loadBgCLD_Regist(int slot, int mapid, void* addr, int size);
static int _loadBgCLD_Replace(int slot, int mapid, void* addr, int size);

static int _loadBgCLD_Delete(int slot) {
    void* addr;
    ASSERT_ON_LINE(0<=slot && slot<LBM_CLD_SLOTS, 21);   
    addr = lbCLD_Ctrl.addr[slot];
    lbCLD_Ctrl.mapid[slot] = 0;
    lbCLD_Ctrl.addr[slot] = NULL;
    lbCLD_Ctrl.size[slot] = 0;
    return (addr != NULL);  
}

static int _loadBgCLD_Regist(int slot, int mapid, void* addr, int size) {
    ASSERT_ON_LINE(0<=slot && slot<LBM_CLD_SLOTS, 31);    
    if ((mapid == lbCLD_Ctrl.mapid[slot]) &&
        (lbCLD_Ctrl.addr[slot] == addr) &&
        (lbCLD_Ctrl.size[slot] == size)) {
        
        return 0;
    }
    lbCLD_Ctrl.mapid[slot] = mapid;
    lbCLD_Ctrl.addr[slot] = addr;
    lbCLD_Ctrl.size[slot] = size;
    return 1;

}

static int _loadBgCLD_Replace(int slot, int mapid, void* addr, int size) {
    int ret = 0; 
    if (((mapid != lbCLD_Ctrl.mapid[slot]) ||
         (lbCLD_Ctrl.addr[slot] != addr) ||
         (lbCLD_Ctrl.size[slot] != size))) {
        
        if (_loadBgCLD_Delete(slot) != 0) ret++;
    }
    if ((mapid != 0) && (addr != NULL) && (size > 0)) {
         if (_loadBgCLD_Regist(slot, mapid, addr, size) != 0) ret += 2;
    }
    return ret;
}

int loadBgCLD_Replace(int slot, int mapid, void* addr, int size) {
    int ret;
    ret = _loadBgCLD_Replace(slot, mapid, addr, size);
    switch (ret) {
    case 1:
        verbose(1, "- cld(%d)\n", slot);
        break;
    case 2:
        verbose(1, " +cld(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        break;
    case 3:
        verbose(1, "-+cld(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        break;
    }
    return ret;
}

void** loadBgCLD_GetLoadedDataAddrList(void) {
    int i;
    int j;   
    void* addr;

    j = 0;
    for (i = 0; i < LBM_CLD_SLOTS; i++) {
        addr = lbCLD_Ctrl.addr[i];
        if (addr != NULL) lbCLD_Ctrl.list[j++] = addr;        
    }
    lbCLD_Ctrl.list[j] = NULL;

    return lbCLD_Ctrl.list;
}
