#include "Font/dic.h"

static u_short dicCode81(u_char c);
static u_short dicCode82(u_char c);
static u_short dicCode83(u_char c);
static u_short dicCode84(u_char c);
static u_short dicCode87(u_char c);
static u_short dicCodeAsc(u_char c);

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicSetStr);

u_short dicTransCode(u_short code) {
    u_char ch = code >> 8;
    u_char cl = code & 0xFF;
    
    switch (ch) {
        case 0x00: return dicCodeAsc(cl);
        case 0x81: return dicCode81(cl);
        case 0x82: return dicCode82(cl);
        case 0x83: return dicCode83(cl);
        case 0x84: return dicCode84(cl);
        case 0x87: return dicCode87(cl);
        default:
            if (cl < 0x40 || cl == 0x7F || cl > 0xFC) {
                return DICTIONARY_INVALID;
            }
            if (code >= 0x889F && code < 0x9873) {
                if (cl > 0x7F) cl--;
                return ((ch - 0x88) * 0xBC + cl + 0x2A0);
            }
            if (code >= 0x989F && code < 0x9FFD) {
                if (cl > 0x7F) cl--;
                return ((ch - 0x98) * 0xBC + cl + 0xE35);
            }
            if (code >= 0xE040 && code < 0xEAA5) {
                if (cl > 0x7F) cl--;
                return ((ch - 0xE0) * 0xBC + cl + 0x1415);
            }
            if (code >= 0xED40 && code < 0xEEED) {
                if (cl > 0x7F) cl--;
                return ((ch - 0xED) * 0xBC + cl + 0x1BED);
            }
            if (code >= 0xFA40 && code < 0xFC4C) {
                if (cl > 0x7F) cl--;
                return ((ch - 0xFA) * 0xBC + cl + 0x1BD1);
            }
            return DICTIONARY_INVALID;
    }
}

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicCodeAsc);

static u_short dicCode81(u_char c) {
    if (!IS_VALID_SJIS_81(c)) {
        return DICTIONARY_INVALID;
    }

    if (c == SJIS_81_SPECIAL) {
        return 0xFFFEU;
    }
    if (c < SJIS_81_DEL) {
        return c + 0x9F;
    }
    if (c < SJIS_81_ROW1_MIN) {
        return c + 0x9E;
    }
    if (c < SJIS_81_ROW2_MIN) {
        return c + 0x93;
    }
    if (c < SJIS_81_ROW3_MIN) {
        return c + 0x8B;
    }
    if (c < SJIS_81_ROW4_MIN) {
        return c + 0x80;
    }
    if (c < SJIS_81_ROW5_MIN) {
        return c + 0x79;
    }
    return 0x171;
}

static u_short dicCode82(u_char c) {
    if (!IS_VALID_SJIS_82(c))
        return DICTIONARY_INVALID;

    if (c <= SJIS_82_DIGIT_MAX)        // 0x4F–0x58, ０–９
        return c + 0x123;
    if (c <= SJIS_82_UPPER_MAX)        // 0x60–0x79, Ａ–Ｚ
        return c + 0x11C;
    if (c <= SJIS_82_LOWER_MAX)        // 0x81–0x9A, ａ–ｚ
        return c + 0x115;
    return c + 0x111;                  // 0x9F–0xF1, ぁ–ん
}

u_short dicCode83(u_char c) {
    if (!IS_VALID_SJIS_83(c)) {
        return DICTIONARY_INVALID;
    }
    if (c < SJIS_83_DEL) {
        return c + 0x1C3;
    }
    if (c <= SJIS_83_KATAKANA_MAX) {
        return c + 0x1C2;
    }
    if (c <= SJIS_83_GREEK_UPPER_MAX) {
        return c + 0x1BA;
    }
    return c + 0x1B2;
}

static u_short dicCode84(u_char c) {
    if (!IS_VALID_SJIS_84(c)) {
        return DICTIONARY_INVALID;
    }
    if (c <= SJIS_84_CYRILLIC_UPPER_MAX) {
        return c + 0x249;
    }
    if (c < SJIS_84_DEL) {
        return c + 0x23A;
    }
    if (c <= SJIS_84_CYRILLIC_LOWER_MAX) {
        return c + 0x239;
    }
    return c + 0x22C;
}

static u_short dicCode87(u_char c) {
    if (!IS_VALID_SJIS_87(c)) {
        return DICTIONARY_INVALID;
    }
    if (c < SJIS_87_UNITS_MIN - 1) {
        return c + 0x2AB;
    }
    if (c < SJIS_87_UNITS_MAX + 1) {
        return c + 0x2AA;
    }
    if (c == SJIS_87_ERA_HEISEI) {
        return 0x320;
    }
    return c + 0x2A1;
}
