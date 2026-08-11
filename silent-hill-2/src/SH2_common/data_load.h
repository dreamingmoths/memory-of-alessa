#ifndef DATA_LOAD_H
#define DATA_LOAD_H

#include "sh2_common.h"

#define SH2_BUFPAGE_SIZE 4096

#define SH2_MES_FILE_COMMON  0
#define SH2_MES_FILE_ITEM    1
#define SH2_MES_FILE_OPTION  2
#define SH2_MES_FILE_MEMO    3
#define SH2_MES_FILE_M_CARD  4
#define SH2_MES_FILE_RESULT  5
#define SH2_MES_FILE_STAGE   6

int DataLoadMessage(int msg /* r2 */);
void shMemCopy(void* ds /* r18 */, void* sr /* r17 */, int datasize /* r16 */);

extern u_short msg_buffer[32768]; // size: 0x10000, address: 0x11B7040
extern u_short msg_station[2048]; // size: 0x1000, address: 0x11C7040

#endif // DATA_LOAD_H
