/*
 * SCB_private.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */

#ifndef SCB_PRIVATE_H_
#define SCB_PRIVATE_H_

#define SCB_REGS		( (volatile SCB*)0xE000ED00 )

typedef struct
{
	u32 CPUID;
	u32 ICSR;
	u32 VTOR;
	u32 AIRCR;
	u32 SCR;
	u32 CCR;
	u32 SHPR1;
	u32 SHPR2;
	u32 SHPR3;
	u32 SHCRS;
	u32 CFSR;
	u32 HFSR;
	u32 MMAR;
	u32 BFAR;

}SCB;


/*the magic key number to write in the Application interrupt and reset control register*/
#define SCB_VECTKEY				0x05FA

/*used in the configuration SCB_INT_PRI_GROUP_SUB_MODE that will be used in MSCB_voidSetGroupPriority function*/
#define SCB_PRIORITY_16GP_0SUB			011
#define SCB_PRIORITY_8GP_2SUB			100
#define SCB_PRIORITY_4GP_4SUB			101
#define SCB_PRIORITY_2GP_8SUB			110
#define SCB_PRIORITY_0GP_16SUB			111


#endif /* SCB_PRIVATE_H_ */
