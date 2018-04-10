#ifndef _MACROS32BIT_H_
#define _MACROS32BIT_H_

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SUM_BIT         32
#define MASK_32BIT      0xFFFFFFFF

#define MASK_BYTE0      0x000000FF
#define MASK_BYTE1      0x0000FF00
#define MASK_BYTE2      0x00FF0000
#define MASK_BYTE3      0xFF000000


#define MASK_EVEN_BIT       0x55555555
#define MASK_LOW_2BITOFBYTE 0x33333333
#define MASK_EVEN_BYTE      0x00FF00FF
#define MASK_LOW_HALFBYTE   0x0F0F0F0F

#define SHIFT_HALFBYTE      4
#define SHIFT_1BYTE         8
#define SHIFT_2BYTE         16
#define SHIFT_3BYTE         24

#define macro_reverseBit(v)       \
    /*reverse odd and even bits*/                                                                      \
    v = ((v >> 1)              & MASK_EVEN_BIT      ) | ((v & MASK_EVEN_BIT)        << 1             );\
    /*reverse consecutive pairs*/                                                                      \
    v = ((v >> 2)              & MASK_LOW_2BITOFBYTE) | ((v & MASK_LOW_2BITOFBYTE)  << 2             );\
    /*reverse nibbles ...*/                                                                            \
    v = ((v >> SHIFT_HALFBYTE) & MASK_LOW_HALFBYTE  ) | ((v & MASK_LOW_HALFBYTE)    << SHIFT_HALFBYTE);\
    /*reverse bytes*/                                                                                  \
    v = ((v >> SHIFT_1BYTE)    & MASK_EVEN_BYTE     ) | ((v & MASK_EVEN_BYTE)       << SHIFT_1BYTE   );\
    /*reverse 2-byte long pairs*/                                                                      \
    v = ( v >> SHIFT_2BYTE                          ) | ( v                         << SHIFT_2BYTE   );   


#define macro_reverseByte(v)       \
    ((v << SHIFT_3BYTE) & MASK_BYTE3) | ((v & MASK_BYTE3) >> SHIFT_3BYTE) |/*swap byte3 and byte0*/    \
    ((v >> SHIFT_1BYTE) & MASK_BYTE1) | ((v & MASK_BYTE1) << SHIFT_1BYTE);/*swap byte2 and byte1*/     




/*******************************************************************************
 * API
 ******************************************************************************/
 
 /*!
* @brief: Reverse bit of number 32 bit
*
*@param[in] x: number need to reverse bit
*
* @return: none
*/
 /*void reverseBit(uint32_t *x);*/
 
 /*!
* @brief: Reverse bit of number 32 bit
*
*@param[in] x: number need to reverse bit
*
* @return: none
*/
 void reverseBit(uint32_t *x);
 
 /*!
* @brief: Reverse byte of number 32 bit
*
*@param[in] x: number need to reverse byte
*
* @return: none
*/
 void reverseByte(uint32_t *x);
 
 /*!
* @brief: print binary of number 32 bit
*
*@param[in] number: number need to print binary
*
* @return: none
*/
 void print_binary(uint32_t number);
 
 #endif
