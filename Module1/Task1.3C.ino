#define MOTION_SENSOR_PIN 2  
#define TEMP_SENSOR_PIN A0
#define LED_PIN 7            

volatile bool motionDetected = false;

void motionISR() {
    motionDetected = true;
}

void setup() {
    pinMode(MOTION_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(MOTION_SENSOR_PIN), motionISR, RISING);
    Serial.begin(9600);
}

void loop() {
    if (motionDetected) {
        Serial.println("Motion detected!");
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        motionDetected = false;
    }

    int sensorValue = analogRead(TEMP_SENSOR_PIN);
    float temperature = sensorValue * (5.0 / 1023.0) * 100.0;  

    Serial.print("Temperature: ");
    Serial.println(temperature);

    if (temperature > 30) { 
        Serial.println("High temperature detected!");
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
    }

    delay(1000);
}
