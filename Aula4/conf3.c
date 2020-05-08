#include <detpic32.h>


void delay(int ms){

	for(; ms > 0; ms--){
		resetCoreTimer();
	while(readCoreTimer() < 20000);


	}


}




int main(void){

	unsigned char segment;
	LATB = (LATB & 0x00FF);
	
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;
	
	TRISB = (TRISB & 0x00FF);
	
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	while(1){
		

		LATDbits.LATD5 = !LATDbits.LATD5;
		LATDbits.LATD6 = !LATDbits.LATD6;
		segment = 1;		
		int i = 0;		
		for( i = 0; i < 7; i++){
	
		LATB = (LATB & 0x00FF) | segment << 8;
		

		delay(500);
		segment = segment << 1;


		
	
	



	

		}

	}
return 1;

}
