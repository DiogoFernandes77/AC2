#include <detpic32.h>
#include "send2displays.c"
#include "toBcd.c"
int duty;
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

void _int_(24) isr_uart1(void){
 
 if((getc() == '+') & (duty < 95)){ 
     duty = duty + 5;
    
     OC1RS = ((PR2 + 1) * duty)/100;
 } if((getc() == '-') &( duty > 5)){ 
     duty = duty - 5;
   
     OC1RS = ((PR2 + 1) * duty)/100;
 }
  IFS0bits.U1RXIF = 0;
 
 } 



int main(void){

   U1MODEbits.BRGH = 0; // x16
   U1BRG = ((20000000+8*19200)/(16*19200))-1;
   U1MODEbits.PDSEL = 01;
   U1MODEbits.STSEL = 1;
   U1STAbits.UTXEN = 1;
   U1STAbits.URXEN = 1;
   

   U1STAbits.URXISEL = 0; // interrupt quando recebe um caracter
   
   
   IPC6bits.U1IP = 2; //prioridade
   IFS0bits.U1RXIF = 0; //flag clear
   IEC0bits.U1RXIE = 1; //enable
   
   U1MODEbits.ON = 1;
 
   EnableInterrupts();
   
   T2CONbits.TCKPS = 2; //pre-scaler 4
   PR2 = 49999;
   TMR2 = 0; //reset
   T2CONbits.TON=1;
   duty =  50;
   OC1RS = ((PR2 + 1) * duty)/100;
   OC1CONbits.OCM = 6;
   OC1CONbits.OCTSEL = 0;
   
 
   OC1CONbits.ON = 1;
   
while(1){
  char dezenas =  (duty/10) +'0';
  char unidades =  (duty % 10) + '0';
  putc(dezenas);
  putc(unidades);
  

  putc('\n');
  
  delay(100);
  
  send2displays(toBcd(duty));
  

}
   
}
