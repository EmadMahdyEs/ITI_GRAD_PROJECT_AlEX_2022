/*
 * SYSTICK_interface.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/************used in the Check error return**************/
typedef u8 SYSTICK_CHECK_ERROR;
#define SYSTICK_OK			1
#define SYSTICK_NOK			0
/*******************************************************/


void MSYSTICK_voidInit(void);
SYSTICK_CHECK_ERROR MSYSTICK_voidLoadTimer(u32 copy_u32LoadTimerValue);
void MSYSTICK_voidEnableTimer(void);
void MSYSTICK_voidDisableTimer(void);
void MSYSTICK_voidSetBusyWait(u32 copy_u32TicksToWait);
void MSYSTICK_voidDelay_ms(u32 copy_u32Time_ms);
void MSYSTICK_voidIntervalSingle(u32 copy_u32TicksToWait, void (*ptr2func)(void));
void MSYSTICK_voidIntervalPeriodic(u32 copy_u32TicksToWait, void (*ptr2func)(void));
u32 MSYSTICK_u32GetElapsedTime(void);
u32 MSYSTICK_u32GetRemainingTime(void);
void MSySTICK_voidStopIntervalPeriodic(void);
void MSYSTICK_voidSetCallBack(void(*FunctionAddress)(void),u8 copy_u8FunctionID);




#endif /* SYSTICK_INTERFACE_H_ */
