#ifndef _TIMER_H_
#define _TIMER_H_                       /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*SysTick CTRL*/
#define SYSTICK_CTRL_NONE_INTERRUPT         5
#define SYSTICK_CTRL_ENABLE_INTERRUPT       7
    
/*PIT TCTRL*/
#define PIT_TCTRL_CHAIN_MODE                7
#define PIT_TCTRL_NOT_CHAIN_MODE            3
    
/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief <configure for SysTick with cycle reload load(ms)>
 *
 * @param load: value (ms) reload
 * @param ctrl: ctrl = SYSTICK_CTRL_NONE_INTERRUPT: enable systick without interrupt
 *              ctrl = SYSTICK_CTRL_ENABLE_INTERRUPT: enable systick with interrupt
 *
 * @return none
 */
void SYSTICK_Init(uint32_t load, uint32_t ctrl);

/*!
 * @brief <configure for PIT with cycle reload ldval cycles>
 *
 * @param chanel: chanel need configure: 0 or 1
 * @param ldval: value (cycles) reload
 * @param interrupt: tctrl = PIT_TCTRL_CHAIN_MODE : enable PIT with chain mode
 *                   tctrl = PIT_TCTRL_NOT_CHAIN_MODE: enable PIT without chain mode
 *
 * @return none
 */
void PIT_Config(uint8_t chanel, uint32_t ldval, uint8_t tctrl);

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
void Sdelay_s(uint32_t x);

#ifdef __cplusplus
}
#endif

#endif