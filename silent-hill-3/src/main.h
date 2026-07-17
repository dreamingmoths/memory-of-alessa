#ifndef MAIN_H
#define MAIN_H

typedef union DB_WATCH_POINT {
    char code0x00000001[1];
    char code0x00000002[2];
    char code0x00000004[4];
    char code0x00000008[8];
    char code0x00000010[16];
    char code0x00000020[32];
    char code0x00000040[64];
    char code0x00000080[128];
    char code0x00000100[256];
    char code0x00000200[512];
    char code0x00000400[1024];
    char code0x00000800[2048];
    char code0x00001000[4096];
    char code0x00002000[8192];
    char code0x00004000[16384];
    char code0x00008000[32768];
    char code0x00010000[65536];
    char code0x00020000[131072];
    char code0x00040000[262144];
    char code0x00080000[524288];
    char code0x00100000[1048576];
    char code0x00200000[2097152];
    char code0x00400000[4194304];
    char code0x00800000[8388608];
    char code0x01000000[16777216];
    char code0x02000000[33554432];
    char code0x04000000[67108864];
} DB_WATCH_POINT;
extern DB_WATCH_POINT* db_watch_point;

extern void func_0012BD80(void);
extern void func_0012BDC0(void);
extern void func_0012C980(void);
extern int func_0012C9B0(void);
extern void func_0012CED0(void);
extern void func_0012CEF0(void);

/* @brief This function retrieves the equivalent of `_SH2_SYS::step[]`.
 * While in SH2 it is required to manually input what state to retrieve, SH3
 * handle this with this function which returns the state of the game based
 * on the current level the code is being executed.
 */
extern int func_0012D080(void);

extern void func_0012DC50(void);
extern void func_0012DCA0(void); 
extern void func_00130640(int arg0);
extern int func_00130650(void);
extern void func_0013A780(void);
extern void func_0013CE70(void);
extern int func_00151150(int arg0, int arg1);
extern void func_00156370(int arg0);
extern void func_00156380(void);
extern void func_00156390(void);
extern void func_00156480(void);
extern void func_00156AC0(void);
extern int func_00156B50(int arg0);
extern int func_00156B80(int arg1);
extern void func_0015DB70(void);
extern void func_00172FA0(void);

/* @note Game states.
 * 1  = Main menu/splash screen
 * 2  = Loading screen
 * 5  = In-game
 * 6  = Inventory
 * 14 = Option menu
 *
 * @note PC apparently shares the same list.
 *
 * @note SH2 counterpart and PC in Ghidra tells this function returns some 4 byte value.
 */
extern void GameMain(void);

extern void func_00195490(void);
extern void func_00195A40(void);
extern void func_00195B90(void);
extern void func_001D90D0(void);
extern void func_001D9190(void);
extern void func_001D91D0(void);
extern void func_001D9350(void);
extern void func_001D9500(void);
extern void func_001E2830(void);
extern void func_001E4E10(void);
extern void func_001E5050(void);
extern void func_001E5170(void);
extern void func_00337AB0(void);

extern int func_00115890(int arg0);
extern void func_0012BDF0(s_char* arg0);

/* @brief This function set a value to the equivalent of `_SH2_SYS::step[]`.
 * Just like `func_0012D080` but it instead of retrieving the value it sets
 * the value.
 */
extern void func_0012CFE0(int arg0);

extern void func_0012DCB0(int arg0);
extern void shSetDF(int fpi);
extern void func_0019B450(void);
extern void func_0019B540(int arg0);
extern int func_0019B580(int arg0);
extern void dSync(int arg0, int arg1, int arg2);
extern void func_001D9090(int arg0);
extern void func_001E4E30(int arg0);
extern void func_00281D80(int, int);
extern void func_00282090(int arg0);

/* extern void func_0026730(int arg0);
 * Used to defines values related framerate limit and sets game's delta timer value.
 */
 
/* extern int func_002A6340(void);
 * Handle both splash screen and main title screen.
 * Unlike SH1/2 where the splash screen is handled in a different state, SH3 handles
 * the splash screen in the same state as the main title screen.
 *
 * 3 = Warning Content Screen Start
 * 4 = Unused Warning Unfinished State Screen
 */

/* extern void func_002A6730(int arg0, int arg1);
 * Used during the splash screens.
 * @param arg0 Background image index
 * @param arg1 Text index
 */
 
extern int D_003D44A0;
extern int D_003D44A8;
extern int D_003D44B0;

#endif
