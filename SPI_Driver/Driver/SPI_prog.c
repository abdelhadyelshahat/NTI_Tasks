/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SPI_prog.c*****************/


/*
*** Layer : MCAL
*** Author : Abdelhady
*** version :1.0
*/

/*LIB includes*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL includes*/
#include "SPI_interface.h"
#include "SPI_privite.h"
#include "SPI_config.h"

/* Global pointers for Asynchronous functions */

/*Global Pointer to the transmitted string */
static u8 *SPI_Pu8StringTranmitted = NULL ;

static u8 *SPI_Pu8StringRecivied = NULL ;

static u8 SPI_Pu8GlobalItrrraor = 0 ;

static void (*SPI_Notification)(void) = NULL ;

static volatile u8 SPI_u8StateFlag = IDLE ;

void SPI_voidInit (void)
{		/* selecting the opreation mode */
	#if SPI_OPREATION_MODE == SPI_MASTER_MODE

		/* select the master mode */
		SET_BIT(SPI_SPCR_REG,MSTR_BIT);	
		
		/********************** selecting the clock rate **************/
		#if SPI_CLOCK_RATE == SPI_CLOCK_OVER_64
			SET_BIT(SPI_SPCR_REG,SPR1_BIT);
			CLR_BIT(SPI_SPCR_REG,SPR0_BIT);
			
		#elif SPI_CLOCK_RATE == SPI_CLOCK_OVER_4
			SET_BIT(SPI_SPCR_REG,SPR1_BIT);
			CLR_BIT(SPI_SPCR_REG,SPR0_BIT);
		
		#elif SPI_CLOCK_RATE == SPI_CLOCK_OVER_16
			CLR_BIT(SPI_SPCR_REG,SPR1_BIT);
			SET_BIT(SPI_SPCR_REG,SPR0_BIT);
		
		#elif SPI_CLOCK_RATE == SPI_CLOCK_OVER_128
			SET_BIT(SPI_SPCR_REG,SPR1_BIT);
			SET_BIT(SPI_SPCR_REG,SPR0_BIT);
		
		#endif
		/***************************************************************/
		
	#elif SPI_OPREATION_MODE == SPI_SLAVE_MODE
		/* select the Slave mode */
		CLR_BIT(SPI_SPCR_REG,MSTR_BIT);
	#endif
	
		/* selecting the interrupt mode  */
	#if SPI_INTERRUPT_MODE == SPI_INTERRUPT_EN
		SET_BIT(SPI_SPCR_REG,SPIE_BIT);
	
	#elif SPI_INTERRUPT_MODE == SPI_INTERRUPT_DIS
		CLR_BIT(SPI_SPCR_REG,SPIE_BIT);
	#endif 
	
		/* selecting data order read direction */ 
	#if SPI_DATA_ORDER_DIRECTION_MODE == SPI_DODR_LSB_FIRST
		SET_BIT(SPI_SPCR_REG,DORD_BIT);
	#elif SPI_DATA_ORDER_DIRECTION_MODE == SPI_DODR_MSB_FIRST
		CLR_BIT(SPI_SPCR_REG,DORD_BIT);
	#endif 
	
		/* select Clock polrity */
	#if SPI_CPOL_MODE == SPI_CPOL_RISING_LEADING
		CLR_BIT(SPI_SPCR_REG,CPOL_BIT);
	#elif SPI_CPOL_MODE == SPI_CPOL_FALLING_LEADING
		SET_BIT(SPI_SPCR_REG,CPOL_BIT);
	#endif
	
		/* selecting clock phase*/
	#if SPI_CPHA_MODE == SPI_CPHL_SETUP_FIRET
		SET_BIT(SPI_SPCR_REG,CPHA_BIT);
	#elif SPI_CPHA_MODE == SPI_CPHL_SAMPLE_FIRET
		CLR_BIT(SPI_SPCR_REG,CPHA_BIT);
	#endif

	/*Enable the SPI */
	SET_BIT(SPI_SPCR_REG,SPE_BIT);



}



