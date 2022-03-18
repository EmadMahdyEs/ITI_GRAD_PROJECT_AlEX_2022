/*
 * GPIO_program.c
 *
 *  Created on: Feb 15, 2022
 *      Author: Mohy
 */
#include "../../include/LIB/std_types.h"
#include "../../include/LIB/bit_math.h"


#include "../../include/MCAL/GPIO/GPIO_private.h"
#include "../../include/MCAL/GPIO/GPIO_configuration.h"
#include "../../include/MCAL/GPIO/GPIO_interface.h"

/******************************************************************************
 * Function: MGPIO_voidSetDirection
 * I/P parms: copy_u8PortNumber , copy_u8PinNumber , copy_u8Mode , copy_u8CNF
 * return: None
 * DESC: this function Set the direction of a GPIO-PIN.
 * *******************************************************************************/
void MGPIO_voidSetDirection(u8 copy_u8PortNumber, u8 copy_u8PinNumber,u8 copy_u8Mode,u8 copy_u8CNF)
{
	switch(copy_u8PortNumber)
	{
	case GPIO_PORTA:
		if (copy_u8PinNumber <= 7)
		{
			GPIO_PORTA_REG->CRL &= ~(15<< (4 * copy_u8PinNumber));
			GPIO_PORTA_REG->CRL |= (copy_u8Mode << (4 * copy_u8PinNumber));
			GPIO_PORTA_REG->CRL |= (copy_u8CNF << ((4 * copy_u8PinNumber) + 2));
		}
		else if (copy_u8PinNumber >= 8 && copy_u8PinNumber <= 15)
		{
			copy_u8PinNumber -= 8;
			GPIO_PORTA_REG->CRH &= ~(15<< (4 * copy_u8PinNumber));
			GPIO_PORTA_REG->CRH |= (copy_u8Mode << (4 * copy_u8PinNumber));
			GPIO_PORTA_REG->CRH |= (copy_u8CNF << ((4 * copy_u8PinNumber) + 2));
		}
		break;

	case GPIO_PORTB:
		if (copy_u8PinNumber <= 7)
		{
			GPIO_PORTB_REG->CRL &= ~(15<< (4 * copy_u8PinNumber));
			GPIO_PORTB_REG->CRL |= (copy_u8Mode << (4 * copy_u8PinNumber));
			GPIO_PORTB_REG->CRL |= (copy_u8CNF << ((4 * copy_u8PinNumber) + 2));
		}
		else if (copy_u8PinNumber >= 8 && copy_u8PinNumber <= 15)
		{
			copy_u8PinNumber -= 8;
			GPIO_PORTB_REG->CRH &= ~(15<< (4 * copy_u8PinNumber));
			GPIO_PORTB_REG->CRH |= (copy_u8Mode << (4 * copy_u8PinNumber));
			GPIO_PORTB_REG->CRH |= (copy_u8CNF << ((4 * copy_u8PinNumber) + 2));
		}
		break;

	case GPIO_PORTC:
		if (copy_u8PinNumber >= 13 && copy_u8PinNumber <= 15)
		{
			copy_u8PinNumber -= 8;
			GPIO_PORTC_REG->CRH &= ~(15<< (4 * copy_u8PinNumber));
			GPIO_PORTC_REG->CRH |= (copy_u8Mode << (4 * copy_u8PinNumber));
			GPIO_PORTC_REG->CRH |= (copy_u8CNF << ((4 * copy_u8PinNumber) + 2));
		}
		break;

	}

}
/******************************************************************************
 * Function: MGPIO_voidSetPinValue
 * I/P parms: copy_u8PortNumber , copy_u8PinNumber , copy_u8Value
 * return: None
 * DESC: this function set a value on a GPIO-PIN.
 * *******************************************************************************/
void MGPIO_voidSetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_u8Value)
{
	if(copy_u8Value==GPIO_HIGH)
	{
		switch(copy_u8PortNumber)
			{
		case GPIO_PORTA:
			GPIO_PORTA_REG->BSRR = (1 << copy_u8PinNumber);
			break;
		case GPIO_PORTB:
			GPIO_PORTB_REG->BSRR = (1 << copy_u8PinNumber);
			break;
		case GPIO_PORTC:
			GPIO_PORTC_REG->BSRR = (1 << copy_u8PinNumber);
			break;
		}
	}
	else if (copy_u8Value == GPIO_LOW)
	{
		switch (copy_u8PortNumber)
		{
		case GPIO_PORTA:
			GPIO_PORTA_REG->BRR = (1 << copy_u8PinNumber);
			break;
		case GPIO_PORTB:
			GPIO_PORTB_REG->BRR = (1 << copy_u8PinNumber);
			break;
		case GPIO_PORTC:
			GPIO_PORTC_REG->BRR = (1 << copy_u8PinNumber);
			break;
		}
	}

}
/******************************************************************************
 * Function: MGPIO_u8GetPinValue
 * I/P parms: copy_u8PortNumber , copy_u8PinNumber , *copy_u8ptrValue
 * return: ERROR_STATUS_TYPE
 * DESC: this function get an input value on a GPIO-PIN.
 * *******************************************************************************/
