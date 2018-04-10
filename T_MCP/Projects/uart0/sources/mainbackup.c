#include "MKL46Z4.h"
#include "uart.h"
#include "fsrec.h"
#include "queue.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_QUEUE_SIZE      4

//typedef struct
//{
//    uint8_t data[78];
//} queue_data_struct_t;
//
//typedef struct
//{
//    uint8_t getIndex;
//    uint8_t putIndex;
//    uint8_t size;
//    queue_data_struct_t element[MAX_QUEUE_SIZE];
//} queue_struct_t;

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
void TaskPaserFsrec();


/*******************************************************************************
 * Variables
 ******************************************************************************/
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
    /*config UART0 with baudrate = 115200*/
    UART0_Config(115200);

    g_queueList.getIndex = 0;
    g_queueList.putIndex = 0;
    g_queueList.size = 0;

    UART0_PrintString("Nguyen Van Chinh\n");

    while(1)
    {
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
    uint8_t checksum;
    parse_status_t status;

    if(g_queueList.putIndex != g_queueList.getIndex)
    {
        UART0_PrintString("\nLine: ");
        /*print srec line*/
        UART0_PrintString(&g_queueList.element[g_queueList.getIndex]);
        /*parse data*/
        checksum = checkSum(&g_queueList.element[g_queueList.getIndex]);
        if(checksum == 255)
        {
            status = parseData(&g_queueList.element[g_queueList.getIndex], &g_Output);
            if(status != e_parseStatus_error)
            {
                /*print address*/
                UART0_PrintString("\nAddress:  ");
                UART0_PrintHex(g_Output.address);

                UART0_PrintString("\nData:         ");
                datalen = g_Output.dataLength;
                /*print data*/
                for(i = 0; i < datalen; i++)
                {
                    UART0_PrintByteToHex(g_Output.data[i]);
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
                UART0_PrintString("\n\n");
            }
            else
            {
                UART0_PrintString("\nConverted data error!\n");
            }
            g_queueList.getIndex++;
            g_queueList.getIndex = g_queueList.getIndex % 4;
        }
        else
        {
            UART0_PrintString("\nCheck sum error!\n");
        }
    }
}