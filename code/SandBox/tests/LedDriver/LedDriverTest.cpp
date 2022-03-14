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
  uint16_t virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  UNSIGNED_LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
  LedDriver_TurnOn(1);
  UNSIGNED_LONGS_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOnAllLeds)
{
  LedDriver_TurnOnAllLeds(&virtualLeds);
  UNSIGNED_LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  LedDriver_TurnOff(8);
  UNSIGNED_LONGS_EQUAL(0x100, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  UNSIGNED_LONGS_EQUAL(384, virtualLeds);

}





























