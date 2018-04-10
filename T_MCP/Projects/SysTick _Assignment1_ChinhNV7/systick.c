#include "systick.h"
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
void initSysTick()
{
    /*Disable SysTick*/
    SysTick->CTRL = 0;
    /*Clear current value*/
    SysTick->VAL = 0;
    /*Set value count down: timing equal 1ms*/
    SysTick->LOAD = (SystemCoreClock / 1000) - 1; 
    /*Enable SysTick*/    
    SysTick->CTRL = 5;
}

void SYST_delay_ms(uint16_t x)
{
    while(x)
    {
        /*Wait until SysTick reloaded*/
        while((SysTick->CTRL & (1 << 16)) == 0);
        /*count down for loop*/
        x--;
    }
}

void SYST_delay_s(uint16_t x)
{
    while(x)
    {
        /*delay 1s*/
        SYST_delay_ms(1000);
        /*count down for loop*/
        x--;
    }
}