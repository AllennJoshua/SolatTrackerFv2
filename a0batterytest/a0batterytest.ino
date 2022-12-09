
int sensorPin = A0;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);

}

void loop() {
  delay(1000);
  
  sensorValue = analogRead(sensorPin);
float voltage=map(sensorValue,244,249,0,100);// map 0-1023 to 0-2500 mV and add correction offset

//  Serial.println(sensorValue);



//if(voltage > 0){
//    Serial.print("Battery is at: ");
//  Serial.println(voltage);
//} else {
//    Serial.println("Battery Not Connected");
//    
//}



  if (voltage > 247) {


    Serial.println("battery is at 100%"); 

    
  } else if (sensorValue > 246) {

    Serial.println("battery is at 80%"); 

    
  } else if (sensorValue > 245) {

    Serial.println("battery is at 60%"); 

    
  } else if (sensorValue > 244) {

    Serial.println("battery is at 40%"); 

    
  } else if (sensorValue > 243) {

    Serial.println("battery is at 20%"); 

    
  }









}
