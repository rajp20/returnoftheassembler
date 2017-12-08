Start:
	loadi 0 $r0		
	loadi 0 $r5
	loadi 0 $r6
	loadi 0 $r1
	loadi 0 $r2
	addi 20 $r1
	shlli 3 $r1
	mov $r1 $r5		
	shlli 1 $r1
	addi -1 $r1						
	addi 30 $r2
	shlli 2 $r2
	mov $r2 $r6
	shlli 1 $r1
	addi -1 $r1
	mov $r6 $r7
	addi -1 $r7
	mov $r5 $r8
	addi 1 $r8
	mov $r6 $r9
	addi 1 $r9
	mov $r5 $r10
	addi -1 $r10	
	jump DrawCursor
Idle:
	cmp $r0 $read_data
	jumpe Idle
	jump ProcessMouse
ProcessMouse:
	cmp $r0 $left_click
	jumpne Draw
	cmp $r0 $right_click
	jumpne Erase
	jump RemovCursor
RemovCursor:
	store $r11 $lr0
	store $r12 $lr1
	store $r13 $lr2
	store $r14 $lr3
	store $r15 $lr4
	jump movCursor
DrawCursor:
	addr $r5 $r6
	mov $lr4 $lr0
	addr $r5 $r7
	mov $lr4 $lr1	
	addr $r8 $r6
	mov $lr4 $lr2
	addr $r5 $r9
	mov $lr4 $lr3
	addr $r10 $r6 	
	load $lr0 $r11
	load $lr1 $r12
	load $lr2 $r13
	load $lr3 $r14
	load $lr4 $r15
	mov $r11 $r16
	incrsr $r16 $r5
	store $r16 $lr0
	mov $r12 $r16
	incrsr $r16 $r5
	store $r16 $lr1
	mov $r13 $r16
	incrsr $r16 $r8
	store $r16 $lr2
	mov $r14 $r16
	incrsr $r16 $r5	
	store $r16 $lr3
	mov $r15 $r16
	incrsr $r16 $r10
	store $r16 $lr4
	loadi 0 $read_data
	jump Idle
movCursor:
	mov $x $r3
	mov $y $r4
	shrli 4 $r3
	addi 1 $r3
	shrli 4 $r4
	addi 1 $r4
	add $r3 $r5
	add $r4 $r6
	cmp $r0 $r5
	jumpg MinXSat
	loadi 1 $r5
MinXSat:
	cmp $r1 $r5
	jumpl MaxXSat
	mov $r1 $r5
	addi -1 $r5
MaxXSat:
	cmp $r0 $r6
	jumpg MinYSat
	loadi 1 $r6
MinYSat:
	cmp $r2 $r6
	jumpl MaxYSat
	mov $r2 $r6
	addi -1 $r6
MaxYSat:
	mov $r6 $r7
	addi -1 $r7
	mov $r5 $r8
	addi 1 $r8
	mov $r6 $r9
	addi 1 $r9
	mov $r5 $r10
	addi -1 $r10
	jump DrawCursor
ExtractAddr:
	addr $r5 $r6
	mov $lr4 $lr0
	addr $r5 $r7
	mov $lr4 $lr1
	addr $r8 $r6
	mov $lr4 $lr2
	addr $r5 $r9
	mov $lr4 $lr3
	addr $r10 $r6
Draw:
    addi 0 $r0
Erase:
	addi 0 $r0
