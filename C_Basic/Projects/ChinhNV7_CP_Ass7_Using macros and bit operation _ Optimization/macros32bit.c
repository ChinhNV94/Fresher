#include "macros32bit.h"
#include <stdint.h>
#include <stdio.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/*void reverseBit(uint32_t *x)
{       
    uint8_t i;
    uint32_t res = 0;
    uint32_t v = *x;
    for(i = 0; i < SUM_BIT; i++)
    {
        res <<= 1;
        res += (v & 1);
        v >>= 1;
    }
    *x = res;
}*/

void reverseBit(uint32_t *x)
{
    uint32_t v;
    v = *x;
    /*reverse odd and even bits*/
    v = ((v >> 1)              & MASK_EVEN_BIT      ) | ((v & MASK_EVEN_BIT)        << 1             );
    /*reverse consecutive pairs*/
    v = ((v >> 2)              & MASK_LOW_2BITOFBYTE) | ((v & MASK_LOW_2BITOFBYTE)  << 2             );
    /*reverse nibbles ...*/ 
    v = ((v >> SHIFT_HALFBYTE) & MASK_LOW_HALFBYTE  ) | ((v & MASK_LOW_HALFBYTE)    << SHIFT_HALFBYTE);
    /*reverse bytes*/
    v = ((v >> SHIFT_1BYTE)    & MASK_EVEN_BYTE     ) | ((v & MASK_EVEN_BYTE)       << SHIFT_1BYTE   );
    /*reverse 2-byte long pairs*/
    v = ( v >> SHIFT_2BYTE                          ) | ( v                         << SHIFT_2BYTE   );
    *x = v;
}
 
void reverseByte(uint32_t *x)
{
    uint32_t v;
    v = *x;
    v = ((v << SHIFT_3BYTE) & MASK_BYTE3) | ((v & MASK_BYTE3) >> SHIFT_3BYTE) |/*swap byte3 and byte0*/
        ((v >> SHIFT_1BYTE) & MASK_BYTE1) | ((v & MASK_BYTE1) << SHIFT_1BYTE); /*swap byte2 and byte1*/
    *x = v;
}

void print_binary(uint32_t number)
{
    uint8_t temp = 0;
    uint8_t i = sizeof(number)*8 - 1;
    do
    {
        if(temp > 0 && !(temp%4))
        {
            printf(" ");
        }
        /*(number >> i) & 1 = 1: print 1 else print 0*/
        (number >> i) & 1 ? printf("1") : printf("0");
        temp++;
    }while(i--);
    printf("\n");
}
