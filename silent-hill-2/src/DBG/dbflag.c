#include "dbflag.h"

extern /* static */ u_int dbflag_reserved; // size: 0x4, address: 0x116DD40
extern /* static */ char* dbflag_explain[32]; // size: 0x80, address: 0x33DE50
static const char no_msg[] = "(no message: why?)"; //@todo: string from dead code?

#line 38
int dbFlagReserve(u_int flag /* r2 */, char* explain_message /* r2 */) {
    u_int check;    // r16
    char** explain; // r17
    if (dbflag_reserved & flag) {


        VERBOSE(1, "can't reserved debug flag : %08x : %s\n", flag, explain_message);

        VERBOSE(2, "alreday reserved          : %08x\n", dbflag_reserved);



        for (check = 1, explain = dbflag_explain; check; check<<=1, explain++) {
            if (check & dbflag_reserved) {
                VERBOSE(3, "flag report               : %08x : %s\n", check, *explain ? *explain : no_msg);

            }
        }
        return false;
    }
    for (check = 1, explain = dbflag_explain; check; check<<=1, explain++) {
        if (check & flag) {
            dbflag_reserved |= check;
            *explain = explain_message;
        }
    }
    VERBOSE(4, "reserved debug flag : %08x : %s\n", flag, explain_message);
    return true;
}



u_int dbFlag(u_int flag) {
    return execEnv_debug_flag & flag;
}


void dbFlagSet(u_int flag) {
    execEnv_debug_flag |= flag;
}
