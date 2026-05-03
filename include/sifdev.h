#ifndef SIFDEV_H
#define SIFDEV_H

int sceFsReset(void);
void sceSifLoadFileReset(void);
int sceSifSyncIop(void);
int sceSifLoadModule(const char* filename, int args, const char* argp);
int sceSifRebootIop(const char* img);

#endif // SIFDEV_H
