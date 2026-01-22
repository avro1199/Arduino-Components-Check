#include <Arduino.h>

#define DEBUG

// -------------------- Motor PWM (LEDC) --------------------
static const uint8_t LEFT_MOTOR_FORWARD = 13;
static const uint8_t LEFT_MOTOR_BACKWARD = 12;
static const uint8_t LEFT_MOTOR_ENABLE = 14;
static const uint8_t RIGHT_MOTOR_ENABLE = 27;
static const uint8_t RIGHT_MOTOR_FORWARD = 26;
static const uint8_t RIGHT_MOTOR_BACKWARD = 25;

// Debug options
static const uint8_t LED = 2;

// LEDC configuration
static const uint32_t PWM_FREQ_HZ = 20000; // 20 kHz
static const uint8_t PWM_RES_BITS = 10;    // 10-bit resolution
static const uint32_t PWM_MAX = (1u << PWM_RES_BITS) - 1;

// RC mapping configuration
static const int RC_MIN = 1000;
static const int RC_MID = 1500;
static const int RC_MAX = 2000;
static const int RC_DEADBAND = 10; // around center (tune if needed)

// Failsafe: if no valid frame recently, stop motors
static const uint32_t FAILSAFE_US = 100000; // 100 ms
static uint32_t lastFrameUs = 0;

// -------------------- iBUS (UART) --------------------
static const uint32_t IBUS_BAUD = 115200;
static const uint8_t IBUS_FRAME_LEN = 32;

HardwareSerial IBusSerial(2);
static const int IBUS_RX_PIN = 16; // iBUS signal
static const int IBUS_TX_PIN = 17; // unused

// iBUS frame buffer
static uint8_t frame[IBUS_FRAME_LEN];
static uint8_t idx = 0;

// Speed control
static uint16_t TOP_SPEED = 0;
static uint16_t BRAKE_THRESHOLD = 1300; // RC value below which braking is applied

void setup()
{
    // Avoid Serial printing in fast control loops; keep minimal here.
    Serial.begin(115200);
    delay(200);

    // iBUS UART
    IBusSerial.begin(IBUS_BAUD, SERIAL_8N1, IBUS_RX_PIN, IBUS_TX_PIN);

    // LEDC setup
    ledcAttach(LEFT_MOTOR_FORWARD, PWM_FREQ_HZ, PWM_RES_BITS);
    ledcAttach(LEFT_MOTOR_BACKWARD, PWM_FREQ_HZ, PWM_RES_BITS);
    ledcAttach(RIGHT_MOTOR_FORWARD, PWM_FREQ_HZ, PWM_RES_BITS);
    ledcAttach(RIGHT_MOTOR_BACKWARD, PWM_FREQ_HZ, PWM_RES_BITS);
    pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
    pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);

    // Debug
    pinMode(LED, OUTPUT);

    allMotorsNeutral();
    lastFrameUs = micros();

    Serial.println("FS-IA10B -> iBUS -> ESP32 -> 2-Motor BTS Soccer control started...");
    Serial.println("CH2=throttle, CH1=steering, differential mix.");
}

void loop()
{
    static uint16_t ch[14];
    int leftSpeed, rightSpeed;

    // Parse frames as they arrive; update motor outputs immediately on a valid frame.
    if (readIbusFrame(ch))
    {
        lastFrameUs = micros();

        // Channel indexing: ch[0]=CH1, ch[1]=CH2, ...
        TOP_SPEED = (uint16_t)map((int)ch[2], RC_MIN, RC_MAX, 0, PWM_MAX); // CH3 for top speed limit

        if (TOP_SPEED < 10)
        {
            allMotorsNeutral();
            digitalWrite(LED, HIGH); // Indicate no speed
            return;
        }

        if (ch[3] < BRAKE_THRESHOLD) // CH4 for e-stop
        {
            allMotorsBrake();
            digitalWrite(LED, HIGH); // Indicate braking
            return;
        }

        digitalWrite(LED, LOW); // Normal operation

        // Differential mix (i.e. leftSpeed = CH2+CH1, rightSpeed = CH2-CH1)
        // Mix can be done in the transmitter for better control.
        int steering = rcToSpeed((int)ch[0]); // CH1
        int throttle = rcToSpeed((int)ch[1]); // CH2

        if (ch[7] > 1500 && throttle < 100) // CH8 for reverse
        {
            leftSpeed = constrain((throttle - steering), -((int)TOP_SPEED), (int)TOP_SPEED);
            rightSpeed = constrain((throttle + steering), -((int)TOP_SPEED), (int)TOP_SPEED);
        }
        else
        {
            leftSpeed = constrain((throttle + steering), -((int)TOP_SPEED), (int)TOP_SPEED);
            rightSpeed = constrain((throttle - steering), -((int)TOP_SPEED), (int)TOP_SPEED);
        }

        setMotor(leftSpeed, rightSpeed);

// Checking in Serial Monitor
#ifdef DEBUG
        Serial.print("Left Speed: ");
        Serial.print(leftSpeed);
        Serial.print(" | Right Speed: ");
        Serial.println(rightSpeed);
#endif
    }

    // Failsafe: stop if signal lost
    uint32_t now = micros();
    if ((uint32_t)(now - lastFrameUs) > FAILSAFE_US)
    {
        allMotorsNeutral();
    }

    // No delays here: keep loop responsive.
}
