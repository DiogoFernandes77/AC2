#include <detpic32.h>
void delay(int ms){
	int i;
	 for(i = ms; i>=0;i--){
	    resetCoreTimer();
	    while(readCoreTimer()<20000);
		}
	}
 void i2c1_init(unsigned int clock_freq)    {
       // Config baudrate generator (see introduction for details)
       I2C1BRG  =   20000000/(2*(clock_freq)) - 1;
       I2C1CONbits.ON = 1;

	
    }
 void i2c1_start(void)    {


	while((I2C1CON & 0x001F) != 0 );  // Wait until the lower 5 bits of I2CxCON are all 0 (the lower 5 bits of I2CxCON must be 0 before attempting to set the SEN bit)
      
      I2C1CONbits.SEN = 1;  // Activate Start event (I2C1CON, bit SEN)
       while(I2C1CONbits.SEN == 1);// Wait for completion of the Start event (I2C1CON, bit SEN)



    } 


	
 void i2c1_stop(void)    { 
      while((I2C1CON & 0x001F) != 0)// Wait until the lower 5 bits of I2CxCON are all 0 (the lower 5 bits   of I2CxCON must be 0 before attempting to set the PEN bit)
     I2C1CONbits.PEN = 1;  // Activate Stop event (I2C1CON, bit PEN)
       while(I2C1CONbits.PEN == 0);// Wait for completion of the Stop event (I2C1CON, bit PEN)
    } 

  int i2c1_send(unsigned char value)    {
     I2C1TRN = value;  // Copy "value" to I2C1TRN register
       // Wait while master transmission is in progress (8 bits + ACK\)
       //    (I2C1STAT, bit TRSTAT – transmit status bit)
       while (I2C1STATbits.TRSTAT == 1);
        // Return acknowledge status bit (I2C1STAT, bit ACKSTAT)
	return I2C1STATbits.ACKSTAT; 
  }


 char i2c1_receive(char ack_bit)    {
      while((I2C1CON &0x001F) != 0);  // Wait util the lower 5 bits of I2C1CON are all 0 (the lower 5 bits
       //   of I2C1CON must be 0 before attempting to set the RCEN bit)
      I2C1CONbits.RCEN = 1; // Activate RCEN bit (receive enable bit, I2C1CON register)
        while (I2C1STATbits.RBF == 1); // Wait while byte not received (I2C1STAT, bit RBF – receive buffer   full status bit)
       // Send ACK / NACK bit. For that:
       //   1. Copy "ack_bit" to I2C1CON, bit ACKDT (be sure "ack_bit" valueis only 0 or1)
	if (ack_bit != 0 && ack_bit != 1) ack_bit = 1;  // todo
	I2C1CONbits.ACKDT = ack_bit;       
	 
	while ((I2C1CON & 0x001F) != 0);//   2. Wait until the lower 5 bits of I2C1CON are all 0 (the lower
     
  //      5 bits of I2C1CON must be 0 before attempting to
        //      set the ACKEN bit.
	
       
	//   3. Start Acknowledge sequence (I2C1CON register, bit ACKEN=1)
       I2C1CONbits.ACKEN = 1;
      
        // Wait for completion of Acknowledge sequence (I2C1CON, bit ACKEN)
	while((I2C1CONbits.ACKEN)==1 )       
	// Return received value (I2C1RCV)
	return     I2C1RCV;
        }



    #define  I2C_READ       1
    #define  I2C_WRITE      0
    #define  I2C_ACK        0
    #define  I2C_NACK       1
    #define  SENS_ADDRESS   0x4D   // device dependent
    #define  ADDR_WR        ((SENS_ADDRESS << 1) | I2C_WRITE)
    #define  ADDR_RD        ((SENS_ADDRESS << 1) | I2C_READ)
    #define  TC74_CLK_FREQ  100000  // 100 KHz
    #define  RTR            0       // Read temperature command


  int main(void) {
   int ack, temperature;
   i2c1_init(TC74_CLK_FREQ); 
   while(1){
	i2c1_start();
	
	ack = i2c1_send(ADDR_WR);
	ack = i2c_send(RTR);
	i2c1_start();
	if(ack != 0){
         i2c1_stop();
         printStr("Error!\n");
         break;
    }
	temperature = i2c_receive(I2C_NACK);

	i2c_stop();
        printSTR("\n");
        printInt10(temperature);

        delay(250);

        LATDbits.LATD8 = 1;





   }



return 1;


}




























