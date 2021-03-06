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


#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include <memory.h>
}
/**
    this is a test fixture which helps in reducing duplicate test code
*/
//START: testGroup
TEST_GROUP(sprintf)
{
    char output[100];               // file scope so accesible by all tests

    // change to handle any size
    char * output2;
    
    const char * expected;
    void setup()
    {
        memset(output, 0xaa, sizeof output);
        expected = "";
    }
    void teardown()
    {
        free(output2);
    }
    void expect(const char * s)
    {
        expected = s;
        int size_op2 = strlen(expected);
        output2 = (char *)malloc(size_op2+1);
    }
    void given(int charsWritten)
    {
        LONGS_EQUAL(strlen(expected), charsWritten);    // test the size 
        // STRCMP_EQUAL(expected, output);     // test the equality
        // BYTES_EQUAL(0xaa, output[strlen(expected) + 1]);    // test that the other memory is not corrupted
        // MEMCMP_EQUAL(expected, output, strlen(expected));
        STRCMP_EQUAL(expected, output2);     // test the equality
        MEMCMP_EQUAL(expected, output2, strlen(expected));
    }
};
//END: testGroup

#if 1 //START: RefactoredTests
TEST(sprintf, NoFormatOperations)
{
    // setup() is called automatically before anything
    expect("hey");
    // given(sprintf(output, "hey"));
    given(sprintf(output2, "hey"));
    // teardown() is called automatically at the end of test
}

TEST(sprintf, InsertString)
{
    expect("Hello World\n");
    // given(sprintf(output, "Hello %s\n", "World"));
    given(sprintf(output2, "Hello %s\n", "World"));
}

TEST(sprintf, LargeInput)
{
    expect("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    // given(sprintf(output, "Hello %s\n", "World"));
    given(sprintf(output2, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}
//END: RefactoredTests

#else //START: Duplication
//START: FormatSpace
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    memset(output, 0xaa, sizeof output);

    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
    BYTES_EQUAL(0xaa, output[2]);
}
//END: FormatSpace

TEST(sprintf, InsertString)
{
    char output[20];
    memset(output, 0xaa, sizeof output);

    LONGS_EQUAL(12, sprintf(output, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", output);
    BYTES_EQUAL(0xaa, output[13]);
}
//END: Duplication
#endif

#if 0 //START: NoFormatOperations1
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}
//END: NoFormatOperations1
#endif

#if 0 //START: NoFormatOperations2
TEST(sprintf, NoFormatOperations)
{
    char output[5] = "";
	
    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}
//END: NoFormatOperations2
#endif


#if 0 //START: oneString
TEST(sprintf, InsertString)
{
    char output[20] = "";

    LONGS_EQUAL(12, sprintf(output, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", output);
}
//END: oneString
#endif

#if 0 //START: failingTest
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    LONGS_EQUAL(4, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}
#endif //END: failingTest

