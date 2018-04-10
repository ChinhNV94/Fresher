#ifndef _FSREC_H_
#define _FSREC_H_

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_LINE_DATA_SIZE      64
#define OK                      0
#define NOT_OK                  1
#define SIZE_CHECKSUM           1


typedef enum {
    e_parseStatus_done = 0x00U,
    e_parseStatus_start = 0x01U,
    e_parseStatus_inprogress = 0x02U,
    e_parseStatus_error = 0xFFU,
}parse_status_t;

typedef struct{
    uint32_t address;
    uint8_t data[MAX_LINE_DATA_SIZE];
    uint8_t dataLength;
}parse_data_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief:  Parse data
 *
 * @param[in]: pInput[] data input need to parse.
 * @param[in]: pOutput struct to save information after parse.
 *
 * @return: e_parseStatus_done: parsing S7 or 8, 9 line
            e_parseStatus_start: parsing S0
            e_parseStatus_inprogress: parsing S1 or 2,3,4,5 or 6 line
            e_parseStatus_error: error
 */
parse_status_t parseData(uint8_t pInput[], parse_data_struct_t *pOutput);

/*!
 * @brief: Get status
 *
 * @param[in]: type: record type, character at index 1 of srec line
 *
 * @return: e_parseStatus_done: parsing S7 or 8, 9 line
            e_parseStatus_start: parsing S0
            e_parseStatus_inprogress: parsing S1 or 2,3,4,5 or 6 line
            e_parseStatus_error: error
 */
uint8_t GetStatus(uint8_t type);

/*!
 * @brief:  Get byte count of srec line
 *
 * @param[in]: pInput[] data input need to parse.
 *
 * @return: byte count of srec file
 */
uint8_t getCount(uint8_t pInput[]);

/*!
 * @brief:  Get length of address in srec line
 *
 * @param[in]: type: record type, character at index 1 of srec line
 *
 * @return: length of address
 */
uint8_t getAddLen(uint8_t type);

/*!
 * @brief:  Get address in srec line
 *
 * @param[in]: pInput[] data input need to parse.
 * @param[in]: pOutput struct to save information after parse.
 *
 * @return: none
 */
void getAddress(uint8_t pInput[], parse_data_struct_t *pOutput);

/*!
 * @brief:  Get data in srec line
 *
 * @param[in]: pInput[] data input need to parse.
 * @param[in]: pOutput struct to save information after parse.
 *
 * @return: checksum value
 */
uint8_t getData(uint8_t pInput[], parse_data_struct_t *pOutput);

/*!
 * @brief:  check checksum of srec line
 *
 * @param[in]: pInput[] data input need to parse.
 *
 * @return: numder to check checksum
 */
uint8_t checkSum(uint8_t pInput[]);

/*!
 * @brief:  convert 1 char to hex
 *
 * @param[in]: c: char to convert
 *
 * @return: hex 
 */
uint8_t convert1CharToHex(uint8_t c);

/*!
 * @brief:  convert 2 char to hex
 *
 * @param[in]: hn: 1/2 byte high
 * @param[in]: ln: 1/2 byte low
 *
 * @return: 1byte hex 
 */
uint8_t convert2CharToHex(uint8_t hn, uint8_t ln);

#endif /* _HEADER_FILENAME_H_ */

