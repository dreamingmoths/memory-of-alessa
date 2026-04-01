// SDK video playback sample code.
// all credits to https://github.com/Mikompilation/Himuro/blob/828c49053f0d0a67694ae678463dfa3b770b6ef3/include/sce/mpeg/vibuf.h

#include "pss_vibuf.h"

int getFIFOindex(ViBuf *f, void *addr)
{
    void *val;

    if (addr == DmaAddr(f->tag + (f->n + 1)))
    {
        return 0;
    }
    else
    {
        return ((u_int)addr - (u_int)f->data) / VIBUF_ELM_SIZE;
    }
}

void setD3_CHCR(u_int val)
{
    DIntr();

    *D_ENABLEW = *D_ENABLER | 0x00010000;

    *D3_CHCR = val;

    *D_ENABLEW = *D_ENABLER & ~0x00010000;

    EIntr();
}

void setD4_CHCR(u_int val)
{
    DIntr();

    *D_ENABLEW = ((*D_ENABLER)|0x00010000);

    *D4_CHCR = val;

    *D_ENABLEW = ((*D_ENABLER)&~0x00010000);

    EIntr();
}

void scTag2(QWORD *q, void *addr, u_int id, u_int qwc)
{
    q->l[0] = (u_long)(u_int)addr << 32 | (u_long)id << 28 | (u_long)qwc << 0;
}

int viBufCreate(ViBuf *f, u_long128 *data, u_long128 *tag, int size, TimeStamp *ts, int n_ts)
{
    SemaParam param;

    f->data = data;
    f->tag = UncAddr(tag);
    f->n = size;
    f->buffSize = size * VIBUF_ELM_SIZE;
    f->ts = ts;
    f->n_ts = n_ts;

    f->sema = CreateSema((SemaParam*) f);

    viBufReset(f);

    f->totalBytes = 0;

    return 1;
}

int viBufReset(ViBuf *f)
{
    int i;

    f->dmaStart = 0;
    f->dmaN = 0;
    f->readBytes = 0;
    f->isActive = 1;
    f->count_ts = 0;
    f->wt_ts = 0;

    for (i = 0; i < f->n_ts; i++)
    {
        f->ts[i].pts = TS_NONE;
        f->ts[i].dts = TS_NONE;
        f->ts[i].pos = 0;
        f->ts[i].len = 0;
    }


    for (i = 0; i < f->n; i++)
    {
        scTag2(
            (QWORD*)(f->tag + i),
            DmaAddr((char*)f->data + VIBUF_ELM_SIZE * i),
            DMA_ID_REF,
            VIBUF_ELM_SIZE / 16
        );
    }

    scTag2(
        (QWORD*)(f->tag + i),
        DmaAddr(f->tag),
        DMA_ID_NEXT,
        0
    );

    *D4_QWC = 0;
    *D4_MADR = (u_int)DmaAddr(f->data);
    *D4_TADR = (u_int)DmaAddr(f->tag);

    setD4_CHCR((0 << 8) | (1 << 2) | 1);

    return 1;
}

void viBufBeginPut(ViBuf *f, u_char **ptr0, int *len0, u_char **ptr1, int *len1)
{
    int en;
    int es;
    int fs;
    int fn;

    WaitSema(f->sema);

    fs = ((f->dmaStart + f->dmaN) * VIBUF_ELM_SIZE);
    fn = ((f->n - 2 -  f->dmaN) * VIBUF_ELM_SIZE);

    es = (fs + f->readBytes) % f->buffSize;
    en = fn - f->readBytes;

    if (f->buffSize - es >= en)
    {
        *ptr0 = (u_char*)f->data + es;
        *len0 = en;
        *ptr1 = NULL;
        *len1 = 0;
    }
    else
    {
        *ptr0 = (u_char*)f->data + es;
        *len0 = f->buffSize - es;
        *ptr1 = (u_char*)f->data;
        *len1 = en - (f->buffSize - es);
    }

    SignalSema(f->sema);
}

void viBufEndPut(ViBuf *f, int size)
{
    WaitSema(f->sema);

    f->readBytes += size;
    f->totalBytes += size;

    SignalSema(f->sema);
}

