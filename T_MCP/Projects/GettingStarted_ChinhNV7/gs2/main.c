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
static uint32_t s_TickCount = 0;
static uint32_t s_TickCountSW1 = 0;
static uint32_t s_SW3Count = 0;
 
/*******************************************************************************
 * Code
 ******************************************************************************/

void main()
{
    /*init system clock*/
    SystemInit();
    /*init GREEN_LED*/
    initLed(GREEN_LED);
    /*init RED_LED*/
    initLed(RED_LED);
    /*init systick enable interrupt with cycle 500ms*/
    initSysTick(100, CTRL_ENABLE_INTERRUPT);
    /*init switch 1 enable interrupt falling edge*/
    initSwitch(SW1, IRQC_INTERRUPT_FAL_EDGE);
    /*init switch 3 enable interrupt falling edge*/
    initSwitch(SW3, IRQC_INTERRUPT_FAL_EDGE);
    /*enable interrupt for PORTC*/
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
    /*turn off led*/
    setLed(GREEN_LED, OFF);
    setLed(RED_LED, OFF);

    while(1)
    {
        /*turn on led 200ms*/
        setLed(RED_LED, ON);
        delay_ms(200);
        /*turn off led 1000ms*/
        setLed(RED_LED, OFF);
        delay_ms(1000);
    }
}

void SysTick_Handler()
{
    /*count tick*/
    s_TickCount++;
    s_TickCountSW1++;
    /*turn off green led after 30*100ms = 3s*/
    if(s_TickCountSW1 == 30)
    {
        setLed(GREEN_LED, OFF);
    }
    /*if press SW3 1st toggle with cycle 500ms ON/500 ms OFF*/
    if((s_SW3Count%2) && (s_TickCount%5 == 0))
    {
        toggleLed(GREEN_LED);
    }
}

/*function interrupt for PORTC*/
void PORTC_PORTD_IRQHandler()
{
    /*interrupt on SW1*/
    if(PORTC->ISFR & (1 << SW1))
    {
        /*turn on GREEN_LED*/
        setLed(GREEN_LED, ON);
        /*reset count of SW3*/
        s_SW3Count = 0;
        /*reset tick count SW1*/
        s_TickCountSW1 = 0;
        /*Clear interrupt flag*/
        clearInterruptFlag(SW1);
    }
    if(PORTC->ISFR & (1 << SW3))
    {
        /*count number fress*/
        s_SW3Count++;
        /*if press SW3 2nd -> turn off led*/
        if(s_SW3Count%2 == 0)
        {
            setLed(GREEN_LED, OFF);
        }
        /*Clear interrupt flag*/
        clearInterruptFlag(SW3);
    }
}