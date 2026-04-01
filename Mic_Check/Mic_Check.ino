void setup() {
    Serial.begin(115200);
}

void loop() {
    // Your code here
    Serial.println(analogRead(A0));
    // delayMicroseconds(10);
}