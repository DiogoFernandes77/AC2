	.equ SFR_BASE_HI, 0xBF88
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB,  0x6060
	.equ TRISE, 0x6100
	.equ PORTE, 0x6110
	.equ LATE, 0x6120
	.data
	.text
	.globl main

	.data
	.text
	.globl main
main:	
	lui $t1,SFR_BASE_HI   #0 saida
	
	lw $t2, TRISE($t1)
	andi $t2,$t2,0xFFFE
	sw $t2, TRISE($t1)


	lw $t3, TRISB($t1)	# entrada
	ori $t3,$t3,0x0001
	sw $t3,TRISB($t1)

while:
		
	lw $t4,PORTB($t1)
	andi $t4,$t4,0x01
	
	lw $t5,LATE($t1)
	andi $t5,$t5, 0xFFFE
	or $t5,$t5,$t4
	sw $t5,LATE($t1)
	
	j while

	jr $ra
