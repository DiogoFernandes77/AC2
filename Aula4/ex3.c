#include <detpic32.h>

    void delay(int ms){
	int i;
	 for(i = ms; i>=0;i--){
	    resetCoreTimer();
	    while(readCoreTimer()<20000);
		}
	}
void main(void){
	

	

	LATB = (LATB & 0x00ff);
	LATDbits.LATD5 = 0; //dysplay low
	LATDbits.LATD6 = 1;
	

	TRISB = (TRISB & 0x00FF);
  	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;	
while(1){
	char c = getChar();
	
	while (c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f' && c != 'g' && c != '.') {
		 c = getChar();
	
	}

	switch (c) {
      case 'a':
        
        LATBbits.LATB8 = 1;
        break;
      case 'b':
      
        LATBbits.LATB9 = 1;
        break;
      case 'c':
      
        LATBbits.LATB10 = 1;
        break;
      case 'd':
      
        LATBbits.LATB11 = 1;
        break;
      case 'e':

        LATBbits.LATB12 = 1;
        break;
      case 'f':
       
        LATBbits.LATB13 = 1;
        break;
      case 'g':
       
        LATBbits.LATB14 = 1;
        break;
      case '.':
       
        LATBbits.LATB15 = 1;
        break;
		}

	delay(500);	
	}
}
