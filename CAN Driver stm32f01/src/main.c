#include "../include/LIB/std_types.h"
#include "../include/LIB/bit_math.h"

#include "../../include/MCAL/RCC/RCC_interface.h"
#include "../../include/MCAL/NVIC/NVIC_interface.h"
#include "../../include/MCAL/SCB/SCB_interface.h"
#include "../../include/MCAl/GPIO/GPIO_interface.h"
#include "../../include/MCAL/SYSTICK/SYSTICK_interface.h"
#include "../../include/MCAl/CAN/CAN_interface.h"


void Toggle_Led(void)
{
	static u8 Value=0;
	Value^=1;
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,Value);
}

//global variable used by CAN_FIFO_0_CallBackFunction
u8 Received_Data_Length=0;
u8 Received_Data[8]={0};

void CAN_FIFO_0_CallBackFunction(void)
{
	Received_Data_Length=CAN_u8ReceiveData(Received_Data);

	if(Received_Data[0]==10 && Received_Data[1]==20)
	{
		Toggle_Led();
	}
}


void main(void)
{
	/*HSI_CLK=8MHZ , all busses prescaller=1*/
	MRCC_Init();
	/*enable clock for GPIOA*/
	MRCC_SetPeripheralConfiguration(RCC_PERIPHERAL_IOPA,RCC_PERIPHERAL_APB2_BUS,RCC_PERIPHERAL_ENABLE);
	/*enable clock for CAN1*/
	MRCC_SetPeripheralConfiguration(RCC_PERIPHERAL_CAN,RCC_PERIPHERAL_APB1_BUS,RCC_PERIPHERAL_ENABLE);
	/*adjust system group priority with the pre-configured value.. GP_PRI=16 , SUB_PRI=0*/
	MSCB_voidSetSystemGroupPriority();
	/*set priority for systick timer ID=SCB_VECT_SYSTICK_ID , GP_PRI=1 , SUB_PRI=neglected*/
	MNVIC_voidSetIntPriority(SCB_VECT_SYSTICK_ID,1,1);
	/*enable interrupt for CAN-RX1*/
	MNVIC_voidEnablePeripheral(21);
	/*set priority for CAN ID=21 , GP_PRI=2 , SUB_PRI=neglected*/
	MNVIC_voidSetIntPriority(21,2,1);
	/*initialize SYSTICK*/
	MSYSTICK_voidInit();
	/*PA0 output -> LED*/
	MGPIO_voidSetDirection(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUT_10M_SPEED_MODE,GPIO_OUTPUT_PUSH_PULL);
	/*PA12 output -> TX*/
	MGPIO_voidSetDirection(GPIO_PORTA,GPIO_PIN12,GPIO_OUTPUT_10M_SPEED_MODE,GPIO_AF_OUTPUT_PUSH_PULL);
	/*PA11 input -> RX*/
	MGPIO_voidSetDirection(GPIO_PORTA,GPIO_PIN11,GPIO_INPUT_MODE,GPIO_FLOATING_INPUT);
	/*PB9 output -> TX*/
	MGPIO_voidSetDirection(GPIO_PORTB,GPIO_PIN9,GPIO_OUTPUT_10M_SPEED_MODE,GPIO_AF_OUTPUT_PUSH_PULL);
	/*PB8 input -> RX*/
	MGPIO_voidSetDirection(GPIO_PORTB,GPIO_PIN8,GPIO_INPUT_MODE,GPIO_FLOATING_INPUT);

	//set call back function for fifo-0 message pending interrupt
	CAN_voidSetCallBack(CAN_FIFO_0_CallBackFunction);
	//initialize can
	CAN_voidInit();

	//data to be sent by CAN
	u8 Data[2]={10,20};

	while (1)
	{
		CAN_voidTransmitDataFrame(0,Data,2,0);
		MSYSTICK_voidSetBusyWait(1000000);
		Received_Data_Length=CAN_u8ReceiveData(Received_Data);
		if(Received_Data[0]==10 && Received_Data[1]==20)
		{
			Toggle_Led();
		}

	}
}
