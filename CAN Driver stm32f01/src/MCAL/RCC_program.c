/*
 * RCC_program.c
 *
 *  Created on: Feb 14, 2022
 *      Author: Mohy
 */

#include "../../include/LIB/std_types.h"
#include "../../include/LIB/bit_math.h"

#include "../../include/MCAL/RCC/RCC_configuration.h"
#include "../../include/MCAL/RCC/RCC_interface.h"
#include "../../include/MCAL/RCC/RCC_private.h"

/***********************************************************************************************
 * Function: MRCC_CheckReady
 *
 * I/P parameters: copy_u8ClkType:
 * 							-CLK_HSI.
 * 							-CLK_HSE.
 * 							-CLK_PLL.
 *
 * return: u8-> error status:
 * 							-CLK_READY.
 * 							-CLK_NOT_READY.
 * 							-CLK_ARG_OUT_OF_RANGE.
 *
 * DESC: this function check if the selected clock source is now stable and ready to work.
 * *********************************************************************************************/
u8 MRCC_CheckReady(u8 copy_u8ClkType)
{
	u8 local_u8_CheckReady=CLK_READY;
	u32 local_u8_counter=0;

	if(copy_u8ClkType!=CLK_HSI && copy_u8ClkType!=CLK_HSE &&  copy_u8ClkType!=CLK_PLL)
	{
		local_u8_CheckReady=CLK_ARG_OUT_OF_RANGE;
	}
	else
	{
		while(GET_BIT(RCC_U32_CR_REG,copy_u8ClkType)==CLK_NOT_READY)
		{
			local_u8_counter++;
			if(local_u8_counter==CLK_READY_TIME_OUT)
			{
				local_u8_CheckReady=CLK_NOT_READY;
				break;
			}
		}
	}


	return local_u8_CheckReady;
}

/***********************************************************************************************
 * Function: MRCC_SetClkSource
 *
 * I/P parameters: copy_u8ClkType:
 * 							-CLK_HSI.
 * 							-CLK_HSE.
 * 							-CLK_PLL.
 *
 * return: u8-> error status:
 * 							-RCC_OK.
 * 							-RCC_NOK.
 *
 * DESC: this function sets the clock source that will be used in the system.
 * *********************************************************************************************/
u8 MRCC_SetClkSource(u8 copy_u8ClkType)
{
	u8 local_u8_check_error=0;
	switch (copy_u8ClkType)
	{
	case CLK_HSI:
		RCC_U32_CFGR_REG = ((RCC_U32_CFGR_REG&0xFFFFFFFC)|0);
		local_u8_check_error = RCC_OK;
		break;
	case CLK_HSE:
		RCC_U32_CFGR_REG = (RCC_U32_CFGR_REG&0xFFFFFFFC)| 1;
		local_u8_check_error = RCC_OK;
		break;
	case CLK_PLL:
		RCC_U32_CFGR_REG = (RCC_U32_CFGR_REG&0xFFFFFFFC)| 2;
		local_u8_check_error = RCC_OK;
		break;
	default:
		local_u8_check_error = RCC_NOK;
	}

	return local_u8_check_error;
}
/***********************************************************************************************
 * Function: MRCC_SetClkSourceStatus
 *
 * I/P parameters: copy_u32ClkSource:
 * 							-CLK_HSI.
 * 							-CLK_HSE.
 * 							-CLK_PLL.
 * 					copy_u8Status:
 * 							-CLK_SRC_ENABLE.
 *							-CLK_SRC_DISABLE.
 *
 * return: NONE
 *
 * DESC: this function enable/disable a specified clock source
 * *********************************************************************************************/
