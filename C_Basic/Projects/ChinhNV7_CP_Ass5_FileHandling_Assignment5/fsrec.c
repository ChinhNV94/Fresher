#include "fsrec.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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

parse_status_t parseData(uint8_t pInput[], parse_data_struct_t *pOutput)
{
    uint8_t i;
    uint8_t count;
    uint8_t checksum;
    uint16_t status;
    
    /*checke error*/
    if(pInput[0] != 'S' || pInput == NULL){
        return e_parseStatus_error;
    }
    
    status = GetStatus(pInput[1]);
    /*check error*/
    if(status != e_parseStatus_error)
    {
        checksum = checkSum(pInput);
        /*check checksum*/
        if(checksum == 255)
        {
            count = getCount(pInput);
            getAddress(pInput, pOutput);
            getData(pInput, pOutput); 
        }
    }
    return status;
}

uint8_t GetStatus(uint8_t type)
{
    uint8_t typeHex;
    
    typeHex = convert1CharToHex(type);
    
    /*check record type to get status*/
    if(typeHex == 0)
    {
        return e_parseStatus_start;
    }
    else if(typeHex == 1 || typeHex == 2 || typeHex == 3 || typeHex == 4 || typeHex == 5 || typeHex == 6)
    {
        return e_parseStatus_inprogress;
    }
    else if(typeHex == 7 || typeHex == 8 || typeHex == 9)
    {
        return e_parseStatus_done;
    }
    else
    {
        return e_parseStatus_error;
    }
    
}

uint8_t getCount(uint8_t pInput[])
{
    uint8_t count;
    /*convert 2 character of byte count to hex*/
    count = convert2CharToHex(pInput[2], pInput[3]);
    return count;
}

uint8_t getAddLen(uint8_t type)
{
    uint8_t typeHex;
    uint8_t addlen;
    
    typeHex = convert1CharToHex(type);
    /*check record type to calculate length address*/
    if(typeHex == 0 || typeHex == 1 || typeHex == 5 || typeHex == 9)
    {
        addlen = 2;
    }
    else if(typeHex == 2 || typeHex == 6 || typeHex == 8)
    {
        addlen = 3;
    }
    else if(typeHex == 3 || typeHex == 7)
    {
        addlen = 4;
    }
    else
    {
        return OK;
    }
    return addlen;
}

void getAddress(uint8_t pInput[], parse_data_struct_t *pOutput)
{
    uint8_t addlen;
    uint8_t temp;
    uint8_t i;
    uint8_t j = 1;
    uint32_t address = 0;
    
    addlen = getAddLen(pInput[1]);
    /*check addlen != 0, calculate address*/
    if(addlen)
    {
        for(i = 4; i < (2*addlen + 4); i += 2)
        {
            /*convert 2 char to hex*/
            temp = convert2CharToHex(pInput[i], pInput[i + 1]);
            /*calculate address*/
            address += (temp << 8*(addlen - j));
            j++;
        }
        /*push address to struct out put*/
        pOutput->address = address;
    }
}


void getData(uint8_t pInput[], parse_data_struct_t *pOutput)
{
    uint8_t i;
    uint8_t j = 0;
    uint8_t count;
    uint8_t addlen;
    uint8_t datalen;
    uint8_t begin;
    uint8_t end;
    uint8_t temp;
    
    count = getCount(pInput);
    addlen = getAddLen(pInput[1]);
    if(addlen)
    {
        /*calculate data length*/
        datalen = count - addlen - SIZE_CHECKSUM;
        pOutput->dataLength = datalen;
        /*calculate index to begin data*/
        begin = 4 + 2*addlen;
        /*calculate index to end data*/
        end = 4 + 2*(addlen + datalen);
        for(i = begin; i < end; i += 2, j++)
        {
            /*convert 2 char data to hex*/
            temp = convert2CharToHex(pInput[i], pInput[i + 1]);
            /*push data to struct out put*/
            pOutput->data[j] = temp;
        }
    }
}

uint8_t checkSum(uint8_t pInput[])
{
    uint8_t checksum = 0;
    uint8_t len;
    uint8_t hn;
    uint8_t ln;
    uint8_t i;
    
    len = strlen(pInput);
    for(i = 2; i < len - 1; i = i + 2)
    {
        /*calculate checksum to check byte checksum*/
        checksum += convert2CharToHex(pInput[i], pInput[i + 1]);
    }
    return checksum;
}

uint8_t convert1CharToHex(uint8_t c)
{
    uint8_t hex;
    hex = c > '9' ? c - 55 : c - '0'; 
    return hex;
}

uint8_t convert2CharToHex(uint8_t hn, uint8_t ln)
{
    uint8_t hex;
    uint8_t h;
    uint8_t l;
    
    h = convert1CharToHex(hn);
    l = convert1CharToHex(ln);
    hex = (h << 4) | l ;
    return hex;
}
