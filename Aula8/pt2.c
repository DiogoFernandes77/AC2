#include<detpic32.h>

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

char getc(void){
   while(U1STAbits.URXDA == 0);
   return U1RXREG;


}


void _int_(24)isr_uart1(void) {
  putc(getc());

  IFS1bits.U2RXIF = 0;
}
int main(void){
   printStr("Diogo Daniel Nunes Fernandes");

   U1MODEbits.BRGH = 0; // 16
   U1BRG = ( (20000000 + 8*115200) / (16 * 115200) ) - 1;
   U1MODEbits.PDSEL = 00;
   U1MODEbits.STSEL = 0;
   U1STAbits.URXEN = 1;
   U1STAbits.UTXEN = 1;
   U1MODEbits.ON = 1;
  
   U1STAbits.URXISEL = 00;

   IFS0bits.U1RXIF = 0;
   IEC0bits.U1RXIE = 1;
   IPC6bits.U1IP = 2;
  
   EnableInterrupts();

   while(1){
   
   putc('p');
   delay(300);

   }
   
}
