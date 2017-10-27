Start:
    loadi 0, $r1
    loadi 15, $r2
Loop:
    addi 1, $r1
    cmp $r1, $r2
    jumpne Loop
