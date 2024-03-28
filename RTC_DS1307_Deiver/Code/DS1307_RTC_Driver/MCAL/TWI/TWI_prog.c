/*>>>>>>>>>>>>>>>>>>>>>>>>>>> TWI_prog.c <<<<<<<<<<<<<<<<<<<<<<*/

/*
** Layer : MCAL 
** Author : Abdelhady Elshahat 
** version : 1.0
**
*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "TWI_interface.h"
#include "TWI_privite.h"
#include "TWI_config.h"


void TWI_voidMasterInit(void)
{
	/* 1- calculate TWBR (bit rate calculation)*/
	/* 2- Enable the ACK */
	/* 3- Enable the TWI peripheral */
	
	/* Assign the PRE-scaler with 0*/
	#if TWI_PRESCALLER == PRESCALLER_BY_1
		CLR_BIT(TWI_TWSR_REG,TWPS1);
		CLR_BIT(TWI_TWSR_REG,TWPS0);
	#elif TWI_PRESCALLER == PRESCALLER_BY_4 
		CLR_BIT(TWI_TWSR_REG,TWPS1);
	    SET_BIT(TWI_TWSR_REG,TWPS0);
	#elif TWI_PRESCALLER == PRESCALLER_BY_16 
		SET_BIT(TWI_TWSR_REG,TWPS1);
	    CLR_BIT(TWI_TWSR_REG,TWPS0);
	#elif TWI_PRESCALLER == PRESCALLER_BY_4 
		SET_BIT(TWI_TWSR_REG,TWPS1);
	    SET_BIT(TWI_TWSR_REG,TWPS0);
	#endif 		
	
	/* Assign the value of bit rate */
	//TWI_TWBR_REG = (u8) (((F_CPU/TWI_SCL_BIT_RATE)-16) / (2*TWI_PRESCALLER));
	/* for 100K bit rate TWI_TWBR_REG  = 32 for 400 K WI_TWBR_REG  = 2 */
	TWI_TWBR_REG = 2 ;
	
	
	/* Enable ACK*/
	SET_BIT(TWI_TWCR_REG,TWEA);
	
	/* Enable TWI */
	SET_BIT(TWI_TWCR_REG,TWEN);
	
}

void TWI_u8SlaveInit(u8 Copy_u8Adress)
{

	/* 1- Set the address of the slave */
	/* 2- Enable the ACK */
	/* 3- Enable the TWI peripheral */
	
	if ( (Copy_u8Adress > 0) &&  (Copy_u8Adress < 127) )
	{
		/* set the address if the MCU is a slave in the system*/
		/* the slave address loaded at the 7 MSB of TWAR REG */
		/* Make sure that the address not start with 1111xxx*/
		TWI_TWAR_REG = (Copy_u8Adress << 1); /* shifted one to loaded at the 7 MSB */
		
		/* Enable ACK*/
	 	SET_BIT(TWI_TWCR_REG,TWEA);
		
		/* Enable TWI */
		SET_BIT(TWI_TWCR_REG,TWEN);
		

	
	}
	
	
}



TWI_enuErrorsState TWI_u8MasterStartCond (void)
{
	TWI_enuErrorsState Local_enuErrorState = StartConditionErr ;
	
	/* 1- initiate the Start condition */
	/* 2- wait till the flag set  */
	/* 3- check the TWSR ACK Code for start condition*/
	/* 4- Clear the TWSTA bit */
	
	
	/* initiate the Start condition */
	SET_BIT(TWI_TWCR_REG,TWSTA);
	
	/*clear the flag to previous operation*/
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_START_COND_SENT)
	{
		Local_enuErrorState = NoError ;
		
//		/* Clear the TWSTA bit */
//		CLR_BIT(TWI_TWCR_REG,TWSTA);
		
		return Local_enuErrorState ;
	}
	
	
	return Local_enuErrorState ;
	
}



