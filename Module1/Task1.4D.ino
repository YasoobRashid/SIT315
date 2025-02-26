#define trigPin 4
#define echoPin 5

int pirPin = 2;       // PIR Sensor (External Interrupt)
int buttonPin = 3;    // Push Button
int ledPin = 7;       // LED

volatile bool motionDetected = false;

void pirISR() {
    motionDetected = true;
}

ISR(TIMER1_COMPA_vect) {
    digitalWrite(ledPin, !digitalRead(ledPin));
}

void setup() {
    pinMode(pirPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(pirPin), pirISR, RISING);

    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 15624;  
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

long getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2; 
    return distance;
}

void loop() {
    if (motionDetected) {
        Serial.println("PIR Motion detected - LED ON!");
        digitalWrite(ledPin, HIGH);
        delay(3000);
        digitalWrite(ledPin, LOW);
        motionDetected = false;
    }

    long distance = getDistance();
    if (distance > 0 && distance < 50) { // If object is closer than 10cm
        Serial.println("Object detected close - LED ON!");
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
    }

    if (digitalRead(buttonPin) == LOW) {
        Serial.println("Button Pressed - LED OFF!");
        digitalWrite(ledPin, LOW);
        motionDetected = false;
    }
}
