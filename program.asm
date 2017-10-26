Start:
setlo A, 0xff   
sethi A, 0xff   
setlo B, 0x00   
sethi B, 0x00   
setlo C, 0x00   
sethi C, 0xE0   
Loop:
loadmem D, B     
storemem D, A   	
setlo D, 0x01   	
sethi D, 0x00 
add A, D        	
add B, D
add C, D
Break:
bim Loop      
setlo B, 0xff	
sethi B, 0xff	
loadmem C, B
Loop2:
storemem C, A  
add B, D  
biz	Start