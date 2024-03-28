/*
 * File Name  : 	R503_prog.c
 * Layer	  :		HAL
 * Created on :		Mar 22, 2024
 * Author	  : 	Abdelhady Elshahat Abdelhady
 */

#ifndef HAL_R503_INTERFACE_H_
#define HAL_R503_INTERFACE_H_

#include "../LIB/STD_TYPES.h"


/******************************** macros for character flies*****************/
#define R503_CHARACTER_FILE_1  0x01
#define R503_CHARACTER_FILE_2  0x02
/**************************************************************************/

/************************* Macros for ACKs*****************************/

/* This macro used to check the success of every operation*/
#define R503_PROCESS_COMPLETE   				 		0x00

/* Errors*/
#define R503_ERROR_WHEN_RECEIVING_DATA_PACKAGE  		0x01
#define R503_NO_FINGER_ON_THE_SENSOR			   		0x02
#define R503_FAIL_TO_ENROLL_THE_FINGER			  		0x03
#define R503_FAIL_TO_GEN_CHAR_FILE_DUE_TO_DISORDERLY  	0x06
#define R503_FAIL_TO_GEN_CHAR_FILE_DUE_TO_LACKNESS  	0x07
#define R503_FINGER_DO_NOT_MATCH					    0x08
#define R503_FAIL_TO_FIND_THE_MATCH_FINGER			    0x09
#define R503_FAIL_TO_COMBINE_THE_CHAR_FILE			    0x0A
#define R503_FAIL_TO_CLEAR_THE_FINGER_LIB		  		0x11
#define R503_FAIL_TO_DELETE_THE_TEMPLATE		  		0x10
/**************************************************************************/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Functions prototypes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

/************************* The third main functionality of the Finger Print **********************************/
/************************* ------ matching operation  1 : N --------   ********************************/

u8 Finger_Ps_Matchinf1toN (void);

/************************* The second main functionality of the Finger Print **********************************/
/************************* ------ matching operation  1 : 1--------   ********************************/

u8 Finger_Ps_Matching1to1(u16 Copy_u16FingerPrintID);


/************************* The first main functionality of the Finger Print **********************************/
/************************* ------ Enrollment operation  --------   ********************************/

u8 Finger_Ps_EnrollmentOpreation( u16 Copy_u16FingerPrintID);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/


/* Brief : this function to turn on the Aura Led and playing with it */
u8 FingerPs_AuraLedConfig (u8 Copy_u8CtrlCode,u8 Copy_u8Speed, u8 Copy_u8ColorIndex , u8 Copy_u8Times);


/** Brief : this function is used to load a template in a character file . */

u8 FingerPS_LoadCharFile(u16 Copy_u8FingurePrintTempleteID ,u8 Copy_u8CharcterFileNumber);



/* Brief : to check if the collected image in character buffer1 is
*			matched with a certain template uploaded in
*			character buffer2
**/

u8 FingerPS_match();



/* Brief : This function should delete a template in the template library */
u8 FingerPS_deleteFinger(u16 Copy_u8FingurePrintTempleteID);



/* Brief : this function is used to delete all templates in template library.*/

u8 FingerPS_emptyLibrary(void);


/*Brief : this function search and match 1 : N
 * 		 compare the character file from of the Two characters buffers with the All Library Fingers
 * 		 if matching or not return an ACK for it
 *
 * */

u8 FingerPS_searchFinger(u8 Copy_u8CharcterFileNumber);

/* Brief : this function is used to store template file in
*			template library saved in Flash Memory .
* */

u8 FingerPS_strTemplate(u16 Copy_u8FingurePrintTempleteID);


/* Brief : This function is used to generate template file from
*			combined character buffers.
* */

u8 FingerPS_genTemplate(void);

/* Brief : This function used to convert from Image stored in Img
*			buffer to a character file saved in a character file buffe
*/
u8 FingerPS_convertImg2CharFile(u8 Copy_u8CharcterFileNumber);

/* Brief : this function should generate Image which is stored
*			in image buffer in RAM of the module
*/
u8 FingerPS_genImg(void);

/* Brief : Perform handshake , this function is used to make
sure that communication is done successfully. */
u8 FingerPS_handShake();

/* Brief : This function receive the ACK massage from the sensor  */
u8 R503_u8_CheckACK(void);

#endif /* HAL_R503_INTERFACE_H_ */
