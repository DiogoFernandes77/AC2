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

main:
	lui $t1,SFR_BASE_HI
	
	lw  $t2,TRISE($t1)
	andi $t2, $t2,0xFFFE # saida, bit menos sig  '0'
	sw  $t2, TRISE($t1)

	
	lw  $t4, TRISB($t1)
	ori $t4,$t4,0x0001
	sw  $t4, TRISB($t1)

while:	lw $t5, PORTB($t1)
	andi $t5,$t5,0x01 #fica apenas o bit menos sig do porto de saida(E)
	
	
	lw   $t3, LATE($t1)
	andi $t3,$t3, 0xFFFE # limpa o bit E0
	or   $t3,$t3,$t5
	sw   $t3,LATE($t1)
	
	j while
	jr $ra
