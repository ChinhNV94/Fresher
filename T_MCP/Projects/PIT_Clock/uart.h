#ifndef _UART_H_
#define _UART_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

    
/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Configure for UART0>
 *
 * @param baud: baudrate need setup for UART0
 *
 * @return none
 */
void UART0_Config(uint32_t baud);

/*!
 * @brief <Print a character use UART0>
 *
 * @param ch: character need print
 *
 * @return none
 */
void UART0_PrintChar(uint8_t ch);

/*!
 * @brief <Print a string use UART0>
 *
 * @param str: pointer save string to print
 *
 * @return none
 */
void UART0_PrintString(uint8_t *str);

/*!
 * @brief <Print value int use UART0>
 *
 * @param in: value to print
 *
 * @return none
 */
void UART0_PrintInt(uint32_t in);

#endif