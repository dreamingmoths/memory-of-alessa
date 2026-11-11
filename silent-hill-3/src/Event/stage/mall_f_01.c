#include "mall_f_01.h"

int func_01F6D680_mall_f_01() {
    switch (D_01F72BC8_mall_f_01) {
        case 0:
            func_001C2290(3, 0.3f);
            func_0019B4B0(7);
            D_01F72BC8_mall_f_01++;
            /* fallthrough */
        case 1:
            if (!func_001C2580(2)) {
                return 0;
            }

            D_01F72BC0_mall_f_01 = &D_01F72758_mall_f_01;
            SET_BIT(D_1D31644, 9);
            D_01F72BC8_mall_f_01++;
            /* fallthrough */
        default:
            if (!func_0016C540(&D_01F72760_mall_f_01, &D_01F727C0_mall_f_01)) {
                float var_f20;

                for (var_f20 = func_001643C0(); D_01F72BC0_mall_f_01->unk0 > 0.0f; D_01F72BC0_mall_f_01++) {
                    if (D_01F72BC0_mall_f_01->unk0 > var_f20) {
                        break;
                    }

                    func_0013D250(0, D_01F72BC0_mall_f_01->unk4, 1.0f);
                }

                return 0;
            }

            UNSET_BIT(D_1D31644, 9);
            func_001C2290(5, 0.5f);
            func_0013D280(0);

            if (GET_BIT(D_1D31784, 1)) {
                SET_BIT(D_1D31784, 2);
            }

            return 1;
    }
}

int func_01F6D820_mall_f_01() {
    int ret = func_0016C540(&D_01F72810_mall_f_01, &D_01F72870_mall_f_01);

    if (!D_01F72BB8_mall_f_01) {
        func_003272C0();
        D_01F72BB8_mall_f_01 = 1;
        D_01F72BB0_mall_f_01 = shRandI() % 30 + 1940;
    } else if (func_001643C0() > 0.0f) {
        float var_f20 = func_001643C0();

        if (var_f20 >= 1940.0f && var_f20 <= 2600.0f && D_01F72BB0_mall_f_01 <= var_f20) {
            D_01F727E0_struct* var_s1 = &D_01F727E0_mall_f_01;
            int temp_v1               = shRandI() % 4;

            while (temp_v1) {
                temp_v1--;
                var_s1++;
            }

            func_0013D250(0, var_s1->unk4, 1.0f);
            D_01F72BB0_mall_f_01 = 15.0f + var_f20 + 30.0f * shRandF();
        }

        func_003272E0();
    }

    if (ret) {
        if (func_001646C0()) {
            func_001602D0(10028, 3, 1, 1.0f);
        }

        func_001C2290(5, 0.5f);
        func_003272D0();
        func_0013D280(0);
    }

    return ret;
}

int func_01F6DA20_mall_f_01() {
    int ret = func_0016C540(&D_01F72890_mall_f_01, &D_01F728F0_mall_f_01);

    if (ret) {
        func_001C2290(5, 0.5f);
    }

    return ret;
}

int func_01F6DA70_mall_f_01() {
    if (!GET_BIT(D_1D3164C, 24)) {
        D_01F72B80_mall_f_01 = 0;
        func_0016C3C0();
        SET_BIT(D_1D3164C, 24);
        func_00317420(5);
        func_00190A20(2);
    }

    switch (D_01F72B80_mall_f_01) {
        case 0:
            if (!func_0016C1C0(50)) {
                return 0;
            } else if (func_00168440()) {
                break;
            }

            func_0016C3C0();
            SeCall(11041, 1.0f, 0.0f);
            ItemGet(5);
            SET_BIT(D_1D3164C, 25);
            func_00317490(5, 0.2f);
            D_01F72B80_mall_f_01++;
            /* fallthrough */
        default:
            if (!func_0016C1C0(72)) {
                return 0;
            }

            func_003174B0(0.2f);
    }

    UNSET_BIT(D_1D3164C, 24);
    func_00190A20(0);

    return 1;
}

int func_01F6DBD0_mall_f_01() {
    int var_s0;
    int var_a1;

    func_0012CFA0();

    if (!func_0012D080()) {
        func_00190A20(2);
    }

    func_0012CFC0();

    if (GET_BIT(D_1D3164C, 27)) {
        var_s0 = 61;
        var_a1 = 48;
    } else {
        var_s0 = 62;
        var_a1 = !GET_BIT(D_1D31BF4, 5) || GetRiddleLevel() != 0 ? 46 : 47;

        if (!GET_BIT(D_1D31784, 1)) {
            SET_BIT(D_1D31784, 1);
        }
    }

    if (!func_0016BED0(var_s0, var_a1)) {
        return 0;
    }

    func_00190A20(0);

    return 1;
}

int func_01F6DCC0_mall_f_01() {
    int var_a0;
    int var_a1;

    func_0012CFA0();

    if (!func_0012D080()) {
        func_00190A20(2);
    }

    func_0012CFC0();

    if (GetRiddleLevel() == 1) {
        var_a0 = 66;
        var_a1 = 51;

        if (!GET_BIT(D_1D316F0, 27) && !GET_BIT(D_1D316F0, 28)) {
            SET_BIT(D_1D316F0, 27);
        }
    } else {
        var_a0 = 65;
        var_a1 = 52;

        if (!GET_BIT(D_1D316F0, 29) && !GET_BIT(D_1D316F0, 30)) {
            SET_BIT(D_1D316F0, 29);
        }
    }

    if (!func_0016BED0(var_a0, var_a1)) {
        return 0;
    }

    func_00190A20(0);

    return 1;
}

