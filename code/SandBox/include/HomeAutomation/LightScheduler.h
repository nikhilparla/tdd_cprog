#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

enum Day
{
    NONE = -1,
    SUNDAY =1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY = 7,
    WEEKEND,
    WEEKDAY,
    EVERYDAY = 10,
};

typedef enum Day Day ;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_WakeUp(void);

#endif