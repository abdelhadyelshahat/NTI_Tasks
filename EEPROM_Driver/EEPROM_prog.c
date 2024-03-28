/* <<<<<<<<<<<<<< EEPROM_prog.c >>>>>>>>>>>>>>>>*/

/* LIB includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define   F_CPU 2000000UL
#include "util/delay.h"

/* MCAL includes */
#include "TWI_interface.h"

/* HAL includes */
#include "EEPROM_interface.h"
#include "EEPROM_privite.h"
#include "EEPROM_config.h"




u8 EEPROM_u8WriteByte(u16 Copy_u16ByteAdress , u8 Copy_u8Data)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK ;


	/*1- start condition*/
	Local_u8ErrorState =TWI_u8MasterStartCond ();


	/*2- write address with W operation */
	Local_u8ErrorState = TWI_u8MasterSendSlaveAdressWrite( EEPROM_FIXED_ADDRESS | (EEPROM_A2_Value << 2) | (u8)(Copy_u16ByteAdress >>8));


	/*3- send the byte address */
	Local_u8ErrorState = TWI_u8MasterSendData((u8)Copy_u16ByteAdress);


	/*4- send the data */
	Local_u8ErrorState = TWI_u8MasterSendData( Copy_u8Data);


	/*5- send stop condition  */
	TWI_u8MasterStopCond();

	_delay_ms(10);

	Local_u8ErrorState = STD_TYPES_OK ;

	return Local_u8ErrorState ;
}


u8 EEPROM_u8ReadByte (u16 Copy_u16ByteAdress , u8 *Copy_Pu8Data)
{
	u8 Local_u8ErrorState = STD_TYPES_OK ;
	TWI_enuErrorsState Local_enuErrorState = NoError ;

	/*1- start condition*/
	Local_enuErrorState = TWI_u8MasterStartCond ();
	Local_u8ErrorState = EEPROM_u8ErrorCheck (Local_enuErrorState);

	/*2- write address with W operation */
	Local_enuErrorState = TWI_u8MasterSendSlaveAdressWrite( EEPROM_FIXED_ADDRESS | (EEPROM_A2_Value << 2) | (u8)(Copy_u16ByteAdress >>8));
	Local_u8ErrorState = EEPROM_u8ErrorCheck (Local_enuErrorState);

	/*3- send the byte address */
	Local_enuErrorState =TWI_u8MasterSendData( (u8) Copy_u16ByteAdress);
	Local_u8ErrorState = EEPROM_u8ErrorCheck (Local_enuErrorState);

	/* 4- Repeated Start condition */
	Local_enuErrorState =  TWI_u8MasterRepetedStartCond();

	/*5- write address with R operation */
	Local_enuErrorState = TWI_u8MasterSendSlaveAdressRead( EEPROM_FIXED_ADDRESS | (EEPROM_A2_Value << 2) | (u8)(Copy_u16ByteAdress >>8));
	Local_u8ErrorState = EEPROM_u8ErrorCheck (Local_enuErrorState);

	/* 6- Read the data */
	Local_enuErrorState = TWI_u8MasterRecData(Copy_Pu8Data);
	Local_u8ErrorState = EEPROM_u8ErrorCheck (Local_enuErrorState);

	/* 7- stop condition*/

	/*5- send stop condition  */
	TWI_u8MasterStopCond();

	return Local_u8ErrorState ;

}

static u8 EEPROM_u8ErrorCheck (TWI_enuErrorsState Copy_enuErrorstate )
{
	u8 Local_u8ErrorState = STD_TYPES_OK ;
	if (Copy_enuErrorstate !=NoError )
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}

	return Local_u8ErrorState ;


}
