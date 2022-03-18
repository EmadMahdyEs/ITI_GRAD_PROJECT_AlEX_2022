/*
 * NVIC_private.h
 *
 *  Created on: Feb 19, 2022
 *      Author: Mohy
 */

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


#define NVIC_REG	((volatile NVIC_BITS*)0xE000E100)


typedef struct
{
	u32 ISER[32];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPR[32];
	u32 IABR[64];
	u8  IPR[81];
	u8 EMPTY5[2735];
	u32 STIR;

} NVIC_BITS;


#endif /* NVIC_PRIVATE_H_ */