void MRCC_SetClkSourceStatus(u8 copy_u32ClkSource, u8 copy_u8Status)
{
	switch(copy_u8Status)
	{
	case CLK_SRC_ENABLE:

		switch (copy_u32ClkSource)
		{
		case CLK_HSI:
			SET_BIT(RCC_U32_CR_REG, CLK_HSI_ON_BIT);
			break;
		case CLK_HSE:
			SET_BIT(RCC_U32_CR_REG, CLK_HSE_ON_BIT);
			break;
		case CLK_PLL:
			SET_BIT(RCC_U32_CR_REG, CLK_PLL_ON_BIT);
			break;
		}

		break;

	case CLK_SRC_DISABLE:

		switch (copy_u32ClkSource)
		{
		case CLK_HSI:
			CLEAR_BIT(RCC_U32_CR_REG,CLK_HSI_ON_BIT);
			break;
		case CLK_HSE:
			CLEAR_BIT(RCC_U32_CR_REG,CLK_HSE_ON_BIT);
			break;
		case CLK_PLL:
			CLEAR_BIT(RCC_U32_CR_REG,CLK_PLL_ON_BIT);
			break;
		}

		break;
	}
}

/***********************************************************************************************
 * Function: MRCC_SetCLKBussesPrescaller
 *
 * I/P parameters: AHP_u16_prescaller:				APB1_u8_prescaller, APB2_u8_prescaller:
 * 							RCC_AHB_PRESCALLER1						RCC_APB_PRESCALLER1
 * 							RCC_AHB_PRESCALLER2		                RCC_APB_PRESCALLER2
 * 							RCC_AHB_PRESCALLER4		                RCC_APB_PRESCALLER4
 * 							RCC_AHB_PRESCALLER8		                RCC_APB_PRESCALLER8
 * 							RCC_AHB_PRESCALLER16	                RCC_APB_PRESCALLER16
 *							RCC_AHB_PRESCALLER64
 *                          RCC_AHB_PRESCALLER128
 *				            RCC_AHB_PRESCALLER256
 *                          RCC_AHB_PRESCALLER512
 *
 * return: NONE
 *
 * DESC: this function set the prescaller for all the system busses.
 * *********************************************************************************************/
void MRCC_SetCLKBussesPrescaller(u16 AHP_u16_prescaller, u8 APB1_u8_prescaller, u8 APB2_u8_prescaller)
{
	RCC_U32_CFGR_REG &= 0xC00F;
	/*set the prescallers of the busses*/
	RCC_U32_CFGR_REG |=(APB1_u8_prescaller<<8);
	RCC_U32_CFGR_REG |=(APB2_u8_prescaller<<11);
	RCC_U32_CFGR_REG |=(AHP_u16_prescaller<<4);
}
/***********************************************************************************************
 * Function: MRCC_SetPLLConfiguration
 *
 * I/P parameters: PLL_u8_Source:						PLL_u8_MulFactor:
 *						-RCC_PLL_SRC_HSI.							-from (PLL_MUL_2) to (PLL_MUL_16)
 *						-RCC_PLL_SRC_HSE.
 *						-RCC_PLL_SRC_HSE_DIV2.
 *
 * return: NONE
 * DESC: this function configure the PLl source and multiplication factor.
 * *********************************************************************************************/
void MRCC_SetPLLConfiguration(u8 PLL_u8_Source, u8 PLL_u8_MulFactor)
{
	switch(PLL_u8_Source)
	{
	case RCC_PLL_SRC_HSI:
		/*use HSI*/
		CLEAR_BIT(RCC_U32_CFGR_REG,RCC_PLL_SRC_BIT);
		/*mul factor*/
		RCC_U32_CFGR_REG = (RCC_U32_CFGR_REG&0xFFC3FFFF)| (PLL_u8_MulFactor<<RCC_PLL_MUL_BIT);
		break;

	case RCC_PLL_SRC_HSE:
		/*use HSE*/
		SET_BIT(RCC_U32_CFGR_REG,RCC_PLL_SRC_BIT);
		/*HSE divider*/
		CLEAR_BIT(RCC_U32_CFGR_REG,RCC_PLL_XTPRE_BIT);
		/*mul factor*/
		RCC_U32_CFGR_REG = (RCC_U32_CFGR_REG&0xFFC3FFFF)| (PLL_u8_MulFactor<<RCC_PLL_MUL_BIT);
		break;

	case RCC_PLL_SRC_HSE_DIV2:
		/*use HSE*/
		SET_BIT(RCC_U32_CFGR_REG,RCC_PLL_SRC_BIT);
		/*HSE divider*/
		SET_BIT(RCC_U32_CFGR_REG,RCC_PLL_XTPRE_BIT);
		/*mul factor*/
		RCC_U32_CFGR_REG = (RCC_U32_CFGR_REG&0xFFC3FFFF)| (PLL_u8_MulFactor<<RCC_PLL_MUL_BIT);
		break;
	}
}

