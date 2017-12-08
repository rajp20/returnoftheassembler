Start:
	loadi 25, $r2
	loadi 1, $lr1
	shlli 13, $lr1
ResetPC:
	loadi 0, $lr0
	loadi 4, $r5
	shlli 4, $r5
	addi 1, $r5
	loadi 0, $r1
Loop:
	loadi 5, $r7
	loadi 6, $r8
	cmp $r8, $r7
	jumpg EndLoop
	cmp $lr0, $lr1
	jumpe ResetPC
	store $r5, $lr0
	addi 1, $lr0
	addi 1, $r5
	addi 1, $r1
	cmp $r1, $r2
	jumpne Loop
	jump ResetLoop
ResetLoop:
	loadi 0, $r1
	addi -25, $r5
	jump Loop
EndLoop:
	jump Start
