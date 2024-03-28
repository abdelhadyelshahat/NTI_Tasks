/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DIO_prog.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * Author : ABDELHADY ELSHAHAT ABDELHADY
 * Layer  : MCAL
 * SWD    : DIO
 */

/* LIB includes */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/*MCAL include */
#include "DIO_interface.h"
#include "DIO_privite.h"
#include "DIO_config.h"

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 1- DIO Initialization  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_void_DIOInit
 *  Arguments   : void
 *  Return type : void
 *  Description : This Function Initialize the DIO Pins [ I/P (Pull-up or floating ) - O/P (High or Low) ]
 * ----------------------------------------------------------------------------------------------
 */

void M_DIO_void_DIOInit(void)
{
	/* Macros for initial Direction of PORTA */
  DIO_u8_DDRA_REG = CONC(DIO_u8_PA7_INTIAL_DIRECTION,DIO_u8_PA6_INTIAL_DIRECTION,
		  	  	  	  	 DIO_u8_PA5_INTIAL_DIRECTION,DIO_u8_PA4_INTIAL_DIRECTION,
						 DIO_u8_PA3_INTIAL_DIRECTION,DIO_u8_PA2_INTIAL_DIRECTION,
						 DIO_u8_PA1_INTIAL_DIRECTION,DIO_u8_PA0_INTIAL_DIRECTION);
  /* Macros for initial Direction of PORTB */
  DIO_u8_DDRB_REG = CONC(DIO_u8_PB7_INTIAL_DIRECTION,DIO_u8_PB6_INTIAL_DIRECTION,
		  	  	  	  	 DIO_u8_PB5_INTIAL_DIRECTION,DIO_u8_PB4_INTIAL_DIRECTION,
						 DIO_u8_PB3_INTIAL_DIRECTION,DIO_u8_PB2_INTIAL_DIRECTION,
						 DIO_u8_PB1_INTIAL_DIRECTION,DIO_u8_PB0_INTIAL_DIRECTION);
  /* Macros for initial Direction of PORTC */
  DIO_u8_DDRC_REG = CONC(DIO_u8_PC7_INTIAL_DIRECTION,DIO_u8_PC6_INTIAL_DIRECTION,
		  	  	  	  	 DIO_u8_PC5_INTIAL_DIRECTION,DIO_u8_PC4_INTIAL_DIRECTION,
						 DIO_u8_PC3_INTIAL_DIRECTION,DIO_u8_PC2_INTIAL_DIRECTION,
						 DIO_u8_PC1_INTIAL_DIRECTION,DIO_u8_PC0_INTIAL_DIRECTION);
  /* Macros for initial Direction of PORTD */
  DIO_u8_DDRD_REG = CONC(DIO_u8_PD7_INTIAL_DIRECTION,DIO_u8_PD6_INTIAL_DIRECTION,
		  	  	  	  	 DIO_u8_PD5_INTIAL_DIRECTION,DIO_u8_PD4_INTIAL_DIRECTION,
						 DIO_u8_PD3_INTIAL_DIRECTION,DIO_u8_PD2_INTIAL_DIRECTION,
						 DIO_u8_PD1_INTIAL_DIRECTION,DIO_u8_PD0_INTIAL_DIRECTION);

  /* Macros for initial values of PORTA */
  DIO_u8_PORTA_REG = CONC(DIO_u8_PA7_INTIAL_VALUE,DIO_u8_PA6_INTIAL_VALUE,
		  	  	  	  	  DIO_u8_PA5_INTIAL_VALUE,DIO_u8_PA4_INTIAL_VALUE,
						  DIO_u8_PA3_INTIAL_VALUE,DIO_u8_PA2_INTIAL_VALUE,
						  DIO_u8_PA1_INTIAL_VALUE,DIO_u8_PA0_INTIAL_VALUE);
  /* Macros for initial values of PORTB */
  DIO_u8_PORTB_REG = CONC(DIO_u8_PB7_INTIAL_VALUE,DIO_u8_PB6_INTIAL_VALUE,
  		  	  	  	  	  DIO_u8_PB5_INTIAL_VALUE,DIO_u8_PB4_INTIAL_VALUE,
  						  DIO_u8_PB3_INTIAL_VALUE,DIO_u8_PB2_INTIAL_VALUE,
  						  DIO_u8_PB1_INTIAL_VALUE,DIO_u8_PB0_INTIAL_VALUE);
    /* Macros for initial values of PORTC */
   DIO_u8_PORTC_REG = CONC(DIO_u8_PC7_INTIAL_VALUE,DIO_u8_PC6_INTIAL_VALUE,
    		  	  	  	   DIO_u8_PC5_INTIAL_VALUE,DIO_u8_PC4_INTIAL_VALUE,
    					   DIO_u8_PC3_INTIAL_VALUE,DIO_u8_PC2_INTIAL_VALUE,
    					   DIO_u8_PC1_INTIAL_VALUE,DIO_u8_PC0_INTIAL_VALUE);
      /* Macros for initial values of PORTD */
    DIO_u8_PORTD_REG = CONC(DIO_u8_PD7_INTIAL_VALUE,DIO_u8_PD6_INTIAL_VALUE,
      		  	  	  	  	DIO_u8_PD5_INTIAL_VALUE,DIO_u8_PD4_INTIAL_VALUE,
      						DIO_u8_PD3_INTIAL_VALUE,DIO_u8_PD2_INTIAL_VALUE,
      						DIO_u8_PD1_INTIAL_VALUE,DIO_u8_PD0_INTIAL_VALUE);

}



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 2- Set Pin Direction  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_voidSetPinDirection
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_u8Direction   Options: DIO_u8_PIN_OUTPUT_DIRECTION, DIO_u8_PIN_INPUT_DIRECTION  	                             	    																**/
 /* Return type :(u8 variable)        Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Sets the Direction of a specific pin (I/P - O/P)
 * ----------------------------------------------------------------------------------------------
 */
