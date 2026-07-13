#ifndef PSS_VODATA_H
#define PSS_VODATA_H

#include "sce/mpeg/vobuf.h"

extern VoBuf voBuf;

VoTag *voBufGetTag(VoBuf *f);
VoData* voBufGetData(VoBuf* f);

#endif
