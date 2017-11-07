Start:
    loadi 0, $r1
    loadi 25, $r2
    loadi 4, $r5
    shrli 3, $r5
    addi 1, $r5
    loadi 0, $lr0
Loop:
    cmp $r1, $r2
    store $r5, $lr0
    addi 1, $r5
    addi 1, $r1
    jumpne Loop
    jump ResetLoop
ResetLoop:
    loadi 0, $r1
    addi -25, $r5
    jump Loop
