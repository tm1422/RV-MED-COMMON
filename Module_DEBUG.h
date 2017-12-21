#ifndef MODULE_DEBUG_H
#define MODULE_DEBUG_H
/**
  ******************************************************************************
  * @file    Module_DEBUG.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    08-September-2017
  * @last    08-September-2017
  * @brief   Functions prototypes for DEBUG
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <stdint.h>                                                           //
                                                                              //
                                                                              //


/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
                                                                              //
                                                                              
                                                                              
/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void Debug_WordToStr(uint16_t input);                                         //
void Debug_WordToStr_no_trim(uint16_t input);                                 //
void Debug_LongToStr(uint32_t input);                                         //
void Debug_IntToStr(uint16_t input);                                          //
                                                                              //
                                                                              
                                                                              
#endif