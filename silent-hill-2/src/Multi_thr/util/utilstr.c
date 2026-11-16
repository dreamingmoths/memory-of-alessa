#include "Multi_thr/util/utilstr.h"







int UtilStrCpyL(s_char* dst, char* src, int limit) {
    int len = 0;
    while (limit > 0) {
        limit--;
        if ((*dst++ = *src++) == 0) break;
        len++;
    }
    return len;
}

int UtilStrCatL(s_char* dst, s_char* s1, s_char* s2, int limit)
{
    int len;
    len = UtilStrCpyL(dst, s1, limit);
    len += UtilStrCpyL(dst + len, s2, limit - len);
    return len;
}


int UtilStrCat3L(s_char* dst, s_char* s1, s_char* s2, s_char* s3, int limit)
{
    int len;
    len = UtilStrCpyL(dst, s1, limit);
    len += UtilStrCpyL(dst + len, s2, limit - len);
    len += UtilStrCpyL(dst + len, s3, limit - len);
    return len;
}

int UtilStrPathCatL(char* dst, char* path1, char* path2, int limit)
{
    int len = 0;


    if (path2 == NULL) return 0;
    if (*path2 != '/' && *path2 != '\\') {
        if (path1 != NULL) {
            len = UtilStrCpyL(dst, path1, limit);
            if (dst[len - 1] != '/' && *path2 != '\\') {
                len += UtilStrCpyL(dst + len, "/", limit - len);
            }
        }
    }
    len += UtilStrCpyL(dst + len, path2, limit - len);

    return len;
}

int UtilStrConvertCdPath(s_char* path) {
    int len;
    s_char ch;
    len = 0;
    for (len = 0; (ch = *path) != 0; path++, len++) {
        if (ch >= 'a' && ch < '{') *path = ch - 0x20;
        else if (ch == '/')        *path = '\\';
    }

    return len - 1;
}

int UtilStrConvertHdPath(s_char* path) {
    int len;
    s_char ch;

    for (len = 0; (ch = *path) != 0; path++, len++) {
        if (ch == '\\') *path = '/';
    }

    return len - 1;
}

int UtilMemCpy(s_char* dst, s_char* src, int n) {
    int loop; // r3
    int bit; // r2


    bit = ((int)dst | (int)src | n) | 0x10;

    if ((bit & sizeof(u_long128) - 1) == 0) {
        u_long128* d = dst; // r2
        u_long128* s = src; // r2
        for (loop = (u_int)n >> 4; loop-- > 0;) *d++ = *s++;

        return n;
    }
    if ((bit & sizeof(long) - 1) == 0) {
        long* d = dst; // r2
        long* s = src; // r2
        for (loop = (u_int)n >> 3; loop-- > 0;) *d++ = *s++;

        return n;
    }
    if ((bit & sizeof(int) - 1) == 0) {
        int* d = dst; // r2
        int* s = src; // r2
        for (loop = (u_int)n >> 2; loop-- > 0;) *d++ = *s++;

        return n;
    }
    if ((bit & sizeof(short) - 1) == 0) {
        short* d = dst; // r2
        short* s = src; // t2
        for (loop = (u_int)n >> 1; loop-- > 0;) *d++ = *s++;

        return n;
    }
    {
        s_char* d = dst; // r2
        s_char* s = src; // r2
        for (loop = n; loop-- > 0;) *d++ = *s++;

        return n;
    }
}


int UtilMemSet(s_char* dst, s_char ch, int n)
{
    int loop; // r5
    int bit; // r2
    bit = ((int)dst | n) | 0x10;
    if ((bit & sizeof(u_long128) - 1) == 0) {
        u_long128* d = dst; // r17
        u_long128 s[1]; // r29+0x30
        u_long128 set; // r3
        ((u_long*)s)[0] = (u_char)ch * 0x0101010101010101;
        ((u_long*)s)[1] = (u_char)ch * 0x0101010101010101;
        set = s[0];
        for (loop = (u_int)n >> 4; loop-- > 0;) *d++ = set;
        return n;
    }
    if ((bit & sizeof(u_long) - 1) == 0) {
        u_long* d = dst; // r17
        u_long set; // r2
        set = (u_char)ch * 0x0101010101010101;
        for (loop = (u_int)n >> 3; loop-- > 0;) *d++ = set;
        return n;
    }
    if ((bit & sizeof(u_int) - 1) == 0) {
        u_int* d = dst; // r2
        u_int set; // r3
        set = (u_char)ch * 0x01010101;
        for (loop = (u_int)n >> 2; loop-- > 0;) *d++ = set;
        return n;
    }
    if ((bit & sizeof(u_short) - 1) == 0) {
        u_short* d = dst; // r2
        u_short set; // r3
        set = (u_char)ch * 0x0101;
        for (loop = (u_int)n >> 1; loop-- > 0;) *d++ = set;
        return n;
    }
    {
        u_char* d = dst; // r2
        u_char set; // r3
        set = (u_short)ch * 0x0101;
        for (loop = n; loop-- > 0;) *d++ = set;
        return n;
    }
}

int UtilMemSwap(s_char* dst, s_char* src, int n) {
    int loop;
    int bit;


    bit = ((int)dst | (int)src | n) | 0x10;

    if ((bit & sizeof(u_long128) - 1) == 0) {
        u_long128* d = dst;
        u_long128* s = src;
        u_long128 tmp;
        loop = (u_int)n >> 4;
        while (loop-- > 0) {
            tmp = *d;
            *d++ = *s;
            *s++ = tmp;
        }
        return n;
    }
    if ((bit & sizeof(long) - 1) == 0) {
        long* d = dst;
        long* s = src;
        long tmp;
        loop = (u_int)n >> 3;
        while (loop-- > 0) {
            tmp = *d;
            *d++ = *s;
            *s++ = tmp;
        }
        return n;
    }
    if ((bit & sizeof(int) - 1) == 0) {
        int* d = dst;
        int* s = src;
        int tmp;
        loop = (u_int)n >> 2;
        while (loop-- > 0) {
            tmp = *d;
            *d++ = *s;
            *s++ = tmp;
        }
        return n;
    }
    if ((bit & sizeof(short) - 1) == 0) {
        short* d = dst;
        short* s = src;
        short tmp;
        loop = (u_int)n >> 1;
        while (loop-- > 0) {
            tmp = *d;
            *d++ = *s;
            *s++ = tmp;
        }
        return n;
    }
    {
        s_char* d = dst;
        s_char* s = src;
        s_char tmp;
        loop = n;
        while (loop-- > 0) {
            tmp = *d;
            *d++ = *s;
            *s++ = tmp;
        }
        return n;
    }
}
