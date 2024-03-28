/*
 * RTC_prog.c
 *
 *  Created on: Mar 25, 2024
 *      Author: hady
 */

/* LIB includes */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>

/* HAL includes */
#include "RTC_interface.h"
#include "RTC_config.h"
#include "RTC_privite.h"

/* MCAL includes */
#include "../../MCAL/TWI/TWI_interface.h"


/********* Setting functions *********/
RTC_Errors_enu RTC_enuSetClock (RTC_Clock_st * Copy_PstClock )
{
	RTC_Errors_enu Local_enuClockError = RTC_SetClock_Ok;

	/* Handle the Hours Mode*/
	Copy_PstClock->RTC_u8Hours = RTC_enuConvertDecToBCD(Copy_PstClock->RTC_u8Hours);

	if (Copy_PstClock->RTC_u8HoursMode == _24_HOURS_MODE)
	{
		CLR_BIT(Copy_PstClock->RTC_u8Hours,6);
	}
	else
	{
		SET_BIT(Copy_PstClock->RTC_u8Hours,6);

		if (Copy_PstClock->RTC_u8HoursMode == _12_HOURS_MODE_AM)
		{
			CLR_BIT(Copy_PstClock->RTC_u8Hours,5);
		}
		else
		{
			SET_BIT(Copy_PstClock->RTC_u8Hours,5);
		}
	}

	/* send start condition */
	TWI_u8MasterStartCond();

	/* send the RTC address with write operation  */
	TWI_u8MasterSendSlaveAdressWrite(0b01101000);

	/* send the start register address to writ which is the seconds */
	/* the address will be sent as sending data */
	TWI_u8MasterSendData(RTC_SECONDS_REG);

	/* send the Seconds value */
	/* be aware that the MSB must be zero to enable the CH (clock hat) */
	TWI_u8MasterSendData(RTC_enuConvertDecToBCD(Copy_PstClock->RTC_u8Senconds));

	/* send the Minutes */
	TWI_u8MasterSendData(RTC_enuConvertDecToBCD(Copy_PstClock->RTC_u8Minutes));

	/* send the Hours   */
	TWI_u8MasterSendData(Copy_PstClock->RTC_u8Hours);

	/* Send stop condition */
	TWI_u8MasterStopCond();

	return Local_enuClockError;
}


//RTC_Errors_enu RTC_enuSetDay (RTC_DAY_enu RTC_DAY)
//{
//	RTC_Errors_enu Local_enuClockError = RTC_SetClock_Ok;
//
//	/* send start condition */
//	TWI_u8MasterStartCond();
//
//	/* send the RTC address with write operation  */
//	TWI_u8MasterSendSlaveAdressWrite(0b01101000);
//
//	/* send the start register address to writ which is the seconds */
//	/* the address will be sent as sending data */
//	TWI_u8MasterSendData(RTC_DAYS_REG);
//
//	/* Set the Day */
//	TWI_u8MasterSendData(RTC_DAY);
//
//	/* Send stop condition */
//	TWI_u8MasterStopCond();
//
//	return Local_enuClockError;
//
//
//
//}

RTC_Errors_enu RTC_enuSetDate (RTC_Date_st * Copy_PstDate)
{
	RTC_Errors_enu Local_enuClockError = RTC_SetClock_Ok;

	/* send start condition */
	TWI_u8MasterStartCond();

	/* send the RTC address with write operation  */
	TWI_u8MasterSendSlaveAdressWrite(0b01101000);

	/* send the start register address to writ which is the Day */
	/* the address will be sent as sending data */
	TWI_u8MasterSendData(RTC_DAYS_REG);

	/* send the Day value */
	/* be aware that the MSB must be zero to enable the CH (clock hat) */
	TWI_u8MasterSendData(RTC_enuConvertDecToBCD(Copy_PstDate->RTC_u8Day));

	/* Send the Date*/
	TWI_u8MasterSendData(RTC_enuConvertDecToBCD(Copy_PstDate->RTC_u8Date));

	/* send the Month */
	TWI_u8MasterSendData(RTC_enuConvertDecToBCD(Copy_PstDate->RTC_u8Month));

	/* send the year   */
	TWI_u8MasterSendData(RTC_enuConvertDecToBCD(Copy_PstDate->RTC_u8Year));

	/* Send stop condition */
	TWI_u8MasterStopCond();

	return Local_enuClockError;
}

