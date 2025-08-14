#include "HardwareTimer.h"

#define CHANNELS 8
#define limit 60 // Limit for the PID output

#define PPM_PIN PA0 // PPM input pin (A0)

#define steering_pot PC1 // A4 for analog input (A4)
#define steering PA4     // DAC pin for steering output (A2)
#define accelarator PA5  // DAC pin for accelerator output (D13)

#define relay_fr PA7 // Relay pin for forward direction (D11)
#define brake_mf PC7 // Motor forward pin (D9)
#define brake_mb PA6 // Motor backward pin (D12)

HardwareTimer *MyTim;

// PPM Capture Variables
volatile uint16_t ppmValues[CHANNELS];
volatile uint8_t ppmIndex = 0;
volatile uint32_t lastCapture = 0;

int target_angle = 0; // Variable to store the target angle

// pid variables
float kp = 6, ki = 4.0, kd = 0; // PID coefficients
int previous_error = 0;         // Previous error for PID
int integral = 0;               // Integral term for PID

uint8_t speed = 0; // Speed variable for motor control

bool braked = false; // Brake state variables

void IC_Handler()
{                                               // No parameters
    uint32_t now = MyTim->getCaptureCompare(1); // CCR1 value
    uint32_t diff = (now >= lastCapture) ? (now - lastCapture) : ((0xFFFF - lastCapture) + now);
    lastCapture = now;

    if (diff > 3000)
    {
        ppmIndex = 0; // new frame
    }
    else if (ppmIndex < CHANNELS)
    {
        ppmValues[ppmIndex] = diff;
        ppmIndex++;
    }
}

void setup()
{

    // TIM2 on PA0 (A0)
    MyTim = new HardwareTimer(TIM2);

    MyTim->setMode(1, TIMER_INPUT_CAPTURE_RISING, PPM_PIN); // channel 1, rising edge, pin
    MyTim->setOverflow(0xFFFF, MICROSEC_FORMAT);            // microsecond resolution
    MyTim->attachInterrupt(1, IC_Handler);                  // channel, callback
    MyTim->setInterruptPriority(0, 0);                      // highest priority
    MyTim->resume();

    // --------------------------------------------------------------------------------------
    Serial2.begin(115200);

    pinMode(steering_pot, INPUT);
    pinMode(steering, OUTPUT);
    pinMode(accelarator, OUTPUT);
    pinMode(brake_mf, OUTPUT); // Motor forward pin
    pinMode(brake_mb, OUTPUT); // Motor backward pin
    pinMode(relay_fr, OUTPUT); // Set relay pin as output

    analogReadResolution(12); // Set ADC resolution to 12 bits
    analogWriteResolution(8); // Set PWM/DAC resolution to 8 bits
    analogWriteFrequency(20000);

    analogWrite(steering, 207);  // Initialize DAC output to 207
    analogWrite(accelarator, 0); //
    analogWrite(brake_mf, 0);    // Initialize motor forward pin to 0
    analogWrite(brake_mb, 0);    // Initialize motor backward pin to 0
    digitalWrite(relay_fr, HIGH);
}

void loop()
{
    target_angle = map(constrain(ppmValues[0], 1000, 2000), 1000, 2000, -35, 35); // Map PPM value to angle range
    Serial2.print("Target Angle: ");
    Serial2.println(target_angle);

    speed = map(constrain(ppmValues[2], 1050, 2000), 1050, 2000, 0, 255); // Map PPM value to speed
    if (braked)
    {
        analogWrite(accelarator, 0);
    }
    else
    {
        analogWrite(accelarator, speed);
    }
    Serial2.print("Speed: ");
    Serial2.println(speed);

    // Control Forward/Backward Relay
    digitalWrite(relay_fr, ppmValues[4] > 1500 ? HIGH : LOW); // Forward if PPM value is above 1500

    // Control Motor Brake
    if (ppmValues[7] > 1500) // Brake if PPM value is above 1500
    {
        if (!braked)
        {
            braked = true;
            analogWrite(accelarator, 0); // Stop the motor
            analogWrite(brake_mf, 250); // Brake motor forward
            analogWrite(brake_mb, 0);   // Stop motor backward
            Serial2.println("Brake applied, Motor stopped");
            delay(700);               // Delay to allow motor to stop
            analogWrite(brake_mf, 0); // Release brake motor forward
            analogWrite(brake_mb, 0); // Release brake motor backward
        }
    }
    else if (ppmValues[7] < 1500)
    {
        if (braked)
        {
            braked = false;
            analogWrite(brake_mf, 0);   // Brake motor forward
            analogWrite(brake_mb, 250); // Stop motor backward
            Serial2.println("Brake released, Motor running");
            delay(500);               // Delay to allow motor to run
            analogWrite(brake_mf, 0); // Release brake motor forward
            analogWrite(brake_mb, 0); // Release brake motor backward
        }
    }

    int current_angle = measure_angle();
    Serial2.print("Current Angle: ");
    Serial2.println(current_angle);

    // Calculate PID control
    int error = target_angle - current_angle; // Calculate error
    if (abs(error) < 2)                       // If error is small, reset integral term
    {
        // ki = 0; // Reset integral term if error is zero
        integral = 0; // Reset integral term
    }
    integral += error;                                         // Update integral term
    int derivative = error - previous_error;                   // Calculate derivative term
    int output = kp * error + ki * integral + kd * derivative; // PID output
    previous_error = error;                                    // Update previous error for next iteration
    output = constrain(output, -limit, limit);                 // Constrain output to DAC range
    Serial2.print("PID Output: ");
    Serial2.println(output);
    // Write output to DAC
    analogWrite(steering, constrain(207 + output, 10, 255)); // Write to DAC pin 25
    delay(20);
}

int measure_angle()
{
    int analogValue = analogRead(steering_pot); // Use GPIO 34 as analog input
    Serial2.print("Raw Value: ");
    Serial2.print(analogValue);
    Serial2.print(" | ");
    analogValue = map(constrain(analogValue, 1300, 2500), 1300, 2500, -35, 35); // Map to a range of 0-100
    Serial2.print("Current Angle: ");
    Serial2.print(analogValue);
    Serial2.println(" degrees");
    return analogValue; // Return the target angle
}