TWI_enuErrorsState TWI_u8MasterSendSlaveAdressWrite (u8 Copy_u8Adress)

{
	TWI_enuErrorsState Local_enuErrorState = SlaveAddressWithWriteErr ;
	
	/* 1- load the address of the slave */
	/* 2- clear the flag to end the address*/
	/* 3- wait until the flag rise */
	/* 4- check the ACK code of the operation */
	
	/*load the address of the slave */
	TWI_TWDR_REG = (Copy_u8Adress << 1);
	
	/* Write operation loaded
	** TWDR used for data loaded and (slave address loaded in the 7 MSB)
	** LSB in slave agree loaded used to control the operation send to slave
	** LSB = 0 for write operation (Dominant bit) , LSB = 1 for read operation
	*/

	CLR_BIT(TWI_TWDR_REG,TWD0);
	
	/* Clear the TWSTA bit */
	CLR_BIT(TWI_TWCR_REG,TWSTA);

	/*clear the flag to send the address*/
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_SLA_W_SENT)
	{
		Local_enuErrorState = NoError ;
		
	}
	
	
	return Local_enuErrorState ;
}
TWI_enuErrorsState TWI_u8MasterSendSlaveAdressRead (u8 Copy_u8Adress)
{
	TWI_enuErrorsState Local_enuErrorState = SlaveAddressWithReadErr ;
	
	/* 1- load the address of the slave */
	/* 2- clear the flag to and the address*/
	/* 3- wait until the flag rise */
	/* 4- check the ACK code of the operation */
	
	/*load the address of the slave */
	TWI_TWDR_REG = (Copy_u8Adress << 1);
	
	/* Read operation loaded
	** TWDR used for data loaded and (slave address loaded in the 7 MSB)
	** LSB in slave address loaded used to control the operation send to slave
	** LSB = 0 for write operation (Dominant bit) , LSB = 1 for read operation
	*/
	SET_BIT(TWI_TWDR_REG,TWD0);
	
	/* Clear the TWSTA bit */
	CLR_BIT(TWI_TWCR_REG,TWSTA);


	/*clear the flag to end the address*/
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	


	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_SLA_R_SENT)
	{
		Local_enuErrorState = NoError ;
	}
	
	
	return Local_enuErrorState ;
		
}

TWI_enuErrorsState TWI_u8MasterSendData (u8 Copy_u8Data)
{
	TWI_enuErrorsState Local_enuErrorState = MasterWriteByteErr ;
	
	/* 1- Load the data to TWDR */
	/* 2- Clear the flag */
	/* 3- wait until the flag being set*/
	/* 4- check the ACK received */
	
	/* Load the data to TWDR */
	TWI_TWDR_REG = Copy_u8Data ; 
	
	/*clear the flag to and the data*/
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_MASTER_DATA_SENT)
	{
		Local_enuErrorState = NoError ;
		
	}
	
	return Local_enuErrorState  ;
}

TWI_enuErrorsState TWI_u8MasterRecData (u8 *Copy_pu8Data)
{
	TWI_enuErrorsState Local_enuErrorState = MasterReadByteErr ;
	/* 1- clear the flag */
	/* 2- Waiting the flag to set */
	/* 3- check the ACK for received data */
	/* 4- Read the data from TWDR */
	
	
	/*clear the flag */
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_MASTER_DATA_REC)
	{
		/*Read the data from TWDR */
		*Copy_pu8Data = TWI_TWDR_REG ;
		
		Local_enuErrorState = NoError ;
	}
	
	return Local_enuErrorState  ;
	
}

/* this function implemented just for the RTC */
u8 TWI_u8MasterRecDataVersion2 ()
{
	u8 Local_u8ValueRec = MasterReadByteErr ;
	/* 1- clear the flag */
	/* 2- Waiting the flag to set */
	/* 3- check the ACK for received data */
	/* 4- Read the data from TWDR */

	/* Enable the ACK bit*/
	SET_BIT(TWI_TWCR_REG,TWEA);


	/*clear the flag */
	SET_BIT(TWI_TWCR_REG,TWINT) ;

	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));

	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_MASTER_DATA_REC)
	{
		/*Read the data from TWDR */
		Local_u8ValueRec = TWI_TWDR_REG ;
	}

	return Local_u8ValueRec  ;

}

