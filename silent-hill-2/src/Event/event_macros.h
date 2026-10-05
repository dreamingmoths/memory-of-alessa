#ifndef SH2_EVENT_MACROS_H
#define SH2_EVENT_MACROS_H

/**
 * Sets the event main step and resets exec, program, and subroutine steps.
 */
#define EV_MAIN_STEP(m_step)         \
do {                                 \
    ev_m_step = m_step;              \
    ev_e_step = 0;                   \
    ev_p_step = 0;                   \
    ev_s_step = 0;                   \
} while (0)

/**
 * Sets the event exec step and resets program and subroutine steps.
 */
#define EV_EXEC_STEP(e_step)         \
do {                                 \
    ev_e_step = e_step;              \
    ev_p_step = 0;                   \
    ev_s_step = 0;                   \
} while (0)

/**
 * Sets the program step and resets the subroutine step.
 */
#define EV_PROG_STEP(p_step)         \
do {                                 \
    ev_p_step = p_step;              \
    ev_s_step = 0;                   \
} while (0)

/**
 * Sets only the event subroutine step.
 */
#define EV_SUB_STEP(s_step)          \
do {                                 \
    ev_s_step = s_step;              \
} while (0)

/* flag bit indices used by `GET_GAME_FLAG`/`SET_GAME_FLAG`/`UNSET_GAME_FLAG` */
#define GAME_FLAG_7    7
#define GAME_FLAG_8    8
#define GAME_FLAG_9    9
#define GAME_FLAG_10   10
#define GAME_FLAG_11   11
#define GAME_FLAG_13   13
#define GAME_FLAG_15   15
#define GAME_FLAG_16   16
#define GAME_FLAG_17   17
#define GAME_FLAG_18   18
#define GAME_FLAG_19   19
#define GAME_FLAG_24   24
#define GAME_FLAG_25   25
#define GAME_FLAG_26   26
#define GAME_FLAG_32   32
#define GAME_FLAG_33   33
#define GAME_FLAG_36   36
#define GAME_FLAG_36   36
#define GAME_FLAG_39   39
#define GAME_FLAG_41   41
#define GAME_FLAG_43   43
#define GAME_FLAG_43   43
#define GAME_FLAG_47   47
#define GAME_FLAG_49   49
#define GAME_FLAG_50   50
#define GAME_FLAG_51   51
#define GAME_FLAG_52   52
#define GAME_FLAG_53   53
#define GAME_FLAG_54   54
#define GAME_FLAG_55   55
#define GAME_FLAG_56   56
#define GAME_FLAG_57   57
#define GAME_FLAG_58   58
#define GAME_FLAG_59   59
#define GAME_FLAG_62   62
#define GAME_FLAG_66   66
#define GAME_FLAG_67   67
#define GAME_FLAG_68   68
#define GAME_FLAG_69   69
#define GAME_FLAG_69   69
#define GAME_FLAG_70   70
#define GAME_FLAG_70   70
#define GAME_FLAG_71   71
#define GAME_FLAG_72   72
#define GAME_FLAG_82   82
#define GAME_FLAG_84   84
#define GAME_FLAG_85   85
#define GAME_FLAG_85   85
#define GAME_FLAG_87   87
#define GAME_FLAG_88   88
#define GAME_FLAG_91   91
#define GAME_FLAG_95   95
#define GAME_FLAG_96   96
#define GAME_FLAG_97   97
#define GAME_FLAG_103  103
#define GAME_FLAG_108  108
#define GAME_FLAG_109  109
#define GAME_FLAG_109  109
#define GAME_FLAG_117  117
#define GAME_FLAG_120  120
#define GAME_FLAG_121  121
#define GAME_FLAG_122  122
#define GAME_FLAG_123  123
#define GAME_FLAG_124  124
#define GAME_FLAG_125  125
#define GAME_FLAG_126  126
#define GAME_FLAG_128  128 
#define GAME_FLAG_129  129
#define GAME_FLAG_130  130
#define GAME_FLAG_131  131
#define GAME_FLAG_132  132
#define GAME_FLAG_138  138
#define GAME_FLAG_139  139
#define GAME_FLAG_140  140
#define GAME_FLAG_141  141
#define GAME_FLAG_142  142
#define GAME_FLAG_146  146
#define GAME_FLAG_147  147
#define GAME_FLAG_148  148
#define GAME_FLAG_150  150
#define GAME_FLAG_152  152
#define GAME_FLAG_152  152
#define GAME_FLAG_153  153
#define GAME_FLAG_154  154
#define GAME_FLAG_157  157
#define GAME_FLAG_162  162
#define GAME_FLAG_162  162
#define GAME_FLAG_163  163
#define GAME_FLAG_168  168
#define GAME_FLAG_171  171
#define GAME_FLAG_192  192
#define GAME_FLAG_193  193
#define GAME_FLAG_194  194
#define GAME_FLAG_197  197
#define GAME_FLAG_227  227
#define GAME_FLAG_228  228
#define GAME_FLAG_240  240
#define GAME_FLAG_251  251
#define GAME_FLAG_272  272
#define GAME_FLAG_317  317
#define GAME_FLAG_318  318
#define GAME_FLAG_319  319
#define GAME_FLAG_319  319
#define GAME_FLAG_320  320
#define GAME_FLAG_321  321
#define GAME_FLAG_322  322
#define GAME_FLAG_323  323
#define GAME_FLAG_324  324
#define GAME_FLAG_368  368
#define GAME_FLAG_379  379
#define GAME_FLAG_380  380
#define GAME_FLAG_406  406
#define GAME_FLAG_472  472
#define GAME_FLAG_501  501
#define GAME_FLAG_502  502
#define GAME_FLAG_503  503
#define GAME_FLAG_506  506
#define GAME_FLAG_508  508
#define GAME_FLAG_517  517
#define GAME_FLAG_518  518
#define GAME_FLAG_543  543
#define GAME_FLAG_607  607
#define GAME_FLAG_609  609
#define GAME_FLAG_610  610
#define GAME_FLAG_611  611
#define GAME_FLAG_1266 1266
#define GAME_FLAG_1268 1268
#define GAME_FLAG_1269 1269
#define GAME_FLAG_1276 1276
#define GAME_FLAG_1295 1295
#define GAME_FLAG_1302 1302
#define GAME_FLAG_1303 1303
#define GAME_FLAG_1322 1322

#define GET_GAME_FLAG(index) ((game_flag.flag[(index) >> 5] >> ((index) & 0x1F)) & 1)
#define SET_GAME_FLAG(index) ((game_flag.flag[(index) >> 5] |= (1 << ((index) & 0x1F))))
#define UNSET_GAME_FLAG(index) ((game_flag.flag[(index) >> 5] &= ~(1 << ((index) & 0x1F))))

#define GET_ENEMY_FLAG(index) ((game_flag.enemy[(index) >> 5] >> ((index) & 0x1F)) & 1)
#define SET_ENEMY_FLAG(index) ((game_flag.enemy[(index) >> 5] |= (1 << ((index) & 0x1F))))

#define CLEAR_END_KIND_0 0
#define CLEAR_END_KIND_1 1
#define CLEAR_END_KIND_2 2
#define CLEAR_END_KIND_3 3
#define CLEAR_END_KIND_4 4
#define CLEAR_END_KIND_5 5
#define CLEAR_END_KIND_6 6
#define CLEAR_END_KIND_7 7

#endif // SH2_EVENT_MACROS_H
