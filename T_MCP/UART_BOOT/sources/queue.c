#include "queue.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
static queue_struct_t s_queueList;


/*******************************************************************************
 * Code
 ******************************************************************************/

void queue_init(void)
{
    /*init values 0 for queue list*/
    s_queueList.getIndex = 0;
    s_queueList.putIndex = 0;
    s_queueList.size = 0;
}

bool queue_isFull(void)
{
    bool retVal = false;
    if (s_queueList.size == MAX_QUEUE_SIZE)
    {
        /*if queue size = MAX_QUEUE_SIZE -> queue is full -> retVal = true*/
        retVal = true;
    }
    return retVal;
}

bool queue_isEmpty(void)
{
    bool retVal = false;
    if (s_queueList.size == 0)
    {
        /*if queue size = 0 -> queue is empty -> retVal = true*/
        retVal = true;
    }
    return retVal;
    
}

void queue_getUnuseElement(uint8_t **outBuff)
{
    /*re-calculate queue index to put data*/
    uint8_t putIndex = s_queueList.putIndex % MAX_QUEUE_SIZE;

    if (!queue_isFull())
    {
        /*if queue is not full -> pointer write data point to first element[putIndex]*/
        *outBuff = (uint8_t *) &s_queueList.element[putIndex];
    }
}

void queue_put(void)
{
    /*increase put index and queue size*/
    s_queueList.putIndex++;
    s_queueList.size++;
}

void queue_getData(uint8_t **outBuff)
{
    /*re-calculate queue index to get data*/
    uint8_t getIndex = s_queueList.getIndex % MAX_QUEUE_SIZE;
    if (!queue_isEmpty())
    {
        /*if queue is not empty -> pointer read data point to first element[getIndex]*/
        *outBuff = (uint8_t *) &s_queueList.element[getIndex];
    }
}

void queue_get(void)
{
    /*increase get index*/
    s_queueList.getIndex++;
    /*decrease queue size*/
    s_queueList.size--;
}