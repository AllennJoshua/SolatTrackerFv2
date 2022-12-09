
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

// REPLACE with your Domain name and URL path or IP address with path
String serverName = "http://solartrackerfv2.site/send.php?batstat=11&batpercent=22&port1stat=33&port1time=44&port2stat=55&port2time=66&port3stat=77&port3time=88";
  
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  int e = 0;
  int f = 0;
  int g = 0;
  int h = 0;
  
void setup() {
  Serial.begin(9600);
  
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
  //Check WiFi connection status
  // REPLACE with your Domain name and URL path or IP address with path

  a = a+1;
  b = b+1;
  c = c+1;
  d = d+1;
  e = e+1;
  f = f+1;
  g = g+1;
  h = h+1;

  String batstat=String(a);
  String batpercent=String(b);
  String port1stat=String(c);
  String port1time=String(d);
  String port2stat=String(e);
  String port2time=String(f);
  String port3stat=String(g);
  String port3time=String(h);
String serverName = "http://solartrackerfv2.site/send.php?batstat="+batstat+"&batpercent="+batpercent+"&port1stat="+port1stat+"&port1time="+port1time+"&port2stat="+port2stat+"&port2time="+port2time+"&port3stat="+port3stat+"&port3time="+port3time;
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
  delay(1000);  
}
