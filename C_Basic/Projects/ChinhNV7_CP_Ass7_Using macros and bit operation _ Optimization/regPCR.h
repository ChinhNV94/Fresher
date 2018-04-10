#ifndef _REGPCR_H_
#define _REGPCR_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MASK_ISF        0x01000000
#define MASK_IRQC       0x000F0000
#define MASK_LK         0x00008000
#define MASK_MUX        0x00000700
#define MASK_DSE        0x00000040
#define MASK_ODE        0x00000020
#define MASK_PFE        0x00000010
#define MASK_SRE        0x00000004
#define MASK_PE         0x00000002
#define MASK_PS         0x00000040

#define SHIFT_ISF       24
#define SHIFT_IRQC      16
#define SHIFT_LK        15
#define SHIFT_MUX       8
#define SHIFT_DSE       6
#define SHIFT_ODE       5
#define SHIFT_PFE       4
#define SHIFT_SRE       2
#define SHIFT_PE        1
#define SHIFT_PS        0

#define macro_setIRQC(PCR, irqc)      (PCR & (~MASK_IRQC)) | (irqc << SHIFT_IRQC);

/*******************************************************************************
 * API
 ******************************************************************************/
 
 #endif
