#include "pad.h"

void shPadInit(void) {
    shQzero(&pad, 0x40);
    shQzero(&pad_bak, 0x28);
    shQzero(&padf, 0x28);
    pad_x = 1;
    key_config.item = 4;
    key_config.front_move = 0x400;
    key_config.back_move = 0x800;
    key_config.right_move = 0x20000;
    key_config.left_move = 0x10000;
    key_config.right_turn = 0x100;
    key_config.left_turn = 0x200;
    key_config.search_view = 0x40000;
    key_config.ready = 0x80000;
    key_config.pause = 8;
    key_config.map = 0x1000;
    key_config.skip = 4;
    key_config.enter = 0x4000;
    key_config.action = 0x4000;
    key_config.cancel = 0x8000;
    key_config.light = 0x2000;
    key_config.dash = 0x8000;
    key_config.attack = 0x4000;
    shPadSetGameKeyAssign();
}

void shPadSet(void) {
    int i;
    int j;
    int work; u_char *foo;
    for (i = 0; i < 20; i++) {
        pad_bak[0][i] = pad[0][i];
        pad_bak[1][i] = pad[1][i];
    }
    repeat[0] = repeat[1] = 0;
    
    
    
    
    
    
    
    
    
    

    
    libShPadRead(0, 0, &pad[0][0]);
    libShPadRead(1, 0, &pad[1][0]);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    shSysKeyNormalize((char *)pad[0]);
    shSysKeyNormalize((char *)pad[1]);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    for (i = 0; i < 2; i++) {
    
        
        
        // Good luck figuring this one out
        work = pad[i][2]; work = pad[i][3];

        
        
        pad[i][0] = pad[i][0x14];
        pad[i][1] = pad[i][0x15];
        pad[i][2] = pad[i][0x16];
        pad[i][3] = pad[i][0x17];
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 20; j++) {
            if (pad[i][j] != 0) {
                if (padf[i][j] == 0.0f) repeat[i] |= (1 << j);
                padf[i][j] += shGetDT();
                if (padf[i][j] > 0.8f) {
                    repeat[i] |= (1 << j);
                    padf[i][j] -= 0.1f;
                }
            } else padf[i][j] = 0.0f;
        }
    }

    
    if (shPadTrigger(pad_x, 8)) {
        pad_x++;
        if (12 < pad_x) pad_x = 1;
        printf("Contoroler 2 port change : %d\n", pad_x);
    }
}

int shPadGetPort(void) {
    if (dbFlag(-1) == 0) {
        return 0;
    }
    if (dbSwitchSysPadPort() != 0) {
        return pad_x;
    }
    return 1;
}

int shPadPress(int port /* r17 */, int key /* r16 */) {

    int ret; // r2
    int i; // r5
   
    if (port != 0) {
        if ((port != 1) && (dbSwitchSysPadPort() == 0)) {
            return 0;
        }
        if ((port != pad_x) && (dbSwitchSysPadPort() != 0)) {
            return 0;
        }
        port = 1;
    }

    ret = 0;
    for (i = 0; i < 0x14; i++) {
        if ((key >> i) & 1) {         
            ret = clamp_max(ret, pad[port][i]);           
        }
    }
    
    return ret;
}

int shPadTrigger(int port /* r17 */, int key /* r16 */)  {
    
    int ret; // r2
    int i; // r5
    
    if (port != 0) {
        if ((port != 1) && (dbSwitchSysPadPort() == 0)) {
            return 0;
        }
        if ((port != pad_x) && (dbSwitchSysPadPort() != 0)) {
            return 0;
        }
        port = 1;
    }
    ret = 0;
    for (i = 0; i < 0x14; i++) {
        if ((key >> i) & 1) {         
            if (pad_bak[port][i] == 0) {
                ret = clamp_max(ret, pad[port][i]);
            }           
        }
    }
    
    return ret;
}

int shPadRepeat(int port /* r17 */, int key /* r16 */) {

    int ret; // r2
    int i; // r5
    
    if (port != 0) {
        if ((port != 1) && (dbSwitchSysPadPort() == 0)) {
            return 0;
        }
        if ((port != pad_x) && (dbSwitchSysPadPort() != 0)) {
            return 0;
        }
        port = 1;
    }

    ret = 0;
    for (i = 0; i < 0x14; i++) {
        if ((key >> i) & 1) {
            if (key & repeat[port]) {
                ret = clamp_max(ret, pad[port][i]);
            }
        }
    }
    return ret;
}

static u_long kc2ga(u_long kconf_button) {

    u_long rem;
    u_long bit;
    u_long ret;

    ret = 0;
    for (bit = 1, rem = kconf_button; rem != 0; bit <<= 1, rem >>= 1) {
        switch (bit & kconf_button) {
            case 0x100:    ret |= 0x1;    break;
            case 0x200:    ret |= 0x2;    break;
            case 0x400:    ret |= 0x4;    break;
            case 0x800:    ret |= 0x8;    break;
            case 0x1000:   ret |= 0x10;   break;
            case 0x2000:   ret |= 0x20;   break;
            case 0x4000:   ret |= 0x40;   break;
            case 0x8000:   ret |= 0x80;   break;
            case 0x10000:  ret |= 0x100;  break;
            case 0x20000:  ret |= 0x200;  break;
            case 0x40000:  ret |= 0x400;  break;
            case 0x80000:  ret |= 0x800;  break;
            case 0x1:      ret |= 0x1000; break;
            case 0x2:      ret |= 0x2000; break;
            case 0x4:      ret |= 0x4000; break;
            case 0x8:      ret |= 0x8000; break;
        }
    }
    return ret;
}

void shPadSetGameKeyAssign(void) {
    struct shGameKeyAssign assign; 
    shGameKeyGetAssign(&assign);


    
    assign.LIGHT = kc2ga(key_config.light);
    
    assign.ITEM = kc2ga(key_config.item);
    assign.MAP = kc2ga(key_config.map);
    
    assign.DECIDE = kc2ga(key_config.enter);
    assign.CANCEL = kc2ga(key_config.cancel);
    
    assign.SKIP = kc2ga(key_config.skip);
    assign.PAUSE = kc2ga(key_config.pause);
    
    key_config.attack = assign.ACTION = kc2ga(key_config.action);
    
    assign.DASH = kc2ga(key_config.dash);
    
    assign.LSLIDE = kc2ga(key_config.left_move);
    assign.RSLIDE = kc2ga(key_config.right_move);
    
    assign.READY = kc2ga(key_config.ready);
    assign.VIEW = kc2ga(key_config.search_view);
    
    shGameKeySetAssign(&assign);
}