void func_01F6DDB0_mall_f_01() {
    PicDraw_Data pic;

    shQzero(&pic, sizeof(PicDraw_Data));

    SET_BIT(pic.status, 9);
    pic.r = 0;
    pic.g = 0;
    pic.b = 255;
    SET_BIT(pic.status, 4);
    pic.otp = 6;
    pic.x0  = 1792;
    pic.y0  = 256;
    pic.x1  = 3968;
    pic.y1  = 256;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);

    pic.x0 = 3968;
    pic.y0 = 256;
    pic.x1 = 3968;
    pic.y1 = 2432;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);

    pic.x0 = 3968;
    pic.y0 = 2432;
    pic.x1 = 1792;
    pic.y1 = 2432;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);

    pic.x0 = 1792;
    pic.y0 = 2432;
    pic.x1 = 1792;
    pic.y1 = 256;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);
}

void func_01F6DF00_mall_f_01(Shakespeare_Puzzle_Work* work) {
    PicDraw_Data* pic_bg = &work->pic_quads[0];

    work->pic_loads[0].ap       = func_00170410(1);
    work->pic_loads[0].tex_adr  = -1;
    work->pic_loads[0].clut_adr = -1;
    work->pic_loads[0].otp      = 0;
    PictureLoadImage(&work->pic_loads[0]);

    shQzero(pic_bg, sizeof(PicDraw_Data));

    pic_bg->ap   = func_00170410(1);
    pic_bg->tex  = -1;
    pic_bg->clut = -1;
    SET_BIT(pic_bg->status, 0);
    pic_bg->otp = 1;
    PictureDraw(pic_bg);
}

void func_01F6DF90_mall_f_01(Shakespeare_Puzzle_Work* work) {
    PicLoadImage_Data* pic_load = &work->pic_loads[1];

    pic_load->ap       = func_00170410(0);
    pic_load->tex_adr  = -1;
    pic_load->clut_adr = -1;
    pic_load->otp      = 2;
    PictureLoadImage(pic_load);
}

