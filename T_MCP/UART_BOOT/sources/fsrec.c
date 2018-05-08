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
    uint8_t checksum;
    parse_status_t status = e_parseStatus_error;

    /*check error*/
    if(pInput[0] == 'S' && pInput != NULL)
    {
        /*get status*/
        status = GetStatus(pInput);
        /*check error*/
        if(status != e_parseStatus_error)
        {
            /*parser address*/
            getAddress(pInput, pOutput);
            /*parser data and calculate checksum*/
            checksum = getData(pInput, pOutput); 
            if(checksum != 255)
            {
                status = e_parseStatus_error;
            }
        }
    }
    return status;
}

parse_status_t GetStatus(uint8_t pInput[])
{
    uint8_t typeHex;

    typeHex = convert1CharToHex(pInput[1]);
    
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
    uint8_t addlen = 0;

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


/*void getData(uint8_t pInput[], parse_data_struct_t *pOutput)*/
uint8_t getData(uint8_t pInput[], parse_data_struct_t *pOutput)
{
    uint8_t i;
    uint8_t j = 0;
    uint8_t count;
    uint8_t addlen;
    uint8_t datalen;
    uint8_t begin;
    uint8_t end;
    uint8_t temp;
    uint8_t checksum = 0;
    uint8_t len;

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
        end = begin + 2*datalen;
        
        /*len = strlen(pInput);*/
        len = 2*(getCount(pInput) +2);
        for(i = 2; i < len; i = i + 2)
        {
            /*convert 2 char data to hex*/
            temp = convert2CharToHex(pInput[i], pInput[i + 1]);
            /*calculate checksum to check byte checksum*/
            checksum += temp;
            if(i >= begin && i < end)
            {
                /*push data to struct out put*/
                pOutput->data[j] = temp;
                j++;
            }
        }
    }
    return checksum;
}

uint8_t checkSum(uint8_t pInput[])
{
    uint8_t checksum = 0;
    uint8_t len;
    uint8_t i;

    len = 2*(getCount(pInput) + 2);
    for(i = 2; i < len; i = i + 2)
    {
        /*calculate checksum to check byte checksum*/
        checksum += convert2CharToHex(pInput[i], pInput[i + 1]);
    }
    return checksum;
}

uint8_t convert1CharToHex(uint8_t c)
{
    uint8_t hex;
    /*hex = c > '9' ? c - 55 : c - 48;*/
    if((c >= 0) && (c <= 9))
    {
		hex = c - 48;
    }
    else if((c >= 'A') && (c <= 'F'))
    {
    	hex = c - 55;
    }
    else if((c >= 'a') && (c <= 'f'))
    {
    	hex = c - 87;
    }
    else
    {
    	hex = c;
    }
    return hex;
}

uint8_t convert2CharToHex(uint8_t _high, uint8_t _low)
{
    uint8_t hex;
    uint8_t high;
    uint8_t low;
    
    high = convert1CharToHex(_high);
    low = convert1CharToHex(_low);
    hex = (high << 4) | low;
    return hex;
}