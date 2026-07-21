#ifndef UTILSTR_H
#define UTILSTR_H

int UtilStrCpyL(char* dst, char* src, int limit);

int UtilStrCatL(char* dst, char* s1, char* s2, int limit);

int UtilStrCat3L(char* dst, char* s1, char* s2, char* s3, int limit);

int UtilStrPathCatL(char* dst, char* path1, char* path2, int limit);

int UtilStrConvertCdPath(char* path);

int UtilStrConvertHdPath(char* path);

int UtilMemCpy(char* dst, char* src, int n);

int UtilMemSet(char* dst, char ch, int n);

int UtilMemSwap(char* dst, char* src, int n);

#endif // UTILSTR_H
