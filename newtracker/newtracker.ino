

//Include the servo motor library
#include <Servo_ESP32.h>
//Define the LDR sensor pins
#define LDR1 34
#define LDR2 35
//Define the error value. You can change it as you like
#define error 150
//Starting point of the servo motor
int Spoint =  90;
//Create an object for the servo motor
Servo_ESP32 servo;

int servopin = 15;
int maxrotate = 180;
int minrotate = 90;

  unsigned long startTime = 0;        // millis counter
  unsigned long servomove = 0;        // 
  unsigned long servoTime = 0;
  
void setup() {
  Serial.begin(9600);
  millis(); //initialize millis start time
//Include servo motor PWM pin
  servo.attach(servopin);
//Set the starting point of the servo
  servo.write(Spoint);
  delay(1000);
}

void loop() {

  servoTime = millis();
  
  
if (servoTime > servomove){
  servomove = startTime + 15;
    
//Get the LDR sensor value
  int ldr1 = analogRead(LDR1);
//Get the LDR sensor value
  int ldr2 = analogRead(LDR2);

//Get the difference of these values
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

//Check these values using a IF condition
  if ((value1 <= error) || (value2 <= error)) {

  } else {
    if (ldr1 > ldr2) {
      Spoint = --Spoint;
        if (Spoint < minrotate){
          Spoint = minrotate;
        } 
    }
    if (ldr1 < ldr2) {
        Spoint = ++Spoint;
    }
    if (Spoint > maxrotate){
      Spoint = maxrotate;
    }
  }
//Write values on the servo motor
  servo.write(Spoint);
//  delay(15);
  Serial.print(ldr1);
  Serial.print("   ");
  Serial.print(ldr2);
  Serial.print("   ");
  Serial.println(Spoint);
}

}