/********************************************************************************************************************
 * Function: MRCC_SetPeripheralConfiguration
 *
 * I/P parameters: Peripheral_Name:						Peripheral_Bus:						Peripheral_Status:
	 *				-RCC_PLL_SRC_HSI.						-RCC_PERIPHERAL_AHB_BUS.			-RCC_PERIPHERAL_ENABLE.
	 *				-RCC_PLL_SRC_HSE.						-RCC_PERIPHERAL_APB2_BUS.			-RCC_PERIPHERAL_DISABLE.
	 *				-RCC_PLL_SRC_HSE_DIV2.					-RCC_PERIPHERAL_APB1_BUS.
 *
 * return: NONE
 * DESC: this function used to enable/disable clock delivery for an intended peripheral on a specific bus.
 * ********************************************************************************************************************/
void MRCC_SetPeripheralConfiguration(u8 Peripheral_Name, u8 Peripheral_Bus,u8 Peripheral_Status)
{
	switch(Peripheral_Bus)
	{
	case RCC_PERIPHERAL_AHB_BUS:
		CLEAR_BIT(RCC_U32_AHBENR_REG, Peripheral_Name);
		RCC_U32_AHBENR_REG |= (Peripheral_Status<<Peripheral_Name);
		break;
	case RCC_PERIPHERAL_APB2_BUS:
		CLEAR_BIT(RCC_U32_APB2ENR_REG, Peripheral_Name);
		RCC_U32_APB2ENR_REG |= (Peripheral_Status<<Peripheral_Name);
		break;
	case RCC_PERIPHERAL_APB1_BUS:
		CLEAR_BIT(RCC_U32_APB1ENR_REG, Peripheral_Name);
		RCC_U32_APB1ENR_REG |= (Peripheral_Status<<Peripheral_Name);
		break;
	}
}

/********************************************************************************************************************
 * Function: MRCC_Init
 *
 * I/P parameters: NONE
 *
 * return: NONE
 *
 * configurations used:
 * 					-RCC_SYS_CLK_SRC.
 * 					-RCC_SYS_CLK_PLL_MUL_FACTOR.
 * 					-RCC_PLL_SRC_HSE_MODE.
 * 					-AHB_BUS_PRESCALLER.
 * 					-APB1_BUS_PRESCALLER.
 * 					-APB2_BUS_PRESCALLER
 *
 * DESC: this function used to initialize the clock for the system and enable it, initialize the busses prescaller.
 * ********************************************************************************************************************/
void MRCC_Init(void)
{
#if RCC_SYS_CLK_SRC==RCC_SYS_CLK_HSI

u8 check_error;
/*enable HSI*/
MRCC_SetClkSourceStatus(CLK_HSI,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_HSI);
while( (check_error==CLK_NOT_READY) || (check_error==CLK_ARG_OUT_OF_RANGE) );
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_HSI);
while(check_error==RCC_NOK);
/*busses prescaller*/
MRCC_SetCLKBussesPrescaller(AHB_BUS_PRESCALLER,APB1_BUS_PRESCALLER,APB2_BUS_PRESCALLER);
/*PLL&HSE disable*/
MRCC_SetClkSourceStatus(CLK_HSE,CLK_SRC_DISABLE);
MRCC_SetClkSourceStatus(CLK_PLL,CLK_SRC_DISABLE);

