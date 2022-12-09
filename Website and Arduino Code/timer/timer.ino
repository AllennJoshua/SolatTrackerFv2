#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "PLDTHOMEFIBR95c68";                  // Your wifi Name
const char* password = "PLDTWIFIxw4aq";          // Your wifi Password

const char* host = "solartrackerfv2.site"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

String batstat = "Not_Charging.";
String batpercent = "52%.";
String port1stat = "Not_Charging.";
String port1time = "0:00.";


int phpcounterr = 0;


unsigned long phpstartTime = 0;        // millis counter
unsigned long phpafter1sec = 0;        // millis counter
int phpdisplaynum = 0;

int irpin = D6;                   // pin for ir sensor
int irvalue;                            // value of irsensor.. 1 or 0
int charger = 55;
String message = "" ;
unsigned long addamount = 6000; // input secs


String chardis;

unsigned long startTime = 0;        // millis counter
unsigned long timerUp = 0;          // remaining millis till timer is up
unsigned long displaycounter = 0;
unsigned long displaynum = 0;       // the value to be displated in the serial monitor
unsigned long newtimerdown = 0;
unsigned long mins = 0;
int irsensor = 0;
int displaynumtimer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                 //initialize serial monitor communication

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



  phpcounterr = phpcounterr + 1;
          Serial.println(phpcounterr);
  if (phpcounterr >= 500){
//        Serial.println("done with 50 counter");
//        Serial.println(counterr);
        phpcounterr = phpcounterr - 500;
        uploadtodb();
//        delay(1000);
    
  }


  startTime = millis();
  displaycounter = timerUp - startTime;
  displaynum = displaycounter / 1000;

  //  Serial.println("PLS INSERT COIN");

  // ================================================================================
  //displays the remainin time
  if (displaynum <= 999) {
    Serial.print("Time remaining: ");
    Serial.print(displaynum);
    Serial.println("secss ");

    chardis = displaynum + "secs";

    lcd.clear();
    lcd.print("Timer: ");
    lcd.print(mins);
    lcd.print(":");
    lcd.print(displaynum);

    delay(100);


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
      mins = mins + 1;

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


  







  String fullbat, halfbat, lowbat;

  if (fullbat) {
    message = "battery is at 100%";

  } else if (halfbat) {
    message = "battery is at 50%";

  } else if (lowbat) {
    message = "battery is at 20%";

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
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  Serial.println("uploaded to php!");
}
