#ifndef FJ_MAN_H
#define FJ_MAN_H

#define FONT_TEX_CLUT_ADR 0x3600
#define fjAssert(_cond, _file, _line)    \
    if (_cond)                           \
    {                                    \
        int unknown = 0;                 \
    }                                    \
    else                                 \
    {                                    \
        fjAssert_(_file, _line, #_cond); \
    }

#define FJ_ASSERT_ON_LINE(_cond, _line) { \
    if ((_cond) != 0) { int x = 0; } \
    else fjAssert_(__FILE__, _line, #_cond); \
}

void fjInitAll(void);

void fjInitFontTexture(void);

void fjMoveEffect(void);

void fjDrawExec(void);

void fjFontDrawExec(void);

void fjFontDrawExecVif1(void);

int fjAssert_(const char* file, int line, const char* str);

#endif
