/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);





  if (sensorValue > 900) {
//    messagedetail = "battery is at 100%";
//    SendSMS();
    Serial.println("battery is at 100%"); 
    
  } else if (sensorValue > 600) {
//    messagedetail = "battery is at 50%";
//    SendSMS();
    Serial.println("battery is at 50%"); 
    
  } else if (sensorValue > 400) {
//    messagedetail = "battery is at 40%";
//    SendSMS();
    Serial.println("battery is at 40%"); 
    
  } else if (sensorValue > 200) {
//    messagedetail = "battery is at 20%";
//    SendSMS();
    Serial.println("battery is at 20%"); 
    
  } else {
//       print the results to the Serial Monitor:
       Serial.print("sensor = ");
       Serial.println(sensorValue);
  }

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
