#include <detpic32.h>
void delay(int ms){
	int i;
	 for(i = ms; i>=0;i--){
	    resetCoreTimer();
	    while(readCoreTimer()<20000);
		}
	}
int main(void){

	TRISBbits.TRISB4 = 1; // entrada digital desconectada
	AD1PCFGbits.PCFG4 = 0;// configuraçao de rb4 como entrada analogica
	AD1CON1bits.SSRC = 7; 
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16; 

	AD1CHSbits.CH0SA =4; //entrada 4 do ADC
	AD1CON2bits.SMPI = 1; // 1 conversao consecutiva
	
	AD1CON1bits.ON = 1;
	while(1){
	AD1CON1bits.ASAM = 1; 
	while(IFS1bits.AD1IF == 0);
	
		
	
	 printInt(ADC1BUF0, 16 | 3 << 16);
	
	 delay(100);
	putChar(' ');
	}




}
