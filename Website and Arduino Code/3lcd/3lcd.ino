#include <SoftwareSerial.h>
SoftwareSerial sim800l(D4, D3); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted
//                    (tx,rx)
//                    (tx pin of sm module, rx pin of arduino)
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "PLDTHOMEFIBR95c68";                  // Your wifi Name
const char* password = "PLDTWIFIxw4aq";          // Your wifi Password


//    HUAWEI-c2h
//    allmight02


const char* host = "solartrackerfv2.site"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

String batstat = "Not_Charging.";
String batpercent = "52%.";
String port1stat = "Not_Charging.";
String port1time = "0:00.";


int phpcounterr = 0;          //timer before uploading data to database




int irpin = D6;                   // pin for ir sensor
int irvalue = 0;                            // value of irsensor.. 1 or 0
int charger = 55;
String message = "" ;




String chardis;



unsigned long phpstartTime = 0;        // millis counter
unsigned long phpafter1sec = 0;        // millis counter
int phpdisplaynum = 0;
unsigned long addamount = 6000; // input secs
unsigned long startTime = 0;        // millis counter
unsigned long timerUp = 0;          // remaining millis till timer is up
unsigned long displaycounter = 0;
unsigned long displaynum = 0;       // the value to be displated in the serial monitor
unsigned long newtimerdown = 0;
unsigned long mins = 0;


int irsensor = 0;
int displaynumtimer = 0;

String messagedetail;

int sensorPin = A0;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor


int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                 //initialize serial monitor communication
//  sim800l.begin(9600);
    // AT command to set sim800l to SMS mode
//  sim800l.print("AT+CMGF=1\r"); 
  delay(100);
  
  // Set module to send SMS data to serial out upon receipt 
//  sim800l.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  millis();
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");

  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  // Wait for connection


  while (WiFi.status() != WL_CONNECTED) {

    delay(250);
    Serial.print(".");
    lcd.clear();
    lcd.print("Connecting...");


    delay(250);
  }


  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  uploadtodb();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP


  pinMode(D5, OUTPUT);

  lcd.clear();
  lcd.print("Insert Coin!");
  Serial.println("Insert Coin!");
  digitalWrite(D5, LOW);



}

void loop() {
  // put your main code here, to run repeatedly:
  irvalue = 0;

  
  sensorValue = analogRead(sensorPin);
float voltage=map(sensorValue,244,249,0,100);// map 0-1023 to 0-2500 mV and add correction offset
  


  
if (port1stat == "Charging!"){
    phpcounterr = phpcounterr + 5;
} else{
    phpcounterr = phpcounterr + 10;
}


  Serial.print(mins);
    Serial.print("  ");

  

//if(displaynum <= 9999) {
//            Serial.println(phpcounterr);
//  if (phpcounterr >= 200){
////        Serial.println("done with 50 counter");
////        Serial.println(counterr);
//        phpcounterr = 0;
//        uploadtodb();
////        delay(1000);
//    
//  }
//}
  

  Serial.println(phpcounterr);
  if (mins >=1){
      if (phpcounterr >= 199){
        phpcounterr = 0;
        uploadtodb();
      }
  }






  startTime = millis();
  displaycounter = timerUp - startTime;
  displaynum = displaycounter / 1000;

  //  Serial.println("PLS INSERT COIN");

  // ================================================================================
  //displays the remainin time
  if (displaynum <= 999) {
    Serial.print("Time remaining: ");
    Serial.print(mins);
    Serial.print(":");
    Serial.print(displaynum);
    Serial.println("secss ");

    chardis = displaynum + "secs";


  // code to display timer in lcd 1
    lcd.clear();
    lcd.print("Timer: ");
    lcd.print(mins);
    lcd.print(":");
    lcd.print(displaynum);
    delay(30);


  } else {

    //  lcd.clear();
    //  lcd.print("Insert Coin!");
    //    Serial.println("Insert Coin!");
    //delay(200);


  }
  // ================================================================================
  irvalue = digitalRead(irpin);
  // print out the value you read:


  //  Serial.println(irvalue);

  if (irvalue == 1) {                         // run when there coin is inserted
    // if coin is inserted, set a 3min timer
    digitalWrite(D5, HIGH);
    port1stat = "Charging!";
    Serial.println("Coin Inserted!!");



    // digitalWrite(charger, HIGH);



    if (mins > 1 ) {

      mins = mins + 5;                  // adds 5mins when button pressed

      timerUp = timerUp + addamount;    // adds 3secs when button pressed
      lcd.clear();
      lcd.print("+5 mins!");
      delay (1000);

    } else {
      mins = mins + 5;

      timerUp = startTime + addamount;
      //    delay (500);
      // wait for 1sec before inserting again
      lcd.clear();
      lcd.print("+5 mins!");
      delay(1000);
    }

  }


  // ================================================================================
  // run when time is up
  //time is up

  if (displaynum == 0 ) {

    if (mins == 0) {
      mins = 0;
      displaynum = 0;
      digitalWrite(D5, LOW);
      port1stat = "Not_Charging";

      lcd.clear();
      lcd.print("Time's Up!");

    } else {
      mins = mins - 1;
      timerUp = timerUp + 60000;

    }



  }



  if (displaynum == 0) {
    displaynumtimer = displaynumtimer + 1;

  }


String tester = "no";
  if (tester == "LDR detecting sun"){
    batstat = "Charging!";
  } else {
    batstat = "Not_Charging";  
  }


  









  if (voltage > 247) {
    messagedetail = "battery is at 100%";
//    Serial.println("battery is at 100%"); 
    batpercent = "100%";
    
  } else if (sensorValue > 240) {
    messagedetail = "battery is at 750%";
//    Serial.println("battery is at 50%"); 
    batpercent = "75%";
    
  } else if (sensorValue > 236) {
    messagedetail = "battery is at 50%";
//    Serial.println("battery is at 50%"); 
    batpercent = "50%";
    
  } else if (sensorValue > 232) {
    messagedetail = "battery is at 25%";
//    Serial.println("battery is at 25%"); 
    batpercent = "25";
    
  } else  {
    messagedetail = "Battery is not connected";
    batpercent = "52%";

    
  }




if (displaynum > 61){
  phpdisplaynum = 0;
} else {
  phpdisplaynum = displaynum;
}




}



void uploadtodb(){
    HTTPClient http;    //Declare object of class HTTPClient
String umins = String(mins);
String udisplaynum = String(phpdisplaynum);
  port1time = umins +":" + udisplaynum;
  String  postData;
  String ip = host;
  http.begin("http://" + ip + "/send.php?batstat="+batstat+"&batpercent="+batpercent+"&port1stat="+port1stat+"&port1time="+port1time);              //Specify request destination
    Serial.println(batstat);
      Serial.println(batpercent);
        Serial.println(port1stat);
          Serial.println(port1time);
//          delay(4000);


          
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  Serial.println("uploaded to php!");
}

void SendSMS() {
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  //Serial.println("AT+CMGF=1\r");
  delay(100);
  sim800l.print("AT+CMGS=\"+639760836760\"\r");  //Your phone number don't forget to include your country code, example "+63..........your number\"
  //Serial.println("AT+CMGS=\"+639760836760\"\r");
  delay(500);
  sim800l.print("" + messagedetail);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  //Serial.println("SIM800l is working");
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(8000);

}
