void sensor_read() {
  sensor = 0;
  sum_trn = 0;
  sum_pid = 0;
  for (int i = 0; i < 10; i++) {
    my_mux.channel(i);
    delayMicroseconds(2);
    s[i] = analogRead(36);
    s[i] > thresh[i] ? s[i] = 0 : s[i] = 1;
    sensor += s[i] * base[i];
  }
  sum_trn = s[2] + s[3] + s[4] + s[5] + s[6] + s[7];
  sum_pid = s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] + s[7] + s[8] + s[9];
}

void show_digital() {
  oled.set2X();
  while (digitalRead(btn_m)) {
    sensor_read();
    oled.clear();
    oled.println(sensor, BIN);
    oled.println(sum_pid);
    oled.println(sum_trn);
    delay(100);
  }
  oled.set1X();
}

void show_analog() {
  while (digitalRead(btn_m)) {
    for (int i = 0; i < 10; i++) {
      my_mux.channel(i);
      delayMicroseconds(2);
      s[i] = analogRead(36);
    }
    for (int i = 0; i < 10; i++) {
      Serial.print(s[i]);
      Serial.print("  ");
    }
    Serial.println();

    oled.clear();
    for (int i = 3; i >= 0; i--) {
      oled.setCursor(0, 2 * i);
      oled.print(s[3 - i]);
    }
    for (int i = 4; i < 7; i++) {
      oled.print(" ");
      if (i == 4 || i == 6) {
        oled.print(" ");
      }
      oled.print(s[i]);
    }
    for (int i = 7; i < 10; i++) {
      oled.setCursor(102, 2 * (i - 6));
      oled.print(s[i]);
    }
  }
}