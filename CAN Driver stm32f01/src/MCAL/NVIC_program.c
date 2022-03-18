/*
 * NVIC_program.c
 *
 *  Created on: Feb 19, 2022
 *      Author: Mohy
 */

#include "../../include/LIB/std_types.h"
#include "../../include/LIB/bit_math.h"

#include "../../include/MCAL/NVIC/NVIC_interface.h"
#include "../../include/MCAL/NVIC/NVIC_configuration.h"
#include "../../include/MCAL/NVIC/NVIC_private.h"
#include "../../include/MCAL/SCB/SCB_interface.h"

/*enable a specific interrupt*/
void MNVIC_voidEnablePeripheral(u8 copy_u8InterruptID)
{
	NVIC_REG->ISER[copy_u8InterruptID/32] |= (1<<copy_u8InterruptID);
}
/*disable a specific interrupt*/
void MNVIC_voidDisablePeripheral(u8 copy_u8InterruptID)
{
	NVIC_REG->ICER[copy_u8InterruptID/32] |= (1<<copy_u8InterruptID);
}
/*set an interrupt to be in the pending state by software*/
void MNVIC_voidSetPending(u8 copy_u8InterruptID)
{
	NVIC_REG->ISPR[copy_u8InterruptID/32] |= (1<<copy_u8InterruptID);
}
/*clear the pending state of an interrupt by software*/
void MNVIC_voidClearPending(u8 copy_u8InterruptID)
{
	NVIC_REG->ICPR[copy_u8InterruptID/32] |= (1<<copy_u8InterruptID);
}

/*check if a specific interrupt is currently active*/
u8 MNVIC_u8CheckActive(u8 copy_u8InterruptID)
{
	u8 local_u8ReturnState = ((NVIC_REG->IABR[copy_u8InterruptID/32])>>copy_u8InterruptID)&0x00000001;

	return local_u8ReturnState;
}


/*before calling this function, the MSCB_voidSetGroupPriority function must be called first to configure the functionality for those bits*/
void MNVIC_voidSetIntPriority(s8 copy_u8InterruptID,u8 copy_u8GroupPriority,u8 copy_u8SubPriority)
{
	/*check if its a core peripheral*/
	if(copy_u8InterruptID < 0)
	{
		MSCB_voidSetCoreIntPriority(copy_u8InterruptID,copy_u8GroupPriority,copy_u8SubPriority);
	}
	else
	{
		/*read the system group interrupt*/
		u8 local_SysGroupPriority=MSCB_voidGetSystemGroupPriority();
		switch(local_SysGroupPriority)
		{
		case SCB_PRIORITY_16GP_0SUB:
			NVIC_REG->IPR[copy_u8InterruptID] = (copy_u8GroupPriority<<4);
			break;

		case SCB_PRIORITY_8GP_2SUB:
			/*ensuring that only the first bit could be used*/
			copy_u8SubPriority &= 0x01;
			NVIC_REG->IPR[copy_u8InterruptID] = (copy_u8GroupPriority<<5)|(copy_u8SubPriority<<4);
			break;

		case SCB_PRIORITY_4GP_4SUB:
			/*ensuring that only the first two bits could be used*/
			copy_u8SubPriority &= 0x03;
			NVIC_REG->IPR[copy_u8InterruptID] = (copy_u8GroupPriority<<6)|(copy_u8SubPriority<<4);
			break;

		case SCB_PRIORITY_2GP_8SUB:
			/*ensuring that only the first three bits could be used*/
			copy_u8SubPriority &= 0x07;
			NVIC_REG->IPR[copy_u8InterruptID] = (copy_u8GroupPriority<<7)|(copy_u8SubPriority<<4);
			break;

		case SCB_PRIORITY_0GP_16SUB:
			NVIC_REG->IPR[copy_u8InterruptID] =(copy_u8SubPriority<<4);
			break;
		}
	}


}





