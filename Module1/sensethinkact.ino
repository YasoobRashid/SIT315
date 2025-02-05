int SensorPin = 2;
int LedPin = 7;

void setup(){
	pinMode(SensorPin, INPUT);
 	pinMode(LedPin, OUTPUT);
  	Serial.begin(9600);
}

void loop(){
	int motion = digitalRead(SensorPin);
  	
  if(motion == HIGH) {
  	digitalWrite(LedPin, HIGH);
    Serial.println("Motion detected");
    delay(1000);
  }
  else{
    digitalWrite(LedPin, LOW);
    Serial.println("No Motion detected");
    delay(1000);
  }
}