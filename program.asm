Start:
    loadi 0, $r1
    loadi -1, $r2
Loop:
    addi 1, $r1
    cmp $lr3, $r2
    jumpne Loop
