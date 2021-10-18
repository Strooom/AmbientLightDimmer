#include <Arduino.h>
#include "runtimer.h"


#define ledPin 10
#define photoResistorPin A0

intervalTimer writeOutputTimer(100U);
intervalTimer readInputTimer(25U);
intervalTimer displayValuesTimer(500U);

constexpr uint8_t nmbrSamples{8U};
uint32_t ambientLight[nmbrSamples];
uint8_t sampleIndex{0};
uint32_t brightness{0};

void setup() {
    delay(200U);
    Serial.begin(115200U);
    Serial.flush();

    pinMode(ledPin, OUTPUT);
    pinMode(photoResistorPin, INPUT);
}

void loop() {
    if (readInputTimer.expired()) {
        ambientLight[sampleIndex] = analogRead(photoResistorPin);
        sampleIndex               = (sampleIndex + 1) % nmbrSamples;
    }

    if (writeOutputTimer.expired()) {
        uint32_t totalAmbientLight{0};
        for (int i = 0; i < nmbrSamples; i++) {
            totalAmbientLight = totalAmbientLight + ambientLight[i];
        }
        uint32_t averageAmbientLight = totalAmbientLight / (nmbrSamples * 4);
        if (averageAmbientLight > 255) {
            averageAmbientLight = 255;
        }
        brightness = 255 - averageAmbientLight;
        analogWrite(ledPin, brightness);
    }

    if (displayValuesTimer.expired()) {
        Serial.print("ambient = ");
        Serial.print(ambientLight[0]);
        Serial.print(" | brightness = ");
        Serial.println(brightness);
    }
}