ERROR_STATUS_TYPE MGPIO_u8GetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 * copy_u8ptrValue)
{
	u8 local_u8_ckeck;
	switch(copy_u8PortNumber)
		{
		case GPIO_PORTA:
			*copy_u8ptrValue = (u8)((GPIO_PORTA_REG->IDR >> copy_u8PinNumber)&0x00000001);
			local_u8_ckeck=GPIO_OK;
			break;
		case GPIO_PORTB:
			*copy_u8ptrValue = (u8)((GPIO_PORTB_REG->IDR >> copy_u8PinNumber)&0x00000001);
			local_u8_ckeck=GPIO_OK;
			break;
		case GPIO_PORTC:
			*copy_u8ptrValue = (u8)((GPIO_PORTC_REG->IDR >> copy_u8PinNumber)&0x00000001);
			local_u8_ckeck=GPIO_OK;
			break;
		default:
			local_u8_ckeck=GPIO_NOK;
		}

	return local_u8_ckeck;
}


/*******************************************************************************************************************************
 * Function: MGPIO_u8LockPortConfigs
 * I/P parms: copy_u8PortNumber , copy_u16PortLockvalue
 * return: ERROR_STATUS_TYPE
 * DESC: this function LOCK the configuration of a port.
 * 		-should receive the port number, and 16-bit configuration for the port deciding which pins are locked and which are not.
 * *****************************************************************************************************************************/
ERROR_STATUS_TYPE MGPIO_u8LockPortConfigs(u8 copy_u8PortNumber,u16 copy_u16PortLockvalue)
{
	ERROR_STATUS_TYPE local_Check=0;

	/*these two variables used as I should write the pin to be locked or not at the same time during performing the lock sequence*/
	u32 local_SetWithConfig = ( (1<<16) |  copy_u16PortLockvalue);
	u32 local_ClearWithConfig = ( (0<<16) | copy_u16PortLockvalue);

	switch (copy_u8PortNumber)
	{
	case GPIO_PORTA:
		/*write 1*/
		GPIO_PORTA_REG->LCKR =local_SetWithConfig;
		/*write 0*/
		GPIO_PORTA_REG->LCKR =local_ClearWithConfig;
		/*write 1*/
		GPIO_PORTA_REG->LCKR =local_SetWithConfig;
		/*read 0*/
		local_Check = (((GPIO_PORTA_REG->LCKR)>>16)&0x00000001);
		/*should read 1*/
		local_Check = (((GPIO_PORTA_REG->LCKR)>>16)&0x00000001);
	break;

	case GPIO_PORTB:
		/*write 1*/
		GPIO_PORTB_REG->LCKR =local_SetWithConfig;
		/*write 0*/
		GPIO_PORTB_REG->LCKR =local_ClearWithConfig;
		/*write 1*/
		GPIO_PORTB_REG->LCKR =local_SetWithConfig;
		/*read 0*/
		local_Check = (((GPIO_PORTB_REG->LCKR)>>16)&0x00000001);
		/*should read 1*/
		local_Check = (((GPIO_PORTB_REG->LCKR)>>16)&0x00000001);
		break;

	case GPIO_PORTC:
		/*write 1*/
		GPIO_PORTC_REG->LCKR =local_SetWithConfig;
		/*write 0*/
		GPIO_PORTC_REG->LCKR =local_ClearWithConfig;
		/*write 1*/
		GPIO_PORTC_REG->LCKR =local_SetWithConfig;
		/*read 0*/
		local_Check = (((GPIO_PORTC_REG->LCKR)>>16)&0x00000001);
		/*should read 1*/
		local_Check = (((GPIO_PORTC_REG->LCKR)>>16)&0x00000001);
		break;
	}

return local_Check;
}

/*******************************************************************************************************************************
 * Function: MGPIO_voidSetPinAlternativeFunction
 * I/P parms: copy_u8PortNumber , copy_u8PinNumber , u8 copy_AF_Mode
 * return: NONE
 * DESC: this function let a GPIO_PIN works with its ALTERNATIVE function.
 * *****************************************************************************************************************************/
void MGPIO_voidSetPinAlternativeFunction(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_AF_Mode)
{
	if(copy_AF_Mode == AFIO_EXTI)
	{
		AFIO_REG->EXTICR[copy_u8PinNumber/4] &=~ (15 << ( (copy_u8PinNumber%4)*4) );
		AFIO_REG->EXTICR[copy_u8PinNumber/4] |= (copy_u8PortNumber<< ( (copy_u8PinNumber%4)*4) );
	}


}

