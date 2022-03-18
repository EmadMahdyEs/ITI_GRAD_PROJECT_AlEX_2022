/*
 * SCB_program.c
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */
#include "../../include/LIB/std_types.h"
#include "../../include/LIB/bit_math.h"

#include "../../../SYSTICK_project/include/MCAL/SCB/SCB_private.h"
#include "../../../SYSTICK_project/include/MCAL/SCB/SCB_configuration.h"
#include "../../../SYSTICK_project/include/MCAL/SCB/SCB_interface.h"



/*this function should be called before the MNVIC_voidSetIntPriority function to determine the functionality of the NVIC_IPRs_bits*/
void MSCB_voidSetSystemGroupPriority(void)
{
	if(	SCB_INT_PRI_GROUP_SUB_MODE==SCB_PRIORITY_16GP_0SUB || SCB_INT_PRI_GROUP_SUB_MODE==SCB_PRIORITY_8GP_2SUB ||
			SCB_INT_PRI_GROUP_SUB_MODE==SCB_PRIORITY_4GP_4SUB || SCB_INT_PRI_GROUP_SUB_MODE==SCB_PRIORITY_2GP_8SUB ||
			SCB_INT_PRI_GROUP_SUB_MODE==SCB_PRIORITY_0GP_16SUB	)
	{
		SCB_REGS->AIRCR = ( (SCB_VECTKEY<<16) | (SCB_INT_PRI_GROUP_SUB_MODE<<8) );
	}
	else
	{	}

}

/*used to know the current system group priority..
 * called by MSCB_voidSetCoreIntPriority function,
 * called by MNVIC_voidSetIntPriority function*/
u8 MSCB_voidGetSystemGroupPriority(void)
{
	return (((SCB_REGS->AIRCR)&0x00000700)>>8);
}


/*used to configure the interrupt priority of any related core peripheral..
 *called by MNVIC_voidSetIntPriority function if the peripheral sent to it is a core peripheral*/
void MSCB_voidSetCoreIntPriority(s8 copy_u8InterruptID,u8 copy_u8GroupPriority,u8 copy_u8SubPriority)
{
	u8 local_SysGroupPriority=MSCB_voidGetSystemGroupPriority();
	u8 local_u8priority=0;

	switch(local_SysGroupPriority)
	{
	case SCB_PRIORITY_16GP_0SUB:
		local_u8priority |= (copy_u8GroupPriority<<0);
		break;

	case SCB_PRIORITY_8GP_2SUB:
		/*ensuring that only the first bit could be used*/
		copy_u8SubPriority &= 0x01;
		local_u8priority |= ( (copy_u8GroupPriority<<1)|(copy_u8SubPriority<<0) );
		break;

	case SCB_PRIORITY_4GP_4SUB:
		/*ensuring that only the first two bits could be used*/
		copy_u8SubPriority &= 0x03;
		local_u8priority |= ( (copy_u8GroupPriority<<2)|(copy_u8SubPriority<<0) );
		break;

	case SCB_PRIORITY_2GP_8SUB:
		/*ensuring that only the first three bits could be used*/
		copy_u8SubPriority &= 0x07;
		local_u8priority |= ( (copy_u8GroupPriority<<3)|(copy_u8SubPriority<<0) );
		break;

	case SCB_PRIORITY_0GP_16SUB:
		local_u8priority |= ( (copy_u8SubPriority<<0) );
		break;
	}


	switch(copy_u8InterruptID)
	{
	case SCB_VECT_MEMORY_MANAGE_ID:
		SCB_REGS->SHPR1 = local_u8priority<<4;
		break;
	case SCB_VECT_BUSFAULT_ID:
		SCB_REGS->SHPR1 = local_u8priority<<12;
		break;
	case SCB_VECT_USAGE_FAULT_ID:
		SCB_REGS->SHPR1 = local_u8priority<<20;
		break;
	case SCB_VECT_SVCALL_ID:
		SCB_REGS->SHPR2 = local_u8priority<<28;
		break;
	case SCB_VECT_PENDSV_ID:
		SCB_REGS->SHPR3 = local_u8priority<<20;
		break;
	case SCB_VECT_SYSTICK_ID:
		SCB_REGS->SHPR3 = local_u8priority<<28;
		break;
	}


}

