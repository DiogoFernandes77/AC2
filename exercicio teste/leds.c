#include<detpic32.h>

void delay(int ms){
   for(;ms >0;ms--){
      resetCoreTimer();
      while(readCoreTimer()< 20000);
   }
}



int main(void){

	TRISEbits.TRISE0 = 0;
	TRISEbits.TRISE1 = 0;
	
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB3 = 1;


    int valor;
	while(1){
		valor =  PORTBbits.RB1;
		
		LATEbits.LATE0 = valor;
		LATEbits.LATE1 = valor;
		printInt10(valor);
		
		
	
	}
	




}
