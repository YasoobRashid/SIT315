const byte LED_PIN = 13;
const byte METER_PIN = A4;
double lastFrequency = 0.5; 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  Serial.begin(9600);
  
  startTimer(lastFrequency); 
}

void loop() {
  double timerFrequency = getPotentiometerFrequency(); 
  
  if (abs(timerFrequency - lastFrequency) > 0.05) {
    lastFrequency = timerFrequency;
    startTimer(timerFrequency);
    Serial.print("Updated Frequency: ");
    Serial.println(timerFrequency);
  }

  delay(500);
}

double getPotentiometerFrequency() {
  int potValue = analogRead(METER_PIN);
  return map(potValue, 0, 1023, 1, 20) / 10.0;  
}

void startTimer(double timerFrequency) {
  noInterrupts();  

  TCCR1A = 0;  
  TCCR1B = 0;
  TCNT1  = 0;  

  int ocrValue = (16000000 / (1024 * timerFrequency)) - 1;
  OCR1A = ocrValue;

  TCCR1B |= (1 << WGM12);  
  TCCR1B |= (1 << CS12) | (1 << CS10); 
  TIMSK1 |= (1 << OCIE1A); 

  interrupts();  
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
