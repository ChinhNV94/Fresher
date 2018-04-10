#include "app.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

extern bootSector_t g_bootSector;
extern listEntry_t *g_list;

/*******************************************************************************
 * Code
 ******************************************************************************/


void getTime(Time_t *time, uint16_t timeFAT)
{
    /*parse time of fat entry*/
    time->hour = (timeFAT & (0x1f << 11)) >> 11;
    time->minute = (timeFAT & (0x3f << 5)) >> 5;
    time->second = timeFAT & 0x1f;
}

void getDate(Date_t *date, uint16_t dateFAT)
{
    /*parse date of fat entry*/
    date->year = 1980 + ((dateFAT & (0x7F << 9)) >> 9);
    date->month = (dateFAT & (0x0f << 5)) >> 5;
    date->day = dateFAT & 0x1f;
}

void getAttribute(Attribute_t *attribute, uint8_t file_attr)
{
    /*parse attribute of fat entry*/
    attribute->RW = ((file_attr & 0x01) == 0) ? false : true;
    attribute->Hidden = ((file_attr & 0x02) == 0) ? false : true;
    attribute->System = ((file_attr & 0x04) == 0) ? false : true;
    attribute->Label = ((file_attr & 0x08) == 0) ? false : true;
    attribute->Directory = ((file_attr & 0x10) == 0) ? false : true;
    attribute->Archived = ((file_attr & 0x20) == 0) ? false : true;
}

void printTime(Time_t time)
{
    printf("Time: %02d:%02d:%02d\n", time.hour, time.minute, time.second);
}

void printDate(Date_t date)
{
    printf("Date: %d/%d/%d\n", date.month, date.day, date.year);
}

void printAttribute(uint8_t attrib)
{
    (attrib & 0x01) == 0 ? :printf("RO ");
    (attrib & 0x02) == 0 ? :printf("Hidden ");
    (attrib & 0x04) == 0 ? :printf("File sytem ");
    (attrib & 0x08) == 0 ? :printf("Label ");
    (attrib & 0x10) == 0 ? :printf("Folder ");
    (attrib & 0x20) == 0 ? :printf("File ");
}

/*for debug*/
void printInfoEntry(fileEntry_t entry)
{
    Time_t time;
    Date_t date;
    uint32_t i;
    
    /*print information of entry*/
    printf("\nFile name: ");
    for(i = 0; i < 8; i++)
    {
        printf("%c", entry.FileName[i]);
    }
    printf("\nFile extension: ");
    for(i = 0; i < 3; i++)
    {
        printf("%c", entry.FileExtension[i]);
    }
    printf("\nAttribute: ");
    printAttribute(entry.Attributes);
    printf("\n");
    getTime(&time, entry.Time);
    printTime(time);
    getDate(&date, entry.Date);
    printDate(date);
    i = entry.StartCluster;
    printf("Start cluster: 0x%04x\n", i);
    printf("FAT[0x%08x] = 0x%03x\n", i, fatfs_get_next_cluster(i));
    printf("File size: %d\n", entry.FileSize);
}

void printEntry(fileEntry_t entry)
{
    uint32_t i;
    /*Print name*/
    for(i = 0; i < 8; i++)
    {
        printf("%c", entry.FileName[i]);
    }
    printf("\t");
    /*Print extension*/
    for(i = 0; i < 3; i++)
    {
        printf("%c", entry.FileExtension[i]);
    }
    printf("\t%d", entry.FileSize);
}

void currentNextStep(listEntry_t **current, uint8_t num)
{
    /*move pointer current to next num step*/
    while(num)
    {
        (*current) = (*current)->next;
        num--;
    }
}

void printBootSector()
{
    uint8_t i;
    /*print infromation of boot sector*/
    printf("Boot sector:\n");
    printf("Byte per sector: %d\n", g_bootSector.BytePerSector);
    printf("Sector per cluster: %d\n", g_bootSector.SectorPerCluster);
    printf("Reserved sector: %d\n", g_bootSector.ReservedSectors);
    printf("Fats: %d\n", g_bootSector.FATs);
    printf("Root directory entries: %d\n", g_bootSector.RootDirEntries);
    printf("Sector per FAT: %d\n", g_bootSector.SectorPerFAT);
    printf("FAT type: ");
    for(i = 0; i < 8; i++)
    {
        printf("%c", g_bootSector.FATtype[i]);
    }
    printf("\n");
}

