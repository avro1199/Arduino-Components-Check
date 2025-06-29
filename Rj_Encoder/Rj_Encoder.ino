bool state, data;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  DDRB = 0b00100000;

  Serial.begin(9600);

  state = digitalRead(5);

  Serial.print("Initial value:");
  Serial.println(count);

}

void loop() {
  // put your main code here, to run repeatedly:
  data = digitalRead(5);
  if(data != state){
    state = data;
    if(digitalRead(6) != data){
      count++;
      Serial.println(count);
      PORTB = 0b00100000;
      // digitalWrite(13, HIGH);

    }
    else if(digitalRead(6) == data){
      count--;
      Serial.println(count);
      PORTB = 0b00000000;
      // digitalWrite(13, LOW);
    }
  }

}
