#include "building_f_02.h"

void func_01F6D680_building_f_02(void) {
    switch (RoomName()) {    
        case BUILDING_KMN_JACK_ROOM:
            if (!((D_1D3166C >> 1) & 1)) { // if you don't have the jack
                func_0016CA40(7);
                D_1D31710 |= 0x200; 
            } else {
                D_1D31710 &= ~0x200; // jack grabbed
            }
        break;
        case BUILDING_5F_SCREWDRIVER_CORRIDOR:
            // riddle diff is normal+(???) & if you don't have the screwdriver
            if (((u_char) GetRiddleLevel()) && !((D_1D31668 >> 0x1E) & 1)) {
                func_0016CA40(4);
                D_1D31710 |= 0x1000;
            } else {
                D_1D31710 &= ~0x1000; // screwdriver grabbed
            }
        break;
        case BUILDING_GALLERY_KATANA_ROOM:
            if (!(D_1D3166C & 1)) { // if you don't have the katana
                func_0016CA40(3);
                D_1D31710 |= 0x2000;
            } else {
                D_1D31710 &= ~0x2000; // katana grabbed
            }
        break;
    }
}
