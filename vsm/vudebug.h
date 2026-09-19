; 
; memory of alessa
; debug vu macros
; 

.ifdef DEBUG
.macro BREAKPOINT4 a, b, c, d
NOP[D] \a \b, \c, \d
.endm

.macro BREAKPOINT3 a, b, c
NOP[D] \a \b, \c
.endm

.macro BREAKPOINT2 a, b
NOP[D] \a \b
.endm
.else
.macro BREAKPOINT4 a, b, c, d
NOP \a \b, \c, \d
.endm

.macro BREAKPOINT3 a, b, c
NOP \a \b, \c
.endm

.macro BREAKPOINT2 a, b
NOP \a \b
.endm
.endif
