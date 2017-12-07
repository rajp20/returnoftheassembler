//initialize program
Start:
	//load starting cursor (160,120)
	xor $(reg_0) $(reg_0)							//establishes a 0 register
	xor $(reg_x_coordinate) $(reg_x_coordinate)		//need XOR instruction
	xor $(reg_y_coordinate) $(reg_y_coordinate)
	xor $(reg_x_boundary) $(reg_x_boundary)
	xor $(reg_y_boundary) $(reg_y_boundary)
	addi 20	$(reg_x_boundary)
	shlli 3 $(reg_x_boundary)
	mov $(reg_x_boundary) $(reg_x_coordinates)		//loads 160 int x coordinate
	shlli 1 $(reg_x_boundary)
	addi -1 $(reg_x_boundary)						//X Boundary set to 319
	addi 30 $(reg_y_boundary)
	shlli 2 $(reg_y_boundary)
	mov $(reg_y_boundary) $(reg_y_coordinates)		//loads 120 int y coordinate
	shlli 1 $(reg_x_boundary)
	addi -1 $(reg_x_boundary)						//Y Boundary set to 239		
	mov $(reg_x_coordinate) $(right_cursor)	//Load current xy into cursor regs
	mov $(reg_x_coordinate) $(left_cursor)
	mov $(reg_y_coordinate) $(up_cursor)
	mov $(reg_y_coordinate) $(down_cursor)
	jmp	DrawCursor

Idle:
	//check status of io reg
	cmp	$0 $(reg_status)
	jumpe Idle
	jump ProcessMouse

ProccessMouse:
	//if left button clicked jmp to Draw
	cmp $(reg_0) $(left_click_reg)
	jumpe MoveCursor
	jump Draw

DrawCursor:
	//read that pixel color address into register (prev_color)
	addr $(reg_x_coordinate) $(reg_y_coordinate)			//SPECIAL INSTRUCTION
	load $(current_address) $(prev_center)
	loadi $(cursor_color) $(current_address)

	addi -1 $(up_cursor)							//fix cursor coordinates
	cmp $(reg_0) $(up_cursor)
	jmpg SkipUp
	addr $(reg_x_coordinate) $(up_cursor)					//SPECIAL INSTRUCTION
	load $(up_address) $(prev_up)
	loadi $(cursor_color) $(up_address)
SkipUp:
	addi 1 $(right_cursor)						//fix cursor coordinates
	cmp $(reg_x_boundary) $(right_cursor)
	jmpg SkipRight
	addr $(right_cursor) $(reg_y_coordinate)				//SPECIAL INSTRUCTION
	load $(right_address) $(prev_right)
	loadi $(cursor_color) $(right_address)
SkipRight:
	addi 1 $(down_cursor)
	cmp $(reg_y_boundary) $(down_cursor)
	jmpg SkipDown
	addr $(reg_x_coordinate) $(down_cursor)					//SPECIAL INSTRUCTION
	load $(down_address) $(prev_down)
	loadi $(cursor_color) $(down_address)
SkipDown:
	addi -1 $(left_cursor)
	cmp $(reg_0) $(left_cursor)
	jmpg Skipleft
	addr $(left_cursor) $(reg_y_coordinate)					//SPECIAL INSTRUCTION
	load $(left_address) $(prev_left)
	loadi $(cursor_color) $(left_address)
SkipLeft:
	//wait
	jmp Idle

MoveCursor:
CheckMaxX:
	add $(x_data)	$(reg_x_coordinate)
	cmp $(reg_x_boundary) $(reg_x_coordinate)
	jmpg OverXBoundary
CheckMinX:
	cmp $(reg_0) $(reg_x_coordinate)
	jmpg UnderXBoundary
CheckMaxX:
	add $(y_data) $(reg_y_coordinate)
	cmp $(reg_y_boundary) $(reg_y_coordinate)
	jmpg OverYBoundary
CheckMinY:
	cmp $(reg_0) $(reg_y_coordinate)
	jmpg UnderYBoundary	
XYSat:
	jmp DrawCursor


	
	

	
	



CursorSat:




	