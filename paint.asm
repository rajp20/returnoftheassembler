//initialize program
Start:

	//load starting cursor (160,120)
	//read that pixel reg index into register (prev_color)
	//store cursor color index into that address
	//store x,y boundary (320, 240)



Idle:
	//check status of io reg
	cmp	$0 $status reg
	jumpe Idle
	jump ProcessMouse


ProcessMouse:
	//grab mouse data into registers
	grabMouse (special instruction){
	(x_v)-> $(reg_a)
	(y_v)-> $(reg_b)
	(x_s)-> $(reg_c)
	(y_s)-> $(reg_d)
	(leftClick)->(reg_e)
	(rightClick)->(reg_f) 
	}
	//convert x_v & y_v to pixel coordinate adjustment
	shrli 4 $(register_a)
	addi 1 $(register_a)
	shrli 4 $(register_b)
	addi 1 $(register_b)
	//if left button clicked jmp to Draw
	cmp $0 $(register_e)
	jumpne Draw
	jump MoveCursor

MoveCursor:
	//draw in previous color
	store $(prev_color index) $(prev_address)

	//move cursor
	cmp $0 $(reg_c)
	jmpne MoveNegX
	add $(reg_a) $(current_x_reg)	//positive x_v
	cmp $0 $(reg_d)
	jumpn MoveNegY
	add $(reg_b) $(current_y_reg)	//positive y_v
	jump DrawCursor
MoveNegY:
	sub $(reg_b) $(current_y_reg)	//negative y_v
	jump DrawCursor

MoveNegX:
	sub $(reg_a) $(current_x_reg)	//negative x_v
	cmp $0 $(reg_d)
	jumpne MoveNegY
	add $(reg_b) $(current_y_reg)	//positive y_v
	jump DrawCursor

Drawcursor:
	//read current x,y pixel reg index into register (prev_color)
	//store that addres into current address register
	//draw cursor color into current x,y
	jump idle


Draw:
	store $(selected_color_reg)	$(current_address)
	cmp $0 $(reg_c)
	jmpne DrawNegX
	cmp $0 $(reg_d)
	jumpne DrawNegYOnly
DrawBothPositive:
	cmp $0 $(reg_a)
	jumpe DrawXDone 				//x is up to date
	addi 1 $(current_x_reg)
	addi -1 (reg_a)
	cmp $0 $(reg_b)
	jumpe DrawYDone					//y is up to date
	addi 1 $(current_y_reg)
	addi -1 (reg_b)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y
	jump DrawBothPositive

DrawPosXDone:				//positive Y
	cmp $0 $(reg_b)
	jumpe DrawDone
	addi 1 $(current_y_reg)
	addi -1 (reg_b)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y
	jump DrawXDone	

DrawPosYDone:				//positive X
	cmp $0 $(reg_a)
	jumpe DrawDone
	addi 1 $(current_x_reg)
	addi -1 (reg_a)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y SPECIAL INSTRUCTION?
	jump DrawYDone

DrawDone:
	jump DrawCursor


DrawNegX:
	cmp $0 $(reg_d)
	jumpne DrawBothNeg
DrawNegXOnly:						//neg x, pos y
	cmp $0 $(reg_a)
	jumpe DrawPosXDone				//x is up to date
	addi -1 $(current_x_reg)
	addi -1 (reg_a)
	cmp $0 $(reg_b)
	jump DrawNegYDone				//y is up to date
	addi 1 $(current_y_reg)
	addi -1 (reg_b)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y SPECIAL INSTRUCTION?
	jump DrawNegXOnly

DrawBothNeg:
	cmp $0 $(reg_a)
	jumpe DrawNegXDone 				//x is up to date
	addi -1 $(current_x_reg)
	addi -1 (reg_a)
	cmp $0 $(reg_b)
	jumpe DrawNegYDone				//y is up to date
	addi -1 $(current_y_reg)
	addi -1 (reg_b)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y SPECIAL INSTRUCTION?
	jump DrawBothPositive

DrawNegXDone:						//Negative Y
	cmp $0 $(reg_b)
	jumpe DrawDone
	addi -1 $(current_y_reg)
	addi -1 (reg_b)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y SPECIAL INSTRUCTION?
	jump DrawXDone	

DrawNegYDone:						//Negative X
	cmp $0 $(reg_a)
	jumpe DrawDone
	addi -1 $(current_x_reg)
	addi -1 (reg_a)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y SPECIAL INSTRUCTION?
	jump DrawYDone


DrawNegYOnly:						//pos x, neg y
	cmp $0 $(reg_a)
	jumpe DrawNegXDone				//x is up to date
	addi 1 $(current_x_reg)
	addi -1 (reg_a)
	cmp $0 $(reg_b)
	jumpe DrawPosYDone				//y is up to date
	addi -1 $(current_y_reg)
	addi -1 (reg_b)
	store $(selected_color_reg)	$(current_address)
	//update address with new x,y SPECIAL INSTRUCTION?
	jump DrawNegYOnly


