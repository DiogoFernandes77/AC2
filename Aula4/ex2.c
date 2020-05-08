#include <detpic32.h>

    void delay(int ms){
	int i;
	 for(i = ms; i>=0;i--){
	    resetCoreTimer();
	    while(readCoreTimer()<20000);
		}
	}


    void main(void)    {
	
      LATE = (LATE & 0x00f0);
      
      TRISE = (TRISE & 0x00f0);
      

       while(1)      {
        delay(250);         // half period = 0.5s
        LATEbits.LATE0 = !LATEbits.LATE0;
	delay(250);  	
	LATEbits.LATE1 = !LATEbits.LATE1;
	delay(250);  	
	LATEbits.LATE2 = !LATEbits.LATE2;
	delay(250);          
	LATEbits.LATE3 = !LATEbits.LATE3;
	}
	  
	} 
