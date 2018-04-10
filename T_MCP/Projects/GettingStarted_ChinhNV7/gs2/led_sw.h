#ifndef _LED_SW_H_
#define _LED_SW_H_                  /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define IN_PUT      0
#define OUT_PUT     1

#define OFF         0
#define ON          1

#define GREEN_LED   5
#define RED_LED     29

#define SW1         3
#define SW3         12
    
#define IRQC_NONE_INTERRUPT         0
#define IRQC_DMA_RIS_EDGE           1
#define IRQC_DMA_FAL_EDGE           2
#define IRQC_DMA_EITHER_EDGE        3
#define IRQC_INTERRUPT_ZERO         8
#define IRQC_INTERRUPT_RIS_EDGE     9
#define IRQC_INTERRUPT_FAL_EDGE     10
#define IRQC_INTERRUPT_EITHER_EDGE  11
#define IRQC_INTERRUPT_ONE          12

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <configure for switch>
 *
 * @param sw: switch need configure:SW1, SW3
 * @param irqc: number set upt for field IRQC
 *
 * @return none
 */
void initSwitch(uint8_t sw, uint8_t irqc);

/*!
 * @brief <check status of switch>
 *
 * @param sw: switch need check status:SW1, SW3
 *
 * @return 1 if switch is pressed else return 0
 */
uint8_t isPressedSW(uint8_t sw);

/*!
 * @brief <clear interrupt flag for SW>
 *
 * @param sw: switch need clear interrupt flag:SW1, SW3
 *
 * @return none
 */
void clearInterruptFlag(uint8_t sw);

/*!
 * @brief <configure for led>
 *
 * @param led: led need configure:green led, red led
 *
 * @return none
 */
void initLed(uint8_t led);

/*!
 * @brief <set status for led>
 *
 * @param led: led need set status:green led, red led
 * @param status: status need set for led
 *
 * @return none
 */
void setLed(uint8_t led, uint8_t status);

/*!
 * @brief <reversed status for led>
 *
 * @param led: led need reversed status:green led, red led
 *
 * @return none
 */
void toggleLed(uint8_t led);

#ifdef __cplusplus
}
#endif

#endif