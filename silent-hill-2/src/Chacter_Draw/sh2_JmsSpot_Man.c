#include "sh2_common.h"

#include "Chacter_Draw/sh2_JmsSpot_Man.h"

#include "Event/event.h"

#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_blockman.h"
#include "GFW/sh2_shadow_filters.h"

static float sh2gfw_Get_MaxDarkScaleFactor(void);
static int sh2gfw_TrueOff_JmsSPOT(void);
static void Flicker_Jms_Spot(void);
static void Calculate_Jms_Spot(void);
static int Light_Spot_OnOffCheck2(void);

/* from sh_vu0.h */
static void _shAddVector(float* v0, float* v1, float* v2);
static void _shScaleVector(float* v0, float* v1, float s);
static void _shNormalize(float* v0, float* v1);
static void _shOuterProduct(float* v0, float* v1, float* v2);
static float _shInnerProduct(float* v0, float* v1);

UNMIGRATED(James_SpotLight_Man JmsSpotMan);
UNMIGRATED(/* static */ DynamicLight DynamicLW);
UNMIGRATED(/* static */ sceVu0FVECTOR colvec); // size: 0x10, address: 0x37B560
UNMIGRATED(/* static */ sceVu0FVECTOR colref); // size: 0x10, address: 0x37B570

#line 92
void sh2gfw_ALLInit_SpotMan(void) {
    JmsSpotMan.GunFlg = 0;
    JmsSpotMan.Spot_Light_OnOff = 0;
    JmsSpotMan.MicroCodeMode = 0;
    JmsSpotMan.MicroChange = 0;
    
    JmsSpotMan.SpotTime = 0;
    JmsSpotMan.MaxTime = 60;
    JmsSpotMan.MinTime = 1;
    JmsSpotMan.SDt = 0;
    
    JmsSpotMan.DarkTrimMax = 450;
    JmsSpotMan.DarkDt = 0;
    JmsSpotMan.NowDarkParm = 0;
    
    
    JmsSpotMan.FlickerRatio = 3;
    JmsSpotMan.FlickerTime = 0;
    JmsSpotMan.FlickerMaxTime = 100;
    JmsSpotMan.FlickerFlg = 0;
    
    JmsSpotMan.Gun_Refrection = 0.0f;
    JmsSpotMan.MaxIntensity = 7.0f;
    JmsSpotMan.MinIntensity = 0.001f;
    JmsSpotMan.NowIntensity = 0.0f;
    JmsSpotMan.MaxAlpha = 1500.0f;
    JmsSpotMan.MinAlpha = 0.001f;
    JmsSpotMan.NowAlpha = 0.0f;
    JmsSpotMan.IntensityFactor = 1.0f;
    JmsSpotMan.DarkFactor = 1.0f;

}

#line 133
void sh2gfw_Propagate_JmsGunLight(void) {
    if (JmsSpotMan.GunFlg == 0) {
        
        if (JmsSpotMan.Gun_Refrection > 0.15f) {
            JmsSpotMan.Gun_Refrection -= 0.15f;            
        } else {
            JmsSpotMan.Gun_Refrection = 0.0f;
        }
        
    } else {
        
        JmsSpotMan.GunFlg = 0;
    } 
}

#line 149
void sh2gfw_Set_JmsGunLight(void) {
    JmsSpotMan.Gun_Refrection = 0.75f;
    JmsSpotMan.GunFlg = 1;
}


#line 156
float sh2gfw_Get_JmsGunLight(void) {
    if (JmsSpotMan.GunFlg) {
        return 0.075f;
    }
    return 0.075f + JmsSpotMan.Gun_Refrection;
}

#line 167
float sh2gfw_Get_GunLight(void) {
    if (JmsSpotMan.GunFlg) {
        return 0.0f;
    }
    return JmsSpotMan.Gun_Refrection;

}

