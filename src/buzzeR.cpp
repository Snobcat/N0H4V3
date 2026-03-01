#include "buzzeR.h"
#include <Arduino.h>
#include "pins.h"
static bool initializedBuzzer = false;
static unsigned long lastBeep = 0;
static unsigned long beepInterval = 1000;
void initBuzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
    initializedBuzzer = true;
}
//helper to beep the buzzer for a duration
static void beep(unsigned int durationMs) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(durationMs);
    digitalWrite(BUZZER_PIN, LOW);
}
void updateBuzzer(SystemState systemState) {
    if (!initializedBuzzer) {return;}
    unsigned long now = millis();
    switch (systemState) {
        case IDLE:
            //random beeps intervals
            if (now - lastBeep > beepInterval) {
                beep(100);
                lastBeep = now;
            }
            break;
        case PROXIMITY:
            //caseholder for noise
            for (int i = 0; i < 3; i++) {
                digitalWrite(BUZZER_PIN, HIGH);
                delay(50);   // 50 ms beep
                digitalWrite(BUZZER_PIN, LOW);
                delay(50);   // 50 ms pause between beeps
            }
            break;
        case TILTED:
            //caseholder
            int beeps = random(1, 5);            // 1 to 4 beeps
            for (int i = 0; i < beeps; i++) {
                digitalWrite(BUZZER_PIN, HIGH);
                delay(random(30, 120));          // random beep length 30-120ms
                digitalWrite(BUZZER_PIN, LOW);
                delay(random(50, 200));          // random pause 50-200ms
            }
            break;
    }
}