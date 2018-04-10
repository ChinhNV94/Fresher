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
 * @brief <Configure for UART0>
 *
 * @param baud: baudrate need setup for UART0
 *
 * @return none
 */
void queue_init(void);

bool queue_isFull(void);

bool queue_isEmpty(void);

void queue_put(void);

void queue_getUnuseElement(uint8_t **outBuff);

void queue_get(void);

void queue_getData(uint8_t **outBuff);

#endif