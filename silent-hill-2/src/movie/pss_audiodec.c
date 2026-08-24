#include "sh2_common.h"

#include "sce/sdrcmd.h"
#include "sce/sdmacro.h"
#include "sce/sif.h"

#include "movie/movie.h"
#include "movie/pss_audiodec.h"

#include "sound/sh_sd_call.h"

#define AUTODMA_CH 0
#define AU_HEADER_SIZE 40
#define UNIT_SIZE 1024
#define PRESET_VALUE(count)	(count)
#define ZERO_BUFF_SIZE 0x1000

extern /* static */ char _0_buf [ZERO_BUFF_SIZE] __attribute__((aligned(64)));

static void iopGetArea(int *pd0, int *d0, int *pd1, int *d1, AudioDec *ad, int pos);
static int sendToIOP2area(int pd0, int d0, int pd1, int d1, u_char *ps0, int s0, u_char *ps1, int s1);
static int sendToIOP(int dst, u_char *src, int size);
static void changeMasterVolume(u_int val);
static void changeInputVolume(u_int val);

#pragma divbyzerocheck off

void pssAudioColdInit(AudioDec* ad, int iopBuffSize) {
    ad->iopBuff = sceSifAllocIopHeap(iopBuffSize);
    if (ad->iopBuff < 0) {
        printf("Cannot allocate IOP memory\n");
    }
    ad->iopZero = sceSifAllocIopHeap(ZERO_BUFF_SIZE);
    if (ad->iopZero < 0) {
        printf("Cannot allocate IOP memory\n");
    }
    memset(&_0_buf, 0, ZERO_BUFF_SIZE);
    sendToIOP(ad->iopZero, (u_char*) _0_buf, ZERO_BUFF_SIZE);
}


// ////////////////////////////////////////////////////////////////
//
// Create audio decoder
//
int audioDecCreate(
    AudioDec *ad,
    u_char *buff,
    int buffSize,
    int iopBuffSize
)
{
    ad->state = AU_STATE_INIT;
    ad->hdrCount = 0;
    ad->data = buff;
    ad->put = 0;
    ad->count = 0;
    ad->size = buffSize;
    ad->totalBytes = 0;
    ad->totalBytesSent = 0;

    ad->iopBuffSize = iopBuffSize;
    ad->iopLastPos = 0;
    ad->iopPausePos = 0;
/*
    // ///////////////////////////////////////
    //
    // Audio data buffer on IOP
    //
    ad->iopBuff = (int)sceSifAllocSysMemory(0, iopBuffSize, 0);
    if((void *)ad->iopBuff == NULL) {
	printf( "Cannot allocate IOP memory\n");
	return 0;
    }
    printf("IOP memory 0x%08x(size:%d) is allocated\n",
    	ad->iopBuff, iopBuffSize);

    // ///////////////////////////////////////
    //
    // Zero data buffer on IOP
    //
    ad->iopZero = (int)sceSifAllocSysMemory(0, ZERO_BUFF_SIZE, 0);
    if((void *)ad->iopZero == NULL) {
	printf( "Cannot allocate IOP memory\n");
	return 0;
    }
    printf("IOP memory 0x%08x(size:%d) is allocated\n",
    	ad->iopZero, ZERO_BUFF_SIZE);

    // send zero data to IOP
    memset (_0_buf, 0, ZERO_BUFF_SIZE);
    sendToIOP(ad->iopZero, _0_buf, ZERO_BUFF_SIZE);

    // ///////////////////////////////////////
    //
    // Change master volume
    //
    changeMasterVolume(0x3fff);
*/
    return 1;
}

// ////////////////////////////////////////////////////////////////
//
// Delete audio decoder
//
int audioDecDelete(AudioDec *ad)
{
/*
    sceSifFreeIopHeap((void *)ad->iopBuff);
    sceSifFreeIopHeap((void *)ad->iopZero);

    // ///////////////////////////////////////
    //
    // Change master volume
    //
    changeMasterVolume(0x0000);
*/
    return 1;
}

// ////////////////////////////////////////////////////////////////
//
// Pause
//
void audioDecPause(AudioDec *ad)
{
    int ret;
    int retry;
    ad->state = AU_STATE_PAUSE;

    // ///////////////////////////////////////
    //
    // Change input volume
    //
    changeInputVolume(0x0000);



    // ///////////////////////////////////////
    //
    // Stop DMA and save the position to be played
    //
    retry = 64;
    while ((ret = sceSdRemote(1, rSdBlockTrans, AUTODMA_CH,
                   SD_TRANS_MODE_STOP, NULL, 0)) < 0) {
        retry--;
        if (retry < 0) {
            printf("rSdBlockTrans failed\n");
            break;
        }
    }
    ad->iopPausePos = (ret & 0x00FFFFFF) - ad->iopBuff;
    sd_call(1016, 0, 0, 0, 0);


    // ///////////////////////////////////////
    //
    // Clear SPU2 buffer
    //
    retry = 64;
    while ((ret = sceSdRemote(1, rSdVoiceTrans, AUTODMA_CH,
    		 SD_TRANS_MODE_WRITE | SD_TRANS_BY_DMA,
    		 ad->iopZero, 0x4000, ZERO_BUFF_SIZE)) < 0) {
        retry--;
        if (retry < 0) {
            printf("rSdVoiceTrans failed\n");
            break;
        }
    }
}

