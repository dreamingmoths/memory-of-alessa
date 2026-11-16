#include "sh2_common.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_blockman.h"
#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_2d_filters.h"

#include "Chacter_Draw/sh2gfw_model_light.h"

typedef struct LP {
    // total size: 0x40
    sceVu0FVECTOR pldir; // offset 0x0, size 0x10
    sceVu0FVECTOR uga; // offset 0x10, size 0x10
    sceVu0FVECTOR poi; // offset 0x20, size 0x10
    sceVu0FVECTOR col; // offset 0x30, size 0x10
} LP;

int sprintf(char *str, const char* format, ...);


Q_WORDDATA noise_clut = {24, 24, 24, 16};

INCLUDE_ASM("asm/nonmatchings/GFW/gfw_test/kari_probe_draw", DBG_data_loadGS);

#line 487
void sh2gfw_Vu0NormalLightPhongMatrix(sceVu0FMATRIX m /* r19 */, sceVu0FVECTOR l0 /* r2 */, sceVu0FVECTOR l1 /* r18 */, sceVu0FVECTOR l2 /* r17 */, sceVu0FVECTOR eyedir /* r16 */) {
    
    
    sceVu0Normalize(m[0], l0);
    sceVu0Normalize(m[1], l1);
    sceVu0Normalize(m[2], l2);
    sceVu0Normalize(m[3], eyedir);
    
    
    sceVu0TransposeMatrix(m, m);

}

