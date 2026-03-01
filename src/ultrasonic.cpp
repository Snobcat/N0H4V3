#include "ultrasonic.h"
#include "pins.h"
#include <Arduino.h>
float readUltrasonic() {
    // Trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo (timeout 30ms)
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if (duration == 0) return -1.0; // out of range

    // Convert to cm
    float distance_cm = duration * 0.0343 / 2.0;
    return distance_cm;
}