#include <Arduino.h>
#include "automation.h"

automationProgress_t progress;

void setup() {
    Serial.begin(115200);
    automationInit(&progress);
}

void loop() {
    // put your main code here, to run repeatedly:
    if(progessOnStep(&progress, 0)){
        if(automationIsStartConfigure(&progress)){
            Serial.println("Automation Started");// this one runs once at start
            stopConfigureStartComplete(&progress);
        }
        // loop code here
        Serial.print("Progress: ");
        Serial.println(progress.progress);
        Serial.print("Elapsed Time: ");
        Serial.println(automationGetEslapsedTime(&progress));
        if(automationIsStopConfigure(&progress)){
            Serial.println("Automation Stopped");// this one runs once at stop
            stopConfigureStopComplete(&progress);
            jumpToNextStep(&progress);
        }
    }
}

