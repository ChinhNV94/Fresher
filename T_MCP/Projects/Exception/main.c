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
/*array frequence of led*/
static uint16_t g_redLedFre[] = {1,2,3,5};
static uint16_t g_greenLedFre[] = {2,1,4,6,4,3};
/*counter for led*/
static uint16_t g_redLedCount = 0;
static uint16_t g_greenLedCount = 0;
/*index frequence of led in array*/
static uint16_t g_redIndex = 0;
static uint16_t g_greenIndex = 0;
/*sizeof array frequence*/
static uint8_t g_redLedFreSize = 0;
static uint8_t g_greenLedFreSize = 0;
 
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

    /*init switch 1 enable interrupt falling edge*/
    initSwitch(SW1, IRQC_INTERRUPT_FAL_EDGE);
    /*init switch 3 enable interrupt falling edge*/
    initSwitch(SW3, IRQC_INTERRUPT_FAL_EDGE);

    /*init systick enable interrupt with cycle 500ms*/
    initSysTick(500, CTRL_ENABLE_INTERRUPT);

    /*get size of array frequence of led*/
    g_redLedFreSize = sizeof(g_redLedFre)/sizeof(g_redLedFre[0]);
    g_greenLedFreSize = sizeof(g_greenLedFre)/sizeof(g_greenLedFre[0]);
    while(1);
}

/*function interrupt for systick*/
void SysTick_Handler()
{
    /*count stick for led*/
    g_greenLedCount++;
    g_redLedCount++;
    /*if count equal frequence of led -> reversed led and reset count*/
    if(g_greenLedCount == g_greenLedFre[g_greenIndex])
    {
        reversedLed(GREEN_LED);
        g_greenLedCount = 0;
    }
    if(g_redLedCount == g_redLedFre[g_redIndex])
    {
        reversedLed(RED_LED);
        g_redLedCount = 0;
    }
}

/*function interrupt for PORTC*/
void PORTC_PORTD_IRQHandler()
{
    /*interrupt on SW1*/
    if(PORTC->ISFR & (1 << SW1))
    {
        /*go to next index of frequence in array*/
        g_redIndex++;
        g_greenIndex++;
        /*if index >= size of array -> index = 0*/
        g_greenIndex = (g_greenIndex >= g_greenLedFreSize) ? 0 : g_greenIndex;
        g_redIndex = (g_redIndex >= g_redLedFreSize) ? 0 : g_redIndex;
        /*Clear interrupt flag*/
        PORTC->ISFR &= ~(1 << SW1);
    }
    if(PORTC->ISFR & (1 << SW3))
    {
        /*if index <= 0 -> index = last index*/
        g_greenIndex = (g_greenIndex <= 0) ? g_greenLedFreSize : g_greenIndex;
        g_redIndex = (g_redIndex <= 0) ? g_redLedFreSize : g_redIndex;
        /*go to previous index of frequence in array*/
        g_redIndex--;
        g_greenIndex--;
        /*Clear interrupt flag*/
        PORTC->ISFR &= ~(1 << SW3);
    }
    g_greenLedCount = 0;
    g_redLedCount = 0;
}