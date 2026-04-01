#ifndef SH_KT_VIF0
#define SH_KT_VIF0

#include "libdma.h"
#include "Chacter_Draw/model_common.h"

typedef struct ktVif1Ot2 {
    // total size: 0x20
    struct _sceDmaTag * top_1; // offset 0x0, size 0x4
    struct _sceDmaTag * top_2; // offset 0x4, size 0x4
    unsigned int n_bits_1; // offset 0x8, size 0x4
    unsigned int n_bits_2; // offset 0xC, size 0x4
    unsigned int length_1; // offset 0x10, size 0x4
    unsigned int length_2; // offset 0x14, size 0x4
    unsigned int mask_1; // offset 0x18, size 0x4
    unsigned int mask_2; // offset 0x1C, size 0x4
} ktVif1Ot2;

void ktVif0Wait2(void);
void ktVif0Send(void *p /* r16 */, signed int tte /* r17 */);
void *ktVif0PkBufCurrent(void);
ktVif1Ot2 * CharacterOt_KtVif1Ot2(Model* model);

#endif
