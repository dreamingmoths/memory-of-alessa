#ifndef SIFDEV_H
#define SIFDEV_H

/* Flag for sceOpen() */
#define SCE_RDONLY      0x0001
#define SCE_WRONLY      0x0002
#define SCE_RDWR        0x0003
#define SCE_NBLOCK      0x0010  /* Non-Blocking I/O */
#define SCE_APPEND      0x0100  /* append (writes guaranteed at the end) */
#define SCE_CREAT       0x0200  /* open with file create */
#define SCE_TRUNC       0x0400  /* open with truncation */
#define SCE_EXCL        0x0800  /* exclusive create */
#define SCE_NOBUF       0x4000  /* no device buffer and console interrupt */
#define SCE_NOWAIT      0x8000  /* asyncronous i/o */

/* Seek Code */
#ifndef SCE_SEEK_SET
#define SCE_SEEK_SET        (0)
#endif
#ifndef SCE_SEEK_CUR
#define SCE_SEEK_CUR        (1)
#endif
#ifndef SCE_SEEK_END
#define SCE_SEEK_END        (2)
#endif


/* Ioctl Code */
#define SCE_FS_EXECUTING	0x1

extern int sceOpen(const char* filename, int flag, ...);
extern int sceClose(int fd);
extern int sceRead(int fd, void* buf, int nbyte);
extern int sceLseek(int fd, int offset, int where); // I am putting these as extern cause this is how they are put in the sdk

int sceFsReset(void);
void *sceSifAllocIopHeap(unsigned int);
void sceSifLoadFileReset(void);
int sceSifSyncIop(void);
int sceSifLoadModule(const char* filename, int args, const char* argp);
int sceSifRebootIop(const char* img);

#endif // SIFDEV_H
