#ifndef DATA_LOAD_H
#define DATA_LOAD_H

#include "sh2_common.h"

#define SH2_BUFPAGE_SIZE 4096

int DataLoadMessage(int msg /* r2 */);
void shMemCopy(void* ds /* r18 */, void* sr /* r17 */, int datasize /* r16 */);

extern u_short msg_buffer[32768]; // size: 0x10000, address: 0x11B7040
extern u_short msg_station[2048]; // size: 0x1000, address: 0x11C7040

#endif // DATA_LOAD_H
