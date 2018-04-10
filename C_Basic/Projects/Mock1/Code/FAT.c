#include "FAT.h"
#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SUCCESS             1
#define NOT_SUCCESS         0

#define BOOT_SECTOR_SIZE    512
#define ENTRY_SIZE          32

#define readShort(buff, index)  ((buff[index] & 0xff) | ((buff[index + 1] & 0xff) << 8))
#define readLong(buff, index)   \
        ((buff[index]  & 0xff) | ((buff[index + 1] & 0xff) << 8) |   \
        ((buff[index + 2] & 0xff) << 16) | ((buff[index + 3] & 0xff) << 24))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
 
bootSector_t g_bootSector;
listEntry_t *g_list;

/*******************************************************************************
 * Code
 ******************************************************************************/


uint8_t fatfs_open(const uint8_t *filename)
{
    uint8_t status = 0;
    /*open file system*/
    status = kmc_init_disk(filename);
    return status;
}

uint8_t fatfs_read_boot_sector(bootSector_t *BS)
{
    uint8_t buff[BOOT_SECTOR_SIZE];
    uint8_t i;
    /*set sector size for HAL layer*/
    kmc_set_sector_size(BOOT_SECTOR_SIZE);
    /*if number byte read is 0 return NOT_SUCCESS*/
    if(!kmc_read_sector(0, buff))
    {
        return NOT_SUCCESS;
    }
    /*parse boot sector*/
    BS->BytePerSector = readShort(buff, 0x0b);
    BS->SectorPerCluster = buff[0x0d];
    BS->ReservedSectors = readShort(buff, 0x0e);
    BS->FATs = buff[0x10];
    BS->RootDirEntries = readShort(buff, 0x11);
    BS->SectorPerFAT = readShort(buff, 0x16);
    for(i = 0; i < 8; i++)
    {
        BS->FATtype[i] = buff[0x36 + i];
    }
    /*set sector size for HAL layer*/
    kmc_set_sector_size(BS->BytePerSector);
    return SUCCESS;
}

void fatfs_read_entry(fileEntry_t *entry, uint8_t *buff)
{
    uint8_t i;
    /*parse infromation of entry*/
    for(i = 0; i < 8; i++)
    {
        entry->FileName[i] = buff[i];
    }
    for(i = 0; i < 3; i++)
    {
        entry->FileExtension[i] = buff[0x08 + i];
    }
    entry->Attributes = buff[0x0b];
    entry->Time = readShort(buff, 0x16);
    entry->Date = readShort(buff, 0x18);
    entry->StartCluster = readShort(buff, 0x1a);
    entry->FileSize = readLong(buff, 0x1c);
}

uint16_t fatfs_get_next_cluster(uint16_t startCluster)
{ 
    uint8_t *buff;
    uint16_t fatEntry = 0;
    uint16_t endoffset = 0;
    uint32_t indexSec = 0;
    /*dynamic memmory to read sector*/
    buff = malloc(g_bootSector.BytePerSector);
    
    indexSec = g_bootSector.ReservedSectors + (startCluster*3/2)/g_bootSector.BytePerSector;
    endoffset = (startCluster*3/2)%g_bootSector.BytePerSector;
    /*if number byte read is not 0 parse fat entry*/
    if(kmc_read_sector(indexSec, buff))
    {
        if(startCluster%2)
        {
            /*fat entry odd*/
            fatEntry = (buff[endoffset] >> 4) | ((uint16_t)buff[endoffset + 1] << 4);
        }
        else
        {
            /*fat entry even*/
            fatEntry = (buff[endoffset] | ((uint16_t)buff[endoffset + 1] & 0x0f) << 8);
        }
    }
    /*free memmory of pointer buff*/
    free(buff);
    return fatEntry;
}

uint32_t fatfs_jmp_cluster(uint16_t cluster)
{
    uint16_t startCluster = 0;
    uint32_t address = 0;
    /*jump to cluster data*/
    startCluster += g_bootSector.ReservedSectors;
    startCluster += g_bootSector.FATs*g_bootSector.SectorPerFAT;
    startCluster += g_bootSector.RootDirEntries*ENTRY_SIZE/g_bootSector.BytePerSector;
    startCluster += cluster - 2;
    return startCluster;
}

