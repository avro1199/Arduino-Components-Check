#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define btn_ok 13
#define btn_cnc 12
#define btn_up 14
#define btn_dwn 27
#define btn_lft 26
#define btn_rht 25

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // put your setup code here, to run once:
  pinMode(btn_ok, INPUT_PULLUP);
  pinMode(btn_cnc, INPUT_PULLUP);
  pinMode(btn_up, INPUT_PULLUP);
  pinMode(btn_dwn, INPUT_PULLUP);
  pinMode(btn_lft, INPUT_PULLUP);
  pinMode(btn_rht, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Rj Avro");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(btn_ok)){
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Ok");
  }
  if(!digitalRead(btn_cnc)){
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Cancel");
  }
  if(!digitalRead(btn_up)){
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Up");
  }
  if(!digitalRead(btn_dwn)){
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Down");
  }
  if(!digitalRead(btn_lft)){
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Left");
  }
  if(!digitalRead(btn_rht)){
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Right");
  }
  
}