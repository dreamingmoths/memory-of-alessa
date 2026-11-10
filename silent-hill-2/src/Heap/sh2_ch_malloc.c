#include "Heap/sh2_ch_malloc.h"

utilHeapCtrl* shCh_ASCDAT_Ctrl = NULL;  // size: 0x4, address: 0xF8E708
u_long128 Anim_Skl_Cls_Data[32772];     // size: 0x80040, address: 0xF8E710

#line 34
utilHeapCtrl* shCh_ASC_InitHead(void* bufhead, int size) {   
    u_int align;
    

    switch (align = (u_int) bufhead & 0x3F) {
        case 16:
            bufhead = ((u_char *)bufhead + 0x10);
            break;    
        case 32:
            break;    
        
        case 48:
            bufhead = ((u_char *)bufhead + 0x30);
            break;    
        case 0:
            bufhead = ((u_char *)bufhead + 0x20);
            break;    
        default:
            DEBUG_LOG_ON_LINE(52, "heap init error\n");
            while (true);
    }
    
    
    
    shCh_ASCDAT_Ctrl = utilHeapInit(bufhead, size);
    
    if (bufhead != shCh_ASCDAT_Ctrl) {
        printf("ASC-address mismatch.\n");
        while (true);
    }
    return shCh_ASCDAT_Ctrl;    
}

#line 70
void* shCh_ASC_Malloc(u_int n) {
    void* p; 
    

    n += 0xF;
    n &= ~0xF;
    
    switch (n & 0x3F) {
        case 0:
            n += 48; 
            break;      
        case 16:
            n += 32; 
            break;    
        case 32:
            n += 16; 
            break;    
        case 48:
            break;      
        default:
            DEBUG_LOG_ON_LINE(90, "halted!\n");
            while (true);
    }
    
    
    p = utilHeapMalloc(shCh_ASCDAT_Ctrl, n);
    
    
    if ((u_int) p & 0x3F) {
        printf("allocate buffer align error.\n");
        while(true);
    }
    
    
    if (p == NULL) {
        printf("ASC-can't allocated.\n");
        while(true);
    }
    memset(p, 0, n);
    
    return p;    
}

void shCh_ASC_Free(void* p) {
    utilHeapFree(p);
}

void kari_ChAlloc_Init(void) {
    shCh_ASC_InitHead(&Anim_Skl_Cls_Data, sizeof(Anim_Skl_Cls_Data));
}
