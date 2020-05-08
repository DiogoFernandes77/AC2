#include <detpic32.h>
void _int_(4) isr_T1(void)       {
          putChar('1');  // print character '1'
          // Reset T1IF flag
	IFS0bits.T1IF = 0;         
	} 

void _int_(12) isr_T3(void)       {
	 putChar('3');         
	IFS0bits.T3IF = 0;   // print character '3'
          // Reset T3IF flag
       } 






int main(void)    {     // Configure Timer T3 (2 Hz with interrupts disabled)
     T3CONbits.TCKPS = 5; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
     PR3 = 62499;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
     TMR3 = 0;            // Reset timer T2 count register
     T3CONbits.TON = 1;   // Enable timer T2 (must be the last 
      
	IPC3bits.T3IP = 2;    //prioridade 
        IEC0bits.T3IE = 1;   // Enable timer T2 interrupts
        IFS0bits.T3IF = 0;   // Reset timer T2 interrupt flag
	
     T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
     PR1 = 39063;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
     TMR1 = 0;            // Reset timer T2 count register
     T1CONbits.TON = 1;   // Enable timer T2 (must be the last 
      
	IPC1bits.T1IP = 2;    //prioridade 
        IEC0bits.T1IE = 1;   // Enable timer T2 interrupts
        IFS0bits.T1IF = 0;   

 EnableInterrupts();

  while(1)       { 
          
  } 
  return 0;    
} 