static u8 RTC_enuConvertDecToBCD (u8 Copy_u8DecmialValue)
{
	u8 Local_u8BCDValue ;

	/* Get the first digit*/
	Local_u8BCDValue = Copy_u8DecmialValue % 10;

	/* Remove the first digit */
	Copy_u8DecmialValue/= 10;

	Local_u8BCDValue |= (Copy_u8DecmialValue << 4);

	return Local_u8BCDValue;
}

u8  RTC_u8ConvertBCDToDecimal (u8 Copy_u8BCDvalue )
{
	u8 Temp_var =0;

	/* Get the MSB half*/
	// 							0b 01010000
	Temp_var = Copy_u8BCDvalue & 0b11110000;

	/* Clear the MSB from the BCD value */
	Copy_u8BCDvalue = Copy_u8BCDvalue & 0b00001111;

	/* Converting Algorithm */
	Temp_var = Copy_u8BCDvalue + ((Temp_var >> 4) * 10);



	return Temp_var;

}

/************ Reading functions ***************************/

RTC_Errors_enu RTC_enuReadingClock (RTC_Clock_st * Copy_PstClock)
{

	RTC_Errors_enu Local_enuClockError = RTC_SetClock_Ok;

	/* send start condition */
	TWI_u8MasterStartCond();

	/*********** Hints in read operations ***************************/
	/* 1- send the slave address with write operation */
	/* send the RTC address with write operation  */
	TWI_u8MasterSendSlaveAdressWrite(0b01101000);

	/* 2- send the start address you want to start read from */
	/* send the start register address to writ which is the seconds */
	/* the address will be sent as sending data */
	TWI_u8MasterSendData(RTC_SECONDS_REG);

	/* 3- send repeat start condition */
	 TWI_u8MasterRepetedStartCond ();

	/* 4- send the same RTC address with read operation */
	 TWI_u8MasterSendSlaveAdressRead (0b01101000);

	 /* 5- receive the seconds from the slave RTC*/
	 Copy_PstClock->RTC_u8Senconds = TWI_u8MasterRecDataVersion2();

	 /* 7- receive the minutes from the slave RTC*/
	 Copy_PstClock->RTC_u8Minutes= TWI_u8MasterRecDataVersion2();

	 /* 6- receive the hours from the slave RTC*/
	 Copy_PstClock->RTC_u8Hours= TWI_u8MasterRecDataNotAck();

	/* Send stop condition */
	TWI_u8MasterStopCond();

	/* Handle the Hours Mode */
	if ( GET_BIT(Copy_PstClock->RTC_u8Hours,6) == _24_HOURS_MODE)
	{
		Copy_PstClock->RTC_u8HoursMode = _24_HOURS_MODE;
	}
	else
	{
		if ( GET_BIT(Copy_PstClock->RTC_u8Hours,6) == _12_HOURS_MODE_PM)
		{
			Copy_PstClock->RTC_u8HoursMode = _12_HOURS_MODE_PM;
		}
		else
		{
			Copy_PstClock->RTC_u8HoursMode = _12_HOURS_MODE_AM;

		}

	}


	return Local_enuClockError;

}

RTC_Errors_enu RTC_enuReadingDate (RTC_Date_st * Copy_PstDate)
{

	RTC_Errors_enu Local_enuClockError = RTC_SetClock_Ok;

	/* send start condition */
	TWI_u8MasterStartCond();

	/*********** Hints in read operations ***************************/
	/* 1- send the slave address with write operation */
	/* send the RTC address with write operation  */
	TWI_u8MasterSendSlaveAdressWrite(0b01101000);

	/* 2- send the start address you want to start read from */
	/* send the start register address to writ which is the seconds */
	/* the address will be sent as sending data */
	TWI_u8MasterSendData(RTC_DAYS_REG);

	/* 3- send repeat start condition */
	 TWI_u8MasterRepetedStartCond ();

	/* 4- send the same RTC address with read operation */
	 TWI_u8MasterSendSlaveAdressRead (0b01101000);

	 /* 5- receive the day from the slave RTC*/
	 Copy_PstDate->RTC_u8Day= TWI_u8MasterRecDataVersion2();

	 /* 7- receive the date from the slave RTC*/
	 Copy_PstDate->RTC_u8Date= TWI_u8MasterRecDataVersion2();

	 /* 6- receive the month from the slave RTC*/
	 Copy_PstDate->RTC_u8Month= TWI_u8MasterRecDataVersion2();

	 /* 8- receive the year from the salve RTC*/
	 Copy_PstDate->RTC_u8Year= TWI_u8MasterRecDataNotAck();



	/* Send stop condition */
	TWI_u8MasterStopCond();



	return Local_enuClockError;

}

