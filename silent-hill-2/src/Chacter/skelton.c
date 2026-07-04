#include "sh2_common.h"
#include "Chacter/character.h"
#include "Chacter/skelton.h"

#define SH2_CHARACTER_NUM_SKELTONS 400

typedef struct shSkeltonWork {
    // total size: 0x17710
    shSkelton work[SH2_CHARACTER_NUM_SKELTONS]; // offset 0x0, size 0x17700
    shSkelton* free;                            // offset 0x17700, size 0x4
    int last;                                   // offset 0x17704, size 0x4
} shSkeltonWork;

shSkeltonWork sh2skelton; // size: 0x17710, address: 0x3CEFC0

void shCharacterInitSkeltons(void) {
    shSkelton* stp;
    int i;

    memset(&sh2skelton, 0, sizeof(sh2skelton));
    sh2skelton.last = SH2_CHARACTER_NUM_SKELTONS;

    stp = &sh2skelton.work[0];
    sh2skelton.free = sh2skelton.work;

    for (i = 0; i < SH2_CHARACTER_NUM_SKELTONS - 1; i++, stp++) {
        stp->next = stp + 1;
    }
    stp->next = NULL;
}

void shCharacterFreeSkeltons(shSkelton* top) {
    int i = 0;
    shSkelton* free;

    if (top != NULL) {

        free = sh2skelton.free;
        sh2skelton.free = top;
        for (; top->next != NULL; top = top->next) {
            sh2skelton.last++;

            i++;
        }
        sh2skelton.last++;

        top->next = free;

        printf("skeltons free %d rest %d\n", i + 1, sh2skelton.last);
    }
}

shSkelton* shCharacterGetSkeletons(int n, u_char* hrc) {
    shSkelton* stp;     // r3
    shSkelton* top_stp; // r16
    shSkelton* pre_stp; // r17
    int i;              // r4
    shSkelton* parent;  // r2
    int j;              // r2

    if (sh2skelton.last < n || n == 0) {
        return NULL;
    }
    sh2skelton.last -= n;

    stp = sh2skelton.free;
    top_stp = stp;
    pre_stp = NULL;
    for (i = 0; i < n; i++, pre_stp = stp, stp = stp->next, hrc++) {

        if (*hrc == 0xff) {
            stp->parent = NULL;

        } else {

            for (j = *hrc, parent = top_stp; j > 0 && parent != NULL; j--) {
                parent = parent->next;
            }
            stp->parent = parent;
        }
    }

    printf("skeltons get %d rest %d\n", n, sh2skelton.last, n);

    sh2skelton.free = pre_stp->next;
    pre_stp->next = NULL;
    return top_stp;
}
