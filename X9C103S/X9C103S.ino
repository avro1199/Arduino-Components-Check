// Digital potentiometer pins
const int udPin = 7;   // U/D (Up/Down)
const int incPin = 8;  // INC (Increment)
const int csPin = 9;   // CS (Chip Select)
const int vccPin = 12;   // power to digipot

// Analog pin for voltage divider
const int rwPin = A0;  // Analog pin to read from RW (Wiper)

// Time delay between INC pulses
const int incDelay = 10; 
const int csDelay = 10;

// Function to initialize the potentiometer and Serial Monitor
void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);  // Set baud rate for serial communication
  
  // Set pin modes
  pinMode(udPin, OUTPUT);
  pinMode(incPin, OUTPUT);
  pinMode(csPin, OUTPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(rwPin, INPUT);  // Set RW pin as input for analog reading

  digitalWrite(incPin, HIGH);
  delay(incDelay);
  digitalWrite(csPin, HIGH); // Start with chip deselected
  delay(csDelay);
  digitalWrite(vccPin, HIGH);
  Serial.println("Setup complete.");
}

void incrementResistance(int steps) {
  digitalWrite(udPin, HIGH); // Set direction to increment
  digitalWrite(csPin, LOW);  // Enable chip
    
  for (int i = 0; i < steps; i++) {
    digitalWrite(incPin, HIGH); // Toggle INC
    delay(incDelay);
    digitalWrite(incPin, LOW);
    delay(incDelay);
  }
  
  digitalWrite(incPin, HIGH);
  delay(incDelay);
  digitalWrite(csPin, HIGH); // Save to memory
  delay(csDelay);
  Serial.print("Incremented resistance by ");
  Serial.print(steps);
  Serial.println(" steps.");
}

// Function to decrement resistance by a given number of steps
void decrementResistance(int steps) {
   digitalWrite(udPin, LOW);  // Set direction to decrement
   digitalWrite(csPin, LOW);  // Enable chip
 
  
  for (int i = 0; i < steps; i++) {
    digitalWrite(incPin, HIGH); // Toggle INC
    delay(incDelay);
    digitalWrite(incPin, LOW);
    delay(incDelay);
  }

  digitalWrite(incPin, HIGH);
  delay(incDelay);
  digitalWrite(csPin, HIGH); // Save to memory
  delay(csDelay);
  Serial.print("Decremented resistance by ");
  Serial.print(steps);
  Serial.println(" steps.");
}

// Function to save current resistance to non-volatile memory
void saveToMemory() {
  digitalWrite(csPin, LOW);
   delay(csDelay);
  digitalWrite(incPin, HIGH);
  delay(incDelay);
  digitalWrite(csPin, HIGH); // Bring CS high to store current position
   delay(csDelay);
  Serial.println("Current resistance saved to memory.");
}

// Function to read the voltage divider output
void readResistance() {
  int analogValue = analogRead(A0);  // Read analog value
  Serial.print("Voltage divider output: "); 
  Serial.println(analogValue);  // Output analog value to Serial Monitor
}

// Example loop to increment, save, then decrement, and save
void loop() {

  while (!Serial){}   // wait until serial monitor is opened

  if(digitalRead(3)==HIGH){
    incrementResistance(1);  // Increment by 10 steps
    delay(500);
  }

 if(digitalRead(2)==HIGH){
    decrementResistance(1);  // Increment by 10 steps
    delay(500);
  }

 if(digitalRead(4)==HIGH){
    readResistance();  // Increment by 10 steps
    delay(500);
  }
  
}
