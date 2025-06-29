//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  pinMode(PA0, INPUT_PULLUP);
  pinMode(PA1, INPUT);

  Wire.setSDA(PB9);
  Wire.setSCL(PB8);
  Wire.begin();

  lcd.init();  // initialize the lcd

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("Hail Arduino!");
  lcd.setCursor(0, 2);
  lcd.print("Arduino LCM IIC 2004");
  lcd.setCursor(2, 3);
  lcd.print("Power By Rj Avro!");

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 1);
  // lcd.noBacklight();
  lcd.print("This is Rj Avro (+)");
  lcd.setCursor(0, 3);
  // lcd.noBacklight();
  lcd.print("One Last Time->");
}

uint32_t m1;
void loop() {

  // delay(4000);
  m1 = micros();
  Serial.print(digitalRead(PA0));
  Serial.print(" -> ");
  Serial.print(analogRead(PA1));
  Serial.print(" ==>> ");
  Serial.println(micros()-m1);

  lcd.setCursor(16, 3);
  lcd.print(analogRead(PA1));
  lcd.print("    ");
  delay(400);
}
