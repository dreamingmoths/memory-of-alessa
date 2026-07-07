#ifndef DATA_LOAD_H
#define DATA_LOAD_H

#include "sh2_common.h"

int DataLoadMessage(int msg /* r2 */);
void shMemCopy(void* ds /* r18 */, void* sr /* r17 */, int datasize /* r16 */);

#endif // DATA_LOAD_H
