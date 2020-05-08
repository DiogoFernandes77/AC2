#include <detpic32.h>
#include "toBcd.c" 
void delay(int ms){
	for(; ms > 0; ms--){
	resetCoreTimer();
	while(readCoreTimer() < 20000);
	
		}
	}


void displays(unsigned char value){


	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

 	static char displayFlag = 0;
	
	LATB = (LATB & 0x00FF);
	TRISB = (TRISB & 0x00FF);
	
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;

	int digit_low = value & 0x0F;
	int digit_high = value >> 4;

	//send digit to low display
	if(displayFlag == 0){
	LATB = (LATB & 0x00FF) | (display7Scodes[digit_low] << 8) ;
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 0;
		
	}

	//send digit to high display
	
	else{
	LATB = (LATB & 0x00FF) | display7Scodes[digit_high] << 8;
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;

			
	}
	displayFlag = !displayFlag;



}




int main(void){


	while(1){
	char counter = 0;

	while(1) {
		displays(toBcd(counter));
		delay(100);
		displays(toBcd(counter));
		delay(100);		
		counter++;
}

	
	}





}
