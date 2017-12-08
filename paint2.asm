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
	addi -3 $r1						
	addi 30 $r2
	shlli 2 $r2
	mov $r2 $r6
	shlli 1 $r2
	addi -1 $r2
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
	jump RemoveCursor
ProcessMouse:
	cmp $r0 $left_click
	jumpne Draw
	cmp $r0 $right_click
	jumpne Erase
	jump RemoveCursor
RemoveCursor:
	store $r15 $lr4
	store $r14 $lr3
	store $r13 $lr2
	store $r12 $lr1
	store $r11 $lr0
ExtractAddress:
	addr $r5 $r6
	mov $lr4 $lr0
	addr $r5 $r7
	mov $lr4 $lr1
	addr $r8 $r6
	mov $lr4 $lr2
	addr $r5 $r9
	mov $lr4 $lr3
	addr $r10 $r6
	cmp $r0 $left_click
	jumpne Draw
	cmp $r0 $right_click
	jumpne Erase
	jump MoveCursor
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
	mov $r11 $r16
	incrsr $r16 $r5
	store $r16 $lr0
	load $lr1 $r12
	mov $r12 $r16
	incrsr $r16 $r5
	store $r16 $lr1
	load $lr2 $r13
	mov $r13 $r16
	incrsr $r16 $r8
	store $r16 $lr2
	load $lr3 $r14
	mov $r14 $r16
	incrsr $r16 $r5	
	store $r16 $lr3
	load $lr4 $r15
	mov $r15 $r16
	incrsr $r16 $r10
	store $r16 $lr4
	loadi 0 $read_data
	jump Idle
MoveCursor:
	mov $x $r3
	mov $y $r4
	shrli 2 $r3
	shrli 2 $r4
	add $r3 $r5
	sub $r4 $r6
	cmp $r0 $left_click
	jumpe NoDraw
	cmp $r0 $right_click
	jumpe NoDraw
	loadi 20 $r17
	cmp $r17 $r5
	jumpg MinXSat
	loadi 21 $r5
	jump MinXSat
NoDraw:
	cmp $r0 $r5
	jumpg MinXSat
	loadi 1 $r5
MinXSat:
	cmp $r1 $r5
	jumpl MaxXSat
	mov $r1 $r5
	addi -3 $r5
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
Draw:
	loadi 22 $r17
	cmp $r17 $r5
	jumpl MoveCursor
	mov $r11 $r16
	indraw $r16 $r5
	store $r16 $lr0
	load $lr1 $r12
	mov $r12 $r16
	indraw $r16 $r5
	store $r16 $lr1
	load $lr2 $r13
	mov $r13 $r16
	indraw $r16 $r8
	store $r16 $lr2
	load $lr3 $r14
	mov $r14 $r16
	indraw $r16 $r5	
	store $r16 $lr3
	load $lr4 $r15
	mov $r15 $r16
	indraw $r16 $r10
	store $r16 $lr4
	jump MoveCursor
Erase:
	loadi 22 $r17
	cmp $r17 $r5
	jumpl PickColor
	mov $r11 $r16
	inersr $r16 $r5
	store $r16 $lr0
	load $lr1 $r12
	mov $r12 $r16
	inersr $r16 $r5
	store $r16 $lr1
	load $lr2 $r13
	mov $r13 $r16
	inersr $r16 $r8
	store $r16 $lr2
	load $lr3 $r14
	mov $r14 $r16
	inersr $r16 $r5	
	store $r16 $lr3
	load $lr4 $r15
	mov $r15 $r16
	inersr $r16 $r10
	store $r16 $lr4
    jump MoveCursor
PickColor:
	setcolr $r11 $r5
	loadi 2 $r18
	loadi 18 $r0
SelectouterLoop:
	loadi 2 $r17
SelectinnerLoop:
	addr $r17 $r18
	load $lr4 $r7
	indraw $r7 $r17
	store $r16 $lr4
	addi 1 $r17
	cmp $r0 $r17
	jumpne SelectinnerLoop
	addi 1 $r18
	cmp $r0 $r18
	jumpne SelectouterLoop
	loadi 0 $r0
	jump MoveCursor
