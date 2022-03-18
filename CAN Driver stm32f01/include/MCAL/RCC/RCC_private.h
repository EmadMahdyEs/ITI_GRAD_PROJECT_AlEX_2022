#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*base address for RCC registers*/
#define RCC_REGS_BASE_ADDRESS 					0x40021000
/*addresses of all registers for RCC*/
#define RCC_U32_CR_REG							(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x00)) )
#define RCC_U32_CFGR_REG						(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x04)) )
#define RCC_U32_CIR_REG							(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x08)) )
#define RCC_U32_APB2RSTR_REG					(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x0C)) )
#define RCC_U32_APB1RSTR_REG					(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x10)) )
#define RCC_U32_AHBENR_REG						(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x14)) )
#define RCC_U32_APB2ENR_REG						(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x18)) )
#define RCC_U32_APB1ENR_REG						(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x1C)) )
#define RCC_U32_BDCR_REG						(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x20)) )
#define RCC_U32_CSR_REG							(*((volatile u32*) (RCC_REGS_BASE_ADDRESS+0x24)) )

/*bits for PLL*/
#define RCC_PLL_SRC_BIT						16
#define RCC_PLL_XTPRE_BIT					17
#define RCC_PLL_MUL_BIT						18


#define RCC_APB_PRESCALLER1				1
#define RCC_APB_PRESCALLER2				2
#define RCC_APB_PRESCALLER4				4
#define RCC_APB_PRESCALLER8				8
#define RCC_APB_PRESCALLER16			16

#define RCC_AHB_PRESCALLER1				1
#define RCC_AHB_PRESCALLER2				2
#define RCC_AHB_PRESCALLER4				4
#define RCC_AHB_PRESCALLER8				8
#define RCC_AHB_PRESCALLER16			16
#define RCC_AHB_PRESCALLER64			64
#define RCC_AHB_PRESCALLER128			128
#define RCC_AHB_PRESCALLER256			256
#define RCC_AHB_PRESCALLER512			512

/*used in RCC_cofiuration to configure the PLl source if PLL is used*/
#define RCC_PLL_SRC_HSI						0
#define RCC_PLL_SRC_HSE						1
#define RCC_PLL_SRC_HSE_DIV2				2
/*used in RCC_cofiuration to configure the system clock source*/
#define RCC_SYS_CLK_HSI				0
#define RCC_SYS_CLK_HSE				1
#define RCC_SYS_CLK_PLL_HSI			2
#define RCC_SYS_CLK_PLL_HSE			3

/*used for the configuration of the multiplication factor of the PLL*/
enum RCC_PLL_MUL_FACTOR
{
	PLL_MUL_2,PLL_MUL_3,PLL_MUL_4,PLL_MUL_5,PLL_MUL_6,PLL_MUL_7,PLL_MUL_8,PLL_MUL_9,PLL_MUL_10,PLL_MUL_11,PLL_MUL_12,
	PLL_MUL_13,PLL_MUL_14,PLL_MUL_15,PLL_MUL_16
};


#endif