u8 TWI_u8MasterRecDataNotAck ()
{
	u8 Local_u8ValueRec = MasterReadByteErr ;
	/* 1- clear the flag */
	/* 2- Waiting the flag to set */
	/* 3- check the ACK for received data */
	/* 4- Read the data from TWDR */

	/* Enable ACK*/
	CLR_BIT(TWI_TWCR_REG,TWEA);

	/*clear the flag */
	SET_BIT(TWI_TWCR_REG,TWINT) ;

	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));

	/*Read the data from TWDR */
	Local_u8ValueRec = TWI_TWDR_REG ;


//	/*  check the TWSR ACK Code for start condition*/
//	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_MASTER_DATA_REC)
//	{
//		/*Read the data from TWDR */
//		Local_u8ValueRec = TWI_TWDR_REG ;
//	}

	return Local_u8ValueRec  ;

}



TWI_enuErrorsState TWI_u8MasterRepetedStartCond (void)
{
	TWI_enuErrorsState Local_enuErrorState = RepeatedStartError ;
	
	/* 1- initiate the Start condition */
	/* 2- Clear the flag */
	/* 3- wait till the flag set  */
	/* 4- check the TWSR ACK Code for Start condition*/
	/* 5- Clear the TWSTA bit */
	
	/* initiate the Start condition */
	SET_BIT(TWI_TWCR_REG,TWSTA);
	
	/*clear the flag */
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check the TWSR ACK Code for Start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_START_COND_SENT)
	{
		/* Clear the TWSTA bit */
//		CLR_BIT(TWI_TWCR_REG,TWSTA);
		
		Local_enuErrorState = NoError ;
	}
	
	return Local_enuErrorState ;	
	
}

void TWI_u8MasterStopCond (void)
{
 
	/* 1- send stop conditon */
	SET_BIT(TWI_TWCR_REG,TWSTO);
	
	/* 2-clear the flag of the interrupt */
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
}

TWI_enuErrorsState TWI_u8SlaveSendData (u8 Copy_u8Data)
{
	TWI_enuErrorsState Local_enuErrorState = SlaveWriteByteErr ;
	/* 1- Load the data to TWDR */
	/* 2- Clear the flag to send the data  */
	/* 3- wait the flag to set*/
	/* 4- check the ACK */
	
	/* 1- Load the data to TWDR */
	TWI_TWDR_REG = Copy_u8Data;
	
	/*clear the flag */
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	/*  check th TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_SLAVE_SENT_DATA)
	{
		Local_enuErrorState = NoError ;
	}
	
	
	return Local_enuErrorState ;
	
	
}
TWI_enuErrorsState TWI_u8SlaveRecData (u8 *Copy_Pu8Data)
{
	TWI_enuErrorsState Local_enuErrorState = SlaveReadByteErr ;
	/* 1- Read the data */
	/* 2- clear the flag */
	/* 3- wait the flag to set */
	/* 4- check the ACK for Data received*/
	
	/*clear the flag */
	SET_BIT(TWI_TWCR_REG,TWINT) ;
	
	/* wait till the flag set  */
	while (!(GET_BIT(TWI_TWCR_REG,TWINT)));
	
	
	/*  check the TWSR ACK Code for start condition*/
	if ( (TWI_TWSR_REG & TWI_STATUES_REG_MSKING_VALUE) == TWI_SLAVE_REC_DATA)
	{
		*Copy_Pu8Data = TWI_TWDR_REG ;
		Local_enuErrorState = NoError ;
	}
	
	
	return Local_enuErrorState ;
	
	
	
}