#line 946
void kari_DBG_print_junbi(u_long* res /* r18 */) {
    char string_buf[128]; // r29+0x90
    float svt[4]; // r29+0x110
    
    u_int iy = 56; // r16
    int padport = shPadGetPort(); // r17

    if (Env_ctl.stat_ctl_2.uc8[0] - 4) {
        
        if (padport != 2 && padport != 3) {
            
            sprintf(string_buf, "pad_x=%d lines=%d ", padport, *res);
            shDBG_print_string(string_buf, 8, iy - 16);
        }
        else
        {
            int kx; // r17
            int ky; // r18
            int ix[8]; // r29+0x120
            int iyy; // r19
            int iz; // r20
            int ih; // r4
            
            
            sh2gde_Get_EyeDir(svt);
            sprintf(string_buf, "padx=%d %d %f %f %f",
                    padport,
                    *res,
                    svt[0],
                    svt[1],
                    svt[2]);
            shDBG_print_string(string_buf, 8, iy - 16);
    
            
            sprintf(string_buf, "X=%f Y=%f Z=%f", Env_ctl.camera_p[0], Env_ctl.camera_p[1], Env_ctl.camera_p[2]);
            shDBG_print_string(string_buf, 8, iy - 8);
            
            vwGetViewPosition(svt);

            #line 1005
            switch (Env_ctl.stat_ctl_1.uc8[0]) {
                case 1:
                    
                    sprintf(string_buf, "X=%f Y=%f Z=%f", Env_ctl.camera_parms[0], Env_ctl.camera_parms[3], Env_ctl.camera_parms[2]);
                    shDBG_print_string(string_buf, 8, iy);
                    iy += 8;
    
    
                    
                    for (ky = 0; ky < 2; ky++) {
                        for (kx = 0; kx < 2; kx++) {
                            
                            const char* sbb[] = {"@", "-", "O"};
                            iyy = iy + 72;
                            
                            for(iz = 0; iz < 8; iz++) {
                                for(ih = 0; ih < 8; ih++) {
                                    
                                    ix[ih] = b_man[kx + (ky * 2)].tileViewClipInfo[iz][ih] >> 4;
                                    
                                    if (iz * 8 + ih == b_man[kx + (ky * 2)].view_tile) ix[ih] = 0;
                                    
                                }
                                sprintf(string_buf,
                                        "%1s%1s%1s%1s%1s%1s%1s%1s",
                                        sbb[ix[0]], sbb[ix[1]], sbb[ix[2]], sbb[ix[3]],
                                        sbb[ix[4]], sbb[ix[5]], sbb[ix[6]], sbb[ix[7]]);
                                shDBG_print_string(string_buf, (kx * 80) + 8, (iyy + 80) - (ky * 160));
                                
                                iyy-=8;
                            }
                            
                        }
                        iy+=80;
                    }
                case 5:
                    break;
                case 6:
                    #line 1067
                    sprintf(string_buf,
                            "%d %f %f %f",
                            Env_ctl.stat_ctl_1.uc8[0],
                            Env_ctl.camera_parms2[2],
                            Env_ctl.camera_parms2[0],
                            Env_ctl.camera_parms2[1]);
                    
                    shDBG_print_string(string_buf, 8, iy);
                    iy += 8;
                    break;
            }
            
            
            
            switch (Env_ctl.stat_ctl_2.uc8[0]) {
                    
                    
                case 0:
                    sprintf(string_buf,
                            "%d %7.2f %7.2f %f %7.3f %7.3f",
                            Env_ctl.stat_ctl_2.uc8[0],
                            Env_ctl.SpotL0.decayparm.fl32[0],
                            Env_ctl.SpotL0.decayparm.fl32[2],
                            Env_ctl.SpotL0.decayparm.fl32[3],
                            Env_ctl.SpotL0.color.fl32[2],
                            Env_ctl.SpotL0.color.fl32[3]);
                    
                    shDBG_print_string(string_buf, 8, iy);
                    
                    
                    break;
                case 1:
    
                    sprintf(string_buf,
                            "%d %f %f %f %f",
                            Env_ctl.stat_ctl_2.uc8[0],
                            Env_ctl.fogparm.fl32[0],
                            Env_ctl.fogparm.fl32[1],
                            Env_ctl.fogparm.fl32[2],
                            Env_ctl.fogparm.fl32[3]);
                    
                    shDBG_print_string(string_buf, 8, iy);
                    break;
                case 2:
                    
                    
                    sprintf(string_buf,
                            "CPF m%d %02X %02X %02X %02X %2d %2d",
                            Env_ctl.CopyFilterColor.ui32[1],
                            Env_ctl.CopyFilterColor.uc8[0],
                            Env_ctl.CopyFilterColor.uc8[1],
                            Env_ctl.CopyFilterColor.uc8[2],
                            Env_ctl.CopyFilterColor.uc8[3],
                            Env_ctl.CopyFilterColor.sc8[6],
                            Env_ctl.CopyFilterColor.sc8[7]);
                    
                    shDBG_print_string(string_buf, 8, iy);
                    
                    break;
                    
                case 3:
                    sprintf(string_buf,
                            "%d %f %f %d %d",
                            Env_ctl.stat_ctl_2.uc8[0],
                            Env_ctl.ambient[0],
                            Env_ctl.ambient[3],
                            Env_ctl.fogcolor.uc8[0],
                            Env_ctl.clearcolor.uc8[0]);
                    
                    
                    shDBG_print_string(string_buf, 8, iy);
                    break;
                
                case 5:
                    sprintf(string_buf,
                            "NS %d %d %d %d %d",
                            Env_ctl.NoiseCondition.uc8[0],
                            Env_ctl.NoiseCondition.uc8[1],
                            Env_ctl.NoiseCondition.uc8[2],
                            Env_ctl.NoiseCondition.uc8[3],
                            Env_ctl.NoiseCondition.uc8[5]);
                    
                    shDBG_print_string(string_buf, 8, iy);
                    
                    return;
                case 6:
                    {
                    int k1 = Env_ctl.stat_ctl_2.uc8[6];
                    LP * lp;
        
                    
                    
                    
                    
    
                    lp = (float (*)[4])Env_ctl.p_light0 + (k1);
                    
                    sprintf(string_buf, "P%d %f %f %f",
                            k1,
                            lp->pldir[0],
                            lp->pldir[1],
                            lp->pldir[2],
                            lp->col[0]);
                    shDBG_print_string(string_buf, 8, iy);
                    sprintf(string_buf, "C%d %f %f %f",
                            k1,
                            lp->col[0], lp->col[1], lp->col[2]);
                    shDBG_print_string(string_buf, 8, iy + 8);
                    }
                    return;
                case 7:
                    {            
                    DrawEnvData* ded; // r2
                    PointLightData* pld; // r2
                    SpotLightData* sld; // r17
                    int realsnum, snum;
    
                    ded = Get_NowDrawEnvData();
                    snum = ded->FakeSpotNum;
                    realsnum = ded->spotLNum;
                    if (realsnum > 0) snum += realsnum;
                    else realsnum = 0;
                    
                    if (snum > 0) {
                        
                        if (snum < Env_ctl.stat_ctl_2.uc8[6]) Env_ctl.stat_ctl_2.uc8[6] = 0;
                        pld = ded->Ld_0;
                        pld += ded->pointLNum; // temp_s1_7 = ded + 0xB0 + (ded->unk7 * 0x30);
                        sld = pld; // still matches the DWARF because no code is emitted for this line
                        
                        if (Env_ctl.stat_ctl_2.uc8[6] >= ded->spotLNum) {
                            
                            
                            pld = sld + realsnum;
                            
                            sld = pld + ded->FakePointNum;
    
                            
                            sld += Env_ctl.stat_ctl_2.uc8[6] - realsnum;
                        } else {
                            sld += Env_ctl.stat_ctl_2.uc8[6];
                        }
                        
                        
                        sprintf(string_buf, "SL%d %f %f %f", Env_ctl.stat_ctl_2.uc8[6],
                                sld->Col[0],sld->Col[1],sld->Col[2]);
                        shDBG_print_string(string_buf, 8, iy);
                        
                        sprintf(string_buf, "?1", Env_ctl.stat_ctl_2.uc8[6],
                                sld->DecayParm[2],0.02f * sld->DecayParm[2]);
                        shDBG_print_string(string_buf, 8, iy + 8);
                        
                        sprintf(string_buf, "?2", Env_ctl.stat_ctl_2.uc8[6],
                               sld->DecayParm[3],0.02f * sld->DecayParm[3]);
                        shDBG_print_string(string_buf, 8, iy + 16);
                        
                        sprintf(string_buf, "?3", Env_ctl.stat_ctl_2.uc8[6],
                                sld->DecayParm[0]);
                        shDBG_print_string(string_buf, 8, iy + 24);
                        
                        sprintf(string_buf, "Pos = %f %f %f",
                                sld->Pos[0], sld->Pos[1], sld->Pos[2]);
                        shDBG_print_string(string_buf, 8, iy + 32);
                        
                        sprintf(string_buf, "Dir = %f %f %f",
                                sld->Dir[0], sld->Dir[1],sld->Dir[2]);
                        shDBG_print_string(string_buf, 8, iy + 40);
                    }
                    
                    }
                    break;
                case 8:
                    
                    sprintf(string_buf, "BC %f %f %f",
                            Env_ctl.BaseVertexColor[0],
                            Env_ctl.BaseVertexColor[1],
                            Env_ctl.BaseVertexColor[2]);
                    
                    shDBG_print_string(string_buf,
                                       8, iy + 2);
                    
                    sprintf(string_buf, "BA %f %f %f",
                            Env_ctl.BaseAmbient[0],
                            Env_ctl.BaseAmbient[1],
                            Env_ctl.BaseAmbient[2]);
                    
                    shDBG_print_string(string_buf,
                                       8, iy + 12);
                    
                    sprintf(string_buf, "VA %f %f %f",
                            Env_ctl.VertexAmbient[0],
                            Env_ctl.VertexAmbient[1],
                            Env_ctl.VertexAmbient[2]);
                    
                    shDBG_print_string(string_buf,
                                       8, iy + 22);
                    
                    sprintf(string_buf, "AM %f %f %f",
                            Env_ctl.ambient[0],
                            Env_ctl.ambient[1],
                            Env_ctl.ambient[2]);
                    
                    shDBG_print_string(string_buf,
                                       8, iy + 32);
                    return;
                case 9:
                    sprintf(string_buf, "FOG %f %f %f",
                            Env_ctl.MoveFogColor.ui32[0],
                            Env_ctl.MoveFogColor.ui32[1],
                            Env_ctl.MoveFogColor.ui32[2],
                            Env_ctl.MoveFogColor.ui32[3]);
                    
                    shDBG_print_string(string_buf, 8, iy);
                    return;
                case 10:
                    sprintf(string_buf, "Filter %d", sh2gfw_Get_FilterCommand());
                    shDBG_print_string(string_buf, 8, iy);
                    {
                    FilterParams* pfp;
                    pfp = sh2gfw_Get_FilterCommandParams();
    
                    switch (sh2gfw_Get_FilterCommand()) {
                    case 5:
                        sprintf(string_buf, "SF I=%d A=%d C=%d Shift=%d",
                                pfp->SoftIter, pfp->SoftAref,pfp->SoftCit,pfp->SoftShift);
                        shDBG_print_string(string_buf, 88, iy);
                        return;
                    case 8:
                    case 9:
                    case 10:
                        sprintf(string_buf, "?", pfp->DOF_ZDepth, pfp->KeyAlpha,pfp->TrimAlpha);
                        
                        shDBG_print_string(string_buf, 88, iy);
                        
                        sprintf(string_buf, "?", pfp->S1_iter, pfp->S1_alpha, pfp->S1_shift, pfp->S1_baseIX);
                        
                        shDBG_print_string(string_buf, 88, iy + 10);
                        
                        sprintf(string_buf, "S2IT=%d S2A=%d S2sh=%d S2ba=%d",pfp->S2_iter, pfp->S2_alpha, pfp->S2_shift, pfp->S2_baseIX);
                        
                        shDBG_print_string(string_buf, 88, iy + 20);
                        return;
                    case 6:
                    case 7:
                        
                        sprintf(string_buf, "SGD I=%d A=%d C=%d", pfp->SoftIter, pfp->SoftAref, pfp->SoftCit);
                        shDBG_print_string(string_buf, 88, iy);
                        sprintf(string_buf, "SGD Ix=%d Iy=%d Shift=%d", pfp->base_Ix, pfp->base_Ix, pfp->SoftShift);
                        
                        shDBG_print_string(string_buf, 88, iy + 8);
                        return;
                    case 0:
                    case 1:
                        
                        sprintf(string_buf, "%d %d",pfp->base_Ix - 4,pfp->base_Iy - 4);// pfp->unk0 - 4, pfp->unk2 - 4);
                        shDBG_print_string(string_buf, 88, iy);
                        sprintf(string_buf,
                                "%d %d %d %d",
                                pfp->TexTrimSX,
                                pfp->TexTrimSY,
                                pfp->TexTrimEX,
                                pfp->TexTrimEY);
                        shDBG_print_string(string_buf,
                                           88, iy + 8);
                        return;
                    case 2:
                        sprintf(string_buf, "%d %d BR=%d",
                                pfp->base_Ix - 4,pfp->base_Iy - 4, pfp->blurRatio);
                        shDBG_print_string(string_buf, 88, iy);
                        return;
                    default:
                        
                        
                        sprintf(string_buf, "%d %d BR=%d LA=%d GA=%d T=%d",
                                pfp->base_Ix - 4,
                                pfp->base_Iy - 4,
                                pfp->blurRatio,
                                pfp->LesserA+127,
                                pfp->GreaterA+224,
                                pfp->FO_timer);
                        shDBG_print_string(string_buf,
                                           88,
                                           iy);
    
                        
                        return;
                    }
                    }
                    break;
                case 11:
                    {
                    DrawEnvData* ded = Get_NowDrawEnvData(); // r2
                    
                    if (ded->pointLNum != 0) {
                        PointLightData* pld; // r2
                        pld = ded->Ld_0;
                        if (ded->spotLNum > 0) /* looks like a macro */ { SpotLightData* sld = pld; sld += ded->spotLNum; pld = sld;}
                        
                        pld = pld + Env_ctl.stat_ctl_2.uc8[5];
                        
                        
                        sprintf(string_buf, "PL%d %f %f %f", Env_ctl.stat_ctl_2.uc8[5],
                                pld->Col[0],pld->Col[1],pld->Col[2]);
                        shDBG_print_string(string_buf, 8, iy);
                        
                        sprintf(string_buf, "PL%d FallStart = %f %f ", Env_ctl.stat_ctl_2.uc8[5],
                                pld->DecayParm[0],0.02f*pld->DecayParm[0]);
                        shDBG_print_string(string_buf, 8, iy + 8);
                        
                        sprintf(string_buf, "PL%d FallEnd = %f %f ", Env_ctl.stat_ctl_2.uc8[5],
                                pld->DecayParm[1],0.02f*pld->DecayParm[1]);
                        shDBG_print_string(string_buf, 8, iy + 16);
                        
                        sprintf(string_buf, "Pos = %f %f %f",
                                pld->Pos[0],pld->Pos[1],pld->Pos[2]);
                        shDBG_print_string(string_buf, 8, iy + 24);
                    }
                    }
                    
                    break;
                
            }
        
        }
    
    }

}
