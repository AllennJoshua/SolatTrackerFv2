// code to test 3 infrared, 3 relays, and 1 voltage sensor.
int sensorValue1;  // variable to store the value coming from the sensor
int sensorValue2;
int sensorValue3;

int voltagepin = A0;    // voltage sensor pins
int voltageValue = 0;

int relay1pin = D3;
int relay2pin = D4;
int relay3pin = D8;

int ledPin1 = D5;   // pins of infrared sensors
int ledPin2 = D6;
int ledPin3 = D7;



void setup() {
  Serial.begin(9600);
    
  pinMode(ledPin1, INPUT);    // setting infrared pins as input pins
  pinMode(ledPin2, INPUT);
  pinMode(ledPin3, INPUT);
  
  pinMode(relay1pin, OUTPUT);   // setting relays as output pins
  pinMode(relay2pin, OUTPUT);
  pinMode(relay3pin, OUTPUT);
  
  pinMode(voltagepin, INPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue1 = digitalRead(ledPin1);    // Reads value of infrared sensors
  sensorValue2 = digitalRead(ledPin2);
  sensorValue3 = digitalRead(ledPin3);

  Serial.print("IR1: ");
  Serial.print(sensorValue1);
  Serial.print("   ");
  Serial.print("IR2: ");
  Serial.print(sensorValue2);
  Serial.print("   ");
  Serial.print("IR3: ");
  Serial.print(sensorValue3);
  Serial.print("   ");


  voltageValue = analogRead(voltagepin);
  Serial.print("voltage: ");
  Serial.print(voltageValue);
  Serial.println("   ");


  if (sensorValue1 == 1){
    digitalWrite(relay1pin, HIGH);
  } else {
    digitalWrite(relay1pin, LOW);
  }

  if (sensorValue2 == 1){
    digitalWrite(relay2pin, HIGH);
  } else {
    digitalWrite(relay2pin, LOW);
  }

  if (sensorValue3 == 1){
    digitalWrite(relay3pin, HIGH);
  } else {
    digitalWrite(relay3pin, LOW);
  }





  
}
