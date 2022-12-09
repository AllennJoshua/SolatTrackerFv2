//Working with 3IR sensor, 3timers, 3lcd, and 3 relays

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

// Replace with your network credentials
const char* ssid     = "PLDTHOMEFIBR95c68";
const char* password = "PLDTWIFIxw4aq";

// Jericho Wifi credential
//const char* ssid     = "HUAWEI-c2hG";
//const char* password = "allmight02";



 #include <Wire.h>  // library for I2C protocol  
 #include <LiquidCrystal_I2C.h> // library for I2C LCD  
 LiquidCrystal_I2C lcd(0x25,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display  
 LiquidCrystal_I2C lcd2(0x26,16,2);
 LiquidCrystal_I2C lcd3(0x27,16,2);

  int sensorValue1;   // variable to store the value coming from the sensor
  int sensorValue2;
  int sensorValue3;
  
  int ledPin1 = 19;   //pins of infrared sensors
  int ledPin2 = 18;
  int ledPin3 = 17; //D7
  
  int relay1pin = 25;
  int relay2pin = 26;
  int relay3pin = 27;

  // code for battery sensor
  int sensorPin = 32;    // select the input pin for the potentiometer
  int sensorValue = 0;  // variable to store the value coming from the sensor
  int battery = 0;


  // universal millis variable
  unsigned long startTime = 0;        // millis counter
  unsigned long uniaddmins = 1;
  unsigned long uniaddamount = 3;

  String batstat = "na";
  String batpercent = "na";
  String port1stat = "na";
  String port1time = "na";
  String port2stat = "na";
  String port2time = "na";
  String port3stat = "na";
  String port3time = "na";

  // LCD TIMER 1
 // amount of time will be added when coin is inserted
  unsigned long addmins = uniaddmins;
  unsigned long addamount = uniaddamount; // input secs
  unsigned long timerUp = 0;          // remaining millis till timer is up
  unsigned long updatedtimerUp = 0;   // counting timer
  unsigned long displaychange = 0;   // to change display in lcd every second
  unsigned long mins = 0;           // mins


  // LCD TIMER 2
 // amount of time will be added when coin is inserted
  unsigned long addmins2 = uniaddmins;
  unsigned long addamount2 = uniaddamount; // input secs
  unsigned long timerUp2 = 0;          // remaining millis till timer is up
  unsigned long updatedtimerUp2 = 0;   // counting timer
  unsigned long displaychange2 = 0;   // to change display in lcd every second
  unsigned long mins2 = 0;           // mins


  // LCD TIMER 3
 // amount of time will be added when coin is inserted
  unsigned long addmins3 = uniaddmins;
  unsigned long addamount3 = uniaddamount; // input secs
  unsigned long timerUp3 = 0;          // remaining millis till timer is up
  unsigned long updatedtimerUp3 = 0;   // counting timer
  unsigned long displaychange3 = 0;   // to change display in lcd every second
  unsigned long mins3 = 0;           // mins




//Include the servo motor library
#include <Servo_ESP32.h>
//Define the LDR sensor pins
#define LDR1 34
#define LDR2 35
//Define the error value. You can change it as you like
#define error 500
//Starting point of the servo motor
int Spoint =  90;
//Create an object for the servo motor
Servo_ESP32 servo;

int servopin = 15;
int maxrotate = 180;
int minrotate = 90;


  unsigned long servomove = 0;        // 
  unsigned long servoTime = 0;

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  millis(); //initialize millis start time
  
  
  pinMode(ledPin1, INPUT);    //setting infrared pins as input pins
  pinMode(ledPin2, INPUT);
  pinMode(ledPin3, INPUT);

  pinMode(relay1pin, OUTPUT);   // setting relays as output pins
  pinMode(relay2pin, OUTPUT);
  pinMode(relay3pin, OUTPUT);
  
  pinMode(sensorPin, INPUT);


  
  

  // defines the size of lcd
//  lcd.begin(16,2);
//  lcd2.begin(16,2);
//  lcd3.begin(16,2);
  // initialize 3 lcds
  lcd.init();
  lcd2.init();
  lcd3.init();
  //turns on backlight
  lcd.backlight();
  lcd2.backlight();
  lcd3.backlight();
  //clears screen to put text
  lcd.clear();
  lcd2.clear();
  lcd3.clear();
  lcd.setCursor(0,0);
  lcd2.setCursor(0,0);
  lcd3.setCursor(0,0);
  //prints to the screen
  lcd.print("Charging Port #1");
  lcd2.print("Charging Port #2");
  lcd3.print("Charging Port #3");
  lcd.setCursor(0,1);
  lcd2.setCursor(0,1);
  lcd3.setCursor(0,1);
  lcd.print("Timer: ");
  lcd2.print("Timer: ");
  lcd3.print("Timer: ");
  lcd.setCursor(9,1);
  lcd2.setCursor(9,1);
  lcd3.setCursor(9,1);
  lcd.print(":");
  lcd2.print(":");
  lcd3.print(":");

//Include servo motor PWM pin
  servo.attach(servopin);
//Set the starting point of the servo
  servo.write(Spoint);
  delay(1000);

    WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  startTime = millis();
  servoTime = millis();
  startTime = startTime / 1000;   // Convert startTime to seconds

  sensorValue1 = digitalRead(ledPin1);    //Reads value of infrared sensors
  sensorValue2 = digitalRead(ledPin2);
  sensorValue3 = digitalRead(ledPin3);
  
  int voltageValue = analogRead(sensorPin);
  int battery=map(voltageValue,788,3950,1,100);



  
  //  Serial.print("IR1: ");
  //  Serial.print(sensorValue1);
  //  Serial.print(" IR2: ");
  //  Serial.print(sensorValue2);
  //  Serial.print(" IR3: ");
  //  Serial.print(sensorValue3);
  //  Serial.print(" ");
  //  Serial.print("voltage: ");
  //  Serial.print(voltageValue);
  //  Serial.println("   ");















  // LCD TIMER 1 ----------------------------------------------------------------------

  updatedtimerUp = timerUp - startTime;
  
  if (updatedtimerUp == 1){
    if (mins > 0){
      timerUp = timerUp + 60;
      mins = mins - 1;
    }
  }
  
  if (updatedtimerUp >= 1000000){
    updatedtimerUp = 0;
  }
  

//  Serial.println(sensorValue1);




      //Runs when IR 
    if (sensorValue1 == 1) {

      if (updatedtimerUp >=1){
        timerUp = timerUp + addamount;
        mins = mins + addmins;
      } else {
        timerUp = startTime + addamount;
        mins = mins + addmins;
      }

      

      Serial.println("coin inserted!!");
      delay(1000);
    }












  // LCD TIMER 2 ----------------------------------------------------------------------

updatedtimerUp2 = timerUp2 - startTime;
  
  if (updatedtimerUp2 == 1){
    if (mins2 > 0){
      timerUp2 = timerUp2 + 60;
      mins2 = mins2 - 1;
    }
  }
  
  if (updatedtimerUp2 >= 1000000){
    updatedtimerUp2 = 0;
  }
  

//  Serial.println(sensorValue1);
  
    if (sensorValue2 == 1) {

      if (updatedtimerUp2 >=1){
        timerUp2 = timerUp2 + addamount2;
        mins2 = mins2 + addmins2;
      } else {
        timerUp2 = startTime + addamount2;
        mins2 = mins2 + addmins2;
      }

      

      Serial.println("coin inserted!!");
      delay(1000);
    }



  // LCD TIMER 3 ----------------------------------------------------------------------

updatedtimerUp3 = timerUp3 - startTime;
  
  if (updatedtimerUp3 == 1){
    if (mins3 > 0){
      timerUp3 = timerUp3 + 60;
      mins3 = mins3 - 1;
    }
  }
  
  if (updatedtimerUp3 >= 1000000){
    updatedtimerUp3 = 0;
  }
  


  
    if (sensorValue3 == 1) {

      if (updatedtimerUp3 >=1){
        timerUp3 = timerUp3 + addamount3;
        mins3 = mins3 + addmins3;
      } else {
        timerUp3 = startTime + addamount3;
        mins3 = mins3 + addmins3;
      }

      

      Serial.println("coin inserted!!");
      delay(1000);
    }






    // turn on relay if timer is running
  if (updatedtimerUp > 0){   
//    digitalWrite(relay1pin, HIGH);

//    Serial.print("relay1pin: ");
//    Serial.print(relay1pin);
//    Serial.print("   ");
//    Serial.print("updatedtimerUp: ");
//    Serial.print(updatedtimerUp);
//    Serial.println("   ");



    digitalWrite(relay1pin, LOW);

  } else {

//    Serial.print("relay1pin: ");
//    Serial.print(relay1pin);
//    Serial.println("   ");


        digitalWrite(relay1pin, HIGH);

  }

  if (updatedtimerUp2 > 0){
    digitalWrite(relay2pin, LOW);
  } else {
    digitalWrite(relay2pin, HIGH);
  }

  if (updatedtimerUp3 > 0){
    digitalWrite(relay3pin, LOW);
  } else {
    digitalWrite(relay3pin, HIGH);
  }















  // Change the time in lcd everysecond -----------------------------------------------
  // 
  if (startTime >= displaychange){
    displaychange = startTime + 1;
    
//    Serial.print("startTime: ");
//    Serial.print(startTime);
//    Serial.print(" ");
//  
//    Serial.print("timerUp: ");
//    Serial.print(timerUp);
//    Serial.print("   ");
//  
    Serial.print("updatedtimerUp: ");
    Serial.print(updatedtimerUp);
    Serial.print(" ");
    
    Serial.print("updatedtimerUp2: ");
    Serial.print(updatedtimerUp2);
    Serial.print(" ");

    Serial.print("updatedtimerUp3: ");
    Serial.print(updatedtimerUp3);
    Serial.print(" ");








    
    Serial.println("   ");



  // LCD TIMER 1 Updater
    if (updatedtimerUp < 10){
  
      if (mins > 9){
        lcd.setCursor(7,1);
        lcd.print(mins);
      } else {
        lcd.setCursor(8,1);
        lcd.print(mins);
        lcd.setCursor(7,1);
        lcd.print(" ");
      }
      
      lcd.setCursor(10,1);
      lcd.print(updatedtimerUp);
      lcd.setCursor(11,1);
      lcd.print(" ");
  
    } else {
      lcd.setCursor(10,1);
      lcd.print(updatedtimerUp);
      
        if (mins > 9){
          lcd.setCursor(7,1);
          lcd.print(mins);
        } else {
          lcd.setCursor(8,1);
          lcd.print(mins);
          lcd.setCursor(7,1);
          lcd.print(" ");
        }
    }



  // LCD TIMER 2 Updater
    if (updatedtimerUp2 < 10){
  
      if (mins2 > 9){
        lcd2.setCursor(7,1);
        lcd2.print(mins2);
      } else {
        lcd2.setCursor(8,1);
        lcd2.print(mins2);
        lcd2.setCursor(7,1);
        lcd2.print(" ");
      }
      
      lcd2.setCursor(10,1);
      lcd2.print(updatedtimerUp2);
      lcd2.setCursor(11,1);
      lcd2.print(" ");
  
    } else {
      lcd2.setCursor(10,1);
      lcd2.print(updatedtimerUp2);
      
        if (mins2 > 9){
          lcd2.setCursor(7,1);
          lcd2.print(mins2);
        } else {
          lcd2.setCursor(8,1);
          lcd2.print(mins2);
          lcd2.setCursor(7,1);
          lcd2.print(" ");
        }
    }
   

  }



  // LCD TIMER 3 Updater
    if (updatedtimerUp3 < 10){
  
      if (mins3 > 9){
        lcd3.setCursor(7,1);
        lcd3.print(mins3);
      } else {
        lcd3.setCursor(8,1);
        lcd3.print(mins3);
        lcd3.setCursor(7,1);
        lcd3.print(" ");
      }
      
      lcd3.setCursor(10,1);
      lcd3.print(updatedtimerUp3);
      lcd3.setCursor(11,1);
      lcd3.print(" ");
  
    } else {
      lcd3.setCursor(10,1);
      lcd3.print(updatedtimerUp3);
      
        if (mins3 > 9){
          lcd3.setCursor(7,1);
          lcd3.print(mins3);
        } else {
          lcd3.setCursor(8,1);
          lcd3.print(mins3);
          lcd3.setCursor(7,1);
          lcd3.print(" ");
        }
    }


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
//  Serial.print(ldr1);
//  Serial.print("   ");
//  Serial.println(ldr2);
}



}



void uploadtodb() {
  // variables to be stored in database
  String batstat="11a";
  String batpercent= String(battery);
  

  if (updatedtimerUp >= 1){
    String port1stat = "Charging";
  } else {
    String port1stat = "Not_Charging";
  }
  
  if (updatedtimerUp2 >= 1){
    String port2stat = "Charging";
  } else {
    String port2stat = "Not_Charging";
  }
  
  if (updatedtimerUp3 >= 1){
    String port3stat = "Charging";
  } else {
    String port3stat = "Not_Charging";
  }

 
 port1time = String(mins) + ":" + String(updatedtimerUp);
 port2time = String(mins2) + ":" + String(updatedtimerUp2);
 port3time = String(mins3) + ":" + String(updatedtimerUp3);
  
String serverName = "http://solartrackerfv2.site/send.php?batstat="+batstat+"&batpercent="+batpercent+"&port1stat="+port1stat+"&port1time="+port1time+"&port2stat="+port2stat+"&port2time="+port2time+"&port3stat="+port3stat+"&port3time="+port3time;
    //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
     
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
   
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
//  delay(30000);  
}
