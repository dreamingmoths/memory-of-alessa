#ifndef MOVIE_H
#define MOVIE_H

#include "shared/movie/movie.h"
#include "sce/libgraph.h"

#define min(x, y) (((x) > (y)) ? (y) : (x))
#define max(x, y) (((x) > (y))? (x): (y))

#define STACK_SIZE    (16*1024)
#define DEF_STACK_SIZE    2048
#define DEF_PRIORITY       0x24
#define IOP_BUFF_SIZE (12288*2) // 512 * 48

#endif // MOVIE_H
