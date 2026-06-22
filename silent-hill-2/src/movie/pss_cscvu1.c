#include "sh2_common.h"
#include "movie/pss_cscvu1.h"
#include "mpeg/defs.h"
#include "eeregs.h"
#include "libvifpk.h"

#pragma divbyzerocheck off

typedef struct {
    u_char y[16][16];
    u_char cb[8][8];
    u_char cr[8][8];
} mbstr;

// VIF code
#define VIF1CMD_BASE 3
#define VIF1CMD_OFFSET 2
#define VIF1CMD_V2_32 0x64
#define VIF1CMD_V4_32 0x6c
#define VIF1CMD_S8 0x62
#define VIF1CMD_MASKEN 0x10

// VUMEM1 allocation
#define VUMEM1_BASE0 0x7
#define VUMEM1_BASE1 0x15A
#define VUMEM1_BASE2 0x2AD
#define VUMEM1_IOFFSET 0x1	// giftag size
#define VUMEM1_IHEADLEN 2	// input header (nextbase, Xd/Yd)
#define VUMEM1_IBUFSIZE 0x150	// input buffer except for IOFFSET/IHEADLEN

static void mkrefpacket(
    sceVif1Packet *pkt,
    void *src,
    u_int upkcmd,
    u_int vuaddr,
    u_int vunum,
    u_int dmarate
);
static void mkcntpacket(sceVif1Packet *pkt, u_int code1, u_int code2);

extern /* static */ u_int vu1_base_adr[3]; /*={
    VUMEM1_BASE0,
    VUMEM1_BASE1,
    VUMEM1_BASE2
};*/

void cscVu1Init(CscVu1 *csc)
{
    // VU1 mpg for interlace frame picture
    csc->micro[CSCVU1_INTER_FRAME ][0]= &load_yuvfrfl0_mpg; // top
    csc->micro[CSCVU1_INTER_FRAME ][1]= &load_yuvfrfl1_mpg; // bottom

    // VU1 mpg for progressive frame picture
    csc->micro[CSCVU1_PROG_FRAME][0]= &load_yuvprg0_mpg; // top
    csc->micro[CSCVU1_PROG_FRAME][1]= &load_yuvprg1_mpg; // bottom
}

void cscVu1Xyz2offset(
    CscVu1 *csc,
    int type,
    int isBottom,
    int xoff,
    int yoff
)
{
    u_int *tag;
    u_int *xyz2offset;

    tag = (u_int *)UncAddr(&vu1_init);
    tag[1] = (u_int)csc->micro[type][isBottom];
    xyz2offset = (u_int *)UncAddr(&vu1_XYZ2Offset);
    xyz2offset[0] = xoff;
    xyz2offset[1] = yoff;
}

void cscVu1Kick(u_int *tags)
{
    *D1_TADR = (u_int)DmaAddr(tags);
    *D1_QWC  = 0;
    *D1_CHCR = 0x145;                 // TTE=1 
}

static u_int *setGIFtag(
    u_int *p,
    u_long regs,
    u_int nreg,
    u_int flg,
    u_int prim,
    u_int pre,
    u_int eop,
    u_int nloop
)
{
    p[0] = eop<<15 | nloop;
    p[1] = pre<<(46-32) | prim<<(47-32) | flg<<(58-32) | nreg<<(60-32);
    p[2] = regs&0xffffffff;
    p[3] = regs>>32;
    return p + 4;
}

