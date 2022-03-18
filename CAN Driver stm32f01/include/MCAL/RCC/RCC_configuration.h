#ifndef RCC_CONFIGURATION_H
#define RCC_CONFIGURATION_H


#define AHB_BUS_PRESCALLER		RCC_AHB_PRESCALLER1
#define APB1_BUS_PRESCALLER		RCC_APB_PRESCALLER1
#define APB2_BUS_PRESCALLER		RCC_APB_PRESCALLER1





/*configure which clock source is used for the system*/
#define RCC_SYS_CLK_SRC						RCC_SYS_CLK_HSI
/*configure the multiplication factor for the PLL*/
#define RCC_SYS_CLK_PLL_MUL_FACTOR			PLL_MUL_5

#define RCC_PLL_SRC_HSE_MODE				RCC_PLL_SRC_HSE_DIV2

/*configure if PLL HSE is used, */

#endif
