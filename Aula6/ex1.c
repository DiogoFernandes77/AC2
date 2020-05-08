#include <detpic32.h>
#include "delay.c"
#include "send2displays.c"
#include "toBcd.c"
// Interrupt Handler    
volatile int adc_value;
    void _int_(27) isr_adc(void)    {
       // Reset RE0                 
       // LATE0 = 0
       // Read ADC1BUF0 value to "adc_value"
       // Set RE0
       // LATE0 = 1
       // Start A/D conversion
       IFS1bits.AD1IF = 0;
           // Reset AD1IF flag   
 } 






 int main(void)    {      
	

	TRISBbits.TRISB4 = 1; // entrada digital desconectada
	TRISEbits.TRISE0 = 0;	
	AD1PCFGbits.PCFG4 = 0;// configuraçao de rb4 como entrada analogica
	AD1CON1bits.SSRC = 7; 
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16; 

	AD1CHSbits.CH0SA =4; //entrada 4 do ADC
	AD1CON2bits.SMPI = 1; // 1 conversao consecutiva
	AD1CON1bits.ON = 1;
	
	
	IPC6bits.AD1IP = 2;  // configure priority of A/D interrupts 

	IFS1bits.AD1IF = 0;  // clear A/D interrupt flag
	
	IEC1bits.AD1IE = 1;  // enable A/D interrupts 
 

	EnableInterrupts(); 

	

	AD1CON1bits.ASAM = 1;
while(1) { 
	}                   


 
   return 0;   

 }
