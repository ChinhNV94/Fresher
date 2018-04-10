#include "MKL46Z4.h"
#include "led_sw.h"

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
void delay_ms(uint32_t x)
{
    /*calculate value for loop while to delay*/
    x = x*(SystemCoreClock/4000) - 1;
    /*Count down from x to 0*/
    while(x)
    {
        x--;
    }
}

void main()
{
    /*init system clock*/
    SystemInit();
    /*init GREEN_LED*/
    initLed(GREEN_LED);
    /*init RED_LED*/
    initLed(RED_LED);
    /*init switch 1*/
    initSwitch(SW1, IRQC_NONE_INTERRUPT);
    /*init switch 3*/
    initSwitch(SW3, IRQC_NONE_INTERRUPT);
    /*Turn off led*/
    setLed(GREEN_LED, OFF);
    setLed(RED_LED, OFF);

    while(1)
    {
        /*Check switch SW1 pressed*/
        if(isPressedSW(SW1))
        {
            /*Wait until SW1 releaed*/
            while(isPressedSW(SW1));
            {
                delay_ms(1);
            }
            /*toggle GREEN_LED*/
            toggleLed(GREEN_LED);
        }
        /*Check switch SW3 pressed*/
        if(isPressedSW(SW3))
        {
            /*Wait until SW3 releaed*/
            while(isPressedSW(SW3));
            {
                delay_ms(1);
            }
            /*Turn on RED_LED*/
            setLed(RED_LED, ON);
            /*Delay 2s*/
            delay_ms(2000);
            /*Turn off RED_LED*/
            setLed(RED_LED, OFF);
        }
    }
}