// ////////////////////////////////////////////////////////////////
//
// Resume
//
void audioDecResume(AudioDec *ad)
{
    // ///////////////////////////////////////
    //
    // Change input volume
    //
    changeInputVolume(0x7fff);

    while (sceSdRemote(1, rSdBlockTrans, AUTODMA_CH,
    		(SD_TRANS_MODE_WRITE_FROM | SD_BLOCK_LOOP),
            ad->iopBuff, (ad->iopBuffSize/UNIT_SIZE)*UNIT_SIZE,
            ad->iopBuff + ad->iopPausePos) < 0) {
        printf("rSdBlockTrans failed\n");
    }

    ad->state = AU_STATE_PLAY;
}

// ////////////////////////////////////////////////////////////////
//
// Start to play audio data
//
void audioDecStart(AudioDec *ad)
{
//    return audioDecResume(ad);
    audioDecResume(ad);
}

// ////////////////////////////////////////////////////////////////
//
// Re-initialize audio decoder
//
void audioDecReset(AudioDec *ad)
{
    // ///////////////////////////////////////
    //
    // Stop audio
    //
    audioDecPause(ad);

    ad->state = AU_STATE_INIT;
    ad->hdrCount = 0;
    ad->put = 0;
    ad->count = 0;
    ad->totalBytes = 0;
    ad->totalBytesSent = 0;
    ad->iopLastPos = 0;
    ad->iopPausePos = 0;
}

// ////////////////////////////////////////////////////////////////
//
// Get empty areas
//
void audioDecBeginPut(AudioDec *ad,
	u_char **ptr0, int *len0, u_char **ptr1, int *len1)
{
    int len;

    // ///////////////////////////////////////
    //
    // return ADS header area when (state == AU_STATE_INIT)
    //
    if (ad->state == AU_STATE_INIT) {
    	*ptr0 = (u_char*)&ad->sshd + ad->hdrCount;
	*len0 = AU_HDR_SIZE - ad->hdrCount;
	*ptr1 = (u_char*)ad->data;
	*len1 = ad->size;

	return;
    }

    // ///////////////////////////////////////
    //
    // Return the empty areas
    //
    len = ad->size - ad->count;

    if (ad->size -  ad->put >= len) { // area0
    	*ptr0 = ad->data + ad->put;
	*len0 = len;
	*ptr1 = NULL;
	*len1 = 0;
    } else {			    // area0 + area1
    	*ptr0 = ad->data + ad->put;
	*len0 = ad->size - ad->put;
	*ptr1 = ad->data;
	*len1 = len - (ad->size - ad->put);
    }
}

// ////////////////////////////////////////////////////////////////
//
// Update pointer
//
void audioDecEndPut(AudioDec *ad, int size)
{
    if (ad->state == AU_STATE_INIT) {
    	int hdr_add = min(size, AU_HDR_SIZE - ad->hdrCount);
    	ad->hdrCount += hdr_add;

	if (ad->hdrCount >= AU_HDR_SIZE) {
	    ad->state = AU_STATE_PRESET;

/*
	    printf("-------- audio information --------------------\n");
	    printf("[%c%c%c%c]\n"
	       "header size:                            %d\n"
	       "type(0:PCM big, 1:PCM little, 2:ADPCM): %d\n"
	       "sampling rate:                          %dHz\n"
	       "channels:                               %d\n"
	       "interleave size:                        %d\n"
	       "interleave start block address:         %d\n"
	       "interleave end block address:           %d\n",
		    ad->sshd.id[0],
		    ad->sshd.id[1],
		    ad->sshd.id[2],
		    ad->sshd.id[3],
		    ad->sshd.size,
		    ad->sshd.type,
		    ad->sshd.rate,
		    ad->sshd.ch,
		    ad->sshd.interSize,
		    ad->sshd.loopStart,
		    ad->sshd.loopEnd
	    );

	    printf("[%c%c%c%c]\n"
	       "data size:                              %d\n",
		    ad->ssbd.id[0],
		    ad->ssbd.id[1],
		    ad->ssbd.id[2],
		    ad->ssbd.id[3],
		    ad->ssbd.size
	    );
*/
	}
	size -= hdr_add;
    }
    ad->put = (ad->put + size) % ad->size;
    ad->count += size;
    ad->totalBytes += size;
}

// ////////////////////////////////////////////////////////////////
//
// Check to see if enough data is already sent to IOP or not
//
int audioDecIsPreset(AudioDec *ad)
{
    return ad->totalBytesSent >= PRESET_VALUE(ad->iopBuffSize);
}

