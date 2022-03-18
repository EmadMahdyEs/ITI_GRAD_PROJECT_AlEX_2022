/*
 * CAN_program.c
 *
 *  Created on: Mar 15, 2022
 *      Author: Mohy
 */
#include "../../include/LIB/std_types.h"
#include "../../include/LIB/bit_math.h"

#include "../../include/MCAL/CAN/CAN_private.h"
#include "../../include/MCAL/CAN/CAN_configuration.h"
#include "../../include/MCAL/CAN/CAN_interface.h"


void CAN_voidInit(void)
{
	//set CAN to work while debugging
	CAN_REG->MCR &=~(1<<CAN_DEBUG_FREEZE_BIT);
	//exit sleep mode and enter initialization mode
	CAN_REG->MCR &=~(1<<CAN_SLEEP_BIT);
	CAN_REG->MCR |=(1<<CAN_INIT_BIT);
	//check if initialization mode is entered
	while( (GET_BIT(CAN_REG->MSR,CAN_SLEEP_ACK_BIT)==1) && (GET_BIT(CAN_REG->MSR,CAN_INIT_ACK_BIT)==0) );

	//configuring the CAN peripheral
	CAN_REG->MCR |=(CAN_AUTO_BUS_OFF_CFG<<CAN_AUTO_BUS_OFF_BIT) | (CAN_AUTO_WAKEUP_CFG<<CAN_AUTO_WAKEUP_BIT) |
					(CAN_AUTO_RETRANSMISSION_CFG<<CAN_NO_AUTO_RETRANSMIT_BIT) | (CAN_OVER_RUN_BEHAVIOR_CFG<<CAN_OVER_RUN_MANAGEMENT_BIT)|
					(CAN_TRANSMIT_PRIORITY_CFG<<CAN_PRIORITY_TRANSMISSION_BIT);

	//enable interrupt for new message arrival in FIFO 0 mail box
	CAN_REG->IER |=(CAN_FIFO_0_MESSAGE_PENDING_INT_ENABLE<<CAN_FIFO_0_MESSAGE_PENDING_BIT);

	//baud rate prescaler in BTR register
	CAN_REG-> BTR=0x001c0001;

	//enter init mode for filters
	CAN_REG->FMR |=(CAN_INIT_MODE_FOR_FILTERS<<CAN_FINIT_BIT);
	//set filter mode to identifier mask mode
	CAN_REG->FM1R |=(CAN_IDENTIFIER_MASK_MODE_FOR_FILTERS<<0);
	//set filter scale to 32 bit register
	CAN_REG->FS1R |=(CAN_32_BIT_SCALE_FOR_FILTERS<<0);
	//activate the filter
	CAN_REG->FA1R |=(1<<0);
	//quit the filters init mode
	CAN_REG->FMR &=~(1<<CAN_FINIT_BIT);

	//quit the init mode and enter the normal mode for CAN, quit the init mode and enter the active mode for filters
	CLEAR_BIT(CAN_REG->MCR,0);
	CLEAR_BIT(CAN_REG->MCR,1);
	//ensuring that the normal mode has been entered
	while(GET_BIT(CAN_REG->MSR , CAN_INIT_ACK_BIT)==1);
	//silent mode combined with loop back mode
	CAN_REG->BTR |=(CAN_SILENT_ENABLE<<CAN_SILENT_MODE_BIT) | (CAN_LOOP_BACK_ENABLE<<CAN_LOOP_BACK_MODE_BIT);
}

