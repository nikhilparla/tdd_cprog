#ifndef TIMESERVICE_H
#define TIMESERVICE_H

typedef struct Time
{
    int minuteOfDay;
    int dayOfWeek;
}Time;

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time *);

typedef void (*WakeupCallback)(void);

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback);


#endif // TIMESERVICE_H