Start:
    loadi 0, $r1
    loadi 25, $r2
    loadi 4, $r5
    shlli 4, $r5
    addi 1, $r5
    loadi 0, $lr0
    loadi 0, $r6
    loadi 7, $r7
    shlli 10, $r7	
Loop:
    addi 1, $r6
    cmp $r6, $r7
    jumpne Loop
    store $r5, $lr0
    addi 1, $r5
    addi 1, $r1
    cmp $r1, $r2
    jumpne Loop
    jump ResetLoop
ResetLoop:
    loadi 0, $r1
    loadi 0, $r6
    addi -25, $r5
    jump Loop
