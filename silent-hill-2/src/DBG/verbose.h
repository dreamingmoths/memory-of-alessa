#ifndef VERBOSE_H
#define VERBOSE_H

#include "sh2_common.h"

#include "mw/mw_stdarg.h"
#include "Exec_Env/exec_env.h"

int verbose(int level, char* format, ...);

#endif // VERBOSE_H
