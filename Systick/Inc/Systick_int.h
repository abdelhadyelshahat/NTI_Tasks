/*****************************************************************/
/* FILE DESCRIPTION:
----------------------------------------------------------------
*  file     : SysTick.h
*  Module   : SysTick 
*  breif    : header file SysTick
*  
*****************************************************************   
*/
#ifndef SysTick_H
#define SysTick_H
/******************************************
  INCLUDES 
*******************************************/
#include "Std_Types.h"
#include "Systick_types.h"


/******************************************
   GLOBAL FUNCTIONS PROTOTYPES
*******************************************/

/* configure Systick timer clock source .*/
void Systick_Init(Systick_clkSrc_t copy_Systick_clkSrc);

/* configure Reload register with required counts. And enables timer and interrupt.*/
void Systick_startTimer(u32 copy_count);

/* disables both timer and interrupt . */
void Systick_stopTimer(void);

/* configure the callback function to be used by the handler .*/
void Systick_setCallBack(void (*ptrfn) (void));




#endif
