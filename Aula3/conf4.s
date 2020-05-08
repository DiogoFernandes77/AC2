		.equ SFR_BASE_HI, 0xBF88
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB,  0x6060
	.equ TRISE, 0x6100
	.equ PORTE, 0x6110
	.equ LATE, 0x6120
          .equ READ_CORE_TIMER, 11
          .equ RESET_CORE_TIMER, 12
          .equ K, 20000

          .data

          .text
          .globl main

main:
	li $t1,SFR_BASE_HI	#saida
	

	lw $t2, TRISE($t1)
	andi $t2,$t2,0xFFF0
	sw $t2,TRISE($t1)

	lw $t3, TRISB($t1)  #entrada
	ori $t3, $t3, 0x000F
	sw $t3,TRISB($t1)



delay:  
	move $t0,$a0   # void delay(int ms)
for:	ble $t0,0,end		
	
	li $v0,RESET_CORE_TIMER
	syscall

while: 
	li $v0,READ_CORE_TIMER
	syscall
	
	blt $v0,20000,while
	
	subu $t0,1
	
	j for
end:
	jr $ra	








