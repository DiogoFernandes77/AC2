#include<detpic32.h>

void putc(char byte){

	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte;
	}

char getc(void){
	while(U1STAbits.URXDA == 0);
	return U1RXREG;

}


void _int_(24) isr_u1(void){

	putc(getc());

	IFS0bits.U1RXIF = 0;
}


int main(void){
	
	U1MODEbits.BRGH = 0; //16
	U1BRG = ((20000000 + 8 *115200) / (16 * 115200))-1;
	
	U1MODEbits.PDSEL = 00; // no parity
	U1MODEbits.STSEL = 0; //1 stop bit
	
	U1STAbits.URXISEL = 00;
	
	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;
	U1MODEbits.ON = 1;
	
	IPC6bits.U1IP = 2;//prioridade
	IFS0bits.U1RXIF = 0; //reset flag
	IEC0bits.U1RXIE = 1; 
	
	PR2 = 49999;
	
	OC1RS = ((PR2+1)*50) / 100;	
	EnableInterrupts();
	





	while(1);
	}
