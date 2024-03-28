/*>>>>>>>>>>>>>>>>>>>>>>>>>>> TWI_intrface.h <<<<<<<<<<<<<<<<<<<<<<*/

/*
** Layer : MCAL 
** Author : Abdelhady Elshahat 
** version : 1.0
**
*/


#ifndef TWI_INTERFACE_H_ 
#define TWI_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
/* declaring enum for errors checking */
typedef enum 
{
	
	NoError,
	StartConditionErr,
	RepeatedStartError,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
	SlaveWriteByteErr,
	SlaveReadByteErr,
	
}TWI_enuErrorsState ;





/* API's*/

void TWI_voidMasterInit(void);

void TWI_u8SlaveInit(u8 Copy_u8Adress);

TWI_enuErrorsState TWI_u8MasterStartCond (void);

TWI_enuErrorsState TWI_u8MasterSendSlaveAdressWrite (u8 Copy_u8Adress);

TWI_enuErrorsState TWI_u8MasterSendSlaveAdressRead (u8 Copy_u8Adress);

TWI_enuErrorsState TWI_u8MasterSendData (u8 Copy_u8Data);

TWI_enuErrorsState TWI_u8MasterRecData (u8 *Copy_pu8Data);

TWI_enuErrorsState TWI_u8MasterRepetedStartCond (void);

void TWI_u8MasterStopCond (void);

TWI_enuErrorsState TWI_u8SlaveSendData (u8 Copy_u8Data);

TWI_enuErrorsState TWI_u8SlaveRecData (u8 *Copy_Pu8Data);

/* For the RTC  */
u8 TWI_u8MasterRecDataVersion2 (void);

u8 TWI_u8MasterRecDataNotAck (void);
#endif 
