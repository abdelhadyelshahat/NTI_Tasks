/*********************************************/
/********** Name : BIT_MATH.h **************/
/********* DAte : 20/06/2023 ***************/
/******** Author : Abdelhady Elshahat *****/
/******* version : 1.0 *******************/
/****************************************/


#ifndef _BIT_MATH_H_ 
#define _BIT_MATH_H_

/*function like macro to set a spacefic bit in reg*/
#define SET_BIT(REG_NAME,BIT_NUMBER) REG_NAME |= (1<<BIT_NUMBER)

/*function like macro to Clear a spacefic bit in reg*/
#define CLR_BIT(REG_NAME,BIT_NUMBER) REG_NAME &= ~(1<<BIT_NUMBER)

/*function like macro to get a spacefic bit in reg*/
#define GET_BIT(REG_NAME,BIT_NUMBER) ((REG_NAME>>BIT_NUMBER) & 0x01)

/*function like macro to toggle a spacefic bit in reg*/
#define TOG_BIT(REG_NAME,BIT_NUMBER) 	REG_NAME ^= (1<<BIT_NUMBER)


#endif
