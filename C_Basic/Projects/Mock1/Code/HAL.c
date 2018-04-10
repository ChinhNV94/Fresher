#include "HAL.h"
#include <stdio.h>
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SUCCESS             1
#define NOT_SUCCESS         0

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static FILE *s_pFile = NULL;
static uint16_t s_sectorSize = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/


uint8_t kmc_init_disk(const uint8_t *filename)
{
    /*open file system to read data*/
    s_pFile = fopen(filename, "rb");
    if(s_pFile == NULL)
    {
        /*if of not successful return NOT_SUCCESS*/
        return NOT_SUCCESS;
    }
    /*if of  successful return SUCCESS*/
    return SUCCESS;
}

void kmc_deinit_disk()
{
    /*close file system*/
    fclose(s_pFile);
}

void kmc_set_sector_size(uint16_t size)
{
    /*set number byte of sector for s_sectorSize*/
    s_sectorSize = size;
}

int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    uint16_t count = 0;

    /*move pointer file to logical index of sector start reading */
    if(!fseek(s_pFile, index*s_sectorSize, SEEK_SET))
    {
        /*read number byte of sector to buff*/
        count = fread(buff, 1, s_sectorSize, s_pFile);
    }
    return count;
}

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    int32_t count = 0;
    while(num)
    {
        /*read data of a sector tor buff*/
        count += kmc_read_sector(index, buff);
        /*move pointer buff to index for read next sector*/
        buff += s_sectorSize;
        /*count to next sector*/
        index ++;
        num--; 
    }
    return count;
}