// ////////////////////////////////////////////////////////////////
//
// Send data to IOP
//
int audioDecSendToIOP(AudioDec *ad)
{
    int pd0, pd1, d0, d1;
    u_char *ps0, *ps1;
    int s0, s1;
    int count_sent = 0;
    int countAdj;
    int pos = 0;

    switch (ad->state) {
        case AU_STATE_INIT:
	    return 0;
	    break;

        case AU_STATE_PRESET:
	    pd0 = ad->iopBuff + (ad->totalBytesSent) % ad->iopBuffSize;
	    d0 = ad->iopBuffSize - ad->totalBytesSent;
	    pd1 = 0;
	    d1 = 0;
	    break;

        case AU_STATE_PLAY:
	    pos = ((sceSdRemote(1, rSdBlockTransStatus, AUTODMA_CH)
	    	& 0x00FFFFFF) - ad->iopBuff);
        if (0 > pos || pos > ad->iopBuffSize)
            printf("audioDecSendToIOP: pos=%d\n", pos);
	    iopGetArea(&pd0, &d0, &pd1, &d1, ad, pos);
	    break;

        case AU_STATE_PAUSE:
	    return 0;
	    break;
    }

    ps0 = ad->data + (ad->put - ad->count + ad->size) % ad->size;
    ps1 = ad->data;

    // adjust to UNIT_SIZE boundary
    countAdj = (ad->count / UNIT_SIZE) * UNIT_SIZE;

    s0 = min(ad->data + ad->size - ps0, countAdj);
    s1 = countAdj - s0;

    if (d0 + d1 >= UNIT_SIZE && s0 + s1 >= UNIT_SIZE) {
    	count_sent = sendToIOP2area(pd0, d0, pd1, d1, ps0, s0, ps1, s1);
    }

    ad->count -= count_sent;

    ad->totalBytesSent += count_sent;
    ad->iopLastPos = (ad->iopLastPos + count_sent) % ad->iopBuffSize;

    return count_sent;
}

// ////////////////////////////////////////////////////////////////
//
// Get empty area of IOP audio buffer
//
static void iopGetArea(int *pd0, int *d0, int *pd1, int *d1,
					AudioDec *ad, int pos)
{
    int len = (pos + ad->iopBuffSize - ad->iopLastPos - UNIT_SIZE)
    			% ad->iopBuffSize;

    // adjust to UNIT_SIZE boundary
    len = (len / UNIT_SIZE) * UNIT_SIZE;

    if (ad->iopBuffSize -  ad->iopLastPos >= len) { // area0
    	*pd0 = ad->iopBuff + ad->iopLastPos;
	*d0 = len;
	*pd1 = 0;
	*d1 = 0;
    } else {			    // area0 + area1
    	*pd0 = ad->iopBuff + ad->iopLastPos;
	*d0 = ad->iopBuffSize - ad->iopLastPos;
	*pd1 = ad->iopBuff;
	*d1 = len - (ad->iopBuffSize - ad->iopLastPos);
    }
}

// ////////////////////////////////////////////////////////////////
//
// Send data to IOP
//
static int sendToIOP2area(int pd0, int d0, int pd1, int d1,
		u_char *ps0, int s0, u_char *ps1, int s1)
{
    if (d0 + d1 < s0 + s1) {
    	int diff = (s0 + s1) - (d0 + d1);
	if (diff >= s1) {
	    s0 -= (diff - s1);
	    s1 = 0;
	} else {
	    s1 -= diff;
	}
    }

    //
    // (d0 + d1 >= s0 + s1)
    //
    if (s0 >= d0) {
    	sendToIOP(pd0,			ps0,		d0);
    	sendToIOP(pd1,			ps0 + d0,	s0 - d0);
    	sendToIOP(pd1 + s0 - d0,	ps1,		s1);
    } else { // s0 < d0
    	if (s1 >= d0 - s0) {
	    sendToIOP(pd0,		ps0,		s0);
	    sendToIOP(pd0 + s0,		ps1,		d0 - s0);
	    sendToIOP(pd1,		ps1 + d0 - s0,	s1 - (d0 - s0));
	} else { // s1 < d0 - s0
	    sendToIOP(pd0,		ps0,		s0);
	    sendToIOP(pd0 + s0,		ps1,		s1);
	}
    }
    return s0 + s1;
}

// ////////////////////////////////////////////////////////////////
//
// Send data to IOP
//
static int sendToIOP(int dst, u_char *src, int size)
{
    sceSifDmaData transData;
    int did;

    if (size <= 0) {
        return 0;
    }

    transData.data = (u_int)src;
    transData.addr = (u_int)dst;
    transData.size = size;
    transData.mode = 0; // caution
    FlushCache(0);

    while ((did = sceSifSetDma( &transData, 1 )) == 0) {
        printf("sceSifSetDma() failed\n");
    }

    while (sceSifDmaStat(did) >= 0)
    	;

    return size;
}

// ////////////////////////////////////////////////////////////////
//
// Change input volume
//
static void changeInputVolume(u_int val)
{
    sceSdRemote(1, rSdSetParam, AUTODMA_CH | SD_P_BVOLL, val);
    sceSdRemote(1, rSdSetParam, AUTODMA_CH | SD_P_BVOLR, val);
}
