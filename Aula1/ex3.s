	.equ getchar,2
	.equ putchar,3

	.data
msg:    .asciiz "Diogo Daniel Nunes Fernandes n:89221 \n"

	.text
	.globl main
main:
	la $a0, msg
	li $v0, 8
	syscall

while:
	li $v0,getchar
	syscall
	beq $v0,0,while
if: 
	beq $v0,'\n',endw
	
	or $a0, $v0, 0
	li $v0, putchar
	syscall
	
	j while

endw:
	ori $v0,$0,0
	jr $ra
