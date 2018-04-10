#include "MKL46Z4.h"
#include "led_sw.h"
#include "systick.h"

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

void main()
{
    /*init system clock*/
    SystemInit();
    /*init for systick timer*/
    initSysTick();
    /*init GREEN_LED*/
    initLed(GREEN_LED);
    /*init RED_LED*/
    initLed(RED_LED);
    /*init switch 1*/
    initSwitch(SW1);
    /*init switch 3*/
    initSwitch(SW3);
    
    /*init value for delay*/
    uint16_t i = 5;

    while(1)
    {
        /*reversed status of green led*/
        reversedLed(GREEN_LED);
        /*delay i*100ms*/
        SYST_delay_ms(i*100);
        /*reversed status of green led*/ 
        reversedLed(GREEN_LED);
        /*delay i*100ms*/
        SYST_delay_ms(i*100);
        /*reversed status of red led*/ 
        reversedLed(RED_LED);
        while(isPressSW(SW1))
        {
            i++;
            /*if i > 100, set i = 100*/
            i = (i > 100) ? 100 : i;
            /*reversed status of green led*/
            reversedLed(GREEN_LED);
            /*turn off red led*/
            setLed(RED_LED, OFF);
            /*delay 1s*/
            SYST_delay_s(1);
        }
        while(isPressSW(SW3))
        {
            i--;
            /*if i < 1. set i = 1*/
            i = (i < 1) ? 1 : i;
            /*turn off green led*/ 
            setLed(GREEN_LED, OFF);
            /*reversed status of red led*/ 
            reversedLed(RED_LED);
            /*delay 1s*/
            SYST_delay_s(1);
        }
    }
}