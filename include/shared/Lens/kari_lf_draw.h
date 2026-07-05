#ifndef KARI_LF_DRAW_SHARED_H
#define KARI_LF_DRAW_SHARED_H

/* @note: this may belong elsewhere */
#define EFF_VALID_ID 0xEF04

static inline u_int reinterpret_as_u_int(float v) {
    return *(u_int*) &v;
}

static inline void set_color_clamped_vec(IVector4* color, float c, IVector4* v) {
    color->x = (int) (v->x * c);
    color->y = (int) (v->y * c);
    color->z = (int) (v->z * c);

    if (color->x > 255) {
        color->x = 255;
    }
    if (color->y > 255) {
        color->y = 255;
    }
    if (color->z > 255) {
        color->z = 255;
    }
}


static inline void set_color_clamped(IVector4* color, float c, float r, float g, float b) {
    color->x = (int) (r * c);
    color->y = (int) (g * c);
    color->z = (int) (b * c);

    if (color->x > 255) {
        color->x = 255;
    }
    if (color->y > 255) {
        color->y = 255;
    }
    if (color->z > 255) {
        color->z = 255;
    }
}

void kari_Thr_LFD2TextureSend(void);

void kari_Thr_LFD1D2SyncKick(void* pktop);

void* kari_shLensFlareDraw(void);

void Kari_LensFlare_DrawExec(void);

#endif // KARI_LF_DRAW_H
