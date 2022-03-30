//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------

extern "C"
{
#include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"
// #include "RuntimeErrorStub.h"

TEST_GROUP(LedDriver)
{
  uint16_t virtualLeds;
    void setup()
    {
      LedDriver_Create(&virtualLeds);
    }

    void teardown()
    {
       LedDriver_Destroy();
    }
};

TEST(LedDriver, LedsOffAfterCreate)
{
  uint16_t virtualLeds = 0;
  LedDriver_Create(&virtualLeds);
  // printf("\n leds_OFF = %x \n", ALL_LEDS_OFF);
  // printf("\n leds_ON = %x \n", ALL_LEDS_ON);
  UNSIGNED_LONGS_EQUAL(0xffff, virtualLeds);
}

IGNORE_TEST(LedDriver, TurnOnLedOne)
{
  LedDriver_TurnOn(LED_ON);
  UNSIGNED_LONGS_EQUAL(LED_ON, virtualLeds);
}

IGNORE_TEST(LedDriver, TurnOnAllLeds)
{
  LedDriver_TurnAllOn();
  UNSIGNED_LONGS_EQUAL(ALL_LEDS_ON, virtualLeds);
}

IGNORE_TEST(LedDriver, TurnOffAnyLed)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  LedDriver_TurnOff(8);
  UNSIGNED_LONGS_EQUAL(0x100, virtualLeds);
}

IGNORE_TEST(LedDriver, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  UNSIGNED_LONGS_EQUAL(384, virtualLeds);

}


IGNORE_TEST(LedDriver, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  UNSIGNED_LONGS_EQUAL(0x80, virtualLeds);
}

IGNORE_TEST(LedDriver, OutofBoundsTurnOnDoesNoHarm)
{
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  UNSIGNED_LONGS_EQUAL(0, virtualLeds);
}

IGNORE_TEST(LedDriver, OutofBoundsTurnOffDoesNoHarm)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  UNSIGNED_LONGS_EQUAL(0xFFFF, virtualLeds);
}

#if 0
IGNORE_TEST(LedDriver, OutofBoundsProducesRunTimeError)
{
  LedDriver_TurnOn(-12);
  STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
  UNSIGNED_LONGS_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}
#endif

IGNORE_TEST(LedDriver, IsOn)
{
  CHECK_FALSE(LedDriver_IsOn(11));
  LedDriver_TurnOn(11);
  CHECK_TRUE(LedDriver_IsOn(11));
}

IGNORE_TEST(LedDriver, IsOff)
{
  CHECK_TRUE(LedDriver_IsOff(11));
  LedDriver_TurnOn(11);
  CHECK_FALSE(LedDriver_IsOff(11));
}

IGNORE_TEST(LedDriver, OutofBoundsLedsAreAlwaysOff)
{
  CHECK_FALSE(LedDriver_IsOn(21));
  CHECK_TRUE(LedDriver_IsOff(-21));
  CHECK_FALSE(LedDriver_IsOn(-5));
  CHECK_TRUE(LedDriver_IsOff(-5));
}

IGNORE_TEST(LedDriver, TurnOffMultipleLeds)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(9);
  LedDriver_TurnOff(8);
  UNSIGNED_LONGS_EQUAL(0xffff & (~0x180), virtualLeds);
}

IGNORE_TEST(LedDriver, TurnAllOff)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
}
