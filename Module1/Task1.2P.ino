int SensorPin = 2;   
int LedPin = 7;      
int ButtonPin = 3;   

volatile bool motionDetected = false; 

void motionISR() {
  motionDetected = true;  
}

void setup() {
  pinMode(SensorPin, INPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);  
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(SensorPin), motionISR, RISING); 
}

void loop() {
  if (motionDetected) {
    Serial.println("Motion detected - LED ON");
    digitalWrite(LedPin, HIGH);
    
    unsigned long startTime = millis(); 

    while (millis() - startTime < 3000) {  
      if (digitalRead(ButtonPin) == LOW) { 
        Serial.println("Button pressed - LED OFF");
        digitalWrite(LedPin, LOW);
        motionDetected = false; 
        return; 
      }
    }

    digitalWrite(LedPin, LOW); 
    Serial.println("Time up - LED OFF");
    motionDetected = false; 
  }
}