#line 195
void sh2gfw_Clear_MicroChange(void) {
    JmsSpotMan.MicroChange = 0;
}
void sh2gfw_Set_MicroChange(void) {
    JmsSpotMan.MicroChange++;
}
void sh2gfw_Change_MicroFLGS(void) {
    if (JmsSpotMan.MicroChange) JmsSpotMan.MicroCodeMode ^= 1;   
}

#line 206
int sh2gfw_Check_MicroCode(void) {
    return JmsSpotMan.MicroCodeMode;
}

#line 210
void sh2gfw_Set_MicroCode(int xx) {
    JmsSpotMan.MicroCodeMode = xx - 1;
}

#line 221
float sh2gfw_Get_DarkTrimFactor(void) {
    return JmsSpotMan.DarkFactor;

}

#line 229
static float sh2gfw_Get_MaxDarkScaleFactor(void) {
    int* mp;

    
    
    
    
    if (!GET_ITEM_FLAG(15)) {
     
        return 1.0f;
    }
    
    
    mp = Get_NowMapId();
    switch (*mp) {
        case 0xA003D:
        case 0xA007D:
        case 0xA0091:
        case 0xA00E6:
            return 0.0f;
    }
    
    
    
    return 0.3f;




}



#line 263
int sh2gfw_Check_JmsSpotOnOff(void) {
    return JmsSpotMan.Spot_Light_OnOff;
}
#line 267
void sh2gfw_On_JmsSPOT(void) {
    int slot;


    
    
    
    if (sh2gfw_Get_NightOrDay()) {   
        if (sh2gde_CheckSpot_JmsOrBG()) {
            
            
            
            
            
            for (slot = 0; slot < 4; slot++) {
                if (b_man[slot].pB_H) {
                    
                    kari_sh2gfw_vu_change(&b_man[slot], 2);
                }
            
            
            
            }
            
            sh2gfw_Set_MicroCode(2);
            
            SetLightMode(2);
            
            Set_DrawEnvData(0, 1);
            JmsSpotMan.Spot_Light_OnOff = 1;
            
            
            
            JmsSpotMan.SDt = 2;
            JmsSpotMan.MaxTime = 60;
        }
    }




}

#line 316
static signed int sh2gfw_TrueOff_JmsSPOT() {
    int slot;
    
    
    if (sh2gfw_Get_NightOrDay()) {
        if (sh2gde_CheckSpot_JmsOrBG()) {
            
            
            if (sh2gfw_Check_DemoSpotLight()) {
                                
                for (slot = 0; slot < 4; slot++) {
                    if (b_man[slot].pB_H) {
                        
                        kari_sh2gfw_vu_change(&b_man[slot], 2);
                    }
                
                
                
                }
                sh2gfw_Set_MicroCode(2);
            
            } else {
                for (slot = 0; slot < 4; slot++) {
                    if (b_man[slot].pB_H) {
                        
                        kari_sh2gfw_vu_change(&b_man[slot], 1);
                    
                    
                    
                    }      
                }
                sh2gfw_Set_MicroCode(1);
            }
            Env_ctl.SpotL0.color.fl32[0] = Env_ctl.SpotL0.color.fl32[1] = Env_ctl.SpotL0.color.fl32[2] = 0.001f;
            
            
            Env_ctl.SpotL0.color.fl32[3] = 1500.0f;
            
            JmsSpotMan.Spot_Light_OnOff = 0;
            JmsSpotMan.DarkDt = 1;
            
            
            sh2gfw_Set_ShadowColorScaleFactor(0.0f);
        }
    }
}

#line 365
void sh2gfw_Off_JmsSPOT(void) {
    
    if (sh2gfw_Get_NightOrDay() == 0) return;
    if (!sh2gde_CheckSpot_JmsOrBG()) return;
    JmsSpotMan.SpotTime = JmsSpotMan.MaxTime;
    JmsSpotMan.SDt = -10;
}

#line 378
void sh2gfw_ForceOff_JmsSPOT(void) {
    
    if (sh2gfw_Get_NightOrDay()) {
        if (sh2gde_CheckSpot_JmsOrBG()) {
            
            JmsSpotMan.SpotTime = 0;
            
            JmsSpotMan.SDt = -1;
            sh2gfw_TrueOff_JmsSPOT();
            
            
            
            
            JmsSpotMan.DarkDt = 0;
            JmsSpotMan.SDt = 0;
        
        }
    }
}

