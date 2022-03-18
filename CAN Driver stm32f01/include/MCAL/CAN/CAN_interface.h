/*
 * CAN_interface.h
 *
 *  Created on: Mar 15, 2022
 *      Author: Mohy
 */

#ifndef CAN_INTERFACE_H_
#define CAN_INTERFACE_H_



#define CAN_IDE_STANDARD_FRAME		0
#define CAN_IDE_EXTENDED_FRAME		1






void CAN_voidInit(void);

void CAN_voidTransmitRemoteFrame(u32 copy_u32MessageID,u8 copy_u8IDE);

void CAN_voidTransmitDataFrame(u32 copy_u32MessageID,u8 *copy_u8DataBytes,u8 copy_u8DataLength,u8 copy_u8IDE);


u8 CAN_u8ReceiveData(u8* Pass_u8Data);

void CAN_voidSetCallBack(void(*ptr)(void) );

#endif /* CAN_INTERFACE_H_ */
