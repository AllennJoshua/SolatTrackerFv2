
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int irpin = D6;                   // pin for ir sensor
int irvalue;                            // value of irsensor.. 1 or 0



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Insert Coin!");
    Serial.println("Insert Coin!");

}

void loop() {
  // put your main code here, to run repeatedly:
  irvalue = digitalRead(irpin);



  lcd.clear();
  lcd.print(irvalue);
  Serial.println(irvalue);
  delay(300);

  

}
