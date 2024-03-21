
/* Author : Abdelhady Elshahat Abdelhady
 * Layer  : MCAL
 * SWC    : UART

 */


/* LIB includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL includes */
#include "UART_interface.h"
#include "UART_privite.h"
#include "UART_config.h"

/***************** UART Variables **********************************/
/* State variable */
static u8 UART_u8_UARTState = IDLE ;

/* Send string Buffer */
static u8 * UART_Pu8sendStringBuffer  = NULL;

/* Receive String Buffer */
static u8 * UART_Pu8sendReceiveBuffer  = NULL;

/* Received String buffer size */
static u8 UART_u8BufferSize;

/* string Iterator */
static u8 UART_u8StringIterrator = 0;

/* Global Pointer to function to carry the address of the Callback function */
static void (* UART_PvoidCallBackFunction) (void) = NULL;


/************************************* UART Function*************************************************************/

/* Function   : M_UART_void_UARTInit
 * Brief   	  : This Function initialize the UART peripheral depend on the UART_config.h file
 * Parameters : void
 * return     : void
 */
void M_UART_void_UARTInit (void)
{
	/* variable to update the UCSRA register */
	u8 Local_u8UCSRAUpdate = 0;
	/**********  1- Set the Baud Rate Value  ************/

	/* calculate the Baud rate using the equation */
	u16 Local_u16BaudRateValue = (u16)((F_CPU_SYS / (UART_BAUD_RATE_VALUE * 16 )) - 1 );

	/* Assign the UBBRH first with the most weight bits*/
	UART_u8_UBRRH_REG = (u8) (Local_u16BaudRateValue >> 8 ) ;

	/* Assign the UBBRL */
	UART_u8_UBRRL_REG = (u8) Local_u16BaudRateValue ;

	/******* 2- Double Speed option ************/
#if UART_u8_U2X_OPTION == UART_u8_U2X_DISABLE
	CLR_BIT(UART_u8_UCSRA_REG,UCSRA_U2X);

#elif UART_u8_U2X_OPTION == UART_u8_U2X_ENABLE
	SET_BIT(UART_u8_UCSRA_REG,UCSRA_U2X);
#endif
/*************** 3- UART interrupts options *****************/
	/************** RX complete INT EN ********************/
#if UART_u8_RXCIE_OPTION == UART_INT_EN

	SET_BIT(UART_u8_UCSRB_REG,UCSRB_RXCIE);

#elif UART_u8_RXCIE_OPTION == UART_INT_DIS
	CLR_BIT(UART_u8_UCSRB_REG,UCSRB_RXCIE);
#endif

	/************** TX complete INT EN ********************/
#if UART_u8_TXCIE_OPTION == UART_INT_EN

	SET_BIT(UART_u8_UCSRB_REG,UCSRB_TXCIE);
#elif UART_u8_RXCIE_OPTION == UART_INT_DIS
	CLR_BIT(UART_u8_UCSRB_REG,UCSRB_TXCIE);
#endif
	/************** UDRE ( UDR register is empty ) INT EN ********************/
#if UART_u8_UDRIE_OPTION == UART_INT_EN

	SET_BIT(UART_u8_UCSRB_REG,UART_u8_TX_EN);
#elif UART_u8_RXCIE_OPTION == UART_INT_DIS
	CLR_BIT(UART_u8_UCSRB_REG,UCSRB_UDRIE);
#endif

	/*************** 4- Select the mode ***************/
#if UART_u8_MODE_OPTION == UART_u8_ASYNCHRONOUS
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UMSEL_BIT);

#elif UART_u8_MODE_OPTION == UART_u8_SYNCHRONOUS
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UMSEL_BIT);
#endif

	/********************** 5- Select parity options  */
#if UART_u8_PARITY_OPTION == DISABLED_PARITY_MODE
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UPM1_BIT);
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UPM0_BIT);
#elif UART_u8_PARITY_OPTION == EVEN_PARITY_MODE
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UPM1_BIT);
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UPM0_BIT);

#elif UART_u8_PARITY_OPTION == ODD_PARITY_MODE
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UPM1_BIT);
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UPM0_BIT);

#endif


	/************** 6- Select stop bits options ***********/
#if UART_STOP_BIT_OPTIONS == UART_u8_ONE_STOP_BIT
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_USBS_BIT);
#elif UART_STOP_BIT_OPTIONS == UART_u8_TWO_STOP_BIT
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_USBS_BIT);
#endif

	/*************** 7- Select character size *****************/
#if UART_u8_CHARACTER_SIZE_OPTION  == UART_DATA_5_BITS
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ0_BIT);
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ1_BIT);
#elif UART_u8_CHARACTER_SIZE_OPTION  == UART_DATA_6_BITS
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ0_BIT);
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ1_BIT);
#elif UART_u8_CHARACTER_SIZE_OPTION  == UART_DATA_7_BITS
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ1_BIT);
	CLR_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ0_BIT);
