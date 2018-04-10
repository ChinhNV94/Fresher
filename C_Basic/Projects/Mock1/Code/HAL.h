#ifndef _HAL_H_
#define _HAL_H_

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
 /*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Open file system>
 *
 * @param[in] filename: name of file system
 *
 * @return SUCCESS: open successful
 *         NOT_SUCCESS: open not successful
 */
uint8_t kmc_init_disk(const uint8_t *filename);

/*!
 * @brief <Close file system>
 *
 * @param none
 *
 * @return none
 */
void kmc_deinit_disk();

/*!
 * @brief <Set number byte of sector>
 *
 * @param[in] size: number byte of sector from up layer
 *
 * @return none
 */
void kmc_set_sector_size(uint16_t size);

/*!
 * @brief <Read data of a sector>
 *
 * @param[in] index: index sector start reading
 * @param[in] buff: Arrays to storage data
 *
 * @return number byte read
 */
int32_t kmc_read_sector(uint32_t index, uint8_t *buff);

/*!
 * @brief <Read data of a sector>
 *
 * @param[in] index: index sector start reading
 * @param[in] num: number sector need read
 * @param[in] buff: Arrays to storage data
 *
 * @return number byte read
 */
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);

#endif

