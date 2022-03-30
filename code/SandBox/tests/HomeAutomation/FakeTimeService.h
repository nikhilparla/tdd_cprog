#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#include "TimeService.h"

enum 
{
    TIME_UNKNOWN = -1,
};

void FakeTimeService_SetDay(int);
void FakeTimeService_SetMinute(int);
WakeupCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);
void FakeTimeService_MinuteIsUp(void);

#endif