#include <Wire.h>
#include <Arduino.h>
#include "servos.h"
#include "pins.h"
#include "rgdLed.h"
#include "buzzeR.h"
#include "oledScreen.h"
#include "system_state.h"
#include "ultrasonic.h"
SystemState systemState;
void setup() {
    Wire.begin(I2C_SDA, I2C_SCL);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TILT_PIN, INPUT_PULLUP);
    pinMode(RGB_R, OUTPUT);
    pinMode(RGB_G, OUTPUT);
    pinMode(RGB_B, OUTPUT);
    initServos();
    initRGB();
    initBuzzer();
    initOled();
}

void loop() {
// write your code here
    //sensory read
    bool tilted = digitalRead(TILT_PIN) == LOW;
    float distance = readUltrasonic();
    //state decision
    if (tilted) {
        systemState = TILTED;
    }
    else if (distance > 0 && distance < 2.0f) {
        systemState = PROXIMITY;
    }
    else {
        systemState = IDLE;
    }
    updateServos(systemState);
    updateRGB(systemState);
    updateBuzzer(systemState);
    updateOled();

}