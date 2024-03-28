/*
 * main.c
 *
 *  Created on: Mar 25, 2024
 *      Author: hady
 */

/* LIB includes*/
#include"../LIB/BIT_MATH.h"
#include <util/delay.h>



/* HAl includes */
#include "../HAL/DS1307_RTC/RTC_interface.h"
#include "../HAL/LCD/LCD_interface.h"

/* MCAL includes */
#include "../MCAL/TWI/TWI_interface.h"

RTC_Clock_st Clock = { _24_HOURS_MODE , 18 , 50 , 51} ;
RTC_Clock_st Clock_rec ;
RTC_Date_st Date = { MON ,25 , 8 , 22};
int main ()
{

	/* TWI INIT*/
	TWI_voidMasterInit();

	/* LCD */
	H_LCD_void_LCD_Init();

	/* Set the clock*/
	RTC_enuSetClock(&Clock);
	/* set the date */
	RTC_enuSetDate(&Date);


	/* Reading the clock*/
	RTC_enuReadingClock(&Clock);
	/* Reading the date*/
	RTC_enuReadingDate(&Date);


	u8 H = (RTC_u8ConvertBCDToDecimal((Clock.RTC_u8Hours)));
	u8 H_M = (RTC_u8ConvertBCDToDecimal((Clock.RTC_u8HoursMode)));
	u8 M = (RTC_u8ConvertBCDToDecimal(Clock.RTC_u8Minutes));
	u8 S = (RTC_u8ConvertBCDToDecimal(Clock.RTC_u8Senconds));

	u8 D = RTC_u8ConvertBCDToDecimal(Date.RTC_u8Day);
	u8 Da = RTC_u8ConvertBCDToDecimal(Date.RTC_u8Date);
	u8 Month = RTC_u8ConvertBCDToDecimal(Date.RTC_u8Month);
	u8 year = (RTC_u8ConvertBCDToDecimal(Date.RTC_u8Year));



	H_LCD_void_SendString("CLK : ");
	H_LCD_void_SendNumber(H);
	H_LCD_void_SendString(":");
	H_LCD_void_SendNumber(M);
	H_LCD_void_SendString(":");
	H_LCD_void_SendNumber(S);

	switch (H_M)
	{
	case _24_HOURS_MODE :H_LCD_void_SendString(" (24)");break;
	case _12_HOURS_MODE_AM :H_LCD_void_SendString(" AM");break;
	case _12_HOURS_MODE_PM :H_LCD_void_SendString(" PM");break;
	}

	H_LCD_voidGoToXY(1,0);
	H_LCD_void_SendString("Day : ");
	switch (D)
	{
	case SAT : H_LCD_void_SendString("SAT"); break;
	case SUN : H_LCD_void_SendString("SUN"); break;
	case MON : H_LCD_void_SendString("MON"); break;
	case TUE : H_LCD_void_SendString("TUE"); break;
	case WED : H_LCD_void_SendString("WED"); break;
	case THR : H_LCD_void_SendString("THR"); break;
	case FRI : H_LCD_void_SendString("FRI"); break;
	}

	H_LCD_voidGoToXY(2,0);
	H_LCD_void_SendString("Date :");
	H_LCD_void_SendNumber(Da);
	H_LCD_void_SendString("/");
	H_LCD_void_SendNumber(Month);
	H_LCD_void_SendString("/20");
	H_LCD_void_SendNumber(year);





	while (1)
		{
			H = 0,H_M = 0, M = 0 ,S =0;
			/* Reading the clock*/

			 RTC_enuReadingClock(&Clock);
			 H = (RTC_u8ConvertBCDToDecimal((Clock.RTC_u8Hours)));
			 H_M = (RTC_u8ConvertBCDToDecimal((Clock.RTC_u8HoursMode)));
			 M = (RTC_u8ConvertBCDToDecimal(Clock.RTC_u8Minutes));

			 S = (RTC_u8ConvertBCDToDecimal(Clock.RTC_u8Senconds));

			 H_LCD_voidGoToXY(0,0);
				H_LCD_void_SendString("CLK : ");
				H_LCD_void_SendNumber(H);
				H_LCD_void_SendString(":");
				H_LCD_void_SendNumber(M);
				H_LCD_void_SendString(":");
				if (S < 9)
				{
					H_LCD_void_SendNumber(S);
					H_LCD_void_SendString(" ");
				}
				else
				{
					H_LCD_void_SendNumber(S);
				}


				_delay_ms(400);



		};
//
//	return 0;
}
