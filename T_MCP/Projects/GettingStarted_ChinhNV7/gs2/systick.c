#include "systick.h"
#include "MKL46Z4.h"

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

void initSysTick(uint16_t load, uint8_t ctrl)
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

void delay_ms(uint32_t x)
{
    x = x*(SystemCoreClock / 4000) - 1;
    while(x)
    {
        /*count down for loop*/
        x--;
    }
}

void delay_s(uint32_t x)
{
    while(x)
    {
        /*delay 1s*/
        delay_ms(1000);
        /*count down for loop*/
        x--;
    }
}