#ifdef NON_MATCHING
void func_01F6DFE0_mall_f_01(Shakespeare_Puzzle_Work* work, int slot_index) {
    PicDraw_Data* book_quad;
    int side;
    int solution_index = 0;
    int book_id;
    int x_start;
    int x_end;
    int i;

    if (!slot_index || !(book_id = work->placed_order[slot_index - 1])) {
        return;
    }

    x_start   = (slot_index - 1) * 42 - 108;
    x_end     = x_start + 48;
    book_quad = &work->pic_quads[(slot_index - 1) * 3 + 1];

    shQzero(book_quad, sizeof(PicDraw_Data));

    book_quad->ap   = func_00170410(0);
    book_quad->tex  = -1;
    book_quad->clut = -1;
    SET_BIT(book_quad->status, 0);
    book_quad->a         = 128;
    book_quad->alpha_a   = 0;
    book_quad->alpha_b   = 1;
    book_quad->alpha_c   = 0;
    book_quad->alpha_d   = 1;
    book_quad->alpha_fix = 0;
    SET_BIT(book_quad->status, 5);
    book_quad->us0 = (book_id - 1) * 768;
    book_quad->vt0 = 0;
    book_quad->us1 = book_id * 768;
    book_quad->vt1 = 4864;
    UNSET_BIT(book_quad->status, 3);
    SET_BIT(book_quad->status, 2);
    book_quad->x0 = FP16(x_start);
    book_quad->y0 = -2368;
    book_quad->x1 = FP16(x_end);
    book_quad->y1 = -2368;
    SET_BIT(book_quad->status, 1);
    book_quad->x2 = FP16(x_start);
    book_quad->y2 = 2496;
    book_quad->x3 = FP16(x_end);
    book_quad->y3 = 2496;
    SET_BIT(book_quad->status, 7);
    book_quad->otp = 3;
    PictureDraw(book_quad);

    if (work->riddle_level >= 2) {
        return;
    }

    for (i = 0; i < 5; i++) {
        if (book_id == work->solution_order[i]) {
            solution_index = i;
            break;
        }
    }

    for (side = 0; side < 2; side++) {
        int x_start;
        int x_end;
        int u_start;
        int v_start;

        if ((!side && !solution_index) || (side && solution_index == 4)) {
            continue;
        }

        u_start   = work->formed_digits[solution_index + side - 1] % 5 * 48 + 240 + (1 - side) * 48 / 2;
        v_start   = work->formed_digits[solution_index + side - 1] / 5 * 144;
        x_start   = (slot_index - 1) * 42 - 108 + (side * 48 / 2);
        x_end     = x_start + 24;
        book_quad = &work->pic_quads[(slot_index - 1) * 3 + 2 + side];

        shQzero(book_quad, sizeof(PicDraw_Data));

        book_quad->ap   = func_00170410(0);
        book_quad->tex  = -1;
        book_quad->clut = -1;
        SET_BIT(book_quad->status, 0);
        book_quad->a         = 128;
        book_quad->alpha_a   = 0;
        book_quad->alpha_b   = 1;
        book_quad->alpha_c   = 0;
        book_quad->alpha_d   = 1;
        book_quad->alpha_fix = 0;
        SET_BIT(book_quad->status, 5);
        book_quad->us0 = FP16(u_start);
        book_quad->vt0 = FP16(v_start);
        book_quad->us1 = FP16(u_start + 24);
        book_quad->vt1 = FP16(v_start + 144);
        UNSET_BIT(book_quad->status, 3);
        SET_BIT(book_quad->status, 2);
        book_quad->x0 = FP16(x_start);
        book_quad->y0 = 192;
        book_quad->x1 = FP16(x_end);
        book_quad->y1 = 192;
        SET_BIT(book_quad->status, 1);
        book_quad->x2 = FP16(x_start);
        book_quad->y2 = 2496;
        book_quad->x3 = FP16(x_end);
        book_quad->y3 = 2496;
        SET_BIT(book_quad->status, 7);
        book_quad->otp = 4;
        PictureDraw(book_quad);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_f_01", func_01F6DFE0_mall_f_01);
#endif

void func_01F6E3F0_mall_f_01(Shakespeare_Puzzle_Work* work, int slot_index) {
    int x_start;
    int y_top;
    int x_end;
    int y_bottom;
    int alpha;
    PicDraw_Data* selection_book;

    if (!slot_index || !work->selection_slots[slot_index - 1]) {
        return;
    }

    if (work->selected_book == slot_index) {
        alpha = 64 + (work->book_blink < 0.5f
            ? 64 * (0.5f - work->book_blink) / 0.5f
            : 64 * (work->book_blink - 0.5f) / 0.5f);
    } else {
        alpha = 128;
    }

    x_start = (slot_index - 1) * 24 + 120;
    y_top   = 48;

    if (work->selected_book == slot_index) {
        y_top -= 24;
    }

    x_end          = x_start + 24;
    y_bottom       = y_top + 96;
    selection_book = &work->pic_quads[slot_index + 32];

    shQzero(selection_book, sizeof(PicDraw_Data));

    selection_book->ap   = func_00170410(0);
    selection_book->tex  = -1;
    selection_book->clut = -1;
    SET_BIT(selection_book->status, 0);
    selection_book->a         = alpha;
    selection_book->alpha_a   = 0;
    selection_book->alpha_b   = 1;
    selection_book->alpha_c   = 0;
    selection_book->alpha_d   = 1;
    selection_book->alpha_fix = 0;
    SET_BIT(selection_book->status, 5);
    selection_book->us0 = (slot_index - 1) * 768;
    selection_book->vt0 = 0;
    selection_book->us1 = slot_index * 768;
    selection_book->vt1 = 4864;
    UNSET_BIT(selection_book->status, 3);
    SET_BIT(selection_book->status, 2);
    selection_book->x0 = FP16(x_start);
    selection_book->y0 = FP16(y_top);
    selection_book->x1 = FP16(x_end);
    selection_book->y1 = FP16(y_top);
    SET_BIT(selection_book->status, 1);
    selection_book->x2 = FP16(x_start);
    selection_book->y2 = FP16(y_bottom);
    selection_book->x3 = FP16(x_end);
    selection_book->y3 = FP16(y_bottom);
    SET_BIT(selection_book->status, 7);
    selection_book->otp = 5;
    PictureDraw(selection_book);
}

void func_01F6E630_mall_f_01(Shakespeare_Puzzle_Work* work) {
    int i;

    func_01F6DF00_mall_f_01(work);
    func_01F6DF90_mall_f_01(work);

    for (i = 0; i < 5; i++) {
        func_01F6DFE0_mall_f_01(work, i + 1);
    }

    for (i = 0; i < 5; i++) {
        func_01F6E3F0_mall_f_01(work, i + 1);
    }

    for (i = 0; i < 5; i++) {
        if (work->selection_slots[i]) {
            func_01F6DDB0_mall_f_01();
            break;
        }
    }
}

int func_01F6E6E0_mall_f_01(Shakespeare_Puzzle_Work* work) {
    return func_001DE5B0(func_01F6E630_mall_f_01, work, 1);
}

int func_01F6E700_mall_f_01() {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

#ifdef NON_MATCHING
int func_01F6E730_mall_f_01(Shakespeare_Puzzle_Work* work) {
    int var_s0;
    float temp_f0;

    if (!work->interactive_mode) {
        if (!func_0016C1C0(work->riddle_level == 0 ? 56 : 53)) {
            return 0;
        } else {
            return 1;
        }
    }

    PlayerResultTimerCountUp();

    if (!work->selected_book || (temp_f0 = work->book_blink + shGetDT()) > 1.0f) {
        work->book_blink = 0.0f;
    } else {
        work->book_blink = temp_f0;
    }

    var_s0 = func_01F6E700_mall_f_01();

    if (func_0013D080(0, 0, 1, 2)) {
        if (work->selected_book) {
            work->selected_book = 0;
        } else {
            fontClear();

            return 1;
        }
    }

    if (work->selected_book) {
        work->message_id = D_01F7290C_mall_f_01[work->selected_book].unk0;
    } else if (var_s0 > 0 && var_s0 < 6 && work->placed_order[var_s0 - 1]) {
        work->message_id = D_01F7290C_mall_f_01[work->placed_order[var_s0 - 1]].unk0;
    } else if (var_s0 >= 6 && work->selection_slots[var_s0 - 6]) {
        work->message_id = D_01F72894_mall_f_01[var_s0].unk0;
    } else {
        work->message_id = 0;
    }

    fontClear();

    if (work->message_id) {
        u_short* msg_ptr = fontGetMesAdr(GetMessageStation(), work->message_id);

        fontPrintStrMain(&msg_ptr, 0);
    }

    if (!func_0013D080(0, 0, 1, 1) || !var_s0) {
        return 0;
    } else if (var_s0 < 6) {
        int index                     = var_s0;
        var_s0                        = work->placed_order[index - 1];
        work->placed_order[index - 1] = work->selected_book;

        if (work->selected_book) {
            SeCall(12101, 1.0f, 0.0f);

            work->selection_slots[work->selected_book - 1] = 0;
            work->selected_book                            = 0;
        }

        if (var_s0) {
            work->selection_slots[var_s0 - 1] = var_s0;
        }
    } else if (work->selection_slots[var_s0 - 6]) {
        if (work->selected_book == (var_s0 - 5)) {
            work->selected_book = 0;
        } else {
            work->selected_book = var_s0 - 5;
        }
    }

    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_f_01", func_01F6E730_mall_f_01);
#endif

#ifdef NON_MATCHING
void func_01F6E9E0_mall_f_01(Shakespeare_Puzzle_Work* work, int arg1) {
    u_int* temp_D_01D31640;
    int i;

    shQzero(work, sizeof(Shakespeare_Puzzle_Work));

    temp_D_01D31640    = D_01D31640;
    work->riddle_level = GetRiddleLevel();

    switch (work->riddle_level) {
        case 0:
            SET_BIT(D_1D316F0, 10);
            break;
        case 1:
            if (GET_BIT(D_1D316F0, 27)) {
                UNSET_BIT(D_1D316F0, 27);
                SET_BIT(D_1D316F0, 12);
            }

            break;
        case 2:
        case 3:
            if (GET_BIT(D_1D316F0, 29)) {
                UNSET_BIT(D_1D316F0, 29);
                SET_BIT(D_1D316F0, 14);
            }
    }

    work->formed_digits[3] = temp_D_01D31640[162] % 16;
    work->formed_digits[2] = (temp_D_01D31640[162] >> 4) % 16;
    work->formed_digits[1] = (temp_D_01D31640[162] >> 8) % 16;
    work->formed_digits[0] = (temp_D_01D31640[162] >> 12) % 16;

    work->solution_order[4] = temp_D_01D31640[161] % 16;
    work->placed_order[4]   = temp_D_01D31640[160] % 16;

    work->solution_order[3] = (temp_D_01D31640[161] >> 4) % 16;
    work->placed_order[3]   = (temp_D_01D31640[160] >> 4) % 16;

    work->solution_order[2] = (temp_D_01D31640[161] >> 8) % 16;
    work->placed_order[2]   = (temp_D_01D31640[160] >> 8) % 16;

    work->solution_order[1] = (temp_D_01D31640[161] >> 12) % 16;
    work->placed_order[1]   = (temp_D_01D31640[160] >> 12) % 16;

    work->solution_order[0] = (temp_D_01D31640[161] >> 16) % 16;
    work->placed_order[0]   = (temp_D_01D31640[160] >> 16) % 16;

    for (i = 0; i < 5; i++) {
        if (work->placed_order[i] && (work->riddle_level || work->placed_order[i] == 1 || work->placed_order[i] == 3)) {
            work->placed_count++;
        }
    }

    if (arg1 || work->placed_count) {
        work->interactive_mode = 3;

        if ((!work->riddle_level && work->placed_count == 2) || (work->riddle_level >= 0 && work->placed_count == 5)) {
            work->message_id = 55;
        } else {
            work->message_id = 54;
        }
    } else {
        work->interactive_mode = 0;
    }

    if (work->interactive_mode) {
        for (i = 0; i < 5; i++) {
            if (GET_FLAG(D_01D319F0 + 128, D_01F72910_mall_f_01[i].unk0)) {
                work->selection_slots[i] = i + 1;

                if (arg1 && arg1 == D_01F72910_mall_f_01[i].unk0) {
                    work->selected_book = i + 1;
                }
            } else {
                work->selection_slots[i] = 0;
            }
        }

        func_0029F9B0();
        func_0029F3D0(8);
        func_002A45F0();

        for (i = 0; i < 5; i++) {
            if (!work->riddle_level) {
                switch (work->placed_order[i]) {
                    case 5:
                    case 4:
                    case 2:
                        continue;
                }
            }

            func_002A4640(i + 1, 42 * i + 151, 120.0f, 42.0f, 280.0f);
        }

        for (i = 0; i < 5; i++) {
            if (!work->riddle_level) {
                switch (i) {
                    case 4:
                    case 3:
                    case 1:
                        continue;
                }
            }

            func_002A4640(i + 6, 24 * i + 376, 280.0f, 24.0f, 120.0f);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_f_01", func_01F6E9E0_mall_f_01);
#endif

int func_01F6EE40_mall_f_01(int arg0) {
    Shakespeare_Puzzle_Work* work = func_00156410(9);
    int i;

    if (!GET_BIT(D_1D31650, 4)) {
        SET_BIT(D_1D31650, 4);
        func_01F6E9E0_mall_f_01(work, arg0);
        func_00190A20(2);
    }

    switch (work->step) {
        case 0:
            func_0016BBF0();
            func_0016C1A0();
            func_0016F550(68, 1);
            func_0016F550(67, 0);
            func_001C2290(3, func_00151150(0, 1) ? 0.8f : 1.2f);
            work->step = 1;
            /* fallthrough */
        case 1:
            if (func_00151150(0, 1) && func_001C2580(2)) {
                func_001C2290(5, 0.8f);
                work->step = 2;
            }

            break;
        case 2:
            func_01F6E6E0_mall_f_01(work);

            if (func_001C2580(4)) {
                if (!work->interactive_mode) {
                    work->step = 4;
                } else {
                    work->step = 3;
                }
            }

            break;
        case 3:
            func_01F6E6E0_mall_f_01(work);

            if (func_0016C1C0(work->message_id)) {
                func_0016C3C0();
                work->message_id = 0;
                work->step       = 4;
            }

            break;
        case 4:
            if (work->interactive_mode) {
                func_0029FA30();
            }

            if (func_01F6E730_mall_f_01(work)) {
                work->step = 5;
            }

            func_01F6E6E0_mall_f_01(work);
            break;
        case 5:
            func_01F6E6E0_mall_f_01(work);
            func_001C2290(3, func_00151150(0, 1) ? 0.8f : 1.2f);

            if (func_001C2580(2)) {
                work->step = 6;
            }

            break;
        default:
            for (i = 0; i < 5; i++) {
                D_1D318C0 <<= 4;
                D_1D318C0 += work->placed_order[i];

                if (!work->interactive_mode) {
                    continue;
                }

                if (work->selection_slots[i]) {
                    SET_FLAG(D_01D319F0 + 128, D_01F72910_mall_f_01[i].unk0);
                } else {
                    UNSET_FLAG(D_01D319F0 + 128, D_01F72910_mall_f_01[i].unk0);
                }
            }

            func_0016C1B0();
            func_001C2290(5, 0.8f);
            UNSET_BIT(D_1D31650, 4);
            func_00190A20(0);

            return 1;
    }

    return 0;
}

int func_01F6F1C0_mall_f_01() {
    return func_01F6EE40_mall_f_01(0);
}

int func_01F6F1D0_mall_f_01() {
    return func_01F6EE40_mall_f_01(39);
}

int func_01F6F1E0_mall_f_01() {
    return func_01F6EE40_mall_f_01(40);
}

int func_01F6F1F0_mall_f_01() {
    return func_01F6EE40_mall_f_01(41);
}

int func_01F6F200_mall_f_01() {
    return func_01F6EE40_mall_f_01(42);
}

int func_01F6F210_mall_f_01() {
    return func_01F6EE40_mall_f_01(43);
}

void func_01F6F220_mall_f_01(Shakespeare_Keypad_Work* work) {
    PicDraw_Data* pic_bg = &work->pic_quads[0];

    work->pic_loads[0].ap       = func_00170410(1);
    work->pic_loads[0].tex_adr  = -1;
    work->pic_loads[0].clut_adr = -1;
    work->pic_loads[0].otp      = 0;
    sh3_PictureLoadImageWrapped(&work->pic_loads[0]);

    shQzero(pic_bg, sizeof(PicDraw_Data));

    pic_bg->ap   = func_00170410(1);
    pic_bg->tex  = -1;
    pic_bg->clut = -1;
    SET_BIT(pic_bg->status, 0);
    pic_bg->otp = 1;
    sh3_PictureDrawWrapped(pic_bg);
}

void func_01F6F2B0_mall_f_01(Shakespeare_Keypad_Work* work) {
    PicLoadImage_Data* pic_load = &work->pic_loads[1];

    pic_load->ap       = func_00170410(0);
    pic_load->tex_adr  = -1;
    pic_load->clut_adr = -1;
    pic_load->otp      = 2;
    sh3_PictureLoadImageWrapped(pic_load);
}

#ifdef NON_MATCHING
void func_01F6F300_mall_f_01(Shakespeare_Keypad_Work* work, int key) {
    int u_start;
    int v_start;
    int x_start;
    int y_top;
    int x_end;
    int y_bottom;
    int i;
    PicDraw_Data* pic_key;
    D_01F72990_struct* temp_D_01F72990;

    if (key < 0 || key >= 11) {
        return;
    }

    for (i = 0, temp_D_01F72990 = D_01F72990_mall_f_01; i < 10; i++, temp_D_01F72990++) {
        if (temp_D_01F72990->unk0 == key) {
            break;
        }
    }

    u_start  = (temp_D_01F72990->unk0 + 9) % 10 % 5 * 32;
    v_start  = (temp_D_01F72990->unk0 + 9) % 10 / 5 * 48;
    x_start  = temp_D_01F72990->unk4 - 256;
    y_top    = temp_D_01F72990->unk8 - 256;
    x_end    = x_start + 32;
    y_bottom = y_top + 48;
    pic_key  = &work->pic_quads[key + 1];

    shQzero(pic_key, sizeof(PicDraw_Data));

    pic_key->ap   = func_00170410(0);
    pic_key->tex  = -1;
    pic_key->clut = -1;
    SET_BIT(pic_key->status, 0);
    pic_key->a         = 128;
    pic_key->alpha_a   = 0;
    pic_key->alpha_b   = 1;
    pic_key->alpha_c   = 0;
    pic_key->alpha_d   = 1;
    pic_key->alpha_fix = 0;
    SET_BIT(pic_key->status, 5);
    pic_key->us0 = FP16(u_start);
    pic_key->vt0 = FP16(v_start);
    pic_key->us1 = FP16(u_start + 32);
    pic_key->vt1 = FP16(v_start + 48);
    UNSET_BIT(pic_key->status, 3);
    SET_BIT(pic_key->status, 2);
    pic_key->x0 = FP16(x_start);
    pic_key->y0 = FP16(y_top);
    pic_key->x1 = FP16(x_end);
    pic_key->y1 = FP16(y_top);
    SET_BIT(pic_key->status, 1);
    pic_key->x2 = FP16(x_start);
    pic_key->y2 = FP16(y_bottom);
    pic_key->x3 = FP16(x_end);
    pic_key->y3 = FP16(y_bottom);
    SET_BIT(pic_key->status, 7);
    pic_key->otp = 3;
    sh3_PictureDrawWrapped(pic_key);
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_f_01", func_01F6F300_mall_f_01);
#endif

void func_01F6F510_mall_f_01(Shakespeare_Keypad_Work* work) {
    int i;

    func_01F6F220_mall_f_01(work);
    func_01F6F2B0_mall_f_01(work);

    for (i = 0; i < 10; i++) {
        if (i != work->last_pressed_key || work->key_blink <= 0.0f) {
            func_01F6F300_mall_f_01(work, i);
        }
    }
}

int func_01F6F5A0_mall_f_01() {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

int func_01F6F5D0_mall_f_01(Shakespeare_Keypad_Work* work) {
    int var_s1;

    PlayerResultTimerCountUp();
    func_0029FA30();

    if (work->key_blink > 0.0f) {
        work->key_blink -= shGetDT();

        return 0;
    }

    if (work->entered_code == work->correct_password) {
        return 2;
    }

    var_s1 = func_01F6F5A0_mall_f_01();

    if (func_0013D080(0, 0, 1, 2)) {
        return 1;
    } else if (func_0013D080(0, 0, 1, 1) && var_s1) {
        work->last_pressed_key = D_01F72974_mall_f_01[var_s1].unk0;
        work->entered_code &= 0xFFFF0FFF;
        work->entered_code <<= 4;
        work->entered_code += work->last_pressed_key;
        work->key_blink = 0.2f;
        SeCall(12100, 1.0f, 0.0f);
    }

    return 0;
}

void func_01F6F720_mall_f_01(Shakespeare_Keypad_Work* work) {
    u_int* temp_D_01D31640 = D_01D31640;
    int i;
    D_01F72990_struct* temp_D_01F72990;

    func_0029F9B0();
    func_002A45F0();

    for (i = 0, temp_D_01F72990 = D_01F72990_mall_f_01; i < 10; i++, temp_D_01F72990++) {
        func_002A4640(i + 1, temp_D_01F72990->unkC, temp_D_01F72990->unk10, temp_D_01F72990->unk14, temp_D_01F72990->unk18);
    }

    shQzero(work, sizeof(Shakespeare_Keypad_Work));

    if (GET_BIT(D_1D31650, 7)) {
        work->step = 1;
    } else {
        SeCall(19004, 1.0f, 0.0f);
        work->step = 0;
    }

    work->correct_password = temp_D_01D31640[162];
    work->entered_code     = 0xFFFF;
}

int func_01F6F810_mall_f_01() {
    Shakespeare_Keypad_Work* work = func_00156410(9);
    int temp_v0;

    if (!GET_BIT(D_1D31650, 8)) {
        SET_BIT(D_1D31650, 8);
        func_01F6F720_mall_f_01(work);
        func_00190A20(2);
    }

    switch (work->step) {
        case 0:
            if (!func_0016C1C0(0)) {
                break;
            }

            work->step = 1;
            /* fallthrough */
        case 1:
            func_0016BBF0();
            func_0016F550(64, 1);
            func_0016F550(63, 0);

            func_001C2290(3, func_00151150(0, 1) ? 0.8f : 1.2f);
            work->step = 2;
            /* fallthrough */
        case 2:
            if (func_00151150(0, 1) && func_001C2580(2)) {
                func_001C2290(5, 0.8f);
                func_0016C1A0();
                work->step = 3;
            }

            break;
        case 3:
            func_01F6F510_mall_f_01(work);

            if (func_001C2580(4)) {
                work->step = 4;
            }

            break;
        case 4:
            temp_v0 = func_01F6F5D0_mall_f_01(work);

            if (temp_v0 == 2) {
                SeCall(19003, 1.0f, 0.0f);
                work->step = 7;
            } else if (temp_v0 == 1) {
                work->step = 5;
            }

            func_01F6F510_mall_f_01(work);
            break;
        case 5:
            func_01F6F510_mall_f_01(work);

            if (GET_BIT(D_1D31650, 6)) {
                func_0016BC00(1);
            }

            func_001C2290(3, func_00151150(0, 1) ? 0.8f : 1.2f);

            if (func_001C2580(2)) {
                work->step = 6;
            }

            break;
        case 7:
            func_01F6F510_mall_f_01(work);
            func_0016BC00(1);

            if (func_0016C1C0(1)) {
                work->step = 5;
                SET_BIT(D_1D31650, 6);
            }

            break;
        default:
            func_0016C1B0();
            func_001C2290(5, 0.8f);

            if (!GET_BIT(D_1D31650, 7)) {
                SET_BIT(D_1D31650, 7);
            }

            if (!GET_BIT(D_1D31784, 15)) {
                SET_BIT(D_1D31784, 15);
            }

            UNSET_BIT(D_1D31650, 8);
            func_00190A20(0);

            return 1;
    }

    return 0;
}

int func_01F6FB30_mall_f_01() {
    int ret = 0;

    if (!GET_BIT(D_1D31650, 13)) {
        D_01F72B90_mall_f_01 = 0.0f;
        D_01F72B88_mall_f_01 = 0;
        func_0016C3C0();
        SET_BIT(D_1D31650, 13);
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(19033, 1.0f, 0.0f);
    }

    D_01F72B90_mall_f_01 += shGetDT();

    switch (D_01F72B88_mall_f_01) {
        case 0:
            if (D_01F72B90_mall_f_01 < 0.5f) {
                return 0;
            }

            SeCall(19032, 1.0f, 0.0f);
            D_01F72B88_mall_f_01++;
            /* fallthrough */
        case 1:
            if (D_01F72B90_mall_f_01 < 1.5f) {
                return 0;
            }

            func_0016C1B0();
            D_01F72B88_mall_f_01++;
            break;
        default:
            ret = 1;
            UNSET_BIT(D_1D31650, 13);
    }

    return ret;
}

int func_01F6FCB0_mall_f_01() {
    sceVu0FVECTOR sp10;

    sp10 = D_01F72AB0_mall_f_01;
    func_002A2E70(&sp10);
    SET_BIT(D_1D3164C, 26);

    return 1;
}

int func_01F6FD00_mall_f_01() {
    int var_a0;
    int var_a1;

    func_0012CFA0();

    if (!func_0012D080()) {
        func_00190A20(2);
    }

    func_0012CFC0();

    if (GET_BIT(D_1D31650, 10) && GET_BIT(D_1D31650, 11)) {
        var_a0 = 214;
        var_a1 = 58;
    } else {
        var_a0 = 215;
        var_a1 = 57;
    }

    if (!func_0016BED0(var_a0, var_a1)) {
        return 0;
    }

    func_00190A20(0);

    return 1;
}

int func_01F6FDA0_mall_f_01() {
    if (!GET_BIT(D_1D31650, 22)) {
        D_01F72BA8_mall_f_01 = 0;
        SET_BIT(D_1D31650, 22);
        func_001C2290(3, 0.5f);
        func_0016C1A0();
        func_00190A20(2);
    }

    switch (D_01F72BA8_mall_f_01) {
        case 0:
            if (!func_001C2580(2)) {
                return 0;
            }

            SeCall(19009, 1.0f, 0.0f);
            func_0016C1B0();
            SET_BIT(D_1D3164C, 30);
            func_001C2290(5, 0.5f);
            D_01F72BA8_mall_f_01++;
            /* fallthrough */
        default:
            if (!func_0016C1C0(76)) {
                return 0;
            }

            UNSET_BIT(D_1D31650, 22);
            func_00190A20(0);

            return 1;
    }
}

int func_01F6FED0_mall_f_01() {
    if (!GET_BIT(D_1D31650, 22)) {
        D_01F72BA0_mall_f_01 = 0;
        D_01F72B98_mall_f_01 = 0;
        SET_BIT(D_1D31650, 22);
        func_001C2290(3, 0.5f);
        func_0016C1A0();
        func_00190A20(2);
        SeCall(19009, 1.0f, 0.0f);
    }

    if (!D_01F72B98_mall_f_01 && func_0016C1C0(76)) {
        D_01F72B98_mall_f_01++;
    }

    switch (D_01F72BA0_mall_f_01) {
        case 0:
            if (!func_001C2580(2)) {
                return 0;
            }

            D_01F72BA0_mall_f_01++;
            /* fallthrough */
        case 1:
            func_0016C1B0();
            SET_BIT(D_1D3164C, 30);
            func_001C2290(5, 0.5f);
            D_01F72BA0_mall_f_01++;
            /* fallthrough */
        default:
            if (!D_01F72BA0_mall_f_01 || !D_01F72B98_mall_f_01) {
                return 0;
            }

            UNSET_BIT(D_1D31650, 22);
            func_00190A20(0);

            return 1;
    }
}

void func_01F70070_mall_f_01() {
    if (!GET_BIT(D_1D31650, 18)) {
        func_01F70720_mall_f_01();
        SET_BIT(D_1D31650, 18);
    }

    switch (RoomName()) {
        case 12:
            D_01F72BC8_mall_f_01 = 0;
            SET_BIT(D_1D31700, 3);
            break;
        case 17:
            D_01F72BB8_mall_f_01 = 0;
            /* fallthrough */
        case 16:
            break;
        case 15:
            SET_BIT(D_1D31784, 13);
            SET_BIT(D_1D31700, 4);
            break;
        case 18:
            SET_BIT(D_1D31700, 6);
    }
}

#ifdef NON_MATCHING
void func_01F70160_mall_f_01() {
    int sp50[5];
    sceVu0FVECTOR sp70;
    sceVu0FVECTOR sp80;
    sceVu0FVECTOR sp90;
    sceVu0FVECTOR spA0;
    sceVu0FMATRIX* spB0[4];
    sceVu0FMATRIX* spC0[4];
    sceVu0FMATRIX* spD0[4];
    sceVu0FMATRIX* spE0[4];
    sceVu0FMATRIX spF0;
    int sp130[4];
    int var_s0;
    int i;
    D_01F72910_struct* temp_D_01F72910_i;
    int* var_s3;

    switch (RoomName()) {
        case 15:
            if (!GET_BIT(D_1D31650, 9)) {
                func_0016CA40(1);
            }

            if (GET_BIT(D_1D31650, 10)) {
                func_0016CA40(6);

                if (!GET_BIT(D_1D31650, 11)) {
                    func_0016CA40(5);
                }
            } else {
                func_0016CA40(7);
            }

            break;
        case 13:
            if (!GET_BIT(D_1D3164C, 26)) {
                func_01F6FCB0_mall_f_01();
            }

            break;
        case 12:
            if (!GET_BIT(D_1D31644, 9) && !GET_BIT(D_1D31644, 8)) {
                func_0016CA40(1);
            }

            if (!GET_BIT(D_1D31644, 9)) {
                func_0016CA40(2);
            }

            break;
        case 11:
            if (GET_BIT(D_1D3164C, 23) && !GET_BIT(D_1D3164C, 25)) {
                SET_BIT(D_1D316FC, 31);
            } else {
                UNSET_BIT(D_1D316FC, 31);
            }

            if (!GET_BIT(D_1D3164C, 23)) {
                func_0016CA40(2);
            } else if (!GET_BIT(D_1D3164C, 25)) {
                func_0016CA40(1);
            }

            break;
        case 14:
            if (!GET_BIT(D_1D3164C, 30)) {
                func_0016CA40(1);
            } else {
                func_0016CA40(2);
            }

            if (GET_FLAG(D_01D31640, 11) && !func_0019B580(5) && !func_0019B580(2)) {
                sp80 = D_01F72AC0_mall_f_01;
                sp90 = D_01F72AD0_mall_f_01;
                spA0 = D_01F72AE0_mall_f_01;
                func_001B3F30(&sp70);
                sp70[2] = 0.25f;
                sp70[1] = 0.25f;
                sp70[0] = 0.25f;
                func_001B3F20(&sp70);
                func_001C7BC0(&sp80, &sp90, &spA0, 512);
            }

            break;
        case 16:
            var_s0 = GetRiddleLevel();

            if (var_s0 == 2) {
                func_0016CA40(6);
            } else if (var_s0 == 1) {
                func_0016CA40(7);
            }

            if (var_s0 && !GET_BIT(D_1D31650, 6)) {
                SET_BIT(D_1D31700, 7);
            } else {
                UNSET_BIT(D_1D31700, 7);
            }

            if (GET_BIT(D_1D3164C, 31) && GET_BIT(D_1D31650, 0) && GET_BIT(D_1D31650, 1) && GET_BIT(D_1D31650, 2) && GET_BIT(D_1D31650, 3)) {
                UNSET_BIT(D_1D31700, 8);
            } else {
                SET_BIT(D_1D31700, 8);
            }

            sp130[2] = 0;
            var_s3   = &sp130[3];
            sp50[4]  = D_1D318C0 % 16;
            sp50[3]  = (D_1D318C0 >> 4) % 16;
            sp50[2]  = (D_1D318C0 >> 8) % 16;
            sp50[1]  = (D_1D318C0 >> 12) % 16;
            sp50[0]  = (D_1D318C0 >> 16) % 16;
            i        = 0;
            *var_s3  = 0;

            do {
                int j;

                temp_D_01F72910_i = &D_01F72910_mall_f_01[i];

                if (!GET_FLAG(D_01D31640, temp_D_01F72910_i->unk4)) {
                    func_0016CA40(temp_D_01F72910_i->unkC);

                    if (!i || i == 3) {
                        sp130[2]++;
                    } else {
                        (*var_s3)++;
                    }
                }

                j = 0;

                do {
                    if (i + 1 == sp50[j]) {
                        break;
                    }

                    j++;
                } while (j < 5);

                if (j < 5) {
                    D_01F72910_struct* temp_D_01F72910_j = &D_01F72910_mall_f_01[j];
                    var_s0 = temp_D_01F72910_i->unk8;

                    func_0016CBD0(spB0, spC0, temp_D_01F72910_j->unk10);
                    func_001C2A80(var_s0, spB0[0]);
                } else {
                    var_s0 = temp_D_01F72910_i->unk8;

                    func_0016CBD0(spD0, spE0, temp_D_01F72910_i->unk10);
                    shMatrixCopy(&spF0, spD0[0]);
                    spF0[3][1] = 10000.0f;
                    func_001C2A80(var_s0, &spF0);
                }

                i++;
            } while (i < 5);

            if (sp130[2]) {
                clAddDynamicWall(&D_01F72310_mall_f_01);
            }

            if (*var_s3) {
                clAddDynamicWall(&D_01F72400_mall_f_01);
            }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_f_01", func_01F70160_mall_f_01);
#endif

#ifdef NON_MATCHING
void func_01F70720_mall_f_01() {
    int spA0[28];
    u_int* temp_D_01D31640;
    int riddle_level;
    int i;

    D_1D318C0       = 0;
    temp_D_01D31640 = D_01D31640;
    D_1D318C4       = 0;
    D_1D318C8       = 0;
    riddle_level    = GetRiddleLevel();

    if (riddle_level == 2) {
        temp_D_01D31640[162] = 33618;
    } else {
        int var_a1 = 0;

        do {
            spA0[var_a1]     = var_a1;
            spA0[var_a1 + 1] = var_a1 + 1;
            spA0[var_a1 + 2] = var_a1 + 2;
            spA0[var_a1 + 3] = var_a1 + 3;
            spA0[var_a1 + 4] = var_a1 + 4;
            spA0[var_a1 + 5] = var_a1 + 5;
            spA0[var_a1 + 6] = var_a1 + 6;
            spA0[var_a1 + 7] = var_a1 + 7;

            var_a1 += 8;
        } while (var_a1 < 2);

        while (var_a1 < 10) {
            spA0[var_a1] = var_a1;
            var_a1++;
        }

        i = 0;

        do {
            var_a1 = shRandI() % (10 - i);

            temp_D_01D31640[162] <<= 4;
            temp_D_01D31640[162] += spA0[var_a1];

            while (var_a1 < 9 - i) {
                spA0[var_a1] = spA0[var_a1 + 1];
                var_a1++;
            }

            i++;
        } while (i < 4);
    }

    spA0[12] = 0;
    spA0[20] = 0;
    spA0[13] = 0;
    spA0[21] = 0;
    spA0[14] = 0;
    spA0[22] = 0;
    spA0[15] = 0;
    spA0[23] = 0;
    spA0[16] = 0;
    spA0[24] = 0;
    i        = 0;

    do {
        int var_a0;

        if (riddle_level <= 0) {
            var_a0 = i;
        } else {
            var_a0 = shRandI() % 5;

            while (spA0[16 + (var_a0 + 4)]) {
                var_a0++;
                var_a0 %= 5;
            }
        }

        spA0[16 + (var_a0 + 4)] = i + 1;

        if (!riddle_level && D_01F72910_mall_f_01[i].unk0 != 39 && D_01F72910_mall_f_01[i].unk0 != 41) {
            SET_FLAG(D_01D31640, D_01F72910_mall_f_01[i].unk4);
            spA0[8 + (var_a0 + 4)] = i + 1;
        } else {
            spA0[8 + (var_a0 + 4)] = 0;
        }

        i++;
    } while (i < 5);

    temp_D_01D31640[161] <<= 4;
    temp_D_01D31640[161] += spA0[20];

    temp_D_01D31640[160] <<= 4;
    temp_D_01D31640[160] += spA0[12];

    temp_D_01D31640[161] <<= 4;
    temp_D_01D31640[161] += spA0[21];

    temp_D_01D31640[160] <<= 4;
    temp_D_01D31640[160] += spA0[13];

    temp_D_01D31640[161] <<= 4;
    temp_D_01D31640[161] += spA0[22];

    temp_D_01D31640[160] <<= 4;
    temp_D_01D31640[160] += spA0[14];

    temp_D_01D31640[161] <<= 4;
    temp_D_01D31640[161] += spA0[23];

    temp_D_01D31640[160] <<= 4;
    temp_D_01D31640[160] += spA0[15];

    temp_D_01D31640[161] <<= 4;
    temp_D_01D31640[161] += spA0[24];

    temp_D_01D31640[160] <<= 4;
    temp_D_01D31640[160] += spA0[16];

    if (func_00199C70(1) && !GET_BIT(D_1D3164C, 23)) {
        SET_BIT(D_1D3164C, 7);
    }

    if (func_00199C70(2) && !GET_BIT(D_1D31650, 10)) {
        SET_BIT(D_1D31650, 10);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_f_01", func_01F70720_mall_f_01);
#endif
