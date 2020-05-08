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

void config(int baudrate,char paridade,int stopBits){
   
  
   int BRG = ((20000000 + 8 * baudrate) / (16 * baudrate)) – 1 ;
   U1MODEbits.BRGH = 0; // x16
   U1BRG = BRG; // 
   

   if(paridade == 'N') U1MODEbits.PDSEL = 00;
   if(paridade == 'E') U1MODEbits.PDSEL = 01;
   if(paridade == 'O') U1MODEbits.PDSEL = 10;
   if(stopBits == 1)      U1MODEbits.STSEL = 1;
   else    U1MODEbits.STSEL = 0;

}




int main(void){

   

   
   U1STAbits.UTXEN = 1;
   U1STAbits.URXEN = 1;
   U1MODEbits.ON = 1;

   char *str = "String de teste\n";

while(1){
   
   while(*str != '\n'){
      putc(*str);
       str++;  
   
	}
	}
delay(400);
}
