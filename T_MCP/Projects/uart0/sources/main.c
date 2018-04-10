#include "MKL46Z4.h"
#include "uart.h"
#include "fsrec.h"
#include "queue.h"
#include <stdio.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief <Task parser line data file srec>
 *
 * @param none
 *
 * @return none
 */
void TaskPaserFsrec();


/*******************************************************************************
 * Variables
 ******************************************************************************/
parse_data_struct_t g_Output;
uint8_t g_index = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

void main()
{
    /*init system clock*/
    SystemInit();
    /*config UART0 with baudrate = 115200*/
    UART0_Config(115200);
    /*intit queue*/
    queue_init();

    UART0_PrintString("Nguyen Van Chinh\n");

    while(1)
    {
        /*task parser line data of file srec*/
        TaskPaserFsrec();
    }
}

void UART0_IRQHandler()
{
    uint8_t c;
    uint8_t *putPtr = NULL;

    /*read character receive*/
    c = UART0_GetChar();
    /*point to first element of data queue*/
    queue_getUnuseElement((uint8_t **) &putPtr);
    /*put character to index of data queue*/
    *(putPtr + g_index) = c;
    /*next index*/
    g_index++;
    if (c == '\n')
    {
        /*move to first index*/
        g_index = 0;
        /*move to next element of queue*/
        queue_put();
    }
}

void TaskPaserFsrec()
{
    uint8_t *getPtr = NULL;
    parse_status_t status;

    if (!queue_isEmpty())
    {
        queue_getData((uint8_t **)&getPtr);
        queue_get();
        /*print srec line*/
//        UART0_PrintString(getPtr);
        /*parse data*/
        status = parseData(getPtr, &g_Output);
        if(status != e_parseStatus_error)
        {
            UART0_PrintString(">>");
        }
        else
        {
            UART0_PrintString("Error");
        }
    }
}