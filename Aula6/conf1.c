#include <detpic32.h>
#include "toBcd.c"
volatile unsigned char voltage = 0;
void delay(int ms){
	for(; ms > 0; ms--){
	resetCoreTimer();
	while(readCoreTimer() <20000);}


	}
void send2displays(unsigned char value){
	static const char code[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char decimalFlag = 0;



	TRISB = TRISB & 0x00FF;
	TRISDbits.TRISD5=0;
	TRISDbits.TRISD6 = 0;
	int digit_low = value & 0x0F;
	int digit_high = value >> 4;
		

	if(decimalFlag == 0){
	LATB = (LATB & 0x00FF) | code[digit_low]<< 8;
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 0;
	}else{
	LATB = (LATB & 0x00FF) | code[digit_high] << 8;
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;
	}
	
	decimalFlag = !decimalFlag;
}



void _int_(27) isr_adc(void){

	int *p = (int *) (&ADC1BUF0);
	int i;
	int media = 0;
	int v = 0;
	for( i = 0; i < 8; i++ ) {

			 v=(p[i*4]*33+511)/1023;
			media += v;
			}	
			

		media = media/8;
			voltage = toBcd( media);
	





	IFS1bits.AD1IF = 0; 



}


int main(void){

	int cnt = 0;
	TRISBbits.TRISB4 = 1;    
	AD1PCFGbits.PCFG4= 0;     
	AD1CON1bits.SSRC = 7;     
	AD1CON1bits.CLRASAM = 1;  	
	AD1CON3bits.SAMC = 16;    
	
	AD1CON2bits.SMPI = 7;  
                             
	AD1CHSbits.CH0SA = 4;

	AD1CON1bits.ON = 1;

	IPC6bits.AD1IP = 2;  // configure priority of A/D interrupts 
	IFS1bits.AD1IF = 0;  // clear A/D interrupt flag 
	IEC1bits.AD1IE = 1;  // enable A/D interrupts 
	
	
	EnableInterrupts();	
	
	
	while(1){
	if(cnt % 25 == 0){		
		

		AD1CON1bits.ASAM = 1;
			 }
	
	
	send2displays(voltage);
	delay(10);



		}

}
