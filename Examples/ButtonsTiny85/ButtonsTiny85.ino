// Based on ADCTouch; mod for ATtiny85.

#include <ADCTouchTiny85.h>
int ref1;     //reference values to remove offset

void setup() 
{
	pinMode(3, OUTPUT);
    ref1 = ADCTouchTiny85.read(A1, 500);    //account for the capacitance of the pad
} 

void loop() 
{

    int value1 = ADCTouchTiny85.read(A1);   //   --> 100 samples
       
    value1 -= ref1;  //remove offset
	
	if(value1 > 20){
		digitalWrite(3, HIGH);
	}else{
		digitalWrite(3, LOW);
	}

    delay(100);
}
