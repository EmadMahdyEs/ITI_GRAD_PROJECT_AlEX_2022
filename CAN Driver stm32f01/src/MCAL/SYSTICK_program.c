/*
 * SYSTICK_program.c
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */
#include "../../include/LIB/std_types.h"
#include "../../include/LIB/bit_math.h"
#include "../../include/MCAL/SYSTICK/SYSTICK_private.h"
#include "../../include/MCAL/SYSTICK/SYSTICK_configuration.h"
#include "../../include/MCAL/SYSTICK/SYSTICK_interface.h"
#include "../../include/MCAL/GPIO/GPIO_interface.h"


/*******************************************************************************************************************************
 * Function: MSYSTICK_voidInit
 * I/P parms: NONE
 * return: NONE
 * DESC: this function Init the Systick timer, the SYSTICK_INTERRUPT_CONFIG and SYSTICK_CLK_CONFIG should be pre-configured .
 * *****************************************************************************************************************************/
void MSYSTICK_voidInit(void)
{
#if SYSTICK_INTERRUPT_CONFIG == SYSTICK_INTERRUPT_ENABLE

	SYSTICK_REGS->CTRL |= (1<<SYSTICK_CTRL_REG_INT_BIT);

#elif	SYSTICK_INTERRUPT_CONFIG == SYSTICK_INTERRUPT_DISABLE

	SYSTICK_REGS->CTRL &=~ (1<<SYSTICK_CTRL_REG_INT_BIT);

#endif

#if	SYSTICK_CLK_CONFIG == SYSTICK_CLK_AHB_DIV_8

	SYSTICK_REGS->CTRL &=~ (1<<SYSTICK_CTRL_REG_CLK_BIT);

#elif	SYSTICK_CLK_CONFIG == SYSTICK_CLK_AHB

	SYSTICK_REGS->CTRL |= (1<<SYSTICK_CTRL_REG_CLK_BIT);

#endif
}

/*******************************************************************************************************************************
 * Function: MSYSTICK_voidLoadTimer
 * I/P parms: copy_u32LoadTimerValue
 * return: SYSTICK_CHECK_ERROR
 * DESC: this function Loads the SYSTICK Timer with the passed argument.
 * *****************************************************************************************************************************/
SYSTICK_CHECK_ERROR MSYSTICK_voidLoadTimer(u32 copy_u32LoadTimerValue)
{
	SYSTICK_CHECK_ERROR local_u8CheckError;
	if( copy_u32LoadTimerValue < SYSTICK_MAX_TICKS )
	{
		local_u8CheckError=SYSTICK_OK;

#if SYSTICK_IMMEDIATE_LOAD_CONFIG == SYSTICK_IMMEDIATE_LOAD

		SYSTICK_REGS->LOAD = copy_u32LoadTimerValue;
		/*write any value to make the count register reset and load the value in SYSTICK_LOAD register*/
		SYSTICK_REGS->VAL = copy_u32LoadTimerValue;

#elif SYSTICK_IMMEDIATE_LOAD_CONFIG == SYSTICK_NOT_IMMEDIATE_LOAD

		SYSTICK_REGS->LOAD = copy_u32LoadTimerValue;

#endif
	}
	else
	{
		local_u8CheckError=SYSTICK_NOK;
	}

	return local_u8CheckError;
}

/*******************************************************************************************************************************
 * Function: MSYSTICK_voidEnableTimer
 * I/P parms: NONE
 * return: NONE
 * DESC: this function let the timer start counting.
 * *****************************************************************************************************************************/
void MSYSTICK_voidEnableTimer(void)
{
	SYSTICK_REGS->CTRL |= (1<<SYSTICK_CTRL_REG_EN_BIT);
}
/*******************************************************************************************************************************
 * Function: MSYSTICK_voidDisableTimer
 * I/P parms: NONE
 * return: NONE
 * DESC: this function let the timer stop counting.
 * *****************************************************************************************************************************/
