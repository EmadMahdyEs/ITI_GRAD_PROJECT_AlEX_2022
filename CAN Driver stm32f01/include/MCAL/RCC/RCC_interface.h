#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


/*the peripherals dependent bus*/
#define RCC_PERIPHERAL_AHB_BUS				0
#define RCC_PERIPHERAL_APB2_BUS				1
#define RCC_PERIPHERAL_APB1_BUS				2
/*states of the peripheral needed*/
#define RCC_PERIPHERAL_ENABLE				1
#define RCC_PERIPHERAL_DISABLE				0
/*peripherals ENABLE BITs for the AHB*/
#define RCC_PERIPHERAL_DMA1		0
#define RCC_PERIPHERAL_DMA2		1
#define RCC_PERIPHERAL_SRAM		2
#define RCC_PERIPHERAL_FLITF	4
#define RCC_PERIPHERAL_CRCE		6
#define RCC_PERIPHERAL_FSMC		8
#define RCC_PERIPHERAL_SDIO		10
/*peripherals ENABLE BITs for the APB2*/
#define RCC_PERIPHERAL_AFIO		0
#define RCC_PERIPHERAL_IOPA		2
#define RCC_PERIPHERAL_IOPB		3
#define RCC_PERIPHERAL_IOPC		4
#define RCC_PERIPHERAL_IOPD		5
#define RCC_PERIPHERAL_IOPE		6
#define RCC_PERIPHERAL_IOPF		7
#define RCC_PERIPHERAL_IOPG		8
#define RCC_PERIPHERAL_ADC1		9
#define RCC_PERIPHERAL_ADC2		10
#define RCC_PERIPHERAL_TIM1		11
#define RCC_PERIPHERAL_SPI1		12
#define RCC_PERIPHERAL_TIM8		13
#define RCC_PERIPHERAL_USART1	14
#define RCC_PERIPHERAL_ADC3		15
#define RCC_PERIPHERAL_TIM9		19
#define RCC_PERIPHERAL_TIM10	20
#define RCC_PERIPHERAL_TIM11	21
/*peripherals ENABLE BITs for the APB1*/
#define RCC_PERIPHERAL_TIM2		0
#define RCC_PERIPHERAL_TIM3		1
#define RCC_PERIPHERAL_TIM4		2
#define RCC_PERIPHERAL_TIM5		3
#define RCC_PERIPHERAL_TIM6		4
#define RCC_PERIPHERAL_TIM7		5
#define RCC_PERIPHERAL_TIM12	6
#define RCC_PERIPHERAL_TIM13	7
#define RCC_PERIPHERAL_TIM14	8
#define RCC_PERIPHERAL_WWDG		11
#define RCC_PERIPHERAL_SPI2		14
#define RCC_PERIPHERAL_SPI3		15
#define RCC_PERIPHERAL_USART2	17
#define RCC_PERIPHERAL_USART3	18
#define RCC_PERIPHERAL_USART4	19
#define RCC_PERIPHERAL_USART5	20
#define RCC_PERIPHERAL_I2C1		21
#define RCC_PERIPHERAL_I2C2		22
#define RCC_PERIPHERAL_USB		23
#define RCC_PERIPHERAL_CAN		25
#define RCC_PERIPHERAL_BKP		27
#define RCC_PERIPHERAL_PWR		28
#define RCC_PERIPHERAL_DAC		29
/*system clock enable bits*/
#define CLK_HSI				1
#define CLK_HSE				17
#define CLK_PLL				25
/*used to compare the return of the Check_Ready function to know is it ready or not*/
#define CLK_ARG_OUT_OF_RANGE	2
#define CLK_NOT_READY			0
#define CLK_READY				1

/*used by MRCC_SetClkSource*/
#define RCC_OK			1
#define RCC_NOK			0

/*used to configure the maximum time allowed for the */
#define CLK_READY_TIME_OUT		(50000UL)

/*clk enable disable*/
#define CLK_SRC_ENABLE			1
#define CLK_SRC_DISABLE			0
/*system clk dependency*/
#define CLK_PLL_ON_BIT			24
#define CLK_HSE_ON_BIT			16
#define CLK_HSI_ON_BIT			0



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
 *
 * DESC: this function check if the selected clock source is now stable and ready to work.
 * *********************************************************************************************/
u8 MRCC_CheckReady(u8 copy_u8ClkType);
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
u8 MRCC_SetClkSource(u8 copy_u8Clk);
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
void MRCC_SetClkSourceStatus(u8 copy_u32ClkSource, u8 copy_u8Status);
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
void MRCC_SetCLKBussesPrescaller(u16 AHP_u16_prescaller, u8 APB1_u8_prescaller, u8 APB2_u8_prescaller);
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
void MRCC_SetPLLConfiguration(u8 PLL_u8_Source, u8 PLL_u8_MulFactor);
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
void MRCC_SetPeripheralConfiguration(u8 Peripheral_Name, u8 Peripheral_Bus,u8 Peripheral_Status);
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
void MRCC_Init(void);



#endif