void cscVu1SetTag_frfl(u_int *tags, void *image, int width, int height)
{
    sceVif1Packet pkt;
    int i, j;
    int dstx, dsty, pdstx, pdsty;
    int basep=1;
    int nextbasep;
    int mbx = width >> 4;
    int mby = height >> 4;
    u_long128 giftagPoint;
    u_long128 giftagGsAD;
    u_int lastkickp;
    u_int *p;
    int vumem1_iuvnum=0x40;			// unpack size for CrCb
    int vumem1_iynum=0x100;			// unpack size for y
    mbstr *imgbase=image;
    mbstr *img;
    char *src;
    int offset;
    int ir;

    p = tags;

    sceVif1PkInit(&pkt, (u_long128 *)p);
    sceVif1PkReset(&pkt);

    sceVif1PkCall(&pkt, (u_long128 *)&vu1_init, 0);

    sceVif1PkCnt(&pkt,0);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSHE(0));
    // RGBAQ+XYZ2(0x51), NREG(2), PACKED(0), POINT(0), EN_PRIM(1), EOP(1), NLOOP=128
    sceVif1PkAddCode(&pkt, 0x01000404);

    // set giftag
    setGIFtag((u_int *)&giftagPoint, 0x51, 2, 0, 0, 1, 1, 128);
    sceVif1PkAddCode(&pkt, (VIF1CMD_V4_32<<24)|(1<<16)|VUMEM1_BASE0);
    sceVif1PkAddUpkData128(&pkt, giftagPoint);
    sceVif1PkAddCode(&pkt, (VIF1CMD_V4_32<<24)|(1<<16)|VUMEM1_BASE1);
    sceVif1PkAddUpkData128(&pkt, giftagPoint);
    sceVif1PkAddCode(&pkt, (VIF1CMD_V4_32<<24)|(1<<16)|VUMEM1_BASE2);
    sceVif1PkAddUpkData128(&pkt, giftagPoint);

    pdstx=0;
    pdsty=0;

    for (i = 0; i < mbx; i++) {
	for (j = 0; j < mby; j++) {
	    img= &imgbase[i*mby+j];

	    nextbasep= (basep+1)%3;
	    dstx=i*16*16;
	    dsty=j*8*16;
		
	    sceVif1PkCnt(&pkt,0);
	    sceVif1PkAddCode(&pkt,
			     ((VIF1CMD_V2_32<<24)
			     | (2<<16)
			     | (vu1_base_adr[basep]+VUMEM1_IOFFSET)));
	    sceVif1PkAddUpkData32(&pkt, vu1_base_adr[nextbasep]); // nextbase
	    sceVif1PkAddUpkData32(&pkt, 0);
	    sceVif1PkAddUpkData32(&pkt, dstx-pdstx); // Xd
	    sceVif1PkAddUpkData32(&pkt, dsty-pdsty); // Yd
		
	    // Y unpack S8, [Y--C]
	    sceVif1PkAddCode(&pkt, (SCE_VIF1_SET_STMASK(0)));
	    sceVif1PkAddData(&pkt, 0xbcbcbcbc);	       // X: input data, YZ:masked W:COL

	    sceVif1PkRef(&pkt, DmaAddr(img->y),vumem1_iynum/16, 0,
			 ((VIF1CMD_S8|VIF1CMD_MASKEN)<<24)
			 | ((vumem1_iynum&0xff)<<16)
			 | 0x4000
			 | (vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN),
			 0);  // Y data

	    if (i<mbx-1){
		offset=0;
		ir=i+1;
	    } else {
		offset= -7;
		ir=i;
	    }

	    // Cb unpack S8, [-Cb--]
  	    // Cb right-upper block
	    if (j>0) src= &imgbase[ir*mby+j-1].cb[6][0];
	    else src= &imgbase[ir*mby+j].cb[0][0];
	    mkcntpacket(&pkt,
			SCE_VIF1_SET_STMASK(0), 0xf3f3f3f3); // Y: input data, XZW:masked
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+offset,
		16, 16);

	    // Cb right-lower block
	    if (j<mby-1) src= &imgbase[ir*mby+j+1].cb[0][0];
	    else src= &imgbase[ir*mby+j].cb[6][0];
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN+16+16+vumem1_iuvnum+offset,
		16, 16);

	    // Cb right-center block
	    mkrefpacket(
		&pkt, &imgbase[ir*mby+j].cb[0][0], VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+16+offset,
		vumem1_iuvnum, 16);

  	    // Cb upper block
	    if (j>0) src= &imgbase[i*mby+j-1].cb[6][0];
	    else src= &img->cb[0][0];
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN
			+(vumem1_iynum-vumem1_iuvnum)-16,
		16, 16);

  	    // Cb lower block
	    if (j<mby-1) src= &imgbase[i*mby+j+1].cb[0][0];
	    else src= &img->cb[6][0];
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN +vumem1_iynum,
		16, 16);

	    // Cb center block
	    mkrefpacket(
		&pkt, img->cb, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+vumem1_iynum-vumem1_iuvnum,
		vumem1_iuvnum, 16);


	    // Cr unpack S8, [--Cr-]
  	    // Cr right-upper block
	    if (j>0) src= &imgbase[ir*mby+j-1].cr[6][0];
	    else src= &imgbase[ir*mby+j].cr[0][0];
	    mkcntpacket(&pkt,
			SCE_VIF1_SET_STMASK(0), 0xcfcfcfcf); // Z: input data, XYW:masked
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+offset,
		16, 16);

	    // Cr right-lower block
	    if (j<mby-1) src= &imgbase[ir*mby+j+1].cr[0][0];
	    else src= &imgbase[ir*mby+j].cr[6][0];
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN+16+16+vumem1_iuvnum+offset,
		16, 16);

	    // Cr right-center block
	    mkrefpacket(
		&pkt, &imgbase[ir*mby+j].cr[0][0], VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+16+offset,
		vumem1_iuvnum, 16);

  	    // upper block
	    if (j>0) src= &imgbase[i*mby+j-1].cr[6][0];
	    else src= &img->cr[0][0];
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN
			+(vumem1_iynum-vumem1_iuvnum)-16,
		16, 16);

	    // Cr lower block
	    if (j<mby-1) src= &imgbase[i*mby+j+1].cr[0][0];
	    else src= &img->cr[6][0];
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN +vumem1_iynum,
		16, 16);

	    // center block
	    mkrefpacket(
		&pkt, img->cr, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+vumem1_iynum-vumem1_iuvnum,
		vumem1_iuvnum, 16);

	    sceVif1PkCnt(&pkt,0);
  	    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSH(0));
    	    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_MSCNT(0));
	    pdstx=dstx;
	    pdsty=dsty;
	    basep=nextbasep;
	}
    }

    // xgkick last data
    lastkickp=CSCVU1_LASTKICK;
    sceVif1PkCnt(&pkt,0);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_MSCALF(lastkickp, 0));

    // send GS_FINISH
    sceVif1PkEnd(&pkt,0);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkOpenDirectCode(&pkt, 0);
    setGIFtag((u_int *)&giftagGsAD, 0xe, 1, 0, 0, 0, 1, 0);
    sceVif1PkOpenGifTag(&pkt, giftagGsAD);
    sceVif1PkAddGsAD(&pkt, SCE_GS_FINISH, 0);
    sceVif1PkCloseGifTag(&pkt);
    sceVif1PkCloseDirectCode(&pkt);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkTerminate(&pkt);

}

