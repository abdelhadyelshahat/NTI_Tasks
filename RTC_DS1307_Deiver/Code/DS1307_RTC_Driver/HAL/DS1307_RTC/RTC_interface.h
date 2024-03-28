/*
 * RTC_interface.h
 *
 *  Created on: Mar 25, 2024
 *      Author: hady
 */

#ifndef HAL_DS1307_RTC_RTC_INTERFACE_H_
#define HAL_DS1307_RTC_RTC_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

typedef enum
{
	RTC_SetClock_Ok,
	RTC_SetClock_NOk,

}RTC_Errors_enu;


typedef enum
{	_24_HOURS_MODE,
	_12_HOURS_MODE_PM,
	_12_HOURS_MODE_AM}
RTC_Hours_mode_enu;

typedef enum
{
	SAT,SUN,MON,TUE,WED,THR,FRI

}RTC_DAY_enu;


typedef struct
{
	u8 RTC_u8HoursMode;
	u8 RTC_u8Hours;
	u8 RTC_u8Minutes;
	u8 RTC_u8Senconds;

}RTC_Clock_st ;

typedef struct
{
	u8 RTC_u8Day;
	u8 RTC_u8Date;
	u8 RTC_u8Month;
	u8 RTC_u8Year;

}RTC_Date_st ;


/*********************function prototypes *******************/
RTC_Errors_enu RTC_enuSetClock (RTC_Clock_st * Copy_PstClock);


RTC_Errors_enu RTC_enuSetDate (RTC_Date_st * Copy_PstDate);


RTC_Errors_enu RTC_enuReadingClock (RTC_Clock_st * Copy_PstClock);

RTC_Errors_enu RTC_enuReadingDate (RTC_Date_st * Copy_PstDate);

u8  RTC_u8ConvertBCDToDecimal (u8 Copy_u8BCDvalue );

#endif /* HAL_DS1307_RTC_RTC_INTERFACE_H_ */
