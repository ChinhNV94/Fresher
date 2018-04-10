#include "timer.h"
#include "MKL46Z4.h"
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*SysTick**********************************************************************/
void SYSTICK_Config(uint32_t load, uint32_t ctrl)
{
    /*Disable SysTick while changing configurations*/
    SysTick->CTRL = 0;
    /*Clear current value*/
    SysTick->VAL = 0;
    /*Set value count down: timing equal 1ms*/
    SysTick->LOAD = load*(SystemCoreClock / 1000) - 1;
    /*Enable SysTick*/
    SysTick->CTRL = ctrl;
}
/*End SysTick******************************************************************/

/*PIT**************************************************************************/
void PIT_Config(uint8_t chanel, uint32_t ldval, uint8_t tctrl)
{
    /*PIT Clock Gate Control: enable*/
    SIM->SCGC6 = SIM_SCGC6_PIT(1);
    /*Enable clock for standard PIT timers*/
    PIT->MCR &= PIT_MCR_MDIS(0);
    /*Disable PIT while changing configurations*/
    PIT->CHANNEL[chanel].TCTRL = 0;
    /*Timer Start Value for count down to 0*/
    PIT->CHANNEL[chanel].LDVAL = ldval - 1;
    /*Set value for Timer Control Register*/
    PIT->CHANNEL[chanel].TCTRL = tctrl;
    /*Clear Timer Interrupt Flag*/
    PIT->CHANNEL[chanel].TFLG = 0;
    /*Enable Interrupt for PIT*/
    NVIC_EnableIRQ(PIT_IRQn);
}
/*End PIT**********************************************************************/

void delay_ms(uint32_t x)
{
    /*Calculate value for loop delay*/
    x = x*(SystemCoreClock / 4000) - 1;
    while(x)
    {
        /*count down value of loop*/
        x--;
    }
}

void delay_s(uint32_t x)
{
    while(x)
    {
        /*delay 1s*/
        delay_ms(1000);
        /*count down value of loop*/
        x--;
    }
}