#ifndef FILEPATH_H
#define FILEPATH_H

#include "sh2_common.h"
#include "Exec_Env/local_env.h"
#include "Exec_Env/exec_env.h"
#include "Multi_thr/util/utilstr.h"

int shPathCheckExecRoot(s_char* filename);

int shPathMakeIop(s_char* fullpath, s_char* filename);

int shPathMakeCdData(s_char* fullpath, s_char* filename);

int shPathMakeHdData(s_char* fullpath, s_char* filename);

int shPathMakeCdDataBase(s_char* fullpath, s_char* filename);

int shPathMakeHdDataBase(s_char* fullpath, s_char* filename);

int ___shPathMakeCdDataBase(s_char* fullpath, s_char* filename);

int ___shPathMakeCdData(s_char* fullpath, s_char* filename);

int ___shPathMakeHdDataBase(s_char* fullpath, s_char* filename);

int ___shPathMakeHdData(s_char* fullpath, s_char* filename);

#endif // FILEPATH_H
