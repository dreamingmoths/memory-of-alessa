#ifndef SH2DT_H
#define SH2DT_H

#include "common.h"

void shSetDF(int fpi /* r2 */);
int shGetDF(void);
float shGetDT(void);
float shGetFPS(void);
void shResetDF(void);
void shSetDFZero(void);
void shSetDFreal(int fpi /* r2 */);
float shGetDTreal(void);

extern float sh2DeltaTimePerFrameReal; // size: 0x4, address: 0x11B6B00
extern int sh2FramePerIntReal; // size: 0x4, address: 0x11B6B08
extern float sh2FramePerSec; // size: 0x4, address: 0x11B6B10
extern float sh2DeltaTimePerFrame; // size: 0x4, address: 0x11B6B18
extern int sh2FramePerIntSave; // size: 0x4, address: 0x11B6B20
extern int sh2FramePerInt; // size: 0x4, address: 0x11B6B28

#endif
