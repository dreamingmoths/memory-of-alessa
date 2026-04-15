#include "sh2_ch_malloc.h"

utilHeapCtrl * shCh_ASC_InitHead(void * bufhead /* r16 */, int size /* r2 */) {
    u_int align; // r2
    
    align = (u_int) bufhead & 0x3F;
    switch (align) {
        case 16:
            bufhead = (void *)((char *)bufhead + 0x10);  // can it be written in a different way?
            break;    
        case 32:
            break;    
        case 48:
            bufhead = (void *)((char *)bufhead + 0x30);
            break;    
        case 0:
            bufhead = (void *)((char *)bufhead + 0x20);
            break;    
        default:
            printf("sh2_ch_malloc.c:52> heap init error\n");
            while (TRUE);
    }
    
    shCh_ASCDAT_Ctrl = utilHeapInit(bufhead, size);
    
    if (bufhead != shCh_ASCDAT_Ctrl) {
        printf("ASC-address mismatch.\n");
        while (TRUE);
    }

    return shCh_ASCDAT_Ctrl;    
}

void * shCh_ASC_Malloc(u_int n /* r17 */) {
    void * p; // r16
    
    n = (n += 0xF) & ~0xF; // macro?
    
    switch (n & 0x3F) {
        case 0:
            n += 0x30; // 48
            break;      
        case 16:
            n += 0x20; // 32
            break;    
        case 32:
            n += 0x10; // 16
            break;    
        case 48:
            break;      
        default:
            printf("sh2_ch_malloc.c:90> halted!\n");
            while (TRUE);
    }
    
    p = utilHeapMalloc(shCh_ASCDAT_Ctrl, n);
    if ((u_int) p & 0x3F) {
        printf("allocate buffer align error.\n");
        while(TRUE);
    }
    if (p == NULL) {
        printf("ASC-can't allocated.\n");
        while(TRUE);
    }
    memset(p, 0, n);
    return p;    
}

void shCh_ASC_Free(void * p /* r2 */) {
    utilHeapFree(p);
}

void kari_ChAlloc_Init(void) {
    shCh_ASC_InitHead(&Anim_Skl_Cls_Data, sizeof(Anim_Skl_Cls_Data));
}
