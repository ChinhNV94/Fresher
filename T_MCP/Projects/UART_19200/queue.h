#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_QUEUE_SIZE      8

typedef struct
{
    uint8_t data[78];
} queue_data_struct_t;

typedef struct
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    queue_data_struct_t element[MAX_QUEUE_SIZE];
} queue_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Init values for queue list>
 *
 * @param none
 *
 * @return none
 */
void queue_init(void);

/*!
 * @brief <Check queue is full?>
 *
 * @param none
 *
 * @return none
 */
bool queue_isFull(void);

/*!
 * @brief <Check queue is empty?>
 *
 * @param none
 *
 * @return none
 */
bool queue_isEmpty(void);

/*!
 * @brief <Put data to queue>
 *
 * @param outBuff: point ter to write data to queue
 *
 * @return none
 */
void queue_getUnuseElement(uint8_t **outBuff);

/*!
 * @brief <increase index to put data and size of queue>
 *
 * @param none
 *
 * @return none
 */
void queue_put(void);

/*!
 * @brief <get data from queue>
 *
 * @param outBuff: point ter to read data from queue
 *
 * @return none
 */
void queue_getData(uint8_t **outBuff);

/*!
 * @brief <increase index to get data and decrease size of queue>
 *
 * @param none
 *
 * @return none
 */
void queue_get(void);

#endif