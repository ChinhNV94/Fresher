#ifndef _FAT_H_
#define _FAT_H_

#include <stdio.h>
#include <stdint.h>
#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct boot_sector
{
    uint8_t FATtype[8];/*FAT12/16/32*/
    uint8_t SectorPerCluster;/*1*/
    uint8_t FATs;/*2*/
    uint16_t BytePerSector;/*512*/
    uint16_t ReservedSectors;/*1*/
    uint16_t RootDirEntries;/*224*/
    uint16_t SectorPerFAT;/*9*/
}bootSector_t;

typedef struct file_entry
{
    uint8_t FileName[8];
    uint8_t FileExtension[3];
    uint8_t Attributes;
    uint16_t Time;/*5/6/5 bits, for hour/minutes/doubleseconds*/
    uint16_t Date;/*7/4/5 bits, for year-since-1980/month/day*/
    uint16_t StartCluster;/*0 for an empty file*/
    uint32_t FileSize;
}fileEntry_t;

typedef struct list_entry
{
    fileEntry_t Entry;
    struct list_entry *next;
}listEntry_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Open file system>
 *
 * @param[in] filename: name of file system
 *
 * @return SUCCESS: if read successful
 *         NOT_CCESS: if read not successful
 */
uint8_t fatfs_open(const uint8_t *filename);

/*!
 * @brief <Read boot sector of file system>
 *
 * @param[in] BS: struct to save information of boot sector 
 *
 * @return SUCCESS: if read successful
 *         NOT_CCESS: if read not successful
 */
uint8_t fatfs_read_boot_sector(bootSector_t *BS);

/*!
 * @brief <Read information of entry>
 *
 * @param[in] entry: struct to save information
 * @param[in] buff: array data of entry
 *
 * @return none
 */
void fatfs_read_entry(fileEntry_t *entry, uint8_t *buff);

/*!
 * @brief <Get next cluster of entry>
 *
 * @param[in] startCluster: cluster of entry
 *
 * @return next cluster
 */
uint16_t fatfs_get_next_cluster(uint16_t startCluster);

/*!
 * @brief <Get index sector start cluster>
 *
 * @param[in] cluster: cluster of entry
 *
 * @return sector start cluster
 */
uint32_t fatfs_jmp_cluster(uint16_t cluster);

/*!
 * @brief <Read information of root directory file system>
 *
 * @param none
 *
 * @return number entry of root directory
 */
uint16_t fatfs_read_root_Dir();

/*!
 * @brief <Read information of sub directory file system>
 *
 * @param none
 *
 * @return number entry of sub directory
 */
uint16_t fatfs_read_sub_Dir(fileEntry_t entry);

/*!
 * @brief <Read data of file>
 *
 * @param[in] entry: struct information of file entry
 *
 * @return none
 */
void fatfs_read_file(fileEntry_t entry);

/*!
 * @brief <Add entry to end of list>
 *
 * @param[in] head: list entry
 * @param[in] entry: struct information of entry
 *
 * @return none
 */
void fatfs_push_list(listEntry_t **head, fileEntry_t entry);

/*!
 * @brief <Free list entry>
 *
 * @param none
 *
 * @return none
 */
void fatfs_free_list();

#endif

