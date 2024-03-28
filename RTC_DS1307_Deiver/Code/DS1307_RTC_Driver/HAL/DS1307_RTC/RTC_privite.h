/*
 * RTC_privite.h
 *
 *  Created on: Mar 25, 2024
 *      Author: hady
 */

#ifndef HAL_DS1307_RTC_RTC_PRIVITE_H_
#define HAL_DS1307_RTC_RTC_PRIVITE_H_


static RTC_Errors_enu RTC_enuConvertDecToBCD (u8 local_u8DecmialValue);



/****** Macros for RTC Registers*******/
#define RTC_SECONDS_REG   0x00
#define RTC_DAYS_REG 	  0x03
#define RTC_DATE_REG 	  0x04


#endif /* HAL_DS1307_RTC_RTC_PRIVITE_H_ */