#elif UART_u8_CHARACTER_SIZE_OPTION  == UART_DATA_8_BITS
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ0_BIT);
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_UCSZ1_BIT);
#endif

	/************************* 8 - Write on UCSRC register ******************/
	/* SET the URSEL Bit */
	SET_BIT(Local_u8UCSRAUpdate,UCSRC_URSEL_BIT);

	/* Write in the register */
	UART_u8_UCSRC_REG = Local_u8UCSRAUpdate;

	/************************ 9- Enable the TX ******************************/
#if UART_u8_TX_OPTION == UART_u8_TX_EN
	SET_BIT(UART_u8_UCSRB_REG,UCSRB_TXEN);
#elif UART_u8_TX_OPTION == UART_u8_TX_DIS
	CLR_BIT(UART_u8_UCSRB_REG,UCSRB_TXEN);
#endif
	/************************ 9- Enable the RX ******************************/
#if UART_u8_RX_OPTION == UART_u8_RX_EN
	SET_BIT(UART_u8_UCSRB_REG,UCSRB_RXEN);
#elif UART_u8_TX_OPTION == UART_u8_RX_DIS
	CLR_BIT(UART_u8_UCSRB_REG,UCSRB_RXEN);
#endif
}


/* Function   : M_UART_u8_UARTSendCharacter
 * Brief   	  : This Function send character out of the AVR by the UART Communication protocol
 * Parameters : Copy_u8Character (the character wanted to send)
 * return     : function error State
 */

u8 M_UART_u8_UARTSendCharacter (u8 Copy_u8Character)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8TimeOutCounter= 0;
	if (UART_u8_UARTState == IDLE)
	{
		UART_u8_UARTState = BUSY;

		 while ((GET_BIT(UART_u8_UCSRA_REG,UCSRA_UDRE) == 0) && (Local_u8TimeOutCounter <= UART_TIME_OUT ))
		 {
			 	 Local_u8TimeOutCounter++;
		 }

		 if (Local_u8TimeOutCounter <= UART_TIME_OUT)
		 {
			 UART_u8_UDR_REG= Copy_u8Character;

		 }
		 else
		 {
			 Local_u8ErrorState = TIME_OUT_ERROR;
		 }

		 UART_u8_UARTState = IDLE;
	}
	else
	{
		Local_u8ErrorState = FUNCTION_BUSY;
	}

	return Local_u8ErrorState;

}

/* Function   : M_UART_u8_Recievecharacter
 * Brief   	  : This Function receive character from outside the AVR using the UART communication protocol
 * Parameters : Copy_Pu8Character
 * return     : function error State
 */

u8  M_UART_u8_Recievecharacter(u8 * Copy_Pu8Character)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8TimeOutCounter= 0;
	if (UART_u8_UARTState == IDLE)
	{
		UART_u8_UARTState = BUSY;

		while (GET_BIT(UART_u8_UCSRA_REG,UCSRA_RXC) == 0 && (Local_u8TimeOutCounter <= UART_TIME_OUT ))
		{
			Local_u8TimeOutCounter++;
		}

		 if (Local_u8TimeOutCounter <= UART_TIME_OUT)
		 {
			 *Copy_Pu8Character = UART_u8_UDR_REG;
		 }
		 else
		 {
			 Local_u8ErrorState = TIME_OUT_ERROR;
		 }

		 UART_u8_UARTState = IDLE;


	}
	else
	{
		Local_u8ErrorState = FUNCTION_BUSY;
	}
	return Local_u8ErrorState;
}


/* Function   : M_UART_u8_SendStringSynch
 * Brief   	  : This Function send string using synch mechanism technique
 * Parameters : Copy_Pu8String
 * return     : function error State
 */

