#include "servos.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

// Private PCA object
static Adafruit_PWMServoDriver pwm(0x40);
static bool initialized = false;

// PCA9685 servo pulse limits
#define SERVOMIN 150
#define SERVOMAX 600

// Servo channels
#define SERVO1_CH 0
#define SERVO2_CH 1

// Optional: store last positions
static int servo1_pos = 90;
static int servo2_pos = 90;

// Map angle to pulse
static int angleToPulse(int angle) {
    angle = constrain(angle, 0, 180);
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// Initialize PCA and servos
void initServos() {
    pwm.begin();
    pwm.setPWMFreq(50); // 50Hz for SG90
    initialized = true;

    // Set initial positions
    pwm.setPWM(SERVO1_CH, 0, angleToPulse(servo1_pos));
    pwm.setPWM(SERVO2_CH, 0, angleToPulse(servo2_pos));
}

// Update servo positions based on state
void updateServos(SystemState state) {
    if (!initialized) return;

    switch (state) {
        case IDLE:
            // small idle jitter/random motion
            servo1_pos = 90 + random(-10, 10);
            servo2_pos = 90 + random(-10, 10);
            break;

        case PROXIMITY:
            // reactive pattern for close object
            servo1_pos = random(30, 150);
            servo2_pos = random(30, 150);
            break;

        case TILTED:
            // reactive pattern for tilt
            servo1_pos = random(0, 180);
            servo2_pos = random(0, 180);
            break;
    }

    pwm.setPWM(SERVO1_CH, 0, angleToPulse(servo1_pos));
    pwm.setPWM(SERVO2_CH, 0, angleToPulse(servo2_pos));
}