#include<detpic32.h>
#include "send2displays.c"
#include "toBcd.c"


volatile int voltage = 0;
 


int main(void){
    


    TRISBbits.TRISB4 = 1;     // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this
                              //  mode an internal counter ends sampling and
                              //  starts conversion
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter
                              //  interrupt is generated. At the same time,
                              //  hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)

    AD1CON2bits.SMPI = 8-1;  // Interrupt is generated after XX samples
                              //  (replace XX by the desired number of
                              //  consecutive samples)
    AD1CHSbits.CH0SA = 4;     // replace x by the desired input
                               //  analog channel (0 to 15)



    AD1CON1bits.ON = 1;   
    
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;




    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 19530;         // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0;            // Reset timer T3 count register
    T1CONbits.TON = 1;   
    	
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;



	IPC1bits.T1IP = 2;   // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1;   // Enable timer T2 interrupts
    IFS0bits.T1IF = 0;
   

  	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;


	EnableInterrupts();
	while(1);
    
	


   } 
void _int_(4) isr_T1(void){

	AD1CON1bits.ASAM = 1; 



   IFS0bits.T1IF = 0;

}




void _int_(27) isr_adc(void){
	
	int media = 0;
	int v;
	int *p = (int *)(&ADC1BUF0); 
	int i;			
	for( i = 0; i < 8; i++ ) {

	 v=(p[i*4]*33+511)/1023;
	media += v;
	}	
	media = media/8;
    voltage = media;
    
   IFS1bits.AD1IF = 0 ;



}
void _int_(12) isr_T3(void){

	send2displays(toBcd(voltage));

	IFS0bits.T3IF = 0;
}
