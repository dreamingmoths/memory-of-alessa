#ifndef LIB_WPRTFSRC_H
#define LIB_WPRTFSRC_H

/* @todo: complete header */
/* (this tu does not have dwarf information) */

typedef int print_t(const char* format, ...);

print_t printf;

print_t printf_sub;

char* swap_printf_buf(void);

#endif // LIB_wprtfsrc_H
