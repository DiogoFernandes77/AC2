        .equ    READ_CORE_TIMER,11
	.equ    RESET_CORE_TIMER,12
	
	.data
	.text
	.globl main
main:
for:
	ble $a0,0,endfor	
	li $v0,RESET_CORE_TIMER
	syscall
	
while:
	li $v0,READ_CORE_TIMER
	syscall
	
	ble $v0, 20000,while
	
	addi $a0,$a0,-1

	j  for
endfor:

	jr $ra
