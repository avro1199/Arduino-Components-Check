// Set motor speeds: left_speed and right_speed
static void setMotor(int left_speed, int right_speed)
{
    // Left motor
    if (left_speed > 0) // Forward
    {
        ledcWrite(LEFT_MOTOR_BACKWARD, 0);
        ledcWrite(LEFT_MOTOR_FORWARD, (uint32_t)left_speed);
        digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
    }
    else if (left_speed < 0) // Backward
    {
        ledcWrite(LEFT_MOTOR_FORWARD, 0);
        ledcWrite(LEFT_MOTOR_BACKWARD, (uint32_t)(-left_speed));
        digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
    }
    else
    {
        // Neutral
        digitalWrite(LEFT_MOTOR_ENABLE, LOW);
    }

    // Right motor
    if (right_speed > 0) // Forward
    {
        ledcWrite(RIGHT_MOTOR_BACKWARD, 0);
        ledcWrite(RIGHT_MOTOR_FORWARD, (uint32_t)right_speed);
        digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    }
    else if (right_speed < 0) // Backward
    {
        ledcWrite(RIGHT_MOTOR_FORWARD, 0);
        ledcWrite(RIGHT_MOTOR_BACKWARD, (uint32_t)(-right_speed));
        digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    }
    else
    {
        // Neutral
        digitalWrite(RIGHT_MOTOR_ENABLE, LOW);
    }
}

static void allMotorsNeutral()
{
    digitalWrite(LEFT_MOTOR_ENABLE, LOW);
    digitalWrite(RIGHT_MOTOR_ENABLE, LOW);
}

static void allMotorsBrake()
{
    ledcWrite(LEFT_MOTOR_FORWARD, 0);
    ledcWrite(LEFT_MOTOR_BACKWARD, 0);
    ledcWrite(RIGHT_MOTOR_FORWARD, 0);
    ledcWrite(RIGHT_MOTOR_BACKWARD, 0);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
}