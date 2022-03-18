/*
 * GPIO_interface.h
 *
 *  Created on: Feb 15, 2022
 *      Author: Mohy
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


typedef u8 ERROR_STATUS_TYPE;

void MGPIO_voidSetDirection(u8 copy_u8PortNumber, u8 copy_u8PinNumber,u8 copy_u8Mode,u8 copy_u8CNF);

void MGPIO_voidSetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_u8Value);

ERROR_STATUS_TYPE MGPIO_u8GetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 * copy_u8ptrValue);

ERROR_STATUS_TYPE MGPIO_u8LockPortConfigs(u8 copy_u8PortNumber,u16 copy_u16PortLockvalue);

void MGPIO_voidSetPinAlternativeFunction(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_AF_Mode);

/*available PORTS*/
#define GPIO_PORTA			0
#define GPIO_PORTB			1
#define GPIO_PORTC			2
/*available PINS*/
#define GPIO_PIN0			0
#define GPIO_PIN1			1
#define GPIO_PIN2			2
#define GPIO_PIN3			3
#define GPIO_PIN4			4
#define GPIO_PIN5			5
#define GPIO_PIN6			6
#define GPIO_PIN7			7
#define GPIO_PIN8			8
#define GPIO_PIN9			9
#define GPIO_PIN10			10
#define GPIO_PIN11			11
#define GPIO_PIN12			12
#define GPIO_PIN13			13
#define GPIO_PIN14			14
#define GPIO_PIN15			15

/*used to adjust CNF bits*/
#define GPIO_OUTPUT_PUSH_PULL			0b00
#define GPIO_OUTPUT_OPEN_DRAIN			0b01
#define GPIO_AF_OUTPUT_PUSH_PULL		0b10
#define GPIO_AF_OUTPUT_OPEN_DRAIN		0b11
#define GPIO_ANALOG_INPUT				0b00
#define GPIO_FLOATING_INPUT				0b01
#define GPIO_PULL_UP_DOWN_INPUT			0b10

/*used to adjust MODE bits*/
#define GPIO_INPUT_MODE					0b00
#define GPIO_OUTPUT_10M_SPEED_MODE		0b01
#define GPIO_OUTPUT_2M_SPEED_MODE		0b10
#define GPIO_OUTPUT_50M_SPEED_MODE		0b11
/*GPIO_PIN values*/
#define GPIO_HIGH		1
#define GPIO_LOW		0
/*ERROR_STATUS*/
#define GPIO_OK			1
#define GPIO_NOK		0
/*LOCKING state*/
#define GPIO_PIN_LOCKED			1
#define GPIO_PIN_NOT_LOCKED		0


/*alternative function modes*/
#define AFIO_EXTI			0




/*external interrupt port number*/
#define AF_EXTI_PORTA		0x0000
#define AF_EXTI_PORTB		0x0001
#define AF_EXTI_PORTC		0x0010

/*used to determine the channel number of an EXTI*/
#define AF_EXTI_CHANNEL0	0
#define AF_EXTI_CHANNEL1	1
#define AF_EXTI_CHANNEL2	2
#define AF_EXTI_CHANNEL3	3
#define AF_EXTI_CHANNEL4	4
#define AF_EXTI_CHANNEL5	5
#define AF_EXTI_CHANNEL6	6
#define AF_EXTI_CHANNEL7	7


#endif /* GPIO_INTERFACE_H_ */
