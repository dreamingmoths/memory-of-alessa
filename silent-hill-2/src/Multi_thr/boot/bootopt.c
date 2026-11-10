#include "common.h"
#include "Multi_thr/boot/bootopt.h"
#include "Multi_thr/boot/bootoptitem.h"

extern BootOptItem BootOptItemList[20]; // size: 0x1E0, address: 0x33B6A0
extern s_char* D_01F01DEC;
extern int optind; // size: 0x4, address: 0x342F8C
#define optarg D_01F01DEC

static int key_index(int key) {
    if (key >= 'a' && key <= 'z') {
        key = key - 'G';
    } else if (key >= 'A' && key <= 'Z') {
        key = key - 'A';
    } else {
        key = -1;
    }
    return key;
}

#ifdef NON_MATCHING
void BootOptGet(int argc, s_char** argv) {
    s_char keylist[256]; // r29+0x60
    BootOptItem* keyitem[62] = {0}; // r29+0x160
    s_char* dst; // r16
    int len; // r2
    int rem; // r17
    int key; // r2
    int idx; // r2
    BootOptItem* item; // r18
    int (* get)(s_char *); // r2
    int var; // r2
    s_char* param; // r5

    for (rem = 0xFF, item = BootOptItemList, dst = keylist; rem > 0 && item->var != NULL; item++) {
        idx = key_index(item->key[0]);
        if (idx < 0) continue;
        keyitem[idx] = item;
        len = UtilStrCpyL(dst, item->key, rem);
        dst += len;
        rem -= len;
    
    }
    for (key = getopt(argc, argv, keylist); key != -1; key = getopt(argc, argv, keylist)) {
        param = optarg;
        idx = key_index(key);
        if (idx >= 0 && (item = keyitem[idx])) {
            get = item->get;
            if (get) {
                var = get(param);
            } else
                if (item->key[1] == ':') {
                    var = *(int*) param;
                } else {
                    var = 1;
                
                }
            item->set = 1;
            if (item->var) *(int*)item->var = var;
        }
    
    
    
    
    
    
    
    }
    while (optind < argc)
        
        
        
        
        
        
        optind++;
}
#else
INCLUDE_ASM("asm/nonmatchings/Multi_thr/boot/bootopt", BootOptGet);
BootOptItem* keyitem_0116D280[62];
#endif
