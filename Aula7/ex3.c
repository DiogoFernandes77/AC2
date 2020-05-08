#include <detpic32.h>
static int tmp = 0;
void _int_(12) isr_T3(void){      
        if(tmp == 0){ 
	  putChar('.');
	  tmp = 1;		
	}else{
	tmp = 0;
	}
	 
	IFS0bits.T3IF = 0;   
    

 }



int main(void)    {     // Configure Timer T3 (2 Hz with interrupts disabled)
     T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
     PR3 = 39063;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
     TMR3 = 0;            // Reset timer T2 count register
     T3CONbits.TON = 1;   // Enable timer T2 (must be the last 
      
	IPC3bits.T3IP = 2;    //prioridade 
        IEC0bits.T3IE = 1;   // Enable timer T2 interrupts
        IFS0bits.T3IF = 0;   // Reset timer T2 interrupt flag
	 EnableInterrupts();

  while(1)       { 
          
  } 
  return 0;    
} 
