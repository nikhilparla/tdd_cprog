#include "FakeTimeService.h"
// #include "common.h"

static Time fakeTime;
static WakeupCallback callback;
static int period;

void TimeService_Create(void)
{
    fakeTime.minuteOfDay = -1;
    fakeTime.dayOfWeek = -1;
    callback = NULL;
    period = -1;
}

void TimeService_Destroy(void)
{

}

void FakeTimeService_MinuteIsUp()
{
    if(callback != NULL)
        callback();
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
    if(cb == callback && period == seconds)
    {
        callback = NULL;
        period = 0;
    }
}

void TimeService_GetTime(Time *time)
{
    time->minuteOfDay = fakeTime.minuteOfDay;
    time->dayOfWeek = fakeTime.dayOfWeek;
}

void FakeTimeService_SetMinute(int minute)
{
    fakeTime.minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day)
{
    fakeTime.dayOfWeek = day;
}

WakeupCallback FakeTimeService_GetAlarmCallback(void)
{
    return callback;
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return period;
}