void cscVu1SetTag_prog(u_int *tags, void *image, int width, int height)
{
    sceVif1Packet pkt;
    int i, j;
    int dstx, dsty, pdstx, pdsty;
    int basep=1;
    int nextbasep;
    int mbx = width >> 4;
    int mby = height >> 4;
    u_long128 giftagPoint;
    u_long128 giftagGsAD;
    u_int lastkickp;
    u_int *p;
    int vumem1_iuvnum=0x40;			// unpack size for CrCb
    int vumem1_iynum=0x100;			// unpack size for y
    mbstr *imgbase=image;
    mbstr *img;
    char *src;
    int ioffset,joffset;
    int ir;

    p = tags;

    sceVif1PkInit(&pkt, (u_long128 *)p);
    sceVif1PkReset(&pkt);

    sceVif1PkCall(&pkt, (u_long128 *)&vu1_init, 0);

    sceVif1PkCnt(&pkt,0);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSHE(0));
    // RGBAQ+XYZ2(0x51), NREG(2), PACKED(0), POINT(0), EN_PRIM(1), EOP(1), NLOOP=128
    sceVif1PkAddCode(&pkt, 0x01000404);

    // set giftag
    setGIFtag((u_int *)&giftagPoint, 0x51, 2, 0, 0, 1, 1, 128);
    sceVif1PkAddCode(&pkt, (VIF1CMD_V4_32<<24)|(1<<16)|VUMEM1_BASE0);
    sceVif1PkAddUpkData128(&pkt, giftagPoint);
    sceVif1PkAddCode(&pkt, (VIF1CMD_V4_32<<24)|(1<<16)|VUMEM1_BASE1);
    sceVif1PkAddUpkData128(&pkt, giftagPoint);
    sceVif1PkAddCode(&pkt, (VIF1CMD_V4_32<<24)|(1<<16)|VUMEM1_BASE2);
    sceVif1PkAddUpkData128(&pkt, giftagPoint);

    pdstx=0;
    pdsty=0;

    for (i = 0; i < mbx; i++) {
	for (j = 0; j < mby; j++) {
	    img= &imgbase[i*mby+j];

	    nextbasep= (basep+1)%3;
	    dstx=i*16*16;
	    dsty=j*8*16;
		
	    sceVif1PkCnt(&pkt,0);
	    sceVif1PkAddCode(&pkt,
			     ((VIF1CMD_V2_32<<24)
			     | (2<<16)
			     | (vu1_base_adr[basep]+VUMEM1_IOFFSET)));

	    sceVif1PkAddUpkData32(&pkt, vu1_base_adr[nextbasep]); // nextbase
	    sceVif1PkAddUpkData32(&pkt, 0);
	    sceVif1PkAddUpkData32(&pkt, dstx-pdstx); // Xd
	    sceVif1PkAddUpkData32(&pkt, dsty-pdsty); // Yd
		
	    // Y unpack S8, [Y--C]
	    sceVif1PkAddCode(&pkt, (SCE_VIF1_SET_STMASK(0)));
	    sceVif1PkAddData(&pkt, 0xbcbcbcbc);	       // X: input data, YZ:masked W:COL

	    sceVif1PkRef(&pkt, DmaAddr(img->y),vumem1_iynum/16, 0,
			 ((VIF1CMD_S8|VIF1CMD_MASKEN)<<24)
			 | ((vumem1_iynum&0xff)<<16)
			 | 0x4000
			 | (vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN),
			 0);  // Y data

	    if (i<mbx-1){
		ioffset=0;
		ir=i+1;
	    } else {
		ioffset= -7;
		ir=i;
	    }

	    // Cb unpack S8, [-Cb--]
  	    // Cb right-upper block
	    if (j>0){
		src= &imgbase[ir*mby+j-1].cb[6][0];
		joffset=0;
	    } else {
		src= &imgbase[ir*mby+j].cb[0][0];
		joffset=8;
	    }
	    mkcntpacket(&pkt,
			SCE_VIF1_SET_STMASK(0), 0xf3f3f3f3); // Y: input data, XZW:masked
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+ioffset+joffset,
		16, 16);

	    // Cb right-lower block
	    if (j<mby-1){
		src= &imgbase[ir*mby+j+1].cb[0][0];
		joffset=0;
	    } else {
		src= &imgbase[ir*mby+j].cb[6][0];
		joffset= -8;
	    }
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN+16+16+vumem1_iuvnum+ioffset+joffset,
		16, 16);

	    // Cb right-center block
	    mkrefpacket(
		&pkt, &imgbase[ir*mby+j].cb[0][0], VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+16+ioffset,
		vumem1_iuvnum, 16);

  	    // Cb upper block
	    if (j>0){
		src= &imgbase[i*mby+j-1].cb[6][0];
		joffset=0;
	    } else {
		src= &img->cb[0][0];
		joffset=8;
	    }
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN
			+(vumem1_iynum-vumem1_iuvnum)-16+joffset,
		16, 16);

  	    // Cb lower block
	    if (j<mby-1){
		src= &imgbase[i*mby+j+1].cb[0][0];
		joffset=0;
	    } else {
		src= &img->cb[6][0];
		joffset= -8;
	    }
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN +vumem1_iynum+joffset,
		16, 16);

	    // Cb center block
	    mkrefpacket(
		&pkt, img->cb, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+vumem1_iynum-vumem1_iuvnum,
		vumem1_iuvnum, 16);


	    // Cr unpack S8, [--Cr-]
  	    // Cr right-upper block
	    if (j>0){
		src= &imgbase[ir*mby+j-1].cr[6][0];
		joffset=0;
	    } else {
		src= &imgbase[ir*mby+j].cr[0][0];
		joffset=8;
	    }
	    mkcntpacket(&pkt,
			SCE_VIF1_SET_STMASK(0), 0xcfcfcfcf); // Z: input data, XYW:masked
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+ioffset+joffset,
		16, 16);

	    // Cr right-lower block
	    if (j<mby-1){
		src= &imgbase[ir*mby+j+1].cr[0][0];
		joffset=0;
	    } else {
		src= &imgbase[ir*mby+j].cr[6][0];
		joffset= -8;
	    }
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN+16+16+vumem1_iuvnum+ioffset+joffset,
		16, 16);

	    // Cr right-center block
	    mkrefpacket(
		&pkt, &imgbase[ir*mby+j].cr[0][0], VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+16+16+ioffset,
		vumem1_iuvnum, 16);

  	    // Cr upper block
	    if (j>0){
		src= &imgbase[i*mby+j-1].cr[6][0];
		joffset=0;
	    } else {
		src= &img->cr[0][0];
		joffset=8;
	    }
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN, 
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN
			+(vumem1_iynum-vumem1_iuvnum)-16+joffset,
		16, 16);

  	    // Cr lower block
	    if (j<mby-1){
		src= &imgbase[i*mby+j+1].cr[0][0];
		joffset=0;
	    } else {
		src= &img->cr[6][0];
		joffset= -8;
	    }
	    mkrefpacket(
		&pkt, src, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep] +VUMEM1_IOFFSET +VUMEM1_IHEADLEN +vumem1_iynum+joffset,
		16, 16);

	    // Cr center block
	    mkrefpacket(
		&pkt, img->cr, VIF1CMD_S8|VIF1CMD_MASKEN,
		vu1_base_adr[basep]+VUMEM1_IOFFSET+VUMEM1_IHEADLEN+vumem1_iynum-vumem1_iuvnum,
		vumem1_iuvnum, 16);

	    sceVif1PkCnt(&pkt,0);
  	    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSH(0));
    	    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_MSCNT(0));
	    pdstx=dstx;
	    pdsty=dsty;
	    basep=nextbasep;
	}
    }

    // xgkick last data
    lastkickp=CSCVU1_LASTKICK;
    sceVif1PkCnt(&pkt,0);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_MSCALF(lastkickp, 0));

    // send GS_FINISH
    sceVif1PkEnd(&pkt,0);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkOpenDirectCode(&pkt, 0);
    setGIFtag((u_int *)&giftagGsAD, 0xe, 1, 0, 0, 0, 1, 0);
    sceVif1PkOpenGifTag(&pkt, giftagGsAD);
    sceVif1PkAddGsAD(&pkt, SCE_GS_FINISH, 0);
    sceVif1PkCloseGifTag(&pkt);
    sceVif1PkCloseDirectCode(&pkt);
    sceVif1PkAddCode(&pkt, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkTerminate(&pkt);
}

void cscVu1SetTag(u_int *tags,
    int type, void *image, int width, int height)
{
    switch (type) {
        case CSCVU1_INTER_FRAME:
	    cscVu1SetTag_frfl(tags, image, width, height);
	    break;

	case CSCVU1_PROG_FRAME:
  	    cscVu1SetTag_prog(tags, image, width, height);
	    break;
    }
}

static void mkrefpacket(sceVif1Packet *pkt, void *src, u_int upkcmd, u_int vuaddr, u_int vunum, u_int dmarate)
{
    sceVif1PkRef(pkt, DmaAddr(src),vunum/dmarate, 0,
		 (upkcmd<<24) | (vunum<<16) | 0x4000 | vuaddr,
		 0); 
}

static void mkcntpacket(sceVif1Packet *pkt, u_int code1, u_int code2)
{
    sceVif1PkCnt(pkt,0);
    sceVif1PkAddData(pkt, code1);
    sceVif1PkAddData(pkt, code2);
}