#endif

#if RCC_SYS_CLK_SRC==RCC_SYS_CLK_HSE

u8 check_error;
/*enable HSI*/
MRCC_SetClkSourceStatus(CLK_HSI,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_HSI);
while(check_error==CLK_NOT_READY || check_error==CLK_ARG_OUT_OF_RANGE);
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_HSI);
while(check_error==RCC_NOK);
/*HSE enable*/
MRCC_SetClkSourceStatus(CLK_HSE,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_HSE);
while(check_error==CLK_NOT_READY || check_error==CLK_ARG_OUT_OF_RANGE);
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_HSE);
/*busses prescaller*/
MRCC_SetCLKBussesPrescaller(AHB_BUS_PRESCALLER,APB1_BUS_PRESCALLER,APB2_BUS_PRESCALLER);
/*PLL&HSI disable*/
MRCC_SetClkSourceStatus(CLK_HSI,CLK_SRC_DISABLE);
MRCC_SetClkSourceStatus(CLK_PLL,CLK_SRC_DISABLE);

#endif

#if RCC_SYS_CLK_SRC==RCC_SYS_CLK_PLL_HSI

u8 check_error;
/*enable HSI*/
MRCC_SetClkSourceStatus(CLK_HSI,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_HSI);
while(check_error==CLK_NOT_READY || check_error==CLK_ARG_OUT_OF_RANGE);
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_HSI);
while(check_error==RCC_NOK);
/*disable PLL*/
MRCC_SetClkSourceStatus(CLK_PLL,CLK_SRC_DISABLE);
/*PLL configurations*/
MRCC_SetPLLConfiguration(RCC_PLL_SRC_HSI,RCC_SYS_CLK_PLL_MUL_FACTOR);
/*PLL enable*/
MRCC_SetClkSourceStatus(CLK_PLL,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_PLL);
while(check_error==CLK_NOT_READY || check_error==CLK_ARG_OUT_OF_RANGE);
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_PLL);
/*busses prescaller*/
MRCC_SetCLKBussesPrescaller(AHB_BUS_PRESCALLER,APB1_BUS_PRESCALLER,APB2_BUS_PRESCALLER);
/*HSE disable*/
MRCC_SetClkSourceStatus(CLK_HSE,CLK_SRC_DISABLE);


#endif

#if RCC_SYS_CLK_SRC==RCC_SYS_CLK_PLL_HSE

u8 check_error;
/*enable HSI*/
MRCC_SetClkSourceStatus(CLK_HSE,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_HSE);
while(check_error==CLK_NOT_READY || check_error==CLK_ARG_OUT_OF_RANGE);
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_HSE);
while(check_error==0);
/*disable PLL*/
MRCC_SetClkSourceStatus(CLK_PLL,CLK_SRC_DISABLE);
/*PLL configurations*/
MRCC_SetPLLConfiguration(RCC_PLL_SRC_HSE_MODE,RCC_SYS_CLK_PLL_MUL_FACTOR);
/*PLL enable*/
MRCC_SetClkSourceStatus(CLK_PLL,CLK_SRC_ENABLE);
/*check ready*/
check_error=MRCC_CheckReady(CLK_PLL);
while(check_error==CLK_NOT_READY || check_error==CLK_ARG_OUT_OF_RANGE);
/*switch system clock*/
check_error=MRCC_SetClkSource(CLK_PLL);
/*busses prescaller*/
MRCC_SetCLKBussesPrescaller(AHB_BUS_PRESCALLER,APB1_BUS_PRESCALLER,APB2_BUS_PRESCALLER);
/*HSI disable*/
MRCC_SetClkSourceStatus(CLK_HSI,CLK_SRC_DISABLE);


#endif
}

