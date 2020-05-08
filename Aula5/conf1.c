# include <detpic32.h>

int delay (int ms){
	for(; ms > 0; ms--){
	resetCoreTimer();
	while(readCoreTimer() < 20000);	
	}

}	

void send2displays(unsigned char value){
	static const char displaycode[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
		
	
	LATB = (LATB & 0x00FF);
	TRISB = (TRISB & 0x00FF);
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;

	static char decimalFlag = 0;
	
	int digit_low = value & 0x0F ;
	int digit_high = value >> 4;


	if(decimalFlag == 0){
	LATB = (LATB & 0x00FF) | displaycode[digit_low] << 8;
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 0;
	}else{
	LATB = (LATB & 0x00FF) | displaycode[digit_high] << 8;
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;
	
	}



}

int main(void){


	TRISBbits.TRISB4 = 1;    
	AD1PCFGbits.PCFG4= 0;     
	AD1CON1bits.SSRC = 7;     
	AD1CON1bits.CLRASAM = 1;  	
	AD1CON3bits.SAMC = 16;    
	
	AD1CON2bits.SMPI = 0;  
                             
	AD1CHSbits.CH0SA = 4;

	AD1CON1bits.ON = 1;



	while(1){

		AD1CON1bits.ASAM = 1;   
		
		while( IFS1bits.AD1IF == 0 );
			
		printInt(ADC1BUF0,16 | 3 << 16);	
		delay(100);
		putChar(' ');

		}




}
