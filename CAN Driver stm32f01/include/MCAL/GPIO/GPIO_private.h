/*
 * GPIO_private.h
 *
 *  Created on: Feb 15, 2022
 *      Author: Mohy
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GIOx_regs;


#define GPIO_PORTA_REG				((volatile GIOx_regs*)0x40010800)
#define GPIO_PORTB_REG				((volatile GIOx_regs*)0x40010C00)
#define GPIO_PORTC_REG				((volatile GIOx_regs*)0x40011000)


typedef struct
{
	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
}AFIOx_regs;

#define AFIO_REG				((volatile AFIOx_regs*)0x40010000)


#endif /* GPIO_PRIVATE_H_ */
