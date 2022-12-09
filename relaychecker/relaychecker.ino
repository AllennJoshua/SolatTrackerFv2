  int relay1pin = 25;
  int relay2pin = 26;
  int relay3pin = 27;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay1pin, OUTPUT);   // setting relays as output pins
  pinMode(relay2pin, OUTPUT);
  pinMode(relay3pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay1pin, HIGH);
  digitalWrite(relay2pin, HIGH);
  digitalWrite(relay3pin, HIGH);
  Serial.println("ON!");
  delay(1000);
  digitalWrite(relay1pin, LOW);
  digitalWrite(relay2pin, LOW);
  digitalWrite(relay3pin, LOW);
  Serial.println("OFF!");
  delay(1000);
}
