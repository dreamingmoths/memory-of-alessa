#ifndef LOADBG_EVENT_H
#define LOADBG_EVENT_H

#include "common.h"

void LoadBgEventInit(void* adr /* r2 */, u_int size /* r2 */);
void LoadBgEventFileLoad(union fsFileIndex* fileid /* r18 */, void* adr /* r17 */);

#endif // LOADBG_EVENT_H
