#ifndef EN_RED_H
#define EN_RED_H

#include "sh2_common.h"
#include "Enemy/en_common.h"

#define SET_DP_STATE_LV(_dp, _slv, _sslv) do { \
    _dp->slv = _slv; \
    _dp->sslv = _sslv; \
} while (0)

#endif // EN_RED_H
