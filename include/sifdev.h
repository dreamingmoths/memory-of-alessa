#ifndef SIFDEV_H
#define SIFDEV_H

extern int sceOpen(const char* filename, int flag, ...);
extern int sceClose(int fd);
extern int sceRead(int fd, void* buf, int nbyte); 
extern int sceLseek(int fd, int offset, int where); // I am putting these as extern cause this is how they are put in the sdk

int sceFsReset(void);
void sceSifLoadFileReset(void);
int sceSifSyncIop(void);
int sceSifLoadModule(const char* filename, int args, const char* argp);
int sceSifRebootIop(const char* img);

#endif // SIFDEV_H