void CAN_voidTransmitRemoteFrame(u32 copy_u32MessageID,u8 copy_u8IDE)
{
	u16 local_u16StandardId=0;
	u16 local_u16ExtendedId=0;
	/*separate the extended ID and the standard ID*/
	switch(copy_u8IDE)
	{
	case CAN_IDE_STANDARD_FRAME:
		local_u16StandardId = copy_u32MessageID & CAN_STANDARD_ID_MASK;
		local_u16ExtendedId = 0;
		break;
	case CAN_IDE_EXTENDED_FRAME:
		local_u16StandardId = copy_u32MessageID & CAN_STANDARD_ID_MASK;
		local_u16ExtendedId = copy_u32MessageID & CAN_EXTENDED_ID_MASK;
		break;
	}
	/*check if the transmission mailbox 0 is empty to use*/
	if( ((CAN_REG->TSR)&0x03000000)==0 )
	{
		CAN_REG->TI0R = (local_u16StandardId<<CAN_STANDARD_ID_BIT) | (local_u16ExtendedId<<CAN_EXTENDED_ID_BIT)|
						(copy_u8IDE<<CAN_IDE_BIT) | (CAN_RTR_REMOTE_FRAME<<CAN_RTR_BIT);
		//DLC is zero and disable time stamp
		CAN_REG->TDT0R &=~ (CAN_DLC_MASK<<CAN_DLC_BIT) | (1<<8);

		//generate transmit request
		CAN_REG->TI0R |=(1<<CAN_TRANSMIT_RQ_BIT);
	}
	/*check if the transmission mailbox 1 is empty to use*/
	else if( ((CAN_REG->TSR)&0x03000000)==1)
	{
		CAN_REG->TI1R = (local_u16StandardId<<CAN_STANDARD_ID_BIT) | (local_u16ExtendedId<<CAN_EXTENDED_ID_BIT)|
						(copy_u8IDE<<CAN_IDE_BIT) | (CAN_RTR_REMOTE_FRAME<<CAN_RTR_BIT);
		//DLC is zero and disable time stamp
		CAN_REG->TDT1R &=~ (CAN_DLC_MASK<<CAN_DLC_BIT) | (1<<8);

		//generate transmit request
		CAN_REG->TI1R |=(1<<CAN_TRANSMIT_RQ_BIT);
	}
	/*check if the transmission mailbox 2 is empty to use*/
	else if( ((CAN_REG->TSR)&0x03000000)==2)
	{
		CAN_REG->TI2R = (local_u16StandardId<<CAN_STANDARD_ID_BIT) | (local_u16ExtendedId<<CAN_EXTENDED_ID_BIT)|
						(copy_u8IDE<<CAN_IDE_BIT) | (CAN_RTR_REMOTE_FRAME<<CAN_RTR_BIT);
		//DLC is zero and disable time stamp
		CAN_REG->TDT2R &=~ (CAN_DLC_MASK<<CAN_DLC_BIT) | (1<<8);

		//generate transmit request
		CAN_REG->TI2R |=(1<<CAN_TRANSMIT_RQ_BIT);
	}

}



