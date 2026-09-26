#include "LoadBg/loadbg_cam.h"
#include "DBG/verbose.h"
#include "view/vc_calc.h"

static loadBgCAM_Ctrl lbCAM_Ctrl = {0};

static int _loadBgCAM_Delete(int slot);
static int _loadBgCAM_Regist(int slot, int mapid, void* addr, int size);
static int _loadBgCAM_Replace(int slot, int mapid, void* addr, int size);

static int _loadBgCAM_Delete(int slot) {
    void* addr;
    ASSERT_ON_LINE(0<=slot && slot<LBM_CAM_SLOTS, 27);
    addr = lbCAM_Ctrl.addr[slot];
    lbCAM_Ctrl.mapid[slot] = 0;
    lbCAM_Ctrl.addr[slot] = NULL;
    lbCAM_Ctrl.size[slot] = 0;
    if (addr == NULL) {
        return 0;
    }
    loadBgCAM_vcReset();
    return 1;

}

static int _loadBgCAM_Regist(int slot, int mapid, void* addr, int size) {
    ASSERT_ON_LINE(0<=slot && slot<LBM_CAM_SLOTS, 42);

    if ((mapid == lbCAM_Ctrl.mapid[slot]) &&
        (lbCAM_Ctrl.addr[slot] == addr) &&
        (lbCAM_Ctrl.size[slot] == size)) {
        
        return 0;
    }
    lbCAM_Ctrl.mapid[slot] = mapid;
    lbCAM_Ctrl.addr[slot] = addr;
    lbCAM_Ctrl.size[slot] = size;
    if (addr != NULL) {
        vcConvertCamFile(addr);
        loadBgCAM_vcReset();
    }
    return 1;

}

static int _loadBgCAM_Replace(int slot, int mapid, void* addr, int size) {
    int ret = 0; 
    if (((mapid != lbCAM_Ctrl.mapid[slot]) ||
         (lbCAM_Ctrl.addr[slot] != addr) ||
         (lbCAM_Ctrl.size[slot] != size)) ) {
        
        if (_loadBgCAM_Delete(slot)) ret += 1;
    }
    if ((mapid != 0) && (addr != NULL) && (size > 0) ) {
        if (_loadBgCAM_Regist(slot, mapid, addr, size)) ret += 2;
    }
    return ret;
}

int loadBgCAM_ReplaceG(int mapid, void* addr, int size) {
    int ret;
    ret = _loadBgCAM_Replace(0, mapid, addr, size);
    switch (ret) {
        case 1:
            verbose(1, "- cam(G)\n");
            break;
        case 2:
            verbose(1, " +cam(G):0x%08x(@0x%08x+0x%08x)\n", mapid, addr, size);
            break;
        case 3:
            verbose(1, "-+cam(G):0x%08x(@0x%08x+0x%08x)\n", mapid, addr, size);
            break;
    }
    return ret;
}

int loadBgCAM_Replace(int slot, int mapid, void* addr, int size) {
    int ret;
    ret = _loadBgCAM_Replace(slot + 1, mapid, addr, size);
    switch (ret) {
        case 1:
            verbose(1, "- cam(%d)\n", slot);
            break;
        case 2:
            verbose(1, " +cam(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
            break;
        case 3:
            verbose(1, "-+cam(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
            break;
    }
    return ret;
}

void** loadBgCAM_GetLoadedDataAddrList(void) {
    int i;
    int j;   
    void* addr;

    j = 0;
    for (i = 0; i < LBM_CAM_SLOTS; i++) {
        addr = lbCAM_Ctrl.addr[i];
        if (addr != NULL) lbCAM_Ctrl.list[j++] = addr;        
    }
    lbCAM_Ctrl.list[j] = NULL;

    return lbCAM_Ctrl.list;
}

void loadBgCAM_vcReset(void) {
    void** list;
    list = loadBgCAM_GetLoadedDataAddrList();
    vcWork.vc_road_ary_list = list;
}
