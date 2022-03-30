
#include "LightScheduler.h"
#include "TimeService.h"
#include "LightController.h"

enum 
{
    UNUSED = -1,
    TURN_OFF,
    TURN_ON,
    MAX_EVENTS = 128,
};

typedef struct 
{
    int id;
    int minuteOfDay;
    int event;
}ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
    if(lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    if(lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{
    if(lightEvent->id == UNUSED)
        return;
    if(lightEvent->minuteOfDay != time->minuteOfDay)
        return;
    operateLight(lightEvent);
}

void LightScheduler_WakeUp(void)
{
    Time time;
    TimeService_GetTime(&time);

    processEventDueNow(&time, &scheduledEvent);   
}

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    scheduledEvent.id = id;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event =  event;
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day,minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day,minuteOfDay, TURN_OFF);
}

