	.equ inkey,1
	.data
str1:	.asciiz "Key pressed\n"
	.text
	.globl main
main: 
	
while:	
	li $v0,inkey
	syscall

	beq $v0,0,while

if:    
	beq $v0,'\n',endw
	
	la $a0,str1
	li $v0,8
	syscall
	
	j while

endw:	 
	ori $v0, $0, 0	
	jr $ra
	


