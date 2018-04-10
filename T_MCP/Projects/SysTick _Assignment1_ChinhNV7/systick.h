#ifndef _SYSTICK_H_
#define _SYSTICK_H_                       /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <configure for SysTick with cycle reload 1ms>
 *
 * @param none
 *
 * @return none
 */
void initSysTick();

/*!
 * @brief <delay (ms) use systick>
 *
 * @param x: number (ms) for delay
 *
 * @return none
 */
void SYST_delay_ms(uint16_t x);

/*!
 * @brief <delay (s) use systick>
 *
 * @param x: number (s) for delay
 *
 * @return none
 */
void SYST_delay_s(uint16_t x);

#ifdef __cplusplus
}
#endif

#endif