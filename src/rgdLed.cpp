#include "rgdLed.h"
#include "pins.h"
#include <Arduino.h>
#include "system_state.h"

static bool initialized = false;

void initRGB() {
    pinMode(RGB_R, OUTPUT);
    pinMode(RGB_G, OUTPUT);
    pinMode(RGB_B, OUTPUT);

    // optional startup blink
    digitalWrite(RGB_R, HIGH);
    digitalWrite(RGB_G, LOW);
    digitalWrite(RGB_B, LOW);
    delay(200);
    digitalWrite(RGB_R, LOW);
    digitalWrite(RGB_G, HIGH);
    digitalWrite(RGB_B, LOW);
    delay(200);
    digitalWrite(RGB_R, LOW);
    digitalWrite(RGB_G, LOW);
    digitalWrite(RGB_B, HIGH);
    delay(200);
    digitalWrite(RGB_R, LOW);
    digitalWrite(RGB_G, LOW);
    digitalWrite(RGB_B, LOW);

    initialized = true;
}

void updateRGB(SystemState systemState) {
    if (!initialized) return;

    switch(systemState) {
        case IDLE:
            // Blue for idle
            digitalWrite(RGB_R, LOW);
            digitalWrite(RGB_G, LOW);
            digitalWrite(RGB_B, HIGH);
            break;

        case PROXIMITY:
            // Yellow for proximity
            digitalWrite(RGB_R, HIGH);
            digitalWrite(RGB_G, HIGH);
            digitalWrite(RGB_B, LOW);
            break;

        case TILTED:
            // Red for tilt
            digitalWrite(RGB_R, HIGH);
            digitalWrite(RGB_G, LOW);
            digitalWrite(RGB_B, LOW);
            break;
    }
}