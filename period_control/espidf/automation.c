#include "automation.h"

#ifdef ESP_PLATFORM
#include "esp_log.h"
#include <Arduino.h>
#elif defined(ARDUINO)
#include <Arduino.h>
#endif

uint32_t ATM_GetCurrentTimeMs(void)
{
#ifdef ESP_PLATFORM
    return millis(); // Convert microseconds to milliseconds
#elif defined(ARDUINO)
    return millis();
#endif
}

void ATM_Init(ATM_Progress_t *process)
{
    process->isStartActive = false;
    process->isStopActive = true;
    process->startTime = 0;
    process->step = 0;
}

void ATM_StartConfigBegin(ATM_Progress_t *progess)
{
    progess->isStartActive = false;
    progess->startTime = ATM_GetCurrentTimeMs();
}
bool ATM_IsStartConfigure(ATM_Progress_t *progess) {
    return !progess->isStartActive; // return true if start has been configured
}
void ATM_StopConfigBegin(ATM_Progress_t *progess) { 
    progess->isStartActive = true; // mark start as configured
}

void ATM_StartConfigEnd(ATM_Progress_t *progess) { 
    progess->isStopActive = false; // mark stop as not yet configured
}

bool ATM_IsStopConfigure(ATM_Progress_t *progess) { 
    return !progess->isStopActive; // return true if stop has been configured
}
void ATM_StopConfigEnd(ATM_Progress_t *progess) { 
    progess->isStopActive = true; // mark stop as configured
}

bool ATM_OnStep(ATM_Progress_t *progess, uint16_t stepProgress)
{
    return (progess->step == stepProgress); // return true if current step matches the given step
}

uint32_t ATM_GetElapTimeMs(ATM_Progress_t *progess)
{
    if (!progess->isStartActive)
    {
        return 0;
    }
    return ATM_GetCurrentTimeMs() - progess->startTime;
}

bool ATM_JumpToStep(ATM_Progress_t *progress, uint16_t stepProgress)
{
    progress->step = stepProgress;
    progress->isStartActive = false;
    progress->isStopActive = true;
    progress->startTime = ATM_GetCurrentTimeMs();
    return true;
}

bool ATM_OnTime(ATM_Progress_t *progess, uint32_t timeMs)
{
    static bool hasStarted = false;
    if(!hasStarted && ATM_GetElapTimeMs(progess) >= timeMs){
        hasStarted = true;
    }
    if (hasStarted && ATM_GetElapTimeMs(progess) < timeMs) {
        hasStarted = false; // reset for next call
    }
    return hasStarted;
}
    
void ATM_JumpToNextStep(ATM_Progress_t *progess) { 
    progess->step += 1; // move to the next step
    progess->startTime = ATM_GetCurrentTimeMs();
}

uint16_t ATM_GetCurrentStep(ATM_Progress_t *progess) { 
    return progess->step; // return the current step 
}