void printSubDirectory(fileEntry_t entry)
{
    uint8_t i = 1;
    uint8_t select = 0;
    static uint16_t numEntry = 0;
    listEntry_t *current = NULL; 
    /*read data of sub directory*/
    numEntry = fatfs_read_sub_Dir(entry);
    printf("\n_____________________________________________________________________________");
    printf("\n\nName\t\tType\tSize");
    /*point to head of list*/
    current = g_list;
    /*move next 2 step*/
    current = current->next->next;
    /*if node current is not null print information of node*/
    while(current != NULL)
    {
        printf("\n%d:", i);
        printEntry(current->Entry);
        /*move to next node*/
        current = current->next;
        i++;
    }
    printf("\n%d: Exit ", numEntry -1);
    printf("\nEnter 0 to back!");
    /*if enter correct re-enter*/
    do
    {
        printf("\nEnter select(0->%d): ", numEntry -1);
    }
    while((scanf("%d", &select) == 0) || select < 0 || select > numEntry - 1);
    /*if exit program*/
    if(select == numEntry - 1)
    {
        fatfs_free_list();
        exit(0);
    }
    
    if(select)
    {
        /*point to head of list*/
        current = g_list;
        /*move to node need read*/
        currentNextStep(&current, select + 1);
        /*if attribute of node is file read file*/
        if(!(current->Entry.Attributes & 0x10))
        {
            /*print name of file*/
            printf("\n%s:\n", current->Entry.FileName);
            /*read and print data of file*/
            fatfs_read_file(current->Entry);
            /*point to head of list*/
            current = g_list;
        }
        /*print sub directory*/
        printSubDirectory(current->Entry);
    }
    else
    {
        /*if go back*/
        /*move to node parent*/
        current = g_list->next;
        if(current->Entry.StartCluster == 0x00)
        {
            /*if claster of parent is 0 -> parent is root directory*/
            /*print root directory*/
            printRootDirectory();
        }
        else
        {
            /*print sub directory parent*/
            printSubDirectory(current->Entry);
        }
    }
}

void printRootDirectory()
{
    uint8_t i = 1;
    static uint8_t rootEntry = 0;
    uint8_t select = 0;
    listEntry_t *current = NULL;
    
    /*read root directory*/
    rootEntry = fatfs_read_root_Dir();
    
    printf("\n_____________________________________________________________________________");
    printf("\n\nName\t\tType\tSize");
    /*point to head of list*/
    current = g_list;
    /*if node current is not null print information of node*/
    while(current != NULL)
    {
        printf("\n%d:", i);
        printEntry(current->Entry);
        /*move to next node*/
        current = current->next;
        i++;
    }
    printf("\n%d: Exit", rootEntry + 1);
    /*if enter correct re-enter*/
    do
    {
        printf("\nEnter select(1->%d): ", rootEntry + 1);
    }
    while((scanf("%d", &select) == 0) || select <= 0 || select > rootEntry + 1);
    
    /*if exit program*/
    if(select == rootEntry + 1)
    {
        fatfs_free_list();
        exit(0);
    }
    /*point to head of list*/
    current = g_list;
    /*move to node need read*/
    currentNextStep(&current, select - 1);
    
    if(current->Entry.Attributes & 0x10)
    {
        /*if entry is sub directory print sub directory*/
        printSubDirectory(current->Entry);
    }
    else
    {
        /*if entry is file*/
        /*print file name*/
        printf("\n%s:\n", current->Entry.FileName);
        /*read and print data of file*/
        fatfs_read_file(current->Entry);
        /*print root directory*/
        printRootDirectory();
    }
}

void fatParse(const uint8_t *filename)
{
    uint8_t status = 0;
    /*open file system*/
    status = fatfs_open(filename);
    /*if not open file sytem print notification and exit program*/
    if(!status)
    {
        printf("Open file system error!!!");
        return;
    }
    /*read boot sector*/
    fatfs_read_boot_sector(&g_bootSector);
    /*print boot sector*/
    printBootSector();
    /*print root directory*/
    printRootDirectory();
}