uint16_t fatfs_read_root_Dir()
{
    uint8_t *buff;
    uint8_t *pbuff;
    uint16_t numEntry = 0;
    uint16_t startSector = 0;
    uint16_t numSector = 0;
    uint32_t numByte = 0;
    fileEntry_t entry;
    
    /*number  byte of root directory*/
    numByte = g_bootSector.RootDirEntries*ENTRY_SIZE;
    /*number  sector of root directory*/
    numSector = numByte/g_bootSector.BytePerSector;
    /*sector start root directory*/
    startSector = g_bootSector.ReservedSectors + g_bootSector.FATs*g_bootSector.SectorPerFAT;
    
    buff = malloc(numByte);
    pbuff = buff;
    
    /*check list is not NULL free list*/
    if(g_list != NULL)
    {
        fatfs_free_list();
    }
    /*if number byte read is not 0 parse root directory*/
    if(kmc_read_multi_sector(startSector, numSector, buff))
    {
        while(1)
        {
            if(buff[0] == 0x00)
            {
                break;
            }
            else if(buff[0x0b] != 0x0f)
            {
                /*read information of entry*/
                fatfs_read_entry(&entry,buff);
                /*add entry to end of list*/
                fatfs_push_list(&g_list, entry);
                numEntry++;
            }
            /*move pointer to next index of information next entry*/
            buff += ENTRY_SIZE;
        }
    }
    
    free(pbuff);
    return numEntry;
}

uint16_t fatfs_read_sub_Dir(fileEntry_t entry)
{
    uint8_t *buff;
    uint8_t *pbuff;
    uint16_t nextCluster = 0;
    uint32_t indexCluster = 0;
    uint32_t numEntry = 0;
    fileEntry_t f_entry;
    listEntry_t *current;
    
    buff = malloc(g_bootSector.BytePerSector);
    pbuff = buff;
    
    /*cluster of entry*/
    nextCluster = entry.StartCluster;
    
    /*check list is not NULL free list*/
    if(g_list != NULL)
    {
        fatfs_free_list();
    }
    
    do
    {
        /*index sector of cluster entry*/
        indexCluster = fatfs_jmp_cluster(nextCluster);
        /*if number byte read is not 0 parse entry*/
        if(kmc_read_sector(indexCluster, buff))
        {
            while(1)
            {
                if(buff[0] == 0x00)
                {
                    break;
                }
                else if(buff[0x0b] != 0x0f)
                {
                    /*parse data of entry*/
                    fatfs_read_entry(&f_entry,buff);
                    /*push entry to end of list*/
                    fatfs_push_list(&g_list, f_entry);
                    numEntry++;
                }
                /*move pointer to next index of information next entry*/
                buff += ENTRY_SIZE;
            }
            /*next cluster of entry*/
            nextCluster = fatfs_get_next_cluster(nextCluster);
        }
        
    }while(0x00 < nextCluster && nextCluster <= 0xff0);
    buff = pbuff;
    free(buff);
    return numEntry;
}

void fatfs_read_file(fileEntry_t entry)
{
    uint8_t *data = NULL;
    uint8_t *pdata = NULL;
    uint16_t nextCluster = 0;
    uint32_t indexCluster = 0;
    uint32_t numSector = 0;
    uint32_t numByte = 0;
    uint32_t i = 0;
    
    /*number sector of file*/
    numSector = entry.FileSize/g_bootSector.BytePerSector + 1;
    data = malloc(numSector*g_bootSector.BytePerSector);
    pdata = data;
    /*cluster of file*/
    nextCluster = entry.StartCluster;
    do
    {
        /*index sector of file*/
        indexCluster = fatfs_jmp_cluster(nextCluster);
        /*read data of file*/
        kmc_read_sector(indexCluster, data);
        /*next cluster of file*/
        nextCluster = fatfs_get_next_cluster(nextCluster);
        /*move pointer to next index of information next sector*/
        data += g_bootSector.BytePerSector;
    }while(0x00 < nextCluster && nextCluster <= 0xff0);
    data = pdata;
    /*printf("%s", data);*/
    for(i = 0; i < entry.FileSize; i++)
    {
        if(data[i] != 7)
        {
            printf("%c", data[i]);
        }
    }
    free(data);
}

void fatfs_push_list(listEntry_t **head, fileEntry_t entry)
{
    listEntry_t *current;
    listEntry_t *newEntry;
    /*dynamic memmory for new node of list*/
    newEntry =  malloc(sizeof(listEntry_t));
    /*read data to new node*/
    newEntry->Entry = entry;
    newEntry->next = NULL;
    
    current = *head;
    /*if list is null head = new node*/
    if(*head == NULL)
    {
        *head = newEntry;
        return;
    }
    /*move to end of list*/
    while(current->next != NULL)
    {
        current = current->next;
    }
    /*add new node to end of list*/
    current->next = newEntry;
    return;
}

void fatfs_free_list()
{
    listEntry_t *current;
    listEntry_t *prev;
    
    prev = NULL;
    /*move to head of list*/
    current = g_list;
    /*if current node is not null free node*/
    while(current != NULL)
    {
        prev = current;
        current = current->next;
        
        free(prev);
    }
    /*lit is null*/
    g_list = NULL;
}