u8 SPI_u8TransRec (u8 Copy_u8TransData , u8 *Copy_Pu8RecData)

{
	u8 Local_u8ErrorState = STD_TYPES_NOK ;
	
	if (Copy_Pu8RecData != NULL)
	{
		
		/* start the transmation*/
		SPI_SPDR_REG = Copy_u8TransData ;
		
		/* waiting until the transimiting finisgh*/
		while (!(GET_BIT(SPI_SPSR_REG,SPIF_BIT))) ;
		
		/* read the recieved data */
		*Copy_Pu8RecData = SPI_SPDR_REG;
		
		Local_u8ErrorState = STD_TYPES_OK ;
			
	}		
	
	
	return Local_u8ErrorState ;
}


void SPI_u8TransData (u8 Copy_u8TransData)
{
	
	/* start the transmation*/
		SPI_SPDR_REG = Copy_u8TransData ;
		
	/* waiting until the transimiting finisgh*/
		while (!(GET_BIT(SPI_SPSR_REG,SPIF_BIT))) ;
	
	
}


u8 SPI_u8RecData (u8 *Copy_Pu8RecData)
{
	
	u8 Local_ErrorState = STD_TYPES_NOK ;
	if (Copy_Pu8RecData != NULL)
	{
		
		/* waiting until the transimiting finisgh*/
		while (!(GET_BIT(SPI_SPSR_REG,SPIF_BIT))) ;
		
		/* read the recieved data */
		*Copy_Pu8RecData = SPI_SPDR_REG;
		
		Local_ErrorState = STD_TYPES_OK ;
		
	}
	
	return Local_ErrorState;
	
}

u8 SPI_u8SendRecStringAsync (u8 *Copy_Pu8SendString , u8 *Copy_Pu8RecString, void (*NofificationFunc) (void))
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if (SPI_u8StateFlag == IDLE )
	{
		if ((Copy_Pu8SendString != NULL) && (Copy_Pu8RecString != NULL) && (NofificationFunc != NULL))
		{
			/* Assign the flag with busy State */
			SPI_u8StateFlag = BUSY ;

			/* Assign the transmitted string*/
			SPI_Pu8StringTranmitted =Copy_Pu8SendString ;

			/* Assign the received string */
			SPI_Pu8StringRecivied = Copy_Pu8RecString ;

			/* assign the notification function */
			SPI_Notification = NofificationFunc;

			/* sending the first char of string */
			SPI_SPDR_REG = Copy_Pu8SendString[SPI_Pu8GlobalItrrraor] ;

			/* Enable the interrupt of SPI*/
			SET_BIT(SPI_SPCR_REG,SPIE_BIT);

			Local_u8ErrorState = STD_TYPES_OK;
		}

	}

	return Local_u8ErrorState ;
}

void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{

	if ((SPI_Pu8StringTranmitted != NULL) && (SPI_Pu8StringRecivied != NULL) && (SPI_Notification!= NULL) )
	{
		/* received a byte */
		SPI_Pu8StringRecivied[SPI_Pu8GlobalItrrraor] = SPI_SPCR_REG ;
		/* incrementing the Iterator*/
		SPI_Pu8GlobalItrrraor++;

		if (SPI_Pu8StringTranmitted[SPI_Pu8GlobalItrrraor] == '\0')
		{
			/* Assign the global iterator with 0 */
			SPI_Pu8GlobalItrrraor =0;
			/* calling the notification function */
			SPI_Notification();
			/* Disable the interrupt*/
			CLR_BIT(SPI_SPCR_REG,SPIE_BIT);
			/* assign the flag with IDLE case */
			SPI_u8StateFlag = IDLE ;

		}
		else
		{
			SPI_SPCR_REG = SPI_Pu8StringTranmitted[SPI_Pu8GlobalItrrraor] ;
		}


	}



}
