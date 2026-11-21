#include "sh2_common.h"
#include "Event/demoview.h"
#include "Chacter/m3_sc.h"
#include "sh2shd/sh2shd_structs.h"

static float get_demo_frame(void);

DROP_SHADOW_ENV default_drop_env = {
    /* .block = */ 1,
    /* .alphaMin = */ 0.0f,
    /* .alphaMax = */ 32.0f,
    /* .heightRevision = */ 0.0f,
    /* .color = */ 8,
};

SHADOW_ENV default_env_bg = {
    /* .block = */ 1,
    /* .clipKind = */ 0,
    /* .leng = */ 6000.0f,
};

SHADOW_ENV default_env_chr = {
    /* .block = */ 1,
    /* .clipKind = */ 0,
    /* .leng = */ 4000.0f,
};

SHADOW_ENV cb_env[] = {
    {
        /* .block = */ 30,
        /* .clipKind = */ 888,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 37,
        /* .clipKind = */ 888,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV cc_env[] = {
    {
        /* .block = */ 4,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 22,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 71,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV bw_env[] = {
    {
        /* .block = */ 1,
        /* .clipKind = */ 0,
        /* .leng = */ 3000.0f,
    },
    {
        /* .block = */ 5,
        /* .clipKind = */ 0,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 9,
        /* .clipKind = */ 0,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV ap_env[] = {
    {
        /* .block = */ 1,
        /* .clipKind = */ 0,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 30,
        /* .clipKind = */ 0,
        /* .leng = */ 3000.0f,
    },
    {
        /* .block = */ 104,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV hp_env[] = {
    {
        /* .block = */ 5,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 9,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 13,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 17,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 29,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 49,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 53,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 61,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 65,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 105,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 113,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 121,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 125,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 145,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 150,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 154,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 178,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 190,
        /* .clipKind = */ 0,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 202,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 206,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 210,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 214,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 222,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV ps_env[] = {
    {
        /* .block = */ 33,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 51,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 93,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 113,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 145,
        /* .clipKind = */ 0,
        /* .leng = */ 2500.0f,
    },
    {
        /* .block = */ 189,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV rr_env[] = {
    {
        /* .block = */ 5,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 9,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 21,
        /* .clipKind = */ 666,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 25,
        /* .clipKind = */ 999,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 29,
        /* .clipKind = */ 0,
        /* .leng = */ 8000.0f,
    },
    {
        /* .block = */ 37,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 51,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 67,
        /* .clipKind = */ 0,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 71,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    },
    {
        /* .block = */ 87,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    }
};

SHADOW_ENV ru_env[] = {
    {
        /* .block = */ 61,
        /* .clipKind = */ 999,
        /* .leng = */ 6000.0f,
    }
};

RODATA_PAD_TO(0x0039B850);

#define ENV_SIZE(_env) (sizeof(_env) / sizeof(SHADOW_ENV))

#line 412
void sh2shd_get_shadow_env_bg(SHADOW_ENV* env, SHADOW_OUTDOOR_HEAD* head) {
    int i;
    int flag;
    *env = default_env_bg;

    switch (head->kind) {
        case 2:
            for (i = 0; i < ENV_SIZE(cb_env); i++) {
                if (head->map_id == cb_env[i].block) {
                    *env = cb_env[i];
                    break;
                }
            }
            break;
        case 3:
            for (i = 0; i < ENV_SIZE(cc_env); i++) {
                if (head->map_id == cc_env[i].block) {
                    *env = cc_env[i];
                    break;
                }
            }
            break;
        case 7:
            for (i = 0; i < ENV_SIZE(bw_env); i++) {
                if (head->map_id == bw_env[i].block) {
                    *env = bw_env[i];
                    break;
                }
            }
            break;
        case 8:
            if (head->map_id == 1) {
                env->block     = 1;
                env->clip_kind = 999;
                env->leng      = 6000.0f;
            } else if (head->map_id == 5) {
                env->block     = 5;
                env->clip_kind = 0;
                env->leng      = 6000.0f;
            }
            break;
        case 9:
            for (i = 0; i < ENV_SIZE(ap_env); i++) {
                if (head->map_id == ap_env[i].block) {
                    *env = ap_env[i];
                    break;
                }
            }

            switch (head->map_id) {
                case 6:
                    env->clip_kind = 666;
                    break;
                case 42:
                    if (EventProgressCheck() < 5 && !sh2gfw_Check_JmsSpotOnOff()) {
                        env->clip_kind = 666;
                        break;
                    }
                    break;
            }
            break;
        case 10:
            for (i = 0; i < ENV_SIZE(hp_env); i++) {
                if (head->map_id == hp_env[i].block) {
                    *env = hp_env[i];
                    break;
                }
            }
            if (head->map_id == 150 && sh2jms.player->pos.z > -222800.0f) {
                env->clip_kind = 999;
                break;
            }
            break;
        case 11:
            for (i = 0; i < ENV_SIZE(ps_env); i++) {
                if (head->map_id == ps_env[i].block) {
                    *env = ps_env[i];
                    break;
                }
            }
            if (head->map_id == 145) {
                sceVu0FVECTOR cam_pos;
                vwGetViewPosition(cam_pos);
                if (cam_pos[1] < -2000.0f) {
                    env->clip_kind = 666;
                    break;
                }
            }
            break;
        case 12:
            for (i = 0; i < ENV_SIZE(rr_env); i++) {
                if (head->map_id == rr_env[i].block) {
                    *env = rr_env[i];
                    break;
                }
            }
            break;
        case 13:
            for (i = 0; i < ENV_SIZE(ru_env); i++) {
                if (head->map_id == ru_env[i].block) {
                    *env = ru_env[i];
                    break;
                }
            }
            break;
        case 0:
            break;
    }
}

void sh2shd_get_shadow_env_chr(SHADOW_ENV* env, SHADOW_CHAR_MAN* chr_man, int glb_coord, int map_id) {
    env->leng = 4000.0f;

    switch (glb_coord) {
        default:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 12:
        case 13:
            break;

        case 9:
            switch (map_id) {
                case 22:
                    env->clip_kind = 999;
                    env->leng      = 4000.0f;
                    break;
                case 30:
                    env->leng = 2000.0f;
                    break;
                case 42:
                    if (!sh2gfw_Check_JmsSpotOnOff() && chr_man->kind == ITEM_TVC_CHARA_KIND /* james dead body model */) {
                        env->clip_kind = 666;
                        break;
                    }
                    break;
                case 50:
                    if (!sh2gfw_Check_JmsSpotOnOff()) {
                        if (chr_man->scp->pos.z > 10550.00f &&
                            ((chr_man->scp->pos.x > -105000.0f && chr_man->scp->pos.x < -103100.0f) || (chr_man->scp->pos.x > -102600.0f && chr_man->scp->pos.x < -101700.0f))) {
                            env->clip_kind = 666;
                            break;
                        }
                    }
                    break;
                case 88:
                    env->leng      = 3000.0f;
                    env->clip_kind = 999;
                    break;
            }
            break;

        case 11:
            switch (map_id) {
                case 15:
                    env->clip_kind = 999;
                    break;
                case 109:
                    env->leng = 6000.0f;
                    break;
                case 145:
                    if (IS_PLAYER_KIND(chr_man->kind)) {
                        env->clip_kind = 999;
                    }
                    break;
            }
            break;
    }
}

#line 672
void sh2shd_get_demo_shadow_env_for_bg(SHADOW_ENV* env, int demo_no) {
    *env = default_env_bg;

    switch (demo_no) {
        case 0:
            break;

        case 9:
            env->clip_kind = 999;
            env->leng      = 8000.0f;
            break;

        case 11:
            env->clip_kind = 999;
            break;

        case 13:
            break;

        case 14:
            env->clip_kind = 666;
            break;

        case 15:
        case 19:
            break;

        case 25:
            env->clip_kind = 999;
            break;

        case 32:
            break;

        case 33:
        case 34:
            break;

        case 38:
            env->leng      = 2500.0f;
            env->clip_kind = 999;
            break;

        case 39:
            break;

        case 40:
            env->clip_kind = 999;
            break;

        case 43:
        case 44:
            break;

        case 46: {
            float env_demo_frame = get_demo_frame();
            if (env_demo_frame >= 563.0f && env_demo_frame <= 576.0f) {
                env->clip_kind = 0;
                break;
            }
            env->clip_kind = 999;
            break;
        }

        case 65:
            break;

        case 66: {
            float env_demo_frame = get_demo_frame();
            if (env_demo_frame >= 136.0f && env_demo_frame <= 192.0f) {
                env->clip_kind = 666;
                break;
            }
            break;
        }

        case 70:
            env->clip_kind = 999;
            break;

        case 75:
        case 80:
            break;
    }
}

#line 863
void sh2shd_get_demo_shadow_env_for_char(SHADOW_ENV* env, SHADOW_CHAR_MAN* man, int demo_no) {
    *env = default_env_chr;

    switch (demo_no) {
        case 0:
            break;
        case 9:
            env->clip_kind = 999;
            break;
        case 13:
            env->clip_kind = 999;
            break;
        case 14:
            if (get_demo_frame() > 394.0f && man->kind == EN_RED_CHARA_KIND) {
                env->clip_kind = 666;
            }
            env->clip_kind = 999;
            env->leng      = 6000.0f;
            break;
        case 75:
            break;
        case 15:
            break;
        case 19:
            env->leng = 4000.0f;
            break;
        case 25:
            env->clip_kind = 999;
            break;
        case 28:
            break;
        case 32:
            env->clip_kind = 999;
            break;
        case 33:
            env->clip_kind = 999;
            break;
        case 34:
            break;
        case 38: {
            float env_demo_frame;
            sceVu0FVECTOR cam_pos;
            vwGetViewPosition(cam_pos);
            env_demo_frame = get_demo_frame();
            if (cam_pos[0] > -141000.0f && cam_pos[2] < -101000.0f) {
                env->clip_kind = 666;
            } else {
                env->clip_kind = 999;
            }
            env->leng = 2000.0f;
            if (env_demo_frame > 2860.0f) {
                env->clip_kind = 666;
                break;
            }
            break;
        }
        case 39:
            break;
        case 40: {
            float env_demo_frame = get_demo_frame();
            if (env_demo_frame > 784.0f && env_demo_frame < 875.0f) {
                env->clip_kind = 666;
                break;
            }
            env->clip_kind = 999;
            break;
        }
        case 43:
            break;
        case 44:
            break;
        case 46:
            env->clip_kind = 999;
            env->leng      = 900.0f;
            break;
        case 62:
            env->clip_kind = 999;
            break;
        case 65:
            break;
        case 66: {
            float env_demo_frame = get_demo_frame();
            if (man->kind == AGL_CHARA_KIND) {
                if (env_demo_frame >= 136.0f && env_demo_frame <= 191.0f) {
                    env->clip_kind = 666;
                } else if (env_demo_frame >= 191.0f && env_demo_frame < 951.0f) {
                    env->clip_kind = 999;
                } else if (env_demo_frame >= 951.0f) {
                    env->clip_kind = 999;
                }
            }
            if (man->kind == EN_PAP_CHARA_KIND) {
                if (env_demo_frame >= 130.0f && env_demo_frame <= 200.0f) {
                    env->clip_kind = 666;
                }
                if (env_demo_frame >= 470.0f && env_demo_frame <= 490.0f) {
                    env->clip_kind = 666;
                    break;
                }
            }
            break;
        }
        case 70:
            env->clip_kind = 999;
            break;
        case 71:
            break;
        case 78:
            break;
        case 79:
            env->clip_kind = 999;
            break;
        case 80:
            env->clip_kind = 999;
            break;
    }
}

#line 1151
void sh2shd_get_jms_shadow_env(JMS_SHADOW_ENV* env, int light_kind, sceVu0FVECTOR light_dir) {
    int glb_coord;
    int map_id;
    sceVu0FVECTOR cam_pos;
    JMS_SHADOW_ENV default_env_self_spot = {
        /* .lightKind = */ -1,
        /* .bias = */ 600.0f,
        /* .heightRevision = */ 900.0f,
        /* .scale = */ 10.0f,
    };
    JMS_SHADOW_ENV default_env_self_para = {
        /* .lightKind = */ -1,
        /* .bias = */ 200.0f,
        /* .heightRevision = */ 1500.0f,
        /* .scale = */ 1.0f,
    };
    int flag;

    get_map_id(&glb_coord, &map_id);
    *env = default_env_self_para;

    switch (glb_coord) {
        case 9:
            switch (map_id) {
                case 34:
                    if (light_kind == 1) {
                        sh2shd_del_jms_head(HLL_JMS_CHARA_KIND, 0);
                        break;
                    }
                    break;
                case 42:
                    if ((EventProgressCheck() < 5) && (sh2gfw_Check_JmsSpotOnOff() == 0)) {
                        env->light_kind = 9;
                        break;
                    }
                    break;
                case 72:
                    vwGetViewPosition(cam_pos);
                    env->light_kind = 4;
                    if (cam_pos[0] > 17500.0f) {
                        sh2shd_add_char_to_shadow_off_work(HLL_JMS_CHARA_KIND, 0);
                        sh2shd_off_char_obj(HLL_JMS_CHARA_KIND, 0, 15);
                        sh2shd_off_char_obj(HLL_JMS_CHARA_KIND, 0, 8);
                        light_dir[0] = 0.0f;
                        light_dir[1] = 0.707f;
                        light_dir[2] = 0.0f;
                        light_dir[3] = 0.0f;
                        break;
                    }
                    light_dir[0] = 0.2f;
                    light_dir[1] = 0.707f;
                    light_dir[2] = -0.707f;
                    light_dir[3] = 0;
                    sh2shd_bg_shadow_off();
                    break;
            }
            break;
        case 10:
            switch (map_id) {
                case 69:
                    env->light_kind = 9;
                    break;
            }
            break;
        case 11:
            switch (map_id) {
                case 1:
                    vwGetViewPosition(cam_pos);
                    if (cam_pos[2] > 20000.0f) {
                        env->light_kind = 5;
                        break;
                    }
                    break;
                case 15:
                    if (sh2gfw_Check_JmsSpotOnOff()) {
                        env->light_kind = 6;
                        break;
                    }
                    break;
                case 51:
                    if (sh2gfw_Check_JmsSpotOnOff()) {
                        env->light_kind = 6;
                        break;
                    }
                    break;
            }
            break;
        case 12:
            switch (map_id) {
                case 1:
                    env->light_kind = 2;
                    break;
                case 5:
                    if (sh2gfw_Check_JmsSpotOnOff()) {
                        env->light_kind = 2;
                        break;
                    }
                    break;
                case 9:
                    env->light_kind = 9;
                    break;
                case 29:
                    if ((sh2jms.player->pos.x < -58800.0f) && (sh2jms.player->pos.x > -61370.0f)) {
                        if ((sh2jms.player->pos.z < 20980.0f) && (sh2jms.player->pos.z > 18430.0f)) {
                            env->light_kind = 5;
                            break;
                        }
                    }
                    break;
                case 33:
                    if (light_kind == 2) {
                        env->light_kind = 3;
                        break;
                    }
                    break;
                case 91:
                    env->light_kind = 4;
                    break;
            }
            break;
    }
}

#line 1615
void sh2shd_get_demo_jms_shadow_env(JMS_SHADOW_ENV* env, int demo_no) {
    static float height_test2 = 1300.0f;
    static float scale_test2  = 10.0f;
    static float bias_test2   = 300.0f;

    env->height_revision = 900.0f;
    env->bias            = 600.0f;
    env->scale           = 10.0f;
    env->light_kind      = -1;

    switch (demo_no) {
        case 9:
            break;
        case 10:
            env->light_kind = 6;
            break;
        case 11:
            env->light_kind = 2;
            break;
        case 14:
            env->light_kind      = 3;
            env->height_revision = 1800.0f;
            env->bias            = 500.0f;
            break;
        case 16:
            env->light_kind = 9;
            break;
        case 19:
            env->light_kind = 8;
            break;
        case 33:
            env->light_kind = 6;
            break;
        case 38: {
            float env_demo_frame = get_demo_frame();
            if (env_demo_frame >= 1000.0f && env_demo_frame < 1360.0f) {
                env->light_kind = 3;
                break;
            }
            if (env_demo_frame >= 1510.0f && env_demo_frame < 2240.0f) {
                env->light_kind = 2;
                break;
            }
            if (env_demo_frame > 2860.0f) {
                env->light_kind = 9;
                break;
            }
            env->light_kind = -1;
            break;
        }
        case 40: {
            float env_demo_frame = get_demo_frame();
            if (env_demo_frame >= 0.0f && env_demo_frame <= 244.0f) {
                env->light_kind = 3;
                break;
            }
            if (env_demo_frame > 244.0f && env_demo_frame <= 1100.0f) {
                env->light_kind = 2;
                break;
            }
            if (env_demo_frame > 1100.0f) {
                env->light_kind = 3;
                break;
            }
            break;
        }
        case 46:
            env->light_kind = 8;
            break;
        case 51:
            env->light_kind      = 8;
            env->height_revision = 3000.0f;
            break;
        case 52:
            env->light_kind = 6;
            break;
        case 65:
            break;
        case 66: {
            float env_demo_frame = get_demo_frame();
            env->light_kind      = -1;
            if (env_demo_frame >= 136.0f && env_demo_frame <= 192.0f) {
                env->light_kind = 9;
                break;
            }
            if (env_demo_frame >= 517.0f && env_demo_frame <= 593.0f) {
                env->light_kind = 9;
                break;
            }
            if (env_demo_frame >= 979.0f && env_demo_frame <= 1020.0f) {
                env->light_kind = 9;
                break;
            }
            if (env_demo_frame >= 2290.0f && env_demo_frame <= 2550.0f) {
                env->light_kind      = 6;
                env->bias            = bias_test2;
                env->height_revision = height_test2;
                env->scale           = scale_test2;
                break;
            }
            break;
        }
        case 69:
            get_demo_frame();
            break;
        case 74: {
            sceVu0FMATRIX mat;
            demo_frame = get_demo_frame();
            shCharacterGetPartsMatrixForShadow(mat, LAU_CHARA_KIND, 0, 0);
            if (mat[3][2] < 59000.0f) {
                env->light_kind = 9;
                break;
            }
            break;
        }
        case 77:
            env->light_kind = 4;
            break;
        case 78:
            env->light_kind = 4;
            break;
        default:
            env->light_kind = -1;
            break;
    }
}

#line 1663
void sh2shd_get_drop_shadow_env(DROP_SHADOW_ENV* env, int glb_coord, int map_id, float x, float z) {
    *env = default_drop_env;

    switch (glb_coord) {
        case 1:
    
            

            if ((map_id - 10) <= 1u || (map_id - 13) <= 1u) {

                env->alpha_max = 64.0f;
                env->color     = 0;

                break;
            }
            break;

        case 3:
            switch (map_id) {
                case 0x33:
                    if (x < -99100.0f) {
                        env->alpha_max = 128.0f;
                        break;
                    }
                    if (x < -98700.0f && z < 39550.0f) {
                        env->alpha_max = 128.0f;
                        break;
                    }
            }
            break;

        case 5:
            env->alpha_max = 128.0f;
            break;
    }
}

#line 1749
void sh2shd_get_demo_drop_shadow_env(DROP_SHADOW_ENV* env, int demo_no) {
    *env = default_drop_env;

    switch (demo_no) {
        case 0:
            return;

        case 3:
        case 4:
            env->alpha_max = 128.0f;
            env->color = 0;
            break;

        case 28:
        case 29:
        case 30:
            env->alpha_min = 32.0f;
            env->alpha_max = 32.0f;
            env->color = 0;
            break;
    }
}

static float tmp_time = 2252.0f;

#line 1815
void sh2shd_demo_shadow_off(int demo_no) {
    float demo_frame;
    float test_time;
    switch (demo_no) {
        case DRAMA_DEMO_9:
            break;




































        case DRAMA_DEMO_D:
            sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
            sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
            return;

        case DRAMA_DEMO_E:
            demo_frame = get_demo_frame();
        

            sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
            if (demo_frame <= 1699.0f)
                sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
            else {

                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xF);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 8);

                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 1);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 3);

                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1A);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x19);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xE);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xD);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 5);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 4);
            }
            
            

            sh2shd_add_char_to_shadow_off_work(EN_RED_CHARA_KIND, 0);
            if (get_demo_frame() < 190.0f) {

                sh2shd_off_char_obj(EN_RED_CHARA_KIND, 0, 0x24);
                sh2shd_off_char_obj(EN_RED_CHARA_KIND, 0, 0x1D);
                return;
            } else if (demo_frame >= 360.0f && demo_frame <= 1699.0f) {

                sh2shd_add_char_to_shadow_off_work(EN_RED_CHARA_KIND, 0);
                sh2shd_off_char_all_parts(EN_RED_CHARA_KIND, 0);
            }
            
            
            
            
            
            
            
            
            
            
            
            

            break;

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        case DRAMA_DEMO_21:
            if (get_demo_frame() < 902.0f) {

                sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
                sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
                

                return;
            }
        

            break;


        case DRAMA_DEMO_26:
            sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
            sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1A);
            return;

        
        











        case DRAMA_DEMO_2E:
            demo_frame = get_demo_frame();
            if (demo_frame < 780.0f) {

                sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x21);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x28);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 3);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 1);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1C);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x22);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x23);
                sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1B);
        

                if (demo_frame > 510.0f) {

                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 4);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 5);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

                    return;
                }
            }
            break;







        case DRAMA_DEMO_41:
            break;

        
        
        
        
        
        
        
        
        
        
        
        case DRAMA_DEMO_42: {
            float cam_pos[4];
            float env_demo_frame;
            vwGetViewPosition(&cam_pos);
            env_demo_frame = get_demo_frame();

            if (env_demo_frame >= 135.0f && env_demo_frame <= 192.0f) {

                sh2shd_add_char_to_shadow_off_work(EN_PAP_CHARA_KIND, 0);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 3);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 4);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 5);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 7);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 8);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 9);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x11);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x12);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x13);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x17);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1B);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1C);
            } else 
                if (env_demo_frame >= 518.0f && env_demo_frame <= 608.0f) {

                sh2shd_add_char_to_shadow_off_work(EN_PAP_CHARA_KIND, 0);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 3);

                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 5);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 7);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 8);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 9);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x11);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x12);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x13);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x17);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1B);
                sh2shd_off_char_obj(EN_PAP_CHARA_KIND, 0, 0x1C);

                sh2shd_add_char_to_shadow_off_work(AGL_CHARA_KIND, 0);
                sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 0x1F);
                sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 6);
                sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 2);
                sh2shd_off_char_obj(AGL_CHARA_KIND, 0, 0);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

                return;
            }
            break;
        }
















        case DRAMA_DEMO_4A: {
            float mat[4][4];
            float env_demo_frame = get_demo_frame();
            shCharacterGetPartsMatrixForShadow(mat, LAU_CHARA_KIND, 0U, 0U);
            if (mat[3][2] > 59000.0f) {

                if (env_demo_frame > 320.0f && env_demo_frame <= 962.0f) {

                    sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                    sh2shd_off_char_all_parts(LAU_CHARA_KIND, 0);

                    return;
                }




            } else if (env_demo_frame >= 782.0f && env_demo_frame < 1420.0f) {

                sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 1);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xB);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xC);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xF);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x10);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 3);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 7);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x12);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x16);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x1F);
                sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x25);
                
                

                return;
            }
            break;
        }


        case DRAMA_DEMO_4E:

            demo_frame = get_demo_frame();
            if (demo_frame > 1750.0f) {
            
                

                sh2shd_add_char_to_shadow_off_work(HHH_JMS_CHARA_KIND, 0);

                if (demo_frame < tmp_time)
                    sh2shd_off_char_all_parts(HHH_JMS_CHARA_KIND, 0);
                else if (demo_frame < 3220.0f) {

                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1A);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x19);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xE);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0xD);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 5);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 4);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 1);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x1B);
                    sh2shd_off_char_obj(HHH_JMS_CHARA_KIND, 0, 0x21);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

                    sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 1);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xB);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xC);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0xF);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x10);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 3);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 7);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x12);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x16);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x1F);
                    sh2shd_off_char_obj(LAU_CHARA_KIND, 0, 0x25);
                }
            }
            break;
    }



































}

