#ifndef FONT_DIC_H
#define FONT_DIC_H

#include "sh2_common.h"

#define DICTIONARY_INVALID         0x7FFF
#define DICTIONARY_SPECIAL         0xFFFE

#define SJIS_81_SPECIAL              0x40
#define SJIS_81_DEL                  0x7F
#define SJIS_81_ROW1_MIN             0xAD
#define SJIS_81_ROW1_MAX             0xB7
#define SJIS_81_ROW2_MIN             0xC0
#define SJIS_81_ROW2_MAX             0xC7
#define SJIS_81_ROW3_MIN             0xCF
#define SJIS_81_ROW3_MAX             0xD9
#define SJIS_81_ROW4_MIN             0xE9
#define SJIS_81_ROW4_MAX             0xEF
#define SJIS_81_ROW5_MIN             0xF8
#define SJIS_81_ROW5_MAX             0xFB
#define SJIS_81_ROW6_MIN             0xFD

#define SJIS_82_DIGIT_MIN            0x4F
#define SJIS_82_DIGIT_MAX            0x58
#define SJIS_82_UPPER_MIN            0x60
#define SJIS_82_UPPER_MAX            0x79
#define SJIS_82_LOWER_MIN            0x81
#define SJIS_82_LOWER_MAX            0x9A
#define SJIS_82_HIRA_MIN             0x9F
#define SJIS_82_HIRA_MAX             0xF2

#define SJIS_83_MIN                  0x40
#define SJIS_83_DEL                  0x7F
#define SJIS_83_KATAKANA_MIN         0x40
#define SJIS_83_KATAKANA_MAX         0x96
#define SJIS_83_GREEK_UPPER_MIN      0x9F
#define SJIS_83_GREEK_UPPER_MAX      0xB6
#define SJIS_83_GREEK_LOWER_MIN      0xBF
#define SJIS_83_GREEK_LOWER_MAX      0xD6

#define SJIS_84_MIN                  0x40
#define SJIS_84_DEL                  0x7F
#define SJIS_84_CYRILLIC_UPPER_MIN   0x40
#define SJIS_84_CYRILLIC_UPPER_MAX   0x60
#define SJIS_84_CYRILLIC_LOWER_MIN   0x70
#define SJIS_84_CYRILLIC_LOWER_MAX   0x91
#define SJIS_84_BOX_MIN              0x9F
#define SJIS_84_BOX_MAX              0xBE
#define SJIS_84_TRAIL_MIN            0xBF

#define SJIS_87_MIN                  0x40
#define SJIS_87_CIRCLED_ROMAN_MIN    0x40
#define SJIS_87_CIRCLED_ROMAN_MAX    0x5D
#define SJIS_87_UNITS_MIN            0x5F
#define SJIS_87_UNITS_MAX            0x75
#define SJIS_87_ERA_HEISEI           0x7E // ㍻
#define SJIS_87_DEL                  0x7F
#define SJIS_87_SYMBOLS_MIN          0x80
#define SJIS_87_SYMBOLS_MAX          0x9C
#define SJIS_87_TRAIL_MIN            0x9D

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

#define IS_VALID_SJIS_83(c) ( \
    (((c) >= SJIS_83_MIN) && \
    ((c) != SJIS_83_DEL) && \
    (((c) < SJIS_83_KATAKANA_MAX + 1) || ((c) > SJIS_83_GREEK_UPPER_MIN - 1)) && \
    (((c) < SJIS_83_GREEK_UPPER_MAX + 1) || (c > SJIS_83_GREEK_LOWER_MIN - 1)) && \
    ((c) < SJIS_83_GREEK_LOWER_MAX + 1)) \
)

#define IS_VALID_SJIS_84(c) ( \
    ((c) >= SJIS_84_MIN) && \
    (((c) < SJIS_84_CYRILLIC_UPPER_MAX + 1) || ((c) > SJIS_84_CYRILLIC_LOWER_MIN - 1)) && \
    ((c) != SJIS_84_DEL) && \
    (((c) < SJIS_84_CYRILLIC_LOWER_MAX + 1) || ((c) > SJIS_84_BOX_MIN - 1)) && \
    ((c) < SJIS_84_TRAIL_MIN) \
)

#define IS_VALID_SJIS_87(c) ( \
    ((c) >= SJIS_87_MIN) && \
    ((c) != SJIS_87_CIRCLED_ROMAN_MAX + 1) && \
    (((c) < SJIS_87_UNITS_MAX + 1) || ((c) > SJIS_87_ERA_HEISEI - 1)) && \
    ((c) != SJIS_87_DEL) && \
    ((c) < SJIS_87_TRAIL_MIN) \
)

u_short dicTransCode(u_short code);

#endif // FONT_DIC_H
