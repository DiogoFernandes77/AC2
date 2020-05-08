#include <detpic32.h>


void delay(int ms){
   for(;ms >0;ms--){
      resetCoreTimer();
      while(readCoreTimer()< 20000);
   }
}

void putc(char byte2send){
   
   while(U1STAbits.UTXBF == 1);
   U1TXREG = byte2send;

}
int main(void){

   U1MODEbits.BRGH = 0; // 
   U1BRG = 10; // 
   U1MODEbits.STSEL = 0;
   U1MODEbits.PDSEL = 00;
   U1STAbits.UTXEN = 1;
   U1STAbits.URXEN = 1;
   U1MODEbits.ON = 1;

   char *str = "String de teste\n";
   char *s=str;
while(1){
   str = s;
   while(*str != '\n'){
      putc(*str);
       str++;  
   }
	
delay(400);
}
}
