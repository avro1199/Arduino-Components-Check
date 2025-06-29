void motor(int lms, int rms) {
  if (lms >= 0) {
    analogWrite(lmf, lms);
    analogWrite(lmb, 0);
    digitalWrite(en_l, 1);
  } else if (lms < 0) {
    lms *= -1;
    analogWrite(lmf, 0);
    analogWrite(lmb, lms);
    digitalWrite(en_l, 1);
  }

  if (rms >= 0) {
    analogWrite(rmf, rms);
    analogWrite(rmb, 0);
    digitalWrite(en_r, 1);
  } else if (rms < 0) {
    rms *= -1;
    analogWrite(rmf, 0);
    analogWrite(rmb, rms);
    digitalWrite(en_r, 1);
  }
}

void neutral() {
  digitalWrite(en_r, 0);
  digitalWrite(en_l, 0);
}

void brake() {
  digitalWrite(en_r, 1);
  digitalWrite(en_l, 1);

  analogWrite(lmf, 0);
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(rmb, 0);
}