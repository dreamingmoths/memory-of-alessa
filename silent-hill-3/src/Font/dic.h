#ifndef FONT_DIC_H
#define FONT_DIC_H

#include "common.h"

#define DICTIONARY_INVALID 0x7FFF
#define DICTIONARY_SPECIAL 0xFFFE

#define SJIS_81_SPECIAL    0x40
#define SJIS_81_DEL        0x7F
#define SJIS_81_ROW1_MIN   0xAD
#define SJIS_81_ROW1_MAX   0xB7
#define SJIS_81_ROW2_MIN   0xC0
#define SJIS_81_ROW2_MAX   0xC7
#define SJIS_81_ROW3_MIN   0xCF
#define SJIS_81_ROW3_MAX   0xD9
#define SJIS_81_ROW4_MIN   0xE9
#define SJIS_81_ROW4_MAX   0xEF
#define SJIS_81_ROW5_MIN   0xF8
#define SJIS_81_ROW5_MAX   0xFB
#define SJIS_81_ROW6_MIN   0xFD

#define SJIS_82_DIGIT_MIN  0x4F
#define SJIS_82_DIGIT_MAX  0x58
#define SJIS_82_UPPER_MIN  0x60
#define SJIS_82_UPPER_MAX  0x79
#define SJIS_82_LOWER_MIN  0x81
#define SJIS_82_LOWER_MAX  0x9A
#define SJIS_82_HIRA_MIN   0x9F
#define SJIS_82_HIRA_MAX   0xF2

#define IS_VALID_SJIS_81(c) ( \
    !((SJIS_81_SPECIAL > (c)) || \
    ((c) == SJIS_81_DEL) || \
    (((c) >= SJIS_81_ROW1_MIN) && (SJIS_81_ROW1_MAX >= (c))) || \
    (((c) >= SJIS_81_ROW2_MIN) && (SJIS_81_ROW2_MAX >= (c))) || \
    (((c) >= SJIS_81_ROW3_MIN) && (SJIS_81_ROW3_MAX >= (c))) || \
    (((c) >= SJIS_81_ROW4_MIN) && (SJIS_81_ROW4_MAX >= (c))) || \
    (((c) >= SJIS_81_ROW5_MIN) && (SJIS_81_ROW5_MAX >= (c))) || \
    ((c) >= SJIS_81_ROW6_MIN)) \
)

#define IS_VALID_SJIS_82(c) ( \
    ((c) >= SJIS_82_DIGIT_MIN) && \
    ((c) < SJIS_82_DIGIT_MAX + 1 || (c) > SJIS_82_UPPER_MIN - 1) && \
    ((c) < SJIS_82_UPPER_MAX + 1 || (c) > SJIS_82_LOWER_MIN - 1) && \
    ((c) < SJIS_82_LOWER_MAX + 1 || (c) > SJIS_82_HIRA_MIN - 1) && \
    ((c) < SJIS_82_HIRA_MAX) \
)

#endif