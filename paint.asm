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
	jump ProcessMouse
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
	shrli 5 $r3
	addi 0 $r3
	shrli 5 $r4
	addi 0 $r4
	add $r3 $r5
	sub $r4 $r6
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
    loadi 20 $r17
	cmp	$r17 $r5
	jumpg ContDraw1:
	jump PickColor
ContDraw1:
	store $r15 $lr4
	store $r14 $lr3
	store $r13 $lr2
	store $r12 $lr1
	mov $r11 $r16
	indraw $r16 $r5
	store $r16 $lr0
	mov $x $r3
	mov $y $r4
	shrli 4 $r3
	shrli 4 $r4
IncrementX:
	cmp $r0 $r3
	jumpg AddX
	cmp $r0 $r3
	jumpl MinusX
	jump XDone
IncrementY:
	cmp $r0 $r4
	jumpg AddY
	cmp $r0 $r4
	jumpl MinusY
	jump YDone
AddX:
	addi 1 $r5
	addi -1 $r3
	jump IncrementY
MinusX:
	addi -1 $r5
	addi 1 $r3
	jump IncrementY
AddY:
	addi -1 $r6
	addi -1 $r4
	jump IncrementX
MinusY:
	addi 1 $r6
	addi 1 $r4
	jump IncrementX
XDone:
	cmp $r0 $r4
	jumpne IncrementY
	mov $r6 $r7
	addi -1 $r7
	mov $r5 $r8
	addi 1 $r8
	mov $r6 $r9
	addi 1 $r9
	mov $r5 $r10
	addi -1 $r10
	jump DrawCursor
YDone:
	cmp $r0 $r3
	jumpne IncrementX
	mov $r6 $r7
	addi -1 $r7
	mov $r5 $r8
	addi 1 $r8
	mov $r6 $r9
	addi 1 $r9
	mov $r5 $r10
	addi -1 $r10
	jump DrawCursor
Erase:
    jump RemoveCursor
PickColor:
	store $r15 $lr4
	store $r14 $lr3
	store $r13 $lr2
	store $r12 $lr1
	store $r11 $lr0
	setcolr $r11 $r5
	jump MoveCursor
