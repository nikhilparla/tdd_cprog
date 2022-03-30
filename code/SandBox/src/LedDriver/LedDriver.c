/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include "LedDriver.h"
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>


static uint16_t * ledAddress;
static uint16_t ledsImage;   // store the value of the bits at all times. I/O map variable not readable
void LedDriver_Create(uint16_t *address)
{
    ledAddress = address;
    ledsImage = 0xffff;
    *ledAddress = ALL_LEDS_OFF;
}

void LedDriver_Destroy(void)
{
}

void updateHardware()
{
    *ledAddress = ledsImage;
}

// adding static to not change global namespace
static uint16_t convertLedNumberToBit(int ledNumber)
{
    return 1<<(ledNumber-1);
}

static void SetLedImageBit(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
}

static void ClearLedImageBit(int ledNumber)
{
    ledsImage &= ~convertLedNumberToBit(ledNumber);
}

static bool IsLedOutOfBounds(int ledNumber)
{
    return (ledNumber < FIRST_LED || ledNumber > LAST_LED);
}

void LedDriver_TurnAllOn()
{
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

void LedDriver_TurnAllOff()
{
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_TurnOn(int ledNumber)
{
    if(IsLedOutOfBounds(ledNumber))
        return;

    SetLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if(IsLedOutOfBounds(ledNumber))
        return;

    ClearLedImageBit(ledNumber);
    updateHardware();
}

bool LedDriver_IsOn(int ledNumber)
{
    if(IsLedOutOfBounds(ledNumber))
        return false;

    return (ledsImage & convertLedNumberToBit(ledNumber));
}

bool LedDriver_IsOff(int ledNumber)
{
    return !(LedDriver_IsOn(ledNumber));
}
