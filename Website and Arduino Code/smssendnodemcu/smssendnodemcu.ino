#include <SoftwareSerial.h>
SoftwareSerial sim800l(D4, D3); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted
//                    (tx,rx)
//                    (tx pin of sm module, rx pin of arduino)

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    sim800l.begin(9600);
    Serial.println("Code Initialized!");

   Serial.print("sim800l ready...");

  // AT command to set sim800l to SMS mode
  sim800l.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  sim800l.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
    SendSMS();
}

void loop() {
  // put your main code here, to run repeatedly:

}


void SendSMS() {
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  //Serial.println("AT+CMGF=1\r");
  delay(100);
  sim800l.print("AT+CMGS=\"+639760836760\"\r");  //Your phone number don't forget to include your country code, example "+63..........your number\"
  //Serial.println("AT+CMGS=\"+639760836760\"\r");
  delay(500);
  sim800l.print("2222222222222");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  //Serial.println("SIM800l is working");
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(8000);

}
