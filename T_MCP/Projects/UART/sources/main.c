#include "MKL46Z4.h"
#include "timer.h"
#include "uart.h"
#include "fsrec.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_QUEUE_SIZE      4

typedef struct
{
    uint8_t data[156];
} queue_data_struct_t;

typedef struct
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    queue_data_struct_t element[MAX_QUEUE_SIZE];
} queue_struct_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief <Print time follow format: (00:00)-(seconds:minute)>
 *
 * @param none
 *
 * @return none
 */
//void TaskPrintTime();

void TaskPaserFsrec();


/*******************************************************************************
 * Variables
 ******************************************************************************/
//static uint8_t s_seconds = 0;
//static uint8_t s_minute = 0;
//static uint8_t s_taskCount = 0;
parse_data_struct_t g_Output;
queue_struct_t g_queueList;
static uint8_t s_dataIndex = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

void main()
{
    /*init system clock*/
    SystemInit();
    /*PIT chanel[0]: enable iterrupt with cycle 1s, not chain mode*/
//    PIT_Config(0, SystemCoreClock / 2, PIT_TCTRL_NOT_CHAIN_MODE);
    /*PIT chanel[1]: enable interrupt in chain mode with cycle 1minute*/
//    PIT_Config(1, 60, PIT_TCTRL_CHAIN_MODE);
    /*config UART0 with baudrate = 115200*/
    UART0_Config(115200);
    
    g_queueList.getIndex = 0;
    g_queueList.putIndex = 0;
    g_queueList.size = 0;
    
    while(1)
    {
//        TaskPrintTime();
        TaskPaserFsrec();
    }
}

void UART0_IRQHandler()
{
    uint8_t c;
    if(UART0->S1 & UART0_S1_RDRF_MASK)
    {
        c = UART0_GetChar();
        if(c != '\n')
        {
            g_queueList.element[g_queueList.putIndex].data[s_dataIndex] = c;
//            UART0_PrintChar(g_queueList.element[g_queueList.putIndex].data[s_dataIndex]);
            s_dataIndex++;
        }
        else
        {
            s_dataIndex = 0;
            g_queueList.putIndex++;
            g_queueList.putIndex = g_queueList.putIndex % 4;
        }
    }
}

void TaskPaserFsrec()
{
    uint8_t i;
    uint8_t datalen;
    uint16_t status;
    
    if(g_queueList.putIndex != g_queueList.getIndex)
    {
        UART0_PrintString("\nLine: ");
        /*print srec line*/
        UART0_PrintString(&g_queueList.element[g_queueList.getIndex].data[0]);
        /*parse data*/
        i = checkSum(&g_queueList.element[g_queueList.getIndex].data[0]);
        status = parseData(&g_queueList.element[g_queueList.getIndex].data[0], &g_Output);
        if(status != e_parseStatus_error)
        {
            /*print address*/
            UART0_PrintString("\nAddress: ");
            UART0_PrintInt(g_Output.address);
            UART0_PrintString("\nData:        ");
            datalen = g_Output.dataLength;
            /*print data*/
            for(i = 0; i < datalen; i++)
            {
                UART0_PrintChar(g_Output.data[i]);
            }
            UART0_PrintString("\nData length: ");
            UART0_PrintInt(datalen);
            
            /*print status*/
            switch(status)
            {
                case e_parseStatus_start:
                    UART0_PrintString("\nStatus: START");
                    break;
                case e_parseStatus_inprogress:
                    UART0_PrintString("\nStatus: INPROGRESS");
                    break;
                case e_parseStatus_done:
                    UART0_PrintString("\nStatus: DONE");
                    break;
                default:
                    break;
            }
            UART0_PrintString("\n\n\n");
        }
        else
        {
            UART0_PrintString("\nConverted data error!\n");
        }
        g_queueList.getIndex++;
        g_queueList.getIndex = g_queueList.getIndex % 4;
    }
}

//void PIT_IRQHandler()
//{
//    /*check for interrupt chanel[0]*/
//    if(PIT->CHANNEL[0].TFLG)
//    {
//        /*clear interrupt flag*/
//        PIT->CHANNEL[0].TFLG = 1;
//        /*count seconds*/ 
//        s_seconds++;
//    }
//    /*check for interrupt chanel[1]*/
//    if(PIT->CHANNEL[1].TFLG)
//    {
//        /*clear interrupt flag*/
//        PIT->CHANNEL[1].TFLG = 1;
//        /*count minute*/
//        s_minute++;
//    }
//}

//void TaskPrintTime()
//{
//    if(s_seconds > s_taskCount)
//    {
//        /*re-calculate value seconds and minute*/
//        s_seconds = (s_seconds % 60);
//        s_minute = (s_minute % 60);
//        /*if seconds < 10 print more 0 before*/
//        if(s_seconds < 10)
//        {
//            UART0_PrintChar('0');
//        }
//        /*print value seconds*/
//        UART0_PrintInt(s_seconds);
//        UART0_PrintChar(':');
//        /*if minute < 10 print more 0 before*/
//        if(s_minute < 10)
//        {
//            UART0_PrintChar('0');
//        }
//        /*print value minute*/
//        UART0_PrintInt(s_minute);
//        UART0_PrintChar('\n');
//        /*save current value seconds*/
//        s_taskCount = s_seconds;
//    }
//}