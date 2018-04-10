#include <stdio.h>
#include <stdint.h>
#include "regPCR.h"
#include "macros32bit.h"

int main()
{
    uint32_t PCR = 0x0FAC00AF;
    
    /*printf("Enter PCR(HEX): ");
    scanf("%x", &PCR);
    printf("\n");*/
    
    printf("PCR = 0x%x\n", PCR);
    printf("                                     IRQC\n");
    printf("PCR                 = ");
    /*print binary of PCR*/
    print_binary(PCR);
    
    printf("setIRQC(macro)      = ");
    /*set IRQC = 3*/
    PCR = macro_setIRQC(PCR, 3);
    /*print binary of PCR*/
    print_binary(PCR);
    
    printf("Reverse byte(macro) = ");
    /*reverse byte of PCR*/
    PCR = macro_reverseByte(PCR);
    /*print binary of PCR*/
    print_binary(PCR);
    
    printf("Reverse byte        = ");
    /*reverse byte of PCR*/
    reverseByte(&PCR);
    /*print binary of PCR*/
    print_binary(PCR);
    
    printf("Reverse bit(macro)  = ");
    /*reverse bit of PCR*/
    PCR = macro_reverseBit(PCR);
    /*print binary of PCR*/
    print_binary(PCR);
    
    printf("Reverse bit         = ");
    /*reverse bit of PCR*/
    reverseBit(&PCR);
    /*print binary of PCR*/
    print_binary(PCR);
    return 0;
}
