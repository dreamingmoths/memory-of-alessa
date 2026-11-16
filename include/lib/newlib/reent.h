#ifndef LIB_NEWLIB_REENT_H
#define LIB_NEWLIB_REENT_H

/**
 * from newlib `reent.h`.
 */

typedef struct __sFILE   __FILE;

typedef struct _reent {
  int _errno;
    __FILE* _stdin, *_stdout, *_stderr;
} reent;

extern reent* _impure_ptr;

#endif // LIB_NEWLIB_REENT_H
