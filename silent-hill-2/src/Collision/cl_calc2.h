#ifndef CL_CALC2_H
#define CL_CALC2_H

#include "cl_main.h"

int clCheckSubLineToPlane(CL_HITRESULT* result, float (* line0)[4], float (* line1)[4], float (* plane0)[4], float (* plane1)[4], float (* plane2)[4], float (* plane3)[4]);

int clCheckSubLineToPlane3(CL_HITRESULT* result, float (* line0)[4], float (* line1)[4], float (* plane0)[4], float (* plane1)[4], float (* plane2)[4]);

int clCheckSubLineToColumnPlus(CL_HITRESULT* result, float (* line0)[4], float (* line1)[4], float (* column)[4]);

int clCheckSubWallToColumn(CL_HITRESULT* result, float (* wall0)[4], float (* wall1)[4], float (* column)[4]);

int clCheckSubColumnToColumn(CL_HITRESULT* result, float (* clm0)[4], float (* clm1)[4]);

#endif // CL_CALC2_H
