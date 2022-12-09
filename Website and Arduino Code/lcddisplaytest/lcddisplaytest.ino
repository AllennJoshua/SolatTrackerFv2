// #include <Wire.h>  // library for I2C protocol  
 #include <LiquidCrystal_I2C.h> // library for I2C LCD  
 LiquidCrystal_I2C lcd(0x25,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display  
 LiquidCrystal_I2C lcd2(0x26,16,2);
 LiquidCrystal_I2C lcd3(0x27,16,2);


unsigned long startTime = 0;        // millis counter
unsigned long displaychange = 0;    
unsigned long bootsecs = 0;

int counter = 0;
int counter2 = 1;
int counter3 = 2;


 void setup()  { 
  Serial.begin(9600); 
  Serial.println("booted");
  millis();
  
  
//  lcd.begin(16,2);
//  lcd2.begin(16,2);
//  lcd3.begin(16,2);
  
  lcd.init();
  lcd2.init();
  lcd3.init();
  
  lcd.backlight();
  lcd2.backlight();
  lcd3.backlight();
  
  lcd.clear();
  lcd2.clear();
  lcd3.clear();
  lcd.setCursor(0,0);
  lcd2.setCursor(0,0);
  lcd3.setCursor(0,0);
  
  lcd.print("LCD #1 Line 1");
  lcd2.print("LCD #2 Line 1");
  lcd3.print("LCD #3 Line 1");
  
  lcd.setCursor(0,1);
  lcd2.setCursor(0,1);
  lcd3.setCursor(0,1);

  lcd.print("LCD #1 Line 2");
  lcd2.print("LCD #2 Line 2");
  lcd3.print("LCD #2 Line 2");
  delay(1000);

  lcd.clear();
  lcd2.clear();
  lcd3.clear();
  
  lcd.setCursor(0,0);
  lcd2.setCursor(0,0);
  lcd3.setCursor(0,0);
  lcd.print("LCD #1: ");
  lcd2.print("LCD #2: ");
  lcd3.print("LCD #3: ");

  lcd.setCursor(0,1);
  lcd2.setCursor(0,1);
  lcd3.setCursor(0,1);
  lcd.print("LCD #1: ");
  lcd2.print("LCD #2: ");
  lcd3.print("LCD #3: ");
 }  

 
 void loop()  {  
  
  startTime = millis();
  bootsecs = startTime / 1000;  // convert startTime to seconds
  
  if (startTime >= displaychange){
    displaychange = startTime + 1000;

    lcd.setCursor(8,0);
    lcd2.setCursor(8,0);
    lcd3.setCursor(8,0);
    lcd.print(bootsecs);
    lcd2.print(bootsecs);
    lcd3.print(bootsecs);
    
    lcd.setCursor(8,1);
    lcd2.setCursor(8,1);
    lcd3.setCursor(8,1);
    lcd.print(bootsecs);
    lcd2.print(bootsecs);
    lcd3.print(bootsecs);
  }
  


  
 }  












 