#line 408
void sh2gfw_ForceOn_JmsSPOT(void) {
    
    if (sh2gfw_Get_NightOrDay()) {
        if (sh2gde_CheckSpot_JmsOrBG()) {        
            
            sh2gfw_On_JmsSPOT();
            JmsSpotMan.SpotTime = JmsSpotMan.MaxTime;
            
            
            sh2gfw_Set_ShadowColorScaleFactor(1.0f);
        }   
    }
}

#line 455
static float LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

#line 465
static void Flicker_Jms_Spot(void) {
    JmsSpotMan.FlickerTime += 1;
    if (JmsSpotMan.FlickerTime >= JmsSpotMan.FlickerMaxTime) {
        
        JmsSpotMan.FlickerTime = 0;
        if (JmsSpotMan.FlickerFlg) {
        
            sh2gfw_ForceOn_JmsSPOT();
        } else {
            
            sh2gfw_ForceOff_JmsSPOT();
        }
    } else {
        u_int ira = 0x19660D;
        u_int irc = 0x3C6EF35F;
        u_int isd;
        /*
        Numerical Recipes ranqd1, Chapter 7.1, §An Even Quicker Generator, Eq. 7.1.6 parameters
        https://library.sciencemadness.org/lanl1_a/lib-www/numerica/f7-1.pdf
        https://en.wikipedia.org/wiki/Linear_congruential_generator
        */
        #line 486
        isd = Env_ctl.random_seeds.ui32[0];
        
        isd = (isd * ira) + irc;
        Env_ctl.random_seeds.ui32[0] = isd;
        
        #line 497
        JmsSpotMan.IntensityFactor = isd / 4294967296.0f;
        JmsSpotMan.NowIntensity = JmsSpotMan.MaxIntensity - ((float) JmsSpotMan.FlickerRatio * JmsSpotMan.IntensityFactor);
    }
    
    #line 504
    Env_ctl.SpotL0.color.fl32[0] =  Env_ctl.SpotL0.color.fl32[1] = Env_ctl.SpotL0.color.fl32[2] = JmsSpotMan.NowIntensity;
    
    #line 509
    sh2gfw_Set_ShadowColorScaleFactor(JmsSpotMan.IntensityFactor);


}

static inline float linearMax() { return 1.0f; }

#line 514
static void Calculate_Jms_Spot(void) {
    float factor; // r29+0x10

    #line 522 
    JmsSpotMan.SpotTime += JmsSpotMan.SDt;
    
    if (JmsSpotMan.SDt > 0 && JmsSpotMan.SpotTime >= JmsSpotMan.MaxTime) {
        JmsSpotMan.SpotTime = JmsSpotMan.MaxTime;
        JmsSpotMan.SDt = 0;
    } else if (JmsSpotMan.SDt < 0 && JmsSpotMan.SpotTime <= JmsSpotMan.MinTime) {
        JmsSpotMan.SpotTime = JmsSpotMan.MinTime;
        JmsSpotMan.SDt = 0;
    }
    
    {
        float m = linearMax();
        JmsSpotMan.NowIntensity = factor = LinearTrim(m, 0.0f, JmsSpotMan.MaxTime, JmsSpotMan.MinTime, JmsSpotMan.SpotTime); // @hack holy candle!!
    }

    #line 553
    Env_ctl.SpotL0.color.fl32[0] = Env_ctl.SpotL0.color.fl32[1] = Env_ctl.SpotL0.color.fl32[2] = JmsSpotMan.MaxIntensity * factor;
    
    #line 558
    JmsSpotMan.IntensityFactor = factor;
    
    sh2gfw_Set_ShadowColorScaleFactor(factor);
    if ((JmsSpotMan.NowIntensity <= 0.2) && (!JmsSpotMan.SDt)) {
        sh2gfw_TrueOff_JmsSPOT();
    }


    #line 567
}