int viBufAddDMA(ViBuf *f)
{
    int i;
    int index;
    u_int d4chcr;
    int isNewData;
    int start;
    int read_n;
    int done;

    isNewData = 0;

    WaitSema(f->sema);

    if (!f->isActive)
    {
        ErrMessage("DMA ADD not active\n");
        return 0;
    }

    setD4_CHCR((DMA_ID_REFE<<28) | (0<<8) | (1<<2) | 1);

    d4chcr = *D4_CHCR;

    index = getFIFOindex(f, (void*)*D4_MADR);

    done = (index + f->n - f->dmaStart) % f->n;

    f->dmaStart = (f->dmaStart + done) % f->n;
    f->dmaN -= done;

    start = (f->dmaStart + f->dmaN) % f->n;
    read_n = f->readBytes/VIBUF_ELM_SIZE;
    f->readBytes %= VIBUF_ELM_SIZE;

    if (read_n > 0)
    {
        u_int offset = (f->dmaStart + f->dmaN - 1 + f->n) % f->n;

        scTag2(
            (QWORD*)(f->tag + offset),
            (char*)f->data + VIBUF_ELM_SIZE * offset,
            DMA_ID_REF,
            VIBUF_ELM_SIZE / 16
        );

        isNewData = 1;
    }

    index = start;

    for (i = 0; i < read_n; i++)
    {
        u_int id = (i == read_n - 1)? DMA_ID_REFE: DMA_ID_REF;

        scTag2(
            (QWORD*)(f->tag + index),
            (char*)f->data + VIBUF_ELM_SIZE * index,
            id,
            VIBUF_ELM_SIZE / 16
        );

        index = (index + 1) % f->n;
    }

    f->dmaN += read_n;

    if (f->dmaN)
    {
        if (isNewData)
        {
            d4chcr = (d4chcr & 0x0fffffff) | (DMA_ID_REF << 28);
        }

        setD4_CHCR(d4chcr | 0x100);
    }

    SignalSema(f->sema);

    return 1;
}

int viBufStopDMA(ViBuf *f)
{
    WaitSema(f->sema);

    f->isActive = 0;

    setD4_CHCR(0 << 8 | 1 << 2 | 1);

    f->env.d4madr = *D4_MADR;
    f->env.d4tadr = *D4_TADR;
    f->env.d4qwc =  *D4_QWC;
    f->env.d4chcr = *D4_CHCR;

    while (DGET_IPU_CTRL() & 0xf0) {}

    setD3_CHCR(0 << 8 | 0);

    f->env.d3madr = *D3_MADR;
    f->env.d3qwc =  *D3_QWC;
    f->env.d3chcr = *D3_CHCR;
    f->env.ipubp = DGET_IPU_BP();
    f->env.ipuctrl = DGET_IPU_CTRL();

    SignalSema(f->sema);

    return 1;
}

int viBufRestartDMA(ViBuf *f)
{
    int bp;
    int fp;
    int ifc;
    u_int d4madr_next;
    u_int d4qwc_next;
    u_int d4tadr_next;
    u_int d4chcr_next;
    int index;
    int index_next;
    int id;

    bp = f->env.ipubp & 0x7f;
    fp = (f->env.ipubp >> 16) & 0x3;
    ifc = (f->env.ipubp >> 8) & 0xf;
    d4madr_next = f->env.d4madr - ((fp + ifc) << 4);
    d4qwc_next = f->env.d4qwc + (fp + ifc);
    d4tadr_next = f->env.d4tadr;
    d4chcr_next = f->env.d4chcr | 0x100;

    WaitSema(f->sema);

    if (d4madr_next < (u_int)f->data)
    {
        d4qwc_next = (DATA_ADDR(0) - d4madr_next) >> 4;
        d4madr_next += (u_int)(f->n * VIBUF_ELM_SIZE);
        d4tadr_next = TAG_ADDR(0);

        id = (f->env.d4madr == DATA_ADDR(0) || f->env.d4madr == DATA_ADDR(f->n)) ? DMA_ID_REFE : DMA_ID_REF;

        d4chcr_next = (f->env.d4chcr & 0x0fffffff) | id << 28 | 0x100;

        if (!IsInRegion(0, f->dmaStart, f->dmaN, f->n))
        {
            f->dmaStart = f->n - 1;
            f->dmaN++;
        }
    }
    else if ((index = getFIFOindex(f, (void*)f->env.d4madr)) != (index_next = getFIFOindex(f, (void*)d4madr_next)))
    {
        d4tadr_next = TAG_ADDR(index);
        d4qwc_next = (DATA_ADDR(index) - d4madr_next) >> 4;

        id = (WRAP_ADDR(f->env.d4madr) == DATA_ADDR((f->dmaStart + f->dmaN) % f->n)) ? DMA_ID_REFE : DMA_ID_REF;

        d4chcr_next = (f->env.d4chcr & 0x0fffffff) | id << 28 | 0x100;

        if (!IsInRegion(index_next, f->dmaStart, f->dmaN, f->n))
        {
            f->dmaStart = index_next;
            f->dmaN++;
        }
    }

    if (f->env.d3madr && f->env.d3qwc)
    {
        *D3_MADR = f->env.d3madr;
        *D3_QWC  = f->env.d3qwc;

        setD3_CHCR(f->env.d3chcr | 0x100);
    }

    if (f->dmaN)
    {
        while (sceIpuIsBusy()) {}

        sceIpuBCLR(bp);

        while (sceIpuIsBusy()) {}
    }

    *D4_MADR = d4madr_next;
    *D4_TADR = d4tadr_next;
    *D4_QWC  = d4qwc_next;

    if (f->dmaN)
    {
        setD4_CHCR(d4chcr_next);
    }

    *IPU_CTRL = f->env.ipuctrl;

    f->isActive = 1;

    SignalSema(f->sema);

    return 1;
}

