#ifndef MODULE_GPIO_H
#define MODULE_GPIO_H
/**
  ******************************************************************************
  * @file    Module_ADC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    08-September-2017
  * @last    08-September-2017
  * @brief   Functions prototypes for the GPIO management
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <stdint.h>                                                           //
#include <Defines.h>                                                          //
#include <built_in.h>                                                         //
#include <Module_CRC.h>                                                       //
#include <eeprom.h>                                                           //
                                                                              //



/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //
                                                                              


/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
                                                                              //
void GPIO_SET();                                                              //
void GPIO_UPDATE_DOUT_STATES();                                               //
                                                                              //
                                                                              //

/* Debug ---------------------------------------------------------------------*/
                                                                              //
uint8_t GPIO_Debug_Mode();                                                    //
                      
                                                                          
                                                                          
#endif