#include "queue.h"
#include <stdint.h>
#include <stdbool.h>

queue_struct_t s_queueList;

void queue_init(void)
{
    s_queueList.getIndex = 0;
    s_queueList.putIndex = 0;
    s_queueList.size = 0;
}

bool queue_isFull(void)
{
    bool retVal = false;
    if (s_queueList.size == MAX_QUEUE_SIZE)
    {
        retVal = true;
    }
    return retVal;
}

bool queue_isEmpty(void)
{
    bool retVal = false;
    if (s_queueList.size == 0)
    {
        retVal = true;
    }
    return retVal;
}

void queue_put(void)
{
    s_queueList.putIndex++;
    s_queueList.size++;
}

void queue_getUnuseElement(uint8_t **outBuff)
{
    uint8_t putIndex = s_queueList.putIndex % MAX_QUEUE_SIZE;

    if (!queue_isFull())
    {
        *outBuff = (uint8_t *) &s_queueList.element[putIndex];
    }
}

void queue_get(void)
{
    s_queueList.getIndex++;
    s_queueList.size--;
}

void queue_getData(uint8_t **outBuff)
{
    uint8_t getIndex = s_queueList.getIndex % MAX_QUEUE_SIZE;
    if (!queue_isFull())
    {
        *outBuff = (uint8_t *) &s_queueList.element[getIndex];
    }
}