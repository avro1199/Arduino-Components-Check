void setup() {
    Serial.begin(115200);
}

void loop() {
    int analogValue = analogRead(34); // Use GPIO 34 as analog input
    Serial.print("Raw Value: ");
    Serial.print(analogValue);
    Serial.print(" | ");
    analogValue = map(constrain(analogValue, 1300, 2500), 1300, 2500, -35, 35); // Map to a range of 0-100
    Serial.print("Analog Value: ");
    Serial.print(analogValue);
    Serial.println(" degrees");
    delay(100);
}