#line 2286
void sh2shd_shadow_off(int glb_coord, int map_id) {
    switch (glb_coord) {
        case 9:
            if (map_id == 88) {
                sh2shd_add_char_to_shadow_off_work(EN_SCU_CHARA_KIND, 9);
                sh2shd_off_char_all_parts(EN_SCU_CHARA_KIND, 9);
                break;
            }
            break;

        case 10:
            if (map_id == 45) {
                sh2shd_add_char_to_shadow_off_work(LAU_CHARA_KIND, 0);
                sh2shd_off_char_all_parts(LAU_CHARA_KIND, 0);
                break;
            } else if (map_id == 150) {
                if (sh2jms.player->pos.z > -222800.0f) {
                    sh2shd_add_map_to_shadow_off_work(150);
                    sh2shd_off_obj(150, 8);
                    break;
                }
                break;
            }
            break;

        case 11: {
            sceVu0FVECTOR cam_pos;

            if (map_id == 113) {
                vwGetViewPosition(cam_pos);
                if (cam_pos[1] > -1000.0f) {
                    sh2shd_add_map_to_shadow_off_work(0x71);
                    sh2shd_off_obj(0x71, 2);
                    sh2shd_off_obj(0x71, 0x15);
                    sh2shd_off_obj(0x71, 0x17);
                    sh2shd_off_obj(0x71, 0x16);
                    sh2shd_off_obj(0x71, 0x18);
                    break;
                }
            }
            break;
        }

        case 12: {
            sceVu0FVECTOR cam_pos;

            if (map_id == 9) {
                vwGetViewPosition(cam_pos);
                if (cam_pos[1] > -2000.0f) {
                    sh2shd_add_map_to_shadow_off_work(9);
                    sh2shd_off_obj(9, 0x52);
                }
            }
            break;
        }
    }
}

#line 2478
static float get_demo_frame(void) {
    return demo_frame;
}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_env", get_map_id);

#line 2505
int check_bg_light_exist(void) {
    int glb_coord;
    int map_id;

    get_map_id(&glb_coord, &map_id);
    switch (glb_coord) {
        case 9:
            switch (map_id) {
                default:
                    break;
                case 42:
                    return 0;
            }
            break;
        case 12:
            if (map_id == 0x5B) {
                return 4;
            }
            break;
    }
    return 9;
}
