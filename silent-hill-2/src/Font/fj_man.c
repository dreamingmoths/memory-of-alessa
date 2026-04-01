#include "common.h"
#include "Font/fj_man.h"

int fjAssert_(const char *file, int line, const char *str) __attribute__((noreturn))
{
    printf("assertion \"%s\" failed: file \"%s\", line %d\n", str, file, line);
    ABORT();
    return 1;
}
