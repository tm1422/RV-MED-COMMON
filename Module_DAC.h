#ifndef MODULE_DAC_h
#define MODULE_DAC_h
/**
  ******************************************************************************
  * @file    Module_ADC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    22-August-2017
  * @last    13-December-2017
  * @brief   Functions prototypes for the DAC used in
             Medicop STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <Defines.h>                                                          //
#include <stdint.h>                                                           //
#include <Module_DEBUG.h>                                                     //
                                                                              //

/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //
                                                                              
/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
void DAC_SET();                                                               //
void DAC_SET_OUTPUT();                                                        //
                                                                              //
                                                                              
/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void DAC_Get_Enabled_DACs();                                                  //
                                                                              //
                                                                              
/* Debug ---------------------------------------------------------------------*/
                                                                              //
uint8_t DAC_Debug_Mode();                                                     //
                              
                              
#endif