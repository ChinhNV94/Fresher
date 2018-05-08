#include "MKL46Z4.h"
#include "uart.h"
#include "fsrec.h"
#include "queue.h"
#include "Flash.h"
#include "led_sw.h"
#include "timer.h"

#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_ADDR        0x8000
#define FLASH_EMPTY     0xFFFFFFFF

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief <Task parser data of srec line>
 *
 * @param none
 *
 * @return true: paser successful
 *         false: paser error
 */
static bool TaskPaserFsrec();

/*static void ClockConfig();*/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static parse_data_struct_t s_Output;

static uint8_t s_char = NULL;

static uint8_t s_index = 0;

static uint32_t s_appADD = APP_ADDR;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void boot_jump(uint32_t address) {
    typedef  void (*pFunction)(void);
    pFunction jumpToApplication = (pFunction) *(__IO uint32_t*)(address + 4);
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) address);
    jumpToApplication();
    /*__set_MSP(*((uint32_t*)address));
    ((void(*)())(*((uint32_t*)(address + 4))))();*/
}

void main()
{
    /*init system*/
    SystemInit();
    SW_Init(SW1, IRQC_NONE_INTERRUPT);
    /*waitting for SW1 pull up*/
    delay_ms(100);
    /*check button SW1*/
    if(!SW_IsPressed(SW1))
    {
        /*if SW1 pressed check value at fisrt application address*/
        if(Read_FlashAddress(APP_ADDR) != FLASH_EMPTY)
        {
            /*if value at fisrt application address is not FLASH_EMPTY jump to application*/
            boot_jump(APP_ADDR);
        }
    }
    /*Erase flash begin application address*/
    Erase_MultiSector(APP_ADDR, 220);
    /*init led*/
    LED_Init(GREEN_LED);
    LED_Init(RED_LED);
    /*configure clock*/
    /*ClockConfig();*/
    /*update system core clock*/
    /*SystemCoreClockUpdate();*/
    /*config UART0 with baudrate = 115200*/
    UART0_Config(9600);
    /*init queue*/
    queue_init();
    /*turn on GREEN_LED*/
    LED_Set(GREEN_LED, ON);
    /*turn of RED_LED*/
    LED_Set(RED_LED, OFF);
    /*for debug*/
    UART0_PrintString("Boot programming!\n");

    while(1)
    {
        /*parser srec line*/
        if(!TaskPaserFsrec())
        {
            break;
        }
    }
}

void UART0_IRQHandler()
{
    uint8_t *putPtr = NULL;
    /*check for interrupt recieve*/
    if(UART0->S1 & UART0_S1_RDRF_MASK)
    {
        /*get data from data register*/
        s_char = UART0_GetChar();
        /*point to fisrt element of queue[putIndex]*/
        queue_getUnuseElement((uint8_t **) &putPtr);
        /*write s_char to element[s_index]*/
        putPtr[s_index] = s_char;
        /*go to next index*/
        s_index++;
        if(s_char == '\n')
        {
            /*if s_char == '\n' -> go to fisrt next element*/
            s_index = 0;
            queue_put();
        }
    }
}

static bool TaskPaserFsrec()
{
    uint8_t *getPtr = NULL;
    uint8_t datalen = 0;
    uint8_t index = 0;
    parse_status_t status;
    bool retVal = true;

    if(!queue_isEmpty())
    {
        /*if queue is not empty -> get data of element to parser*/
        queue_getData((uint8_t **)&getPtr);
        queue_get();
        /*parser data of srec line*/
        status = parseData(getPtr, &s_Output);
        /*check status*/
        if(status == e_parseStatus_start)
        {
            /*if status is start: print "Start"*/
            UART0_PrintString("Start\n");
        }
        else if(status == e_parseStatus_inprogress)
        {
            /*if status is inprogress: print ">>" and write data to flash*/
            UART0_PrintString(">>");
            /*get data length*/
            datalen = s_Output.dataLength;
            /*write data to flash*/
            while(datalen)
            {
                /*disable interrupt*/
                NVIC_DisableIRQ(UART0_IRQn);
                /*write 4byte data to flash*/
                Program_LongWord_8B(s_appADD, &s_Output.data[index]);
                s_appADD += 4;
                index += 4;
                datalen -= 4;
                /*enable interrupt*/
                NVIC_EnableIRQ(UART0_IRQn);
            }
        }
        else if(status == e_parseStatus_done)
        {
            /*if status is done print "Done" enable RED_LED*/
            UART0_PrintString("\nDone\n");
            LED_Set(RED_LED, ON);
        }
        else if(status == e_parseStatus_error)
        {
            /*if status is error: print "Error" and reVal = false*/
            UART0_PrintString("Error");
            retVal = false;
        }
    }
    return retVal;
}

//static void ClockConfig()
//{
//    /*configure system core clock = bus clock = MCGOUTCLK = MCGFLLCLK = 48MHz*/
//    /*Selects the clock source for MCGOUTCLK: FLL or PLL*/
//    MCG->C1 &= MCG_C1_CLKS(0);
//    /*Selects the slow internal reference clock source for the FLL: 32.768KHz*/
//    MCG->C1 |= MCG_C1_IREFS(1);
//    /*Select FLL factor: 1464-> clock = 32768*1464(48MHz)*/
//    MCG->C4 &= ~MCG_C4_DRST_DRS_MASK;
//    MCG->C4 |= MCG_C4_DRST_DRS(1);
//    MCG->C4 |= MCG_C4_DMX32(1);
//}