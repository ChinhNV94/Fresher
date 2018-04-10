#include "led_sw.h"
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
void initSwitch(uint8_t sw, uint8_t irqc)
{
    /*Enable clock fo PORTC (SW1 & SW3)*/
    SIM->SCGC5 &= ~SIM_SCGC5_PORTC_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    /*Configure mux for (SW)*/
    PORTC->PCR[sw] &= ~PORT_PCR_MUX_MASK;
    PORTC->PCR[sw] |= PORT_PCR_MUX(1);
    PORTC->PCR[sw] |= PORT_PCR_PE(1);
    PORTC->PCR[sw] |= PORT_PCR_PS(1);
    /*configure IFS for SW*/
    PORTC->PCR[sw] |= PORT_PCR_ISF(1);
    /*Configure irqc for (SW)*/
    PORTC->PCR[sw] &= ~PORT_PCR_IRQC_MASK;
    PORTC->PCR[sw] |= PORT_PCR_IRQC(irqc);
    /*Configure PTCx (SW) as input*/
    GPIOC->PDDR &= ~(1 << sw);
}

uint8_t isPressedSW(uint8_t sw)
{
    /*if sw is pressed return 1 else return 0*/
    if((GPIOC->PDIR & (1 << sw)) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
    
void clearInterruptFlag(uint8_t sw)
{
    /*Clear interrupt flag*/
    PORTC->ISFR |= (1 << sw);
}

void initLed(uint8_t led)
{
    if(led == GREEN_LED)/*if led is GREEN_LED -> configure for GREEN_LED*/
    {
        /*Enable clock for PORTD (GREEN LED)*/
        SIM->SCGC5 &= ~SIM_SCGC5_PORTD_MASK;
        SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
        /*Configure pin mux*/
        PORTD->PCR[led] &= ~PORT_PCR_MUX_MASK;
        PORTD->PCR[led] |= PORT_PCR_MUX(1);
        /*Configure as oput*/
        GPIOD->PDDR |= (1 << led);
    }
    else if(led == RED_LED)/*if led is RED_LED -> configure for RED_LED*/
    {
        /*Enable clock for PORTE (RED LED)*/
        SIM->SCGC5 &= ~SIM_SCGC5_PORTE_MASK;
        SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;        
        /*Configure pin mux*/
        PORTE->PCR[led] &= ~PORT_PCR_MUX_MASK;
        PORTE->PCR[led] |= PORT_PCR_MUX(1);
        /*Configure as oput*/
        GPIOE->PDDR |= (1 << led);
    }
}

void setLed(uint8_t led, uint8_t status)
{
    if(led == GREEN_LED)/*if led is GREEN_LED -> configure for GREEN_LED*/
    {
        if(status == ON)
        {
            /*Clear PTEx as RED Led on*/
            GPIOD->PCOR |= (1 << led);
        }
        else if(status == OFF)
        {
            /*Set PTEx as RED Led off*/
            GPIOD->PSOR |= (1 << led);
        }
    }
    else if(led == RED_LED)/*if led is RED_LED -> configure for RED_LED*/
    {
        if(status == ON)
        {
            /*Clear PTEx as RED Led on*/
            GPIOE->PCOR |= (1 << led);
        }
        else if(status == OFF)
        {
            /*Set PTEx as RED Led off*/
            GPIOE->PSOR |= (1 << led);
        }
    }
}

void toggleLed(uint8_t led)
{
    if(led == GREEN_LED)/*if led is GREEN_LED -> configure for GREEN_LED*/
    {
        /*reversed status for GREEN_LED*/
        GPIOD->PTOR = (1 << 5);
    }
    else if(led == RED_LED)/*if led is RED_LED -> configure for RED_LED*/
    {
        /*reversed status for RED_LED*/
        GPIOE->PTOR = (1 << 29);
    }
}