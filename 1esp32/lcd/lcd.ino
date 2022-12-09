
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
LiquidCrystal_I2C lcd2(0x26,16,2);
LiquidCrystal_I2C lcd3(0x25,16,2);

unsigned long startTime = 0;        // millis counter
unsigned long displaychange = 0;    
unsigned long bootsecs = 0;

int counter = 0;
int counter2 = 1;
int counter3 = 2;


void setup(){
  Serial.begin(9600);
  millis();
  Serial.println("boot");
  
  lcd.begin(16,2);
  lcd2.begin(16,2);
  lcd3.begin(16,2);
  
  lcd.init();                 
  lcd.backlight();

  lcd2.init();                 
  lcd2.backlight();

  lcd3.init();                 
  lcd3.backlight();









  
}
void loop(){


  
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


//  lcd.clear(); 
//  lcd.setCursor(0, 0);
//  lcd.print("Hello, World!");
//
//  lcd2.clear(); 
//  lcd2.setCursor(0, 0);
//  lcd2.print("Hello, World!");
//
//  lcd3.clear(); 
//  lcd3.setCursor(0, 0);
//  lcd3.print("Hello, World!");
//
//
//  lcd.clear();
//  lcd.setCursor(0,1);
//  lcd.print("Hello, World!");
//
//  lcd2.clear();
//  lcd2.setCursor(0,1);
//  lcd2.print("Hello, World!");
//
//  lcd3.clear();
//  lcd3.setCursor(0,1);
//  lcd3.print("Hello, World!");

}
