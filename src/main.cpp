#include <Arduino.h>
#include "runtimer.h"
#include "logging.h"

#define ledPin 10
#define photoResistorPin A1

constexpr uint32_t brightnessIncrement{10U};
constexpr uint32_t brightnessMax{120U};

intervalTimer writeOutputTimer(250U);
uLog theLog(loggingLevel::Debug, true);
uint32_t brightness{0};

void setup() {
    delay(200U);
    Serial.begin(115200U);
    Serial.flush();
    theLog.setOutputIsAvailable(true);

    pinMode(ledPin, OUTPUT);
    pinMode(photoResistorPin, INPUT);
}

void loop() {
    if (writeOutputTimer.expired()) {
        theLog.snprintf(loggingLevel::Debug, "brightness = %d", brightness);
        analogWrite(ledPin, brightness);
        brightness = ((brightness + brightnessIncrement) % brightnessMax);
    }
}