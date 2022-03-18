/*
 * CAN_private.h
 *
 *  Created on: Mar 15, 2022
 *      Author: Mohy
 */

#ifndef CAN_PRIVATE_H_
#define CAN_PRIVATE_H_

typedef struct
{
	volatile u32 FR[2];

}Filters_Struct;

#define CAN_REG 		( (volatile CanRegx*)0x40006400 )
typedef struct
{
	volatile u32 MCR;
	volatile u32 MSR;
	volatile u32 TSR;
	volatile u32 RF0R;
	volatile u32 RF1R;
	volatile u32 IER;
	volatile u32 ESR;
	volatile u32 BTR;

	volatile u32 RESERVED0[88];

	volatile u32 TI0R;
	volatile u32 TDT0R;
	volatile u32 TDL0R;
	volatile u32 TDH0R;

	volatile u32 TI1R;
	volatile u32 TDT1R;
	volatile u32 TDL1R;
	volatile u32 TDH1R;

	volatile u32 TI2R;
	volatile u32 TDT2R;
	volatile u32 TDL2R;
	volatile u32 TDH2R;

	volatile u32 RI0R;
	volatile u32 RDT0R;
	volatile u32 RDL0R;
	volatile u32 RDH0R;

	volatile u32 RI1R;
	volatile u32 RDT1R;
	volatile u32 RDL1R;
	volatile u32 RDH1R;

	volatile u32 RESERVED1[12];

	volatile u32 FMR;
	volatile u32 FM1R;

	volatile u32 RESERVED2;

	volatile u32 FS1R;

	volatile u32 RESERVED3;

	volatile u32 FFA1R;

	volatile u32 RESERVED4;

	volatile u32 FA1R;

	volatile u32 RESERVED5[8];

	volatile Filters_Struct* Filters[14];

}CanRegx;





/***********************************************CAN_MCR register bits*****************************************************/
#define CAN_DEBUG_FREEZE_BIT				16
#define CAN_AUTO_BUS_OFF_BIT				6
#define CAN_AUTO_WAKEUP_BIT					5
#define CAN_NO_AUTO_RETRANSMIT_BIT			4
#define CAN_OVER_RUN_MANAGEMENT_BIT			3
#define CAN_PRIORITY_TRANSMISSION_BIT		2
#define CAN_SLEEP_BIT						1
#define CAN_INIT_BIT						0
/**************************************************************************************************************************/

/********************************************CAN_MCR register options***************************************************/

#define CAN_AUTO_BUS_OFF				1
#define CAN_NO_AUTO_BUS_OFF				0

#define CAN_AUTO_WAKEUP					1
#define CAN_NO_AUTO_WAKEUP				0

#define CAN_AUTO_RETRANSMISSION			0
#define CAN_NO_AUTO_RETRANSMISSION		1

#define CAN_OVRUN_OVERWRITE				0
#define CAN_OVRUN_DISCARD				1

#define CAN_ID_PRIORITY					0
#define CAN_RQ_PRIORITY					1
/****************************************************************************************************************************/

/***********************************************CAN_MSR register bits*****************************************************/
#define CAN_ERROR_INT_BIT				6
#define CAN_SLEEP_ACK_BIT				5
#define CAN_INIT_ACK_BIT				4
/**************************************************************************************************************************/

/***********************************************CAN_MSR register options*****************************************************/
#define CAN_INIT_MODE_ACK				1
#define CAN_SLEEP_MODE_ACK				1
/**************************************************************************************************************************/


/***********************************************CAN_BTR register bits*****************************************************/
#define CAN_SILENT_MODE_BIT					31
#define CAN_LOOP_BACK_MODE_BIT				30
/**************************************************************************************************************************/

/***********************************************CAN_BTR register options*****************************************************/
#define CAN_SILENT_ENABLE					1
#define CAN_SILENT_DISABLE					0

#define CAN_LOOP_BACK_ENABLE					1
#define CAN_LOOP_BACK_DISABLE					0
/**************************************************************************************************************************/


/***********************************************CAN_TIxR register bits*****************************************************/
#define CAN_STANDARD_ID_BIT			21
#define CAN_EXTENDED_ID_BIT			3
#define CAN_IDE_BIT					2
#define CAN_RTR_BIT					1
#define CAN_TRANSMIT_RQ_BIT			0
/**************************************************************************************************************************/

/***********************************************CAN_TIxR register options*****************************************************/
#define CAN_STANDARD_ID_MASK				0x7ff
#define CAN_EXTENDED_ID_MASK				0xffff800

#define CAN_RTR_DATA_FRAME			0
#define CAN_RTR_REMOTE_FRAME		1
/**************************************************************************************************************************/


/***********************************************CAN_TDTxR register bits*****************************************************/
#define CAN_DLC_BIT					0
/**************************************************************************************************************************/

/***********************************************CAN_TDTxR register options*****************************************************/
#define CAN_DLC_MASK				0x0f
/**************************************************************************************************************************/

/***********************************************CAN_TSR register bits*****************************************************/
#define CAN_TX_EMPTY_CODE_BIT				24
/**************************************************************************************************************************/

/***********************************************CAN_FMR register bits*****************************************************/
#define CAN_FINIT_BIT				0
/**************************************************************************************************************************/

/***********************************************CAN_FMR register options*****************************************************/
#define CAN_INIT_MODE_FOR_FILTERS				1
#define CAN_ACTIVE_MODE_FOR_FILTERS				0
/**************************************************************************************************************************/

/***********************************************CAN_FM1R register options*****************************************************/
#define CAN_IDENTIFIER_MASK_MODE_FOR_FILTERS				0
#define CAN_IDENTIFIER_LIST_MODE_FOR_FILTERS				1
/**************************************************************************************************************************/


/***********************************************CAN_FS1R register options*****************************************************/
#define CAN_32_BIT_SCALE_FOR_FILTERS				1
#define CAN_16_BIT_SCALE_FOR_FILTERS				0
/**************************************************************************************************************************/

/***********************************************CAN_IER register bits*****************************************************/
#define CAN_FIFO_0_MESSAGE_PENDING_BIT				1
/**************************************************************************************************************************/
/***********************************************CAN_IER register options*****************************************************/
#define CAN_FIFO_0_MESSAGE_PENDING_INT_ENABLE				1
#define CAN_FIFO_0_MESSAGE_PENDING_INT_DISABLE				0
/**************************************************************************************************************************/

/***********************************************CAN_RF0R register bits*****************************************************/
#define CAN_RELEASE_FIFO_0_RQ_BIT				5
/**************************************************************************************************************************/
/***********************************************CAN_RF0R register options*****************************************************/
#define CAN_RELEASE_FIFO_0_RQ				1
/**************************************************************************************************************************/


#endif /* CAN_PRIVATE_H_ */
