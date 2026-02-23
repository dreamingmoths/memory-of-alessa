#include "utilheap.h"


utilHeapCtrl* utilHeapInit(void* buf, u_int bytesize) {
    u_int size; // $v1
    __int128 * bufhead; // $v0
    __int128 * buftail; // $v0
    utilHeapMBlock * mblock; // $v1
    utilHeapCtrl * heapctrl; // $v0
    u_int free; // $a0
    
    if (buf < (void *) 0x100000) return NULL;

    bufhead = (__int128 *) CEIL16((u_int) buf);
    size = FLOOR16((u_int) buf + bytesize);

    size -= (u_int) bufhead;

    if (size < 0x100) return NULL;

    heapctrl = (utilHeapCtrl *) bufhead;

    heapctrl->size = size;

    free = size - 0x20, heapctrl->free = free;

    buftail = (__int128*) (heapctrl + 1);
    mblock = (utilHeapMBlock*) buftail;

    mblock->size = free;
    mblock->heapctrl = 0;


    heapctrl->head = mblock;
    heapctrl->tail = mblock;

    mblock->prev = NULL;
    mblock->next = NULL;

    return heapctrl;
}

void* utilHeapMalloc(utilHeapCtrl* heapctrl, u_int n)
{
    utilHeapMBlock * mblock; // r3 $v1
    utilHeapMBlock * next; // r2 $v0
    u_int size; // r6 $a2
    u_int postsize; // r2 $v0
    utilHeapMBlock * postblock; // r7 $a3

    n = CEIL16(n);
    if (n == 0) return NULL;
    if (heapctrl->size < n) return NULL;


    mblock = (utilHeapMBlock*) heapctrl->head;
    while (mblock != NULL) {

        if (mblock->heapctrl == NULL) {

            size = mblock->size;
            if (size >= n) {

                heapctrl->free -= n;
                if (size != n) {
                    postblock = (utilHeapMBlock*) (n + (u_int) mblock + 0x10);
                    postsize = size - n - 0x10;
                    postblock->size = postsize;
                    postblock->heapctrl = NULL;
    
                    mblock->size = n;
    
                    heapctrl->free -= 0x10;
    
                    next = mblock->next;
                    postblock->next = next;
                    postblock->prev = mblock;
                    mblock->next = postblock;
                    if (next != NULL) {
                        next->prev = postblock;
                    } else {
                        heapctrl->tail = postblock;
                    }
                }
                mblock->heapctrl = heapctrl;
                return (void*)((u_char*)mblock + 0x10);
            }
        }

        mblock = mblock->next;
    }

    return NULL;
    
}

void utilHeapFree(void *obj)
{
    utilHeapMBlock *mblock;
    utilHeapCtrl   *heapctrl;
    utilHeapMBlock *preblock;
    utilHeapMBlock *postblock;

    if (obj == NULL)
        return;
    if ((u_int) obj & 0xF) {
        #ifdef DEBUG
        printf("utilheap.c:201> illegal address error in utilHeapFree().");
        #endif
        return;
    }

    mblock   = (utilHeapMBlock *) obj - 1;
    heapctrl = mblock->heapctrl;

    if ((u_int) heapctrl < 0x100000) {
        #ifdef DEBUG
        printf("utilheap.c:201> illegal address error in utilHeapFree().");
        #endif
        return;
    }

    mblock->heapctrl = NULL;
    heapctrl->free += mblock->size;

    postblock = mblock->next;
    if (postblock != NULL) {

        if (postblock->heapctrl == NULL) {
            utilHeapMBlock * next;

            u_int combinesize = mblock->size;
            combinesize += postblock->size + 0x10;
            mblock->size = combinesize;
            
            heapctrl->free += 0x10;

            
            next      = postblock->next;
            mblock->next   = next;
            if (next != NULL) {
                next->prev = mblock;
            }
            else {
                heapctrl->tail = mblock;
            }
        }
    }

    preblock = mblock->prev;
    if (preblock != NULL) {
    
        if (preblock->heapctrl == NULL) {
            utilHeapMBlock * next;

            u_int combinesize = preblock->size;
            combinesize += mblock->size + 0x10;
            preblock->size = combinesize;

            heapctrl->free += 0x10;

            
            next      = mblock->next;
            preblock->next   = next;
            if (next != NULL) {
                next->prev = preblock;
            }
            else {
                heapctrl->tail = mblock;
            }
        }
    }
}