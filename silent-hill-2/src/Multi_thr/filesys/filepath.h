#ifndef FILEPATH_H
#define FILEPATH_H

#include "sh2_common.h"

int shPathCheckExecRoot(char* filename);
int shPathMakeIop(char* fullpath, char* filename);
int shPathMakeCdData(char* fullpath, char* filename);
int shPathMakeHdData(char* fullpath, char* filename);
int shPathMakeCdDataBase(char* fullpath, char* filename);
int shPathMakeHdDataBase(char* fullpath, char* filename);
int ___shPathMakeCdDataBase(char* fullpath, char* filename);
int ___shPathMakeCdData(char* fullpath, char* filename);
int ___shPathMakeHdDataBase(char* fullpath, char* filename);
int ___shPathMakeHdData(char* fullpath, char* filename);

#endif // FILEPATH_H
