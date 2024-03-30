
/*****************************************************************/
/* FILE DESCRIPTION:
----------------------------------------------------------------
*  file    : Systick.c
*  brief   : Systick Driver
*  details : 
*****************************************************************   
*
*/
/******************************************
  INCLUDES 
*******************************************/
#include "Std_Types.h"
#include "BitMath.h"
#include "Systick_int.h"
#include "Mcu_HW.h"

static void (*g_ptrfn) (void) = NULL;

/* configure Systick timer clock source .*/
void Systick_Init(Systick_clkSrc_t copy_Systick_clkSrc){
	
	switch(copy_Systick_clkSrc){
		case PIOSC_4: ST_CTRL_R = 0x00000000; break;
		case FCPU   : ST_CTRL_R = 0x00000004; break;
	}
}

/* configure Reload register with required counts. And enables timer and interrupt.*/
void Systick_startTimer(u32 copy_count){
	
	// adjust reload value
	ST_RELOAD_R =  copy_count;

	// clear current register value
	ST_CURRENT_R =0;

    
    // enables timer and interrupt.
		SET_BIT(ST_CTRL_R , 0);
		SET_BIT(ST_CTRL_R , 1);
		//SET_BIT(ST_CTRL_R , 2);
	
}
/* disables both timer and interrupt . */
void Systick_stopTimer(void){
		
	 // disable the timer and interrupt
	
	CLR_BIT(ST_CTRL_R , 0);
	CLR_BIT(ST_CTRL_R , 1);
	
}
/* configure the callback function to be used by the handler .*/
void Systick_setCallBack(void (*ptrfn) (void))
{
	if( ptrfn != NULL)
	{
		g_ptrfn = ptrfn;
	}
	else
	{
		// error state NULL pointer
	}
}

// SysTick interrupt handler
void SysTick_Handler(void) {
    if (g_ptrfn != NULL) {
        g_ptrfn();
    }
}


