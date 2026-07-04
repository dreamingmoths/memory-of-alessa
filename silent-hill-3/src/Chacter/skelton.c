#include "common.h"
#include "Chacter/character.h"
#include "Chacter/skelton.h"

#define SH3_CHARACTER_NUM_SKELTONS 400

// 0x10 bytes got removed..... not sure which ones
// parent & next were swapped
typedef struct sh3_Skelton {
    // total size: 0xE0
    struct sh3_Skelton* parent; // offset 0x4, size 0x4
    struct sh3_Skelton* next;   // offset 0x0, size 0x4
    Matrix4 src_m;
    Vector4 src_t;
    Matrix4 des_m;
    Vector4 des_t;
    Vector4 axis;
    float theta;     // offset 0xC0, size 0x4
    float xx;        // offset 0xC4, size 0x4
    float yy;        // offset 0xC8, size 0x4
    float zz;        // offset 0xCC, size 0x4
    float xy;        // offset 0xD0, size 0x4
    float yz;        // offset 0xD4, size 0x4
    float zx;        // offset 0xD8, size 0x4
    u_short c_count; // offset 0xDC, size 0x2
    u_short c_speed; // offset 0xDE, size 0x2
    // s_char change; // offset 0xE0, size 0x1
    // char reserved; // offset 0xE1, size 0x1
    // char is_key; // offset 0xE2, size 0x1
    // char pad; // offset 0xE3, size 0x1
    // void* untouchable; // offset 0xE4, size 0x4
} sh3_Skelton;

typedef struct sh3_SkeltonWork {
    // total size: 0x15E10
    sh3_Skelton work[SH3_CHARACTER_NUM_SKELTONS]; // offset 0x0, size 0x15E00
    sh3_Skelton* free;                            // offset 0x15E00, size 0x4
    int last;                                     // offset 0x15E04, size 0x4
} sh3_SkeltonWork;

sh3_SkeltonWork sh3skelton; // address: 0x046E870, size: 0x15E10

void shCharacterInitSkeltons(void) {
    sh3_Skelton* stp;
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

void shCharacterFreeSkeltons(sh3_Skelton* top) {
    int i = 0;
    sh3_Skelton* free;

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

sh3_Skelton* shCharacterGetSkeletons(int n, u_char* hrc) {
    sh3_Skelton* stp;     // r3
    sh3_Skelton* top_stp; // r16
    sh3_Skelton* pre_stp; // r17
    int i;                // r4
    sh3_Skelton* parent;  // r2
    int j;                // r2

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
