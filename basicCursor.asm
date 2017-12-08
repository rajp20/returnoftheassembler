//initialize program
Start:
	//load starting cursor (160,120)
	loadi 0 $(reg_0)							//establishes a 0 register
	loadi 0 $(reg_x_coordinate)		//need XOR instruction
	loadi 0 $(reg_y_coordinate)
	loadi 0 $(reg_x_boundary)
	loadi 0 $(reg_y_boundary)
	addi 20	$(reg_x_boundary)
	shlli 3 $(reg_x_boundary)
	mov $(reg_x_boundary) $(reg_x_coordinates)		//loads 160 int x coordinate
	shlli 1 $(reg_x_boundary)
	addi -1 $(reg_x_boundary)						//X Boundary set to 319 (right cursor boundar)
	addi 30 $(reg_y_boundary)
	shlli 2 $(reg_y_boundary)
	mov $(reg_y_boundary) $(reg_y_coordinates)		//loads 120 int y coordinate
	shlli 1 $(reg_x_boundary)
	addi -1 $(reg_x_boundary)						//Y Boundary set to 239 (bottom cursor boundary)		
	jmp	DrawCursor
Idle:
	//check status of io reg
	cmp	$0 $(reg_status)
	jumpe Idle
	jump ProcessMouse

ProccessMouse:
	//if left button clicked jmp to Draw
	cmp $(reg_0) $(left_click_reg)
	jumpne Draw
	cmp $(reg_0) $(right_click_reg)
	jumpne Erase
	jump RemoveCursor

RemoveCursor:
	store $(prev_center) $(current_addr)
	store $(prev_up) $(up_addr)
	store $(prev_right) $(right_addr)
	store $(prev_down) $(down_addr)
	store $(prev_left) $(left_addr)
	jump MoveCursor

DrawCursor:
	//read that pixel color address into register (prev_color)
	aadr $(reg_x_coordinate) $(reg_y_coordinate)				//SPECIAL INSTRUCTION
	load $(current_addr) $(prev_center)
	load $(up_addr) $(prev_up)
	load $(right_address) $(prev_right)
	load $(down_addr) $(prev_down)
	load $(left_addr) $(prev_left)
	store $(cursor_color) $(current_addr)
	store $(cursor_color) $(up_addr)
	store $(cursor_color) $(right_addr)
	store $(cursor_color) $(down_addr)
	store $(cursor_color) $(left_addr)
	loadi 0 $(reg_status)
	jump Idle

MoveCursor:
	move $(x_data) $(reg_a)
	move $(y_data) $(reg_b)
	shrli 4 $(reg_a)
	addi 1 $(reg_a)
	shrli 4 $(reg_b)
	addi 1 $(reg_b)
	add $(reg_a) $(reg_x_coordinate)
	add $(reg_b) $(rerg_y_coordinate)
	cmp $(reg_0) $(reg_x_coordinate)
	jumpg MinXSat
	loadi 1 $(reg_x_coordinate)
MinXSat:
	cmp $(reg_x_boundary) $(reg_x_coordinate)
	jumpl MaxXSat
	mov $(reg_x_boundary) $(reg_x_coordinate)
	addi -1 $(reg_x_coordinate)
MaxXsat:
	cmp $(reg_0) $(reg_y_coordinate)
	jumpg MinYSat
	loadi 1 $(reg_y_coordinate)
MinYSat:
	cmp $(reg_y_boundary) $(reg_y_coordinate)
	jumpl MaxYSat
	mov $(reg_y_boundary) $(reg_y_coordinate)
	addi -1 $(reg_y_coordinate)
MaxYsat:
	jump DrawCursor





	