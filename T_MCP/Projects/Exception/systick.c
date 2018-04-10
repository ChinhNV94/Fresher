#include "systick.h"
#include "MKL46Z4.h"
#include "led_sw.h"
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

void initSysTick(uint32_t load, uint32_t ctrl)
{
    /*Disable SysTick*/
    SysTick->CTRL = 0;
    /*Clear current value*/
    SysTick->VAL = 0;
    /*Set value count down: timing equal 1ms*/
    SysTick->LOAD = load*(SystemCoreClock / 1000) - 1;
    /*Enable SysTick*/
    SysTick->CTRL = ctrl;
}

void SYST_delay_ms(uint32_t x)
{
    x = x*(SystemCoreClock / 1000) - 1; 
    while(x)
    {
        /*count down for loop*/
        x--;
    }
}

void SYST_delay_s(uint32_t x)
{
    while(x)
    {
        /*delay 1s*/
        SYST_delay_ms(1000);
        /*count down for loop*/
        x--;
    }
}