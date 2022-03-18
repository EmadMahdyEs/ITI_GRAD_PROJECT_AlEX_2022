/*
 * SCB_interface.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */

#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_


void MSCB_voidSetSystemGroupPriority(void);
u8 MSCB_voidGetSystemGroupPriority(void);
void MSCB_voidSetCoreIntPriority(s8 copy_u8InterruptID,u8 copy_u8GroupPriority,u8 copy_u8SubPriority);

/*used in the configuration SCB_INT_PRI_GROUP_SUB_MODE that will be used in MSCB_voidSetGroupPriority function*/
#define SCB_PRIORITY_16GP_0SUB			011
#define SCB_PRIORITY_8GP_2SUB			100
#define SCB_PRIORITY_4GP_4SUB			101
#define SCB_PRIORITY_2GP_8SUB			110
#define SCB_PRIORITY_0GP_16SUB			111

/*used to send the interrupt ID to MSCB_voidSetCoreIntPriority function*/
#define SCB_VECT_SYSTICK_ID						-1
#define SCB_VECT_PENDSV_ID						-2
#define SCB_VECT_DEBUG_MONITOR_ID				-3
#define SCB_VECT_SVCALL_ID						-4
#define SCB_VECT_USAGE_FAULT_ID					-5
#define SCB_VECT_BUSFAULT_ID					-6
#define SCB_VECT_MEMORY_MANAGE_ID				-7


#endif /* SCB_INTERFACE_H_ */
