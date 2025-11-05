#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    bool isStartActive;
    bool isStopActive;
    uint32_t startTime;
    uint16_t step;
} ATM_Progress_t;

void ATM_Init(ATM_Progress_t *process);

void ATM_StartConfigBegin(ATM_Progress_t *progess);
bool ATM_IsStartConfigure(ATM_Progress_t *progess);
void ATM_StopConfigBegin(ATM_Progress_t *progess);

void ATM_StartConfigEnd(ATM_Progress_t *progess);
bool ATM_IsStopConfigure(ATM_Progress_t *progess);
void ATM_StopConfigEnd(ATM_Progress_t *progess);

uint32_t ATM_GetCurrentTimeMs(void);
bool ATM_OnStep(ATM_Progress_t *progess, uint16_t stepProgress);
uint32_t ATM_GetElapTimeMs(ATM_Progress_t *progess);
bool ATM_JumpToStep(ATM_Progress_t *progess, uint16_t stepProgress);
bool ATM_OnTime(ATM_Progress_t *progess, uint32_t timeMs);
void ATM_JumpToNextStep(ATM_Progress_t *progess);
uint16_t ATM_GetCurrentStep(ATM_Progress_t *progess);
// try to use #define to just fill a block of code functions
// #define test(block) do { block } while(0)
// just call: test({ /* code here */ })