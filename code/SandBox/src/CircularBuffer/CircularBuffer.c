#include "CircularBuffer.h"

typedef struct CircularBufferStruct_t{
    int curr_pos;
    int buffer[BUFFER_SIZE];
}CircularBufferStruct;

void CircularBufferCreate(CircularBufferPtr_t buf)
{
    buf->curr_pos = 0;
}