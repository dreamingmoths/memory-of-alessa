#ifndef EF_STAGE_H
#define EF_STAGE_H

#include "common.h"
#include "Effect/ef_common.h"

int InitEffectObjectGunFire(EFCTObject* pObj /* r18 */, int nIndex /* r2 */, float* Pos /* r2 */, float* vec /* r17 */, int wep_kind /* r19 */, u_char light_status /* r16 */);
int InitEffectObjectGunSmoke(EFCTObject* pObj /* r17 */, int nIndex /* r2 */, float* Pos /* r2 */, int wep_kind /* r18 */, u_char light_status /* r16 */);

#endif // EF_STAGE_H
