/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/

#include "TYPES.h"

#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "USART_INTERFACE.h"
#include "NVIC_INTERFACE.h"

#include "ESP8266_INTERFACE.h"


int main ( void ){

	/* Create Variable To Receive Data From Server */
	u8 LOC_u8Data = 0;

	/* Initialize RCC to work with 8MHz */
	MRCC_VidInit();

	/* Enable USART 1 */
	MRCC_VidEnablePeripheralClock( APB2_BUS , USART1_RCC );

	/* Enable GPIOA */
	MRCC_VidEnablePeripheralClock( APB2_BUS , GPIOA_RCC  );

	/* Configure A9  (Tx1) as Output AFPP @ 2MHz */
	MGPIO_VidSetPinDirection  ( GPIOA , PIN9 , OUTPUT_SPEED_2MHZ_AFPP ) ;

	/* Configure A10 (RX1) as input Floating     */
	MGPIO_VidSetPinDirection  ( GPIOA , PIN10 , INPUT_FLOATING        ) ;

	/* Configure A0  (A0) as Output PP @ 2MHz */
	MGPIO_VidSetPinDirection  ( GPIOA , PIN0 , OUTPUT_SPEED_2MHZ_PP   ) ;

	/* Enable NVIC For USART1 */
	MNVIC_VidSetPriority      ( USART1 , 1 , NO_SUB_PRIORITY , GROUP3 ) ;
	MNVIC_VidEnablePeripheral ( USART1                                ) ;

	/* Initialize UART */
	MUSART_VidInit();

	/* Setting ESP8266 Mode */
	ESP8266_VidInit();

	/* Connecting To WIFI Network */
	ESP8266_VidConnectToWiFi( (u8 *)"The flower" , (u8 *)"nona909090" );

	while(1){

		/* Connecting To yrabiot3.freevar.com */
		ESP8266_VidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

		/* Connecting To yrabiot3.freevar.com */
		LOC_u8Data = ESP8266_u8ReceiveHttpReq( (u8 *)"yrabiot3.freevar.com" , (u8 *)"50" );

		/* We Receive ASCII So We Will Subtract 48 From Data Come */
		MGPIO_VidSetPinValue( GPIOA , PIN0 , LOC_u8Data - 48 );

	}

	return 0;

}
