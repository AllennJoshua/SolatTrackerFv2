 #include <Wire.h>  // library for I2C protocol  
 #include <LiquidCrystal_I2C.h> // library for I2C LCD  
 LiquidCrystal_I2C lcd(0x25,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display  
 LiquidCrystal_I2C lcd2(0x26,16,2);
 LiquidCrystal_I2C lcd3(0x27,16,2);

  int sensorValue1;   // variable to store the value coming from the sensor
  int sensorValue2;
  int sensorValue3;
  
  int ledPin1 = D5;   //pins of infrared sensors
  int ledPin2 = D6;
  int ledPin3 = D7;


  // universal millis variable
  unsigned long startTime = 0;        // millis counter



  // LCD TIMER 1
 // amount of time will be added when coin is inserted
  unsigned long addmins = 5;
  unsigned long addamount = 3; // input secs
  unsigned long timerUp = 0;          // remaining millis till timer is up
  unsigned long updatedtimerUp = 0;   // counting timer
  unsigned long displaychange = 0;   // to change display in lcd every second
  unsigned long mins = 0;           // mins


  // LCD TIMER 2
 // amount of time will be added when coin is inserted
  unsigned long addmins2 = 5;
  unsigned long addamount2 = 3; // input secs
  unsigned long timerUp2 = 0;          // remaining millis till timer is up
  unsigned long updatedtimerUp2 = 0;   // counting timer
  unsigned long displaychange2 = 0;   // to change display in lcd every second
  unsigned long mins2 = 0;           // mins


  // LCD TIMER 3
 // amount of time will be added when coin is inserted
  unsigned long addmins3 = 5;
  unsigned long addamount3 = 3; // input secs
  unsigned long timerUp3 = 0;          // remaining millis till timer is up
  unsigned long updatedtimerUp3 = 0;   // counting timer
  unsigned long displaychange3 = 0;   // to change display in lcd every second
  unsigned long mins3 = 0;           // mins






 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(ledPin1, INPUT);    //setting infrared pins as input pins
  pinMode(ledPin2, INPUT);
  pinMode(ledPin3, INPUT);


  
  millis(); //initialize millis start time

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

}

void loop() {
  // put your main code here, to run repeatedly:
  startTime = millis();
  startTime = startTime / 1000;   // Convert startTime to seconds

  sensorValue1 = digitalRead(ledPin1);    //Reads value of infrared sensors
  sensorValue2 = digitalRead(ledPin2);
  sensorValue3 = digitalRead(ledPin3);


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

  // Change the time in lcd everysecond -----------------------------------------------
  // 
  if (startTime >= displaychange){
    displaychange = startTime + 1;
    
    Serial.print("startTime: ");
    Serial.print(startTime);
    Serial.print("   ");
  
    Serial.print("timerUp: ");
    Serial.print(timerUp);
    Serial.print("   ");
  
    Serial.print("updatedtimerUp: ");
    Serial.print(updatedtimerUp);
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






}
