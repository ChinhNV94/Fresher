#ifndef _SYSTICK_H_
#define _SYSTICK_H_                /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CTRL_NONE_INTERRUPT      5
#define CTRL_ENABLE_INTERRUPT    7
    
/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief <configure for SysTick with cycle reload x(ms) using interrupt>
 *
 * @param load: value(ms) reload and interrupt
 * @param ctrl: ctrl = NONE_INTERRUPT: enable systick without interrupt
 *              ctrl = ENABLE_INTERRUPT: enable systick with interrupt
 *
 * @return none
 */
void initSysTick(uint16_t load, uint8_t ctrl);

/*!
 * @brief <delay (ms) use systick>
 *
 * @param x: number (ms) for delay
 *
 * @return none
 */
void delay_ms(uint32_t x);

/*!
 * @brief <delay (s) use systick>
 *
 * @param x: number (s) for delay
 *
 * @return none
 */
void delay_ms(uint32_t x);

#ifdef __cplusplus
}
#endif

#endif