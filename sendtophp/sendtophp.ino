#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);



int Led_OnBoard = 2;                  // Initialize the Led_OnBoard 

const char* ssid = "PLDTHOMEFIBR95c68";                  // Your wifi Name       
const char* password = "PLDTWIFIxw4aq";          // Your wifi Password

const char* host = "192.168.1.2"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

String batstat = "Not_Charging";
String batpercent = "bb"; 
String port1stat = "Not_Charging";
String port1time = "bb";


int irpin = 56;                   // pin for ir sensor
int irvalue;                            // value of irsensor.. 1 or 0
int charger = 55;
String message = "" ;
unsigned long addamount =6000; // input secs


String chardis;

unsigned long startTime = 0;        // millis counter
unsigned long timerUp = 0;          // remaining millis till timer is up
unsigned long displaycounter = 0;
unsigned long displaynum = 0;       // the value to be displated in the serial monitor
unsigned long newtimerdown = 0; 
unsigned long mins = 0;
int irsensor = 0;


unsigned long secstodisplay = 0;



void setup() {
  // put your setup code here, to run once:


  millis();
  lcd.begin(16,2);


  pinMode(Led_OnBoard, OUTPUT);       // Initialize the Led_OnBoard pin as an output
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
  }

  digitalWrite(Led_OnBoard, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;    //Declare object of class HTTPClient




// ================================================================================
  startTime = millis();
  displaycounter = timerUp - startTime;
  displaynum = displaycounter/1000;

//  Serial.println("PLS INSERT COIN");

// ================================================================================
//displays the remainin time
  if (displaynum <= 999){
  Serial.print("Time remaining: ");
  Serial.print(displaynum);
  Serial.println("secss ");
  secstodisplay = displaynum;
  chardis = displaynum + "secs";

  lcd.clear();
  lcd.print(mins);
  lcd.print(":");
  lcd.print(displaynum);

delay(200);

  
  } 



if (timerUp > startTime){
  
}


  
// ================================================================================
irvalue = digitalRead(irpin);
  // print out the value you read:


//  Serial.println(irvalue);

  if(irvalue == 1){                           // run when there coin is inserted
  // if coin is inserted, set a 3min timer
  port1stat = "Charging";
        delay(1000);
    // digitalWrite(charger, HIGH);



if (displaynum > 1 ){               // if display is higher than 1, add time

  mins = mins + 5;                  // adds 5mins when button pressed
  
  timerUp = timerUp + addamount;    // adds 3secs when button pressed
//  delay (500);
  
} else {                            // else, make a new time
    mins = mins + 5;
    
    timerUp = startTime + addamount; 
//    delay (500);
    // wait for 1sec before inserting again
}
    
  }


// ================================================================================
  if (displaynum == 0){                        // run when time is up
    //time is up

       if (mins >0 ){
         mins =mins -1;
         timerUp = timerUp + 60000;
//         displaynum = 60;
       }else if (mins<=0&& displaynum<1){
        port1stat = "Not Charging";
         timerUp = 0;                                                               // edit this if code deosnt work
         Serial.println("Time is up!");
        mins = 0;
         lcd.clear();
         lcd.print("TIME IS UP");
       }

  }

String fullbat = "false", halfbat = "false", lowbat = "false";

if (fullbat = "true"){
  message = "battery is at 100%";
  batpercent = "100%";
} else if (halfbat = "true"){
  message = "battery is at 50%";
  batpercent = "50%";
} else if (lowbat = "true"){
  message = "battery is at 20%";
  batpercent = "20%";
}


//=================================================



 
// Serial.print("mins is");
// Serial.println(mins);
// Serial.print("secs is");
// Serial.println(secstodisplay);

 port1time = mins +":" + secstodisplay;
  String  postData;
  String ip = host;
  http.begin("http://" + ip + "/testcode/send.php?batstat="+batstat+"&batpercent="+batpercent+"&port1stat="+port1stat+"&port1time="+port1time+"");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
//  Serial.println("uploaded to php!");
  delay(3000);
}
