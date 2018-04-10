#include "MKL46Z4.h"
#include "led_sw.h"
#include "timer.h"
#include "uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief <Print time follow format: (00:00)-(seconds:minute)>
 *
 * @param none
 *
 * @return none
 */
void TaskPrintTime();


/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t s_seconds = 0;
static uint8_t s_minute = 0;
static uint8_t s_taskCount = 0;


/*******************************************************************************
 * Code
 ******************************************************************************/

void main()
{
    /*init system clock*/
    SystemInit();
    /*PIT chanel[0]: enable iterrupt with cycle 1s, not chain mode*/
    PIT_Config(0, SystemCoreClock / 2, PIT_TCTRL_NOT_CHAIN_MODE);
    /*PIT chanel[1]: enable interrupt in chain mode with cycle 1minute*/
    PIT_Config(1, 60, PIT_TCTRL_CHAIN_MODE);
    /*config UART0 with baudrate = 115200*/
    UART0_Config(115200);
    
    while(1)
    {
        TaskPrintTime();
    }
}

void PIT_IRQHandler()
{
    /*check for interrupt chanel[0]*/
    if(PIT->CHANNEL[0].TFLG)
    {
        /*clear interrupt flag*/
        PIT->CHANNEL[0].TFLG = 1;
        /*count seconds*/ 
        s_seconds++;
    }
    /*check for interrupt chanel[1]*/
    if(PIT->CHANNEL[1].TFLG)
    {
        /*clear interrupt flag*/
        PIT->CHANNEL[1].TFLG = 1;
        /*count minute*/
        s_minute++;
    }
}

void TaskPrintTime()
{
    if(s_seconds > s_taskCount)
    {
        /*re-calculate value seconds and minute*/
        s_seconds = (s_seconds % 60);
        s_minute = (s_minute % 60);
        /*if seconds < 10 print more 0 before*/
        if(s_seconds < 10)
        {
            UART0_PrintChar('0');
        }
        /*print value seconds*/
        UART0_PrintInt(s_seconds);
        UART0_PrintChar(':');
        /*if minute < 10 print more 0 before*/
        if(s_minute < 10)
        {
            UART0_PrintChar('0');
        }
        /*print value minute*/
        UART0_PrintInt(s_minute);
        UART0_PrintChar('\n');
        /*save current value seconds*/
        s_taskCount = s_seconds;
    }
}