#include <detpic32.h>
#include "delay.c"
#include "send2displays.c"
#include "toBcd.c"
volatile unsigned char voltage = 0;   // Global variable
// Interrupt Handler    
void _int_(27) isr_adc(void)  // Replace VECTOR by the A/D vector    // number - see "PIC32 family data   // sheet" (pages 74-76)    
{      
	int media = 0;
			int v;
			int *p = (int *)(&ADC1BUF0); 
			int i;			
			for( i = 0; i < 8; i++ ) {

			 v=(p[i*4]*33+511)/1023;
			media += v;
			}	
			media = media/8;
			voltage = toBcd( media);				
	



	//printInt(ADC1BUF0, 16 | 3 << 16);// Hexadecimal (3 digits format)
	
	
	
	
	IFS1bits.AD1IF = 0; 
        // Reset AD1IF flag    
}







 int main(void)    {      
	unsigned int cnt = 0; 

	TRISBbits.TRISB4 = 1; // entrada digital desconectada
	AD1PCFGbits.PCFG4 = 0;// configuraçao de rb4 como entrada analogica
	AD1CON1bits.SSRC = 7; 
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16; 

	AD1CHSbits.CH0SA =4; //entrada 4 do ADC
	AD1CON2bits.SMPI = 7; // 1 conversao consecutiva
	AD1CON1bits.ON = 1;
	
	
	IPC6bits.AD1IP = 2;  // configure priority of A/D interrupts 

	IFS1bits.AD1IF = 0;  // clear A/D interrupt flag
	
	IEC1bits.AD1IE = 1;  // enable A/D interrupts 
 

	EnableInterrupts(); 

	

	
while(1) {
	 if(cnt % 25 == 0)   // 250 ms (4 samples/second)          
	 { 
           
	 AD1CON1bits.ASAM = 1;
	 // Start A/D conversion          
	

	}          // Send "voltage" variable to displays  
	send2displays(voltage,1);        
	cnt++;     









	delay(10);


     // Wait 10 ms 
	}                   
return 0;
}
