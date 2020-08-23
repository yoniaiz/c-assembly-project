.extern X
.entry EXTERN
MAIN:   add r3, LIST
LOOP:   prn #48
        lea STR, r6
        mov r3, K
        sub NOT_EXIST, r4
EXTERN: dec X
        bne END
        cmp K, #-6
.entry STR
        add X, X
        bne &END
        dec K
        jmp &LOOP
END:    stop
STR:    .string "abcd"
LIST:   .data 6, -9
        .data -100
K:      .data 31