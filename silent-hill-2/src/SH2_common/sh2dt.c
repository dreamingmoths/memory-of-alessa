#include "sh2dt.h"

void shSetDF(int fpi /* r2 */) { 
    
    sh2FramePerIntSave = sh2FramePerInt = fpi;                                 
    sh2DeltaTimePerFrame = fpi / 60.0f;
    sh2FramePerSec = 60.0f / fpi;  
}

int shGetDF(void) {
    return sh2FramePerInt;
}

float shGetDT(void) {
    return sh2DeltaTimePerFrame;
}

float shGetFPS(void) {
    return sh2FramePerSec;
}

void shResetDF(void) {
    shSetDF(sh2FramePerIntSave);
}

void shSetDFZero(void) {
    sh2FramePerInt = 0;
    sh2DeltaTimePerFrame = 0.0f;
    sh2FramePerSec = 0.0f;
}

void shSetDFreal(int fpi /* r2 */) {
    sh2FramePerIntReal = fpi;
    sh2DeltaTimePerFrameReal = fpi / 60.0f;
}

float shGetDTreal(void)  {
    return sh2DeltaTimePerFrameReal;
}