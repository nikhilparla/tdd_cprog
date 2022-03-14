extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer)
{
    CircularBufferPtr_t buf =(CircularBufferPtr_t)malloc(sizeof(CircularBufferStruct_t));
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CircularBuffer, Create)
{
    printf("SizePointer = [%ld]", sizeof(CircularBufferStruct_t));
    CircularBufferCreate(buf);
}
