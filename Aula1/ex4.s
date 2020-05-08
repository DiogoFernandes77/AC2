	.equ print_int10,7
	.equ read_int10,5
	.equ print_str,8
	.equ print_int,6
	
	.data
msg: .asciiz "\nIntroduza um numero (sinal e módulo): "
msg2: .asciiz "\n"
	.text
	.globl main
main:
	la $a0, msg
	li $v0,print_str
	syscall
 	
	li $v0,read_int10
	syscall
	
	or $t0, $v0 ,$0
	
	la $a0, msg2
	li $v0,print_str
	syscall

	move $a0, $t0   //base 2
	li $a1,2
	li $v0, print_int
	syscall

	la $a0, msg2
	li $v0,print_str
	syscall	


	move $a0, $t0  //base 16
	li $a1,16
	li $v0, print_int
	syscall
	

	la $a0, msg2
	li $v0,print_str
	syscall


	move $a0, $t0
	
	li $v0, print_int10
	syscall
	
	la $a0, msg2
	li $v0,print_str
	syscall

	move $a0, $t0
	li $a1,10
	li $v0, print_int
	syscall


	jr $ra
