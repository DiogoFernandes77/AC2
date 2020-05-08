#include <detpic32.h>





int main(void)    {     // Configure Timer T3 (2 Hz with interrupts disabled)
     T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
     PR3 = 39063;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
     TMR3 = 0;            // Reset timer T2 count register
     T3CONbits.TON = 1;   // Enable timer T2 (must be the last 


  while(1)       { 
          // Wait until T3IF = 1
  while(IFS0bits.T3IF == 0);      
	
      IFS0bits.T3IF = 0;   // Reset timer T2 interrupt flag // Reset T3IF 
     
 	  
      putChar('.');

} 
  return 0;    
} 