u8 M_UART_u8_SendStringSynch(u8 * Copy_Pu8String)
{
	u8 Local_u8ErrorState = STD_TYPES_OK ;
	u8 Local_u8StringIterrator =0 ;

	if (Copy_Pu8String != NULL)
	{

			while (Copy_Pu8String[Local_u8StringIterrator] != '\0')
			{
				if (M_UART_u8_UARTSendCharacter(Copy_Pu8String[Local_u8StringIterrator]) == STD_TYPES_OK)
				{
					Local_u8StringIterrator++;
				}
				else
				{
					return Local_u8ErrorState;
				}

			}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;

}

/* Function   : M_UART_u8SendStringAsynch
 * Brief   	  : This Function send string using Asynchronous mechanism technique
 * Parameters : Copy_Pu8String , AppCallBackFunction
 * return     : function error State
 */

u8 M_UART_u8SendStringAsynch(u8 * Copy_Pu8String , void (* AppCallBackFunction) (void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if (UART_u8_UARTState == IDLE)
	{

		if ((Copy_Pu8String != NULL) && (AppCallBackFunction != NULL))
		{
			/* UART is Busy*/
			UART_u8_UARTState = BUSY;

			/* Assign the string to the string buffer */
			UART_Pu8sendStringBuffer = Copy_Pu8String ;


			/* Assign the call back function */
			UART_PvoidCallBackFunction = AppCallBackFunction ;


			/* send the first Bit */
			UART_u8_UDR_REG = UART_Pu8sendStringBuffer[UART_u8StringIterrator];
			UART_u8StringIterrator ++;

			/* Enable the Transmit complete interrupt  */
			SET_BIT(UART_u8_UCSRB_REG,UCSRB_TXCIE);

		}
		else
		{
			Local_u8ErrorState =STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = FUNCTION_BUSY ;
	}

	return Local_u8ErrorState;
}


/* Function   : M_UART_u8RecieveBufferSynch
 * Brief   	  : This Function receive string using synchronous technique
 * Parameters : => Copy_Pu8String
 * 				=> Copy_u8StringIterator
 * return     : function error State
 */

u8 M_UART_u8RecieveBufferSynch (u8 * Copy_Pu8String , u8 Copy_u8StringIterator)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8StringIterator =0;

	if (Copy_Pu8String != NULL)
	{

		while (Local_u8StringIterator < Copy_u8StringIterator)
		{
			if (M_UART_u8_Recievecharacter(&Copy_Pu8String[Local_u8StringIterator]) == STD_TYPES_OK)
			{
				Local_u8StringIterator++;
			}
			else
			{
				return Local_u8ErrorState;
			}
		}


	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;



}


/* Function   : M_UART_u8RecieveBufferASynch
 * Brief   	  : This Function receive string using Asynchronous technique
 * Parameters : => Copy_Pu8String
 * 				=> Copy_u8StringIterator
 * 				=>AppCallBackFunction
 * return     : function error State
 */

u8 M_UART_u8RecieveBufferASynch (u8 * Copy_Pu8String , u8 Copy_u8StringSize , void (* AppCallBackFunction) (void))
{
	u8 Loca_u8ErrorState = STD_TYPES_OK;

	if (UART_u8_UARTState == IDLE)
	{
		if ( (Copy_Pu8String != NULL ) && (AppCallBackFunction != NULL ))
		{
			/* UART is Busy */
			UART_u8_UARTState = BUSY;

			/*Assign the Received pointer  */
			UART_Pu8sendReceiveBuffer = Copy_Pu8String;

			/* Assign the Call back function */
			UART_PvoidCallBackFunction = AppCallBackFunction ;

			/* Assign the buffer Size */
			UART_u8BufferSize = Copy_u8StringSize ;

			/* set the index of the first element */
			UART_u8StringIterrator = 0 ;

			/* Enable the RX completer interrupt */
			SET_BIT(UART_u8_UCSRB_REG,UCSRB_RXCIE);

		}
		else
		{
			Loca_u8ErrorState = STD_TYPES_NOK;
		}

	}

	else
	{
		Loca_u8ErrorState = FUNCTION_BUSY ;
	}
	return Loca_u8ErrorState;

}


/* ISR of TX complete */
void __vector_15 (void)		__attribute__ ((signal)) ;
void __vector_15 (void)
{

	if ( (UART_Pu8sendStringBuffer[UART_u8StringIterrator]) != '\0')
	{
		UART_u8_UDR_REG = UART_Pu8sendStringBuffer[UART_u8StringIterrator];
		UART_u8StringIterrator++;
	}
	else
	{

		/* Assign the String Iterator to zero*/
		UART_u8StringIterrator = 0;

		/* Back the state to IDLE*/
		UART_u8_UARTState  = IDLE;

		/* Call the application function */
		UART_PvoidCallBackFunction();

		/* Disable the TX complete interrupt */
		CLR_BIT(UART_u8_UCSRB_REG,UCSRB_TXCIE);
	}

}

/* ISR of RX complete */
void __vector_13 (void)		__attribute__ ((signal)) ;
void __vector_13 (void)
{
	/* receive the Next character  */
	 UART_Pu8sendReceiveBuffer[UART_u8StringIterrator]= UART_u8_UDR_REG;

	 /* increment the string iterator */
	 UART_u8StringIterrator++;

	 /* check if buffer size */
	 if (UART_u8StringIterrator >= UART_u8BufferSize)
	 {
			/* UART is Available */
			UART_u8_UARTState = IDLE;

			/* Assign the string iterator with zero for the next operations */
			UART_u8StringIterrator = 0 ;

			/* Call the Application function */
			UART_PvoidCallBackFunction();

			/* Disable the RX complete interrupt */
			CLR_BIT(UART_u8_UCSRB_REG,UCSRB_RXCIE);
	 }

}

