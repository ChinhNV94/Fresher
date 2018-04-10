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
 * @brief <Task parser data of srec line>
 *
 * @param none
 *
 * @return none
 */
static void TaskPaserFsrec();

static void ClockConfig();

/*******************************************************************************
 * Variables
 ******************************************************************************/
static parse_data_struct_t s_Output;

static uint8_t s_char = NULL;

static uint8_t s_index = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

void main()
{
    /*init system*/
    SystemInit();
    /*configure clock*/
    ClockConfig();
    /*update system core clock*/
    SystemCoreClockUpdate();
    /*config UART0 with baudrate = 115200*/
    UART0_Config(38400);
    /*init queue*/
    queue_init();
    UART0_PrintString("NVC\n");
    while(1)
    {
        /*parser srec line*/
        TaskPaserFsrec();
    }
}

void UART0_IRQHandler()
{
    uint8_t *putPtr = NULL;
    /*check for interrupt recieve*/
    if(UART0->S1 & UART0_S1_RDRF_MASK)
    {
        /*get data from data register*/
        s_char = UART0_GetChar();
        /*point to fisrt element of queue[putIndex]*/
        queue_getUnuseElement((uint8_t **) &putPtr);
        /*write s_char to element[s_index]*/
        putPtr[s_index] = s_char;
        /*go to next index*/
        s_index++;
        if(s_char == '\n')
        {
            /*if s_char == '\n' -> go to fisrt next element*/
            s_index = 0;
            queue_put();
        }
    }
}

static void TaskPaserFsrec()
{
    uint8_t *getPtr = NULL;
    parse_status_t status;

    if(!queue_isEmpty())
    {
        /*if queue is not empty -> get data of element to parser*/
        queue_getData((uint8_t **)&getPtr);
        queue_get();
        /*parser data of srec line*/
        status = parseData(getPtr, &s_Output);
        /*if parser error -> print "Error" else print ">>"*/
        if(status == e_parseStatus_error)
        {
            UART0_PrintString("Error");
        }
        else
        {
            UART0_PrintString(">>");
        }
    }
}

static void ClockConfig()
{
    /*configure system core clock = bus clock = MCGOUTCLK = MCGFLLCLK = 48MHz*/
    /*Selects the clock source for MCGOUTCLK: FLL or PLL*/
    MCG->C1 &= MCG_C1_CLKS(0);
    /*Selects the slow internal reference clock source for the FLL: 32.768KHz*/
    MCG->C1 |= MCG_C1_IREFS(1);
    /*Select FLL factor: 1464-> clock = 32768*1464(48MHz)*/
    MCG->C4 &= ~MCG_C4_DRST_DRS_MASK;
    MCG->C4 |= MCG_C4_DRST_DRS(1);
    MCG->C4 |= MCG_C4_DMX32(1);
}