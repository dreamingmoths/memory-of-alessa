#include "sh2_common.h"
#include "SH2_common/sh2dt.h"

#include "Chacter/lake_wave.h"
#include "Chacter/character.h"

// @note found in a string
#define WAVE_NUM 20

// not found in a string
#define WAVE_TIME_SCALE 4.0f

const static Vector4 base_point = { -100.0f, 0.0f, -120.0f, 1.0f }; // size: 0x10, address: 0x39A680

static int rand_seed; // size: 0x4, address: 0x1202720
shLakeWaveInfo wave[20]; // size: 0x190, address: 0x1202590
static int newest_wave; // size: 0x4, address: 0x1202580

#line 98
void mizTestLakeWaveInit(void) {
    int i1; // r3

    for (i1 = 0; i1 < WAVE_NUM; i1++) {


        
        wave[i1].timer = WAVE_TIME_SCALE * i1;


        
        wave[i1].distance[0] = 3.0f * wave[i1].timer;



        wave[i1].distance[1] = 3.0f + (0.03f * wave[i1].timer);




        
        wave[i1].energy = 0.5f - (0.015f * wave[i1].timer);
        
        wave[i1].prev = i1 + 1;
        wave[i1].next = i1 - 1;
    }
    wave->next = WAVE_NUM - 1;
    wave[WAVE_NUM - 1].prev = 0;
    newest_wave = 0;
    rand_seed = 0;


    
}

#line 140
shLakeWaveInfo* mizTestLakeWaveMain(SubCharacter* scp) {
    int i1, prev; // r2 @note only `i1` was found in the symbols
    float pos_x; // r20
    float pos_z; // r21
    float angle; // r29+0x80
    float distance; // r29+0x80
    ASSERT(newest_wave >= 0 && newest_wave < WAVE_NUM);


    
    for (i1 = 0; i1 < WAVE_NUM; i1++) {
        wave[i1].timer += shGetDT();


        
        
        wave[i1].distance[0] = 3.0f * wave[i1].timer;
        wave[i1].distance[1] = 3.0f + (0.03f * wave[i1].timer);
        wave[i1].energy -= 0.015f * shGetDT();
        if (wave[i1].distance[0] >= 240.0f) {


            
            newest_wave = i1;
            wave[i1].distance[0] = 0.0f;
            wave[i1].distance[1] = 3.0f;
            wave[i1].timer = 0.0f;
            wave[i1].energy = 0.5f + (0.25f * sinf((PI * rand_seed) / 180.0));
        }
    }





    
    ASSERT(newest_wave >= 0 && newest_wave < WAVE_NUM);



    
    pos_x = (scp->pos.x / 500.0f) - base_point.x;
    pos_z = (scp->pos.z / 500.0f) - base_point.z;
    
    distance = sqrtf(pos_x * pos_x + pos_z * pos_z);



    
    i1 = newest_wave;
    ASSERT(newest_wave >= 0 && newest_wave < WAVE_NUM);
    while ((prev = wave[i1].prev) != newest_wave) {
        if (((wave[i1].distance[0] - wave[i1].distance[1]) < distance) && (distance <= (wave[i1].distance[0] + wave[i1].distance[1]))) {





            
            angle = PI * (fabsf(wave[i1].distance[0] - distance) / wave[i1].distance[1]);

            
            wave[i1].distance[0] = wave[i1].energy + cosf(angle) * wave[i1].energy;
            
            wave[i1].distance[1] = atan2f(pos_x, pos_z);

            
            
            rand_seed++;
            ASSERT(newest_wave >= 0 && newest_wave < WAVE_NUM);
            return &wave[i1];
        }

        i1 = prev;
        ASSERT(i1 >= 0 && i1 < WAVE_NUM);
    }

    ASSERT(newest_wave >= 0 && newest_wave < WAVE_NUM);

    return 0;
}
