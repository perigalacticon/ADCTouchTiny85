/*
  ADCTouchTiny85.cpp - Library for Capacittive touch sensors using only one ADC PIN for the ATTINY85 Microcontroller.
  Created by Stephen Kramer 7/24/2016.
  This is a version of ADCTouch.cpp by martin2250, April 23, 2014; modified for the ATTINY85 Microcontroller.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ADCTouchTiny85.h"
// #define DEBUG true


int ADCTouchTiny85Class::read(byte ADCChannel, int samples)
{
    dataflash.end();
    SPI.end();

#if DEBUG
        Serial.print("1st ADCSRA = ");		
		Serial.println(ADCSRA, BIN);
#endif

	long _value = 0;
	for(int _counter = 0; _counter < samples; _counter ++)
	{
		pinMode(ADCChannel, INPUT_PULLUP);
		
#if DEBUG
		Serial.print("0 ADMUA = ");
		Serial.println(ADMUX, BIN);
#endif

		ADMUX |= 0b1101;  // set MUX to ground for tiny85
		ADCSRA |= _BV(ADPS1) | _BV(ADPS2); // enable ADC and set clock to 64.

#if DEBUG
        Serial.print("1st ADMUX = ");
		Serial.println(ADMUX, BIN);
        Serial.print("2nd ADCSRA = ");		
		Serial.println(ADCSRA, BIN);		
#endif

		ADCSRA |= (1<<ADSC); //start conversion
		
#if DEBUG
        Serial.print("3rd ADCSRA = ");		
		Serial.println(ADCSRA, BIN);
#endif

		while(!(ADCSRA & (1<<ADIF))); //wait for conversion to finish
		ADCSRA |= (1<<ADIF); //reset the flag
		
#if DEBUG
        Serial.print("4th ADCSRA = ");		
		Serial.println(ADCSRA, BIN);
#endif

		pinMode(ADCChannel, INPUT);
		
#if DEBUG
        Serial.print("2nd ADMUX = ");
		Serial.println(ADMUX, BIN);
#endif
		
		_value += analogRead(ADCChannel);
		
#if DEBUG
    Serial.print("3rd ADMUX = ");
	Serial.println(ADMUX, BIN);
#endif

	}
    SPI.begin();

	return _value / samples;
}

ADCTouchTiny85Class ADCTouchTiny85;