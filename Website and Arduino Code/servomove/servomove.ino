

#include <Servo_ESP32.h>




unsigned long startTime = 0;        // millis counter
unsigned long displaychange = 0;    
unsigned long bootsecs = 0;


// twelve servo objects can be created on most boards

int ldrleftpin = 34;
int ldrrightpin = 35;

int pos = 0;    // variable to store the servo position
int ldrleft = 0;
int ldrright = 0;
int servomove = 0;

int servohLimitHigh = 180;
int servohLimitLow = 90;
int servopin = 15;

Servo_ESP32 myservo;


void setup() {
  Serial.begin(9600);
//  pinMode(ldrleftpin, INPUT);
//  pinMode(ldrrightpin, INPUT);
  myservo.attach(servopin);  // attaches the servo on servopin
  myservo.write(0);
  delay(3000);
}

void loop() {

  int ldrleft = analogRead(ldrleftpin);
  int ldrright = analogRead(ldrrightpin);

  

  if (ldrleft > ldrright){
    servomove = --servomove;
    
      if (servomove < servohLimitLow){
          servomove = servohLimitLow;
      }
      
  }
  
  if (ldrleft < ldrright){
    servomove = ++servomove;
    
     if (servomove > servohLimitHigh){
         servomove = servohLimitHigh;
     }
     
  }


  
//myservo.write(servomove);



  
  startTime = millis();
  bootsecs = startTime / 1000;  // convert startTime to seconds
  
  if (startTime >= displaychange){
    displaychange = startTime + 500;
  Serial.print("ldrleft: ");
  Serial.print(ldrleft);
  Serial.print("   ");
  Serial.print("ldrright: ");
  Serial.print(ldrright);
  Serial.print("   ");
  Serial.println(servomove);
  myservo.write(servomove);
    


  }






  
}
