#ifndef FJ_MAN_H

#ifdef DEBUG
#define fjAssert(_cond, _file, _line)    \
    if (_cond)                           \
    {                                    \
        int unknown = 0;                 \
    }                                    \
    else                                 \
    {                                    \
        fjAssert_(_file, _line, #_cond); \
    }
#endif

#endif