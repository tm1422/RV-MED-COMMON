#ifndef MODULE_CRC_H
#define MODULE_CRC_H

/**
  ******************************************************************************
  * @file    Module_CRC.h
  * @author  Toni Malovrh
  * @version V1.0.0
  * @date    16-August-2017
  * @brief   Functions prototypes for the hardware CRC calculations used in
             Medicop STM32F072 CAN modules
  ******************************************************************************
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
                                                                              //
#include <stdint.h>                                                           //
#include <Defines.h>                                                          //
#include <stm32f0xx_crc.h>                                                    //
#include <built_in.h>                                                         //
#include <stm32f0xx_rcc.h>                                                    //
#include <Module_DEBUG.h>                                                     //
#include <Module_CONFIG.h>                                                           //
                                                                              //

/* External ------------------------------------------------------------------*/
/* MUST be defined externally!                                                */
                                                                              //
extern uint8_t CAN_Buffer[32][8];                                             //
extern uint16_t Configuration_Table[12][16];                                  //
extern uint16_t REMOTE_RECEIVED_Configuration_Table[13][16];                  //
                                                                              //


/* Function prototypes - MAINS -----------------------------------------------*/
                                                                              //
uint32_t CRC_Calculate_Table(uint8_t Table_Nr);                               //
                                                                              //
                                                                              
                                                                              
/* Function prototypes - SUBS ------------------------------------------------*/
                                                                              //
void CRC_Config(uint32_t poly);                                               //
                                                                              //
                                                                              
/* Debug ---------------------------------------------------------------------*/
                                                                              //
uint8_t CRC_Debug_Mode();                                                     //


#endif                                                                              //