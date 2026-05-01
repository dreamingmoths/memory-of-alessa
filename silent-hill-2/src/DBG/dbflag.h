#ifndef DBFLAG_H
#define DBFLAG_H

#include "common.h"

u_int dbFlag(u_int flag /* r2 */);
int dbFlagReserve(u_int flag /* r2 */, char* explain_message /* r2 */);

#endif // DBFLAG_H