#line 581
static int Light_Spot_OnOffCheck2(void) {
    return GET_ITEM_FLAG(15) != 0;



}

#ifdef HOLY_CANDLE
#line 590
void Programed_Light_Set(void) {
    /* r20      */ float inner;
    /* r29+0x70 */ float factor; /* r20      */ float MaxFactor; // @note factor should probably be used here
    /* r29+0x40 */ sceVu0FVECTOR tmp; /* r29+0x50 */ sceVu0FVECTOR plane; /* r29+0x60 */ sceVu0FVECTOR aimdir;
    /* r16      */ int ipara; /* r17      */ int slot;

    ipara = sh2gfw_Check_ParallelDemoLight(1);
    
    sceVu0CopyVector(DynamicLW.BeforeCamDir, DynamicLW.NowCamDir);
    sceVu0CopyVector(DynamicLW.BeforeDir, DynamicLW.NowDir);
    
    sh2gde_Get_EyeDir(DynamicLW.NowCamDir);
    
    inner = _shInnerProduct(DynamicLW.NowCamDir, DynamicLW.BeforeDir);
    
    _shOuterProduct(plane, DynamicLW.NowCamDir, DynamicLW.BeforeDir);
    _shNormalize(plane, plane);
    _shOuterProduct(aimdir, DynamicLW.BeforeDir, plane);
    
    inner = 0.1f / (2.0f + inner);
    if (inner < 0.0333f) inner = 0.0f;
    _shScaleVector(aimdir, aimdir, inner);
    _shAddVector(tmp, aimdir, DynamicLW.BeforeDir);
    _shNormalize(DynamicLW.NowDir, tmp);
    
    #line 619
    if (!sh2gfw_Check_DemoRefrectionHightLight() && !DramaDemoNumber()) {
    
        if (sh2gfw_Get_NightOrDay()) {
        
            sh2gfw_Set_DemoRefrectionHighLight(DynamicLW.NowDir, colref);
        } else {
        
            sceVu0ScaleVector(tmp, colref, 0.7f);
            sh2gfw_Set_DemoRefrectionHighLight(DynamicLW.NowDir, tmp);
        }
    }
    
    
    
    if (!sh2gde_CheckSpot_JmsOrBG()) {
        if (!sh2gfw_Check_JmsSpotOnOff()) {
            
            
            
            
            
            
            if (sh2gfw_Get_NightOrDay()) {
            
                for (slot = 0; slot < 4; slot++) {
                    if (b_man[slot].pB_H) {
                        
                        kari_sh2gfw_vu_change(&(&b_man)[slot], 2U);
                    }
                    
                    
                
                }
                
                sh2gfw_Set_MicroCode(2);
                
                SetLightMode(2);
                
                Set_DrawEnvData(0, 1);
                JmsSpotMan.Spot_Light_OnOff = 1;
                JmsSpotMan.SDt = 2;
                JmsSpotMan.MaxTime = 60;
                JmsSpotMan.SpotTime = JmsSpotMan.MaxTime;
            }
        }
    }

    else if (sh2gfw_Check_JmsSpotOnOff() == 1 && Light_Spot_OnOffCheck2() == 0) {
    
        JmsSpotMan.Spot_Light_OnOff = 0;
        sh2gfw_ForceOff_JmsSPOT();
    }
    
    
    
    
    if (JmsSpotMan.FlickerTime) {
        Flicker_Jms_Spot();
    } else if (JmsSpotMan.SDt) {
        Calculate_Jms_Spot();
    }
    
    MaxFactor = sh2gfw_Get_MaxDarkScaleFactor();
    
    
    
    if (MaxFactor > 0.0f && sh2gfw_Get_NightOrDay()) {
    
        if (sh2gfw_Check_JmsSpotOnOff()) {
        
            if (JmsSpotMan.SDt > 0) {
            
                MaxFactor = JmsSpotMan.DarkFactor - JmsSpotMan.IntensityFactor;
                if (MaxFactor >= 0.001f) {
                    sceVu0ScaleVector(tmp, colvec, MaxFactor);
                    JmsSpotMan.DarkFactor = MaxFactor;
                
                    if (ipara == 0) {
                        sh2gfw_Set_PallarelLight(DynamicLW.NowDir, tmp, 1);
                    }
                }
                
                JmsSpotMan.NowDarkParm = 0;
            }
        
        
        
        } else {
        
            
            if (ipara == 0) {
                if ((JmsSpotMan.DarkDt) && (JmsSpotMan.DarkTrimMax >= JmsSpotMan.NowDarkParm)) {
            
                    JmsSpotMan.NowDarkParm += JmsSpotMan.DarkDt;
                    
                    MaxFactor = LinearTrim(MaxFactor, 0.0f, JmsSpotMan.DarkTrimMax, 0.0f, JmsSpotMan.NowDarkParm);
                } else {
                    JmsSpotMan.DarkDt = 0;
                    JmsSpotMan.NowDarkParm = 0;
                }
                
                sceVu0ScaleVector(tmp, colvec, MaxFactor);
                JmsSpotMan.DarkFactor = MaxFactor;
                sh2gfw_Set_PallarelLight(DynamicLW.NowDir, tmp, 1);
                sh2gfw_Set_ShadowColorScaleFactor(MaxFactor);
            } else {
                sh2gfw_Set_ShadowColorScaleFactor(1.0f);
            }
        }
    }



}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2_JmsSpot_Man", Programed_Light_Set)
#endif

