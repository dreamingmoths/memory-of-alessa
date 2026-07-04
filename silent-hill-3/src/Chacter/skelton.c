#include "common.h"
#include "Chacter/character.h"
#include "Chacter/skelton.h"

#define SH3_CHARACTER_NUM_SKELTONS 400

typedef struct shSkeltonWork {
    // total size: 0x15E10
    shSkelton work[SH3_CHARACTER_NUM_SKELTONS]; // offset 0x0, size 0x15E00
    shSkelton* free;                            // offset 0x15E00, size 0x4
    int last;                                   // offset 0x15E04, size 0x4
} shSkeltonWork;

shSkeltonWork sh3skelton; // address: 0x046E870, size: 0x15E10

void shCharacterInitSkeltons(void) {
    shSkelton* stp;
    int i;

    memset(&sh3skelton, 0, sizeof(sh3skelton));
    sh3skelton.last = SH3_CHARACTER_NUM_SKELTONS;

    stp = &sh3skelton.work[0];
    sh3skelton.free = sh3skelton.work;

    for (i = 0; i < SH3_CHARACTER_NUM_SKELTONS - 1; i++, stp++) {
        stp->next = stp + 1;
    }
    stp->next = NULL;
}

void shCharacterFreeSkeltons(shSkelton* top) {
    int i = 0;
    shSkelton* free;

    if (top != NULL) {

        free = sh3skelton.free;
        sh3skelton.free = top;
        for (; top->next != NULL; top = top->next) {
            sh3skelton.last++;

            i++;
        }
        sh3skelton.last++;

        top->next = free;

        debugPrintf("skeltons free %d rest %d\n", i + 1, sh3skelton.last);
    }
}

void sh3CharacterSubtractSkeletons(int n) {
    sh3skelton.last -= n;
}

void sh3CharacterAddSkeletons(int n) {
    sh3skelton.last += n;
}

shSkelton* shCharacterGetSkeletons(int n, u_char* hrc) {
    shSkelton* stp;     // r3
    shSkelton* top_stp; // r16
    shSkelton* pre_stp; // r17
    int i;              // r4
    shSkelton* parent;  // r2
    int j;              // r2

    if (sh3skelton.last < n || n == 0) {
        return NULL;
    }
    sh3skelton.last -= n;

    stp = sh3skelton.free;
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

    printf("skeltons get %d rest %d\n", n, sh3skelton.last, i);

    sh3skelton.free = pre_stp->next;
    pre_stp->next = NULL;
    return top_stp;
}