int viBufDelete(ViBuf *f)
{
    setD4_CHCR(0 << 8 | 1 << 2 | 1);

    *D4_QWC = 0;
    *D4_MADR = 0;
    *D4_TADR = 0;

    DeleteSema(f->sema);

    return 1;
}

void viBufFlush(ViBuf *f)
{
    WaitSema(f->sema);

    f->readBytes = bound(f->readBytes, VIBUF_ELM_SIZE);

    SignalSema(f->sema);
}

int viBufModifyPts(ViBuf *f, TimeStamp *new_ts)
{
    TimeStamp *ts;
    int rd;
    int datasize;
    int loop;
    int tgt;
    int pos;
    int size;
    int len;

    rd = (f->wt_ts - f->count_ts + f->n_ts) % f->n_ts;
    datasize =  VIBUF_ELM_SIZE * f->n;
    loop = 1;

    if (f->count_ts > 0)
    {
        while (loop)
        {
            ts = f->ts + rd;

            if (ts->len == 0 || new_ts->len == 0)
            {
                break;
            }

            if (IsPtsInRegion(ts->pos, new_ts->pos, new_ts->len, datasize))
            {
                len = min(new_ts->pos + new_ts->len - ts->pos, ts->len);

                ts->pos = (ts->pos + len) % datasize;
                ts->len -= len;

                if (ts->len == 0)
                {
                    if (ts->pts >= 0)
                    {
                        ts->pts = TS_NONE;
                        ts->dts = TS_NONE;
                        ts->pos = 0;
                        ts->len = 0;
                    }

                    f->count_ts = max(f->count_ts - 1, 0);
                }
            }
            else
            {
                loop = 0;
            }

            rd = (rd + 1) % f->n_ts;
        }
    }

    return 0;
}

int viBufPutTs(ViBuf *f, TimeStamp *ts)
{
    int ret;

    ret = 0;

    WaitSema(f->sema);

    if (f->count_ts < f->n_ts)
    {
        viBufModifyPts(f, ts);

        if (ts->pts >= 0 || ts->dts >= 0)
        {
            f->ts[f->wt_ts].pts = ts->pts;
            f->ts[f->wt_ts].dts = ts->dts;
            f->ts[f->wt_ts].pos = ts->pos;
            f->ts[f->wt_ts].len = ts->len;

            f->count_ts++;
            f->wt_ts = (f->wt_ts + 1) % f->n_ts;
        }

        ret = 1;
    }

    SignalSema(f->sema);

    return ret;
}

int viBufGetTs(ViBuf *f, TimeStamp *ts)
{
    u_int d4madr;
    u_int ipubp;
    int bp;
    int fp;
    int ifc;
    int datasize;
    int tscount;
    u_int stop;
    int isEnd;
    int wt;
    int i;
    int pos;
    int len;
    u_int d4madr_next;
    int size;

    d4madr = *D4_MADR;
    ipubp = DGET_IPU_BP();
    bp = f->env.ipubp & 0x7f;
    fp = (ipubp >> 16) & 0x3;
    ifc = (ipubp >> 8) & 0xf;
    d4madr_next = d4madr - ((fp + ifc) << 4);
    datasize =  VIBUF_ELM_SIZE * f->n;
    isEnd = 0;

    WaitSema(f->sema);

    ts->pts = TS_NONE;
    ts->dts = TS_NONE;

    stop = (d4madr_next + (bp >> 3) + datasize - (u_int)f->data) % datasize;

    tscount = f->count_ts;

    wt = f->wt_ts;

    for (i = 0; i < tscount && !isEnd; i++)
    {
        int j = (wt - tscount + f->n_ts + i) % f->n_ts;

        if (IsPtsInRegion(stop, f->ts[j].pos, f->ts[j].len, datasize))
        {
            isEnd = 1;

            ts->pts = f->ts[j].pts;
            ts->dts = f->ts[j].dts;

            f->ts[j].pts = TS_NONE;
            f->ts[j].dts = TS_NONE;

            f->count_ts -= min(1, f->count_ts);
        }
    }

    SignalSema(f->sema);

    return 1;
}