u8 M_DIO_u8_SetPinDirection(u8 Copy_u8PortNumber , u8 Copy_u8PinNumber, u8 Copy_u8Direction )
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK ;

	/* Input validation ( check if the port Number and Pin Number are in the valid range )*/
	if ((Copy_u8PortNumber <= DIO_u8_PORTD) && (Copy_u8PinNumber <= DIO_u8_PIN7))
	{
		Local_u8ErrorState = STD_TYPES_OK;

		if (Copy_u8Direction == DIO_u8_PIN_OUTPUT_DIRECTION) /* check the direction */
		{
			switch (Copy_u8PortNumber) /* check the port Number */
			{
			case DIO_u8_PORTA : SET_BIT(DIO_u8_DDRA_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTB : SET_BIT(DIO_u8_DDRB_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTC : SET_BIT(DIO_u8_DDRC_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTD : SET_BIT(DIO_u8_DDRD_REG,Copy_u8PinNumber) ; break;
			}
		}

		else if (Copy_u8Direction == DIO_u8_PIN_INPUT_DIRECTION) /* check the direction */
		{
			switch (Copy_u8PortNumber) /* check the port Number */
			{
			case DIO_u8_PORTA : CLR_BIT(DIO_u8_DDRA_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTB : CLR_BIT(DIO_u8_DDRB_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTC : CLR_BIT(DIO_u8_DDRC_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTD : CLR_BIT(DIO_u8_DDRD_REG,Copy_u8PinNumber) ; break;
			}
		}
		else /* Invalid Direction option */
		{
			 Local_u8ErrorState = STD_TYPES_NOK ;
		}

	}


	return Local_u8ErrorState;
}



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 3- Set Pin Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_SetPinValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_u8OValue      Options: DIO_u8_PIN_VALUE_HIGH, DIO_u8_PIN_VALUE_LOW  	                             	    																**/
 /* Return type :(u8 variable)        Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Sets the value of a specific pin (HIGH - LOW)
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_SetPinValue (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber, u8 Copy_u8Value)
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK ;

	/* Input validation ( check if the port Number and Pin Number are in the valid range )*/
	if ((Copy_u8PortNumber <= DIO_u8_PORTD) && (Copy_u8PinNumber <= DIO_u8_PIN7))
	{

		Local_u8ErrorState = STD_TYPES_OK;

		if (Copy_u8Value == DIO_u8_PIN_VALUE_HIGH) /* check the direction */
		{
			switch (Copy_u8PortNumber) /* check the port Number */
			{
			case DIO_u8_PORTA : SET_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTB : SET_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTC : SET_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTD : SET_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber) ; break;
			}
		}

		else if (Copy_u8Value == DIO_u8_PIN_VALUE_LOW) /* check the direction */
		{
			switch (Copy_u8PortNumber) /* check the port Number */
			{
			case DIO_u8_PORTA : CLR_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTB : CLR_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTC : CLR_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber) ; break;
			case DIO_u8_PORTD : CLR_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber) ; break;
			}
		}
		else /* Invalid Direction option */
		{
			Local_u8ErrorState = STD_TYPES_NOK ;
		}

	}

	return Local_u8ErrorState;
}



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 4- Get Pin Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_GetPinValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_Pu8PinValue   pointer to receive the pin value  	                             	    																**/
 /* Return type :(u8 variable)        Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Gets the value of a specific pin (HIGH - LOW)
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_GetPinValue (u8 Copy_u8PortNumber,u8 Copy_u8PinNumber, u8 * Copy_Pu8PinValue)
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK ;

	/* Input validation ( check if the port Number and Pin Number are in the valid range && if the user pass a Pointer)*/
	if ((Copy_u8PortNumber <= DIO_u8_PORTD) && (Copy_u8PinNumber <= DIO_u8_PIN7) && (Copy_Pu8PinValue != NULL))
	{
		Local_u8ErrorState = STD_TYPES_OK;

		switch (Copy_u8PortNumber)/* check the port Number */
		{
			case DIO_u8_PORTA : *Copy_Pu8PinValue =GET_BIT(DIO_u8_PINA_REG,Copy_u8PinNumber);break; /* update the variable with Pin value*/
			case DIO_u8_PORTB : *Copy_Pu8PinValue =GET_BIT(DIO_u8_PINB_REG,Copy_u8PinNumber);break;  /* update the variable with Pin value*/
			case DIO_u8_PORTC : *Copy_Pu8PinValue =GET_BIT(DIO_u8_PINC_REG,Copy_u8PinNumber);break; /* update the variable with Pin value*/
			case DIO_u8_PORTD : *Copy_Pu8PinValue =GET_BIT(DIO_u8_PIND_REG,Copy_u8PinNumber);break; /* update the variable with Pin value*/
		}

	}

	return Local_u8ErrorState ;

}


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 5- Toggle Pin Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_TogglePinValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * Return type :(u8 variable)        Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Toggles the value of a specific Pin
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_TogglePinValue (u8 Copy_u8PortNumber,u8 Copy_u8PinNumber)
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK ;

	/* Input validation ( check if the port Number and Pin Number are in the valid range) */
	if (Copy_u8PortNumber <= DIO_u8_PORTD && Copy_u8PinNumber <= DIO_u8_PIN7)
	{
		Local_u8ErrorState = STD_TYPES_OK ;

		switch (Copy_u8PortNumber ) /* check the port Number */
		{
		case DIO_u8_PORTA : TOG_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber); break;
		case DIO_u8_PORTB : TOG_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber); break;
		case DIO_u8_PORTC : TOG_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber); break;
		case DIO_u8_PORTD : TOG_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber); break;
		}


	}
	return Local_u8ErrorState;

}



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 6- Set Port Direction  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_SetPortDirection
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PortDirection   Options: DIO_u8_PORT_DIRECTION_OUTPUT, DIO_u8_PORT_DIRECTION_INPUT                           	    																**/
 /* Return type :(u8 variable)        Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Sets the Direction of a specific PORT (O/P - I/P)
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_SetPortDirection (u8 Copy_u8PortNumber , u8 Copy_u8PortDirection )
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	/* Input validation ( check if the port Number is in the valid range */
	if (Copy_u8PortNumber <= DIO_u8_PORTD )
	{
		Local_u8ErrorState = STD_TYPES_OK;

		switch (Copy_u8PortNumber) /* check the port Number */
		{
			case DIO_u8_PORTA : DIO_u8_DDRA_REG = Copy_u8PortDirection ; break;
			case DIO_u8_PORTB : DIO_u8_DDRB_REG = Copy_u8PortDirection ; break;
			case DIO_u8_PORTC : DIO_u8_DDRC_REG = Copy_u8PortDirection ; break;
			case DIO_u8_PORTD : DIO_u8_DDRD_REG = Copy_u8PortDirection ; break;
		}

	}
	return Local_u8ErrorState;

}


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 7- Set Port Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_SetPortValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PortValue   Options: DIO_u8_PORT_VALUE_HIGH, DIO_u8_PORT_VALUE_LOW , custom values by user                          	    																**/
 /* Return type :(u8 variable)        Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Sets the Value of a specific PORT (HIGH - LOW)
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_SetPortValue (u8 Copy_u8PortNumber , u8 Copy_u8PortValue )
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	/* Input validation ( check if the port Number is in the valid range */
	if (Copy_u8PortNumber <= DIO_u8_PORTD )
	{
		Local_u8ErrorState = STD_TYPES_OK;

			switch (Copy_u8PortNumber)  /* check the port Number */
			{
				case DIO_u8_PORTA : DIO_u8_PORTA_REG = Copy_u8PortValue ; break;
				case DIO_u8_PORTB : DIO_u8_PORTB_REG = Copy_u8PortValue ; break;
				case DIO_u8_PORTC : DIO_u8_PORTC_REG = Copy_u8PortValue ; break;
				case DIO_u8_PORTD : DIO_u8_PORTD_REG = Copy_u8PortValue ; break;
			}

	}
	return Local_u8ErrorState;


}


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 8- Active Pull-up Resistor  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_ActivePullupResistor
 *  Arguments   :
 * 				 =>Copy_u8PortNumber      Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber       Options: Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_u8State           Options: DIO_u8_PULLUP_RES_EN, DIO_u8_PULLUP_RES_DIS              	    																**/
 /* Return type :(u8 variable)        	  Error State  (STD_TYPES_NOK, STD_TYPES_OK)
 *  Description : This Function Enables and Disables  the internal Pull-up Resistor on a specific pin
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_ActivePullupResistor (u8 Copy_u8PortNumber ,u8 Copy_u8PinNumber , u8 Copy_u8State)
{
	/* Error State variable  */
	u8 Local_u8ErrorState = STD_TYPES_NOK ;
	/* Input validation ( check if the port Number and Pin Number are in the valid range) */
	if (Copy_u8PortNumber <  DIO_u8_PORTD && Copy_u8PinNumber < DIO_u8_PIN7 )
	{
		Local_u8ErrorState = STD_TYPES_OK ;
		/* check the state of the Pull-up*/
		if (Copy_u8State == DIO_u8_PULLUP_RES_EN )
		{
			switch (Copy_u8PortNumber) /* check the port Number*/
			{
			case DIO_u8_PORTA :
				CLR_BIT(DIO_u8_DDRA_REG,Copy_u8PinNumber);  /*  set the direction of the pin to input */
				SET_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber); /*  Active the pull-up resistor       */
				break;
			case DIO_u8_PORTB :
				CLR_BIT(DIO_u8_DDRB_REG,Copy_u8PinNumber);    /*  set the direction of the pin to input */
				SET_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber);   /*  Active the pull-up resistor       */
				break;

			case DIO_u8_PORTC :
				CLR_BIT(DIO_u8_DDRC_REG,Copy_u8PinNumber);    /*  set the direction of the pin to input */
				SET_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber);   /*  Active the pull-up resistor       */
				break;

			case DIO_u8_PORTD :
				CLR_BIT(DIO_u8_DDRD_REG,Copy_u8PinNumber);   /*  set the direction of the pin  to input */
				SET_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber);  /*  Active the pull-up resistor       */
				break;
			}
		}
		else if (Copy_u8State == DIO_u8_PULLUP_RES_DIS ) /* check the state of the Pull-up Resistor */
		{
			switch (Copy_u8PortNumber)
			{
			case DIO_u8_PORTA : CLR_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber); break; /*Disable the pull-up Resistor*/
			case DIO_u8_PORTB :	CLR_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber); break; /*Disable the pull-up Resistor*/
			case DIO_u8_PORTC :	CLR_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber); break; /*Disable the pull-up Resistor*/
			case DIO_u8_PORTD :	CLR_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber); break; /*Disable the pull-up Resistor*/
			}

		}
		else { Local_u8ErrorState = STD_TYPES_NOK ;	}

	}

	return Local_u8ErrorState ;
}







