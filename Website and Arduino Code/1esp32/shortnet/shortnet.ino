
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>


// Replace with your network credentials
const char* ssid     = "PLDTHOMEFIBR95c68";
const char* password = "PLDTWIFIxw4aq";



  // universal millis variable
  unsigned long startTime = 0;        // millis counter
  unsigned long uploaddata = 0;

String batstat = "na";
String batpercent = "na";
String port1stat = "na";
String port1time = "na";
String port2stat = "na";
String port2time = "na";
String port3stat = "na";
String port3time = "na";


void setup() {
  Serial.begin(9600);
  millis(); //initialize millis start time
  
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
  startTime = millis();
  startTime = startTime / 1000;   // Convert startTime to seconds


    if (startTime >= uploaddata){
    uploaddata = startTime + 10;



 batstat = "11";
 batpercent = "22";
 port1stat = "33";
 port1time = "44";
 port2stat = "55";
 port2time = "66";
 port3stat = "77";
 port3time = "88";

    
    // REPLACE with your Domain name and URL path or IP address with path
String serverName = "http://solartrackerfv2.site/send.php?batstat="+batstat+"&batpercent="+batpercent+"&port1stat="+port1stat+"&port1time="+port1time+"&port2stat="+port2stat+"&port2time="+port2time+"&port3stat="+port3stat+"&port3time="+port3time+"";
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
      
      // You can comment the httpRequestData variable above
      // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";
  
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
       
      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
          
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
    } else {
      Serial.println("WiFi Disconnected");
    }  
  }



  
}
