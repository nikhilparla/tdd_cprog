#include "LightController.h"

enum 
{
    LIGHT_ID_UNKNOWN = -1,
    LIGHT_STATE_UNKNOWN = -1,
    LIGHT_OFF = 0,
    LIGHT_ON = 1,
};

void LightController_Create(void);
int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);