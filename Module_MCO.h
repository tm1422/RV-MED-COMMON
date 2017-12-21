#ifndef MODULE_MCO_H
#define MODULE_MCO_H

/**
  ******************************************************************************
  * @file    Module_MCO.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    07-September-2017
  * @last    07-September-2017
  * @brief   Functions prototypes for the MCO used in
             Medicop STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <stdint.h>                                                           //
#include <Defines.h>                                                          //
#include <stm32f0xx_rcc.h>                                                    //
#include <Module_DEBUG.h>                                                     //
                                                                              //


/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint16_t Configuration_Table[12][16];                                  //
                                                                              //
                                                                              
                                                                              


/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
void MCO_SET();                                                               //
                                                                              //



/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void Module_MCO_Config(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler);     //
                                                                            
                                                                            
#endif