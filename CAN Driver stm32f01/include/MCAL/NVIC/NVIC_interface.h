/*
 * NVIC_interface.h
 *
 *  Created on: Feb 19, 2022
 *      Author: Mohy
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_


void MNVIC_voidEnablePeripheral(u8 copy_u8InterruptID);

void MNVIC_voidDisablePeripheral(u8 copy_u8InterruptID);

void MNVIC_voidSetPending(u8 copy_u8InterruptID);

void MNVIC_voidClearPending(u8 copy_u8InterruptID);

u8 MNVIC_u8CheckActive(u8 copy_u8InterruptID);

void MNVIC_voidSetIntPriority(s8 copy_u8InterruptID,u8 copy_u8GroupPriority,u8 copy_u8SubPriority);

/*used to check the return of the MNVIC_u8CheckActive function*/
#define NVIC_ACTIVE_INTERRUPT		1
#define NVIC_NOT_ACTIVE_INTERRUPT	0
/***********************************************************/





#endif /* NVIC_INTERFACE_H_ */
