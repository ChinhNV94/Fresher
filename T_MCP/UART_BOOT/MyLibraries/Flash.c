/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKL46Z4.h"
#include "Flash.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/
/* Get address*/
uint32_t Read_FlashAddress(uint32_t Addr)
{
    return *(__IO uint32_t*)Addr;
}

/* Program Address and Data (8bit pointer) into Flash Memory */
uint8_t Program_LongWord_8B(uint32_t Addr, uint8_t *Data)
{
    /* wait previous cmd finish */
    while (FTFA->FSTAT == 0x00);

    /* clear previous cmd error */
    if(FTFA->FSTAT != 0x80)
    {
        FTFA->FSTAT = 0x30;
    }
    /* Program 4 bytes in a program flash block */
    FTFA->FCCOB0 = CMD_PROGRAM_LONGWORD;

    /* fill Address */
    FTFA->FCCOB1 = (uint8_t)(Addr >>16);
    FTFA->FCCOB2 = (uint8_t)(Addr >>8);
    FTFA->FCCOB3 = (uint8_t)(Addr >>0);

    /* fill Data */
    FTFA->FCCOB4 = (uint8_t)(Data[3]);
    FTFA->FCCOB5 = (uint8_t)(Data[2]);
    FTFA->FCCOB6 = (uint8_t)(Data[1]);
    FTFA->FCCOB7 = (uint8_t)(Data[0]);

    /* Clear CCIF */
    FTFA->FSTAT = 0x80;
    /* wait cmd finish */
    while (FTFA->FSTAT == 0x00);
    return 1;
}

/* Program Address and Data (32bit) into Flash Memory */
uint8_t Program_LongWord(uint32_t Addr, uint32_t Data)
{
    /* wait previous cmd finish */
    while (FTFA->FSTAT == 0x00);

    /* clear previous cmd error */
    if(FTFA->FSTAT != 0x80)
    {
        FTFA->FSTAT = 0x30;
    }
    /* Program 4 bytes in a program flash block */
    FTFA->FCCOB0 = CMD_PROGRAM_LONGWORD;

    /* fill Address */
    FTFA->FCCOB1 = (uint8_t)(Addr >>16);
    FTFA->FCCOB2 = (uint8_t)(Addr >>8);
    FTFA->FCCOB3 = (uint8_t)(Addr >>0);

    /* fill Data */
    FTFA->FCCOB4 = (uint8_t)(Data >>24);
    FTFA->FCCOB5 = (uint8_t)(Data >>16);
    FTFA->FCCOB6 = (uint8_t)(Data >>8);
    FTFA->FCCOB7 = (uint8_t)(Data >>0);

    /* Clear CCIF */
    FTFA->FSTAT = 0x80;
    /* wait cmd finish */
    while (FTFA->FSTAT == 0x00);
    return 1;
}

/* Erase a flash Sector */
uint8_t Erase_Sector(uint32_t Addr)
{
    /* wait previous cmd finish */
    while (FTFA->FSTAT == 0x00);

    /* clear previous cmd error */
    if(FTFA->FSTAT != 0x80)
    {
        FTFA->FSTAT = 0x30;
    }
    /* Erase all bytes in a program flash sector */
    FTFA->FCCOB0 = CMD_ERASE_FLASH_SECTOR;

    /* fill Address */
    FTFA->FCCOB1 = (uint8_t)(Addr >>16);
    FTFA->FCCOB2 = (uint8_t)(Addr >>8);
    FTFA->FCCOB3 = (uint8_t)(Addr >>0);

    /* Clear CCIF */
    FTFA->FSTAT = 0x80;
    /* wait cmd finish */
    while (FTFA->FSTAT == 0x00);
    return 1;
}

/* Erase a flash Sector */
uint8_t Erase_MultiSector(uint32_t Addr, uint32_t numSec)
{
    uint32_t i = 0;
    uint32_t addr = Addr;
    while(i < numSec)
    {
        /*erase a sector*/
        Erase_Sector(addr);
        /*go to next sector*/
        addr += 1024;
        /*count sector*/
        i++;
    }
    return 1;
}