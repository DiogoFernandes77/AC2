 void delay(int ms){
	int i;
	 for(i = ms; i>=0;i--){
	    resetCoreTimer();
	    while(readCoreTimer()<20000);
		}
	}
