#include "pss_vobuf.h"

void voBufCreate(
    VoBuf *f,
    VoData *data,
    VoTag *tagProg,
    VoTag *tagInter,
    VoTag *tagTop,
    VoTag *tagBot,
    int size
) {
    int i;

    f->data = data;
    f->tagInter = tagInter;

    f->tag = tagInter;
    f->size = size;
    f->count = 0;
    f->write = 0;

    for (i = 0; i < size; i++)
    {
        f->tagInter[i].status = VOBUF_STATUS_EMPTY;
    }
}

void voBufDelete(VoBuf *f)
{
    return;
}

void voBufReset(VoBuf *f)
{
    f->count = 0;
    f->write = 0;
}

int voBufIsFull(VoBuf *f)
{
    return f->count == f->size;
}

void voBufIncCount(VoBuf *f)
{
    DIntr();

    f->tag[f->write].status = VOBUF_STATUS_FULL;
    f->count++;
    f->write = (f->write + 1) % f->size;

    EIntr();
}

VoData* voBufGetData(VoBuf *f)
{
    return voBufIsFull(f) ? NULL: f->data + f->write;
}

int voBufIsEmpty(VoBuf *f)
{
    return f->count == 0;
}

VoTag* voBufGetTag(VoBuf *f)
{
    return voBufIsEmpty(f) ? NULL : f->tag + ((f->write - f->count + f->size) % f->size);
}

void voBufDecCount(VoBuf *f)
{
    if (f->count > 0)
    {
        f->count--;
    }
}
