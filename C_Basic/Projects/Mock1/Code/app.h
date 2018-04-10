#ifndef _APP_H_
#define _APP_H_

#include <stdint.h>
#include <stdbool.h>
#include "FAT.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct attribute
{
    bool RW;
    bool Hidden;
    bool System;
    bool Label;
    bool Directory;
    bool Archived;
}Attribute_t;

typedef struct time
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}Time_t;

typedef struct date
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
}Date_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Parse time create entry fat to: hour, minute, second>
 *
 * @param[in] time: struct time to follow parse
 * @param[in] timeFAT: time data of entry fat
 *
 * @return none
 */
void getTime(Time_t *time, uint16_t timeFAT);

/*!
 * @brief <Parse date create entry fat to: year, month, day>
 *
 * @param[in] data: struct date to follow parse
 * @param[in] dateFAT: date data of entry fat
 *
 * @return none
 */
void getDate(Date_t *date, uint16_t dateFAT);

/*!
 * @brief <Parse attribute of entry fat>
 *
 * @param[in] attribute: struct attribute to follow parse
 * @param[in] timeFAT: attribute data of entry fat
 *
 * @return none
 */
void getAttribute(Attribute_t *attribute, uint8_t file_attr);

/*!
 * @brief <Print time follow: hour, minute, second>
 *
 * @param[in] time: struct time to print
 *
 * @return none
 */
void printTime(Time_t time);

/*!
 * @brief <Print date follow: month, day, year>
 *
 * @param[in] date: struct date to print
 *
 * @return none
 */
void printDate(Date_t date);

/*!
 * @brief <Print attribute of entry>
 *
 * @param[in] attrib: struct attribute to print
 *
 * @return none
 */
void printAttribute(uint8_t attrib);

/*!
 * @brief <Print all information of entry>
 *
 * @param[in] entry: struct information of entry to print
 *
 * @return none
 */
void printInfoEntry(fileEntry_t entry);

/*!
 * @brief <Print information name, extension, size of entry>
 *
 * @param[in] entry: struct information of entry to print
 *
 * @return none
 */
void printEntry(fileEntry_t entry);

/*!
 * @brief <Move head of list to first element of list have information level equals level>
 *
 * @param[in] level: level of elements need find
 *
 * @return first element of list have information level equals level
 */

void currentNextStep(listEntry_t **current, uint8_t num);

/*!
 * @brief <Print information of boot sector>
 *
 * @param none
 *
 * @return none
 */
void printBootSector();

/*!
 * @brief <Print information name, extension, size of sub directory entries>
 *
 * @param entry: struct information of entry
 *
 * @return none
 */
void printSubDirectory(fileEntry_t entry);

/*!
 * @brief <Print information name, extension, size of root entries>
 *
 * @param none
 *
 * @return none
 */
void printRootDirectory();

/*!
 * @brief <Parser fat file system>
 *
 * @param[in] filename: name of file system
 *
 * @return none
 */
void fatParse(const uint8_t *filename);

#endif

