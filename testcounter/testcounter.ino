

int counterr = 0;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  counterr = counterr + 1;
        Serial.println(counterr);
  if (counterr >= 3000){
//        Serial.println("done with 50 counter");
//        Serial.println(counterr);
        counterr = counterr - 3000;

    
  }




}
