#include "MKL46Z4.h"
#include <stdio.h>

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

void UART0_Config(uint32_t baud)
{
    /*Enable clock for PORTA)*/
    SIM->SCGC5 &= ~SIM_SCGC5_PORTA_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    /*enable clock for pin TX, RX*/
    PORTA->PCR[1] &= ~PORT_PCR_MUX_MASK;
    PORTA->PCR[1] |= PORT_PCR_MUX(2);
    PORTA->PCR[2] &= ~PORT_PCR_MUX_MASK;
    PORTA->PCR[2] |= PORT_PCR_MUX(2);
    /*Configure PTA1 as input*/
    GPIOA->PDDR &= ~(1 << 1);
    /*Configure PTA2 as output*/
    GPIOA->PDDR |= (1 << 2);
    /*enable clock for uart0*/
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);
    /*UART0 Clock Source Select FLL clock*/
    SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    /*Disable UART0 while changing configuarations*/
    UART0->C2 = 0;
    /*Configure baud rate: baudrate = BaudClock/((OSR+1)*BR)*/
    /*default fixed OSR = 15; ->configure BR = (BaudClock/baudrate)/16*/
    UART0->BDH &= UART0_BDH_SBR(0);
    UART0->BDL = UART0_BDL_SBR((SystemCoreClock/baud)/16);
    /*Receiver Interrupt Enable for RDRF*/
    UART0->C2 |= UART0_C2_RIE(1);
    /*Enable TX*/
    UART0->C2 |= UART0_C2_TE(1);
    /*Enable RX*/
    UART0->C2 |= UART0_C2_RE(1);
    /*Enable intrrupt for UART0*/
    NVIC_EnableIRQ(UART0_IRQn);
}

uint8_t UART0_GetChar()
{
    /*wait for receive data buffer full*/
    while(!(UART0->S1 & UART0_S1_RDRF_MASK));
    /*read data from data register*/
    return (UART0->D);
}

void UART0_PrintChar(uint8_t ch)
{
    /*wait for transmit buffer empty*/
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));
    /*send a char*/
    UART0->D = ch;
}

void UART0_PrintString(uint8_t *str)
{
    while(*str)
    {
        /*print current char*/
        UART0_PrintChar(*str);
        /*move to next char*/
        str++;
    }
}

void UART0_PrintInt(uint32_t in)
{
    uint8_t val = 0;
    uint32_t temp = 0;
    uint32_t temp1 = 0;
    uint32_t count = 0;

    temp = in;
    /*reverse value follow decimal: abcd->dcba*/
    do
    {
        val = temp%10;
        temp = temp/10;
        temp1 = temp1*10 + val;
        count++;
    }while(temp);
    /*print value dcba->abcd*/
    for( ; count > 0; count--)
    {
        val = temp1%10 + 48;
        temp1 = temp1/10;
        UART0_PrintChar(val);
    }
}