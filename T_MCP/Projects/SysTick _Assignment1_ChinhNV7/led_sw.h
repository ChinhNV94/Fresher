#ifndef _LED_SW_H_
#define _LED_SW_H_                       /**< Symbol preventing repeated inclusion */

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

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <configure for switch>
 *
 * @param sw: switch need configure:SW1, SW3
 *
 * @return none
 */
void initSwitch(uint8_t sw);

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
 * @param type: status need set for led
 *
 * @return none
 */
void setLed(uint8_t led, uint8_t type);

/*!
 * @brief <reversed status for led>
 *
 * @param led: led need reversed status:green led, red led
 *
 * @return none
 */
void reversedLed(uint8_t led);

/*!
 * @brief <check status of switch>
 *
 * @param sw: switch need check status:SW1, SW3
 *
 * @return 1 if switch is pressed else return 0
 */
uint8_t isPressSW(uint8_t sw);

#ifdef __cplusplus
}
#endif

#endif