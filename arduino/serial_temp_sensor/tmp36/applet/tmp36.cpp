/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see www.ladyada.net/learn/sensors/cds.html */
 
#include "WProgram.h"
void setup(void);
void loop(void);
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin1 = 8;          // connect Red LED to pin 11 (PWM pin)
int LEDpin2 = 9;
int LEDpin3 = 10;
int LEDpin4 = 11;
int LEDpin5 = 12;
int LEDbrightness;        // 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  //Serial.print("Analog reading = ");
  
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  //analogWrite(LEDpin, LEDbrightness);
  Serial.println(LEDbrightness);     // the raw analog reading
  
  if(LEDbrightness<=70){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,LOW);
    digitalWrite(LEDpin3,LOW);
    digitalWrite(LEDpin4,LOW);
    digitalWrite(LEDpin5,LOW);
  }
  else if((LEDbrightness>70)&(LEDbrightness<=100)){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
    digitalWrite(LEDpin3,LOW);
    digitalWrite(LEDpin4,LOW);
    digitalWrite(LEDpin5,LOW);
  }
  else if((LEDbrightness>100)&(LEDbrightness<=150)){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
    digitalWrite(LEDpin3,HIGH);
    digitalWrite(LEDpin4,LOW);
    digitalWrite(LEDpin5,LOW);
  }
  else if((LEDbrightness>150)&(LEDbrightness<=200)){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
    digitalWrite(LEDpin3,HIGH);
    digitalWrite(LEDpin4,HIGH);
    digitalWrite(LEDpin5,LOW);
  }
  else if(LEDbrightness>200){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
    digitalWrite(LEDpin3,HIGH);
    digitalWrite(LEDpin4,HIGH);
    digitalWrite(LEDpin5,HIGH);
  }
 
  delay(100);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