void CAN_voidTransmitDataFrame(u32 copy_u32MessageID,u8 *copy_u8DataBytes,u8 copy_u8DataLength,u8 copy_u8IDE)
{
	u16 local_u16StandardId=0;
	u16 local_u16ExtendedId=0;
	/*separate the extended ID and the standard ID*/
	switch(copy_u8IDE)
	{
	case CAN_IDE_STANDARD_FRAME:
		local_u16StandardId = copy_u32MessageID & CAN_STANDARD_ID_MASK;
		local_u16ExtendedId = 0;
		break;
	case CAN_IDE_EXTENDED_FRAME:
		local_u16StandardId = copy_u32MessageID & CAN_STANDARD_ID_MASK;
		local_u16ExtendedId = copy_u32MessageID & CAN_EXTENDED_ID_MASK;
		break;
	}

	/*check if the transmission mailbox 0 is empty to use*/
	if( ((CAN_REG->TSR)&0x03000000)== 0 )
	{
		//set the ID, IDE and RTR
		CAN_REG->TI0R = (local_u16StandardId<<CAN_STANDARD_ID_BIT) | (local_u16ExtendedId<<CAN_EXTENDED_ID_BIT)|
						(copy_u8IDE<<CAN_IDE_BIT) | (CAN_RTR_DATA_FRAME<<CAN_RTR_BIT);
		//disable time stamp
		CAN_REG->TDT0R &=~ (1<<8);

		//check if the number of bytes is equal or less than 4 bytes
		if(copy_u8DataLength<=4)
		{
			//set DLC bits
			CAN_REG->TDT0R |= ( copy_u8DataLength << CAN_DLC_BIT );
			//put the data to be sent
			for(u8 i=0;i<copy_u8DataLength;i++)
			{
				CAN_REG->TDL0R |=( (copy_u8DataBytes[i])<< (i*8) );
			}
		}
		//check if the number of bytes is equal or less than 8 bytes
		else if(copy_u8DataLength>=5 && copy_u8DataLength<=8)
		{
			//set DLC bits
			CAN_REG->TDT0R |= ( copy_u8DataLength << CAN_DLC_BIT );
			//put the data to be sent
			for(u8 i=0;i<4;i++)
			{
				CAN_REG->TDL0R |=( (copy_u8DataBytes[i])<< (i*8) );
			}
			for(u8 i=4;i<copy_u8DataLength;i++)
			{
				CAN_REG->TDH0R |=( (copy_u8DataBytes[i])<< ( (i-4) *8) );
			}
		}
		else
		{
			//don't continue to generate an interrupt request if the data length sent exceeds 8 bytes
			return;
		}
		//generate transmit request
		CAN_REG->TI0R |=(1<<CAN_TRANSMIT_RQ_BIT);
	}
	/*check if the transmission mailbox 1 is empty to use*/
	else if( ((CAN_REG->TSR)&0x03000000)== 1)
	{
		//set the ID, IDE and RTR
		CAN_REG->TI1R = (local_u16StandardId<<CAN_STANDARD_ID_BIT) | (local_u16ExtendedId<<CAN_EXTENDED_ID_BIT)|
						(copy_u8IDE<<CAN_IDE_BIT) | (CAN_RTR_DATA_FRAME<<CAN_RTR_BIT);
		//disable time stamp
		CAN_REG->TDT1R &=~ (1<<8);

		//check if the number of bytes is equal or less than 4 bytes
		if(copy_u8DataLength<=4)
		{
			//set DLC bits
			CAN_REG->TDT1R |= ( copy_u8DataLength << CAN_DLC_BIT );
			//put the data to be sent
			for(u8 i=0;i<4;i++)
			{
				CAN_REG->TDL1R |=( (copy_u8DataBytes[i])<< (i*8) );
			}
		}
		//check if the number of bytes is equal or less than 8 bytes
		else if(copy_u8DataLength>=5 && copy_u8DataLength<=8)
		{
			//set DLC bits
			CAN_REG->TDT1R |= ( copy_u8DataLength << CAN_DLC_BIT );
			//put the data to be sent
			for(u8 i=0;i<4;i++)
			{
				CAN_REG->TDL1R |=( (copy_u8DataBytes[i])<< (i*8) );
			}
			for(u8 i=4;i<8;i++)
			{
				CAN_REG->TDH1R |=( (copy_u8DataBytes[i])<< ( (i-4) *8) );
			}
		}
		else
		{
			//don't continue to generate an interrupt request if the data length sent exceeds 8 bytes
			return;
		}
		//generate transmit request
		CAN_REG->TI1R |=(1<<CAN_TRANSMIT_RQ_BIT);
	}
	/*check if the transmission mailbox 2 is empty to use*/
	else if( ((CAN_REG->TSR)&0x03000000)== 2)
	{
		//set the ID, IDE and RTR
		CAN_REG->TI2R = (local_u16StandardId<<CAN_STANDARD_ID_BIT) | (local_u16ExtendedId<<CAN_EXTENDED_ID_BIT)|
						(copy_u8IDE<<CAN_IDE_BIT) | (CAN_RTR_DATA_FRAME<<CAN_RTR_BIT);
		//disable time stamp
		CAN_REG->TDT2R &=~ (1<<8);

		//check if the number of bytes is equal or less than 4 bytes
		if(copy_u8DataLength<=4)
		{
			//set DLC bits
			CAN_REG->TDT2R |= ( copy_u8DataLength << CAN_DLC_BIT );
			//put the data to be sent
			for(u8 i=0;i<4;i++)
			{
				CAN_REG->TDL2R |=( (copy_u8DataBytes[i])<< (i*8) );
			}
		}
		//check if the number of bytes is equal or less than 8 bytes
		else if(copy_u8DataLength>=5 && copy_u8DataLength<=8)
		{
			//set DLC bits
			CAN_REG->TDT2R |= ( copy_u8DataLength << CAN_DLC_BIT );
			//put the data to be sent
			for(u8 i=0;i<4;i++)
			{
				CAN_REG->TDL2R |=( (copy_u8DataBytes[i])<< (i*8) );
			}
			for(u8 i=4;i<8;i++)
			{
				CAN_REG->TDH2R |=( (copy_u8DataBytes[i])<< ( (i-4) *8) );
			}
		}
		else
		{
			//don't continue to generate an interrupt request if the data length sent exceeds 8 bytes
			return;
		}
		//generate transmit request
		CAN_REG->TI2R |=(1<<CAN_TRANSMIT_RQ_BIT);
	}
}

