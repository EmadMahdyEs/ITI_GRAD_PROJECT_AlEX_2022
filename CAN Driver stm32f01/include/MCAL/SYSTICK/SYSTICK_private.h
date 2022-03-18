/*
 * SYSTICK_private.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_

#define SYSTICK_REGS		((volatile SYSTICK_STRUCT*)0xE000E010)


typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;


}SYSTICK_STRUCT;


#define SYSTICK_INTERRUPT_ENABLE	1
#define SYSTICK_INTERRUPT_DISABLE	0

#define SYSTICK_TIMER_ENABLE		1
#define SYSTICK_TIMER_DISABLE		0

#define SYSTICK_CLK_AHB				1
#define SYSTICK_CLK_AHB_DIV_8		0

#define SYSTICK_IMMEDIATE_LOAD		1
#define SYSTICK_NOT_IMMEDIATE_LOAD	0

/****************control register bits****************/
#define SYSTICK_CTRL_REG_EN_BIT				0
#define SYSTICK_CTRL_REG_INT_BIT			1
#define SYSTICK_CTRL_REG_CLK_BIT			2
#define SYSTICK_CTRL_REG__COUNT_FLAG_BIT	16
/******************************************************/

/*systick maximum Ticks*/
#define SYSTICK_MAX_TICKS		(16777216UL)


#endif /* SYSTICK_PRIVATE_H_ */