#line 1260
static void _shAddVector(float* v0, float* v1, float* v2) {
    asm("
        lqc2 $vf4, 0(%1)\n
        lqc2 $vf5, 0(%2)\n
        vadd $vf4, $vf4, $vf5\n
        sqc2 $vf4, 0(%0)\n"
    : : "r"(v0), "r"(v1), "r"(v2) : "memory");
}

#line 1357
static void _shScaleVector(float* v0, float* v1, float s) {
    asm("
        mfc1 $t7, %2\n
        lqc2 $vf4, 0(%1)\n
        qmtc2 $t7, $vf5\n
        vmulx $vf4, $vf4, $vf5x\n
        sqc2 $vf4, 0(%0)\n"
    : : "r"(v0), "r"(v1), "f"(s) : "t7", "memory");
}

#line 1240
static void _shNormalize(float* v0, float* v1) {
    asm("
        lqc2 $vf4, 0(%1)\n
        vmul.xyz $vf5, $vf4, $vf4\n
        vaddy.x $vf5, $vf5, $vf5y\n
        vaddz.x $vf5, $vf5, $vf5z\n
        vrsqrt Q, $vf0w, $vf5x\n
        vwaitq\n
        vmulq.xyz $vf4, $vf4, Q\n
        sqc2 $vf4, 0(%0)\n"
    : : "r"(v0), "r"(v1) : "memory");
}

#line 1117
static void _shOuterProduct(float* v0, float* v1, float* v2) {
    asm("
        lqc2 $vf5, 0(%1)\n
        lqc2 $vf6, 0(%2)\n
        vsub.w $vf4, $vf0, $vf0\n
        vopmula.xyz $acc, $vf5, $vf6\n
        vopmsub.xyz $vf4, $vf6, $vf5\n
        sqc2 $vf4, 0(%0)\n"
    : : "r"(v0), "r"(v1), "r"(v2) : "memory");
}

#line 1134
static float _shInnerProduct(float* v0, float* v1) {
    float ret = 0;
    asm("
        lwc1  $f0, 0(%1)\n
        lwc1  $f8, 0(%2)\n
        lwc1  $f9, 4(%1)\n
        lwc1  $f10, 4(%2)\n
        mula.s $f0, $f8\n
        lwc1  $f0, 8(%1)\n
        lwc1  $f8, 8(%2)\n
        madda.s $f9, $f10\n
        madd.s %0, $f0, $f8\n"
    : "=f"(ret) : "r"(v0), "r"(v1) : "memory");
    return ret;
}