/*
void CAN_voidAddMessageId(u32 copy_u32MessageId, u8 copy)
{
	u8 local_u8ReadyFilterNumber=0;
	//I'm always setting the scale to two-32 bit registers so if the value is 0 means I didn't used it yet
	while(GET_BIT(CAN_REG->FS1R,local_u8ReadyFilterNumber)==0 && local_u8ReadyFilterNumber<14)
	{
		local_u8ReadyFilterNumber++;
	}
	//Init mode for filters
	CAN_REG->FMR |=(CAN_INIT_MODE_FOR_FILTERS<<CAN_FINIT_BIT);
	//set filter mode to identifier list mode
	CAN_REG->FM1R |=(CAN_IDENTIFIER_LIST_MODE_FOR_FILTERS<<local_u8ReadyFilterNumber);
	//set filter scale to 32 bit register
	CAN_REG->FS1R |=(CAN_32_BIT_SCALE_FOR_FILTERS<<local_u8ReadyFilterNumber);
	//set message ID
	CAN_REG->Filters[local_u8ReadyFilterNumber]->FR[0] |= (copy_u32MessageId&0x);

}
*/



u8 CAN_u8ReceiveData(u8* Pass_u8Data)
{
	u8 Local_u8DataLength=0;
	//check the length of the data
	Local_u8DataLength= (CAN_REG->RDT0R)& 0x0000000f;
	//reading the data received
	if(Local_u8DataLength<=4)
	{
		for(u8 counter=0;counter<Local_u8DataLength;counter++)
		{
			Pass_u8Data[counter]= ( (CAN_REG->RDL0R)<<(counter*8));
		}
	}
	else
	{
		for(u8 counter=0;counter<4;counter++)
		{
			Pass_u8Data[counter]= (CAN_REG->RDL0R<<(counter*8));
		}
		for(u8 counter=4;counter<Local_u8DataLength;counter++)
		{
			Pass_u8Data[counter]= (CAN_REG->RDH0R<<( (counter-4)*8 ));
		}
	}

	//release the FIFO 0 mail box
	CAN_REG->RF0R |=(CAN_RELEASE_FIFO_0_RQ<<CAN_RELEASE_FIFO_0_RQ_BIT);

	return Local_u8DataLength;
}



void (*CAN_PTR2func)(void);

void CAN_voidSetCallBack(void(*ptr)(void) )
{
	CAN_PTR2func = ptr;
}

void CAN1_RX1_IRQHandler(void)
{
	CAN_PTR2func();
}

void CAN1_RX0_IRQHandler(void)
{
	CAN_PTR2func();
}





