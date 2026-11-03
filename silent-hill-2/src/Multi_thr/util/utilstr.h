#ifndef UTILSTR_H
#define UTILSTR_H

#include "sh2_common.h"

int UtilStrCpyL(s_char* dst, char* src, int limit);

int UtilStrCatL(s_char* dst, s_char* s1, s_char* s2, int limit);

int UtilStrCat3L(s_char* dst, s_char* s1, s_char* s2, s_char* s3, int limit);

int UtilStrPathCatL(char* dst, char* path1, char* path2, int limit);

int UtilStrConvertCdPath(s_char* path);

int UtilStrConvertHdPath(s_char* path);

int UtilMemCpy(s_char* dst, s_char* src, int n);

int UtilMemSet(s_char* dst, s_char ch, int n);

int UtilMemSwap(s_char* dst, s_char* src, int n);

#endif // UTILSTR_H
