#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#define BUFFER_SIZE     10

typedef struct CircularBufferStruct_t * CircularBufferPtr_t;

void CircularBufferCreate(CircularBufferPtr_t buffer);

#endif