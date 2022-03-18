/*
 * SYSTICK_configuration.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohy
 */

#ifndef SYSTICK_CONFIGURATION_H_
#define SYSTICK_CONFIGURATION_H_

#define SYSTICK_IMMEDIATE_LOAD_CONFIG		SYSTICK_IMMEDIATE_LOAD
#define SYSTICK_INTERRUPT_CONFIG			SYSTICK_INTERRUPT_ENABLE
#define SYSTICK_CLK_CONFIG					SYSTICK_CLK_AHB_DIV_8

/*this configuration must be rightly calculated, its used by the MSYSTICK_voidDelay_ms function*/
#define SYSTICK_CLK_FREQUENCY				(1000000UL)

#endif /* SYSTICK_CONFIGURATION_H_ */
