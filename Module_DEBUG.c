/**
  ******************************************************************************
  * @file    Module_ADC.c
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    08-September-2017
  * @last    08-September-2017
  * @brief   This file provides functions to manage the following
  *          functionalities of the DEBUG mode:
               - common int to string to UART functions
               - DEBUG mode can be selected for each library separatly in
                 configuration table
  *
*/


/* Includes ------------------------------------------------------------------*/
#include <Module_DEBUG.h>                                                     //
                                                                              //
                                                                              //
                                                                              

/******************************************************************************/
/************************  WORD TO TEXT TO UART  ******************************/
/******************************************************************************/
/* Debug_WordToStr() ---------------------------------------------------------*/
/*                                                                            //
    Function converts 16-bit unsigned integer and sends it as text on UART1   //
    Function includes trimm option for trailing spaces                        //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + unsigned 16 bit integer                                               //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/

void Debug_WordToStr(uint16_t input){
  uint8_t txt6[6];
    
  /* Convert unsigned 16-bit input integer to txt */
  WordToStr(input, txt6);
  
  /* Write left trimmed unsigned 16-bit integer as txt on UART1 */
  UART1_Write_Text(Ltrim(txt6));
}


/******************************************************************************/
/*************  WORD TO TEXT TO UART - NO RESULT TRIMMING *********************/
/******************************************************************************/
/* Debug_WordToStr_no_trim() -------------------------------------------------*/
/*                                                                            //
    Function converts 16-bit unsigned integer and sends it as text on UART1   //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + unsigned 16 bit integer                                               //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/

void Debug_WordToStr_no_trim(uint16_t input){
  uint8_t txt6[6];
    
  /* Convert unsigned 16-bit input integer to txt */
  WordToStr(input, txt6);
  
  /* Write unsigned 16-bit integer as txt on UART1 */
  UART1_Write_Text(txt6);
}


/******************************************************************************/
/************************  LONG TO TEXT TO UART  ******************************/
/******************************************************************************/
/* Debug_LongToStr() ---------------------------------------------------------*/
/*                                                                            //
    Function converts 32-bit signed integer and sends it as text on UART1     //
    Function includes trimm option for trailing spaces                        //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + signed 32 bit integer                                                 //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/

void Debug_LongToStr(uint32_t input){
  uint8_t txt12[12];
    
  /* Convert unsigned 32-bit input integer to txt */
  LongToStr(input, txt12);
  
  /* Write left trimmed 32-bit integer as txt on UART1 */
  UART1_Write_Text(Ltrim(txt12));
}

/******************************************************************************/
/************************  INT TO TEXT TO UART  *******************************/
/******************************************************************************/
/* Debug_IntToStr() ----------------------------------------------------------*/
/*                                                                            //
    Function converts 16-bit signed integer and sends it as text on UART1     //
    Function includes trimm option for trailing spaces                        //
    ______________________________________                                    //
                                                                              //
    INPUT VALUES:                                                             //
                                                                              //
      + signed 16 bit integer                                                 //
                                                                              //
    RETURN VALUE:                                                             //
                                                                              //
      + none                                                                  //
    ______________________________________                                    //
*/

void Debug_IntToStr(uint16_t input){
  uint8_t txt7[7];
    
  /* Convert 16-bit input integer to txt */
  IntToStr(input, txt7);
  
  /* Write left trimmed 16-bit integer as txt on UART1 */
  UART1_Write_Text(Ltrim(txt7));
}