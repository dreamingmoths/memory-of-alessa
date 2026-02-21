#ifndef SH_KT_VIF0
#define SH_KT_VIF0

void ktVif0Wait2();
void ktVif0Send(void *p /* r16 */, signed int tte /* r17 */);
void *ktVif0PkBufCurrent();

#endif