void MSYSTICK_voidDisableTimer(void)
{
	SYSTICK_REGS->CTRL &=~ (1<<SYSTICK_CTRL_REG_EN_BIT);
}

/*******************************************************************************************************************************
 * Function: MSYSTICK_voidSetBusyWait
 * I/P parms: copy_u32TicksToWait
 * return: NONE
 * DESC: this function works as the delay function, it takes the number of ticks to wait.
 * *****************************************************************************************************************************/
void MSYSTICK_voidSetBusyWait(u32 copy_u32TicksToWait)
{
	/*load the value in the LOAD register*/
	SYSTICK_REGS->LOAD = copy_u32TicksToWait;
	/*write any value to make the count register reset and load the value in SYSTICK_LOAD register*/
	SYSTICK_REGS->VAL = copy_u32TicksToWait;
	/*enable the timer*/
	SYSTICK_REGS->CTRL |=(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*polling on the flag waiting for underflow of the SYSTICK*/
	while( GET_BIT(SYSTICK_REGS->CTRL,SYSTICK_CTRL_REG__COUNT_FLAG_BIT) !=1 );
	/*disable the SYSTICK timer*/
	SYSTICK_REGS->CTRL &=~(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*pre-load=0*/
	SYSTICK_REGS->LOAD = 0;
}

/*******************************************************************************************************************************
 * Function: MSYSTICK_voidDelay_ms
 * I/P parms: copy_u32Time_ms
 * return: NONE
 * DESC: this function works as the delay function, it takes the time to wait in Millisecond.
 * *****************************************************************************************************************************/
void MSYSTICK_voidDelay_ms(u32 copy_u32Time_ms)
{
	u32 local_u32TicksToWait=0;

	local_u32TicksToWait = (copy_u32Time_ms*1000);
	/*load the value in the LOAD register*/
	SYSTICK_REGS->LOAD = local_u32TicksToWait;
	/*write any value to make the count register reset and load the value in SYSTICK_LOAD register*/
	SYSTICK_REGS->VAL = local_u32TicksToWait;
	/*enable the timer*/
	SYSTICK_REGS->CTRL |=(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*polling on the flag waiting for underflow of the SYSTICK*/
	while( GET_BIT(SYSTICK_REGS->CTRL,SYSTICK_CTRL_REG__COUNT_FLAG_BIT) !=1 );
	/*disable the SYSTICK timer*/
	SYSTICK_REGS->CTRL &=~(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*pre-load=0*/
	SYSTICK_REGS->LOAD = 0;
}


/*******************************************************************************************************************************
 * Function: MSYSTICK_voidIntervalSingle
 * I/P parms: copy_u32TicksToWait ,  void (*ptr2func)(void)
 * return: NONE
 * DESC: this function calls the passed ptr2func only once after the passed copy_u32TicksToWait passes unless the timer reseted.
 * *****************************************************************************************************************************/
void MSYSTICK_voidIntervalSingle(u32 copy_u32TicksToWait, void (*ptr2func)(void))
{
	/*load the value in the LOAD register*/
	SYSTICK_REGS->LOAD = copy_u32TicksToWait;
	/*write any value to make the count register reset and load the value in SYSTICK_LOAD register*/
	SYSTICK_REGS->VAL = copy_u32TicksToWait;
	/*enable the timer*/
	SYSTICK_REGS->CTRL |=(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*set callback_func to the function sent as input argument */
	MSYSTICK_voidSetCallBack(ptr2func,0);
}

/*******************************************************************************************************************************
 * Function: MSYSTICK_voidIntervalPeriodic
 * I/P parms: copy_u32TicksToWait ,  void (*ptr2func)(void)
 * return: NONE
 * DESC: this function calls the passed ptr2func after the passed copy_u32TicksToWait passes unless the timer reseted.
 * *****************************************************************************************************************************/
void MSYSTICK_voidIntervalPeriodic(u32 copy_u32TicksToWait, void (*ptr2func)(void))
{
	/*load the value in the LOAD register*/
	SYSTICK_REGS->LOAD = copy_u32TicksToWait;
	/*write any value to make the count register reset and load the value in SYSTICK_LOAD register*/
	SYSTICK_REGS->VAL = copy_u32TicksToWait;
	/*enable the timer*/
	SYSTICK_REGS->CTRL |=(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*set callback_func to the function sent as input argument */
	MSYSTICK_voidSetCallBack(ptr2func,1);
}


/*******************************************************************************************************************************
 * Function: MSYSTICK_u32GetElapsedTime
 * I/P parms: NONE
 * return: u32
 * DESC: this function returns the passed time since the last load.
 * *****************************************************************************************************************************/
u32 MSYSTICK_u32GetElapsedTime(void)
{
	u32 local_u32ElapsedTime = (SYSTICK_REGS->LOAD) - (SYSTICK_REGS->VAL);

	return local_u32ElapsedTime;
}

/*******************************************************************************************************************************
 * Function: MSYSTICK_u32GetRemainingTime
 * I/P parms: NONE
 * return: u32
 * DESC: this function returns the remaining time to underflow since the last load.
 * *****************************************************************************************************************************/
u32 MSYSTICK_u32GetRemainingTime(void)
{
	u32 local_u32RemainingTime = SYSTICK_REGS->VAL;

	return local_u32RemainingTime;
}

/*array of pointers to functions, used in callback*/
void (*ptrs[2])(void)={NULL,NULL};


/*******************************************************************************************************************************
 * Function: MSySTICK_voidStopIntervalPeriodic
 * I/P parms: NONE
 * return: NONE
 * DESC: this function is used to stop the periodic interval function
 * *****************************************************************************************************************************/
void MSySTICK_voidStopIntervalPeriodic(void)
{
	/*un-initialize the ptr2function of the periodic interval function*/
	ptrs[1] = NULL;
	/*disable interrupt*/
	SYSTICK_REGS->CTRL &=~ (1<<SYSTICK_CTRL_REG_INT_BIT);
	/*stop the timer*/
	SYSTICK_REGS->CTRL &=~(1<<SYSTICK_CTRL_REG_EN_BIT);
	/*clear the load register*/
	SYSTICK_REGS->LOAD = 0;
}





/*assume ID=0 to SYSTICK_voidIntervalSingle , ID=1 to SYSTICK_voidIntervalPeriodic*/
/*******************************************************************************************************************************
 * Function: MSYSTICK_voidSetCallBack
 * I/P parms: NONE
 * return: NONE
 * DESC: this function sets the callback function for both SYSTICK_voidIntervalSingle, SYSTICK_voidIntervalPeriodic functions.
 * 			-assume ID=0 to SYSTICK_voidIntervalSingle , ID=1 to SYSTICK_voidIntervalPeriodic.
 * *****************************************************************************************************************************/
void MSYSTICK_voidSetCallBack(void(*FunctionAddress)(void),u8 copy_u8FunctionID)
{
	if(copy_u8FunctionID == 0)
	{
		ptrs[0] = FunctionAddress;
		ptrs[1] = NULL;
	}
	else if (copy_u8FunctionID == 1)
	{
		ptrs[1] = FunctionAddress;
		ptrs[0] = NULL;
	}

}

/*Systick ISR*/
void SysTick_Handler(void)
{
	/*check which function should be executed*/
	if(ptrs[0]!=NULL)
	{
		/*disable timer*/
		SYSTICK_REGS->CTRL &=~(1<<SYSTICK_CTRL_REG_EN_BIT);
		/*disable interrupt*/
		//SYSTICK_REGS->CTRL &=~ (1<<SYSTICK_CTRL_REG_INT_BIT);
		/*call the single interval function*/
		ptrs[0]();
	}
	else if(ptrs[1]!=NULL)
	{
		/*call the periodic interval function*/
		ptrs[1]();
	}
	/*clear Int flag by reading it*/
	u32 temp = GET_BIT( (SYSTICK_REGS->CTRL) ,16);
}


