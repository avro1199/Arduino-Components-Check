void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial2.begin(115200);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on
    Serial2.println("LED is ON");
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED off
    Serial2.println("LED is OFF");
    delay(1000);
    // Add more functionality as needed
    // For example, reading sensors, controlling motors, etc.
}