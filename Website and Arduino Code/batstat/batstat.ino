
int sensorPin = 32;    // select the input pin for the potentiometer
int voltageValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
    pinMode(sensorPin, INPUT);
}

void loop() {
  // read the value from the sensor:
  int voltageValue = analogRead(sensorPin);
  int battery=map(voltageValue,788,3950,1,100);
  
  Serial.println(battery);
  delay(200);
}
